//
//  GNC.cpp
//  GNC
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>
#include <exception>
#include <stdio.h>

#include "GNC.h"
#include "Service.h"

GNC::GNC(std::string hostName, int localPort) : ServerInternal(hostName, localPort, P_GNC), pollTime(0) {
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
    
    // Initialize localError to healthy
    localError = PE_AllHealthy;
    
    // Application Specific Member Initializations
    readReferenceTrajectory();
    covariance = new double[36];
    trajectoryDev = new double[6];
    
    logFile = nullptr;
}

GNC::~GNC() {
    //Free Messages from Memory
    delete processHealthMessage;
    delete captureImageMessage;
    delete solutionMessage;
    delete pointRequest;
    delete[] covariance;
    delete[] trajectoryDev;
    
    // Close Log File
    if (logFile)
        fclose(logFile);
}

void GNC::open() {
    // Create File Name
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    
    rawtime = time(0);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80, "./log/GNCLog_%d-%m-%Y.log",timeinfo);
    
    // Open Log File
    logFile = fopen(buffer, "a+");
    
    // Log Application Starting
    fprintf(logFile, "GNC Application Started, Time = %ld\n", time(0));
    
    // Set Timeout to 1 minute
    setTimeoutTime(10, 0);
    
    //Acceptor
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
    
    // Connect to Camera Controller
    if(connectToAppl(hostName, 10000, &cameraController) == true) {
        fprintf(logFile, "Connection: Connected to Camera Controller\n");
    } else {
        fprintf(logFile, "Error: Unable to Connect to CameraController\n");
    }
}

/*
 1. Need to check that all connections are still open
 2. Need to Send Timed Pointing Requests to the Spacecraft
 3. Need to Send Timed Capture Image Requests to the Camera
 */
void GNC::handleTimeout() {
    // Check all connections are still open
    //Acceptor
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
    
    // Connect to Camera Controller
    
    if (cameraController == nullptr || cameraController->isConnected() == false) {
        if(connectToAppl(hostName, 10000, &cameraController) == true) {
            fprintf(logFile, "Connection: Connected to CameraController\n");
        } else {
            fprintf(logFile, "Error: Unable to Connect to CameraController\n");
        }
    }
    
    
    // Send Timed Capture Image Requests to Camera
    time_t currentTime = time(NULL);
    
    // Send Poll
    if (currentTime > pollTime) {
        if (point == PEM_NA) {
            point = PEM_Earth;
        } else if (point == PEM_Earth) {
            point = PEM_Moon;
        } else {
            point = PEM_Earth;
        }
        
        if ((scComms != nullptr) && (scComms -> isConnected())) {
            pointRequest->update(point);
            scComms -> sendMessage(pointRequest);
            fprintf(logFile, "Sent Message: Pointing Request to ScComms\n");
        }
        
        if ((cameraController != nullptr) && (cameraController->isConnected())) {
            captureImageMessage->update(point, latestPosition);
            cameraController -> sendMessage(captureImageMessage);
            fprintf(logFile, "Sent Message: CaptureImageMessage to CameraController\n");
        }
        
        pollTime = currentTime + 20;
    }
    flushLog();
}

// *******************************
//
// Application Functionality:
//
// ********************************

// TODO: Waiting On Cameron to Complete
void GNC::computeSolution(DataMessage* dataMessage, ProcessedImageMessage* procMessage) {
    // Check Inputs <- unecessary if Cameron does it
    
    // Call Camerons Code Here
    // Compute Solution
    // YAY HAVE SOLUTION!!!
    
    // TEMPORARY FIX:
    // LETS CODE COMPILE
    double position[3] {1, 2, 3};
    double positionError[3] {4, 5, 6};
    double velocity[3] {7, 8, 9};
    double velocityError[3] {10, 11, 12};
    double earthScMoonAngle {180};
    
    // Update Solution Message
    solutionMessage->update(position, positionError, velocity, velocityError, earthScMoonAngle);
}

void GNC::readReferenceTrajectory() {
    std::cout << "Need To Implement: readReferenceTrajectory" << std::endl;
    //fprintf(logFile, "Need To Implement: readReferenceTrajectory\n");
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
 1. Store the Data Message in circular buffer
 */
void GNC::handleDataMessage(DataMessage* msg, ServiceInternal* service) {
    fprintf(logFile, "Received Message: DataMessage from ScComms\n");
    
    // Put Data Into Circular Buffer
    circBuf.put(msg);
}

/*
 1. Get Spacecraft Data Message
 2. Call Compute
 3. Send a Solution Message
 */
void GNC::handleProcessedImageMessage(ProcessedImageMessage* msg, ServiceInternal* service) {
    fprintf(logFile, "Received Message: ProcessedImageMessage from ScComms\n");
    
    DataMessage* scData;
    try {
        scData = circBuf.get(msg->timeStamp);
    } catch (const char* exception) {
        fprintf(logFile, "Error: Data Message Not Received, Exception: %s\n", exception);
    }
    
    // Compute Solution and Update Solution Message
    try {
        computeSolution(scData, msg);
        throw std::exception();
        
    } catch(std::exception &exception) {
        fprintf(logFile, "Error: HandleProcessedImageMessage() Exception Caught: %s\n", exception.what());
        localError = PE_invalidData;
        
    } catch (...) {
        fprintf(logFile, "Error: HandleProcessedImageMessage() Unknown Type of Exception Caught\n");
        throw;
    }
    
    // Send Solution Message
    if (scComms != nullptr) {
        scComms -> sendMessage(solutionMessage);
        fprintf(logFile, "Sent Message: SolutionMessage to ScComms\n");
    }
}


// *******************************
//
// Message Handlers: Not Supported by GNC
//
// ********************************
void GNC::handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: OSPRE Status, Closing Connection\n");
    service->closeConnection();
}
void GNC::handleProcessHealthAndStatusResponse(ProcessHealthAndStatusResponse* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: ResponseMessage, Closing Connection\n");
    service->closeConnection();
}
void GNC::handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: CaptureImageRequest, Closing Connection\n");
    service->closeConnection();
}
void GNC::handleImageAdjustment(ImageAdjustment* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: ImageAdjustmentMessage, Closing Connection\n");
    service->closeConnection();
}
void GNC::handleImageMessage(ImageMessage* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: ImageMessage, Closing Connection\n");
    service->closeConnection();
}
void GNC::handlePointingRequest(PointingRequest* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: PointingRequest, Closing Connection\n");
    service->closeConnection();
}
void GNC::handleSolutionMessage(SolutionMessage* msg, ServiceInternal* service){
    fprintf(logFile, "Error: Invalid Message Recived: SolutionMessage, Closing Connection\n");
    service->closeConnection();
}

