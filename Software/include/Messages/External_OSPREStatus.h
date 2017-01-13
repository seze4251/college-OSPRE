//
//  External_OSPREStatus.h
//  External_OSPREStatus
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef EXTERNAL_OSPRESTATUS_H
#define EXTERNAL_OSPRESTATUS_H

#include "Message.h"

class External_OSPREStatus : public Message {
public:
    External_OSPREStatus() : Message(getMessageID(), time(0)) {}
    
    MessageID getMessageID() { return E_OSPREStatus; }
};

#endif
