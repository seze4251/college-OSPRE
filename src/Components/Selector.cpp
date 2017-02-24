//
//  Selector.h
//  Selector
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>
#include <cstring>
#include <string>
#include <errno.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "Selector.h"
#include "Service.h"

Selector::Selector() {
    std::cout << "Selector Constructor Called \n";
    for (int x = 0; x < FD_SETSIZE; x++) {
        services[x] = NULL;
    }
    
    FD_ZERO(&readFds);
    FD_ZERO(&writeFds);
}


Selector::~Selector() {
    
}

void Selector::registerService(int fd, Service *srv) {
    printf("Selector:: registerService fd: %d\n",fd);
    services[fd] = srv;
}

void Selector::unregisterService(int fd) {
    services[fd] = NULL;
    noInterestInRead(fd);
    noInterestInWrite(fd);
}

void Selector::interestInRead(int fd) {
   // printf("Selector:: Interest in Read fd: %d\n",fd);
    //std::cout << "Printing ReadFds" << std::endl;
    //printFds(&readFds);
    FD_SET(fd, &readFds);
}

void Selector::interestInWrite(int fd) {
    //printf("Selector:: Interest in Write fd: %d\n",fd);
    FD_SET(fd, &writeFds);
}

void Selector::noInterestInRead(int fd) {
    printf("Selector:: NO---Interest in Read fd: %d\n",fd);
    FD_CLR(fd, &readFds);
}

void Selector::noInterestInWrite(int fd) {
    //printf("Selector:: NO --- Interest in Write fd: %d\n",fd);
    FD_CLR(fd, &writeFds);
}

int Selector::select(timeval *timeout) {
    //std::cout << "Selector::select(timeout)" << std::endl;
    while (true) {
        
        memcpy(&tempReadFds, &readFds, sizeof(readFds));
        memcpy(&tempWriteFds, &writeFds, sizeof(writeFds));
        
       // std::cout << "Printing tempReadFds" << std::endl;
       // printFds(&tempReadFds);
        int numSelected = ::select(FD_SETSIZE, &tempReadFds, &tempWriteFds, NULL, timeout);
        //printf("Select Returned: %d\n", numSelected);
        
        if (numSelected == -1) {
            if (errno == EINTR) {
                continue;
            } else {
                return -1;
            }
        } else if (numSelected == 0) {
            return 0;
        }
        
       // std::cout<< " checking readFds & writeFds" << std::endl;
        
        for (int i = 0, count = 0; (count < numSelected) && (i < FD_SETSIZE) ; i++) {
            if (FD_ISSET(i, &tempReadFds)) {
                
                if (services[i] != NULL) {
                    printf("HandleRead Called for %d\n", i);
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
                    if (FD_ISSET(i, &writeFds)) {
                        std::cerr << "Error, attempt to write() on FD with no associated service" << std::endl;
                        return -1;
                    }
                }
                count++;
            }
        }
        
        break;
    }
    return 0;
}


void Selector::printFds(fd_set* set) {
    
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (FD_ISSET(i, set)) {
            std::cout << "File Descriptor: " << i << " is set" << std::endl;
        }
    }
}





