//
//  CameraController.cpp
//  CameraController
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>

#include "CameraController.h"
#include "Service.h"

CameraController::CameraController(std::string hostName, int localPort, int watchDogPort) : ServerInternal(hostName, localPort, P_CameraController), watchDogPort(watchDogPort) {
    std::cout<< "CameraController Constructor called" << std::endl;
    setAppl(this);
}

CameraController::~CameraController() {
    
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************

// Connect to WatchDog
bool CameraController::open() {
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

void CameraController::handleTimeout() {
    
}

// *******************************
//
// Message Handler Defualt Behavior Below, Need to Implement
//
// ********************************

// Message Handlers
void CameraController::handleProccessHealthAndStatusRequest(ProccessHealthAndStatusRequest* msg, ServiceInternal* service) {
    std::cout << "WatchDogService::handleProccessHealthAndStatusRequest(): Process Health and Status Response Received" << std::endl;
    service->sendStatusResponseMessage(p_ID);
}

void CameraController::handleProccessHealthAndStatusResponse(ProccessHealthAndStatusResponse* msg, ServiceInternal* service) {
    std::cerr << "CameraController::handleProccessHealthAndStatusResponse() Not Supported for CameraController" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}


void CameraController::handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service) {
    std::cerr << "CameraController::handleCaptureImageRequest() Not Supported for CameraController" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void CameraController::handleDataRequest(DataRequest* msg, ServiceInternal* service) {
    std::cerr << "CameraController::handleDataRequest() Not Supported for CameraController" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void CameraController::handleEphemerisMessage(EphemerisMessage* msg, ServiceInternal* service) {
    std::cerr << "CameraController::handleEphemerisMessage() Not Supported for CameraController" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void CameraController::handleImageAdjustment(ImageAdjustment* msg, ServiceInternal* service) {
    std::cerr << "ScCoCameraControllermms::handleImageAdjustment() Not Supported for CameraController" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void CameraController::handleImageMessage(ImageMessage* msg, ServiceInternal* service) {
    std::cerr << "CameraController::handleImageMessage() Not Supported for CameraController" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void CameraController::handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service) {
    std::cerr << "CameraController::handleOSPREStatus() Not Supported for CameraController" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void CameraController::handlePointingRequest(PointingRequest* msg, ServiceInternal* service) {
    std::cerr << "CameraController::handlePointingRequest() Not Supported for CameraController" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void CameraController::handleSolutionMessage(SolutionMessage* msg, ServiceInternal* service){
    std::cerr << "CameraController::handleSolutionMessage() Not Supported for CameraController" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

