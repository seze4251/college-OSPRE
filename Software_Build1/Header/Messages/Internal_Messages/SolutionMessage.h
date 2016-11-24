//
//  SolutionMessage.h
//  SolutionMessage
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SOLUTIONMESSAGE_H
#define SOLUTIONMESSAGE_H

#include "Message.h"

//Need to find the copy vector method!!
class SolutionMessage : public Message {
public:
    std::vector <double> position;
    std::vector <double> positionError;
    std::vector <double> velocity;
    std::vector <double> velocityError;
    double earthScMoonAngle;
    
    SolutionMessage(std::vector position, std::vector positionError, std::vector velocity,
                    std::vector velocityError, double earthScMoonAngle) {
        this -> position = position;
        this -> positionError = positionError;
        this -> velocity = velocity;
        this -> velocityError = velocityError;
        this -> earthScMoonAngle = earthScMoonAngle;
    }
};

#endif
