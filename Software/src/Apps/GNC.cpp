//
//  GNC.cpp
//  GNC
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>

#include "GNC.h"
#include "Service.h"

GNC::GNC(std::string hostName, int localPort, int watchDogPort) : ServerInternal(hostName, localPort, P_GNC), watchDogPort(watchDogPort) {
    std::cout<< "GNC Constructor called" << std::endl;
    setAppl(this);
}

GNC::~GNC() {
    
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************

bool GNC::open() {
    //Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            std::cerr << "CameraController Server Socket Failed To Open, CameraController Exiting" << std::endl;
            exit(-1);
        }
        std::cout << "CameraController Server Socket Opened" << std::endl;
    }
    
    // Other Services
    // TODO: Change Bool to something more useful
    if (connectionCount < ServerInternal::MaxClients) {
        connections[connectionCount] = new ServiceInternal(getAppl()->getSelector());
        if (connections[connectionCount]->open(hostName, watchDogPort) == true) {
            // Register CallBack
            connections[connectionCount]->registerCallback(handleMessage);
            std::cout << "handleConnectionRequest() New Client Added" << std::endl;
            connectionCount++;
        } else {
            std::cout << "handleConnectionRequest() New Client Addition Failed" << std::endl;
        }
        
        return true;
    } else {
        std::cout << "handleConnectionRequest() New Client Addition Failed, too many clients" << std::endl;
        return false;
    }
}

void GNC::handleTimeout() {
    
}

// *******************************
//
// Message Handler Defualt Behavior Below, Need to Implement
//
// ********************************

// Message Handlers
void GNC::handleProccessHealthAndStatusRequest(ProccessHealthAndStatusRequest* msg, ServiceInternal* service) {
    std::cout << "WatchDogService::handleProccessHealthAndStatusRequest(): Process Health and Status Response Received" << std::endl;
    service->sendStatusResponseMessage(p_ID);
}

void GNC::handleProccessHealthAndStatusResponse(ProccessHealthAndStatusResponse* msg, ServiceInternal* service) {
    std::cerr << "GNC::handleProccessHealthAndStatusResponse() Not Supported for GNC" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void GNC::handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service) {
    std::cerr << "GNC::handleCaptureImageRequest() Not Supported for GNC" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void GNC::handleDataRequest(DataRequest* msg, ServiceInternal* service) {
    std::cerr << "GNC::handleDataRequest() Not Supported for GNC" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void GNC::handleEphemerisMessage(EphemerisMessage* msg, ServiceInternal* service) {
    std::cerr << "GNC::handleEphemerisMessage() Not Supported for GNC" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void GNC::handleImageAdjustment(ImageAdjustment* msg, ServiceInternal* service) {
    std::cerr << "GNC::handleImageAdjustment() Not Supported for GNC" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void GNC::handleImageMessage(ImageMessage* msg, ServiceInternal* service) {
    std::cerr << "GNC::handleImageMessage() Not Supported for GNC" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void GNC::handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service) {
    std::cerr << "GNC::handleOSPREStatus() Not Supported for GNC" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void GNC::handlePointingRequest(PointingRequest* msg, ServiceInternal* service) {
    std::cerr << "GNC::handlePointingRequest() Not Supported for GNC" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void GNC::handleSolutionMessage(SolutionMessage* msg, ServiceInternal* service){
    std::cerr << "GNC::handleSolutionMessage() Not Supported for GNC" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

