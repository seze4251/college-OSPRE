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
#include <cstring>

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
    void print(FILE* logFile) {
        printHeader(FILE* logFile);
        fprintf(logFile, "Printing External_DataMessage");
        fprintf(logFile, "Ephem = ");
        for (int i = 0; i < 3; i++) {
            fprintf(logFile, "%f ", ephem[i]);
        }
        fprintf(logFile, " (km)\n");
        
       
        fprintf(logFile, "Quat = ");
        for (int i = 0; i < 4; i++) {
            fprintf(logFile, "%f ", quat[i]);
        }
        fprintf(logFile, " \n");
        
        fprintf(logFile, "Angular Velocity = ");
        for (int i = 0; i < 3; i++) {
            fprintf(logFile, "%f ", angularVelocity[i]);
        }
        fprintf(logFile, " (rad/s)\n");
        fprintf(logFile, "Sun Angle = %f (degrees), satTime = %f(s)\n", sunAngle, satTime);
        
        if (sleep == true) {
            fprintf(logFile, "Sleeping, no Capturing Data");
        } else {
            fprintf(logFile, "Capturing Data Mode");
        }
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
