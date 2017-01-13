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

class WatchDogService : public ServiceInternal {
public:
    WatchDogService(Selector &sel, std::string hostName, int portNumber);
    ~WatchDogService();
    bool open();
    bool isConnected() { return fd != -1 ? true : false; }
    void close();
    
    void handleRead();
    void handleWrite();
    
private:
    int fd;
    std::string hostName;
    int portNumber;
};

#endif
