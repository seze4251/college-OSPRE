//
//  ServiceInternal.h
//  ServiceInternal
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SERVICEINTERNAL_H
#define SERVICEINTERNAL_H
#include <string>
#include <iostream> 
#include <vector>

#include "Service.h"
#include "Builder.h"
#include "Parser.h"
#include "ByteBuffer.h"


class ServiceInternal : public Service {
public:
    // Constructor
    ServiceInternal(Selector& sel, int fd = -1,  int buffSize = 1024*1024);
    
    // Destructor
    ~ServiceInternal();
    
    //Initialize InternalService Methods
    bool open(int fd);
    bool open(std::string hostName, int portNumber);
    void registerCallback(void (*messageCallBackFunc)(Message*, ServiceInternal*));
    
    //Virtual Service Methods
    virtual void handleRead();
    virtual void handleWrite();
    virtual bool isConnected() { return fd != -1 ? true : false; }
    virtual void closeConnection();

    //Send Message Functions
    void sendStatusRequestMessage();
    void sendStatusResponseMessage(std::vector<ProcessError> status);
    void sendImageMessage(char* image);
    void sendProcessedImageMessage();
    void sendCaptureImageRequestMessage();
    void sendPointingRequestMessage();
    void sendSolutionMessage();
    
protected:
    int fd;
    ByteBuffer readbuf;
    ByteBuffer writebuf;
    Builder build;
    Parser parse;

private:
    // Callback Function
    void (*messageCallBack)(Message*, ServiceInternal*);

    
};

#endif
