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
    Parser(ByteBuffer &bufParam);
    
    //Destructor
    ~Parser();
    
    Message* parseMessage(bool* partialMessage);

private:
    ByteBuffer &buf;
    
    //Message Header
    int messageLength;
    MessageID messageID;
    time_t timeStamp;
    
    // Messages
    CaptureImageRequest* capture;
    DataMessage* data;
    ImageAdjustment* adjustment;
    ImageMessage* image;
    OSPREStatus* status;
    PointingRequest* pointing;
    ProcessHealthAndStatusRequest* request;
    ProcessHealthAndStatusResponse* response;
    SolutionMessage* solution;
    ProcessedImageMessage* processed;
    
    // Message Parser Methods
    Message* parseCaptureImageRequest();
    Message* parseDataMessage();
    Message* parseImageAdjustment();
    Message* parseImageMessage();
    Message* parseOSPREStatus();
    Message* parsePointingRequest();
    Message* parseProcessHealthAndStatusRequest();
    Message* parseProcessHealthAndStatusResponse();
    Message* parseSolutionMessage();
    Message* parseProcessedImageMessage();
};



#endif
