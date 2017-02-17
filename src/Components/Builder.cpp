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
    // Verify Length Parameter is valid
    if (length <= 0) {
        throw "Builder::createHeader() Length cannot <= 0";
    }
    
    buf.putInt((int) msgID);
    buf.putInt(length);
    buf.putLong((long) timeStamp);
}

void Builder::buildProcessHealthAndStatusRequest(ProcessHealthAndStatusRequest &msg) {
    int messageSize = HEADER_MESSAGE_SIZE;
    
    // Check Buffer Has Enough Room to write message
    if (buf.remaining() < messageSize) {
        throw "Builder::buildProcessHealthAndStatusRequest(), Not enough room to create message, write buffer full";
    }
    
    createHeader(messageSize, msg.iden, msg.timeStamp);
}

void Builder::buildProcessHealthAndStatusResponse(ProcessHealthAndStatusResponse &msg) {
    int messageSize = msg.error.size() * sizeof(int) + HEADER_MESSAGE_SIZE;
    
    // Check Buffer Has Enough Room to write message
    if (buf.remaining() < messageSize) {
        throw "Builder::buildProcessHealthAndStatusResponse() Not enough room to create message, write buffer full";
    }
    
    createHeader(messageSize, msg.iden, msg.timeStamp);
    for (std::vector<ProcessError>::iterator it = msg.error.begin(); it != msg.error.end(); it++ ) {
        buf.putInt((int) (*it));
    }
}

void Builder::buildCaptureImageRequest(CaptureImageRequest &msg) {
    int messageSize = HEADER_MESSAGE_SIZE + 3*sizeof(long) + sizeof(int);
    
    // Check Buffer Has Enough Room to write message
    if (buf.remaining() < messageSize) {
        throw "Builder::buildCaptureImageRequest() Not enough room to create message, write buffer full";
    }
    
    createHeader(messageSize, msg.iden, msg.timeStamp);
    buf.putInt((int) msg.point);
    
    for (int i = 0; i < 3; i++) {
        buf.putDouble(msg.estimatedPosition[i]);
    }
    
}

void Builder::buildDataMessage(DataMessage &msg) {
    int messageSize = HEADER_MESSAGE_SIZE + 12*sizeof(long) + 1;
    
    // Check Buffer Has Enough Room to write message
    if (buf.remaining() < messageSize) {
        throw "Builder::buildDataMessage() Not enough room to create message, write buffer full";
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
    int messageSize = msg.error.size() * sizeof(int) + HEADER_MESSAGE_SIZE;
    
    // Check Buffer Has Enough Room to write message
    if (buf.remaining() < messageSize) {
        throw "Builder::buildDataMessage() Not enough room to create message, write buffer full";
    }
    
    createHeader(messageSize, msg.iden, msg.timeStamp);
    
    for (std::vector<ProcessError>::iterator it = msg.error.begin(); it != msg.error.end(); it++ ) {
        buf.putInt((int) (*it));
    }
    
}

void Builder::buildPointingRequest(PointingRequest &msg) {
    int messageSize = HEADER_MESSAGE_SIZE + sizeof(int);
    
    // Check Buffer Has Enough Room to write message
    if (buf.remaining() < messageSize) {
        throw "Builder::buildPointingRequest() Not enough room to create message, write buffer full";
    }
    
    createHeader(messageSize, msg.iden, msg.timeStamp);
    buf.putInt((int) msg.point);
}


void Builder::buildSolutionMessage(SolutionMessage &msg) {
    int messageSize = HEADER_MESSAGE_SIZE +  13*sizeof(long);
    
    // Check Buffer Has Enough Room to write message
    if (buf.remaining() < messageSize) {
        throw "Builder::buildSolutionMessage() Not enough room to create message, write buffer full";
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
    int messageSize = HEADER_MESSAGE_SIZE + 4*sizeof(long) + sizeof(int);
    
    // Check Buffer Has Enough Room to write message
    if (buf.remaining() < messageSize) {
        throw "Builder::buildProcessedImageMessage() Not enough room to create message, write buffer full";
    }
    
    createHeader(messageSize, msg.iden, msg.timeStamp);
    
    buf.putDouble(msg.alpha);
    buf.putDouble(msg.beta);
    buf.putDouble(msg.theta);
    buf.putDouble(msg.pixel_error);
    buf.putInt(msg.point);
}

void Builder::buildImageMessage(ImageMessage &msg) {
    int messageSize = msg.currentImageSize + HEADER_MESSAGE_SIZE + 3 * sizeof(int) + sizeof(double);
    
    // Check Buffer Has Enough Room to write message
    if (buf.remaining() < messageSize) {
        throw "Builder::buildImageMessage() Not enough room to create message, write buffer full";
    }
    
    createHeader(messageSize, msg.iden, msg.timeStamp);
    buf.putInt((int) msg.point);
    buf.putInt(msg.cameraWidth);
    buf.putInt(msg.cameraHeight);
    buf.putDouble(msg.FOV);
    buf.put(msg.getImagePointer(), msg.currentImageSize);
}

// Todo: Implement in future when OSPRE gets camera funcitonality
void Builder::buildImageAdjustment(ImageAdjustment &msg) {
    int messageSize = HEADER_MESSAGE_SIZE;
    
    // Check Buffer Has Enough Room to write message
    if (buf.remaining() < messageSize) {
        throw "Builder::buildImageAdjustment() Not enough room to create message, write buffer full";
    }
    
    createHeader(messageSize, msg.iden, msg.timeStamp);
    
}

