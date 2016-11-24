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
    char * ephem;
    
    EphemerisMessage(char * ephem) {
        ephem = new sizeof(*ephem);
        strcpy(ephem, this -> ephem, sizeof(*ephem));
    }
    
    ~EphemerisMessage() {
        free(ephem);
    }
};

#endif
