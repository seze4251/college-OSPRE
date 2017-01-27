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

GNC::GNC(std::string hostName, int localPort) : ServerInternal(hostName, localPort, P_GNC), pollTime(0) {
    std::cout<< "GNC Constructor called" << std::endl;
    setAppl(this);
    scComms = nullptr;
    cameraController = nullptr;
}

GNC::~GNC() {
    
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************

void GNC::open() {
    //Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            std::cerr << "CameraController Server Socket Failed To Open, CameraController Exiting" << std::endl;
            exit(-1);
        }
        std::cout << "CameraController Server Socket Opened" << std::endl;
    }
    
    //Connect to ScComms
    if(connectToAppl(hostName, 7000, &scComms) == true) {
        std::cout << "GNC: Connected to ScComms" << std::endl;
    } else {
        std::cout << "GNC: Failure to Connect to ScComms" << std::endl;
    }
    
    // Connect to Camera Controller
    if(connectToAppl(hostName, 10000, &cameraController) == true) {
        std::cout << "GNC: Connected to Camera Controller" << std::endl;
    } else {
        std::cout << "GNC: Failure to Connect to Camera Controller" << std::endl;
    }
}

/*
 1. Need to check that all connections are still open
 2. Need to Send Timed Pointing Requests to the Spacecraft
 3. Need to Send Timed Capture Image Requests to the Camera
 */
void GNC::handleTimeout() {
    this->open();
}

// *******************************
//
// Message Handlers: Supported by GNC
//
// ********************************

/*
 Determine Process Status
 Send Status to WatchDog
 */
void GNC::handleProcessHealthAndStatusRequest(ProcessHealthAndStatusRequest* msg, ServiceInternal* service) {
    std::cout << "WatchDogService::handleProcessHealthAndStatusRequest(): Process Health and Status Response Received" << std::endl;
    service->sendStatusResponseMessage(p_ID);
}

void GNC::handleEphemerisMessage(EphemerisMessage* msg, ServiceInternal* service) {
    std::cerr << "GNC::handleEphemerisMessage() Not Supported for GNC" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void GNC::handleProcessedImageMessage(ProcessedImageMessage* msg, ServiceInternal* service) {
    std::cerr << "GNC::handleProcessedImageMessage() Not Supported for GNC" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void GNC::handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service) {
    std::cerr << "GNC::handleOSPREStatus() Not Supported for GNC" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}


// *******************************
//
// Message Handlers: Not Supported by GNC
//
// ********************************
void GNC::handleProcessHealthAndStatusResponse(ProcessHealthAndStatusResponse* msg, ServiceInternal* service) {
    std::cerr << "GNC::handleProcessHealthAndStatusResponse() Not Supported for GNC" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void GNC::handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service) {
    std::cerr << "GNC::handleCaptureImageRequest() Not Supported for GNC" << std::endl;
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

