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

#include "ServerInternal.h"
#include "WatchDogClientHandler.h"
#include "ProcessID.h"

class WatchDog : public ServerInternal {
    public:
    enum {MaxClients = 16 };
    WatchDog(std::string hostName, int serverPort);
    ~WatchDog();
    static void handleWatchDogConnections(int fd);
    bool open();
    virtual void handleTimeout();
    
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

    // Process ID object, temporary
    ProcessID p_ID;
    
private:
    static WatchDogClientHandler *client[MaxClients];
    static int clientCount;
    time_t pollTime;
    
    //Acceptor Port and Host
    std::string hostName;
    int localPort;
};

#endif
