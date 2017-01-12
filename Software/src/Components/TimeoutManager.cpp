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
    std::cout<< "TimeoutManager Constructor\n";
}

TimeoutManager::~TimeoutManager() {
    
}

ErrorCode TimeoutManager::handleTimeout() {
    std::cout << "TimeoutManager handleTimeout() " << std::endl;
    return SUCCESS;
}

bool TimeoutManager::getNextTimeout(timeval *t) {
    std::cout << "TimeoutManager getNextTimeout() " << std::endl;
    t = &timeout;
    return true;
}
