//
//  Spacecraft.h
//  Spacecraft
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>
#include <stdio.h>

#include "Spacecraft.h"

#define Spacecraft_APPL_ID 2

ServiceExternal* Spacecraft::scComms;

Spacecraft::Spacecraft(std::string ospreHostName, int osprePort) : pollTime(0), ospreHostName(ospreHostName), osprePort(osprePort) {
    setAppl(this);
    
    // Initialize scComms
    scComms = nullptr;
    
    // Allocate Memory for Messages to Send
    dataMessage = new External_DataMessage(Spacecraft_APPL_ID);
    
    logFile = nullptr;
}

Spacecraft::~Spacecraft() {
    //Free Messages from Memory
    delete dataMessage;
    
    // Free ServiceExternal
    if (scComms != nullptr) {
        delete scComms;
    }
    
    // Close Log File
    if (logFile)
        fclose(logFile);
}

void Spacecraft::open() {
    // Create File Name
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    
    rawtime = time(0);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80,"./log/SpacecraftLog_%d-%m-%Y.log",timeinfo);
    
    // Open Log File
    logFile = fopen(buffer, "a+");
    
    // Log Application Starting
    fprintf(logFile, "Spacecraft Application Started, Time = %ld\n", time(0));
    
    // Set Timeout to half a second
    setTimeoutTime(0, 500000);
    
    // Make Sure Service is not NULL
    if (scComms == nullptr) {
        scComms = new ServiceExternal(getAppl()->getSelector());
    }
    
    // Check to see if Client is already Connected
    scComms->open(ospreHostName, osprePort);
    scComms->registerCallback(handleExternalMessage);
    if (scComms->isConnected() == false) {
        fprintf(logFile, "Connection: Connected to ScComms\n");
    } else {
        fprintf(logFile, "Error: Unable to Connect to ScComms\n");
    }
    
}

void Spacecraft::handleTimeout() {
    // Check to see if Client is already Connected
    if (scComms->isConnected() == false) {
        scComms->open(ospreHostName, osprePort);
        scComms->registerCallback(handleExternalMessage);
        if (scComms->isConnected() == false) {
            fprintf(logFile, "Connection: Connected to ScComms\n");
        } else {
            fprintf(logFile, "Error: Unable to Connect to ScComms\n");
        }
    }
    
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
            fprintf(logFile, "Sent Message: ExternalDataMessage to ScComms\n");
            scComms->sendMessage(dataMessage);
            pollTime = currentTime + 1;
        }
    }
    
}

FILE* Spacecraft::getLogFileID() {
    return logFile;
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
            service->closeConnection();
            throw "Error: Unexpected Message Type Recieved, Closing Client Connection";
    }
}


// *******************************
//
// Message Handlers: Supported on Spacecraft
//  External Messages
//
// ********************************


void Spacecraft::handleExternalOSPREStatusMessage(External_OSPREStatus* msg, ServiceExternal* service) {
    fprintf(logFile, "Received Message: ExternalOSPREStatus Message from ScComms\n");
    //msg->print();
}

void Spacecraft::handleExternalPointingMessage(External_PointingRequest* msg, ServiceExternal* service) {
    fprintf(logFile, "Received Message: ExternalPointing Message from ScComms\n");
    // msg->print();
}

void Spacecraft::handleExternalSolutionMessage(External_SolutionMessage* msg, ServiceExternal* service) {
    fprintf(logFile, "Received Message: ExternalSolution Message from ScComms\n");
    //msg->print();
    
}

void Spacecraft::handleExternalDataMessage(External_DataMessage* msg, ServiceExternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: ExternalDataMessage, Closing Connection\n");
    scComms->closeConnection();
}
















