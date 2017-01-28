//
//  DataMessage.h
//  DataMessage
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef DATAMESSAGE_H
#define DATAMESSAGE_H

#include "Message.h"

// Not quite sure how ephemris is going to be passed to us!
class DataMessage : public Message {
public:
    DataMessage() : Message(getMessageID(), time(0)) {}
    
    MessageID getMessageID() { return I_DataMessage; }
};
    
#endif
