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
    
    void print() {
        printMessageHeader();
        
        std::cout << "Position = ";
        for (int i = 0; i < 3; i++) {
            std::cout << position[i] << " ";
        }
        std::cout << " (km)" << std::endl;
        
        std::cout << "Position Error = ";
        for (int i = 0; i < 3; i++) {
            std::cout << positionError[i] << " ";
        }
        std::cout << " (km)" << std::endl;
        
        std::cout << "Velocity = ";
        for (int i = 0; i < 3; i++) {
            std::cout << velocity[i] << " ";
        }
        std::cout << " (m/s)" << std::endl;
        
        std::cout << "Velocity Error = ";
        for (int i = 0; i < 3; i++) {
            std::cout << velocityError[i] << " ";
        }
        std::cout << " (m/s)" << std::endl;
        
        std::cout << "Earth-SC-Moon Angle = " << earthScMoonAngle << " (degrees)" << std::endl;
        
    }
    
    // Specific Data Members
    double position[3];
    double positionError[3];
    double velocity[3];
    double velocityError[3];
    double earthScMoonAngle;
};

#endif
