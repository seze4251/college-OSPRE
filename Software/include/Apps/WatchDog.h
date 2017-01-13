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

class WatchDog : public Server {
    enum {MaxClients = 16 };
public:
    WatchDog(int localPort);
    ~WatchDog();
    static void handleWatchDogConnections(int i);
    bool open();
    
private:
    Acceptor accept;
    WatchDogClientHandler *client[MaxClients];
    
};

#endif
