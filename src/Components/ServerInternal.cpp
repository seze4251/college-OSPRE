//
//  ServerInternal.cpp
//  ServerInternal
//
//  Created by Seth on 01/17/2017.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <unistd.h>

#include "ServerInternal.h"

ServiceInternal* ServerInternal::connections[ServerInternal::MaxClients];
ProcessID ServerInternal::p_ID_Static;

// Constructors
ServerInternal::ServerInternal(std::string hostName, int localPort, ProcessID p_ID) : accept(getSelector()), hostName(hostName), localPort(localPort), p_ID(p_ID) {
    accept.registerCallback(handleConnectionRequest);
    
    for (int i = 0; i < MaxClients; i++) {
        connections[i] = nullptr;
    }
    p_ID_Static = p_ID;
}

//Destructor
ServerInternal::~ServerInternal() {
    for (int i = 0; i < MaxClients; i++) {
        if ((connections[i] != nullptr)) {
            delete connections[i];
        }
    }
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
        ::close(fd);
        throw "ServerInternal::handleConnectionRequest() New Client Addition Failed, too many clients, Closed fd";
    }
    
    // if memory for ServiceInternal has not been created, allocate it
    if (connections[avail] == nullptr) {
        if ((p_ID_Static == P_CameraController) || (p_ID_Static == P_ImageProcessor)) {
            connections[avail] = new ServiceInternal(getAppl()->getSelector(), -1, IMAGE_SIZE * 4);
        } else {
            connections[avail] = new ServiceInternal(getAppl()->getSelector());
        }
    }
    
    if (connections[avail]->open(fd) == true) {
        // Register CallBack
        connections[avail]->registerCallback(handleMessage);
        
    } else {
        throw "handleConnectionRequest() New Client Addition Failed";
    }
}

bool ServerInternal::connectToAppl(std::string host, int port, ServiceInternal** service) {
    
    // Make Sure Service is not NULL
    if (service == nullptr) {
        throw "ServerInternal::connectToAppl(): service is a nullptr";
    }
    
    // Check to see if Client is already Connected
    if (*service != nullptr) {
        if ((*service)->isConnected() == true) {
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
        throw "ServerInternal::connectToAppl() New Client Addition Failed, too many clients";
        if (service != nullptr) {
            *service = nullptr;
        }
        return false;
        
    }
    
    
    // if memory for ServiceInternal has not been created, allocate it
    if (connections[avail] == nullptr) {
        if ((p_ID == P_CameraController) || (p_ID == P_ImageProcessor)) {
            connections[avail] = new ServiceInternal(getAppl()->getSelector(), -1, IMAGE_SIZE * 4);
            
        } else {
            connections[avail] = new ServiceInternal(getAppl()->getSelector());
        }
    }
    
    if (connections[avail]->open(host, port) == true) {
        // Register CallBack
        connections[avail]->registerCallback(handleMessage);
        
        if (service != nullptr) {
            *service = connections[avail];
        }
        return true;
        
    } else {
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
            ((ServerInternal*) getAppl())->handleProcessHealthAndStatusRequest((ProcessHealthAndStatusRequest*) msg, service);
            break;
            
        case I_ProcessHealthAndStatusResponse:
            ((ServerInternal*) getAppl())->handleProcessHealthAndStatusResponse((ProcessHealthAndStatusResponse*) msg, service);
            break;
            
        case I_SolutionMessage:
            ((ServerInternal*) getAppl())->handleSolutionMessage((SolutionMessage*) msg, service);
            break;
            
        default:
            throw "ServerInternal::handleMessage(): Unknown Message Type Recived";
            service->closeConnection();
    }
}


