//
//  ProccessHealthAndStatusResponse.h
//  ProccessHealthAndStatusResponse
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef PROCCESSHEALTHANDSTATUSRESPONSE_H
#define PROCCESSHEALTHANDSTATUSRESPONSE_H

#include "Message.h"

class ProccessHealthAndStatusResponse : public Message {
public:
    MessageID getMessageID() {return I_ProccessHealthAndStatusResponse; }
};

#endif
