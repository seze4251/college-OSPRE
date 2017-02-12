//
//  CircularBuffer.cpp
//  CircularBuffer
//
//  Created by Seth on 01/31/2017.
//  Copyright © 2017 Seth. All rights reserved.
//

#include <string.h>
#include <iostream>

#include "CircularBuffer.h"

// Constructor
CircularBuffer::CircularBuffer(int numDataMessage) {
    bufferHead = new DataMessage[numDataMessage];
    insert = bufferHead;
    buffSize = numDataMessage;
    
    // 0 out all time values because time values are initally set to current time
    // Initalize Loop Parameters
    DataMessage* it;
    int j;
    
    for (it = bufferHead, j = 0; j < numDataMessage; it++, j++) {
        it->timeStamp = 0;
    }
}

//Destructor
CircularBuffer::~CircularBuffer() {
    delete bufferHead;
}

// Public Methods
/*
 1. copy data message into
*/

void CircularBuffer::put(DataMessage* msg) {
    // If We are at the end of the buffer, Wrap around
    if (bufferHead + buffSize * sizeof(DataMessage) == insert) {
        insert = bufferHead;
    }
    
    // Copy the Data Message
    memcpy((void*) insert, (void*) msg, sizeof(DataMessage));
    
    //std::cout << "Circular Buffer Added Timestamp: " << msg->timeStamp << std::endl;
    
    insert++;
}

DataMessage* CircularBuffer::get(time_t timeStamp) {
    // Initalize Loop Parameters
    bool foundMessage = false;
    DataMessage* it;
    int j;
    
    for (it = bufferHead, j = 0; j < buffSize; j++, it++) {
        if (it->timeStamp == timeStamp) {
            std::cout << "CircularBuffer::get() Found Message Timestamp: " << timeStamp << std::endl;
            foundMessage = true;
            break;
        }
    }
    
    if (foundMessage == false) {
        // TODO: Throw exception here
        std::cout << "\n\n\nCircularBuffer::get() could not find Data Message\n\n\n" << std::endl;
        return nullptr;
    }
    
    return it;
}





