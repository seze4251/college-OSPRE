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
#include <cstring>

#include "Message.h"

// Not quite sure how ephemris is going to be passed to us!
class DataMessage : public Message {
public:
    DataMessage() : Message(getMessageID(), time(0)) {}
    
    MessageID getMessageID() { return I_DataMessage; }
    
    void update(double* ephem, double* quat, double* angularVelocity, time_t satTime, double* sunAngle, bool sleep) {
        this->timeStamp = time(0);
        memcpy(this->ephem, ephem, 3 * sizeof(double));
        memcpy(this->quat, quat, 4 * sizeof(double));
        memcpy(this->angularVelocity, angularVelocity, 3 * sizeof(double));
        this->satTime = satTime;
        memcpy(this->sunAngle, sunAngle, 3 * sizeof(double));
        this->sleep = sleep;
    }
    
    void print(FILE* logFile) {
        fprintf(logFile, "Printing DataMessage");
        printMessageHeader(logFile);
        
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
        fprintf(logFile, " (deg/s)\n");
        
        fprintf(logFile, "Sun Angle = ");
        for (int i = 0; i < 3; i++) {
            fprintf(logFile, "%f ", sunAngle[i]);
        }
        
        fprintf(logFile, " (degrees)\n");
        
        fprintf(logFile, "satTime = %ld(s)\n", satTime);
        
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
    double sunAngle[3];
    
    bool sleep;
    
    
};

#endif




