//
//  Acceptor.cpp
//  Acceptor
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "Acceptor.h"

Acceptor::Acceptor(Selector &sel) : Service(sel) {
    port = -1;
    hostName = "";
    fd = -1;
}

bool Acceptor::open(std::string hostName, int portNumber) {
    // Check to see if Acceptor is open
    if (isConnected() == true) {
        return true;
    }

    // Assign Inputs To Object Members
    this->port = portNumber;
    this->hostName = hostName;
    
    // Open Server Socket
    fd = openServerSocket(port);
    
    if (fd == -1) {
        throw "Acceptor::open() Failure to Open Server Socket, Acceptor Exiting";
    }
    
    if (callBack == NULL) {
        throw "Acceptor::open() CallBack equals NULL, Acceptor Exiting";
    }
    
    getSelector().registerService(fd, this);
    getSelector().interestInRead(fd);
    return true;
}

void Acceptor::registerCallback(void (*callbackFunc)(int)) {
    callBack = callbackFunc;
}

void Acceptor::closeConnection() {
    if (fd != -1) {
        ::close(fd);
        fd = -1;
    }
}

void Acceptor::handleRead() {
    int cfd = accept(fd, NULL, NULL);
    int opt = 1;
    
    // Make Socket Nonblocking
    ioctl(cfd, FIONBIO, &opt);
    
    // Acceptor Callback to handle the new connection 
    (*callBack)(cfd);
}

void Acceptor::handleWrite() {
    throw "Acceptor::handleWrite() Method Should not be called ever!";
}




