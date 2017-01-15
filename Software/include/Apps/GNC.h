//
//  GNC.h
//  GNC
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef GNC_H
#define GNC_H

#include <string>

#include "Server.h"
#include "WatchDogService.h"
#include "ProcessID.h"

class GNC : public Server {
public:
    GNC(std::string hostName, int watchDogPort);
    ~GNC();
    virtual void handleTimeout();
    bool open();
    
    ProcessID p_ID;
private:
    time_t pollTime;
    WatchDogService watchDog;
};

#endif

