//
//  External_DataMessage.h
//  External_DataMessage
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef EXTERNALDATAMESSAGE_H
#define EXTERNALDATAMESSAGE_H

#include <ctime>

#include "Message_External.h"

class External_DataMessage : public Message_External {
public:
    
    External_DataMessage(unsigned int applicationProcessID) :  Message_External(applicationProcessID, E_SpacecraftDataMessage) {
        header.header_struct.packetType = 0;
        header.header_struct.sequenceFlags = 3;
        header.header_struct.packetSequence = 0;
        header.header_struct.packetDataLength = (8 * 12 + 5) - 1;
    }
    
    // Specific Data Members
    
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
