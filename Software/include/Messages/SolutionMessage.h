//
//  SolutionMessage.h
//  SolutionMessage
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SOLUTIONMESSAGE_H
#define SOLUTIONMESSAGE_H

#include <vector>

#include "Message.h"

class SolutionMessage : public Message {
public:
    SolutionMessage(PointEarthMoon point, std::vector<long> position, std::vector<long> positionError, std::vector<long> velocity, std::vector<long> velocityError) : Message(getMessageID(), time(0)), point(point), position(position), positionError(positionError), velocity(velocity), velocityError(velocityError) {}
    
    MessageID getMessageID() {return I_SolutionMessage;}
    
    // Specific Data Members
    PointEarthMoon point;
    std::vector<long> position;
    std::vector<long> positionError;
    std::vector<long> velocity;
    std::vector<long> velocityError;
    long earthScMoonAngle;
};

#endif
