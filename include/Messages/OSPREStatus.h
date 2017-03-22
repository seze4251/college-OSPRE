//
//  OSPREStatus.h
//  OSPREStatus
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef OSPRESTATUS_H
#define OSPRESTATUS_H

#include <vector>
#include <iostream>

#include "Message.h"
#include "ProcessError.h"
#include "ProcessID.h"

class OSPREStatus : public Message {
public:
    OSPREStatus() : Message(getMessageID(), time(0)) {
        numProblemProcesses = 0;
    }
    MessageID getMessageID() { return I_OSPREStatus; }
    
    // Specific Data Members
    void update(ProcessError p_error, ProcessID PID) {
        this->timeStamp = time(0);
        pID.push_back(PID);
        error.push_back(p_error);
        numProblemProcesses = error.size();
    }
    
    void clear() {
        numProblemProcesses = 0;
        pID.clear();
        error.clear();
    }
    
    // Print Message
    void print(FILE* logFile) {
        fprintf(logFile, "Printing OSPRE Status Message\n");
        printMessageHeader(logFile);
        printProcessError(totalHealth, logFile);
        fprintf(logFile, "Number of Processes with Errors = %d\n", numProblemProcesses);
        
        std::vector<ProcessID>::iterator itPID;
        std::vector<ProcessError>::iterator itPError;
        
        for (itPID = pID.begin(), itPError = error.begin(); itPError != error.end(); itPID++, itPError++ ) {
            printProcessID(*itPID, logFile);
            printProcessError(*itPError, logFile);
        }
    }
    
    //OSPRE System Health
    ProcessError totalHealth;
    
    //OSPRE Process Health
    int numProblemProcesses;
    std::vector<ProcessID> pID;
    std::vector<ProcessError> error;
};


#endif
