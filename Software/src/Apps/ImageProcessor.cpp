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

ImageProcessor::ImageProcessor(std::string hostName, int localPort) : ServerInternal(hostName, localPort, P_ImageProcessor), pollTime(0) {
    std::cout<< "ImageProcessor Constructor called" << std::endl;
    setAppl(this);
    gnc = nullptr;
}

ImageProcessor::~ImageProcessor() {
    
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************
void ImageProcessor::open() {
    //Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            std::cerr << "ImageProcessor Server Socket Failed To Open, ImageProcessor Exiting" << std::endl;
            exit(-1);
        }
        std::cout << "ImageProcessor Server Socket Opened" << std::endl;
    }
    
    //Connect to GNC
    if(connectToAppl(hostName, 9000, &gnc) == true) {
        std::cout << "ImageProcessor: Connected to WatchDog" << std::endl;
    } else {
        std::cout << "ImageProcessor: Failure to Connect to WatchDog" << std::endl;
    }
}

/*
 1. Need to check that all connections are still open
 */
void ImageProcessor::handleTimeout() {
    this->open();
}

// *******************************
//
// Application Functionality:
//
// ********************************
// TODO: Anthony to complete
void ImageProcessor::processImage(ImageMessage* msg) {
    
}


// *******************************
//
// Message Handlers: Supported by Image Processor
//
// ********************************

/*
 Determine Process Status
 Send Status to WatchDog
 */
void ImageProcessor::handleProcessHealthAndStatusRequest(ProcessHealthAndStatusRequest* msg, ServiceInternal* service) {
    std::cout << "WatchDogService::handleProcessHealthAndStatusRequest(): Process Health and Status Response Received" << std::endl;
    service->sendStatusResponseMessage(status);
    // Clear Status
    status.clear();
}

/*
 1. Check Message Integrity
 2. Process Image
 3. Send Processed Image Message to GNC
 4. Send Image Adjustment to Camera Controller
*/
void ImageProcessor::handleImageMessage(ImageMessage* msg, ServiceInternal* service) {
    std::cerr << "ImageProcessor::handleImageMessage() Image Message Recived" << std::endl;
    //Check Message Integrity
    
    processImage(msg);
}

// *******************************
//
// Message Handlers: Not Supported on Image Processor
//
// ********************************
void ImageProcessor::handleProcessHealthAndStatusResponse(ProcessHealthAndStatusResponse* msg, ServiceInternal* service) {
    std::cerr << "ImageProcessor::handleProcessHealthAndStatusResponse() Not Supported for ImageProcessor" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void ImageProcessor::handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service) {
    std::cerr << "ImageProcessor::handleCaptureImageRequest() Not Supported for ImageProcessor" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void ImageProcessor::handleDataMessage(DataMessage* msg, ServiceInternal* service) {
    std::cerr << "ImageProcessor::handleDataMessage() Not Supported for ImageProcessor" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void ImageProcessor::handleImageAdjustment(ImageAdjustment* msg, ServiceInternal* service) {
    std::cerr << "ImageProcessor::handleImageAdjustment() Not Supported for ImageProcessor" << std::endl;
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
void ImageProcessor::handleProcessedImageMessage(ProcessedImageMessage* msg, ServiceInternal* service) {
    std::cerr << "ImageProcessor::handleProcessedImageMessage() Not Supported for ImageProcessor" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

