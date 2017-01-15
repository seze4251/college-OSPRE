//
//  CameraController.cpp
//  CameraController
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>

#include "CameraController.h"
#include "Service.h"

CameraController::CameraController(std::string hostName, int localPort, int watchDogPort) : watchDog(getSelector(), hostName, watchDogPort), accept(getSelector()), pollTime(0), hostName(hostName), localPort(localPort) {
    std::cout<< "CameraController Constructor called" << std::endl;
    setAppl(this);
    accept.registerCallback(CameraController::handleCameraControllerConnections);
    p_ID = P_CameraController;
    watchDog.p_ID = p_ID;
}

CameraController::~CameraController() {
    
}

// Connect to WatchDog
bool CameraController::open() {
    //WatchDog Service
    if (watchDog.isConnected() == false) {
        watchDog.open();
    }
    
    //Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            std::cerr << "CameraController Server Socket Failed To Open, CameraController Exiting" << std::endl;
            exit(-1);
        }
        std::cout << "CameraController Server Socket Opened" << std::endl;
    }
    
    // Other Services
    // TODO: Change Bool to something more useful
    return true;
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************

void CameraController::handleTimeout() {
    
}

void CameraController::handleCameraControllerConnections(int fd) {
    
}
