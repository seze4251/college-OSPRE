//
//  ByteBuffer.h
//  ByteBuffer
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef BYTEBUFFER_H
#define BYTEBUFFER_H

#include "ErrorCode.h"

class ByteBuffer {
public:
    //Constructor
    ByteBuffer(int capacity);
    
    //Destructor
    ~ByteBuffer();
    
    ErrorCode clear();
    
    ErrorCode compact();
    
    ErrorCode flip();
    
    ErrorCode position();
    
    ErrorCode limit();
    
    ErrorCode getInt();
    ErrorCode putInt(int i);
    
    ErrorCode get();
    ErrorCode put(char c);
    
private:
    char *buf;
    int length;
    char *head;
    char *tail;
};


#endif
