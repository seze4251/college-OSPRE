//
//  Builder.cpp
//  Builder
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include "Builder.h"

Builder::Builder(ByteBuffer& bufParam) : buf(bufParam) {}

Builder::~Builder() {}

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
    int messageSize = sizeof(int) + HEADER_MESSAGE_SIZE;
    
    // Check Buffer Has Enough Room to write message
    if (buf.remaining() < messageSize) {
        throw "Builder::buildProcessHealthAndStatusResponse() Not enough room to create message, write buffer full";
    }
    
    createHeader(messageSize, msg.iden, msg.timeStamp);
    buf.putInt((int) msg.error);
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
    int messageSize = HEADER_MESSAGE_SIZE + 14*sizeof(long) + 1;
    
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
    for (int i = 0; i < 3; i++) {
        buf.putDouble(msg.sunAngle[i]);
    }
    
    buf.put((char) msg.sleep);
    
}

void Builder::buildOSPREStatus(OSPREStatus &msg) {
    int messageSize = 2 * msg.error.size() * sizeof(int) + 2 * sizeof(int) + HEADER_MESSAGE_SIZE;
    
    // Check Buffer Has Enough Room to write message
    if (buf.remaining() < messageSize) {
        throw "Builder::buildDataMessage() Not enough room to create message, write buffer full";
    }
    
    createHeader(messageSize, msg.iden, msg.timeStamp);
    
    buf.putInt((int) msg.totalHealth);
    buf.putInt(msg.numProblemProcesses);
    
    std::vector<ProcessID>::iterator itPID;
    std::vector<ProcessError>::iterator itPError;
    
    for (itPID = msg.pID.begin(), itPError = msg.error.begin(); itPError != msg.error.end(); itPID++, itPError++ ) {
        buf.putInt((int) (*itPID));
        buf.putInt((int) (*itPError));
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
    int messageSize = msg.currentImageSize + HEADER_MESSAGE_SIZE + 5*sizeof(int) + 8*sizeof(double);
    
    // Check Buffer Has Enough Room to write message
    if (buf.remaining() < messageSize) {
        throw "Builder::buildImageMessage() Not enough room to create message, write buffer full";
    }
    
    createHeader(messageSize, msg.iden, msg.timeStamp);
    buf.putInt((int) msg.point);
    
    buf.putInt(msg.cameraWidth);
    buf.putInt(msg.cameraHeight);
    
    // pix_deg
    for (int i = 0; i < 2; i++) {
        buf.putDouble(msg.pix_deg[i]);
    }
    
    // cropCord
    for (int i = 0; i < 2; i++) {
        buf.putInt(msg.cropCoords[i]);
    }
    
    // estimated position
    for (int i = 0; i < 3; i++) {
        buf.putDouble(msg.estimatedPosition[i]);
    }
    
    // moon ephemeris
    for (int i = 0; i < 3; i++) {
        buf.putDouble(msg.moonEphem[i]);
    }
    
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

