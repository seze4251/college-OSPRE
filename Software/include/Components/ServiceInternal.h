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

#include "Service.h"
#include "Builder.h"
#include "Parser.h"
#include "ByteBuffer.h"


class ServiceInternal : public Service {
public:
    ServiceInternal(Selector& sel, int fd = -1) : Service(sel), fd(fd), readbuf(1024*1024), writebuf(1024*1024), build(writebuf), parse(readbuf) {
        std::cout << "ServiceInternal Constructor Called" << std::endl;
    }
    
    void handleRead();
    void handleWrite();
    
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
    int fd;
    ByteBuffer readbuf;
    ByteBuffer writebuf;
    Builder build;
    Parser parse;

private:
    int parseAndProcessMessages();

    
};

#endif
