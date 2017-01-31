//
//  Spacecraft.h
//  Spacecraft
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>


#include "Spacecraft.h"

Spacecraft::Spacecraft(std::string hostName, int localPort) : pollTime(0) {
    std::cout<< " Spacecraft Constructor called" << std::endl;
    setAppl(this);
    scComms = nullptr;
    
    // Allocate Memory for Messages to Send
    dataMessage = new External_DataMessage();
    
}


// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************


Spacecraft::~Spacecraft() {
    //Free Messages from Memory
    delete dataMessage;
}

void Spacecraft::handleTimeout() {
    
}

void Spacecraft::open() {
    
}












