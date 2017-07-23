//
//  WatchDogClientHandler.cpp
//  WatchDogClientHandler
//
//  Created by Seth on 11/27/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#include "ServiceInternal.h"
#include "Server.h"

// Constructor
ServiceInternal::ServiceInternal(Selector& sel, int fd, int buffSize) : Service(sel), fd(fd), readbuf(buffSize), writebuf(buffSize), build(writebuf), parse(readbuf) {}

// Destructor
ServiceInternal::~ServiceInternal() {}

//Initialize InternalService Methods
bool ServiceInternal::open(int fd) {
    this->fd = fd;
    getSelector().registerService(fd, this);
    getSelector().interestInRead(fd);
    return true;
}

bool ServiceInternal::open(std::string hostName, int portNumber) {
    fd = Service::connectToServer(hostName.c_str(), portNumber);
    
    if (fd < 0) {
        // Could Not Connect To Server
        return false;
    }
    
    getSelector().registerService(fd, this);
    getSelector().interestInRead(fd);
    return true;
}

void ServiceInternal::registerCallback(void (*messageCallBackFunc)(Message*, ServiceInternal*)) {
    messageCallBack = messageCallBackFunc;
}

// Virtual Methods from Server
void ServiceInternal::handleRead() {
    int length = readbuf.remaining();
    
    if (length == 0) {
        throw "ServiceInternal::handleRead(): No room to read into buffer";
    }
    
    char* buf = readbuf.getBuffer();
    int amountRead = -1;
    
    while (amountRead < 0) {
        amountRead = ::read(fd, buf, length);

        if (amountRead == 0) {
            fprintf(Server::getAppl()->getLogFileID(), "Client Disconnection: ServiceInternal::handleRead(): read() returned 0, closing connection\n");
            closeConnection();
            return;
            
        } else if (amountRead == -1) {
            if (errno == EINTR) {
                continue;
            } else {
                perror("Error: ");
                closeConnection();
                return;
            }
        }
    }
    
    readbuf.positionRead(amountRead);
    
    Message* msg = nullptr;
    int count = 0;
    
    // Flip Buffer
    readbuf.flip();
    
    while (true) {
        msg = parse.parseMessage();
        if (msg == nullptr) {
            break;
        }
        
        (*messageCallBack)(msg, this);
        count++;
    }
    
    //Compact and flip buffer
    readbuf.compact();
    readbuf.flip();
}



void ServiceInternal::handleWrite() {
    int length = writebuf.used();
    
    if (length == 0) {
        //Nothing Left to Write to Socket
        getSelector().noInterestInWrite(fd);
        return;
    }
    
    writebuf.flip();
    char* buf = writebuf.getBuffer();
    
    int amountWritten = write(fd, buf, length);
    if (amountWritten == -1) {
        perror("Write Error: ");
    }
    
    if (amountWritten == length) {
        writebuf.clear();
        getSelector().noInterestInWrite(fd);
    } else {
        // Compact Buffer and keep the interest in writing with selector
        writebuf.positionWrite(amountWritten);
        writebuf.compact();
        writebuf.flip();
    }
}

void ServiceInternal::closeConnection() {
    if (fd != -1) {
        getSelector().unregisterService(fd);
        ::close(fd);
        fd = -1;
    }
    readbuf.clear();
    writebuf.clear();
}




void ServiceInternal::sendMessage(Message* msg) {
    if (isConnected() == false) {
        // Service is no longer connected
        return;
    }
    
    if (msg == nullptr) {
        throw "ServiceInternal::sendMessage() Message = nullptr";
    }
    
    switch (msg->iden) {
        case I_CaptureImageRequest:
            build.buildCaptureImageRequest(*((CaptureImageRequest*) msg));
            break;
            
        case I_DataMessage:
            build.buildDataMessage(*((DataMessage*) msg));
            break;
            
        case I_ImageAdjustment:
            build.buildImageAdjustment(*((ImageAdjustment*) msg));
            break;
            
        case I_ImageMessage:
            build.buildImageMessage(*((ImageMessage*) msg));
            break;
            
        case I_OSPREStatus:
            build.buildOSPREStatus(*((OSPREStatus*) msg));
            break;
            
        case I_PointingRequest:
            build.buildPointingRequest(*((PointingRequest*) msg));
            break;
            
        case I_ProcessHealthAndStatusRequest:
            build.buildProcessHealthAndStatusRequest(*((ProcessHealthAndStatusRequest*) msg));
            break;
            
        case I_ProcessHealthAndStatusResponse:
            build.buildProcessHealthAndStatusResponse(*((ProcessHealthAndStatusResponse*) msg));
            break;
        case I_SolutionMessage:
            build.buildSolutionMessage(*((SolutionMessage*) msg));
            
            break;
        case I_ProcessedImageMessage:
            build.buildProcessedImageMessage(*((ProcessedImageMessage*) msg));
            break;
        default:
            throw "ServiceInternal::sendMessage() msgID unknown";
    }
    
    // Register Intrest in Write
    getSelector().interestInWrite(fd);
}








