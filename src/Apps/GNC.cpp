//
//  GNC.cpp
//  GNC
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>
#include <exception>

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
    
    // Initialize localError to healthy
    localError = PE_AllHealthy;
    
    // Application Specific Member Initializations
    readReferenceTrajectory();
    covariance = new double[36];
    trajectoryDev = new double[6];
    
}

GNC::~GNC() {
    //Free Messages from Memory
    delete processHealthMessage;
    delete captureImageMessage;
    delete solutionMessage;
    delete pointRequest;
    delete covariance;
    delete trajectoryDev;
}

void GNC::open() {
    // Set Timeout to 1 minute
    setTimeoutTime(10, 0);
    
    //Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            std::cerr << "GNC Server Socket Failed To Open, GNC Exiting" << std::endl;
            exit(-1);
        }
        std::cout << "GNC Server Socket Opened" << std::endl;
    }
    
    //Connect to ScComms
    if(connectToAppl(hostName, 7000, &scComms) == true) {
        //    std::cout << "GNC: Connected to ScComms" << std::endl;
    } else {
        std::cout << "GNC: Failure to Connect to ScComms" << std::endl;
    }
    
    // Connect to Camera Controller
    if(connectToAppl(hostName, 10000, &cameraController) == true) {
        //   std::cout << "GNC: Connected to Camera Controller" << std::endl;
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
            std::cout << "\nSending Pointing Request\n" << std::endl;
            
            pointRequest->update(point);
            scComms -> sendMessage(pointRequest);
        }
        
        if ((cameraController != nullptr) && (cameraController->isConnected())) {
            captureImageMessage->update(point, latestPosition);
            
            std::cout << "\nSending Capture Image Message\n" << std::endl;
            cameraController -> sendMessage(captureImageMessage);
        }
        
        pollTime = currentTime + 20;
    }
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
    std::cout << "Read In Reference Trajectory Here, Need to implement" << std::endl;
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
    
    // Update ProcessHealthAndStatusResponse Message
    processHealthMessage->update(localError);
    
    // Send Status Message
    service->sendMessage(processHealthMessage);
    
    // Reset Error Enum
    localError = PE_AllHealthy;
}

/*
 1. Store the Data Message in circular buffer
 */
void GNC::handleDataMessage(DataMessage* msg, ServiceInternal* service) {
    std::cerr << "\n\nGNC::handleDataMessage() Data Message Recived\n\n" << std::endl;
    
    // Print Message
    //  msg->print();
    
    // Put Data Into Circular Buffer
    circBuf.put(msg);
}

/*
 1. Get Spacecraft Data Message
 2. Call Compute
 3. Send a Solution Message
 */
void GNC::handleProcessedImageMessage(ProcessedImageMessage* msg, ServiceInternal* service) {
    std::cerr << "\n\nGNC::handleProcessedImageMessage() Processed Image Message Recieved\n\n" << std::endl;
    
    // Print Message
    //  msg->print();
    
    DataMessage* scData = circBuf.get(msg->timeStamp);
    
    // Should this move into computeSolution or get rid of completly?
    if (scData == nullptr) {
        std::cout << "Data Message == nullptr, circular buffer broken, or Data Message not found!" << std::endl;
        //TODO: Throw exception here
        return;
    }
    
    // Compute Solution and Update Solution Message
    try {
        computeSolution(scData, msg);
        
    } catch(std::exception &exception) {
        std::cerr << "ScComms: Standard exception: " << exception.what() << '\n';
        // TODO: Do Somthing here to send watchdog the problem
        localError = PE_NotHealthy;
        
    } catch (...) {
        std::cerr << "Unknown Exception thrown in GNC::computeSolution()" << std::endl;
        throw;
    }
    
    // Send Solution Message
    if (scComms != nullptr) {
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

