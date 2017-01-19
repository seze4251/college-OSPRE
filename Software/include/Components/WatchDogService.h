//
//  WatchDogService.h
//  WatchDogService
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

// GOES INTO CLIENTS

#ifndef WATCHDOGSERVICE_H
#define WATCHDOGSERVICE_H

#include "ServiceInternal.h"
#include "ProcessID.h"

class WatchDogService : public ServiceInternal {
public:
    WatchDogService(Selector &sel, std::string hostName, int portNumber);
    ~WatchDogService();
    bool open();
    
    void sendStatusResponseMessage();
    
    // Added Process ID
    ProcessID p_ID;
    
private:
    // Hostname and PortNumber for Server Socket
    std::string hostName;
    int portNumber;
};

#endif
