//
//  ScComms.cpp
//  ScComms
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include "ScComms.h"
#include "Service.h"
#include <iostream>

ScComms::ScComms( std::string hostName, int portNumber) : watchDog(getSelector(), hostName, portNumber), accept(getSelector()) {
    setAppl(this);
    std::cout<< " ScComms Constructor called" << std::endl;
    
}

ScComms::~ScComms() {
    
}

// Connect to Camera Controller
// Connect to WatchDog
// Connect to GNC
// Accept S/C
bool ScComms::open(std::string hostName, int portNumber, int localPort) {
    
    //WatchDog Service
    if (watchDog.isConnected() == false) {
        watchDog.open();
    }
    
    //Acceptor
    if (accept.isConnected() == false) {
        accept.open(hostName, localPort);
    }
        
    
    
    // Other Services
    
    return true;
}

void getStatus() {
    
}


