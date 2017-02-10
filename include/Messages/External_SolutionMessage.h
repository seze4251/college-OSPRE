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
#include "MessageID.h"

class External_SolutionMessage : public Message_External {
public:
    
    // Need to set: packetType, sequenceFlags, packetDataLength
    External_SolutionMessage(unsigned int applicationProcessID) : Messege_External(applicationProcessID) {
        packetType = 0;
        sequenceFlags = 3;
        packetSequence = 0;
        packetDataLength = (8 * 13 + 4)  - 1;
        iden = E_SolutionMessage;
    }
    
    // Message ID
    MessageID iden;
    
    // Specific Data Members
    double position[3];
    double positionError[3];
    double velocity[3];
    double velocityError[3];
    double earthScMoonAngle;

};

#endif
