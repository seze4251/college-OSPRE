//
//  Acceptor.cpp
//  Acceptor
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include "Acceptor.h"
#include <iostream>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h> 

Acceptor::Acceptor(Selector &sel) : Service(sel) {
    std::cout << "Acceptor Constructor" << std::endl;
    port = -1;
    hostName = "";
    fd = -1;
}

bool Acceptor::open(std::string hostName, int portNumber) {
    // Check to see if Acceptor is open
    if (isConnected() == true) {
        std::cout << "Acceptor is already connected" << std::endl;
        return true;
    }
    
    // Assign Inputs To Object Members
    this->port = portNumber;
    this->hostName = hostName;
    
    // Open Server Socket
    fd = openServerSocket(port);
    
    if (fd == -1) {
        std::cerr << "Acceptor::open() Failure to Open Server Socket, Acceptor Exiting\n";
        return false;
    }
    
    if (callBack == NULL) {
        std::cerr << "Acceptor::open() CallBack equals NULL, Acceptor Exiting\n";
        return false;
    }
    getSelector().registerService(fd, this);
    getSelector().interestInRead(fd);
    return true;
}

void Acceptor::registerCallback(void (*callbackFunc)(int)) {
    //std::cout << "Acceptor registerCallback()" << std::endl;
    callBack = callbackFunc;
}

void Acceptor::closeConnection() {
    if (fd != -1) {
        ::close(fd);
        fd = -1;
    }
}

void Acceptor::handleRead() {
   // std::cout << "Acceptor handleRead()" << std::endl;
    int cfd = accept(fd, NULL, NULL);
    
    std::cout << "Received client connection, processing input " << cfd << std::endl;
    int opt = 1;
    
    // Make Socket Nonblocking
    ioctl(cfd, FIONBIO, &opt);
    
    // Acceptor Callback to handle the new connection 
    (*callBack)(cfd);
}

void Acceptor::handleWrite() {
    std::cerr << "Acceptor::handleWrite() Method Not Implemented, Don't Call This, Throwing Exception" << std::endl;
    throw "Acceptor::handleWrite() Method Should not be called ever!";
}




