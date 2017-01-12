//
//  Builder.cpp
//  Builder
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include "Builder.h"
#include <iostream>

Builder::Builder(ByteBuffer &bufParam) : buf(bufParam) {
    std::cout << "Builder Constructor" << std::endl;
}

Builder::~Builder() {
    
}

// Current Message Header
// Message Header
// Message ID
// Message Length
void Builder::createHeader(int length, MessageID msgID) {
    buf.putInt((int) msgID);
    buf.putInt(length);
}

void Builder::buildCaptureImageRequest(DataRequest &msg) {
   // Check Buffer Has Enough Room
    if (buf.remaining() < sizeof(CaptureImageRequest)) {
        //TODO: Throw Exception Here
        return;
    }
    
    createHeader(sizeof(CaptureImageRequest), I_CaptureImageRequest);
    buf.putLong(msg.timeStamp);
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************


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

void Builder::buildProccessHealthAndStatusRequest(ProccessHealthAndStatusRequest &msg) {
    
}

void Builder::buildProccessHealthAndStatusResponse(ProccessHealthAndStatusResponse &msg) {
    
}

void Builder::buildSolutionMessage(SolutionMessage &msg) {
    
}






