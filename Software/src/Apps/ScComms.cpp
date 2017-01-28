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

ScComms::ScComms( std::string hostName, int localPort, int externalPort) : ServerInternal(hostName, localPort, P_ScComms), external_accept(getSelector()), hostName(hostName), localPort(localPort), externalPort(externalPort), pollTime(0) {
    std::cout<< " ScComms Constructor called" << std::endl;
    setAppl(this);
    external_accept.registerCallback(handleExternalConnection);
    spacecraft = nullptr;
}

ScComms::~ScComms() {
    
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************
void ScComms::open() {
    //Internal Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            std::cerr << "ScComms Internal Server Socket Failed To Open, ScComms Exiting" << std::endl;
            exit(-1);
        }
        std::cout << "ScComms Internal Server Socket Opened" << std::endl;
    }
    
    // External Acceptor
    if (external_accept.isConnected() == false) {
        if(external_accept.open(hostName, externalPort) == false) {
            std::cerr << "ScComms External Server Socket Failed To Open, ScComms Exiting" << std::endl;
            exit(-1);
        }
        std::cout << "ScComms External Server Socket Opened" << std::endl;
    }

}

/*
 1. Need to check that all connections are still open
 */
void ScComms::handleTimeout() {
    this->open();
}

// *******************************
//
// Application Functionality:
//
// ********************************
// TODO: Seth to complete
void handleExternalConnection(int fd) {
    
}


// *******************************
//
// Message Handlers: Supported on ScComms
//
// ********************************

/*
 Determine Process Status
 Send Status to WatchDog
 */
void ScComms::handleProcessHealthAndStatusRequest(ProcessHealthAndStatusRequest* msg, ServiceInternal* service) {
    std::cout << "WatchDogService::handleProcessHealthAndStatusRequest(): Process Health and Status Response Received" << std::endl;
    service->sendStatusResponseMessage(status);
    // Clear Status
    status.clear();
}

/*
 1. Foward Data Message to all Subscribers? or everybody?
 */
void ScComms::handleDataMessage(DataMessage* msg, ServiceInternal* service) {
    std::cerr << "ScComms::handleDataMessage() Not Supported for ScComms" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

/*
 1. Send OSPRE Status to S/C
 */
void ScComms::handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service) {
    std::cerr << "ScComms::handleOSPREStatus() Not Supported for ScComms" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

/*
 1. Send Pointing Request to S/C
 */
void ScComms::handlePointingRequest(PointingRequest* msg, ServiceInternal* service) {
    std::cerr << "ScComms::handlePointingRequest() Not Supported for ScComms" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

/*
 1. Send Solution Message to S/C
 */
void ScComms::handleSolutionMessage(SolutionMessage* msg, ServiceInternal* service){
    std::cerr << "ScComms::handleSolutionMessage() Not Supported for ScComms" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}



// *******************************
//
// Message Handlers: Not Supported on ScComms
//
// ********************************
void ScComms::handleProcessHealthAndStatusResponse(ProcessHealthAndStatusResponse* msg, ServiceInternal* service) {
    std::cerr << "ScComms::handleProcessHealthAndStatusResponse() Not Supported for ScComms" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void ScComms::handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service) {
    std::cerr << "ScComms::handleCaptureImageRequest() Not Supported for ScComms" << std::endl;
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

void ScComms::handleProcessedImageMessage(ProcessedImageMessage* msg, ServiceInternal* service) {
    std::cerr << "ScComms::handleProcessedImageMessage() Not Supported for ScComms" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}









