//
//  ProccessHealthAndStatusRequest.h
//  ProccessHealthAndStatusRequest
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef PROCCESSHEALTHANDSTATUSREQUEST_H
#define PROCCESSHEALTHANDSTATUSREQUEST_H

#include "Message.h"

// Small and tight
class ProccessHealthAndStatusRequest : public Message {
public:
    MessageID getMessageID() { return I_ProccessHealthAndStatusRequest; }
};
#endif
