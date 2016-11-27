//
//  Message.h
//  Message
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef MESSAGE_H
#define MESSAGE_H

#include "MessageID.h"

class Message {
public:
    virtual MessageID getMessageID() = 0;
    long timeStamp;
};

#endif
