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
    if (size < sizeof(int)) {
        // TODO: add throw of exception
        std::cout << "Should Throw Exception in getInt" << std::endl;
        return 0;
    }
    
    int i;
    //char* ptr = (char*) &i;
    memcpy(&i, currentPos, sizeof(int));
    size -= sizeof(int);
    currentPos += sizeof(int);
    //i = ntohl(i);
    return i;
}



void ByteBuffer::putInt(int i) {
    if ((size + sizeof(int)) > capacity) {
        // TODO: add throw of Exception
        std::cout << "Should Throw Exception in putInt" << std::endl;
        return;
    }
    
   // i = htonl(i); // convert from host to network format
    //char* ptr = (char*) &i;
    memcpy(currentPos, &i, sizeof(int));
    size += sizeof(int);
    currentPos += sizeof(int);
}

void ByteBuffer::putLong(long i) {
    if ((size + sizeof(long)) > capacity) {
        // TODO: add throw of Exception
        std::cout << "Should Throw Exception in putLong" << std::endl;
        return;
    }
    
   // i = htonl(i); // convert from host to network format
    //char* ptr = (char*) &i;
    memcpy(currentPos, &i, sizeof(long));
    size += sizeof(long);
    currentPos += sizeof(long);
}

long ByteBuffer::getLong() {
    if (size < sizeof(long)) {
        // TODO: add throw of exception
        std::cout << "Should Throw Exception in getLong" << std::endl;
        return 0;
    }
    
    long i;
    //char* ptr = (char*) &i;
    memcpy(&i, currentPos, sizeof(long));
    size -= sizeof(long);
    currentPos += sizeof(long);
   // i = ntohl(i);
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
    if (length < 0) {
        //TODO: Throw Exception
        return;
    }
    
    if ((size + length) > capacity) {
        // TODO: add throw of Exception
        return;
    }
    
    memcpy(currentPos, c, length);
    
    currentPos += length;
    size += length;
}

void ByteBuffer::get(char* location, int length) {
    if (size < length) {
        // TODO: add throw of exception
        std::cout << "Should Throw Exception in get(char*, int)" << std::endl;
        return;
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





