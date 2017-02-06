//
//  ProccessHealthAndStatusRequest.h
//  ProccessHealthAndStatusRequest
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef PROCESSHEALTHANDSTATUSREQUEST_H
#define PROCESSHEALTHANDSTATUSREQUEST_H

#include "Message.h"

// Small and tight
class ProcessHealthAndStatusRequest : public Message {
public:
    ProcessHealthAndStatusRequest() : Message(getMessageID(), time(0)) {}
    MessageID getMessageID() { return I_ProcessHealthAndStatusRequest; }
   
    void update() {
        this->timeStamp = time(0);
    }
};
#endif
