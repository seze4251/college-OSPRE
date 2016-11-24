//
//  Parser.h
//  Parser
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef PARSER_H
#define PARSER_H

#include "ErrorCode.h"

class Parser {
public:
    //Constructor
    Parser();
    
    //Destructor
    ~Parser();
    
    ErrorCode parseMessage();
    
private:
    ByteBuffer *buf;
    
    
};



#endif
