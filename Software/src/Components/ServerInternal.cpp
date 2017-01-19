//
//  ServerInternal.cpp
//  ServerInternal
//
//  Created by Seth on 01/17/2017.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>
#include <unistd.h>

#include "ServerInternal.h"

int ServerInternal::connectionCount;
ServiceInternal* ServerInternal::connections[ServerInternal::MaxClients];

// Constructors
ServerInternal::ServerInternal(std::string hostName, int localPort, ProcessID p_ID) : accept(getSelector()), pollTime(0), hostName(hostName), localPort(localPort), p_ID(p_ID) {
    std::cout << "ServerInternal Constructor called" << std::endl;
    
    accept.registerCallback(handleConnectionRequest);
    
    connectionCount = 0;
    for (int i = 0; i < MaxClients; i++) {
        connections[i] = nullptr;
    }
}

//Destructor
ServerInternal::~ServerInternal() {
    
}

// Public Methods
void ServerInternal::handleConnectionRequest(int fd) {
    // Check to make sure max client count is not exceeded
    if (connectionCount >= ServerInternal::MaxClients) {
        std::cout << "handleConnectionRequest() closing Connection: Too Many Connections" << std::endl;
        ::close(fd);
        return;
    }
    
    connections[connectionCount] = new ServiceInternal(getAppl()->getSelector());
    if (connections[connectionCount]->open(fd) == true) {
        connectionCount++;
        std::cout << "handleConnectionRequest() New Client Added" << std::endl;
    } else {
        std::cout << "handleConnectionRequest() New Client Addition Failed" << std::endl;
    }
}

void ServerInternal::handleMessage(Message* msg, ServiceInternal* service) {
    
    switch (msg->iden) {
        case I_CaptureImageRequest:
            handleCaptureImageRequest((CaptureImageRequest*) msg, service);
            break;
            
        case I_DataRequest:
            handleDataRequest((DataRequest*) msg, service);
            break;
            
        case I_EphemerisMessage:
            handleEphemerisMessage((EphemerisMessage*) msg, service);
            break;
            
        case I_ImageAdjustment:
            handleImageAdjustment((ImageAdjustment*) msg, service);
            break;
            
        case I_ImageMessage:
            handleImageMessage((ImageMessage*) msg, service);
            break;
            
        case I_OSPREStatus:
            handleOSPREStatus((OSPREStatus*) msg, service);
            break;
            
        case I_PointingRequest:
            handlePointingRequest((PointingRequest*) msg, service);
            break;
            
        case I_ProccessHealthAndStatusRequest:
            std::cout << "Entering handleProccessHealthAndStatusRequest" << std::endl;
            handleProccessHealthAndStatusRequest((ProccessHealthAndStatusRequest*) msg, service);
            break;
            
        case I_ProccessHealthAndStatusResponse:
            handleProccessHealthAndStatusResponse((ProccessHealthAndStatusResponse*) msg, service);
            break;
            
        case I_SolutionMessage:
            handleSolutionMessage((SolutionMessage*) msg, service);
            break;
            
        default:
            std::cerr << "ServerInternal::handleMessage(): Unknown Message Type Recived: " << msg->iden << std::endl;
            //TODO:: FIGURE OUT WAY TO THROW EXCEPTION OR CLOSE CONNECTION
            std::cerr << "Fatal Error: Closing Connection" << std::endl;
            service->closeConnection();
    }
}


