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

CameraController::CameraController(std::string hostName, int localPort, bool readImageFile) : ServerInternal(hostName, localPort, P_CameraController), pollTime(0), readImageFile(readImageFile) {
    std::cout<< "CameraController Constructor called" << std::endl;
    setAppl(this);
    
    // Set pointers to services to NULL
    imageProc = nullptr;
    scComms = nullptr;
    
    // Allocate size of image
    image = new char[1024*1024];
    
    // Allocate Memory for Messages to Send
    imageMessage = new ImageMessage();
    processHealthMessage = new ProcessHealthAndStatusResponse();
}

CameraController::~CameraController() {
    //Free Messages from Memory
    delete imageMessage;
    delete processHealthMessage;
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************


void CameraController::open() {
    //Open Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            std::cerr << "CameraController Server Socket Failed To Open, CameraController Exiting" << std::endl;
            exit(-1);
        }
        std::cout << "CameraController Server Socket Opened" << std::endl;
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
}

/*
 1. Need to check that all connections are still open
 2. Check to make sure that Camera is still connected
 */
void CameraController::handleTimeout() {
    this->open();
    
    // Check to make sure that Camera is still available <- ping camera
}

// *******************************
//
// Application Functionality:
//
// ********************************
//TODO: Needs Implementation
bool CameraController::canCaptureImage(CaptureImageRequest* msg) {
    std::cout << "CameraController::canCaptureImage(CaptureImageRequest* msg): Not Implemented yet" << std::endl;
    return false;
}

// TODO: Waiting on Dylan for Implementation
char* CameraController::captureImage() {
    std::cout << "CameraController::captureImage(): Not Implemented yet" << std::endl;
    char* image = nullptr;
    return image;
}

// TODO: Seth Implement
char* CameraController::readImage() {
    std::cout << "CameraController::readImage(): Not Implemented yet" << std::endl;
    char* image = nullptr;
    return image;
}

//TODO: Waiting on Dylan for how to implement, might not need
void CameraController::adjustCameraSettings(ImageAdjustment* msg) {
    std::cout << "CameraController::adjustCameraSettings(ImageAdjustment* msg): Not Implemented yet" << std::endl;
}




// *******************************
//
// Message Handlers: Supported By Camera Controller
//
// ********************************

/*
 Determine Process Status
 Send Status to WatchDog
 */
void CameraController::handleProcessHealthAndStatusRequest(ProcessHealthAndStatusRequest* msg, ServiceInternal* service) {
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
 CameraController::handleCaptureImageRequest() Logic
 Determine if Camera Controller can Take a picture
 If Can:
 Take A Picture / Load A Picture
 Send Image Message to Image Processor
 If Cannot:
 Send WatchDog Reason why Camera Controller Cannot Take Picture
 Optional: Send Message to GNC stating that data cannot be gathered at this time, I can do this but do I need to?
 */

void CameraController::handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service) {
    std::cerr << "CameraController::handleCaptureImageRequest() Capture Image Request Message Recived" << std::endl;
    
    // Decide if Camera Controller can Capture Image or if it can read an image
    if (canCaptureImage(msg) == true || readImageFile) {
        
        if (readImageFile == true) {
            image = readImage();
        } else {
            image = captureImage();
        }
        
        // Update Image Message
        imageMessage->update(image, msg->point);
        
        // Send Image Message to Image Processor
        imageProc->sendMessage(imageMessage);
        
    } else {
        // Update Process Status, potenially do this in canCaptureImage()
        //status.push_back()
    }
}

// TODO: Decide is this Needed?
void CameraController::handleImageAdjustment(ImageAdjustment* msg, ServiceInternal* service) {
    std::cerr << "ScCoCameraControllermms::handleImageAdjustment(): Recived Image Adjustment Message" << std::endl;
    adjustCameraSettings(msg);
}


// *******************************
//
// Message Handlers: Not Supported By Camera Controller
//
// ********************************
void CameraController::handleProcessHealthAndStatusResponse(ProcessHealthAndStatusResponse* msg, ServiceInternal* service) {
    std::cerr << "CameraController::handleProcessHealthAndStatusResponse() Not Supported for CameraController" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void CameraController::handleDataMessage(DataMessage* msg, ServiceInternal* service) {
    std::cerr << "CameraController::handleEphemerisMessage() Not Supported for CameraController" << std::endl;
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
void CameraController::handleProcessedImageMessage(ProcessedImageMessage* msg, ServiceInternal* service) {
    std::cerr << "CameraController::handleProcessedImageMessage() Not Supported for CameraController" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

