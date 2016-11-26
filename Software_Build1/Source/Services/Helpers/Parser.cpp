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
    messageLength = -1;
    capture = NULL;
    // TODO:: Set Rest to NULL
}

Parser::~Parser() {
    
}

bool Parser::parseHeader() {
    // If there is not a full header, do not parse header
    if (buf.remaining() < 2 * sizeof(int)) {
        return false;
    }
    messageID = buf.getInt();
    messageLength = buf.getInt();
    return true;
}

Message* Parser::parseMessage() {
    if (messageLength == -1) {
        if(!parseHeader()) {
            return NULL;
        }
    }
    
    if (buf.remaining() < messageLength) {
        return NULL;
    }
    
    Message* msg;
    switch (messageID) {
        case I_CaptureImageRequest:
             msg = parseCaptureImageRequest();
            break;
        default:
            msg = NULL;
            std::cout << "Need To Implement Rest of Parser";
            break;
    }
    messageLength = -1;
    return msg;
}

Message* Parser::parseCaptureImageRequest() {
    if (capture == NULL) {
        capture = CaptureImageRequest();
    }
    capture.timeStamp = buf.getLong();
    return capture;
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************

Message* Parser::parseDataRequest() {
    
}

Message* Parser::parseEphemerisMessage() {
    
}

Message* Parser::parseImageAdjustment() {
    
}

Message* Parser::parseImageMessage() {
    
}

Message* Parser::parseOSPREStatus() {
    
}

Message* Parser::parsePointingRequest() {
    
}

Message* Parser::parseProccessHealthAndStatusRequest() {
    
}

Message* Parser::parseProccessHealthAndStatusResponse() {
    
}

Message* Parser::parseSolutionMessage() {
    
}
