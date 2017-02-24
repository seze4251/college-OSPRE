//
//  ServerInternal.h
//  ServerInternal
//
//  Created by Seth on 01/17/2017.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SERVERINTERNAL_H
#define SERVERINTERNAL_H

#include "Server.h"
#include "ServiceInternal.h"
#include "Internal_Messages.h"
#include "Message.h"

class ServerInternal : public Server {
public:
    // Constructors
    ServerInternal(std::string hostName, int localPort, ProcessID p_ID);
    
    //Destructor
    virtual ~ServerInternal();
    
    //Maximum Clients Enumeration
    enum { MaxClients = 20 };
    
    // Virtual CallBack Method for Acceptor
    static void handleConnectionRequest(int fd);
    
    //Public Methods
    static void handleMessage(Message* msg, ServiceInternal* service);
    
    // Virtual Open Method for Applications
    virtual void open() = 0;
    
    // Connect to Internal Applicaiton
    bool connectToAppl(std::string host, int port, ServiceInternal** service);
    
    // Message Handlers
    virtual void handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service) = 0;
    virtual void handleDataMessage(DataMessage* msg, ServiceInternal* service) = 0;
    virtual void handleImageAdjustment(ImageAdjustment* msg, ServiceInternal* service) = 0;
    virtual void handleImageMessage(ImageMessage* msg, ServiceInternal* service) = 0;
    virtual void handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service) = 0;
    virtual void handlePointingRequest(PointingRequest* msg, ServiceInternal* service) = 0;
    virtual void handleProcessHealthAndStatusRequest(ProcessHealthAndStatusRequest* msg, ServiceInternal* service) = 0;
    virtual void handleProcessHealthAndStatusResponse(ProcessHealthAndStatusResponse* msg, ServiceInternal* service) = 0;
    virtual void handleSolutionMessage(SolutionMessage* msg, ServiceInternal* service) = 0;
    virtual void handleProcessedImageMessage(ProcessedImageMessage* msg, ServiceInternal* service) = 0;
    
    // Process ID object, temporary
    ProcessID p_ID;
    static ProcessID p_ID_Static;
    
protected:
    Acceptor accept;
    
    std::string hostName;
    int localPort;
    
    static ServiceInternal *connections[MaxClients];
    
private:
    
    
};

#endif
