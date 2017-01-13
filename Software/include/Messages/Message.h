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
#include <ctime>

class Message {
public:
    Message(MessageID iden, time_t timeStamp) : timeStamp(timeStamp), iden(iden) {}
    virtual MessageID getMessageID() = 0;
    time_t timeStamp;
    MessageID iden;
};

#endif
