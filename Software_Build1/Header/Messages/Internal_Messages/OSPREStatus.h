//
//  OSPREStatus.h
//  OSPREStatus
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef MESSAGES_H
#define MESSAGES_H

#include "Message.h"


class OSPREStatus : public Message {
public:
    bool active; // True if On, False if Off
    bool healthy; // True if Healthy, False if sick
    char * message;
    
    OSPREStatus() {
        
    }
    
    OSPREStatus(bool active, bool healthy, char * message) {
        this -> active = active;
        this -> healthy = healthy;
        this -> message = new sizeof(*message);
        bcopy(message, this -> message, sizeof(*message));
    }
    
    ~OSPREStatus() {
        free(message);
    }
};


#endif
