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

ServiceInternal* ServerInternal::connections[ServerInternal::MaxClients];

// Constructors
ServerInternal::ServerInternal(std::string hostName, int localPort, ProcessID p_ID) : accept(getSelector()), hostName(hostName), localPort(localPort), p_ID(p_ID) {
    std::cout << "ServerInternal Constructor called" << std::endl;
    
    accept.registerCallback(handleConnectionRequest);
    
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
    int avail = -1;
    for (int i = 0; i < ServerInternal::MaxClients; i++) {
        if (connections[i] == nullptr) {
            avail = i;
            break;
        }
        
        if (connections[i]->isConnected() == false) {
            avail = i;
            break;
        }
    }
    
    if (avail == -1) {
        std::cout << "ServerInternal::handleConnectionRequest() New Client Addition Failed, too many clients" << std::endl;
        ::close(fd);
        return;
        
    }
    
    // if memory for ServiceInternal has not been created, allocate it
    if (connections[avail] == nullptr) {
        connections[avail] = new ServiceInternal(getAppl()->getSelector());
    }
    
    if (connections[avail]->open(fd) == true) {
        // Register CallBack
        connections[avail]->registerCallback(handleMessage);
        std::cout << "ServerInternal::handleConnectionRequest() New Client Added" << std::endl;
        
    } else {
        std::cout << "handleConnectionRequest() New Client Addition Failed" << std::endl;
    }
}

bool ServerInternal::connectToAppl(std::string host, int port, ServiceInternal** service) {
    
    // Make Sure Service is not NULL
    if (service == nullptr) {
        std::cout << "ServerInternal::connectToAppl(): service is a nullptr" << std::endl;
        return false;
    }
    
    // Check to see if Client is already Connected
    if (*service != nullptr) {
        if ((*service)->isConnected() == true) {
            std::cout << "ServerInternal::connectToAppl(): Service is already connected" << std::endl;
            return true;
        }
    }
    
    // Look for available space in connection array
    int avail = -1;
    for (int i = 0; i < ServerInternal::MaxClients; i++) {
        if (connections[i] == nullptr) {
            avail = i;
            break;
        }
        
        if (connections[i]->isConnected() == false) {
            avail = i;
            break;
        }
    }
    
    // No available space to add a service
    if (avail == -1) {
        std::cout << "ServerInternal::connectToAppl() New Client Addition Failed, too many clients" << std::endl;
        if (service != nullptr) {
            *service = nullptr;
        }
        return false;
        
    }
    
    
    // if memory for ServiceInternal has not been created, allocate it
    if (connections[avail] == nullptr) {
        connections[avail] = new ServiceInternal(getAppl()->getSelector());
    }
    
    if (connections[avail]->open(host, port) == true) {
        // Register CallBack
        connections[avail]->registerCallback(handleMessage);
        std::cout << "ServerInternal::connectToAppl(): New Client Added" << std::endl;
        
        if (service != nullptr) {
            *service = connections[avail];
        }
        return true;
        
    } else {
        std::cout << "ServerInternal::connectToAppl(): New Client Addition Failed" << std::endl;
        *service = nullptr;
        return false;
    }
}

void ServerInternal::handleMessage(Message* msg, ServiceInternal* service) {
    switch (msg->iden) {
        case I_CaptureImageRequest:
            ((ServerInternal*) getAppl())->handleCaptureImageRequest((CaptureImageRequest*) msg, service);
            break;
            
        case I_ProcessedImageMessage:
            ((ServerInternal*) getAppl())->handleProcessedImageMessage((ProcessedImageMessage*) msg, service);
            break;
            
        case I_DataMessage:
            ((ServerInternal*) getAppl())->handleDataMessage((DataMessage*) msg, service);
            break;
            
        case I_ImageAdjustment:
            ((ServerInternal*) getAppl())->handleImageAdjustment((ImageAdjustment*) msg, service);
            break;
            
        case I_ImageMessage:
            ((ServerInternal*) getAppl())->handleImageMessage((ImageMessage*) msg, service);
            break;
            
        case I_OSPREStatus:
            ((ServerInternal*) getAppl())->handleOSPREStatus((OSPREStatus*) msg, service);
            break;
            
        case I_PointingRequest:
            ((ServerInternal*) getAppl())->handlePointingRequest((PointingRequest*) msg, service);
            break;
            
        case I_ProcessHealthAndStatusRequest:
            std::cout << "Entering handleProcessHealthAndStatusRequest" << std::endl;
            ((ServerInternal*) getAppl())->handleProcessHealthAndStatusRequest((ProcessHealthAndStatusRequest*) msg, service);
            break;
            
        case I_ProcessHealthAndStatusResponse:
            ((ServerInternal*) getAppl())->handleProcessHealthAndStatusResponse((ProcessHealthAndStatusResponse*) msg, service);
            break;
            
        case I_SolutionMessage:
            ((ServerInternal*) getAppl())->handleSolutionMessage((SolutionMessage*) msg, service);
            break;
            
        default:
            std::cerr << "ServerInternal::handleMessage(): Unknown Message Type Recived: " << msg->iden << std::endl;
            //TODO:: FIGURE OUT WAY TO THROW EXCEPTION OR CLOSE CONNECTION
            std::cerr << "Fatal Error: Closing Connection" << std::endl;
            service->closeConnection();
    }
    std::cout << "Leaving ServerInternal::handleMessage, back to ServiceInternal::handleRead()" << std::endl;
}


