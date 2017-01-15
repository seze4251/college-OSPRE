//
//  WatchDogClientHandler.h
//  WatchDogClientHandler
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

// GOES INTO WATCHDOG

#ifndef WATCHDOGCLIENTHANDLER_H
#define WATCHDOGCLIENTHANDLER_H

#include "ServiceInternal.h"

class WatchDogClientHandler : ServiceInternal {
public:
    //Constructor
    WatchDogClientHandler(Selector &sel, int fd);
    
    // Destructor
    ~WatchDogClientHandler();
    
    virtual bool isConnected() { return fd != -1 ? true : false; }
    virtual void closeConnection();

    void sendStatusRequestMessage();
    
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
    
private:
};


#endif
