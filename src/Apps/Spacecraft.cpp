//
//  Spacecraft.h
//  Spacecraft
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>


#include "Spacecraft.h"

Spacecraft::Spacecraft(std::string ospreHostName, int osprePort) : pollTime(0), ospreHostName(ospreHostName), osprePort(osprePort) {
    std::cout<< " Spacecraft Constructor called" << std::endl;
    setAppl(this);
    
    // Initialize scComms
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
    
    // Free ServiceExternal
    delete scComms;
}

void Spacecraft::handleTimeout() {
    // Make sure connections are still connected
    open();
    
    /*
    // Send Timed Capture Image Requests to Camera
    time_t currentTime = time(NULL);
    
    if (currentTime > pollTime) {
        // Send Poll
        if (scComms -> isConnected()) {
            //TODO: Update Data Message
            scComms->sendExternalDataMessage(dataMessage);
            pollTime = currentTime + 1;
        }
    }
    */
}

void Spacecraft::open() {
    // Make Sure Service is not NULL
    if (scComms == nullptr) {
        scComms = new ServiceExternal(getAppl()->getSelector());
    }
    
    // Check to see if Client is already Connected
    if (scComms->isConnected() == true) {
        std::cout << "ServerExternal::openl(): Spacecraft is already connected to ScComms" << std::endl;
        return;
    } else {
        scComms->open(ospreHostName, osprePort);
    }
    
}












