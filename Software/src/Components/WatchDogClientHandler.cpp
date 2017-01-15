//
//  WatchDogClientHandler.cpp
//  WatchDogClientHandler
//
//  Created by Seth on 11/27/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <WatchDogClientHandler.h>
#include <iostream>
#include <unistd.h> 

WatchDogClientHandler::WatchDogClientHandler(Selector &sel, int fd) : ServiceInternal(sel, fd) {
    std::cout << "WatchDogClientHandler Constructor " << std::endl;
    getSelector().registerService(fd, this);
    getSelector().interestInRead(fd);
    
}

WatchDogClientHandler::~WatchDogClientHandler() {
    
}

void WatchDogClientHandler::sendStatusRequestMessage() {
    if (isConnected() == false) {
        return;
    }
    
    // Create Message
    ProccessHealthAndStatusRequest* msg = new ProccessHealthAndStatusRequest();
    // Put Message in Write Buffer
    build.buildProccessHealthAndStatusRequest(*msg);
    // Register Intrest in Write
    getSelector().interestInWrite(fd);
}

void WatchDogClientHandler::closeConnection() {
    if (fd != -1) {
        getSelector().unregisterService(fd);
        ::close(fd);
        fd = -1;
    }
    readbuf.clear();
    writebuf.clear();
}

// Message Handlers
void WatchDogClientHandler::handleProccessHealthAndStatusResponse(ProccessHealthAndStatusResponse* msg) {
    std::cerr << "handleProccessHealthAndStatusResponse() Not Supported for WatchDogClientHandler" << std::endl;
}

// *******************************
//
// Message Handler Defualt Behavior Below
//
// ********************************

void WatchDogClientHandler::handleCaptureImageRequest(CaptureImageRequest* msg) {
    std::cerr << "handleCaptureImageRequest() Not Supported for WatchDogClientHandler" << std::endl;
}

void WatchDogClientHandler::handleDataRequest(DataRequest* msg) {
    std::cerr << "handleDataRequest() Not Supported for WatchDogClientHandler" << std::endl;
}
void WatchDogClientHandler::handleEphemerisMessage(EphemerisMessage* msg) {
    std::cerr << "handleEphemerisMessage() Not Supported for WatchDogClientHandler" << std::endl;
}
void WatchDogClientHandler::handleImageAdjustment(ImageAdjustment* msg) {
    std::cerr << "handleImageAdjustment() Not Supported for WatchDogClientHandler" << std::endl;
}
void WatchDogClientHandler::handleImageMessage(ImageMessage* msg) {
    std::cerr << "handleImageMessage() Not Supported for WatchDogClientHandler" << std::endl;
}
void WatchDogClientHandler::handleOSPREStatus(OSPREStatus* msg) {
    std::cerr << "handleOSPREStatus() Not Supported for WatchDogClientHandler" << std::endl;
}
void WatchDogClientHandler::handlePointingRequest(PointingRequest* msg) {
    std::cerr << "handlePointingRequest() Not Supported for WatchDogClientHandler" << std::endl;
}
void WatchDogClientHandler::handleProccessHealthAndStatusRequest(ProccessHealthAndStatusRequest* msg) {
    std::cerr << "handleProccessHealthAndStatusRequest() Not Supported for WatchDogClientHandler" << std::endl;
}

void WatchDogClientHandler::handleSolutionMessage(SolutionMessage* msg){
    std::cerr << "handleSolutionMessage() Not Supported for WatchDogClientHandler" << std::endl;
}









