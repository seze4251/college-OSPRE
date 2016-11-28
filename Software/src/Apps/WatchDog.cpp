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
WatchDog::WatchDog(int localPort) /* : accept(getSelector(), NULL, localPort, WatchDog::handleWatchDogConnections)*/ {
    std::cout<< "Made it to WatchDog Constructor\n";
    
}

WatchDog::~WatchDog() {
    
}

void WatchDog::handleWatchDogConnections(int i) {
    std::cout << "handleWatchDogConnections closing Connection\n";
    close(i);
}
