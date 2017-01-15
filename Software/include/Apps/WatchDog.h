//
//  WatchDog.h
//  WatchDog
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <string>

#include "Server.h"
#include "Acceptor.h"
#include "WatchDogClientHandler.h"
#include "ProcessID.h"

class WatchDog : public Server {
    public:
    enum {MaxClients = 16 };
    WatchDog(std::string hostName, int serverPort);
    ~WatchDog();
    static void handleWatchDogConnections(int fd);
    bool open();
    virtual void handleTimeout();
    
    ProcessID p_ID;
    
private:
    Acceptor accept;
    static WatchDogClientHandler *client[MaxClients];
    static int clientCount;
    time_t pollTime;
    
    //Acceptor Port and Host
    std::string hostName;
    int localPort;
};

#endif
