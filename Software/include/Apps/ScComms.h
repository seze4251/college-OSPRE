//
//  ScComms.h
//  ScComms
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SCCOMMS_H
#define SCCOMMS_H

#include <string>

#include "Server.h"
#include "WatchDogService.h"
#include "Acceptor.h"
#include "ProcessID.h"


class ScComms : public Server {
public:
    ScComms(std::string hostName, int localPort, int watchDogPort);
    ~ScComms();
    bool open();
    virtual void handleTimeout();
    static void handleScCommsConnections(int fd);
    
    ProcessID p_ID;
private:
    Acceptor accept;
    WatchDogService watchDog;
    
    //Acceptor Port and Host
    std::string hostName;
    int localPort;
};

#endif
