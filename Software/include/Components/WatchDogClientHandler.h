//
//  WatchDogClientHandler.h
//  WatchDogClientHandler
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

// GOES INTO WATCHDOG

#ifndef WATCHDOGCLIENTHANDLER_H
#define WATCHDOGCLIENTHANDLER_H

#include "ServiceInternal.h"

class WatchDogClientHandler : ServiceInternal {
public:
    //Constructor
    WatchDogClientHandler(Selector &sel, int fd);
    ~WatchDogClientHandler();
    bool isConnected() { return fd != -1 ? true : false; }
    
    void sendStatusRequestMessage();
    
private:
};


#endif
