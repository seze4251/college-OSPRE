//
//  Acceptor.cpp
//  Acceptor
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include "Acceptor.h"

Acceptor::Acceptor(Selector &sel, std::string hostName, int port) : Service(sel) {
    this->port = port;
    this->hostName = hostName;
    fd = openServerSocket();
    if (fd == -1) {
        std::cerr << "Failure to Open Server Socket, Acceptor Exiting";
        exit();
    }
}

void Acceptor::handleRead() {
    int cfd = accept(sfd, NULL, NULL);
    
    std::cout << "Received client connection, processing input " << cfd << std::endl;
    int opt = 1;
    ioctl(cfd, FIONBIO, &opt); // Make Socket Nonblock
}

void Acceptor::handleWrite() {
    std::cerr << "Don't Call This" << std::endl;
}
