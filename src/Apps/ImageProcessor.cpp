//
//  ImageProcessor.cpp
//  ImageProcessor
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>
#include <unistd.h>
#include <exception>

#include "ImageProcessor.h"
#include "Service.h"

ImageProcessor::ImageProcessor(std::string hostName, int localPort) : ServerInternal(hostName, localPort, P_ImageProcessor), pollTime(0) {
    std::cout<< "ImageProcessor Constructor called" << std::endl;
    setAppl(this);
    gnc = nullptr;
    
    // Allocate Memory for Messages to Send
    processedImageMessage = new ProcessedImageMessage;
    processHealthMessage = new ProcessHealthAndStatusResponse();
    
    // Image Processing Specific Members
    sensitivity = 1.0;
}

ImageProcessor::~ImageProcessor() {
    //Free Messages from Memory
    delete processedImageMessage;
    delete processHealthMessage;
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************
void ImageProcessor::open() {
    // Set Timeout to 1 minute
    setTimeoutTime(60, 0);
    
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
    //    std::cout << "ImageProcessor: Connected to GNC" << std::endl;
    } else {
        std::cout << "ImageProcessor: Failure to Connect to GNC" << std::endl;
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
    
    //TODO: ANTHONY's Code HERE!!!!
    
    double alpha = 15.1, beta = 20.2, theta = 25.3, pixel_error = 1.3;
    sleep(10);
    // Update ProcessedImageMessage
    processedImageMessage->update(alpha, beta, theta, pixel_error, msg->point, msg->timeStamp);
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
    
    // Update Status
    // TODO: Implement Status Update HERE
    
    // Update ProcessHealthAndStatusResponse Message
    processHealthMessage->update(status);
    
    // Send Status Message
    service->sendMessage(processHealthMessage);
    
    // Reset Status
    status.clear();
}

/*
 1. Check Message Integrity
 2. Process Image
 3. Send Processed Image Message to GNC
 4. Send Image Adjustment to Camera Controller
 */
void ImageProcessor::handleImageMessage(ImageMessage* msg, ServiceInternal* service) {
    std::cerr << "\n\nImageProcessor::handleImageMessage() Image Message Recived\n\n" << std::endl;
    
    //TODO: Do Something Here
    // Process the Image
    
    try {
    processImage(msg);
        
    } catch(std::exception &exception) {
        std::cerr << "ScComms: Standard exception: " << exception.what() << '\n';
        // TODO: Do Somthing here to send watchdog the problem
    } catch (...) {
        std::cerr << "Unknown Exception thrown in ImageProcessor::processImage()" << std::endl;
        throw;
    }
    
    
    
    // Send Processed Image Message to GNC
    if (gnc != nullptr) {
        gnc->sendMessage(processedImageMessage);
    }
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

