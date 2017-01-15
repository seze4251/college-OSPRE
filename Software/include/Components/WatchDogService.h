//
//  WatchDogService.h
//  WatchDogService
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

// GOES INTO CLIENTS

#ifndef WATCHDOGSERVICE_H
#define WATCHDOGSERVICE_H

#include "ServiceInternal.h"
#include "ProcessID.h"

class WatchDogService : public ServiceInternal {
public:
    WatchDogService(Selector &sel, std::string hostName, int portNumber);
    ~WatchDogService();
    bool open();
    virtual bool isConnected() { return fd != -1 ? true : false; }
    virtual void closeConnection();
    
    void sendStatusResponseMessage();
    
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
    
    // Added Process ID
    ProcessID p_ID;
    
private:
    // Hostname and PortNumber for Server Socket
    std::string hostName;
    int portNumber;
};

#endif
