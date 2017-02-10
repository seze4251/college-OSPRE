//
//  Spacecraft.h
//  Spacecraft
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include <string>
#include <ctime>


#include "Server.h"
#include "ServiceExternal.h"

class Spacecraft : public Server {
public:
    // Constructor
    Spacecraft(std::string hostName, int localPort);
    
    // Destructor
    ~Spacecraft();
    
    virtual void handleTimeout();
    void open();
    
    // Generic Message Handler for External Messages
    void handleExternalMessage(Message_External* msg, ServiceExternal* service);
    
    // Additional Message Handler for Spacecraft
    void handleExternalDataMessage(External_DataMessage* msg, ServiceExternal* service);
    void handleExternalOSPREStatusMessage(External_OSPREStatus* msg, ServiceExternal* service);
    void handleExternalPointingMessage(External_PointingRequest* msg, ServiceExternal* service);
    void handleExternalSolutionMessage(External_SolutionMessage* msg, ServiceExternal* service);
    
private:
    // Connect to OSPRE
    std::string ospreHostName;
    int osprePort;
    
    // System Architecture
    time_t pollTime;
    ServiceExternal* scComms;
    
    // Pointer To Hold Messages that Are being sent
    External_DataMessage* dataMessage;
};

#endif

// Connect to ScComms

