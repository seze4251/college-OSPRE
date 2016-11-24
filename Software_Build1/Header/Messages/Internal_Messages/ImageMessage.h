//
//  ImageMessage.h
//  ImageMessage
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef IMAGEMESSAGE_H
#define IMAGEMESSAGE_H

#include "Message.h"

class ImageMessage : public Message {
public:
    bool active; // True if On, False if Off
    bool healthy; // True if Healthy, False if sick
    char * message;
    
    ImageMessage(bool active, bool healthy, char * message) {
        this -> active = active;
        this -> healthy = healthy;
        this -> message = new sizeof(*message);
        bcopy(message, this -> message, sizeof(*message));
    }
    
    ~ImageMessage() {
        free(message);
    }
};

#endif
