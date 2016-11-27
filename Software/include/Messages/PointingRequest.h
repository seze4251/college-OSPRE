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
    MessageID getMessageID() { return I_PointingRequest; }
};


#endif
