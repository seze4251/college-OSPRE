//
//  ServiceExternal.cpp
//  ServiceExternal
//
//  Created by Seth on 1/29/2017.
//  Copyright © 2016 Seth. All rights reserved.
//


#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#include "ServiceExternal.h"


// Constructor
ServiceExternal::ServiceExternal(Selector& sel, int fd, int buffSize) : Service(sel), fd(fd), readbuf(buffSize), writebuf(buffSize), build(writebuf), parse(readbuf),  partialMessage(false)  {
    std::cout << "ServiceExternal Constructor Called" << std::endl;
}

// Destructor
ServiceExternal::~ServiceExternal() {
    
}

void ServiceExternal::registerCallback(void (*messageCallBackFunc)(Message_External*, ServiceExternal*)) {
    std::cout << "ServiceExternal::registerCallback()" << std::endl;
    messageCallBack = messageCallBackFunc;
}

bool ServiceExternal::open(int fd) {
    std::cout << "Service External Open(int fd)" << std::endl;
    this->fd = fd;
    getSelector().registerService(fd, this);
    getSelector().interestInRead(fd);
    return true;

}

bool ServiceExternal::open(std::string hostName, int portNumber) {
    fd = Service::connectToServer(hostName.c_str(), portNumber);
    
    if (fd == -1) {
        return false;
    }
    
    getSelector().registerService(fd, this);
    getSelector().interestInRead(fd);
    return true;
}


// Virtual Methods from Server
void ServiceExternal::handleRead() {
    std::cout << "Entering ServiceExternal::handleRead()" << std::endl;
    int length = readbuf.remaining();
    
    if (length == 0) {
        std::cout << "ServiceExternal::handleRead(): No room to read into buffer" << std::endl;
    }
    
    char* buf = readbuf.getBuffer();
    int amountRead = -1;
    
    while (amountRead < 0) {
        amountRead = ::read(fd, buf, length);
        std::cout << "ServiceExternal::handleRead(): Amount Read: " << amountRead << std::endl;
        
        // ToDo: Revisit code confiriming MANPAGE on read error conditions
        if (amountRead == 0) {
            std::cerr << "ServiceExternal::handleRead(): read() returned 0, closing connection" << std::endl;
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
    
    ///**************
    //TEMP
    // readbuf.printBuffer();
    //TEMP
    //********************
    
    Message* msg = nullptr;
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
        std::cerr << "ServiceExternal::handleRead(): Message is big for buffer" << std::endl;
        closeConnection();
        return;
    }
    
    std::cout << "ServiceExternal::handleRead(): messagesParsed: " << count << std::endl;
}



void ServiceExternal::handleWrite() {
    std::cout << "Entering ServiceExternal::handleWrite()" << std::endl;
    int length = writebuf.used();
    std::cout << "ServiceExternal::handleWrite() writebuf.used: " << length << std::endl;
    
    if (length == 0) {
        std::cout << "Nothing Left to Write to Socket" << std::endl;
        getSelector().noInterestInWrite(fd);
        return;
    }
    
    
    //std::cout << "ServiceInternal::handleWrite(): Printing Write Buffer" << std::endl;
    //writebuf.printBuffer();
    
    
    writebuf.flip();
    
    char* buf = writebuf.getBuffer();
    
    int amountWritten = write(fd, buf, length);
    if (amountWritten == -1) {
        perror("Write Error: ");
    }
    
    std::cout << "Wrote " << amountWritten << " Bytes" << std::endl;
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
void ServiceInternal::sendMessage(Message_External* msg) {
    if (isConnected() == false) {
        std::cout << "ServiceExternal::sendMessage Service is not Connected, returning" << std::endl;
        return;
    }
    
    std::cout << "ServiceExternal::sendMessage() Sending Message" << std::endl;
    
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
            std::cout << "ServiceExternal::sendMessage() msgID unknown, process exiting" << std::endl;
            exit(-1);
    }
    
    // Register Intrest in Write
    getSelector().interestInWrite(fd);
}





