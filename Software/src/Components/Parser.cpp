//
//  Parser.cpp
//  Parser
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <iostream>
#include "Parser.h"

Parser::Parser(ByteBuffer &bufParam) : buf(bufParam) {
    messageLength = -1;
    capture = nullptr;
}

Parser::~Parser() {
    
}

bool Parser::parseHeader() {
    // If there is not a full header, do not parse header
    if (buf.remaining() < 2 * sizeof(int)) {
        return false;
    }
    messageID = (MessageID) buf.getInt();
    messageLength = buf.getInt();
    return true;
}

Message* Parser::parseMessage() {
    if (messageLength == -1) {
        if(!parseHeader()) {
            return nullptr;
        }
    }
    
    if (buf.remaining() < messageLength) {
        return nullptr;
    }
    
    Message* msg;
    switch (messageID) {
        case I_CaptureImageRequest:
             msg = parseCaptureImageRequest();
            break;
        default:
            msg = nullptr;
            std::cout << "Need To Implement Rest of Parser";
            break;
    }
    messageLength = -1;
    return msg;
}

Message* Parser::parseCaptureImageRequest() {
    if (capture == nullptr) {
        capture = new CaptureImageRequest;
    }
    capture->timeStamp = buf.getLong();
    return capture;
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************

Message* Parser::parseDataRequest() {
    return nullptr;
}

Message* Parser::parseEphemerisMessage() {
    return nullptr;
}

Message* Parser::parseImageAdjustment() {
    return nullptr;
}

Message* Parser::parseImageMessage() {
    return nullptr;
}

Message* Parser::parseOSPREStatus() {
    return nullptr;
}

Message* Parser::parsePointingRequest() {
    return nullptr;
}

Message* Parser::parseProccessHealthAndStatusRequest() {
    return nullptr;
}

Message* Parser::parseProccessHealthAndStatusResponse() {
    return nullptr;
}

Message* Parser::parseSolutionMessage() {
    return nullptr;
}
