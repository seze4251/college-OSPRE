//
//  ScComms.cpp
//  ScComms
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>
#include <stdio.h>

#include "ScComms.h"
#include "Service.h"

#define SCCOMMS_APPL_ID 1

ServiceExternal* ScComms::spacecraft;

ScComms::ScComms( std::string hostName, int localPort, int externalPort) : ServerInternal(hostName, localPort, P_ScComms), external_accept(getSelector()), externalPort(externalPort), pollTime(0) {
    setAppl(this);
    external_accept.registerCallback(handleExternalConnection);
    spacecraft = nullptr;
    
    // Allocate Memory for Messages to Send
    processHealthMessage = new ProcessHealthAndStatusResponse();
    dataMessage = new DataMessage();
    externalOspreStatusMessage = new External_OSPREStatus(SCCOMMS_APPL_ID);
    externalPointingMessage = new External_PointingRequest(SCCOMMS_APPL_ID);
    externalSolutionMessage = new External_SolutionMessage(SCCOMMS_APPL_ID);
    
    // Initialize localError to healthy
    localError = PE_AllHealthy;
    logFile = nullptr;
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
    
    // Close Log File
    if (logFile)
        fclose(logFile);
}

void ScComms::open() {
    // Create File Name
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    
    rawtime = time(0);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80,"./log/ScCommsLog_%d-%m-%Y.log",timeinfo);
    
    // Open Log File
    logFile = fopen(buffer, "a+");
    
    // Log Application Starting
    fprintf(logFile, "ScComms Application Started, Time = %ld", time(0));
    
    // Set Timeout to 1 minute
    setTimeoutTime(60, 0);
    
    //Internal Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            fprintf(logFile, "Error: Unable to Open Internal Acceptor, Exiting...\n");
            exit(-1);
        }
        fprintf(logFile, "Connection: Internal Server Socket Opened\n");
    }
    
    // External Acceptor
    if (external_accept.isConnected() == false) {
        if(external_accept.open(hostName, externalPort) == false) {
            fprintf(logFile, "Error: Unable to Open External Acceptor, Exiting...\n");
            exit(-1);
        }
        fprintf(logFile, "Connection: External Server Socket Opened\n");
    }
}

/*
 1. Need to check that all connections are still open
 */
void ScComms::handleTimeout() {
    //Internal Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            fprintf(logFile, "Error: Unable to Open Internal Acceptor, Exiting...\n");
            exit(-1);
        }
        fprintf(logFile, "Connection: Internal Server Socket Opened\n");
    }
    
    // External Acceptor
    if (external_accept.isConnected() == false) {
        if(external_accept.open(hostName, externalPort) == false) {
            fprintf(logFile, "Error: Unable to Open External Acceptor, Exiting...\n");
            exit(-1);
        }
        fprintf(logFile, "Connection: External Server Socket Opened\n");
    }
    flushLog();
}

// *******************************
//
// Application Functionality:
//
// ********************************

void ScComms::handleExternalConnection(int fd) {
    // File Descriptors less than 0 are invalid
    if (fd < 0) {
        throw "handleExternalConnection() Invalid File Descriptor";
    }
    
    // If spacecraft hasn't connected before, allocate memory for Service External
    if (spacecraft == nullptr) {
        spacecraft = new ServiceExternal(appl->getSelector());
        spacecraft->registerCallback(handleExternalMessage);
    }
    
    // If the spacecraft is already connected, close current connection only one instance of client (spacecraft) is allowed
    if (spacecraft->isConnected()) {
        spacecraft->closeConnection();
        fprintf(logFile, "Error: Spacecraft is already connected to OSPRE, cannot have two spacecraft connections\n");
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
            service->closeConnection();
            throw "Error: ScComms::handleExternalMessage(): Unknown Message Type Recived, Closing Connection";
    }
}


// *******************************
//
// Message Handlers: Supported on ScComms
//  INTERNAL MESSAGES
//
// ********************************

void ScComms::handleProcessHealthAndStatusRequest(ProcessHealthAndStatusRequest* msg, ServiceInternal* service) {
    fprintf(logFile, "Received Message: ProcessHealthAndStatusRequest from WatchDog\n");
    msg->print(logFile);
    
    processHealthMessage->update(localError);
    
    service->sendMessage(processHealthMessage);
    fprintf(logFile, "Sent Message: StatusAndHealthResponse to WatchDog\n");
    
    // Reset Error Enum
    localError = PE_AllHealthy;
}


/*
 1. Send OSPRE Status to S/C
 */
void ScComms::handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service) {
    fprintf(logFile, "Received Message: OSPREStatus Message from WatchDog\n");
    msg->print(logFile);
    
    // Convert OSPRE Status to External OSPRE Status
    externalOspreStatusMessage->update(msg);
    
    if ((spacecraft != nullptr) && (spacecraft->isConnected())) {
        spacecraft->sendMessage(externalOspreStatusMessage);
        fprintf(logFile, "Sent Message: ExternalOSPREStatus to Spacecraft\n");
    }
}

/*
 1. Send Pointing Request to S/C
 */
void ScComms::handlePointingRequest(PointingRequest* msg, ServiceInternal* service) {
    fprintf(logFile, "Received Message: PointingRequest from GNC\n");
    msg->print(logFile);
    // Convert Pointing Request to External Pointing Request
    externalPointingMessage->update(msg->point);
    
    if ((spacecraft != nullptr) && (spacecraft->isConnected())) {
        spacecraft->sendMessage(externalPointingMessage);
        fprintf(logFile, "Sent Message: ExternalPointingRequest to Spacecraft\n");
    }
    
    
}

/*
 1. Send Solution Message to S/C
 */
void ScComms::handleSolutionMessage(SolutionMessage* msg, ServiceInternal* service){
    fprintf(logFile, "Received Message: SolutionMessage from GNC\n");
    msg->print(logFile);
    // Convert Internal Solution Message to External Solution Message
    externalSolutionMessage->update(msg->position, msg->positionError, msg->velocity, msg->velocityError, msg->earthScMoonAngle);
    
    if ((spacecraft != nullptr) && (spacecraft->isConnected())) {
        spacecraft->sendMessage(externalSolutionMessage);
        fprintf(logFile, "Sent Message: ExternalSolutionMessage to Spacecraft\n");
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
    fprintf(logFile, "Received Message: ExternalDataMessage from Spacecraft\n");
    msg->print(logFile);
    
    // Conver External Data Message to internal Data Message
    dataMessage->update(msg->ephem, msg->quat, msg->angularVelocity, msg->satTime, msg->sunAngle, msg->sleep);
    
    //Send Data Message
    for (int i = 0; i < MaxClients; i++) {
        if ((connections[i] != nullptr) && (connections[i]->isConnected())) {
            connections[i]->sendMessage(dataMessage);
            fprintf(logFile, "Sent Message: DataMessage to Client[%d]\n", i);
        }
    }
}

// *******************************
//
// Message Handlers: Not Supported on ScComms
//
// ********************************

void ScComms::handleExternalOSPREStatusMessage(External_OSPREStatus* msg, ServiceExternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: ExternalStatus, Closing Connection\n");
    service->closeConnection();
}
void ScComms::handleExternalPointingMessage(External_PointingRequest* msg, ServiceExternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: ExternalPointing, Closing Connection\n");
    service->closeConnection();
}
void ScComms::handleExternalSolutionMessage(External_SolutionMessage* msg, ServiceExternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: ExternalSolution, Closing Connection\n");
    service->closeConnection();
}

void ScComms::handleProcessHealthAndStatusResponse(ProcessHealthAndStatusResponse* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: Response, Closing Connection\n");
    service->closeConnection();
}

void ScComms::handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: CaptureImageRequest, Closing Connection\n");
    service->closeConnection();
}

void ScComms::handleImageAdjustment(ImageAdjustment* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: ImageAdjustment, Closing Connection\n");
    service->closeConnection();
}

void ScComms::handleImageMessage(ImageMessage* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: ImageMessage, Closing Connection\n");
    service->closeConnection();
}

void ScComms::handleProcessedImageMessage(ProcessedImageMessage* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: ProcessedImageMessage, Closing Connection\n");
    service->closeConnection();
}

void ScComms::handleDataMessage(DataMessage* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: DataMessage, Closing Connection\n");
    service->closeConnection();
}







