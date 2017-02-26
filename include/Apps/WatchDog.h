//
//  WatchDog.h
//  WatchDog
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <string>
#include <ctime>
#include <stdio.h>

#include "ServerInternal.h"
#include "ProcessID.h"
#include "OSPRE_Exceptions.h"

class WatchDog : public ServerInternal {
public:
    // Constructor
    WatchDog(std::string hostName, int serverPort);
    
    // Destructor
    ~WatchDog();
    
    // Opens WatchDogs Connections
    virtual void open();
    
    virtual void handleTimeout();
    
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
    // Poll Times
    time_t pollProcess;
    time_t pollStatus;
    
    // Connected Services
    ServiceInternal* scComms;
    ServiceInternal* gnc;
    ServiceInternal* imageProc;
    ServiceInternal* cameraControl;
    
    // Pointer To Hold Messages that Are being sent
    ProcessHealthAndStatusRequest* processHealthRequestMessage;
    OSPREStatus* ospreStatusMessage;
    
    // Received Responses from Process
    bool healthyScComms;
    bool healthyScGnc;
    bool healthyImageProc;
    bool healthyCameraControl;
};

#endif

// Connect to Nobody
