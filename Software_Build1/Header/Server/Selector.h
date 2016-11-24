//
//  Selector.h
//  Selector
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SELECTOR_H
#define SELECTOR_H

#include "ErrorCode.h"
#include <sys/select.h>

// *****Needed???********
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
// *****Needed???********

class Selector {
public:
    // Constructors
    Selector();
    
    // Destructor
    ~Selector();
    
    //Public Methods
    int select();
    
    void registerService(int fd, Service *srv);
    void unregisterSerivce(int fd);
    
    void interestInRead(int fd);
    void interestInWrite(int fd);
    
    void noInterestInRead(int fd);
    void noInterestInWrite(int fd);
    
    ErrorCode select(timeval &timeout);
    ErrorCode selectNow();
    
    
    // Public Members
    bool read;
    bool write;
    
private:
    std::vector<Service> srv;
    Service *services[FD_SETSIZE];
    fd_set readFds, writeFds;
    fd_set tempReadFds, tempWriteFds;
    
};

#endif
