//
//  ImageProcessor.h
//  ImageProcessor
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef IMAPGEPROCESSOR_H
#define IMAPGEPROCESSOR_H

#include <string>
#include <ctime>
#include <vector>
#include <stdio.h>

#include "PointEarthMoon.h"
#include "ServerInternal.h"
#include "ProcessID.h"
#include "OSPRE_Exceptions.h"

class ImageProcessor : public ServerInternal {
public:
    // Constructor
    ImageProcessor(std::string hostName, int localPort);
    
    // Destructor
    ~ImageProcessor();
    
    // Opens ImageProcessor Connections
    virtual void open();
    
    virtual void handleTimeout();
    
    // Applicaiton Functionality
    void setImageParameters(PointEarthMoon point, double* pix_deg, double* estimatedPosition, double* moonEphem);
    
    void processImage(ImageMessage* msg);
    
    // Message Handlers
    virtual void handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service);
    virtual void handleDataMessage(DataMessage* msg, ServiceInternal* service);
    virtual void handleImageAdjustment(ImageAdjustment* msg, ServiceInternal* service);
    virtual void handleImageMessage(ImageMessage* msg, ServiceInternal* service);
    virtual void handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service);
    virtual void handlePointingRequest(PointingRequest* msg, ServiceInternal* service);
    virtual void handleProcessHealthAndStatusRequest(ProcessHealthAndStatusRequest* msg, ServiceInternal* service);
    virtual void handleProcessHealthAndStatusResponse(ProcessHealthAndStatusResponse* msg, ServiceInternal* service);
    virtual void handleSolutionMessage(SolutionMessage* msg, ServiceInternal* service);
    virtual void handleProcessedImageMessage(ProcessedImageMessage* msg, ServiceInternal* service);
    
private:
    // Result File
    FILE* resultFile;
    
    time_t pollTime;
    ServiceInternal* gnc;
    
    // Pointer To Hold Messages that are being sent
    ProcessedImageMessage* processedImageMessage;
    ProcessHealthAndStatusResponse* processHealthMessage;
    
    ProcessError localError;
    
    
    // Application Specific Members
    // INPUTS: Set in funciton before Analyze Image Call
    double sensitivity;
    double dv3[2]; //Pixel Radius Guess from estimated Position
    
    // OUTPUTS:
    double numCirc; // Number of Circles (Output)
    double alpha; // Degrees, (Output)
    double beta; // Degrees, (Output)
    double theta; // Degrees, (Output)
    double centerPt_data[2]; // Calculated Center (Pixels)
    int centerPt_size[2]; // Don't Know (Unused)
    double radius; // Output Radius (Pixels)
    
    // TEMP TEMP
    double pixel_error;
    // TEMP TEMP
    
    void calcRadGuess(double* , double* , PointEarthMoon, double* );
    double calcSens(double* moonPxDiam, double* estimatedPosition, PointEarthMoon point);
};

#endif

// Connect to WatchDog

