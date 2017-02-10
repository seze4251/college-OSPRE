//
//  External_PointingRequest.h
//  External_PointingRequest
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef EXTERNAL_POINTINGREQUEST_H
#define EXTERNAL_POINTINGREQUEST_H

#include "Message_External.h"
#include "MessageID.h"

class External_PointingRequest : public Message_External {
public:
    
    // Need to set: packetType, sequenceFlags, packetDataLength
    External_PointingRequest(unsigned int applicationProcessID) : Messege_External(applicationProcessID) {
        packetType = 1;
        sequenceFlags = 3;
        packetSequence = 0;
        packetDataLength = (8) - 1;
        iden = E_PointingRequest;
    }
    
    // Message ID
    MessageID iden;
    
    // Specific Data Members
    PointEarthMoon point;
    
};
#endif
