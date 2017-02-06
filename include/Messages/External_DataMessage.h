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

class External_DataMessage {
public:
    External_DataMessage() {}
    
    
    // Specific Data Members
    // Ephemeris
    double ephem[3];
    
    // Quaternion
    double quat[4];
    
    // Angular Velocity
    double angularVelocity[3];
    
    // Time
    time_t time;
    
    // Sun Angle
    long sunAngle;

};

#endif
