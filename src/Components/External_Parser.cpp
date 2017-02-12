//
//  Parser.cpp
//  Parser
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <iostream>

#include "MessageSizes.h"
#include "External_Parser.h"

External_Parser::External_Parser(ByteBuffer &bufParam) : buf(bufParam), messageHeader(0, NA) {
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
    if (buf.used() < 10 ) {
        std::cout << "External_Parser::parseMessage no header left in buffer" << std::endl;
        return nullptr;
    }
    
    buf.get(messageHeader.header.bytes, EXTERNAL_HEADER_MESSAGE_SIZE);
    messageID = (MessageID) buf.getInt();
    
    std::cout<< "buf.used() = " << buf.used() << " 1+packetDataLength = " << (1 + messageHeader.header.header_struct.packetDataLength - sizeof(int)) << std::endl;
    
    // If there is a partial Message, rewind buffer and return null ptr
    if (buf.used() < (1 + messageHeader.header.header_struct.packetDataLength - sizeof(int)) ) {
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
    data->sunAngle = buf.getDouble();
    data->sleep = (bool) buf.get();
    
    return data;
}

Message_External* External_Parser::parseExternal_OSPREStatus() {
    if (status == nullptr) {
        status = new External_OSPREStatus(0);
    }
    
    // Transfer Header and Message ID
    memcpy(status->header.bytes, messageHeader.header.bytes, EXTERNAL_HEADER_MESSAGE_SIZE);
    status->iden = messageID;
    
    int messageBody = (messageHeader.header.header_struct.packetDataLength + 1 - sizeof(int)) / sizeof(int);
    std::cout << "Message Body = " << messageBody << "packetDataLength" << messageHeader.header.header_struct.packetDataLength << std::endl;
    
    for (int i = 0; i < messageBody; i++) {
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
