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


class WatchDog : public Server {
public:
    WatchDog(int localPort);
    ~WatchDog();
    
private:
    
};

#endif
