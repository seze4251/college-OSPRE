//
//  Builder.cpp
//  Builder
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include "Builder.h"
#include <iostream>

Builder::Builder(ByteBuffer& bufParam) : buf(bufParam) {
    std::cout << "Builder Constructor" << std::endl;
}

Builder::~Builder() {
    
}

// Current Message Header
// int Message ID
// int Message Length
// int Time Stamp

void Builder::createHeader(int length, MessageID msgID, time_t timeStamp) {
    buf.putInt((int) msgID);
    buf.putInt(length);
    buf.putLong((long) timeStamp);
    //  std::cout << "Builder: Print Header msgID: " << msgID << " length: " << length << " timeStamp: " << timeStamp << std::endl;
    // buf.printBuffer();
}

void Builder::buildProcessHealthAndStatusRequest(ProcessHealthAndStatusRequest &msg) {
    int messageSize = HEADER_MESSAGE_SIZE;
    if (buf.remaining() < messageSize) {
        //TODO: Throw Exception Here
        std::cout << "Builder::buildProcessHealthAndStatusRequest Should Throw Exception here!, need to implement" << std::endl;
        return;
    }
    
    createHeader(messageSize, msg.iden, msg.timeStamp);
}

void Builder::buildProcessHealthAndStatusResponse(ProcessHealthAndStatusResponse &msg) {
    int errorSize = msg.error.size();
    
    int messageSize = errorSize * sizeof(int) + HEADER_MESSAGE_SIZE;
    if (buf.remaining() < messageSize) {
        //TODO: Throw Exception Here
        std::cout << "Builder::buildProcessHealthAndStatusResponse: Should Throw Exception here!, need to implement" << std::endl;
        return;
    }
    
    createHeader(messageSize, msg.iden, msg.timeStamp);
    for (std::vector<ProcessError>::iterator it = msg.error.begin(); it != msg.error.end(); it++ ) {
        buf.putInt((int) (*it));
    }
}

void Builder::buildCaptureImageRequest(CaptureImageRequest &msg) {
    int messageSize = HEADER_MESSAGE_SIZE + 3*sizeof(long) + sizeof(int);
    // Check Buffer Has Enough Room
    if (buf.remaining() < messageSize) {
        //TODO: Throw Exception Here
        std::cout << "Builder::buildCaptureImageRequest Should Throw Exception here!, need to implement" << std::endl;
        return;
    }
    
    createHeader(messageSize, msg.iden, msg.timeStamp);
    buf.putInt((int) msg.point);
    
    for (int i = 0; i < 3; i++) {
        buf.putDouble(msg.estimatedPosition[i]);
    }
    
}

void Builder::buildDataMessage(DataMessage &msg) {
    int messageSize = HEADER_MESSAGE_SIZE + 12*sizeof(long) + 1;
    // Check Buffer Has Enough Room
    if (buf.remaining() < messageSize) {
        //TODO: Throw Exception Here
        std::cout << "Builder::buildDataMessage Should Throw Exception here!, need to implement" << std::endl;
        return;
    }
    
    createHeader(messageSize, msg.iden, msg.timeStamp);
    
    // ephem
    for (int i = 0; i < 3; i++) {
        buf.putDouble(msg.ephem[i]);
    }
    
    // quat
    for (int i = 0; i < 4; i++) {
        buf.putDouble(msg.quat[i]);
    }
    
    // angularVelocity
    for (int i = 0; i < 3; i++) {
        buf.putDouble(msg.angularVelocity[i]);
    }
    
    // satTime
    buf.putLong(msg.satTime);
    
    // sunAngle
    buf.putDouble(msg.sunAngle);
    
    buf.put((char) msg.sleep);
    
}

void Builder::buildOSPREStatus(OSPREStatus &msg) {
    int errorSize = msg.error.size();
    
    int messageSize = errorSize * sizeof(int) + HEADER_MESSAGE_SIZE;
    if (buf.remaining() < messageSize) {
        //TODO: Throw Exception Here
        std::cout << "Builder::buildOSPREStatus Should Throw Exception here!, need to implement" << std::endl;
        return;
    }
    
    createHeader(messageSize, msg.iden, msg.timeStamp);
    
    for (std::vector<ProcessError>::iterator it = msg.error.begin(); it != msg.error.end(); it++ ) {
        buf.putInt((int) (*it));
    }
    
}

void Builder::buildPointingRequest(PointingRequest &msg) {
    int messageSize = HEADER_MESSAGE_SIZE + sizeof(int);
    if (buf.remaining() < messageSize) {
        //TODO: Throw Exception Here
        std::cout << "Builder::buildPointingRequest Should Throw Exception here!, need to implement" << std::endl;
        return;
    }
    
    createHeader(messageSize, msg.iden, msg.timeStamp);
    buf.putInt((int) msg.point);
}


void Builder::buildSolutionMessage(SolutionMessage &msg) {
    int messageSize =HEADER_MESSAGE_SIZE +  13*sizeof(long);
    if (buf.remaining() < messageSize) {
        //TODO: Throw Exception Here
        std::cout << "Builder::buildSolutionMessage Should Throw Exception here!, need to implement" << std::endl;
        return;
    }
    
    createHeader(messageSize, msg.iden, msg.timeStamp);
    
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

void Builder::buildProcessedImageMessage(ProcessedImageMessage &msg) {
    int messageSize = HEADER_MESSAGE_SIZE + 2*sizeof(long) + sizeof(int);
    if (buf.remaining() < messageSize) {
        //TODO: Throw Exception Here
        std::cout << "Builder::buildProcessedImageMessage Should Throw Exception here!, need to implement" << std::endl;
        return;
    }
    
    createHeader(messageSize, msg.iden, msg.timeStamp);
    
    buf.putDouble(msg.distance);
    buf.putDouble(msg.error);
    buf.putInt(msg.point);
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************
void Builder::buildImageAdjustment(ImageAdjustment &msg) {
    int messageSize = HEADER_MESSAGE_SIZE;
    if (buf.remaining() < messageSize) {
        //TODO: Throw Exception Here
        std::cout << "Builder::buildImageAdjustment Should Throw Exception here!, need to implement" << std::endl;
        return;
    }
    
    createHeader(messageSize, msg.iden, msg.timeStamp);
    
}

// TODO: Find size of Image Message
void Builder::buildImageMessage(ImageMessage &msg) {
    int messageSize = msg.currentImageSize + HEADER_MESSAGE_SIZE + sizeof(int);
    
    if (buf.remaining() < messageSize) {
        //TODO: Throw Exception Here
        std::cout << "Builder::buildImageMessage Should Throw Exception here!, need to implement" << std::endl;
        return;
    }
    
    createHeader(messageSize, msg.iden, msg.timeStamp);
    buf.putInt((int) msg.point);
    buf.put(msg.getImagePointer(), msg.currentImageSize);
}




