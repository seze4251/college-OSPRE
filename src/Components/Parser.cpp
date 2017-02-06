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
    adjustment = nullptr;
    image = nullptr;
    status = nullptr;
    pointing = nullptr;
    request = nullptr;
    response = nullptr;
    solution = nullptr;
    processed = nullptr;
}

Parser::~Parser() {
    if (capture != nullptr) {
        delete capture;
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
    
    if (processed != nullptr) {
        delete processed;
    }
}

Message* Parser::parseMessage(bool* partialMessage) {
    // If there is not a full header, do not parse header
    if (buf.used() < (2 * sizeof(int) + sizeof(long)) ) {
        std::cout << "Parser::parseMessage no header left in buffer" << std::endl;
        *partialMessage = false;
        return nullptr;
    }
    
    messageID = (MessageID) buf.getInt();
    messageLength = buf.getInt();
    
 //   std::cout << "Parser::parseMessage: messageID: " << messageID << " messageLength: " << messageLength << std::endl;
    std::cout << "Message Length: " << messageLength << "  buf.used: " << buf.used() << std::endl;
    
    // If there is a partial Message, rewind buffer and return null ptr
    if (buf.used() < (messageLength - 2 * sizeof(int)) ) {
        std::cout << "Parser::parseMessage: Partial Message, Rewinding Buffer" << std::endl;
        buf.rewind((2 * sizeof(int) ));
        *partialMessage = true;
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
            msg = parseDataMessage();
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
}

Message* Parser::parseProcessHealthAndStatusRequest() {
    if (request == nullptr) {
        request = new ProcessHealthAndStatusRequest();
    }
    
    request->timeStamp = timeStamp;
    request->iden = messageID;
    return request;
}


Message* Parser::parseProcessHealthAndStatusResponse() {
    if (response == nullptr) {
        response = new ProcessHealthAndStatusResponse();
    }
    
    int messageHeader = 2 * sizeof(int) + sizeof(time_t);
    int messageBody = (messageLength - messageHeader) / sizeof(int);
    
    response->timeStamp = timeStamp;
    response->iden = messageID;
    
    for (int i = 0; i < messageBody; i++) {
        response->error.push_back((ProcessError) buf.getInt());
    }
    
    return response;
}

Message* Parser::parseProcessedImageMessage() {
    if (processed == nullptr) {
        processed = new ProcessedImageMessage();
    }
    
    processed->timeStamp = timeStamp;
    processed->iden = messageID;
    
    // Specific Data Members
    processed->distance = buf.getDouble();
    processed->error = buf.getDouble();
    processed->point = (PointEarthMoon) buf.getInt();
    
    return processed;
}

Message* Parser::parseCaptureImageRequest() {
    if (capture == nullptr) {
        capture = new CaptureImageRequest();
    }
    
    capture->timeStamp = timeStamp;
    capture->iden = messageID;
    
    // Specific Data Members
    capture->point = (PointEarthMoon) buf.getInt();
    for (int i = 0; i < 3; i++) {
        capture->estimatedPosition[i] = buf.getDouble();
    }
    
    return capture;
}

Message* Parser::parseDataMessage() {
    if (data == nullptr) {
        data = new DataMessage();
    }

    data->timeStamp = timeStamp;
    data->iden = messageID;
    
    // Specific Data Members ephem quat angularVelocity satTime sunAngle
    for (int i = 0; i < 3; i++) {
        data->ephem[i] = buf.getDouble();
    }
    
    for (int i = 0; i < 4; i++) {
        data->quat[i] = buf.getDouble();
    }
    
    for (int i = 0; i < 3; i++) {
        data->angularVelocity[i] = buf.getDouble();
    }
    
    data->satTime = buf.getLong();
    data->sunAngle = buf.getDouble();
    
    return data;
}

Message* Parser::parseImageAdjustment() {
    if (adjustment == nullptr) {
        adjustment = new ImageAdjustment();
    }
  
    adjustment->timeStamp = timeStamp;
    adjustment->iden = messageID;
    return adjustment;
}



Message* Parser::parseOSPREStatus() {
    if (status == nullptr) {
        status = new OSPREStatus();
    }
    
    int messageHeader = 2 * sizeof(int) + sizeof(time_t);
    int messageBody = (messageLength - messageHeader) / sizeof(int);
    
    status->timeStamp = timeStamp;
    status->iden = messageID;
    
    for (int i = 0; i < messageBody; i++) {
        status->error.push_back((ProcessError) buf.getInt());
    }
    
    return status;
}

Message* Parser::parsePointingRequest() {
    if (pointing == nullptr) {
        pointing = new PointingRequest();
    }
    
    pointing->timeStamp = timeStamp;
    pointing->iden = messageID;
    
    // Specific Data Members
    pointing->point = (PointEarthMoon) buf.getInt();
    
    return pointing;
}

Message* Parser::parseSolutionMessage() {
    if (solution == nullptr) {
        solution = new SolutionMessage();
    }
    
    solution->timeStamp = timeStamp;
    solution->iden = messageID;
    
    for (int i = 0; i < 3; i++) {
        solution->position[i] = buf.getDouble();
    }
    
    for (int i = 0; i < 3; i++) {
        solution->positionError[i] = buf.getDouble();
    }
    
    for (int i = 0; i < 3; i++) {
        solution->velocity[i] = buf.getDouble();
    }
    
    for (int i = 0; i < 3; i++) {
        solution->velocityError[i] = buf.getDouble();
    }
    
    solution->earthScMoonAngle = buf.getDouble();
    
    return solution;
}

//**************************
//TODO: COmplete This
Message* Parser::parseImageMessage() {
    if (image == nullptr) {
        image = new ImageMessage();
    }
    
    image->timeStamp = timeStamp;
    image->iden = messageID;
    image->point = (PointEarthMoon) buf.getInt();
    buf.get(image->image, IMAGE_SIZE);
    
    return image;
}



