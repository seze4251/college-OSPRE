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
    // Constructor
    WatchDog(std::string hostName, int serverPort);
    
    // Destructor
    ~WatchDog();
    
    // Opens WatchDogs Connections
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
    

};

#endif

// Connect to Nobody
