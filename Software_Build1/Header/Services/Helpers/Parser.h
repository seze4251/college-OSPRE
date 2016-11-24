//
//  Parser.h
//  Parser
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef PARSER_H
#define PARSER_H

#include "ByteBuffer.h"
#include "MessageID.h"
#include "Internal_Messages.h"

class Parser {
public:
    //Constructor
    Parser(ByteBuffer &buf);
    
    //Destructor
    ~Parser();
    
    // Message Header: 1. int MSG ID 2. int length
    // If I have full Message return True, Else return False
    bool fullMessage();
    
    // Return Message Type
    MessageID typeMessage();
    
    //Do I need or not, how will I use this class?
    parseMessage();
    
    
    CaptureImageRequest& parseCaptureImageRequest();
    DataRequest& parseDataRequest();
    EphemerisMessage& parseEphemerisMessage();
    ImageAdjustment& parseImageAdjustment();
    ImageMessage& parseImageMessage();
    OSPREStatus& parseOSPREStatus();
    PointingRequest& parsePointingRequest();
    ProccessHealthAndStatusRequest& parseProccessHealthAndStatusRequest();
    ProccessHealthAndStatusResponse& parseProccessHealthAndStatusResponse();
    SolutionMessage& parseSolutionMessage();

    
private:
    ByteBuffer &buf;
    
};



#endif
