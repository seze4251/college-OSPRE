//
//  ScComms.cpp
//  ScComms
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>

#include "ScComms.h"
#include "Service.h"

#define SCCOMMS_APPL_ID 1

ServiceExternal* ScComms::spacecraft;

ScComms::ScComms( std::string hostName, int localPort, int externalPort) : ServerInternal(hostName, localPort, P_ScComms), external_accept(getSelector()), externalPort(externalPort), pollTime(0) {
    std::cout<< " ScComms Constructor called" << std::endl;
    setAppl(this);
    external_accept.registerCallback(handleExternalConnection);
    spacecraft = nullptr;
    
    // Allocate Memory for Messages to Send
    processHealthMessage = new ProcessHealthAndStatusResponse();
    dataMessage = new DataMessage();
    externalOspreStatusMessage = new External_OSPREStatus(SCCOMMS_APPL_ID);
    externalPointingMessage = new External_PointingRequest(SCCOMMS_APPL_ID);
    externalSolutionMessage = new External_SolutionMessage(SCCOMMS_APPL_ID);
}

ScComms::~ScComms() {
    //Free Messages from Memory
    delete processHealthMessage;
    delete dataMessage;
    delete externalOspreStatusMessage;
    delete externalPointingMessage;
    delete externalSolutionMessage;
    
    if (spacecraft != nullptr) {
        delete spacecraft;
    }
}

void ScComms::open() {
    // Set Timeout to 1 minute
    setTimeoutTime(60, 0);
    
    //Internal Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            std::cerr << "ScComms Internal Server Socket Failed To Open, ScComms Exiting" << std::endl;
            exit(-1);
        }
        std::cout << "ScComms Internal Server Socket Opened" << std::endl;
    }
    
    // External Acceptor
    if (external_accept.isConnected() == false) {
        if(external_accept.open(hostName, externalPort) == false) {
            std::cerr << "ScComms External Server Socket Failed To Open, ScComms Exiting" << std::endl;
            exit(-1);
        }
        std::cout << "ScComms External Server Socket Opened" << std::endl;
    }
    
}

/*
 1. Need to check that all connections are still open
 */
void ScComms::handleTimeout() {
    this->open();
}

// *******************************
//
// Application Functionality:
//
// ********************************

void ScComms::handleExternalConnection(int fd) {
    // File Descriptors less than 0 are invalid
    if (fd < 0) {
        std::cout << "ScComms::handleExternalConnection() Invalid File Descriptor" << std::endl;
        return;
    }
    
    // If spacecraft hasn't connected before, allocate memory for Service External
    if (spacecraft == nullptr) {
        spacecraft = new ServiceExternal(appl->getSelector());
        spacecraft->registerCallback(handleExternalMessage);
    }
    
    // If the spacecraft is already connected, close current connection only one instance of client (spacecraft) is allowed
    if (spacecraft->isConnected()) {
        spacecraft->closeConnection();
    }
    
    spacecraft->open(fd);
}

void ScComms::handleExternalMessage(Message_External* msg, ServiceExternal* service) {
    switch (msg->iden) {
        case E_OSPREStatus:
            ((ScComms*) getAppl())->handleExternalOSPREStatusMessage((External_OSPREStatus*) msg, service);
            break;
            
        case E_PointingRequest:
            ((ScComms*) getAppl())->handleExternalPointingMessage((External_PointingRequest*) msg, service);
            break;
            
        case E_SolutionMessage:
            ((ScComms*) getAppl())->handleExternalSolutionMessage((External_SolutionMessage*) msg, service);
            break;
            
        case E_SpacecraftDataMessage:
            ((ScComms*) getAppl())->handleExternalDataMessage((External_DataMessage*) msg, service);
            break;
            
        default:
            std::cerr << "ScComms::handleExternalMessage(): Unknown Message Type Recived: " << msg->iden << std::endl;
            std::cerr << "Closing Connection" << std::endl;
            service->closeConnection();
    }
}


// *******************************
//
// Message Handlers: Supported on ScComms
//  INTERNAL MESSAGES
//
// ********************************

void ScComms::handleProcessHealthAndStatusRequest(ProcessHealthAndStatusRequest* msg, ServiceInternal* service) {
    
    std::cout << "ScComms::handleProcessHealthAndStatusRequest(): Process Health and Status Response Received" << std::endl;
    
    // Update Status
    // TODO: Implement Status Update HERE
    
    // Update ProcessHealthAndStatusResponse Message
    processHealthMessage->update(status);
    
    // Send Status Message
    service->sendMessage(processHealthMessage);
    
    // Reset Status
    status.clear();
}


/*
 1. Send OSPRE Status to S/C
 */
void ScComms::handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service) {
    std::cout << "ScComms::handleOSPREStatus() OSPRE Status Message Recived" << std::endl;
    // Print Message
   // msg->print();
    
    // Convert OSPRE Status to External OSPRE Status
    externalOspreStatusMessage->update(msg->error);
    
    if ((spacecraft != nullptr) && (spacecraft->isConnected())) {
        spacecraft->sendMessage(externalOspreStatusMessage);
    }
}

/*
 1. Send Pointing Request to S/C
 */
void ScComms::handlePointingRequest(PointingRequest* msg, ServiceInternal* service) {
    std::cout << "ScComms::handlePointingRequest() Pointing Request Received" << std::endl;
    // Print Message
    //msg->print();
    
    // Convert Pointing Request to External Pointing Request
    externalPointingMessage->update(msg->point);
    
    if ((spacecraft != nullptr) && (spacecraft->isConnected())) {
        spacecraft->sendMessage(externalPointingMessage);
    }
    

}

/*
 1. Send Solution Message to S/C
 */
void ScComms::handleSolutionMessage(SolutionMessage* msg, ServiceInternal* service){
    std::cout << "ScComms::handleSolutionMessage() Solution message Recived" << std::endl;
    // Print Message
    //msg->print();
    
    // Convert Internal Solution Message to External Solution Message
    externalSolutionMessage->update(msg->position, msg->positionError, msg->velocity, msg->velocityError, msg->earthScMoonAngle);
    
    if ((spacecraft != nullptr) && (spacecraft->isConnected())) {
        spacecraft->sendMessage(externalSolutionMessage);
    }
    

}

// *******************************
//
// Message Handlers: Supported on ScComms
//  External Messages
//
// ********************************
/*
 1. Foward Data Message to everyone
 */
void ScComms::handleExternalDataMessage(External_DataMessage* msg, ServiceExternal* service) {
    std::cout << "ScComms::handleExternalDataMessage() External Data Message Received" << std::endl;
   // msg->print();
    
    // Conver External Data Message to internal Data Message
    dataMessage->update(msg->ephem, msg->quat, msg->angularVelocity, msg->satTime, msg->sunAngle, msg->sleep);
    
    //Send Data Message
    for (int i = 0; i < MaxClients; i++) {
        if ((connections[i] != nullptr) && (connections[i]->isConnected())) {
            connections[i]->sendMessage(dataMessage);
        }
    }
}

void ScComms::handleExternalOSPREStatusMessage(External_OSPREStatus* msg, ServiceExternal* service) {
    std::cout << "ScComms::handleExternalOSPREStatusMessage() not implemented, exiting process..." << std::endl;
    exit(-1);
}
void ScComms::handleExternalPointingMessage(External_PointingRequest* msg, ServiceExternal* service) {
    std::cout << "ScComms::handleExternalPointingMessage() not implemented, exiting process..." << std::endl;
    exit(-1);
}
void ScComms::handleExternalSolutionMessage(External_SolutionMessage* msg, ServiceExternal* service) {
    std::cout << "ScComms::handleExternalSolutionMessage() not implemented, exiting process..." << std::endl;
    exit(-1);
}

// *******************************
//
// Message Handlers: Not Supported on ScComms
//
// ********************************
void ScComms::handleProcessHealthAndStatusResponse(ProcessHealthAndStatusResponse* msg, ServiceInternal* service) {
    std::cerr << "ScComms::handleProcessHealthAndStatusResponse() Not Supported for ScComms" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void ScComms::handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service) {
    std::cerr << "ScComms::handleCaptureImageRequest() Not Supported for ScComms" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void ScComms::handleImageAdjustment(ImageAdjustment* msg, ServiceInternal* service) {
    std::cerr << "ScComms::handleImageAdjustment() Not Supported for ScComms" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void ScComms::handleImageMessage(ImageMessage* msg, ServiceInternal* service) {
    std::cerr << "ScComms::handleImageMessage() Not Supported for ScComms" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void ScComms::handleProcessedImageMessage(ProcessedImageMessage* msg, ServiceInternal* service) {
    std::cerr << "ScComms::handleProcessedImageMessage() Not Supported for ScComms" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void ScComms::handleDataMessage(DataMessage* msg, ServiceInternal* service) {
    std::cerr << "ScComms::handleDataMessage() Not Supported for ScComms" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}







