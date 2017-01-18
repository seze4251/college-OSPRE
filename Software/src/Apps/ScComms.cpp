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

ScComms::ScComms( std::string hostName, int localPort, int watchDogPort) : watchDog(getSelector(), hostName, watchDogPort), hostName(hostName), localPort(localPort) {
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

// *******************************
//
// Message Handler Defualt Behavior Below, Need to Implement
//
// ********************************

// Message Handlers
void ScComms::handleProccessHealthAndStatusRequest(ProccessHealthAndStatusRequest* msg) {
    std::cout << "ScComms::handleProccessHealthAndStatusRequest():  Not Supported for ScComms" << std::endl;
    
}

void ScComms::handleProccessHealthAndStatusResponse(ProccessHealthAndStatusResponse* msg) {
    std::cerr << "ScComms::handleProccessHealthAndStatusResponse() Not Supported for ScComms" << std::endl;
}

void ScComms::handleCaptureImageRequest(CaptureImageRequest* msg) {
    std::cerr << "ScComms::handleCaptureImageRequest() Not Supported for ScComms" << std::endl;
}

void ScComms::handleDataRequest(DataRequest* msg) {
    std::cerr << "ScComms::handleDataRequest() Not Supported for ScComms" << std::endl;
}
void ScComms::handleEphemerisMessage(EphemerisMessage* msg) {
    std::cerr << "ScComms::handleEphemerisMessage() Not Supported for ScComms" << std::endl;
}
void ScComms::handleImageAdjustment(ImageAdjustment* msg) {
    std::cerr << "ScComms::handleImageAdjustment() Not Supported for ScComms" << std::endl;
}
void ScComms::handleImageMessage(ImageMessage* msg) {
    std::cerr << "ScComms::handleImageMessage() Not Supported for ScComms" << std::endl;
}
void ScComms::handleOSPREStatus(OSPREStatus* msg) {
    std::cerr << "ScComms::handleOSPREStatus() Not Supported for ScComms" << std::endl;
}
void ScComms::handlePointingRequest(PointingRequest* msg) {
    std::cerr << "ScComms::handlePointingRequest() Not Supported for ScComms" << std::endl;
}

void ScComms::handleSolutionMessage(SolutionMessage* msg){
    std::cerr << "ScComms::handleSolutionMessage() Not Supported for ScComms" << std::endl;
}






