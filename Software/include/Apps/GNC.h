//
//  GNC.h
//  GNC
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef GNC_H
#define GNC_H

#include <string>
#include <ctime>
#include <vector>


#include "ServerInternal.h"
#include "ProcessID.h"
#include "PointEarthMoon.h"
#include "CircularBuffer.h"

class GNC : public ServerInternal {
public:
    // Constructor
    GNC(std::string hostName, int localPort);
    
    // Destructor
    ~GNC();
    
    // Opens GNC Connections
    virtual void open();
    
    virtual void handleTimeout();
    
    // Applicaiton Functionality
    void computeSolution(DataMessage*, ProcessedImageMessage*);
    
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
    // Internal Members  for System Architecture
    time_t pollTime;
    ServiceInternal* scComms;
    ServiceInternal* cameraController;
    std::vector<ProcessError> status;
    
    // Pointer To Hold Messages that Are being sent
    ProcessHealthAndStatusResponse* processHealthMessage;
    PointingRequest* pointRequest;
    CaptureImageRequest* captureImageMessage;
    SolutionMessage* solutionMessage;
    
    // Buffer to hold Data Messages
    CircularBuffer circBuf;
    
    // Where Spacecraft is currently pointing (Earth or Moon)
    PointEarthMoon point;
    
    // Spacecraft Position
    double latestPosition[3];
    


    
};

#endif

// GNC Connect to WatchDog, IP and SC Comms

