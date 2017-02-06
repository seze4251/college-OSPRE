//
//  ServiceExternal.h
//  ServiceExternal
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SERVICEEXTERNAL_H
#define SERVICEEXTERNAL_H
#include <string>
#include <iostream>
#include <vector>

#include "Service.h"
#include "External_Builder.h"
#include "External_Parser.h"
#include "ByteBuffer.h"

class ServiceExternal : public Service {
public:
    // Constructor
    ServiceExternal(Selector& sel, int fd = -1, int buffSize = 1024*1024);
    
    // Destructor
    ~ServiceExternal();
    // Service Virtual Methods
    virtual void handleRead();
    virtual void handleWrite();
    virtual bool isConnected() { return fd != -1 ? true : false; }
    virtual void closeConnection();
    
    // Open Methods
    bool open(int fd);
    bool open(std::string hostName, int portNumber);
    
    // Send Message Funcitons
    void sendExternalDataMessage(External_DataMessage* msg);
    void sendExternalSolutionMessage(External_SolutionMessage* msg);
    void sendExternalOSPREStatusMessage(External_OSPREStatus* msg);
    void sendExternalPointingRequestMessage(External_PointingRequest* msg);


protected:
    
private:
    int fd;
    ByteBuffer readbuf;
    ByteBuffer writebuf;
    External_Builder build;
    External_Parser parse;
    
    
};

#endif
