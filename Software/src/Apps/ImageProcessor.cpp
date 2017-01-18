//
//  ImageProcessor.cpp
//  ImageProcessor
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>

#include "ImageProcessor.h"
#include "Service.h"

ImageProcessor::ImageProcessor(std::string hostName, int localPort, int watchDogPort) : watchDog(getSelector(), hostName, watchDogPort), pollTime(0), hostName(hostName), localPort(localPort) {
    std::cout<< "ImageProcessor Constructor called" << std::endl;
    setAppl(this);
    accept.registerCallback(ImageProcessor::handleImageProcessorConnections);
    p_ID = P_ImageProcessor;
    watchDog.p_ID = p_ID;
}

ImageProcessor::~ImageProcessor() {
    
}

bool ImageProcessor::open() {
    //WatchDog Service
    if (watchDog.isConnected() == false) {
        watchDog.open();
    }
    
    //Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            std::cerr << "ImageProcessor Server Socket Failed To Open, ImageProcessor Exiting" << std::endl;
            exit(-1);
        }
        std::cout << "ImageProcessor Server Socket Opened" << std::endl;
    }
    
    // Other Services
    // TODO: Change Bool to something more useful
    return true;
}


// Connect to Camera Controller
// Connect to WatchDog

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************


void ImageProcessor::handleTimeout() {
    
}

void ImageProcessor::handleImageProcessorConnections(int fd) {
    
}

// *******************************
//
// Message Handler Defualt Behavior Below, Need to Implement
//
// ********************************

// Message Handlers
void ImageProcessor::handleProccessHealthAndStatusRequest(ProccessHealthAndStatusRequest* msg) {
    std::cout << "ImageProcessor::handleProccessHealthAndStatusRequest():  Not Supported for ImageProcessor" << std::endl;
    
}

void ImageProcessor::handleProccessHealthAndStatusResponse(ProccessHealthAndStatusResponse* msg) {
    std::cerr << "ImageProcessor::handleProccessHealthAndStatusResponse() Not Supported for ImageProcessor" << std::endl;
}

void ImageProcessor::handleCaptureImageRequest(CaptureImageRequest* msg) {
    std::cerr << "ImageProcessor::handleCaptureImageRequest() Not Supported for ImageProcessor" << std::endl;
}

void ImageProcessor::handleDataRequest(DataRequest* msg) {
    std::cerr << "ImageProcessor::handleDataRequest() Not Supported for ImageProcessor" << std::endl;
}
void ImageProcessor::handleEphemerisMessage(EphemerisMessage* msg) {
    std::cerr << "ImageProcessor::handleEphemerisMessage() Not Supported for ImageProcessor" << std::endl;
}
void ImageProcessor::handleImageAdjustment(ImageAdjustment* msg) {
    std::cerr << "ImageProcessor::handleImageAdjustment() Not Supported for ImageProcessor" << std::endl;
}
void ImageProcessor::handleImageMessage(ImageMessage* msg) {
    std::cerr << "ImageProcessor::handleImageMessage() Not Supported for ImageProcessor" << std::endl;
}
void ImageProcessor::handleOSPREStatus(OSPREStatus* msg) {
    std::cerr << "ImageProcessor::handleOSPREStatus() Not Supported for ImageProcessor" << std::endl;
}
void ImageProcessor::handlePointingRequest(PointingRequest* msg) {
    std::cerr << "ImageProcessor::handlePointingRequest() Not Supported for ImageProcessor" << std::endl;
}

void ImageProcessor::handleSolutionMessage(SolutionMessage* msg){
    std::cerr << "ImageProcessor::handleSolutionMessage() Not Supported for ImageProcessor" << std::endl;
}

