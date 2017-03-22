//
//  External_OSPREStatus.h
//  External_OSPREStatus
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#ifndef MESSAGES_H
#define MESSAGES_H

#include <vector>

#include "Message_External.h"
#include "ProcessError.h"
#include "OSPREStatus.h"

class External_OSPREStatus : public Message_External {
public:
    // Need to set: packetType, sequenceFlags, packetDataLength
    External_OSPREStatus(unsigned int applicationProcessID) : Message_External(applicationProcessID, E_OSPREStatus) {
        header.header_struct.packetType = 0;
        header.header_struct.sequenceFlags = 3;
        header.header_struct.packetSequence = 0;
        header.header_struct.packetDataLength = 0;
    }
    
    // Update Message Length
    void updatePacketDataLength() {
        header.header_struct.packetDataLength = (2 * pID.size() + 2 * error.size() + 3 *sizeof(int)) - 1;
    }
    
    // Update Message
    void update(OSPREStatus* msg) {
        totalHealth = msg->totalHealth;
        numProblemProcesses = msg->numProblemProcesses;
        pID = msg->pID;
        error = msg->error;
    }
    
    // Print Message
    void print(FILE* logFile) {
        printHeader(FILE* logFile);
        printProcessError(totalHealth);
        std::cout << "Number of Processes with Errors: " << numProblemProcesses << std::endl;
        
        std::vector<ProcessID>::iterator itPID;
        std::vector<ProcessError>::iterator itPError;

        for (itPID = pID.begin(), itPError = error.begin(); itPError != error.end(); itPID++, itPError++ ) {
            printProcessID(*itPID);
            printProcessError(*itPError);
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
