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
    bool pointAtEarth; // If true point towards Earth, If False point towards moon
    
    PointingRequest(bool point) {
        pointAtEarth = point;
    }
};


#endif
