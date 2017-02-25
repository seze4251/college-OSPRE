//
//  CameraController.cpp
//  CameraController
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>
#include <stdio.h>

#include "CameraController.h"
#include "Service.h"


CameraController::CameraController(std::string hostName, int localPort, bool readImageFile) : ServerInternal(hostName, localPort, P_CameraController), pollTime(0), readImageFile(readImageFile) {
    setAppl(this);
    
    // Set pointers to services to NULL
    imageProc = nullptr;
    scComms = nullptr;
    
    // Allocate Memory for Messages to Send
    imageMessage = new ImageMessage();
    processHealthMessage = new ProcessHealthAndStatusResponse();
    
    // Initialize localError to healthy
    localError = PE_AllHealthy;
    logFile = nullptr;
}

CameraController::~CameraController() {
    //Free Messages from Memory
    delete imageMessage;
    delete processHealthMessage;
    
    // Close Log File
    if (logFile)
        fclose(logFile);
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************


void CameraController::open() {
    // Create File Name
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    
    rawtime = time(0);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80,"./log/CameraControllerLog_%d-%m-%Y.log",timeinfo);
    
    // Open Log File
    logFile = fopen(buffer, "a+");
    
    // Log Application Starting
    fprintf(logFile, "Camera Controller Application Started, Time = %ld\n", time(0));
    
    // Set Timeout to 1 minute
    setTimeoutTime(60, 0);
    
    //Open Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            fprintf(logFile, "Error: Unable to Open Acceptor, Exiting...\n");
            exit(-1);
        }
        fprintf(logFile, "Connection: Server Socket Opened\n");
    }
    
    //Connect to ScComms
    if(connectToAppl(hostName, 7000, &scComms) == true) {
        fprintf(logFile, "Connection: Connected to ScComms\n");
    } else {
        fprintf(logFile, "Error: Unable to Connect to ScComms\n");
    }
    
    // Connect to ImageProcessing
    if(connectToAppl(hostName, 8000, &imageProc) == true) {
        fprintf(logFile, "Connection: Connected to Image Processing\n");
    } else {
        fprintf(logFile, "Error: Unable to Connect to ImageProcessor\n");
    }
}

/*
 1. Need to check that all connections are still open
 2. Check to make sure that Camera is still connected
 */
void CameraController::handleTimeout() {
    //Open Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            fprintf(logFile, "Error: Unable to Open Acceptor, Exiting...\n");
            exit(-1);
        }
        fprintf(logFile, "Connection: Server Socket Opened\n");
    }
    
    //Connect to ScComms
    if (scComms == nullptr || scComms->isConnected() == false) {
        if(connectToAppl(hostName, 7000, &scComms) == true) {
            fprintf(logFile, "Connection: Connected to ScComms\n");
        } else {
            fprintf(logFile, "Error: Unable to Connect to ScComms\n");
        }
    }
    
    // Connect to ImageProcessing
    if (imageProc == nullptr || imageProc->isConnected() == false) {
        if(connectToAppl(hostName, 8000, &imageProc) == true) {
            fprintf(logFile, "Connection: Connected to Image Processing\n");
        } else {
            fprintf(logFile, "Error: Unable to Connect to ImageProcessing\n");
        }
    }
    
    // Check to make sure that Camera is still available <- ping camera
}

FILE* CameraController::getLogFileID() {
    return logFile;
}

// *******************************
//
// Application Functionality:
//
// ********************************
//TODO: Needs Implementation
bool CameraController::canCaptureImage(CaptureImageRequest* msg) {
    fprintf(logFile, "TODO: Need to Implement canCaptureImage()\n");
    return false;
}

// TODO: Waiting on Dylan for Implementation
void CameraController::captureImage() {
    fprintf(logFile, "TODO: Need to Implement captureImage\n");
}

// TODO: Seth Implement
void CameraController::readImage() {
    fprintf(logFile, "TODO: Need To Implement readImage\n");
}

//TODO: Waiting on Dylan for how to implement, might not need
void CameraController::adjustCameraSettings(ImageAdjustment* msg) {
    fprintf(logFile, "TODO: Need To Implement adjustCameraSettings\n");
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
    fprintf(logFile, "Received Message: ProcessHealthAndStatusRequest from WatchDog\n");
    
    // Update ProcessHealthAndStatusResponse Message
    processHealthMessage->update(localError);
    
    // Send Status Message
    service->sendMessage(processHealthMessage);
    fprintf(logFile, "Sent Message: StatusAndHealthResponse to WatchDog\n");
    
    // Reset Error Enum
    localError = PE_AllHealthy;
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
    fprintf(logFile, "Received Message: CaptureImageRequest from GNC\n");
    
    // Decide if Camera Controller can Capture Image or if it can read an image
    if (canCaptureImage(msg) == true || readImageFile) {
        
        if (readImageFile == true) {
            readImage();
        } else {
            captureImage();
        }
        
        // Update Image Message
        //********************************
        //TEMP TEMP Need to fix when Image Size is Known
        int cameraWidth = 100, cameraHeight = 80;
        double FOV = 70;
        imageMessage->update(msg->point, IMAGE_SIZE, cameraWidth, cameraHeight, FOV);
        //TEMP TEMP Need to fix when Image Size is Known
        //******************************
        
        // Send Image Message to Image Processor
        if (imageProc != nullptr) {
            imageProc->sendMessage(imageMessage);
            fprintf(logFile, "Sent Message: ImageMessage to ImageProcessor\n");
        }
        
    } else {
        // Update Process Status, potenially do this in canCaptureImage()
        //status.push_back()
    }
}

void CameraController::handleDataMessage(DataMessage* msg, ServiceInternal* service) {
    fprintf(logFile, "Received Message: DataMessage from ScComms\n");
}

// TODO: Decide is this Needed?
void CameraController::handleImageAdjustment(ImageAdjustment* msg, ServiceInternal* service) {
    fprintf(logFile, "Received Message: ImageAdjustmentMessage from ImageProcessing\n");
    adjustCameraSettings(msg);
}


// *******************************
//
// Message Handlers: Not Supported By Camera Controller
//
// ********************************
void CameraController::handleProcessHealthAndStatusResponse(ProcessHealthAndStatusResponse* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: ProcessHealthAndStatusResponse, Closing Connection\n");
    service->closeConnection();
}

void CameraController::handleImageMessage(ImageMessage* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: ImageMessage, Closing Connection\n");
    service->closeConnection();
}
void CameraController::handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: OSPREStatus, Closing Connection\n");
    service->closeConnection();
}
void CameraController::handlePointingRequest(PointingRequest* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: PointingRequest, Closing Connection\n");
    service->closeConnection();
}
void CameraController::handleSolutionMessage(SolutionMessage* msg, ServiceInternal* service){
    fprintf(logFile, "Error: Invalid Message Recived: SolutionMessage, Closing Connection\n");
    service->closeConnection();
}
void CameraController::handleProcessedImageMessage(ProcessedImageMessage* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: ProcessedImageMessage, Closing Connection\n");
    service->closeConnection();
}

