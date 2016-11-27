//
//  Server.h
//  Server
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include "Server.h"
#include <iostream>
#include <sys/time.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/select.h>
#include <signal.h>
#include <errno.h>
#include <sys/ioctl.h>

Server::Server(int localPort) {
    
}

Server::~Server() {
    
}

ErrorCode Server::run() {
    
    bool terminateFlag = false;
    while (terminateFlag == false) {
        timeval t;
        
        if (timeout.getNextTimeout(&t) == true) {
            if (sel.select(&t) == false) {
                std::cerr << "select() error, exiting" << std::endl;
                break;
            }
            
            timeout.handleTimeout();
        } else {
            if (sel.select() == false) {
                std::cerr << "select() error, exiting" << std::endl;
                break;
            }
        }
    }
    
    return SUCCESS;
}


