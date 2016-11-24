//
//  Parser.cpp
//  Parser
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include "Parser.h"

Parser::Parser(ByteBuffer &buf) {
    this->buf = buf;
}

bool Parser::fullMessage() {
    if (buf.remaining() >= buf.peakAheadInt()) {
        return true;
    } else {
        return false;
    }
}

MessageID Parser::typeMessage() {
    return (MessageID) buf.peekInt();
}

CaptureImageRequest& Parser::parseCaptureImageRequest() {
    
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************

DataRequest& Parser::parseDataRequest() {
    
}

EphemerisMessage& Parser::parseEphemerisMessage() {
    
}

ImageAdjustment& Parser::parseImageAdjustment() {
    
}

ImageMessage& Parser::parseImageMessage() {
    
}

OSPREStatus& Parser::parseOSPREStatus() {
    
}

PointingRequest& Parser::parsePointingRequest() {
    
}

ProccessHealthAndStatusRequest& Parser::parseProccessHealthAndStatusRequest() {
    
}

ProccessHealthAndStatusResponse& Parser::parseProccessHealthAndStatusResponse() {
    
}

SolutionMessage& Parser::parseSolutionMessage() {
    
}
