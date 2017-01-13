//
//  ScComms.h
//  ScComms
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SCCOMMS_H
#define SCCOMMS_H

#include "Server.h"
#include "ErrorCode.h"
#include "WatchDogService.h"
#include "Acceptor.h"
#include <string>

class ScComms : public Server {
public:
    ScComms(std::string hostName, int portNumber);
    ~ScComms();
    bool open(std::string hostName, int portNumber, int localPort);
    
private:
    int fd;
    Acceptor accept;
    WatchDogService watchDog;
};

#endif
