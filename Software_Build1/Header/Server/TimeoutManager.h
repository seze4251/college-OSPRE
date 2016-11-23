//
//  TimeoutManager.h
//  TimeoutManager
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef TIMEOUTMANAGER_H
#def TIMEOUTMANAGER_H

#include "ErrorCode.h"

class TimeoutManager {
public:
    // Constructors
    TimeoutManager();
    
    // Destructor
    ~TimeoutManager();
    
    //Public Methods
    ErrorCode handleTimeout();
    
    //Public Members
    bool timeout;
    
private:
    struct timeval timeout;
    
};

#endif
