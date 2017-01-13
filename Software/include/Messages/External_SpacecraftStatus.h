//
//  External_SpacecraftStatus.h
//  External_SpacecraftStatus
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef MESSAGES_H
#define MESSAGES_H

#include "Message.h"

class External_SpacecraftStatus : public Message {
public:
    External_SpacecraftStatus() : Message(getMessageID(), time(0)) {}
    MessageID getMessageID() { return E_SpacecraftStatus; }
};

#endif
