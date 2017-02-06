//
//  External_Builder.h
//  External_Builder
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef EXTERNALBUILDER_H
#define EXTERNALBUILDER_H

#include "External_Messages.h"
#include "MessageID.h"
#include "ByteBuffer.h"

class External_Builder {
public:
    
    //Constructor
    External_Builder(ByteBuffer &bufParam);
    
    // Destructor
    ~External_Builder();
    
    // Public Methods
    void buildExternal_DataMessage(External_DataMessage &msg);
    void buildExternal_OSPREStatus(External_OSPREStatus &msg);
    void buildExternal_PointingRequest(External_PointingRequest &msg);
    void buildExternal_SolutionMessage(External_SolutionMessage &msg);
    
private:
    //Members
    ByteBuffer& buf;
    
};

#endif
