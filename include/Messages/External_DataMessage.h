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
    
    // Update Data Message
    void update(double* ephem, double* quat, double* angularVelocity, time_t satTime, double sunAngle, bool sleep) {
        memcpy(this->ephem, ephem, 3*sizeof(double));
        memcpy(this->quat, quat, 4*sizeof(double));
        memcpy(this->angularVelocity, angularVelocity, 3*sizeof(double));
        this->sleep = sleep;
        this->sunAngle = sunAngle;
        this->satTime = satTime;
    }
    
    // Print Message
    void print() {
        std::cout << "Data Message: Printing Message" << std::endl;
        printHeader();
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
        
        std::cout << "Sun Angle = " << sunAngle << std::endl;
        std::cout << " satTime = " << satTime << std::endl;
        std::cout << "Sleep = " << sleep << ", Awake = 0, sleep = 1" << std::endl;
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
    
    // Sleep Mode, when == true go to sleep
    bool sleep;
    
    };

#endif
