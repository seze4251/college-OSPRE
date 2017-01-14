//
//  WatchDogService.cpp
//  WatchDogService
//
//  Created by Seth on 11/27/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include "WatchDogService.h"
#include <unistd.h>
#include <iostream>

WatchDogService::WatchDogService(Selector &sel, std::string hostName, int portNumber) : ServiceInternal(sel), hostName(hostName), portNumber(portNumber) {
    std::cout << "WatchDogService Constructor called" << std::endl;
}

WatchDogService::~WatchDogService() {
    
}

bool WatchDogService::open() {
    // Connect to WatchDog
    fd = Service::connectToServer(hostName.c_str(), portNumber);
    return true;
}


void WatchDogService::close() {
    std::cout << "WatchDogService close() " << std::endl;
    if (fd != -1) {
        ::close(fd);
        fd = -1;
    }
    readbuf.clear();
    writebuf.clear();
}



