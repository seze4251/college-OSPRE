//
//  ScComms.cpp
//  ScComms
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>

#include "ScComms.h"
#include "Service.h"

ScComms::ScComms( std::string hostName, int localPort, int watchDogPort) : watchDog(getSelector(), hostName, watchDogPort), accept(getSelector()), hostName(hostName), localPort(localPort) {
    setAppl(this);
    accept.registerCallback(ScComms::handleScCommsConnections);
    std::cout<< " ScComms Constructor called" << std::endl;
    p_ID = P_ScComms;
    watchDog.p_ID = p_ID;
}

ScComms::~ScComms() {
    
}

// Connect to Camera Controller
// Connect to WatchDog
// Connect to GNC
// Accept S/C
bool ScComms::open() {
    //WatchDog Service
    if (watchDog.isConnected() == false) {
        watchDog.open();
    }
 
    //Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            std::cerr << "ScComms Server Socket Failed To Open, ScComms Exiting" << std::endl;
            exit(-1);
        }
        std::cout << "ScComms Server Socket Opened" << std::endl;
    }
    
    // Other Services
    // TODO: Change Bool to something more useful
    return true;
}


void ScComms::handleTimeout() {
    if (watchDog.isConnected() == false) {
        watchDog.open();
    }
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************

void ScComms::handleScCommsConnections(int fd) {
    
}





