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
    
    Message* parseMessage();
    
    // Header
    
    MessageID messageID;
    
    // Messages
    CaptureImageRequest *capture;
    DataRequest *data;
    EphemerisMessage *ephem;
    ImageAdjustment *adjustment;
    ImageMessage *image;
    OSPREStatus *status;
    PointingRequest *pointing;
    ProccessHealthAndStatusRequest *request;
    ProccessHealthAndStatusResponse *response;
    SolutionMessage *solution;
    
    
    
private:
    // Buffer
    ByteBuffer &buf;
    int messageLength;
    
    bool parseHeader();
    Message* parseCaptureImageRequest();
    Message* parseDataRequest();
    Message* parseEphemerisMessage();
    Message* parseImageAdjustment();
    Message* parseImageMessage();
    Message* parseOSPREStatus();
    Message* parsePointingRequest();
    Message* parseProccessHealthAndStatusRequest();
    Message* parseProccessHealthAndStatusResponse();
    Message* parseSolutionMessage();
};



#endif
