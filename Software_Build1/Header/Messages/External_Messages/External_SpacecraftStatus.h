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
    std::vector <double> quat;
    std::vector <double> angularVelocity;
    double sunAngle;
    clock_t time;
    bool active;
    
    SpacecraftStatus(bool active, bool healthy, char * message) {
        this -> active = active;
        this -> healthy = healthy;
        this -> message = new sizeof(*message);
        strcpy(message, this -> message, sizeof(*message));
    }
    
    ~SpacecraftStatus() {
        free(message);
    }
};

#endif
