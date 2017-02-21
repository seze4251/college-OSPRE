//
//  ByteBuffer.cpp
//  ByteBuffer
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <string>
#include <iostream>
#include <arpa/inet.h>

#include "ByteBuffer.h"

ByteBuffer::ByteBuffer(int capacity) {
    std::cout << "ByteBuffer Constructor" << std::endl;
    if (capacity <= 0) {
        throw "ByteBuffer::ByteBuffer() Capacity is less than or equal to 0";
    }
    
    buf = new char[capacity];
    currentPos = buf;
    this->capacity = capacity;
    size = 0;
}

ByteBuffer::~ByteBuffer() {
    if (buf) {
        delete[] buf;
    }
}

void ByteBuffer::clear() {
    currentPos = buf;
    size = 0;
}

void ByteBuffer::compact() {
    if (size == 0) {
        clear();
    } else {
        memcpy(buf, currentPos, size);
        currentPos = buf;
    }
}

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
    if (written < 0) {
        throw "ByteBuffer::positionWrite() Input is less than 0, cannot write less than 0";
    }
    
    if (size - written < 0) {
        throw "ByteBuffer::position() size can not decrease below 0";
    }
    
    currentPos += written;
    size -= written;
    
}

void ByteBuffer::positionRead(int read) {
    if (read < 0) {
        throw "ByteBuffer::position() Input is less than 0, cannot read less than 0";
    }
    
    if (size + read > capacity) {
        throw "ByteBuffer::position() trying to increase the size to be greater than the capacity of buffer";
    }
    
    currentPos += read;
    size += read;
}

void ByteBuffer::rewind(int length) {
    if (length < 0) {
        throw "ByteBuffer::rewind() Input is less than 0, cannot rewind less than 0";
    }
    
    if ((size + length) > capacity) {
        throw "ByteBuffer::rewind() ByteBuffer.size can not increase above capacity";
    }
    
    if (currentPos - length < buf) {
        throw "ByteBuffer::rewind() current position can not go out of the ByteBuffer's allocated memory";
    }
    
    currentPos -= length;
    size += length;
}

char ByteBuffer::get() {
    if (size <= 0) {
        throw "ByteBuffer::get() Nothing in Byte Buffer to get";
    }
    
    char c = *currentPos;
    size--;
    currentPos++;
    return c;
}

void ByteBuffer::put(char c) {
    if (size == capacity) {
        throw "ByteBuffer::put() Byte Buffer is full";
    }
    
    if (capacity  < (int) (size + sizeof(char))) {
        throw "ByteBuffer::put(char) ByteBuffer is full";
    }

    *currentPos = c;
    currentPos++;
    size++;
}

int ByteBuffer::getInt() {
    if (size < (int) sizeof(int)) {
        throw "ByteBuffer::getInt() No int in Buffer";
    }
    
    int i;
    memcpy(&i, currentPos, sizeof(int));
    size -= sizeof(int);
    currentPos += sizeof(int);
    return i;
}



void ByteBuffer::putInt(int i) {
    if ( capacity  < (int) (size + sizeof(int))) {
        throw "ByteBuffer::putInt() No Room to put int into Buffer";
    }
    
    if (size == capacity) {
        throw "ByteBuffer::putInt() ByteBuffer is full";
    }
    
    memcpy(currentPos, &i, sizeof(int));
    size += sizeof(int);
    currentPos += sizeof(int);
}

void ByteBuffer::putLong(long i) {
    if (capacity < (size + (int) sizeof(long))) {
        throw "ByteBuffer::putLong() No Room to put long into Buffer";
    }
    
    if (size == capacity) {
        throw "ByteBuffer::putLong() ByteBuffer is full";
    }
    
    memcpy(currentPos, &i, sizeof(long));
    size += sizeof(long);
    currentPos += sizeof(long);
}

long ByteBuffer::getLong() {
    if (size < (int) sizeof(long)) {
        throw "ByteBuffer::getLong() No long in Buffer";
    }
    
    long i;
    memcpy(&i, currentPos, sizeof(long));
    size -= sizeof(long);
    currentPos += sizeof(long);
    return i;
}

// Keeps 6 decimals of percision
double ByteBuffer::getDouble() {
    long i = getLong();
    double d = (double) (i / 1000000.0);
    return d;
}

// Keeps 6 decimals of percision
void ByteBuffer::putDouble(double d) {
    long i = (long) (d * 1000000.0);
    putLong(i);
}

void ByteBuffer::put(char* c, int length) {
    if (length <= 0) {
        throw "ByteBuffer::put(char*, int) Can not put length <=0 into buffer";
    }
    
    if (size == capacity) {
        throw "ByteBuffer::put(char*, int) ByteBuffer is full";
    }
    
    if (capacity < (size + length) ) {
        throw "ByteBuffer::put(char*, int) Not enough size in Buffer to put message";
    }
    
    if (c == nullptr) {
        throw "ByteBuffer::get(char*, int) Passed in null ptr";
    }
    
    memcpy(currentPos, c, length);
    
    currentPos += length;
    size += length;
}

void ByteBuffer::get(char* location, int length) {
    if (size < length) {
        throw "ByteBuffer::get(char*, int) Message does not exist within Buffer";
    }
    
    if (length < 0) {
        throw "ByteBuffer::get(char*, int) Length is less than 0";
    }
    
    if (location == nullptr) {
        throw "ByteBuffer::get(char*, int) Passed in null ptr";
    }
    
    
    memcpy(location, currentPos, length);
    size -= length;
    currentPos += length;
}

void ByteBuffer::printBuffer() {
    std::cout<< "Size: " << size << " Capacity: " << capacity<< " <";
    
    if (currentPos == buf) {
        std::cout << "printBuffer: currentPos == buf, nothing in buffer" << std::endl;
    }
    
    for (char* ptr = buf; ptr < currentPos; ptr++) {
        printf("%x",*ptr);
    }
    std::cout << ">"<< std::endl;
}





