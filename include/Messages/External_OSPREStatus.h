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
        header.header_struct.packetDataLength = (4 * error.size() + 4) - 1;
    }
    
    // Update Message
    void update(std::vector<ProcessError> error) {
        this->error = error;
    }
    
    // Print Message
    void print() {
        printHeader();
        for (auto i = error.begin(); i != error.end(); ++i)
            printProcessError(*i);
    }
    
    //Specific Data Members
    std::vector<ProcessError> error;

};

#endif
