//
//  ByteBuffer.cpp
//  ByteBuffer
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <string>
#include "ByteBuffer.h"

ByteBuffer::ByteBuffer(int capacity) {
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

void ByteBuffer::compact() {
    if (size == 0) {
        clear();
    } else {
        memcpy(buf, (currentPos - size), size);
        currentPos = buf + size;
    }
}

void ByteBuffer::flip() {
    currentPos = buf;
}

int ByteBuffer::position() {
    return (int) (currentPos-buf);
}

int ByteBuffer::remaining() {
    if ((currentPos - size) == buf) {
        return (capacity - size);
    } else {
        return size;
    }
}

bool ByteBuffer::insertionMode() {
    if ((currentPos - size) == buf) {
        return true;
    } else {
        return false;
    }
}

void ByteBuffer::putIntoInsertionMode() {
    
    if (!insertionMode()) {
        compact();
        flip();
    }
}

void ByteBuffer::putIntoExtractionMode() {
    if (insertionMode()) {
        flip();
    }
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

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************

int ByteBuffer::getInt() {
    return 0;
}

void ByteBuffer::putInt(int i) {
    
}

long ByteBuffer::getLong() {
    return (long) 0;
}

void ByteBuffer::putLong(long d) {
    
}

char * ByteBuffer::get(int bytes) {
    return NULL;
}

void ByteBuffer::put(char * c, int length) {
    
}









