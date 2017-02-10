//
//  External_OSPREStatus.h
//  External_OSPREStatus
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#ifndef MESSAGES_H
#define MESSAGES_H

#include "Message_External.h"
#include "MessageID.h"

class External_OSPREStatus : public Message_External {
public:
    
    // Need to set: packetType, sequenceFlags, packetDataLength
    External_OSPREStatus(unsigned int applicationProcessID) : Messege_External(applicationProcessID) {
        packetType = 0;
        sequenceFlags = 3;
        packetSequence = 0;
        packetDataLength = 0;
        iden = E_OSPREStatus;
    }
    
    void updatePacketDataLength() {
        packetDataLength = (4 * error.size() + 4) - 1;
    }
    
    // Message ID
    MessageID iden;
    
    //Specific Data Members
    std::vector<ProcessError> error;

};

#endif
