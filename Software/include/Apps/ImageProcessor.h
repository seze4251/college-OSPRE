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

#include "ServerInternal.h"
#include "WatchDogService.h"
#include "ProcessID.h"

class ImageProcessor : public ServerInternal {
public:
    ImageProcessor(std::string hostName, int localPort, int watchDogPort);
    ~ImageProcessor();
    virtual void handleTimeout();
    bool open();
    static void handleImageProcessorConnections(int fd);
    
    // Message Handlers
    virtual void handleCaptureImageRequest(CaptureImageRequest* msg);
    virtual void handleDataRequest(DataRequest* msg);
    virtual void handleEphemerisMessage(EphemerisMessage* msg);
    virtual void handleImageAdjustment(ImageAdjustment* msg);
    virtual void handleImageMessage(ImageMessage* msg);
    virtual void handleOSPREStatus(OSPREStatus* msg);
    virtual void handlePointingRequest(PointingRequest* msg);
    virtual void handleProccessHealthAndStatusRequest(ProccessHealthAndStatusRequest* msg);
    virtual void handleProccessHealthAndStatusResponse(ProccessHealthAndStatusResponse* msg);
    virtual void handleSolutionMessage(SolutionMessage* msg);
    
    ProcessID p_ID;
private:
    time_t pollTime;
    WatchDogService watchDog;
    
    //Acceptor Port and Host
    std::string hostName;
    int localPort;
};

#endif

