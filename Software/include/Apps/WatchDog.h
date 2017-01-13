//
//  WatchDog.h
//  WatchDog
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "Server.h"
#include "Acceptor.h"
#include "WatchDogClientHandler.h"
#include <string>

class WatchDog : public Server {
    public:
    enum {MaxClients = 16 };
    WatchDog(int localPort);
    ~WatchDog();
    static void handleWatchDogConnections(int fd);
    bool open(std::string hostname, int portNumber);
    
private:
    Acceptor accept;
    static WatchDogClientHandler *client[MaxClients];
    static int clientCount;
};

#endif
