//
//  WatchDogClientHandler.h
//  WatchDogClientHandler
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef WATCHDOGCLIENTHANDLER_H
#define WATCHDOGCLIENTHANDLER_H

#include "ServiceInternal.h"

class WatchDogClientHandler : ServiceInternal {
public:
    //Constructor
    WatchDogClientHandler(Selector &sel, std::string hostName, int portNumber);
    ~WatchDogClientHandler();
    
    //
    
private:
    int fd;
    
};


#endif
