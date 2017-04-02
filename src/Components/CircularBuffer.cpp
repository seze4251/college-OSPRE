//
//  CircularBuffer.cpp
//  CircularBuffer
//
//  Created by Seth on 01/31/2017.
//  Copyright © 2017 Seth. All rights reserved.
//

#include <cstring>
#include <string.h>
#include <iostream>
#include <exception>

#include "CircularBuffer.h"

// Constructor
CircularBuffer::CircularBuffer(int numDataMessage) {
    if (numDataMessage <= 0) {
        throw "CircularBuffer::CircularBuffer() Amount of Data messages to hold is <= 0";
    }
    
    bufferHead = new DataMessage[numDataMessage];
    insert = bufferHead;
    nextSimMessage = bufferHead;
    buffSize = numDataMessage;
    
    // Initalize Loop Parameters
    DataMessage* it;
    int j;
    
    // Zero out all buffer loop timestamps
    for (it = bufferHead, j = 0; j < numDataMessage; it++, j++) {
        it->satTime = 0;
    }
}

//Destructor
CircularBuffer::~CircularBuffer() {
    if (bufferHead) {
            delete[] bufferHead;
        }
 }

void CircularBuffer::put(DataMessage* msg) {
    // Check for Invalid Input
    if (msg == nullptr) {
        throw "CircularBuffer::put() Data Message Input equals nullptr";
    }
    
    if (msg->satTime < 0) {
        throw "CircularBuffer::put() Data Message has a negative timestap, invalid";
    }
    
    // At the end of the buffer?, Wrap around to begining
    if ((bufferHead + buffSize) == insert) {
        insert = bufferHead;
    }
    
    // Copy the Data Message into the buffer
    memcpy((void*) insert, (void*) msg, sizeof(DataMessage));
    
    // move the insert pointer foward
    insert++;
}

DataMessage* CircularBuffer::get(time_t satTime) {
    // Check Input
    if (satTime <= 0) {
        throw "CircularBuffer::get() Invalid Time Stamp";
    }
    
    // Initalize Loop Parameters
    bool foundMessage = false;
    DataMessage* it;
    int j;
    
    for (it = bufferHead, j = 0; j < buffSize; j++, it++) {
        if (it->satTime == satTime) {
            foundMessage = true;
            break;
        }
    }
    
    if (foundMessage == false) {
        throw "CircularBuffer::get() DataMessage Not Found in buffer";
    }
    
    return it;
}

//**************************
// ASSUMPTIONS
// 1: We will not have enough DataMessages in SIM mode to overflow the Circular Buffer
// 2: Every DataMessage in SIM mode corresponds to the next image that is going to be read in
// 3:  This method is only going to be used for SIM cases, not livemode in order to make testing easier
//***************************
DataMessage* CircularBuffer::getNextSimMessage() {
    return nextSimMessage++;
    
}

// This method is used to verify the ciruclar buffer
void CircularBuffer::printBuffer() {
    DataMessage* it;
    int j;
    
    std::cout << "Printing Circular Buffer Timestamps" << std::endl;
    
    for (it = bufferHead, j = 0; j < buffSize; j++, it++) {
        std::cout << it->satTime << std::endl;
    }
    
    std::cout << "Finished Printing Ciruclar Buffer" << std::endl;
}




