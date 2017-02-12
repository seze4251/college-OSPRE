//
//  DataMessage.h
//  DataMessage
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef DATAMESSAGE_H
#define DATAMESSAGE_H
#include <iostream>

#include "Message.h"

// Not quite sure how ephemris is going to be passed to us!
class DataMessage : public Message {
public:
    DataMessage() : Message(getMessageID(), time(0)) {}
    
    MessageID getMessageID() { return I_DataMessage; }
    
    void update(double* ephem, double* quat, double* angularVelocity, time_t satTime, double sunAngle, bool sleep) {
        this->timeStamp = time(0);
        memcpy(this->ephem, ephem, 3 * sizeof(double));
        memcpy(this->quat, quat, 4 * sizeof(double));
        memcpy(this->angularVelocity, angularVelocity, 3 * sizeof(double));
        this->satTime = satTime;
        this->sunAngle = sunAngle;
        this->sleep = sleep;
    }
    
    void print() {
        std::cout<< "Printing Data Message" << std::endl;
        std::cout << "Ephem = ";
        for (int i = 0; i < 3; i++) {
            std::cout << ephem[i] << " ";
        }
        std::cout << std::endl;
        
        std::cout << "quat = ";
        for (int i = 0; i < 4; i++) {
            std::cout << quat[i] << " ";
        }
        std::cout << std::endl;
        
        std::cout << "Angular Velocity = ";
        for (int i = 0; i < 3; i++) {
            std::cout << angularVelocity[i] << " ";
        }
        std::cout << std::endl;
        
        std::cout << "Sun Angle = " << sunAngle << " satTime = " << satTime << std::endl;
        
        std::cout << "satTime = " << satTime << std::endl;
        
        std::cout << "Sleep = " << sleep << ", 0 = Awake, 1 = sleep" << std::endl;
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
    
    bool sleep;
    
    
};

#endif




