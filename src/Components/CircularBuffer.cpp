//
//  CircularBuffer.cpp
//  CircularBuffer
//
//  Created by Seth on 01/31/2017.
//  Copyright © 2017 Seth. All rights reserved.
//

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
    std::cout << "Starting CircularBuffer Destructor" << std::endl;
  /*  try {
        if (bufferHead) {
            try {
                delete bufferHead;
            } catch (std::exception exception) {
                std::cout << "Error: " << exception.what() << std::endl;
            } catch (...) {
                std::cout << "Error: Unkown type of exception caught" << std::endl;
                throw;
            }
        }
    } catch (std::exception) {
        std::cout << "Cannot do if statement on buffer head" << std::endl;
        throw;
    } */
    std::cout << "Ending CircularBuffer Destructor" << std::endl;
}

void CircularBuffer::put(DataMessage* msg) {
    // Check for Invalid Input
    if (msg == nullptr) {
        throw "CircularBuffer::put() Data Message Input equals nullptr";
    }
    
    if (msg->timeStamp < 0) {
        throw "CircularBuffer::put() Data Message has a negative timestap, invalid";
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
            foundMessage = true;
            break;
        }
    }
    
    if (foundMessage == false) {
        throw "CircularBuffer::get() DataMessage Not Found in buffer";
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




