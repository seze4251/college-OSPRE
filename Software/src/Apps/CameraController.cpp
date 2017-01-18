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

CameraController::CameraController(std::string hostName, int localPort, int watchDogPort) : watchDog(getSelector(), hostName, watchDogPort), pollTime(0), hostName(hostName), localPort(localPort) {
    std::cout<< "CameraController Constructor called" << std::endl;
    setAppl(this);
    accept.registerCallback(CameraController::handleCameraControllerConnections);
    p_ID = P_CameraController;
    watchDog.p_ID = p_ID;
}

CameraController::~CameraController() {
    
}

// Connect to WatchDog
bool CameraController::open() {
    //WatchDog Service
    if (watchDog.isConnected() == false) {
        watchDog.open();
    }
    
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
    return true;
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************

void CameraController::handleTimeout() {
    
}

void CameraController::handleCameraControllerConnections(int fd) {
    
}

// *******************************
//
// Message Handler Defualt Behavior Below, Need to Implement
//
// ********************************

// Message Handlers
void CameraController::handleProccessHealthAndStatusRequest(ProccessHealthAndStatusRequest* msg) {
    std::cout << "CameraController::handleProccessHealthAndStatusRequest():  Not Supported for CameraController" << std::endl;
    
}

void CameraController::handleProccessHealthAndStatusResponse(ProccessHealthAndStatusResponse* msg) {
    std::cerr << "CameraController::handleProccessHealthAndStatusResponse() Not Supported for CameraController" << std::endl;
}

void CameraController::handleCaptureImageRequest(CaptureImageRequest* msg) {
    std::cerr << "CameraController::handleCaptureImageRequest() Not Supported for CameraController" << std::endl;
}

void CameraController::handleDataRequest(DataRequest* msg) {
    std::cerr << "CameraController::handleDataRequest() Not Supported for CameraController" << std::endl;
}
void CameraController::handleEphemerisMessage(EphemerisMessage* msg) {
    std::cerr << "CameraController::handleEphemerisMessage() Not Supported for CameraController" << std::endl;
}
void CameraController::handleImageAdjustment(ImageAdjustment* msg) {
    std::cerr << "ScCoCameraControllermms::handleImageAdjustment() Not Supported for CameraController" << std::endl;
}
void CameraController::handleImageMessage(ImageMessage* msg) {
    std::cerr << "CameraController::handleImageMessage() Not Supported for CameraController" << std::endl;
}
void CameraController::handleOSPREStatus(OSPREStatus* msg) {
    std::cerr << "CameraController::handleOSPREStatus() Not Supported for CameraController" << std::endl;
}
void CameraController::handlePointingRequest(PointingRequest* msg) {
    std::cerr << "CameraController::handlePointingRequest() Not Supported for CameraController" << std::endl;
}

void CameraController::handleSolutionMessage(SolutionMessage* msg){
    std::cerr << "CameraController::handleSolutionMessage() Not Supported for CameraController" << std::endl;
}

