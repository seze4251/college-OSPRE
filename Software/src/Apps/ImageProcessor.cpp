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

ImageProcessor::ImageProcessor(std::string hostName, int localPort, int watchDogPort) : ServerInternal(hostName, localPort, P_ImageProcessor), watchDogPort(watchDogPort) {
    std::cout<< "ImageProcessor Constructor called" << std::endl;
    setAppl(this);
}

ImageProcessor::~ImageProcessor() {
    
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************
bool ImageProcessor::open() {
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
    if (connectionCount < ServerInternal::MaxClients) {
        connections[connectionCount] = new ServiceInternal(getAppl()->getSelector());
        if (connections[connectionCount]->open(hostName, watchDogPort) == true) {
            // Register CallBack
            connections[connectionCount]->registerCallback(handleMessage);
            std::cout << "handleConnectionRequest() New Client Added" << std::endl;
            connectionCount++;
        } else {
            std::cout << "handleConnectionRequest() New Client Addition Failed" << std::endl;
        }
        
        return true;
    } else {
        std::cout << "handleConnectionRequest() New Client Addition Failed, too many clients" << std::endl;
        return false;
    }
}

void ImageProcessor::handleTimeout() {
    
}



// *******************************
//
// Message Handler Defualt Behavior Below, Need to Implement
//
// ********************************

// Message Handlers
void ImageProcessor::handleProccessHealthAndStatusRequest(ProccessHealthAndStatusRequest* msg, ServiceInternal* service) {
    std::cout << "WatchDogService::handleProccessHealthAndStatusRequest(): Process Health and Status Response Received" << std::endl;
    service->sendStatusResponseMessage();
}

void ImageProcessor::handleProccessHealthAndStatusResponse(ProccessHealthAndStatusResponse* msg, ServiceInternal* service) {
    std::cerr << "ImageProcessor::handleProccessHealthAndStatusResponse() Not Supported for ImageProcessor" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void ImageProcessor::handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service) {
    std::cerr << "ImageProcessor::handleCaptureImageRequest() Not Supported for ImageProcessor" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void ImageProcessor::handleDataRequest(DataRequest* msg, ServiceInternal* service) {
    std::cerr << "ImageProcessor::handleDataRequest() Not Supported for ImageProcessor" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void ImageProcessor::handleEphemerisMessage(EphemerisMessage* msg, ServiceInternal* service) {
    std::cerr << "ImageProcessor::handleEphemerisMessage() Not Supported for ImageProcessor" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void ImageProcessor::handleImageAdjustment(ImageAdjustment* msg, ServiceInternal* service) {
    std::cerr << "ImageProcessor::handleImageAdjustment() Not Supported for ImageProcessor" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void ImageProcessor::handleImageMessage(ImageMessage* msg, ServiceInternal* service) {
    std::cerr << "ImageProcessor::handleImageMessage() Not Supported for ImageProcessor" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void ImageProcessor::handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service) {
    std::cerr << "ImageProcessor::handleOSPREStatus() Not Supported for ImageProcessor" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void ImageProcessor::handlePointingRequest(PointingRequest* msg, ServiceInternal* service) {
    std::cerr << "ImageProcessor::handlePointingRequest() Not Supported for ImageProcessor" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void ImageProcessor::handleSolutionMessage(SolutionMessage* msg, ServiceInternal* service){
    std::cerr << "ImageProcessor::handleSolutionMessage() Not Supported for ImageProcessor" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

