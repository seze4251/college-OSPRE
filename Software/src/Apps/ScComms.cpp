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

ScComms::ScComms( std::string hostName, int localPort, int externalPort) : ServerInternal(hostName, localPort, P_ScComms), external_accept(getSelector()), externalPort(externalPort), pollTime(0) {
    std::cout<< " ScComms Constructor called" << std::endl;
    setAppl(this);
    external_accept.registerCallback(handleExternalConnection);
    spacecraft = nullptr;
    
    // Allocate Memory for Messages to Send
    processHealthMessage = new ProcessHealthAndStatusResponse();
    dataMessage = new DataMessage();
    externalOspreStatusMessage = new External_OSPREStatus();
    externalPointingMessage = new External_PointingRequest();
    externalSolutionMessage = new External_SolutionMessage();
}

ScComms::~ScComms() {
    //Free Messages from Memory
    delete processHealthMessage;
    delete dataMessage;
    delete externalOspreStatusMessage;
    delete externalPointingMessage;
    delete externalSolutionMessage;
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************
void ScComms::open() {
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
// TODO: Seth to complete
void ScComms::handleExternalConnection(int fd) {
    
}


// *******************************
//
// Message Handlers: Supported on ScComms
//
// ********************************

/*
 Determine Process Status
 Send Status to WatchDog
 */
void ScComms::handleProcessHealthAndStatusRequest(ProcessHealthAndStatusRequest* msg, ServiceInternal* service) {
    std::cout << "WatchDogService::handleProcessHealthAndStatusRequest(): Process Health and Status Response Received" << std::endl;
    
    // Update Status
    // TODO: Implement Status Update HERE
    
    // Update ProcessHealthAndStatusResponse Message
    processHealthMessage.update(status);
    
    // Send Status Message
    service->sendMessage(processHealthMessage);
    
    // Reset Status
    status.clear();
}

/*
 1. Foward Data Message to everyone 
 */
void ScComms::handleExternalDataMessage(External_DataMessage* msg) {
    std::cerr << "ScComms::handleExternalDataMessage() External Data Message Received" << std::endl;
    
    // TODO: Convert External Data Message to Data Message
    
    //Send Data Message
    for (int i = 1; i < MaxClients; i++) {
        if ((connections[i] != nullptr) && (connections[i]->isConnected())) {
            connections[i]->sendMessage(dataMessage);
        }
    }
}

/*
 1. Send OSPRE Status to S/C
 */
void ScComms::handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service) {
    std::cerr << "ScComms::handleOSPREStatus() OSPRE Status Message Recived" << std::endl;
    
    // TODO: Convert OSPRE Status Message to External OSPRE Status Message
    
    spacecraft->sendMessage(externalOspreStatusMessage)
}

/*
 1. Send Pointing Request to S/C
 */
void ScComms::handlePointingRequest(PointingRequest* msg, ServiceInternal* service) {
    std::cerr << "ScComms::handlePointingRequest() Pointing Request Received" << std::endl;
    
    // TODO: Convert Pointing Request Message to External Pointing Request Message
    
    spacecraft->sendMessage(externalPointingMessage)
}

/*
 1. Send Solution Message to S/C
 */
void ScComms::handleSolutionMessage(SolutionMessage* msg, ServiceInternal* service){
    std::cerr << "ScComms::handleSolutionMessage() Not Supported for ScComms" << std::endl;
    
    // TODO: Convert Solution Message to External Solution Message
    
    spacecraft->sendMessage(externalSolutionMessage)
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







