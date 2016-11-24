//
//  ByteBuffer.h
//  ByteBuffer
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#ifndef BYTEBUFFER_H
#define BYTEBUFFER_H

class ByteBuffer {
public:
    //Constructor
    ByteBuffer(int capacity);
    
    //Destructor
    ~ByteBuffer();
    
    void clear();
    void compact();
    void flip();
    
    int* position();
    int remaining();
    
    void putIntoInsertionMode();
    void putIntoExtractionMode();
    
    char get();
    void put(char c);
    
    int getInt();
    int peakInt();
    int peakAheadInt();
    void putInt(int i);
    
    double getDouble();
    void putDouble(double d);
    
    char * get(int length);
    void put(char * c, int length);
    
   
    
private:
    char *buf;
    char *currentPos;
    int size;
    int capacity;
    
    bool insertionMode();
};

#endif
