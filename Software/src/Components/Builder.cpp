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

void Builder::buildProccessHealthAndStatusRequest(ProccessHealthAndStatusRequest &msg) {
    if (buf.remaining() < (sizeof(long) + 2*sizeof(int))) {
        //TODO: Throw Exception Here
        std::cout << "Builder::buildProccessHealthAndStatusRequest Should Throw Exception here!, need to implement" << std::endl;
        return;
    }
    
    createHeader((sizeof(long) + 2*sizeof(int)), msg.iden, msg.timeStamp);
}

void Builder::buildProccessHealthAndStatusResponse(ProccessHealthAndStatusResponse &msg) {
    if (buf.remaining() < (sizeof(long) + 3*sizeof(int))) {
        //TODO: Throw Exception Here
        std::cout << "Builder::buildProccessHealthAndStatusResponse: Should Throw Exception here!, need to implement" << std::endl;
        return;
    }
    
    createHeader((sizeof(long) + 3*sizeof(int)), msg.iden, msg.timeStamp);
    buf.putInt((int) msg.p_ID);
    std::cout << "Builder: buildResponseMessage, printing buffer:" << std::endl;
    buf.printBuffer();
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************

void Builder::buildCaptureImageRequest(DataRequest &msg) {
    // Check Buffer Has Enough Room
    if (buf.remaining() < sizeof(CaptureImageRequest)) {
        //TODO: Throw Exception Here
        return;
    }
    
    createHeader(sizeof(CaptureImageRequest), msg.iden, msg.timeStamp);
}

void Builder::buildDataRequest(DataRequest &msg) {
    
}

void Builder::buildEphemerisMessage(EphemerisMessage &msg) {
    
}

void Builder::buildImageAdjustment(ImageAdjustment &msg) {
    
}

void Builder::buildImageMessage(ImageMessage &msg) {
    
}

void Builder::buildOSPREStatus(OSPREStatus &msg) {
    
}

void Builder::buildPointingRequest(PointingRequest &msg) {
    
}


void Builder::buildSolutionMessage(SolutionMessage &msg) {
    
}






