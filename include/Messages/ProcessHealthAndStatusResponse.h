//
//  ProccessHealthAndStatusResponse.h
//  ProccessHealthAndStatusResponse
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef PROCESSHEALTHANDSTATUSRESPONSE_H
#define PROCESSHEALTHANDSTATUSRESPONSE_H

#include <vector>
#include <iostream> 

#include "Message.h"
#include "ProcessID.h"
#include "ProcessError.h"

class ProcessHealthAndStatusResponse : public Message {
public:
    //Constructors:
    ProcessHealthAndStatusResponse() : Message(getMessageID(), time(0)) {}
    
    ProcessHealthAndStatusResponse(std::vector<ProcessError> error) : Message(getMessageID(), time(0)), error(error) {}
    
    MessageID getMessageID() {return I_ProcessHealthAndStatusResponse; }
    
    //Member Functions
    void update(std::vector<ProcessError> error) {
        timeStamp = time(0);
        this->error = error;
    }
    
    void print() {
        std::cout<< "Printing OSPREStatus Message" << std::endl;
        for (auto i = error.begin(); i != error.end(); ++i)
            std::cout << *i << ' ';
    }
    
    // Specific Data Members
    std::vector<ProcessError> error;
    
    
};

#endif
