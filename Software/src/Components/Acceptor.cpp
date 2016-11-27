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

Acceptor::Acceptor(Selector &sel, std::string hostName, int port, void (*callBack)(int)) : Service(sel) {
    this->port = port;
    this->hostName = hostName;
    fd = openServerSocket(port);
    if (fd == -1) {
        std::cerr << "Failure to Open Server Socket, Acceptor Exiting\n";
        exit(-1);
    }
    this->callBack = callBack;
    
    if (callBack == NULL) {
        std::cerr << "CallBack equals NULL, Acceptor Exiting\n";
        exit(-1);
    }
}

void Acceptor::handleRead() {
    int cfd = accept(fd, NULL, NULL);
    
    std::cout << "Received client connection, processing input " << cfd << std::endl;
    int opt = 1;
    ioctl(cfd, FIONBIO, &opt); // Make Socket Nonblock
    (*callBack)(cfd);
}

void Acceptor::handleWrite() {
    std::cerr << "Don't Call This" << std::endl;
}
