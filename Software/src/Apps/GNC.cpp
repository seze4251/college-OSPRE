//
//  GNC.cpp
//  GNC
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>

#include "GNC.h"
#include "Service.h"

GNC::GNC(std::string hostName, int watchDogPort) : watchDog(getSelector(), hostName, watchDogPort), pollTime(0) {
    std::cout<< "GNC Constructor called" << std::endl;
    setAppl(this);
    p_ID = P_GNC;
    watchDog.p_ID = p_ID;
}

GNC::~GNC() {
    
}

// Connect to Image Processor
// Connect to WatchDog
// Connect to ScComms

bool GNC::open() {
    if (watchDog.isConnected() == false) {
        watchDog.open();
    }
    
    if (watchDog.isConnected() == true) {
        return true;
    }else {
        return false;
    }
}


// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************


void GNC::handleTimeout() {
    
}
