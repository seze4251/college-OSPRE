//
//  Spacecraft.h
//  Spacecraft
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>

#include "Spacecraft.h"
#include "Service.h"

Spacecraft::Spacecraft(std::string hostName, int localPort) : pollTime(0), hostName(hostName), localPort(localPort) {
    std::cout<< " Spacecraft Constructor called" << std::endl;
    setAppl(this);
    p_ID = P_WatchDog;
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************


Spacecraft::~Spacecraft() {
    
}

// Connect to ScComms

void Spacecraft::handleTimeout() {
    
}

bool Spacecraft::open() {
    return true;
}
