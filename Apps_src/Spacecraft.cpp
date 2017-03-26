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

Spacecraft::Spacecraft(std::string ospreHostName, int osprePort) : scDataReader(Spacecraft_APPL_ID), pollTime(0), ospreHostName(ospreHostName), osprePort(osprePort) {
    setAppl(this);
    
    // Initialize scComms
    scComms = nullptr;
    
    logFile = nullptr;
}

Spacecraft::~Spacecraft() {
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
    
    // Read in OSPRE CONFIG File
    readOSPREServerConfigFile();
    fprintf(logFile, "File Input: Read OSPRE Config File\n");
    
    // Read in Spacecraft DataFile
    scDataReader.readDataFile("OSPRE_Test_DIR/Test_Data/Satellite_Data.txt");
    fprintf(logFile, "File Input: Read Spacecraft Data File\n");
    
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
        if (scComms->isConnected() == true) {
            fprintf(logFile, "Connection: Connected to ScComms\n");
        } else {
            fprintf(logFile, "Error: Unable to Connect to ScComms\n");
        }
    }
    
    // Send Timed Data Messages to OSPRE
    time_t currentTime = time(NULL);
    
    if (currentTime > pollTime) {
        // Send Poll
        if (scComms -> isConnected()) {
            dataMessage = scDataReader.getNextDataMessage();
            dataMessage->sleep =  false;
            
            fprintf(logFile, "Sent Message: ExternalDataMessage to ScComms\n");
            scComms->sendMessage(dataMessage);
            pollTime = currentTime + 1;
        }
    }
    flushLog();
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
    msg->print(logFile);
}

void Spacecraft::handleExternalPointingMessage(External_PointingRequest* msg, ServiceExternal* service) {
    fprintf(logFile, "Received Message: ExternalPointing Message from ScComms\n");
    msg->print(logFile);
}

void Spacecraft::handleExternalSolutionMessage(External_SolutionMessage* msg, ServiceExternal* service) {
    fprintf(logFile, "Received Message: ExternalSolution Message from ScComms\n");
    msg->print(logFile);
    
}

void Spacecraft::handleExternalDataMessage(External_DataMessage* msg, ServiceExternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: ExternalDataMessage, Closing Connection\n");
    scComms->closeConnection();
}







