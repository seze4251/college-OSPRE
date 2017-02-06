//
//  OSPREStatus.h
//  OSPREStatus
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef OSPRESTATUS_H
#define OSPRESTATUS_H

#include <vector>
#include <iostream>

#include "Message.h"
#include "ProcessError.h"

class OSPREStatus : public Message {
public:
    OSPREStatus() : Message(getMessageID(), time(0)) {}
    MessageID getMessageID() { return I_OSPREStatus; }
    
    // Specific Data Members
    void update( std::vector<ProcessError> error) {
        this->error = error;
    }
    
    void print() {
        std::cout<< "Printing OSPREStatus Message" << std::endl;
        for (auto i = error.begin(); i != error.end(); ++i)
            std::cout << *i << ' ';
    }
    
    //Specific Data Members
    std::vector<ProcessError> error;
};


#endif
