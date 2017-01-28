//
//  WatchDog.cpp
//  WatchDog
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>
#include <unistd.h>

#include "WatchDog.h"

WatchDog::WatchDog(std::string hostName, int localPort) : ServerInternal(hostName, localPort, P_WatchDog), pollTime(0) {
    std::cout<< " WatchDog Constructor called" << std::endl;
    setAppl(this);
    scComms = nullptr;
    gnc = nullptr;
    imageProc = nullptr;
    cameraControl = nullptr;
}

WatchDog::~WatchDog() {
    
}

void WatchDog::open() {
    //Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            std::cerr << "WatchDog Server Socket Failed To Open, ScComms Exiting" << std::endl;
            exit(-1);
        }
        std::cout << "WatchDog Server Socket Opened" << std::endl;
    }
    
    // Connect to ScComms
    if(connectToAppl(hostName, 7000, &scComms) == true) {
        std::cout << "ScComms: Connected to ScComms" << std::endl;
    } else {
        std::cout << "ScComms: Failure to Connect to ScComms" << std::endl;
    }
    
    // Connect to GNC
    if(connectToAppl(hostName, 9000, &gnc) == true) {
        std::cout << "ScComms: Connected to GNC" << std::endl;
    } else {
        std::cout << "ScComms: Failure to Connect to GNC" << std::endl;
    }
    
    // Connect to Image Processor
    if(connectToAppl(hostName, 8000, &imageProc) == true) {
        std::cout << "ScComms: Connected to Image Processor" << std::endl;
    } else {
        std::cout << "ScComms: Failure to Connect to Image Processor" << std::endl;
    }
    
    // Connect to Camera Controller
    if(connectToAppl(hostName, 10000, &cameraControl) == true) {
        std::cout << "ScComms: Connected to Camera Controller" << std::endl;
    } else {
        std::cout << "ScComms: Failure to Connect to Camera Controller" << std::endl;
    }
}

/*
 1. Need to send out a poll at timed intervals
 2. Need to check that all processes have responded to the poll
 3. Need to send OSPRE Status Message to ScComms at timed intervals
 4. Need to check that all connections are still open
*/
void WatchDog::handleTimeout() {
    time_t currentTime = time(NULL);
    
    if (currentTime > pollTime) {
        // Send Poll
        for (int i = 0; i < MaxClients; i++) {
            if ( (connections[i] != nullptr) && (connections[i]->isConnected() == true)) {
                std::cout << "Attempting to send status request to client " << i << std::endl;
                connections[i]->sendStatusRequestMessage();
            }
            
        }
        pollTime = currentTime + 5;
    }
}

// *******************************
//
// Message Handlers: Supported By WatchDog
//
// ********************************

/*
 When a response message is recived, diagnose if there are any issues with the processess and store them for the creation of the OSPRE status message
 */
void WatchDog::handleProcessHealthAndStatusResponse(ProcessHealthAndStatusResponse* msg, ServiceInternal* service) {
    //Determine which client sent the message and print that message has been recived
    switch (msg->p_ID) {
        case P_CameraController:
            std::cout << "WatchDog: Health and Status Response Recived from Camera Controller" << std::endl;
            break;
            
        case P_ScComms:
            std::cout << "WatchDog: Health and Status Response Recived from ScComms" << std::endl;
            break;
            
        case P_GNC:
            std::cout << "WatchDog: Health and Status Response Recived from GNC" << std::endl;
            break;
            
        case P_ImageProcessor:
            std::cout << "WatchDog: Health and Status Response Recived from ImageProcessor" << std::endl;
            break;
            
        default:
            std::cerr << "WatchDogClientHandler::handleProcessHealthAndStatusResponse: Incorrect Process ID, WatchDog Not Monoriting Process ID: " << msg->p_ID << std::endl;
            std::cerr << "Closing Connection" << std::endl;
            service->closeConnection();
    }
}

// *******************************
//
// Message Handlers: Not Supported By WatchDog
//
// ********************************
void WatchDog::handleProcessHealthAndStatusRequest(ProcessHealthAndStatusRequest* msg, ServiceInternal* service) {
    std::cout << "WatchDog::handleProcessHealthAndStatusRequest():  Not Supported for WatchDog" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
    
}
void WatchDog::handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service) {
    std::cerr << "WatchDog::handleCaptureImageRequest() Not Supported for WatchDog" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void WatchDog::handleDataMessage(DataMessage* msg, ServiceInternal* service) {
    std::cerr << "WatchDog::handleDataMessage() Not Supported for WatchDog" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void WatchDog::handleImageAdjustment(ImageAdjustment* msg, ServiceInternal* service) {
    std::cerr << "WatchDog::handleImageAdjustment() Not Supported for WatchDog" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void WatchDog::handleImageMessage(ImageMessage* msg, ServiceInternal* service) {
    std::cerr << "WatchDog::handleImageMessage() Not Supported for WatchDog" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void WatchDog::handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service) {
    std::cerr << "WatchDog::handleOSPREStatus() Not Supported for WatchDog" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void WatchDog::handlePointingRequest(PointingRequest* msg, ServiceInternal* service) {
    std::cerr << "WatchDog::handlePointingRequest() Not Supported for WatchDog" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void WatchDog::handleSolutionMessage(SolutionMessage* msg, ServiceInternal* service){
    std::cerr << "WatchDog::handleSolutionMessage() Not Supported for WatchDog" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void WatchDog::handleProcessedImageMessage(ProcessedImageMessage* msg, ServiceInternal* service) {
    std::cerr << "WatchDog::handleProcessedImageMessage() Not Supported for WatchDog" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}




