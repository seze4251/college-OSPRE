//
//  Message.h
//  Message
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef MESSAGE_H
#define MESSAGE_H

#include <ctime>
#include <string.h>
#include <iostream>
#include <stdio.h>

#include "PointEarthMoon.h"
#include "MessageID.h"

class Message {
public:
    Message(MessageID iden, time_t timeStamp) : timeStamp(timeStamp), iden(iden) {}
    virtual ~Message() {}
    virtual MessageID getMessageID() = 0;
    time_t timeStamp;
    MessageID iden;
    
    void printMessageHeader(FILE* logFile) {
        printMessageID(iden, logFile);
        fprintf(logFile, "Message.timeStamp = %ld (s)", timeStamp);
    }
};

#endif
