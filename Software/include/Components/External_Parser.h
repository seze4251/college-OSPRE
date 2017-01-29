//
//  External_Parser.h
//  External_Parser
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef EXTERNALPARSER_H
#define EXTERNALPARSER_H

#include "ByteBuffer.h"
#include "Message.h"
#include "External_Messages.h"

class External_Parser {
public:
    //Constructor
    External_Parser(ByteBuffer &bufParam);
    
    //Destructor
    ~External_Parser();
    
    Message* parseMessage();
    
private:
    ByteBuffer &buf;
    
    // Messages
    External_DataMessage* data;
    External_OSPREStatus* status;
    External_PointingRequest* pointing;
    External_SolutionMessage* solution;

    // Message Parser Methods
    Message* parseExternal_DataMessage();
    Message* parseExternal_OSPREStatus();
    Message* parseExternal_PointingRequest();
    Message* parseExternal_SolutionMessage();
};



#endif
