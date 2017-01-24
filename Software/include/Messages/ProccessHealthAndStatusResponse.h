//
//  ProccessHealthAndStatusResponse.h
//  ProccessHealthAndStatusResponse
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef PROCCESSHEALTHANDSTATUSRESPONSE_H
#define PROCCESSHEALTHANDSTATUSRESPONSE_H

#include <vector>

#include "Message.h"
#include "ProcessID.h"
#include "ProcessError.h"

class ProccessHealthAndStatusResponse : public Message {
public:
    //TODO:
    //Implement this constructor later!
//        ProccessHealthAndStatusResponse(ProcessID p_ID, std::vector<ProcessError> error) : Message(getMessageID(), time(0)), p_ID(p_ID), error(error) {}
    
    ProccessHealthAndStatusResponse(ProcessID p_ID) : Message(getMessageID(), time(0)), p_ID(p_ID) {}
    MessageID getMessageID() {return I_ProccessHealthAndStatusResponse; }
    
    // Specific Data Members
    ProcessID p_ID;
    std::vector<ProcessError> error;
};

#endif
