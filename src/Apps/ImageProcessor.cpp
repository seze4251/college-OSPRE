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
#include <stdio.h>

#include "ImageProcessor.h"
#include "Service.h"

ImageProcessor::ImageProcessor(std::string hostName, int localPort) : ServerInternal(hostName, localPort, P_ImageProcessor), pollTime(0) {
    setAppl(this);
    gnc = nullptr;
    
    // Allocate Memory for Messages to Send
    processedImageMessage = new ProcessedImageMessage;
    processHealthMessage = new ProcessHealthAndStatusResponse();
    
    // Initialize localError to healthy
    localError = PE_AllHealthy;
    
    // Image Processing Specific Members
    sensitivity = 1.0;
    
    //TEMP TEMP TEMP
    test = false;
    logFile = nullptr;
}

ImageProcessor::~ImageProcessor() {
    //Free Messages from Memory
    delete processedImageMessage;
    delete processHealthMessage;
    
    // Close Log File
    if (logFile)
        fclose(logFile);
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************
void ImageProcessor::open() {
    // Create File Name
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    
    rawtime = time(0);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80,"./log/ImageProcessorLog_%d-%m-%Y.log",timeinfo);
    
    std::cout << "made it to 1" <<std::endl;
    
    // Open Log File
    logFile = fopen(buffer, "a+");
    
    std::cout << "made it to 1.5" <<std::endl;
    
    // Log Application Starting
    fprintf(logFile, "Image Processor Application Started, Time = %ld\n", time(0));
    std::cout << "made it to 1.75" <<std::endl;
    
    // Set Timeout to 1 minute
    setTimeoutTime(60, 0);
    
    std::cout << "made it to 2" <<std::endl;
    
    //Acceptor
    if (accept.isConnected() == false) {
        std::cout << "Am I in here?" << std::endl;
        if(accept.open(hostName, localPort) == false) {
            fprintf(logFile, "Error: Unable to Open Acceptor, Exiting...\n");
            exit(-1);
        }
    
        fprintf(logFile, "Connection: Server Socket Opened\n");
    }
    
    std::cout << "made it to 3" <<std::endl;
    //Connect to GNC
    if(connectToAppl(hostName, 9000, &gnc) == true) {
        fprintf(logFile, "Connection: Connected to GNC\n");
    } else {
        fprintf(logFile, "Error: Unable to Connect to GNC\n");
    }
}

/*
 1. Need to check that all connections are still open
 */
void ImageProcessor::handleTimeout() {
    //Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            fprintf(logFile, "Error: Unable to Open Acceptor, Exiting...\n");
            exit(-1);
        }
        fprintf(logFile, "Connection: Server Socket Opened\n");
    }
    
    //Connect to GNC
    if(connectToAppl(hostName, 9000, &gnc) == true) {
        fprintf(logFile, "Connection: Connected to GNC\n");
    } else {
        fprintf(logFile, "Error: Unable to Connect to GNC\n");
    }
}

FILE* ImageProcessor::getLogFileID() {
    return logFile;
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
    fprintf(logFile, "Received Message: ProcessHealthAndStatusRequest from WatchDog\n");
    
    processHealthMessage->update(localError);
    
    // Send Status Message
    service->sendMessage(processHealthMessage);
    fprintf(logFile, "Sent Message: StatusAndHealthResponse to WatchDog\n");
    
    // Reset Error Enum
    localError = PE_AllHealthy;
}

/*
 1. Check Message Integrity
 2. Process Image
 3. Send Processed Image Message to GNC
 4. Send Image Adjustment to Camera Controller
 */
void ImageProcessor::handleImageMessage(ImageMessage* msg, ServiceInternal* service) {
    fprintf(logFile, "Received Message: ImageMessage from CameraController\n");
    
    //TODO: Do Something Here
    // Process the Image
    if (test == true) {
        test = false;
    } else {
        test = true;
    }
    
    try {
    processImage(msg);
        if (test) {
        throw std::exception();
        }
    } catch(std::exception &exception) {
        fprintf(logFile, "Error: HandleImageMessage() Exception Caught: %s\n", exception.what());
        localError = PE_IP_noBodyInImage;
    } catch (...) {
        fprintf(logFile, "Error: HandleImageMessage() Unknown Type of Exception Caught\n");
        throw;
    }
    
    // Send Processed Image Message to GNC
    if (gnc != nullptr) {
        gnc->sendMessage(processedImageMessage);
        fprintf(logFile, "Sent Message: ProcessedImageMessage to GNC\n");
    }
}

// *******************************
//
// Message Handlers: Not Supported on Image Processor
//
// ********************************
void ImageProcessor::handleProcessHealthAndStatusResponse(ProcessHealthAndStatusResponse* msg, ServiceInternal* service) {
fprintf(logFile, "Error: Invalid Message Recived: Response, Closing Connection\n");
    service->closeConnection();
}
void ImageProcessor::handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service) {
fprintf(logFile, "Error: Invalid Message Recived: CaptureImageRequest, Closing Connection\n");
    service->closeConnection();
}

void ImageProcessor::handleDataMessage(DataMessage* msg, ServiceInternal* service) {
fprintf(logFile, "Error: Invalid Message Recived: DataMessage, Closing Connection\n");
    service->closeConnection();
}
void ImageProcessor::handleImageAdjustment(ImageAdjustment* msg, ServiceInternal* service) {
fprintf(logFile, "Error: Invalid Message Recived: ImageAdjustment, Closing Connection\n");
    service->closeConnection();
}
void ImageProcessor::handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service) {
fprintf(logFile, "Error: Invalid Message Recived: OSPREStatus, Closing Connection\n");
    service->closeConnection();
}
void ImageProcessor::handlePointingRequest(PointingRequest* msg, ServiceInternal* service) {
fprintf(logFile, "Error: Invalid Message Recived: PointingRequest, Closing Connection\n");
    service->closeConnection();
}
void ImageProcessor::handleSolutionMessage(SolutionMessage* msg, ServiceInternal* service){
fprintf(logFile, "Error: Invalid Message Recived: SolutionMessage, Closing Connection\n");
    service->closeConnection();
}
void ImageProcessor::handleProcessedImageMessage(ProcessedImageMessage* msg, ServiceInternal* service) {
fprintf(logFile, "Error: Invalid Message Recived: ProcessedImageMessage, Closing Connection\n");
    service->closeConnection();
}

