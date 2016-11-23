//
//  Builder.h
//  Builder
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


// Builder will get passed a generic Message type and determine which message it is and build a charecter sting to send the message.  I
#ifndef BUILDER_H
#def BUILDER_H

#include "ErrorCode.h"
#include "Messages.h"

class Builder {
public:
    
    //Constructor
    Builder();
    
    // Destructor
    ~Builder();
    
    // Public Methods
    ErrorCode buildMessage(Message message, char ** builtMessage);
    
private:
    ErrorCode buildHeader();
    ErrorCode buildBody();
    
};

#endif
