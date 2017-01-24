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
    imageProc = nullptr;
    scComms = nullptr;
    watchDog = nullptr;
}

CameraController::~CameraController() {
    
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************

// TODO: Change hard coded ports and hostnames to config file if time
// TODO: Decide if this function should return bool or void or something else

bool CameraController::open() {
    
    //Open Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            std::cerr << "CameraController Server Socket Failed To Open, CameraController Exiting" << std::endl;
            exit(-1);
        }
        std::cout << "CameraController Server Socket Opened" << std::endl;
    }
    
    //Connect to WatchDog
    if(connectToAppl(hostName, watchDogPort, &watchDog) == true) {
        std::cout << "CameraController: Connected to WatchDog" << std::endl;
    } else {
        std::cout << "CameraController: Failure to Connect to WatchDog" << std::endl;
    }
    
    //Connect to ScComms
    if(connectToAppl(hostName, 7000, &scComms) == true) {
        std::cout << "CameraController: Connected to ScComms" << std::endl;
    } else {
        std::cout << "CameraController: Failure to Connect to ScComms" << std::endl;
    }
    
    // Connect to ImageProcessing
    if(connectToAppl(hostName, 8000, &imageProc) == true) {
        std::cout << "CameraController: Connected to ImageProcessor" << std::endl;
    } else {
        std::cout << "CameraController: Failure to Connect to ImageProcessor" << std::endl;
    }
    
    return true;
}

void CameraController::handleTimeout() {
    this->open();
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

