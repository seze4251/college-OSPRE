//
//  Builder.cpp
//  Builder
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include "External_Builder.h"
#include <iostream>

unsigned int External_Builder::sequence : 14;

External_Builder::External_Builder(ByteBuffer& bufParam) : buf(bufParam) {
    std::cout << "External_Builder Constructor" << std::endl;
    sequence = 0;
}

External_Builder::~External_Builder() {
    
}

void External_Builder::buildExternal_DataMessage(External_DataMessage&msg) {
    
    // Purposefully overflow at around 65,000
    msg.packetSequence = sequence++;
    
    if (buf.remaining() < 7 + msg.packetDataLength) {
        //TODO: Throw Exception Here
        std::cout << "External_Builder::buildExternal_DataMessage Should Throw Exception here!, need to implement" << std::endl;
        return;
    }
    
    // Put Header
    buf.put(msg.bytes, 6);
    
    // Put Message ID
    buf.putInt((int) msg.iden);
    
    // Put Ephem
    for (int i = 0; i < 3; i++) {
        buf.putDouble(msg.ephem[i]);
    }
    
    // Put Quat
    for (int i = 0; i < 4; i++) {
        buf.putDouble(msg.quat[i]);
    }
    
    // Put Angular Velocity
    for (int i = 0; i < 3; i++) {
        buf.putDouble(msg.angularVelocity[i]);
    }
    
    // Time
    buf.putDouble(msg.satTime);
    
    // Sun Angle
    buf.putDouble(msg.sunAngle);
    
    // Sleep
    buf.put(msg.sleep);
    
}

void External_Builder::buildExternal_OSPREStatus(External_OSPREStatus&msg) {
    
    // Purposefully overflow at around 65,000
    msg.packetSequence = sequence++;
    
    // Update Message Length because Status Message has Varible length
    msg.updatePacketDataLength();
    
    if (buf.remaining() < 7 + msg.packetDataLength) {
        //TODO: Throw Exception Here
        std::cout << "External_Builder::buildExternal_DataMessage Should Throw Exception here!, need to implement" << std::endl;
        return;
    }
    
    // Put Header
    buf.put(msg.bytes, 6);
    
    // Put Message ID
    buf.putInt((int) msg.iden);
    
    // Put Error Messages
    for (std::vector<ProcessError>::iterator it = msg.error.begin(); it != msg.error.end(); it++ ) {
        buf.putInt((int) (*it));
    }
    
    
}

void External_Builder::buildExternal_PointingRequest(External_PointingRequest& msg) {
    
    // Purposefully overflow at around 65,000
    msg.packetSequence = sequence++;
    
    if (buf.remaining() < 7 + msg.packetDataLength) {
        //TODO: Throw Exception Here
        std::cout << "External_Builder::buildExternal_DataMessage Should Throw Exception here!, need to implement" << std::endl;
        return;
    }
    
    // Put Header
    buf.put(msg.bytes, 6);
    
    // Put Message ID
    buf.putInt((int) msg.iden);
    
    // Put Pointing Request Message
    buf.putInt((int) msg.point);
    
}


void External_Builder::buildExternal_SolutionMessage(External_SolutionMessage& msg) {
    
    // Purposefully overflow at around 65,000
    msg.packetSequence = sequence++;
    
    if (buf.remaining() < 7 + msg.packetDataLength) {
        //TODO: Throw Exception Here
        std::cout << "External_Builder::buildExternal_DataMessage Should Throw Exception here!, need to implement" << std::endl;
        return;
    }
    
    // Put Header
    buf.put(msg.bytes, 6);
    
    // Put Message ID
    buf.putInt((int) msg.iden);
    
    // position
    for (int i = 0; i < 3; i++) {
        buf.putDouble(msg.position[i]);
    }
    
    // position error
    for (int i = 0; i < 3; i++) {
        buf.putDouble(msg.positionError[i]);
    }
    
    // velocity
    for (int i = 0; i < 3; i++) {
        buf.putDouble(msg.velocity[i]);
    }
    
    // velocity error
    for (int i = 0; i < 3; i++) {
        buf.putDouble(msg.velocityError[i]);
    }
    
    // earthScMoonAngle
    buf.putDouble(msg.earthScMoonAngle);
}

