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

ServiceExternal* Spacecraft::scComms;

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
            
            // BS data members to start
            double ephem[3] {4, 5, 6};
            double quat[4] {0.25, 0.55, 0.75, 1.5};
            double angularVelocity[3] {1, 2, 3};
            time_t satTime = time(0);
            double sunAngle = 5;
            bool sleep = false;
            
            // Update Data Message
            dataMessage->update(ephem, quat, angularVelocity, satTime, sunAngle, sleep);
           // dataMessage->print();
            scComms->sendMessage(dataMessage);
            pollTime = currentTime + 1;
        }
    }
    
}

void Spacecraft::open() {
    // Set Timeout to half a second
    setTimeoutTime(0, 500000);
    
    // Make Sure Service is not NULL
    if (scComms == nullptr) {
        scComms = new ServiceExternal(getAppl()->getSelector());
    }
    
    // Check to see if Client is already Connected
    if (scComms->isConnected() == true) {
       // std::cout << "ServerExternal::openl(): Spacecraft is already connected to ScComms" << std::endl;
        return;
    } else {
        std::cout << "Spacecraft Lost connection to S/C Comms, Attempting to reconnect" << std::endl;
        scComms->open(ospreHostName, osprePort);
        scComms->registerCallback(handleExternalMessage);
    }
    
}

void Spacecraft::handleExternalMessage(Message_External* msg, ServiceExternal* service) {
    switch (msg->iden) {
        case E_OSPREStatus:
            std::cout << "OSPRE Status Recivied" << std::endl;
            ((Spacecraft*) getAppl())->handleExternalOSPREStatusMessage((External_OSPREStatus*) msg, service);
            break;
            
        case E_PointingRequest:
            std::cout << "Pointing Request Recivied" << std::endl;
            ((Spacecraft*) getAppl())->handleExternalPointingMessage((External_PointingRequest*) msg, service);
            break;
            
        case E_SolutionMessage:
            std::cout << "Solution Message Recivied" << std::endl;
            ((Spacecraft*) getAppl())->handleExternalSolutionMessage((External_SolutionMessage*) msg, service);
            break;
            
        case E_SpacecraftDataMessage:
            std::cout << "Spacecraft Data message Recivied" << std::endl;
            ((Spacecraft*) getAppl())->handleExternalDataMessage((External_DataMessage*) msg, service);
            break;
            
        default:
            std::cerr << "\n\nScComms::handleExternalMessage(): Unknown Message Type Recived: " << msg->iden << std::endl;
            std::cerr << "Closing Connection\n\n" << std::endl;
            service->closeConnection();
    }
}


// *******************************
//
// Message Handlers: Supported on Spacecraft
//  External Messages
//
// ********************************


void Spacecraft::handleExternalOSPREStatusMessage(External_OSPREStatus* msg, ServiceExternal* service) {
    msg->print();
}

void Spacecraft::handleExternalPointingMessage(External_PointingRequest* msg, ServiceExternal* service) {
    msg->print();
}

void Spacecraft::handleExternalSolutionMessage(External_SolutionMessage* msg, ServiceExternal* service) {
    msg->print();
    
}

void Spacecraft::handleExternalDataMessage(External_DataMessage* msg, ServiceExternal* service) {
    std::cout << "\n\nData Message Recived: Invalid Message, Closing Connection\n\n" << std::endl;
    scComms->closeConnection();
}
















