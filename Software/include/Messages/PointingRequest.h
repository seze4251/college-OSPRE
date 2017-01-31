//
//  PointingRequest.h
//  PointingRequest
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef POINTINGREQUEST_H
#define POINTINGREQUEST_H

#include "Message.h"

class PointingRequest : public Message {
public:
    PointingRequest() : Message(getMessageID(), time(0)), point(PEM_NA) {}
    MessageID getMessageID() { return I_PointingRequest; }
    
    void update(PointEarthMoon point) {
        this->point = point;
    }
    
    // Specific Data Members
    PointEarthMoon point;
};


#endif
