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
    
    // Set pointers to services to NULL
    scComms = nullptr;
    cameraController = nullptr;
    
    // Initialize Pointing Destination
    point = PEM_NA;
    
    // Allocate Memory for Messages to Send
    processHealthMessage = new ProcessHealthAndStatusResponse();
    captureImageMessage = new CaptureImageRequest();
    solutionMessage = new SolutionMessage();
    pointRequest = new PointingRequest();
}

GNC::~GNC() {
    //Free Messages from Memory
    delete processHealthMessage;
    delete captureImageMessage;
    delete solutionMessage;
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
    // Check all connections are still open
    this->open();
    
    // Send Timed Capture Image Requests to Camera
    time_t currentTime = time(NULL);
    
    if (currentTime > pollTime) {
        // Send Poll
        if (scComms -> isConnected()) {
            if (point == PEM_NA) {
                point = PEM_Earth;
            } else if (point == PEM_Earth) {
                point = PEM_Moon;
            } else {
                point = PEM_Earth;
            }
            
            pointRequest->update(point);
            scComms -> sendMessage(pointRequest);
        }
        if (cameraController->isConnected()) {
            captureImageMessage->update(point);
            cameraController -> sendMessage(captureImageMessage);
        }
        pollTime = currentTime + 2*60;
    }
}

// *******************************
//
// Application Functionality:
//
// ********************************
// TODO: Seth will complete
bool GNC::hasAllDataNeededForCompute() {
    return false;
}


// TODO: Waiting On Cameron to Complete
void GNC::computeSolution() {
    
}


// *******************************
//
// Message Handlers: Supported by GNC
//
// ********************************

/*
 Send Status to WatchDog
 */
void GNC::handleProcessHealthAndStatusRequest(ProcessHealthAndStatusRequest* msg, ServiceInternal* service) {
    std::cout << "WatchDogService::handleProcessHealthAndStatusRequest(): Process Health and Status Response Received" << std::endl;
    
    // Update Status
    // TODO: Implement Status Update HERE
    
    // Update ProcessHealthAndStatusResponse Message
    processHealthMessage->update(status);
    
    // Send Status Message
    service->sendMessage(processHealthMessage);
    
    // Reset Status
    status.clear();
}

/*
 1. Store the Data Message
 2. Check to see if there is enough data to call compute
 3. Call Compute and register for Writing
 */
void GNC::handleDataMessage(DataMessage* msg, ServiceInternal* service) {
    std::cerr << "GNC::handleDataMessage() Data Message Recived" << std::endl;
    // TODO:
    // Store Ephemeris
    // Check to See if there is enough data to compute
    if (hasAllDataNeededForCompute() == true) {
        computeSolution();
        
        // Update Solution Message
        solutionMessage->update();
        
        scComms -> sendMessage(solutionMessage);
    }
}

/*
 1. Store Data
 2. Check to see if there is enough data to call compute
 if there is enough data to compute:
 3a. Call Compute
 4a. Send a Solution Message
 */
void GNC::handleProcessedImageMessage(ProcessedImageMessage* msg, ServiceInternal* service) {
    std::cerr << "GNC::handleProcessedImageMessage() Processed Image Message Recieved" << std::endl;
    if (hasAllDataNeededForCompute() == true) {
        computeSolution();
        
        // Update Solution Message
        solutionMessage->update();
        
        scComms -> sendMessage(solutionMessage);
    }
}


// *******************************
//
// Message Handlers: Not Supported by GNC
//
// ********************************
void GNC::handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service) {
    std::cerr << "GNC::handleOSPREStatus() Not Supported for GNC" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
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

