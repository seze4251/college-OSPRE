//
//  External_PointingRequest.h
//  External_PointingRequest
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef EXTERNAL_POINTINGREQUEST_H
#define EXTERNAL_POINTINGREQUEST_H

#include "Message.h"

class External_PointingRequest : public Message {
public:
    External_PointingRequest() : Message(getMessageID(), time(0)) {}
    
    MessageID getMessageID() { return E_PointingRequest; }
};
#endif
