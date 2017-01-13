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

//accept(getSelector(), NULL, localPort, WatchDog::handleWatchDogConnections)
WatchDog::WatchDog(int localPort) : accept(getSelector()) {
    std::cout<< " WatchDog Constructor called" << std::endl;
    accept.registerCallback(WatchDog::handleWatchDogConnections);
}

WatchDog::~WatchDog() {
    
}


bool WatchDog::open(){
       if(accept.open("localhost", 5000) == false) {
        
        std::cerr << "Server Socket Failed To Open, WatchDog Exiting" << std::endl;
        exit(-1);
    }
    std::cout << "Server Socket Opened" << std::endl;
    return true;
}

void WatchDog::handleWatchDogConnections(int i) {
    std::cout << "handleWatchDogConnections closing Connection\n";
    close(i);
}
