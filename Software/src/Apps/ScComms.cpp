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

ScComms::ScComms( std::string hostName, int localPort, int watchDogPort) : ServerInternal(hostName, localPort, P_ScComms), watchDogPort(watchDogPort) {
    std::cout<< " ScComms Constructor called" << std::endl;
    setAppl(this);
    watchDog = nullptr;
}

ScComms::~ScComms() {
    
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************
bool ScComms::open() {
    //Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            std::cerr << "ScComms Server Socket Failed To Open, ScComms Exiting" << std::endl;
            exit(-1);
        }
        std::cout << "ScComms Server Socket Opened" << std::endl;
    }
    
    //Connect to WatchDog
    if(connectToAppl(hostName, watchDogPort, &watchDog) == true) {
        std::cout << "ScComms: Connected to WatchDog" << std::endl;
    } else {
        std::cout << "ScComms: Failure to Connect to WatchDog" << std::endl;
    }
    
    return true;
}


void ScComms::handleTimeout() {
    this->open();
}

// *******************************
//
// Message Handler Defualt Behavior Below, Need to Implement
//
// ********************************

// Message Handlers
void ScComms::handleProccessHealthAndStatusRequest(ProccessHealthAndStatusRequest* msg, ServiceInternal* service) {
    std::cout << "WatchDogService::handleProccessHealthAndStatusRequest(): Process Health and Status Response Received" << std::endl;
    service->sendStatusResponseMessage(p_ID);
}

void ScComms::handleProccessHealthAndStatusResponse(ProccessHealthAndStatusResponse* msg, ServiceInternal* service) {
    std::cerr << "ScComms::handleProccessHealthAndStatusResponse() Not Supported for ScComms" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void ScComms::handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service) {
    std::cerr << "ScComms::handleCaptureImageRequest() Not Supported for ScComms" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void ScComms::handleDataRequest(DataRequest* msg, ServiceInternal* service) {
    std::cerr << "ScComms::handleDataRequest() Not Supported for ScComms" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void ScComms::handleEphemerisMessage(EphemerisMessage* msg, ServiceInternal* service) {
    std::cerr << "ScComms::handleEphemerisMessage() Not Supported for ScComms" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void ScComms::handleImageAdjustment(ImageAdjustment* msg, ServiceInternal* service) {
    std::cerr << "ScComms::handleImageAdjustment() Not Supported for ScComms" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void ScComms::handleImageMessage(ImageMessage* msg, ServiceInternal* service) {
    std::cerr << "ScComms::handleImageMessage() Not Supported for ScComms" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void ScComms::handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service) {
    std::cerr << "ScComms::handleOSPREStatus() Not Supported for ScComms" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void ScComms::handlePointingRequest(PointingRequest* msg, ServiceInternal* service) {
    std::cerr << "ScComms::handlePointingRequest() Not Supported for ScComms" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void ScComms::handleSolutionMessage(SolutionMessage* msg, ServiceInternal* service){
    std::cerr << "ScComms::handleSolutionMessage() Not Supported for ScComms" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}






