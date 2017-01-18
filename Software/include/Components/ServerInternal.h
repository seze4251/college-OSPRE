//
//  ServerInternal.h
//  ServerInternal
//
//  Created by Seth on 01/17/2017.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SERVERINTERNAL_H
#define SERVERINTERNAL_H

#include <ctime>

#include "Server.h"
#include "Internal_Messages.h"
#include "Message.h"

class ServerInternal : public Server {
public:
    // Constructors
    ServerInternal();
    
    //Destructor
    virtual ~ServerInternal();
    
    //Public Methods
    void handleMessage(Message* msg);
    
    // Message Handlers
    virtual void handleCaptureImageRequest(CaptureImageRequest* msg) = 0;
    virtual void handleDataRequest(DataRequest* msg) = 0;
    virtual void handleEphemerisMessage(EphemerisMessage* msg) = 0;
    virtual void handleImageAdjustment(ImageAdjustment* msg) = 0;
    virtual void handleImageMessage(ImageMessage* msg) = 0;
    virtual void handleOSPREStatus(OSPREStatus* msg) = 0;
    virtual void handlePointingRequest(PointingRequest* msg) = 0;
    virtual void handleProccessHealthAndStatusRequest(ProccessHealthAndStatusRequest* msg) = 0;
    virtual void handleProccessHealthAndStatusResponse(ProccessHealthAndStatusResponse* msg) = 0;
    virtual void handleSolutionMessage(SolutionMessage* msg) = 0;

protected:
    Acceptor accept;
    time_t pollTime;

private:
    
    
};

#endif
