//
//  Selector.h
//  Selector
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include "Selector.h"
#include <iostream>
#include <string>
#include <errno.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include "Service.h"

Selector::Selector() {
    std::cout << "Selector Constructor Called \n";
    for (int x = 0; x < FD_SETSIZE; x++) {
        services[x] = NULL;
    }
}


Selector::~Selector() {
    
}

void Selector::registerService(int fd, Service *srv) {
    services[fd] = srv;
}

void Selector::unregisterService(int fd) {
    services[fd] = NULL;
    noInterestInRead(fd);
    noInterestInWrite(fd);
}

void Selector::interestInRead(int fd) {
    FD_SET(fd, &readFds);
}

void Selector::interestInWrite(int fd) {
    FD_SET(fd, &writeFds);
}

void Selector::noInterestInRead(int fd) {
    FD_CLR(fd, &readFds);
}

void Selector::noInterestInWrite(int fd) {
    FD_CLR(fd, &writeFds);
}

int Selector::select() {
    
    while (true) {
        memcpy(&tempReadFds, &readFds, sizeof(readFds));
        memcpy(&tempWriteFds, &writeFds, sizeof(writeFds));
        
        int numSelected = ::select(FD_SETSIZE, &tempReadFds, &tempWriteFds, NULL, NULL);
        
        if (numSelected == -1) {
            if (errno == EINTR) {
                continue;
            } else {
                return -1;
            }
        }
        
        for (int i = 0, count = 0; (count < numSelected) && (i < FD_SETSIZE) ; i++) {
            if (FD_ISSET(i, &tempReadFds)) {
                
                if (services[i] != NULL) {
                    services[i]->handleRead();
                } else {
                    std::cerr << "Error, attempt to read() on FD with no associated service" << std::endl;
                    return -1;
                }
                count++;
            }
            
            if (FD_ISSET(i, &tempWriteFds)) {
                
                if (services[i] != NULL) {
                    services[i]->handleWrite();
                } else {
                    std::cerr << "Error, attempt to write() on FD with no associated service" << std::endl;
                    return -1;
                }
                count++;
                
            }
        }
        
        break;
    }
    return 0;
}




// Very Incomplete
int Selector::select(timeval *timeout) {
    int numSelect = ::select(FD_SETSIZE, &readFds, &writeFds, NULL, timeout);
    return numSelect;
}


int Selector::selectNow() {
    return 0;
}



