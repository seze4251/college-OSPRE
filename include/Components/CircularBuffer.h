//
//  CircularBuffer.h
//  CircularBuffer
//
//  Created by Seth on 01/31/2017.
//  Copyright © 2017 Seth. All rights reserved.
//


#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include "DataMessage.h"

class CircularBuffer {
public:
    // Constructor
    CircularBuffer(int numDataMessage = 6*60);
    
    // Destructor
    ~CircularBuffer();
    
    // Public Methods
    void put(DataMessage* msg);
    DataMessage* get(time_t timeStamp);
    DataMessage* getNextSimMessage();
    void printBuffer();
    
private:
    // Buffer Pointers
    DataMessage* bufferHead;
    DataMessage* insert;
    DataMessage* nextSimMessage;
    
    //Buffer Constants
    int buffSize;
};

#endif
