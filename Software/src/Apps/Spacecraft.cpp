//
//  Spacecraft.h
//  Spacecraft
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>


#include "Spacecraft.h"

Spacecraft::Spacecraft(std::string hostName, int localPort) : hostName(hostName), localPort(localPort), pollTime(0) {
    std::cout<< " Spacecraft Constructor called" << std::endl;
    setAppl(this);
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

void Spacecraft::open() {
    
}
