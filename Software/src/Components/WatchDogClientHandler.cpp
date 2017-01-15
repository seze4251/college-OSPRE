//
//  WatchDogClientHandler.cpp
//  WatchDogClientHandler
//
//  Created by Seth on 11/27/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>
#include <unistd.h>

#include "WatchDogClientHandler.h"
#include "ProcessID.h"

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
            closeConnection();
    }
    
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









