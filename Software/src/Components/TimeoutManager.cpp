//
//  TimeoutManager.cpp
//  TimeoutManager
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include "TimeoutManager.h"
#include <iostream>

TimeoutManager::TimeoutManager() {
    std::cout<< "TimeoutManager Constructor Called\n";
}

TimeoutManager::~TimeoutManager() {
    
}

ErrorCode TimeoutManager::handleTimeout() {
    return SUCCESS;
}

bool TimeoutManager::getNextTimeout(timeval *t) {
    t = &timeout;
    return true;
}
