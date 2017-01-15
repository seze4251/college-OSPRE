//
//  ByteBuffer.cpp
//  ByteBuffer
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <string>
#include <iostream>

#include "ByteBuffer.h"

ByteBuffer::ByteBuffer(int capacity) {
    std::cout << "ByteBuffer Constructor" << std::endl;
    buf = new char[capacity];
    currentPos = buf;
    this->capacity = capacity;
    size = 0;
}

ByteBuffer::~ByteBuffer() {
    delete[] buf;
}

void ByteBuffer::clear() {
    currentPos = buf;
    size = 0;
}

// verify - looks right
void ByteBuffer::compact() {
    if (size == 0) {
        clear();
    } else {
        memcpy(buf, currentPos, size);
        currentPos = buf;
    }
}

// verify - looks right so long as size is kept accurate
void ByteBuffer::flip() {
    if (buf + size == currentPos) {
        currentPos = buf;
    } else {
        currentPos = buf + size;
    }
}

int ByteBuffer::position() {
    return (int) (currentPos-buf);
}


void ByteBuffer::positionWrite(int written) {
    currentPos += written;
    size -= written;
    
}

void ByteBuffer::positionRead(int read) {
    currentPos += read;
    size += read;
}

void ByteBuffer::rewind(int length) {
    currentPos -= length;
    size += length;
}

char ByteBuffer::get() {
    if (size == 0) {
        // TODO: add throw of Exception
        return '\0';
    }
    
    char c = *currentPos;
    size--;
    currentPos++;
    return c;
}

void ByteBuffer::put(char c) {
    // Is there space to put char in?
    if (size == capacity) {
        // TODO: add throw of Exception
        return;
    }
    
    *currentPos = c;
    currentPos++;
    size++;
}

int ByteBuffer::getInt() {
    if (remaining() < sizeof (int)) {
        // TODO: throw exception - there is not enough data to extract an int.
        return 0;
    }
    
    int val = *currentPos;
    currentPos += sizeof (int);
    size -= sizeof (int);
    return val;
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************

void ByteBuffer::putInt(int i) {
    
}

long ByteBuffer::getLong() {
    return (long) 0;
}

void ByteBuffer::putLong(long d) {
    
}


void ByteBuffer::put(char * c, int length) {
    
}







