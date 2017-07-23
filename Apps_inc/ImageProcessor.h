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
    
    ServiceInternal* gnc;
    
    // Pointer To Hold Messages that are being sent
    ProcessedImageMessage* processedImageMessage;
    ProcessHealthAndStatusResponse* processHealthMessage;
    
    ProcessError localError;
    
    
    // Application Specific Members
    // INPUTS: Set in funciton before Analyze Image Call
    double sensitivity;
    double dv3[2]; //Pixel Radius Guess from estimated Position

    // Horizontal px/deg poly coefficients
    constexpr static double h_p1 = -2.309e-21;
    constexpr static double h_p2 = 1.681e-17;
    constexpr static double h_p3 = -4.875e-14;
    constexpr static double h_p4 = 7.101e-11;
    constexpr static double h_p5 = -5.405e-8;
    constexpr static double h_p6 = 1.795e-5;
    constexpr static double h_p7 = 0.01462;

    // Vertical px/deg poly coefficients
    constexpr static double v_p1 = -1.067e-20;
    constexpr static double v_p2 = 6.086e-17;
    constexpr static double v_p3 = -1.365e-13;
    constexpr static double v_p4 = 1.53e-10;
    constexpr static double v_p5 = -8.988e-8;
    constexpr static double v_p6 = 2.387e-5;
    
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
    
    void calcRadGuess(double*);
    double calcSens();
    void updatePxDeg(ImageMessage* msg);
    double calcHorzPxDeg(ImageMessage* msg);
    double calcVertPxDeg(ImageMessage* msg);
};

#endif

// Connect to WatchDog

