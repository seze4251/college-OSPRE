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
    int used() {return size;}
    int remaining() {return (capacity - size);}
    
    int position();
    void positionWrite(int length);
    void positionRead(int length);
    void rewind(int length);
    
    char get();
    void put(char c);
    
    int getInt();
    void putInt(int i);
    
    long getLong();
    void putLong(long d);
    
    double getDouble();
    void putDouble(double d);
    
    char* getBuffer() {return currentPos;}
    
    void put(char* c, int length);
    //void get(int length);
    
    void printBuffer();
    
private:
    char *buf;
    char *currentPos;
    int size;
    int capacity;
    
};

#endif
