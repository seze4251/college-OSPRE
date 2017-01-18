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

#include "ServerInternal.h"
#include "WatchDogService.h"
#include "ProcessID.h"

class GNC : public ServerInternal {
public:
    GNC(std::string hostName, int watchDogPort);
    ~GNC();
    virtual void handleTimeout();
    bool open();
    
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
};

#endif

