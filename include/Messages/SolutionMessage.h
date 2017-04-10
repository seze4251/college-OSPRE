//
//  SolutionMessage.h
//  SolutionMessage
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#ifndef SOLUTIONMESSAGE_H
#define SOLUTIONMESSAGE_H

#include <cstring>
#include <vector>
#include <iostream>

#include "Message.h"

class SolutionMessage : public Message {
public:
    // Constructors
    SolutionMessage() : Message(getMessageID(), time(0)) {}
    
    MessageID getMessageID() {return I_SolutionMessage;}

    
    void update(double* position, double* positionError, double* velocity, double* velocityError, double earthScMoonAngle) {
        memcpy(this->position, position, 3 * sizeof(double));
        memcpy(this->positionError, positionError, 3 * sizeof(double));
        memcpy(this->velocity, velocity, 3 * sizeof(double));
        memcpy(this->velocityError, velocityError, 3 * sizeof(double));
        this->earthScMoonAngle = earthScMoonAngle;
        this->timeStamp = time(0);
    }
    
    void print(FILE* logFile) {
        fprintf(logFile, "Printing Solution Message\n");
        printMessageHeader(logFile);
        
        fprintf(logFile, "Position = ");
        for (int i = 0; i < 3; i++) {
            fprintf(logFile, " %f", position[i]);
        }
        fprintf(logFile, " (km)\n");
        
        fprintf(logFile, "Position Error = ");
        for (int i = 0; i < 3; i++) {
            fprintf(logFile, " %f", positionError[i]);
        }
        fprintf(logFile, " (km)\n");
        
        fprintf(logFile, "Velocity = ");
        for (int i = 0; i < 3; i++) {
            fprintf(logFile, " %f", velocity[i]);
            std::cout << velocity[i] << " ";
        }
        fprintf(logFile, " (km/s)\n");
        
        fprintf(logFile, "Velocity Error = ");
        for (int i = 0; i < 3; i++) {
            fprintf(logFile, " %f", velocityError[i]);
        }
        fprintf(logFile, " (km/s)\n");
        
        fprintf(logFile, "Earth-SC-Moon Angle = %f (degrees)", earthScMoonAngle);
    }
    
    // Specific Data Members
    double position[3];
    double positionError[3];
    double velocity[3];
    double velocityError[3];
    double earthScMoonAngle;
};

#endif
