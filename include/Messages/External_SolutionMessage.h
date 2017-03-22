//
//  External_SolutionMessage.h
//  External_SolutionMessage
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef EXTERNAL_SOLUTIONMESSAGE_H
#define EXTERNAL_SOLUTIONMESSAGE_H

#include <cstring>

#include "Message_External.h"

class External_SolutionMessage : public Message_External {
public:
    
    // Need to set: packetType, sequenceFlags, packetDataLength
    External_SolutionMessage(unsigned int applicationProcessID) : Message_External(applicationProcessID, E_SolutionMessage) {
        header.header_struct.packetType = 0;
        header.header_struct.sequenceFlags = 3;
        header.header_struct.packetSequence = 0;
        header.header_struct.packetDataLength = (8 * 13 + 4)  - 1;
    }
    
    // Update Message
    void update(double* position, double* positionError, double* velocity, double* velocityError, double earthScMoonAngle) {
        memcpy(this->position, position, 3*sizeof(double));
        memcpy(this->positionError, positionError, 3*sizeof(double));
        memcpy(this->velocity, velocity, 3*sizeof(double));
        memcpy(this->velocityError, velocityError, 3*sizeof(double));
        this->earthScMoonAngle = earthScMoonAngle;
    }
    
    // Print Message
    void print(FILE* logFile) {
        printHeader(FILE* logFile);
        
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
