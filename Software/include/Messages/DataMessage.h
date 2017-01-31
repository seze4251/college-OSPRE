//
//  DataMessage.h
//  DataMessage
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef DATAMESSAGE_H
#define DATAMESSAGE_H

#include <vector>

#include "Message.h"

// Not quite sure how ephemris is going to be passed to us!
class DataMessage : public Message {
public:
    DataMessage() : Message(getMessageID(), time(0)) {}
    
    MessageID getMessageID() { return I_DataMessage; }
    
    void update(std::vector<long> ephem, std::vector<long> quat, std::vector<long> angularVelocity, time_t satTime, long sunAngle) {
        this->ephem = ephem;
        this->quat = quat;
        this->angularVelocity = angularVelocity;
        this->satTime = satTime;
        this->sunAngle = sunAngle;
    }
    
    // Specific Data Members
    // Ephemeris
    std::vector<long> ephem;
    
    // Quaternion
    std::vector<long> quat;
    
    // Angular Velocity
    std::vector<long> angularVelocity;
    
    // Time
    time_t satTime;
    
    // Sun Angle
    long sunAngle;
    
};

#endif




