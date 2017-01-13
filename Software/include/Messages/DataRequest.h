//
//  DataRequest.h
//  DataRequest
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef DATAREQUEST_H
#define DATAREQUEST_H

#include "Message.h"

class DataRequest : public Message {
public:
    DataRequest() : Message(getMessageID(), time(0)) {}
    
    MessageID getMessageID() { return I_DataRequest; }
};

#endif
