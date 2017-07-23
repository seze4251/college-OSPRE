//
//  ScComms.h
//  ScComms
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SCCOMMS_H
#define SCCOMMS_H

#include <string>
#include <ctime>
#include <vector>
#include <stdio.h>

#include "ServerInternal.h"
#include "ProcessID.h"
#include "ServiceExternal.h"
#include "OSPRE_Exceptions.h"

class ScComms : public ServerInternal {
public:
    // Constructor
    ScComms(std::string hostName, int localPort, int externalPort);
    
    //Destructor
    ~ScComms();
    
    // Opens ScComms Connections
    virtual void open();
    
    virtual void handleTimeout();
    
    //Acceptor function for External Connections
    static void handleExternalConnection(int fd);
    
    // Generic Message Handler for External Messages
    static void handleExternalMessage(Message_External* msg, ServiceExternal* service);
    
    // Additional Message Handler for ScComms
    void handleExternalDataMessage(External_DataMessage* msg, ServiceExternal* service);
    void handleExternalOSPREStatusMessage(External_OSPREStatus* msg, ServiceExternal* service);
    void handleExternalPointingMessage(External_PointingRequest* msg, ServiceExternal* service);
    void handleExternalSolutionMessage(External_SolutionMessage* msg, ServiceExternal* service);
    
    
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
    Acceptor external_accept;
    int externalPort;
    
    static ServiceExternal* spacecraft;
    
    // Pointer To Hold Messages that Are being sent
    ProcessHealthAndStatusResponse* processHealthMessage;
    DataMessage*  dataMessage;
    External_OSPREStatus* externalOspreStatusMessage;
    External_PointingRequest* externalPointingMessage;
    External_SolutionMessage* externalSolutionMessage;
    
    ProcessError localError;
};

#endif


