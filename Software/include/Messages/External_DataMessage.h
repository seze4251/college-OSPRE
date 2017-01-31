//
//  External_DataMessage.h
//  External_DataMessage
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef EXTERNALDATAMESSAGE_H
#define EXTERNALDATAMESSAGE_H

class External_DataMessage {
public:
    External_DataMessage() {}
    
    
    // Specific Data Members
    // Ephemeris
    std::vector<long> ephem;
    
    // Quaternion
    std::vector<long> quat;
    
    // Angular Velocity
    std::vector<long> angularVelocity;
    
    // Time
    time_t time;
    
    // Sun Angle
    long sunAngle;

};

#endif
