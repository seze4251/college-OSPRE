//
//  CameraController.h
//  CameraController
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <string>
#include <ctime>


#include "ServerInternal.h"
#include "WatchDogService.h"
#include "ProcessID.h"

class CameraController : public ServerInternal {
public:
    // Constructor
    CameraController(std::string hostName, int localPort);
    
    // Destructor
    ~CameraController();
    
    // Opens CameraController Connections
    virtual void open();
    
    virtual void handleTimeout();
    
    // Message Handlers
    virtual void handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service);
    virtual void handleEphemerisMessage(EphemerisMessage* msg, ServiceInternal* service);
    virtual void handleImageAdjustment(ImageAdjustment* msg, ServiceInternal* service);
    virtual void handleImageMessage(ImageMessage* msg, ServiceInternal* service);
    virtual void handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service);
    virtual void handlePointingRequest(PointingRequest* msg, ServiceInternal* service);
    virtual void handleProcessHealthAndStatusRequest(ProcessHealthAndStatusRequest* msg, ServiceInternal* service);
    virtual void handleProcessHealthAndStatusResponse(ProcessHealthAndStatusResponse* msg, ServiceInternal* service);
    virtual void handleSolutionMessage(SolutionMessage* msg, ServiceInternal* service);
    virtual void handleProcessedImageMessage(ProcessedImageMessage* msg, ServiceInternal* service);
    
private:
    time_t pollTime;
    ServiceInternal* imageProc;
    ServiceInternal* scComms;
    
};

#endif

// Camera Controller Connect to ScComms, WatchDog and IP
