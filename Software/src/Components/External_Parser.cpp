//
//  Parser.cpp
//  Parser
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <iostream>
#include "External_Parser.h"

External_Parser::External_Parser(ByteBuffer &bufParam) : buf(bufParam) {
    std::cout << "External_Parser Constructor" << std::endl;
    data = nullptr;
    status = nullptr;
    pointing = nullptr;
    solution = nullptr;
}

External_Parser::~External_Parser() {
    if (data != nullptr) {
        delete data;
    }
    
     if (status != nullptr) {
        delete status;
    }
    
    if (pointing != nullptr) {
        delete pointing;
    }

    if (solution != nullptr) {
        delete solution;
    }
}

Message* External_Parser::parseMessage() {
    // Parser code, needs to update for external parser
    /*
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
            
        case I_ProcessedImageMessage:
            msg = parseProcessedImageMessage();
            break;
            
        case I_DataMessage:
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
            
        case I_ProcessHealthAndStatusRequest:
            std::cout << "Entering parseProcessHealthAndStatusRequest" << std::endl;
            msg = parseProcessHealthAndStatusRequest();
            break;
            
        case I_ProcessHealthAndStatusResponse:
            msg = parseProcessHealthAndStatusResponse();
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
    */
    return nullptr;
}

Message* External_Parser::parseExternal_DataMessage() {
    return nullptr;
}

Message* External_Parser::parseExternal_OSPREStatus() {
    return nullptr;
}

Message* External_Parser::parseExternal_PointingRequest() {
    return nullptr;
}

Message* External_Parser::parseExternal_SolutionMessage() {
    return nullptr;
}
