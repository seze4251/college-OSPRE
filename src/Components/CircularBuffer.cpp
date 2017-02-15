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
    if (numDataMessage <= 0) {
        throw "CircularBuffer::CircularBuffer() Amount of Data messages to hold is <= 0";
    }
    
    bufferHead = new DataMessage[numDataMessage];
    insert = bufferHead;
    buffSize = numDataMessage;
    
    // Initalize Loop Parameters
    DataMessage* it;
    int j;
    
    // Zero out all buffer loop timestamps
    for (it = bufferHead, j = 0; j < numDataMessage; it++, j++) {
        it->timeStamp = 0;
    }
}

//Destructor
CircularBuffer::~CircularBuffer() {
    if (bufferHead) {
        delete bufferHead;
    }
}

void CircularBuffer::put(DataMessage* msg) {
    // Check for Invalid Input
    if (msg == nullptr) {
        throw "CircularBuffer::put() Data Message Input equals nullptr";
    }
    
    // At the end of the buffer?, Wrap around to begining
    if ((bufferHead + buffSize * sizeof(DataMessage)) == insert) {
        insert = bufferHead;
    }
    
    // Copy the Data Message into the buffer
    memcpy((void*) insert, (void*) msg, sizeof(DataMessage));
    
    // move the insert pointer foward
    insert++;
}

DataMessage* CircularBuffer::get(time_t timeStamp) {
    // Check Input
    if (timeStamp <= 0) {
        throw "CircularBuffer::get() Invalid Time Stamp";
    }
    
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

// This method is used to verify the ciruclar buffer
void CircularBuffer::printBuffer() {
    DataMessage* it;
    int j;
    
    std::cout << "Printing Circular Buffer Timestamps" << std::endl;
    
    for (it = bufferHead, j = 0; j < buffSize; j++, it++) {
        std::cout << it->timeStamp << std::endl;

    }
    
    std::cout << "Finished Printing Ciruclar Buffer" << std::endl;
}




