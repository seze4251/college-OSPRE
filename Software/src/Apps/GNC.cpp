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

GNC::GNC(std::string hostName, int watchDogPort) : watchDog(getSelector(), hostName, watchDogPort), pollTime(0) {
    std::cout<< "GNC Constructor called" << std::endl;
    setAppl(this);
    p_ID = P_GNC;
    watchDog.p_ID = p_ID;
}

GNC::~GNC() {
    
}

// Connect to Image Processor
// Connect to WatchDog
// Connect to ScComms

bool GNC::open() {
    if (watchDog.isConnected() == false) {
        watchDog.open();
    }
    
    if (watchDog.isConnected() == true) {
        return true;
    }else {
        return false;
    }
}


// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************


void GNC::handleTimeout() {
    
}

// *******************************
//
// Message Handler Defualt Behavior Below, Need to Implement
//
// ********************************

// Message Handlers
void GNC::handleProccessHealthAndStatusRequest(ProccessHealthAndStatusRequest* msg) {
    std::cout << "GNC::handleProccessHealthAndStatusRequest():  Not Supported for GNC" << std::endl;
    
}

void GNC::handleProccessHealthAndStatusResponse(ProccessHealthAndStatusResponse* msg) {
    std::cerr << "GNC::handleProccessHealthAndStatusResponse() Not Supported for GNC" << std::endl;
}

void GNC::handleCaptureImageRequest(CaptureImageRequest* msg) {
    std::cerr << "GNC::handleCaptureImageRequest() Not Supported for GNC" << std::endl;
}

void GNC::handleDataRequest(DataRequest* msg) {
    std::cerr << "GNC::handleDataRequest() Not Supported for GNC" << std::endl;
}
void GNC::handleEphemerisMessage(EphemerisMessage* msg) {
    std::cerr << "GNC::handleEphemerisMessage() Not Supported for GNC" << std::endl;
}
void GNC::handleImageAdjustment(ImageAdjustment* msg) {
    std::cerr << "GNC::handleImageAdjustment() Not Supported for GNC" << std::endl;
}
void GNC::handleImageMessage(ImageMessage* msg) {
    std::cerr << "GNC::handleImageMessage() Not Supported for GNC" << std::endl;
}
void GNC::handleOSPREStatus(OSPREStatus* msg) {
    std::cerr << "GNC::handleOSPREStatus() Not Supported for GNC" << std::endl;
}
void GNC::handlePointingRequest(PointingRequest* msg) {
    std::cerr << "GNC::handlePointingRequest() Not Supported for GNC" << std::endl;
}

void GNC::handleSolutionMessage(SolutionMessage* msg){
    std::cerr << "GNC::handleSolutionMessage() Not Supported for GNC" << std::endl;
}

