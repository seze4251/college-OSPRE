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

Message_External* External_Parser::parseMessage(bool* partialMessage) {
    // Set this equal to true now, if false later then change
    *partialMessage = false;
    
    // If there is not a full header + message ID, do not parse header
    if (buf.used() < 20 ) {
        std::cout << "External_Parser::parseMessage no header left in buffer" << std::endl;
        return nullptr;
    }
    
    buf.getget(messageHeader.bytes, 6);
    messageID = (MessageID) buf.getInt();
    
    
    
    // If there is a partial Message, rewind buffer and return null ptr
    if (buf.used() < (messageLength - 2 * sizeof(int)) ) {
        std::cout << "External_Parser::parseMessage: Partial Message, Rewinding Buffer" << std::endl;
        buf.rewind(10);
        *partialMessage = true;
        return nullptr;
    }
    
    
    Message_External* msg = nullptr;
    
    std::cout << "External_Parser::parseMessage() starting Message ID switch Statement" << std::endl;
    
    switch (messageID) {
        case E_OSPREStatus:
            msg = parseExternal_OSPREStatus();
            std::cout << "External_Parser::parseMessage() OSPREStatus" << std::endl;
            break;
            
        case E_PointingRequest:
            msg = parseExternal_PointingRequest();
            std::cout << "External_Parser::parseMessage() Pointing Request" << std::endl;
            break;
            
        case E_SpacecraftDataMessage:
            msg = parseExternal_DataMessage();
            std::cout << "External_Parser::parseMessage() Data Message" << std::endl;
            break;
            
        case E_SolutionMessage:
            msg = parseExternal_SolutionMessage();
            std::cout << "External_Parser::parseMessage() Solution Message" << std::endl;
            break;
            
        default:
            std::cerr << "External_Parser::parseMessage(): Unknown Message Type Recived: " << messageID << std::endl;
            std::cerr << "Fatal Error: Exiting" << std::endl;
            exit(-1);
    }
    
    return msg;
}

Message_External* External_Parser::parseExternal_DataMessage() {
    if (data == nullptr) {
        data = new DataMessage();
    }
    
    // Transfer Header and Message ID
    data->bytes = messageHeader.bytes;
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

Message_External* External_Parser::parseExternal_OSPREStatus() {
    if (status == nullptr) {
        status = new OSPREStatus();
    }
    
    // Transfer Header and Message ID
    status->bytes = messageHeader.bytes;
    status->iden = messageID;
    
    int messageBody = (messageHeader.packetDataLength + 1) / 4;
    
    for (int i = 0; i < messageBody; i++) {
        status->error.push_back((ProcessError) buf.getInt());
    }
    
    return status;

}

Message_External* External_Parser::parseExternal_PointingRequest() {
    if (pointing == nullptr) {
        pointing = new PointingRequest();
    }
    
    // Transfer Header and Message ID
    pointing->bytes = messageHeader.bytes;
    pointing->iden = messageID;
    
    // Specific Data Members
    pointing->point = (PointEarthMoon) buf.getInt();
    
    return pointing;
}

Message_External* External_Parser::parseExternal_SolutionMessage() {
    if (solution == nullptr) {
        solution = new SolutionMessage();
    }
    
    // Transfer Header and Message ID
    solution->bytes = messageHeader.bytes;
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
