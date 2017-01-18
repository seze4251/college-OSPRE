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

int WatchDog::clientCount;
WatchDogClientHandler* WatchDog::client[WatchDog::MaxClients];

WatchDog::WatchDog(std::string hostName, int localPort) : pollTime(0), hostName(hostName), localPort(localPort) {
    setAppl(this);
    std::cout<< " WatchDog Constructor called" << std::endl;
    accept.registerCallback(WatchDog::handleWatchDogConnections);
    clientCount = 0;
    for (int i = 0; i < MaxClients; i++) {
        client[i] = nullptr;
    }
    p_ID = P_WatchDog;
}

WatchDog::~WatchDog() {
    
}

// Connect to no processes
// Accept ScComms, ImageProcessor, GNC, CameraController
bool WatchDog::open(){
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

void WatchDog::handleWatchDogConnections(int fd) {
    // Check to make sure max client count is not exceeded
    if (clientCount >= MaxClients) {
        std::cout << "handleWatchDogConnections closing Connection: Too Many Connections" << std::endl;
        ::close(fd);
        return;
    }
    
    client[clientCount] = new WatchDogClientHandler(appl->getSelector(), fd);
    clientCount++;
}

void WatchDog::handleTimeout() {
    time_t currentTime = time(NULL);
    
    if (currentTime > pollTime) {
        // Send Poll
        for (int i = 0; i < MaxClients; i++) {
            if ( (client[i] != nullptr) && (client[i]->isConnected() == true)) {
                std::cout << "Attempting to send status request to client " << i << std::endl;
                client[i]->sendStatusRequestMessage();
            }
            
        }
        pollTime = currentTime + 5;
    }
}


// *******************************
//
// Message Handler Defualt Behavior Below, Need to Implement
//
// ********************************
// Message Handlers
void WatchDog::handleProccessHealthAndStatusRequest(ProccessHealthAndStatusRequest* msg) {
    std::cout << "WatchDog::handleProccessHealthAndStatusRequest():  Not Supported for WatchDog" << std::endl;
    
}

void WatchDog::handleProccessHealthAndStatusResponse(ProccessHealthAndStatusResponse* msg) {
    std::cerr << "WatchDog::handleProccessHealthAndStatusResponse() Not Supported for WatchDog" << std::endl;
}

void WatchDog::handleCaptureImageRequest(CaptureImageRequest* msg) {
    std::cerr << "WatchDog::handleCaptureImageRequest() Not Supported for WatchDog" << std::endl;
}

void WatchDog::handleDataRequest(DataRequest* msg) {
    std::cerr << "WatchDog::handleDataRequest() Not Supported for WatchDog" << std::endl;
}
void WatchDog::handleEphemerisMessage(EphemerisMessage* msg) {
    std::cerr << "WatchDog::handleEphemerisMessage() Not Supported for WatchDog" << std::endl;
}
void WatchDog::handleImageAdjustment(ImageAdjustment* msg) {
    std::cerr << "WatchDog::handleImageAdjustment() Not Supported for WatchDog" << std::endl;
}
void WatchDog::handleImageMessage(ImageMessage* msg) {
    std::cerr << "WatchDog::handleImageMessage() Not Supported for WatchDog" << std::endl;
}
void WatchDog::handleOSPREStatus(OSPREStatus* msg) {
    std::cerr << "WatchDog::handleOSPREStatus() Not Supported for WatchDog" << std::endl;
}
void WatchDog::handlePointingRequest(PointingRequest* msg) {
    std::cerr << "WatchDog::handlePointingRequest() Not Supported for WatchDog" << std::endl;
}

void WatchDog::handleSolutionMessage(SolutionMessage* msg){
    std::cerr << "WatchDog::handleSolutionMessage() Not Supported for WatchDog" << std::endl;
}





