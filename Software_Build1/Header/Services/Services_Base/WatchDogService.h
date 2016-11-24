//
//  WatchDogService.h
//  WatchDogService
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef WATCHDOGSERVICE_H
#define WATCHDOGSERVICE_H

#include "ServiceInternal.h"

class WatchDogService : public ServiceInternal {
public:
    WatchDogService(std::string hostName, int portNumber, Selector &) : ServiceInternal();
    ~WatchDogService();
    
    bool isConnected() { return fd != -1 ? true : false; }
    void close();
    
    void handleRead();
    void handleWrite();
    
private:
    std::string hostName;
    int portNumber;
    socket fd;
    Builder build;
    Parser parse;
    ByteBuffer readbuf;
    ByteBuffer writebuf;
    


};

#endif
