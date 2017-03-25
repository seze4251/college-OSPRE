//
//  Parser.cpp
//  Parser
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <cstring>

#include "MessageSizes.h"
#include "External_Parser.h"

External_Parser::External_Parser(ByteBuffer &bufParam) : buf(bufParam), messageHeader(0, NA) {
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

Message_External* External_Parser::parseMessage(bool* partialMessage) {
    // Set this equal to true now, if false later then change
    *partialMessage = false;
    
    // If there is not a full header + message ID, do not parse header
    if (buf.used() < 10 ) {
        return nullptr;
    }
    
    buf.get(messageHeader.header.bytes, EXTERNAL_HEADER_MESSAGE_SIZE);
    messageID = (MessageID) buf.getInt();
    
    // If there is a partial Message, rewind buffer and return null ptr
    if (buf.used() < (1 + messageHeader.header.header_struct.packetDataLength - sizeof(int)) ) {
        buf.rewind(10);
        *partialMessage = true;
        return nullptr;
    }
    
    Message_External* msg = nullptr;
    
    switch (messageID) {
        case E_OSPREStatus:
            msg = parseExternal_OSPREStatus();
            break;
            
        case E_PointingRequest:
            msg = parseExternal_PointingRequest();
            break;
            
        case E_SpacecraftDataMessage:
            msg = parseExternal_DataMessage();
            break;
            
        case E_SolutionMessage:
            msg = parseExternal_SolutionMessage();
            break;
            
        default:
            throw "External_Parser::parseMessage() Unknown message type recived";
    }
    
    return msg;
}

Message_External* External_Parser::parseExternal_DataMessage() {
    if (data == nullptr) {
        data = new External_DataMessage(0);
    }
    
    // Transfer Header and Message ID
    memcpy(data->header.bytes, messageHeader.header.bytes, EXTERNAL_HEADER_MESSAGE_SIZE);
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
    
    for (int i = 0; i < 3; i++) {
        data->sunAngle[i] = buf.getDouble();
    }
    
    
    data->sleep = (bool) buf.get();
    
    return data;
}

Message_External* External_Parser::parseExternal_OSPREStatus() {
    if (status == nullptr) {
        status = new External_OSPREStatus(0);
    } else {
        status->pID.clear();
        status->error.clear();
    }
    
    // Transfer Header and Message ID
    memcpy(status->header.bytes, messageHeader.header.bytes, EXTERNAL_HEADER_MESSAGE_SIZE);
    
    status->iden = messageID;
    status->totalHealth = (ProcessError) buf.getInt();
    status->numProblemProcesses = buf.getInt();
    
    for (int i = 0; i < status->numProblemProcesses; i++) {
        status->pID.push_back((ProcessID) buf.getInt());
        status->error.push_back((ProcessError) buf.getInt());
    }

    return status;
}

Message_External* External_Parser::parseExternal_PointingRequest() {
    if (pointing == nullptr) {
        pointing = new External_PointingRequest(0);
    }
    
    // Transfer Header and Message ID
    memcpy(pointing->header.bytes, messageHeader.header.bytes, EXTERNAL_HEADER_MESSAGE_SIZE);
    
    pointing->iden = messageID;
    
    // Specific Data Members
    pointing->point = (PointEarthMoon) buf.getInt();
    
    return pointing;
}

Message_External* External_Parser::parseExternal_SolutionMessage() {
    if (solution == nullptr) {
        solution = new External_SolutionMessage(0);
    }
    
    // Transfer Header and Message ID
    memcpy(solution->header.bytes, messageHeader.header.bytes, EXTERNAL_HEADER_MESSAGE_SIZE);
    solution->iden = messageID;
    
    // Position
    for (int i = 0; i < 3; i++) {
        solution->position[i] = buf.getDouble();
    }
    
    // Position Error
    for (int i = 0; i < 3; i++) {
        solution->positionError[i] = buf.getDouble();
    }
    
    // Velocity
    for (int i = 0; i < 3; i++) {
        solution->velocity[i] = buf.getDouble();
    }
    
    // Velocity Error
    for (int i = 0; i < 3; i++) {
        solution->velocityError[i] = buf.getDouble();
    }
    
    // Earth Spacecraft Moon Angle
    solution->earthScMoonAngle = buf.getDouble();
    
    return solution;
}
