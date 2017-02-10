//
//  Spacecraft.h
//  Spacecraft
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>

#include "Spacecraft.h"

#define Spacecraft_APPL_ID 2

Spacecraft::Spacecraft(std::string ospreHostName, int osprePort) : pollTime(0), ospreHostName(ospreHostName), osprePort(osprePort) {
    std::cout<< " Spacecraft Constructor called" << std::endl;
    setAppl(this);
    
    // Initialize scComms
    scComms = nullptr;
    
    // Allocate Memory for Messages to Send
    dataMessage = new External_DataMessage(Spacecraft_APPL_ID);
}

Spacecraft::~Spacecraft() {
    //Free Messages from Memory
    delete dataMessage;
    
    // Free ServiceExternal
    delete scComms;
}

void Spacecraft::handleTimeout() {
    // Make sure connections are still connected
    open();
    
    // Send Timed Capture Image Requests to Camera
    time_t currentTime = time(NULL);
    
    if (currentTime > pollTime) {
        // Send Poll
        if (scComms -> isConnected()) {
            //TODO: Update Data Message
            scComms->sendMessage(dataMessage);
            pollTime = currentTime + 1;
        }
    }
    
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

void Spacecraft::handleExternalMessage(Message_External* msg, ServiceExternal* service) {
    switch (msg->iden) {
        case E_OSPREStatus:
            ((Spacecraft*) getAppl())->handleExternalOSPREStatusMessage((External_OSPREStatus*) msg, service);
            break;
            
        case E_PointingRequest:
            ((Spacecraft*) getAppl())->handleExternalPointingMessage((External_PointingRequest*) msg, service);
            break;
            
        case E_SolutionMessage:
            ((Spacecraft*) getAppl())->handleExternalSolutionMessage((External_SolutionMessage*) msg, service);
            break;
            
        case E_SpacecraftDataMessage:
            ((Spacecraft*) getAppl())->handleExternalDataMessage((External_DataMessage*) msg, service);
            break;
            
        default:
            std::cerr << "ScComms::handleExternalMessage(): Unknown Message Type Recived: " << msg->iden << std::endl;
            std::cerr << "Closing Connection" << std::endl;
            service->closeConnection();
    }
}


// *******************************
//
// Message Handlers: Supported on Spacecraft
//  External Messages
//
// ********************************


void Spacecraft::handleExternalOSPREStatusMessage(External_OSPREStatus* msg, ServiceExternal* service)g {
    
}

void Spacecraft::handleExternalPointingMessage(External_PointingRequest* msg, ServiceExternal* service) {
    
}

void Spacecraft::handleExternalSolutionMessage(External_SolutionMessage* msg, ServiceExternal* service) {
    
}

void Spacecraft::handleExternalDataMessage(External_DataMessage* msg, ServiceExternal* service) {
    
}
















