//
//  Parser.cpp
//  Parser
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include "Parser.h"

Parser::Parser(ByteBuffer &bufParam) : buf(bufParam) {
    messageLength = -1;
    messageID = NA;
    timeStamp = 0;
    
    // Initialize all message pointers to nullptr
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
    
    if (data != nullptr) {
        delete data;
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
    if (buf.used() < HEADER_MESSAGE_SIZE ) {
        *partialMessage = false;
        return nullptr;
    }
    
    messageID = (MessageID) buf.getInt();
    messageLength = buf.getInt();
    
    // If there is a partial Message, rewind buffer and return null ptr
    if (buf.used() < (messageLength - 2 * sizeof(int)) ) {
        buf.rewind((2 * sizeof(int) ));
        *partialMessage = true;
        return nullptr;
    }
    
    timeStamp = (time_t) buf.getLong();
    Message* msg = nullptr;

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
            msg = parseProcessHealthAndStatusRequest();
            break;
            
        case I_ProcessHealthAndStatusResponse:
            msg = parseProcessHealthAndStatusResponse();
            break;
            
        case I_SolutionMessage:
            msg = parseSolutionMessage();
            break;
            
        default:
            throw "Parser::parseMessage(): Unknown Message Type Recived";
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
    
    response->timeStamp = timeStamp;
    response->iden = messageID;
    
    response->error = (ProcessError) buf.getInt();
    return response;
}

Message* Parser::parseProcessedImageMessage() {
    if (processed == nullptr) {
        processed = new ProcessedImageMessage();
    }
    
    processed->timeStamp = timeStamp;
    processed->iden = messageID;
    
    // Specific Data Members
    processed->alpha = buf.getDouble();
    processed->beta = buf.getDouble();
    processed->theta = buf.getDouble();
    processed->pixel_error = buf.getDouble();
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
    data->sleep = (bool) buf.get();
    
    return data;
}

Message* Parser::parseOSPREStatus() {
    if (status == nullptr) {
        status = new OSPREStatus();
    } else {
        status->pID.clear();
        status->error.clear();
    }
    
    status->timeStamp = timeStamp;
    status->iden = messageID;
    
    status->totalHealth = (ProcessError) buf.getInt();
    status->numProblemProcesses = buf.getInt();
    
    for (int i = 0; i < status->numProblemProcesses; i++) {
        status->pID.push_back((ProcessID) buf.getInt());
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

Message* Parser::parseImageMessage() {
    if (image == nullptr) {
        image = new ImageMessage();
    }
    
    image->timeStamp = timeStamp;
    image->iden = messageID;
    image->point = (PointEarthMoon) buf.getInt();
    image->cameraWidth = buf.getInt();
    image->cameraHeight = buf.getInt();
    image->FOV = buf.getDouble();
    
    int imageLength = messageLength - (HEADER_MESSAGE_SIZE + 3 * sizeof(int) + sizeof(double));
    
    
    if( imageLength > image->imageBufferSize) {
        image->resizeImageArray(2*buf.used());
    }
    
    image->currentImageSize = imageLength;
    buf.get(image->getImagePointer(), imageLength);
    
    return image;
}

// TODO: Implement in future when OSPRE gets camera funcitonality
Message* Parser::parseImageAdjustment() {
    if (adjustment == nullptr) {
        adjustment = new ImageAdjustment();
    }
    
    adjustment->timeStamp = timeStamp;
    adjustment->iden = messageID;
    return adjustment;
}



