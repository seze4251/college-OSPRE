//
//  WatchDog.cpp
//  WatchDog
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include "WatchDog.h"
#include <iostream>
#include <unistd.h>


int WatchDog::clientCount;
WatchDogClientHandler* WatchDog::client[WatchDog::MaxClients];

WatchDog::WatchDog(int localPort) : accept(getSelector()) {
    setAppl(this);
    std::cout<< " WatchDog Constructor called" << std::endl;
    accept.registerCallback(WatchDog::handleWatchDogConnections);
    clientCount = 0;
    for (int i = 0; i < MaxClients; i++) {
        client[i] = nullptr;
    }
}

WatchDog::~WatchDog() {
    
}

// Connect to no processes
// Accept ScComms, ImageProcessor, GNC, CameraController
bool WatchDog::open(std::string hostname, int portNumber){
    if(accept.open(hostname, portNumber) == false) {
        
        std::cerr << "Server Socket Failed To Open, WatchDog Exiting" << std::endl;
        return false;
    }
    std::cout << "Server Socket Opened" << std::endl;
    return true;
}

void WatchDog::handleWatchDogConnections(int fd) {
    // Check to make sure max client count is not exceeded
    if (clientCount >= MaxClients) {
        std::cout << "handleWatchDogConnections closing Connection: Too Many Connections" << std::endl;
        ::close(fd);
        return;
    }
    
    client[clientCount] = new WatchDogClientHandler(appl->getSelector(), fd);
    clientCount++;
}


