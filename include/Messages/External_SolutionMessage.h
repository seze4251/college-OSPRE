//
//  External_SolutionMessage.h
//  External_SolutionMessage
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef EXTERNAL_SOLUTIONMESSAGE_H
#define EXTERNAL_SOLUTIONMESSAGE_H

#include "Message_External.h"

class External_SolutionMessage : public Message_External {
public:
    
    // Need to set: packetType, sequenceFlags, packetDataLength
    External_SolutionMessage(unsigned int applicationProcessID) : Message_External(applicationProcessID, E_SolutionMessage) {
        header.header_struct.packetType = 0;
        header.header_struct.sequenceFlags = 3;
        header.header_struct.packetSequence = 0;
        header.header_struct.packetDataLength = (8 * 13 + 4)  - 1;
    }
    
    // Specific Data Members
    double position[3];
    double positionError[3];
    double velocity[3];
    double velocityError[3];
    double earthScMoonAngle;

};

#endif
