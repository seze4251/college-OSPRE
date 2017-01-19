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

WatchDog::WatchDog(std::string hostName, int localPort) : ServerInternal(hostName, localPort, P_WatchDog) {
    std::cout<< " WatchDog Constructor called" << std::endl;
    setAppl(this);
}

WatchDog::~WatchDog() {
    
}

bool WatchDog::open() {
    if (accept.isConnected() == true) {
        return true;
    }
    
    if(accept.open(hostName, localPort) == false) {
        std::cerr << "Watch Dog Server Socket Failed To Open, WatchDog Exiting" << std::endl;
        exit(-1);
    }
        
    std::cout << "WatchDog Server Socket Opened" << std::endl;
    return true;
}

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
// Message Handler Defualt Behavior Below, Need to Implement Exceptions / Logs in unsupported messages
//
// ********************************
// Message Handlers

void WatchDog::handleProccessHealthAndStatusResponse(ProccessHealthAndStatusResponse* msg, ServiceInternal* service) {
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
            std::cerr << "WatchDogClientHandler::handleProccessHealthAndStatusResponse: Incorrect Process ID, WatchDog Not Monoriting Process ID: " << msg->p_ID << std::endl;
            std::cerr << "Closing Connection" << std::endl;
            service->closeConnection();
    }
}

void WatchDog::handleProccessHealthAndStatusRequest(ProccessHealthAndStatusRequest* msg, ServiceInternal* service) {
    std::cout << "WatchDog::handleProccessHealthAndStatusRequest():  Not Supported for WatchDog" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
    
}

void WatchDog::handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service) {
    std::cerr << "WatchDog::handleCaptureImageRequest() Not Supported for WatchDog" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void WatchDog::handleDataRequest(DataRequest* msg, ServiceInternal* service) {
    std::cerr << "WatchDog::handleDataRequest() Not Supported for WatchDog" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void WatchDog::handleEphemerisMessage(EphemerisMessage* msg, ServiceInternal* service) {
    std::cerr << "WatchDog::handleEphemerisMessage() Not Supported for WatchDog" << std::endl;
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





