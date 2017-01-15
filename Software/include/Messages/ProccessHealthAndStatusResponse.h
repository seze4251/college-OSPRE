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
#include "ProcessID.h"

class ProccessHealthAndStatusResponse : public Message {
public:
        ProccessHealthAndStatusResponse(ProcessID p_ID) : Message(getMessageID(), time(0)), p_ID(p_ID) {}
    MessageID getMessageID() {return I_ProccessHealthAndStatusResponse; }
    ProcessID p_ID;
};

#endif
