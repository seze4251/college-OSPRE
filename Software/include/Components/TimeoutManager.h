//
//  TimeoutManager.h
//  TimeoutManager
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef TIMEOUTMANAGER_H
#define TIMEOUTMANAGER_H

#include "ErrorCode.h"
#include <sys/time.h>

class TimeoutManager {
public:
    // Constructors
    TimeoutManager();
    
    // Destructor
    ~TimeoutManager();
    
    //Public Methods
    ErrorCode handleTimeout();
    bool getNextTimeout(timeval *t);
    
    
private:
    timeval timeout;
    
};

#endif
