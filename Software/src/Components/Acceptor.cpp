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

Acceptor::Acceptor(Selector &sel) : Service(sel) {
    std::cout << "Acceptor Constructor" << std::endl;
    port = -1;
    hostName = "";
    fd = -1;
}

bool Acceptor::open(std::string hostName, int portNumber) {
    std::cout << "Acceptor open()" << std::endl;
    port = portNumber;
    this->hostName = hostName;
    fd = openServerSocket(port);
    if (fd == -1) {
        std::cerr << "Failure to Open Server Socket, Acceptor Exiting\n";
        return false;
    }
    
    if (callBack == NULL) {
        std::cerr << "CallBack equals NULL, Acceptor Exiting\n";
        return false;
    }
    getSelector().registerService(fd, this);
    getSelector().interestInRead(fd);
    return true;
}

void Acceptor::registerCallback(void (*callbackFunc)(int)) {
    std::cout << "Acceptor registerCallback()" << std::endl;
    callBack = callbackFunc;
}

void Acceptor::handleRead() {
    std::cout << "Acceptor handleRead()" << std::endl;
    int cfd = accept(fd, NULL, NULL);
    
    std::cout << "Received client connection, processing input " << cfd << std::endl;
    int opt = 1;
    ioctl(cfd, FIONBIO, &opt); // Make Socket Nonblock
    (*callBack)(cfd);
}

void Acceptor::handleWrite() {
    std::cerr << "Acceptor handleWrite() Don't Call This" << std::endl;
}
