//
//  External_DataMessage.h
//  External_DataMessage
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef EXTERNALDATAMESSAGE_H
#define EXTERNALDATAMESSAGE_H

#include "Message_External.h"
#include "MessageID.h"

class External_DataMessage : public Message_External {
public:
    
    External_DataMessage(unsigned int applicationProcessID) :  Messege_External(applicationProcessID) {
        packetType = 0;
        sequenceFlags = 3;
        packetSequence = 0;
        packetDataLength = (8 * 12 + 5) - 1;
        iden = E_SpacecraftDataMessage;
    }
    
    // Specific Data Members
    
    // Message ID
    MessageID iden;
    
    // Ephemeris
    double ephem[3];
    
    // Quaternion
    double quat[4];
    
    // Angular Velocity
    double angularVelocity[3];
    
    // Time
    time_t satTime;
    
    // Sun Angle
    double sunAngle;
    
    // Sleep Mode
    bool sleep;
    
    };

#endif
