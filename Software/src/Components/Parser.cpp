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
    std::cout << "Parser Constructor" << std::endl;
    messageLength = -1;
    messageID = NA;
    timeStamp = 0;
    capture = nullptr;
    data = nullptr;
    ephem = nullptr;
    adjustment = nullptr;
    image = nullptr;
    status = nullptr;
    pointing = nullptr;
    request = nullptr;
    response = nullptr;
    solution = nullptr;
}

Parser::~Parser() {
    if (capture != nullptr) {
        delete capture;
    }
    
    if (data != nullptr) {
        delete data;
    }
    
    if (ephem != nullptr) {
        delete ephem;
    }
    
    if (adjustment != nullptr) {
        delete adjustment;
    }
    
    if (image != nullptr) {
        delete image;
    }
    
    if (status != nullptr) {
        delete status;
    }
    
    if (pointing != nullptr) {
        delete pointing;
    }
    
    if (request != nullptr) {
        delete request;
    }
    
    if (response != nullptr) {
        delete response;
    }
    
    if (solution != nullptr) {
        delete solution;
    }
}

Message* Parser::parseMessage() {
    // If there is not a full header, do not parse header
    if (buf.used() < (2 * sizeof(int) + sizeof(long)) ) {
        std::cout << "Parser::parseMessage is bailing in first check" << std::endl;
        return nullptr;
    }
    
    messageID = (MessageID) buf.getInt();
    messageLength = buf.getInt();
    
    std::cout << "Parser::parseMessage: messageID: " << messageID << " messageLength: " << messageLength << std::endl;
    std::cout << "buf.used: " << buf.used() << std::endl;
    // If there is a partial Message, rewind buffer and return null ptr
    if (buf.used() < (messageLength - 2 * sizeof(int)) ) {
        std::cout << "Parser::parseMessage: Partial Message, Rewinding Buffer" << std::endl;
        buf.rewind((2 * sizeof(int) ));
        return nullptr;
    }
    
    timeStamp = (time_t) buf.getLong();
    Message* msg = nullptr;
    std::cout << "Parser Dump: MessageID: " << messageID << " Message Length: " << messageLength << " timeStamp: " << timeStamp << std::endl;
    std::cout << "Current Time: " << time(0) << std::endl;
    switch (messageID) {
        case I_CaptureImageRequest:
            msg = parseCaptureImageRequest();
            break;
            
        case I_DataRequest:
            msg = parseDataRequest();
            break;
            
        case I_EphemerisMessage:
            msg = parseEphemerisMessage();
            break;
            
        case I_ImageAdjustment:
            msg = parseImageAdjustment();
            break;
            
        case I_ImageMessage:
            msg = parseImageMessage();
            break;
            
        case I_OSPREStatus:
            msg = parseOSPREStatus();
            break;
            
        case I_PointingRequest:
            msg = parsePointingRequest();
            break;
            
        case I_ProccessHealthAndStatusRequest:
            std::cout << "Entering parseProccessHealthAndStatusRequest" << std::endl;
            msg = parseProccessHealthAndStatusRequest();
            break;
            
        case I_ProccessHealthAndStatusResponse:
            msg = parseProccessHealthAndStatusResponse();
            break;
            
        case I_SolutionMessage:
            msg = parseSolutionMessage();
            break;
            
        default:
            std::cerr << "Parser::parseMessage(): Unknown Message Type Recived: " << messageID << std::endl;
            std::cerr << "Fatal Error: Closing Connection" << std::endl;
            // TODO: Throw Error to close connection
            //Change this exit to throw exception!!
            exit(-1);
    }
    
    return msg;
}

Message* Parser::parseProccessHealthAndStatusRequest() {
    if (request == nullptr) {
        request = new ProccessHealthAndStatusRequest();
    }
    
    if (messageLength != (2 * sizeof(int) + sizeof(time_t) ) ) {
        std::cerr << "Parser::parseProcessHealthAndStatusRequest(): Message Length Incorrect, length = " << messageLength << std::endl;
        return nullptr;
    }
    
    request->timeStamp = timeStamp;
    request->iden = messageID;
    return request;
}


Message* Parser::parseProccessHealthAndStatusResponse() {
    if (response == nullptr) {
        response = new ProccessHealthAndStatusResponse();
    }
    // *******************************
    //
    // TODO: Change Size check when message gets completed
    //
    // ********************************
    if (messageLength != (2 * sizeof(int) + sizeof(time_t) ) ) {
        std::cerr << "Parser::parseProcessHealthAndStatusRequest(): Message Length Incorrect, length = " << messageLength << std::endl;
        return nullptr;
    }
    
    response->timeStamp = timeStamp;
    response->iden = messageID;
    return response;
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************

Message* Parser::parseCaptureImageRequest() {
    if (capture == nullptr) {
        capture = new CaptureImageRequest();
    }
    capture->timeStamp = buf.getLong();
    return capture;
}

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

Message* Parser::parseSolutionMessage() {
    return nullptr;
}
