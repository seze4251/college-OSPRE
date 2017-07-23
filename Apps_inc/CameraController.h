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
#include <vector>
#include <stdio.h>


#include "ServerInternal.h"
#include "ProcessID.h"
#include "ProcessError.h"
#include "OSPRE_Exceptions.h"
#include "ImageNameReader.h"

class CameraController : public ServerInternal {
public:
    // Constructor
    CameraController(std::string hostName, int localPort);
    
    // Destructor
    ~CameraController();
    
    // Opens CameraController Connections
    virtual void open();
    
    virtual void handleTimeout();
    
    // Applicaiton Functionality
    bool canCaptureImage(CaptureImageRequest* msg);
    void captureImage();
    void readImage(std::string);
    void adjustCameraSettings(ImageAdjustment* msg);
    
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
    ServiceInternal* imageProc;
    ServiceInternal* scComms;
    
    // Pointer To Hold Messages that are being sent
    ImageMessage* imageMessage;
    ProcessHealthAndStatusResponse* processHealthMessage;
    
    // Hold Most Recent Data Message
    DataMessage data;
    
    ProcessError localError;
    
    ImageNameReader imageReader;
    
    int currentImageSize;
    int cameraHeight;
    int cameraWidth;
    double pix_deg[2];
    int rectCoords[2];
    int cropCoords[2];

    void read_ConfigFile(std::string config_file);
};

#endif

