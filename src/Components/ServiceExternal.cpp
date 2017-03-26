//
//  ServiceExternal.cpp
//  ServiceExternal
//
//  Created by Seth on 1/29/2017.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#include "ServiceExternal.h"
#include "Server.h"

// Constructor
ServiceExternal::ServiceExternal(Selector& sel, int fd, int buffSize) : Service(sel), fd(fd), readbuf(buffSize), writebuf(buffSize), build(writebuf), parse(readbuf),  partialMessage(false)  {
}

// Destructor
ServiceExternal::~ServiceExternal() {}

void ServiceExternal::registerCallback(void (*messageCallBackFunc)(Message_External*, ServiceExternal*)) {
    messageCallBack = messageCallBackFunc;
}

bool ServiceExternal::open(int fd) {
    this->fd = fd;
    getSelector().registerService(fd, this);
    getSelector().interestInRead(fd);
    return true;
}

bool ServiceExternal::open(std::string hostName, int portNumber) {
    fd = Service::connectToServer(hostName.c_str(), portNumber);
    
    if (fd < 0) {
        // Failed to connect to Server
        return false;
    }
    
    getSelector().registerService(fd, this);
    getSelector().interestInRead(fd);
    return true;
}


// Virtual Methods from Server
void ServiceExternal::handleRead() {
    int length = readbuf.remaining();
    
    if (length == 0) {
        throw "ServiceExternal::handleRead(): No room to read into buffer";
    }
    
    char* buf = readbuf.getBuffer();
    int amountRead = -1;
    
    while (amountRead < 0) {
        amountRead = ::read(fd, buf, length);
        
        if (amountRead == 0) {
            fprintf(Server::getAppl()->getLogFileID(), "Client Disconnection: ServiceExternal::handleRead(): read() returned 0, closing connection\n");
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
    Message_External* msg = nullptr;
    int count = 0;
    // Flip Buffer
    readbuf.flip();
    
    while (true) {
        msg = parse.parseMessage(&partialMessage);
        if (msg == nullptr) {
            break;
        }
        
        (*messageCallBack)(msg, this);
        count++;
    }
    
    //Compact and flip buffer
    readbuf.compact();
    readbuf.flip();
    
    if ((count == 0) && (partialMessage = false)) {
        closeConnection();
        throw "ServiceExternal::handleRead(): Message is big for buffer";
    }
}



void ServiceExternal::handleWrite() {
    int length = writebuf.used();
    
    if (length == 0) {
        // Nothing left to write to socket
        getSelector().noInterestInWrite(fd);
        return;
    }
    
    writebuf.flip();
    char* buf = writebuf.getBuffer();
    
    int amountWritten = write(fd, buf, length);
    if (amountWritten == -1) {
        throw "Error Writing to Socket, Amount Written = -1";
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

void ServiceExternal::closeConnection() {
    if (fd != -1) {
        getSelector().unregisterService(fd);
        ::close(fd);
        fd = -1;
    }
    readbuf.clear();
    writebuf.clear();
}

//Send Message
void ServiceExternal::sendMessage(Message_External* msg) {
    if (isConnected() == false) {
        // Leave If Service is no longer connected
        return;
    }
    
    if (msg == nullptr) {
        throw "ServiceExternal::sendMessage() Message = nullptr";
    }
    
    switch (msg->iden) {
        case E_OSPREStatus:
            build.buildExternal_OSPREStatus(*((External_OSPREStatus*) msg));
            break;
            
        case E_PointingRequest:
            build.buildExternal_PointingRequest(*((External_PointingRequest*) msg));
            break;
            
        case E_SpacecraftDataMessage:
            build.buildExternal_DataMessage(*((External_DataMessage*) msg));
            break;
            
        case E_SolutionMessage:
            build.buildExternal_SolutionMessage(*((External_SolutionMessage*) msg));
            break;
            
        default:
            throw "ServiceExternal::sendMessage() msgID unknown, process exiting";
    }
    
    // Register Intrest in Write
    getSelector().interestInWrite(fd);
}





