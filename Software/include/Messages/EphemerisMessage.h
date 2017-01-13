//
//  EphemerisMessage.h
//  EphemerisMessage
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef EPHEMERISMESSAGE_H
#define EPHEMERISMESSAGE_H

#include "Message.h"

// Not quite sure how ephemris is going to be passed to us!
class EphemerisMessage : public Message {
public:
    EphemerisMessage() : Message(getMessageID(), time(0)) {}
    
    MessageID getMessageID() { return I_EphemerisMessage; }
};
    
#endif
