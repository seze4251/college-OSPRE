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

#include "ServerInternal.h"
#include "WatchDogService.h"
#include "ProcessID.h"

class CameraController : public ServerInternal {
public:
    // Constructor
    CameraController(std::string hostName, int localPort, int watchDogPort);
    
    // Destructor
    ~CameraController();
    
    // Opens CameraController Connections
    virtual bool open();
    
    virtual void handleTimeout();
    
    // Message Handlers
    virtual void handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service);
    virtual void handleDataRequest(DataRequest* msg, ServiceInternal* service);
    virtual void handleEphemerisMessage(EphemerisMessage* msg, ServiceInternal* service);
    virtual void handleImageAdjustment(ImageAdjustment* msg, ServiceInternal* service);
    virtual void handleImageMessage(ImageMessage* msg, ServiceInternal* service);
    virtual void handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service);
    virtual void handlePointingRequest(PointingRequest* msg, ServiceInternal* service);
    virtual void handleProccessHealthAndStatusRequest(ProccessHealthAndStatusRequest* msg, ServiceInternal* service);
    virtual void handleProccessHealthAndStatusResponse(ProccessHealthAndStatusResponse* msg, ServiceInternal* service);
    virtual void handleSolutionMessage(SolutionMessage* msg, ServiceInternal* service);
    
private:
    int watchDogPort;
    ServiceInternal* imageProc;
    ServiceInternal* scComms;
    ServiceInternal* watchDog;
    
};

#endif

// Camera Controller Connect to ScComms, WatchDog and IP
