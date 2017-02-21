//
//  testByteBuffer.cpp
//
//  Created by Seth on 02/14/2017.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <string>

#include "ByteBuffer.h"

/*
 Summary of Tests:
 Call ByteBuffer Concstructor with negative capacity
 Test charecter put() / get() functionality
 Test remaining()
 Test used()
 Test flip()
 Test compact()
 Test rewind()
 Test clear()
 Test Case: Partial Message
 Test Case: Write into buffer and Read from buffer
 Test Case: Rewind buffer, flip add more, flip back read, compact and read more
 Test putInt() / getInt()
 Test putLong() / getLong()
 Test putDouble / getDouble()
 Test put(char*) / get(char*)
 Test Inputs:
 void positionWrite(int length);
 void positionRead(int length);
 void put(char* c, int length);
 void get(char* location, int length);
 Attempt to overflow buffer in all put methods
 */

int main(int argc, char **argv) {
    std::cout << "\nTesting ByteBuffer Starting\n";
    bool passedAllTests = true;
    
    /*
     Call ByteBuffer Concstructor with negative capacity
     */
    bool bufConstruct = true;
    try {
        ByteBuffer buf_temp = ByteBuffer(-10);
    } catch (const char*){
        bufConstruct = false;
    }
    
    if (bufConstruct) {
        passedAllTests = false;
        std::cout << "Test 0.5, Can call ByteBuffer Constructor with negative number,Very Bad" << std::endl;
    }
    
    // Create ByteBuffer with average capacity for testing
    ByteBuffer buf = ByteBuffer(1024*1024);
    
    /*
     Test charecter put() / get() functionality
     Test remaining()
     Test used()
     Test flip()
     Test compact()
     Test rewind()
     Test clear()
     
     Specific Cases:
     Test Case: Partial Message
     Test Case: Write into buffer and Read from buffer
     Test Case: Rewind buffer, flip add more, flip back read, compact and read more
     */
    
    int length = buf.remaining();
    
    // Test void put(char c);
    buf.put('S');
    
    if (buf.used() != sizeof(char)) {
        passedAllTests = false;
        std::cout << "Test 1: ByteBuffer::put(char) is not functioning normally" << std::endl;
    }
    
    // Flip
    buf.flip();
    
    // Test char get();
    char c = buf.get();
    if (buf.used() != 0 && c != 'S') {
        passedAllTests = false;
        std::cout << "Test 2: ByteBuffer::put(char)/get(char) is not functioning normally" << std::endl;
    }
    
    //Compact and Flip
    buf.compact();
    buf.flip();
    
    if (buf.used() != 0) {
        passedAllTests = false;
        std::cout << "Test 3: ByteBuffer::put(char)/get is not functioning normally" << std::endl;
    }
    
    int messageLength = 5;
    buf.put('S');
    buf.put('E');
    buf.put('T');
    buf.put('H');
    
    buf.flip();
    
    char name[5];
    bool test2 = false;
    
    for (int i = 0; i < 5; i++) {
        try {
            name[i] = buf.get();
        } catch (const char* exception) {
            test2 = true;
        }
    }
    
    if (!test2) {
        passedAllTests = false;
        std::cout << "Test 4: ByteBuffer::get did not throw exception" << std::endl;
    }
    
    if (buf.remaining() != 0 && buf.used() != 0) {
        passedAllTests = false;
        std::cout << "Test 5: ByteBuffer::used and remaining aren't working as expected" << std::endl;
    }
    
    buf.rewind(4);
    
    if (buf.remaining() != (1024*1024) - 4 && buf.used() != 4) {
        passedAllTests = false;
        std::cout << "Test 6: Rewind not working as expected" << std::endl;
    }
    
    c = buf.get();
    
    if (c != 'S') {
        passedAllTests = false;
        std::cout << "Test 7: Rewind not working as expected / sequence incorrect" << std::endl;
    }
    
    buf.compact();
    buf.flip();
    
    buf.put('Y');
    
    if (buf.used() != 4) {
        passedAllTests = false;
        std::cout << "Test 8: Rewind not working as expected / sequence incorrect" << std::endl;
    }
    
    buf.flip();
    
    name[0] = buf.get();
    name[1] = buf.get();
    
    buf.compact();
    
    name[2] = buf.get();
    name[3] = buf.get();
    
    if (name[0] != 'E' && name[1] != 'T' && name[2] != 'H' && name[3] != 'Y') {
        passedAllTests = false;
        std::cout << "Test 8: Rewind not working as expected / sequence incorrect" << std::endl;
    }
    
    buf.clear();
    
    /*
     Test putInt() / getInt()
     Test putLong() / getLong()
     Test putDouble / getDouble()
     Test put(char*) / get(char*)
     Test put/get(char*) for bad inputs
     */
    
    // Test int methods
    buf.putInt(5);
    
    if (buf.used() != sizeof(int)) {
        passedAllTests = false;
        std::cout << "Test 9: ByteBuffer::put(int) is not functioning normally" << std::endl;
    }
    
    // Flip
    buf.flip();
    
    int testInt = buf.getInt();
    
    if (buf.used() != 0 && testInt != 5) {
        passedAllTests = false;
        std::cout << "Test 10: ByteBuffer::get(int) is not functioning normally" << std::endl;
    }
    
    // Test long methods
    buf.putLong(3434);
    
    if (buf.used() != sizeof(long)) {
        passedAllTests = false;
        std::cout << "Test 11: ByteBuffer::put(long) is not functioning normally" << std::endl;
    }
    
    // Flip
    buf.flip();
    
    long testLong = buf.getLong();
    
    if (buf.used() != 0 && testLong != 3434) {
        passedAllTests = false;
        std::cout << "Test 12: ByteBuffer::get(long) is not functioning normally" << std::endl;
    }
    
    // Test Double methods
    // Maximum amount of decmils = 6
    buf.putDouble(555.3435);
    
    if (buf.used() != sizeof(double)) {
        passedAllTests = false;
        std::cout << "Test 13: ByteBuffer::put(double) is not functioning normally" << std::endl;
    }
    
    // Flip
    buf.flip();
    
    double testDouble = buf.getDouble();
    
    if (buf.used() != 0 && testLong != 555.3435) {
        passedAllTests = false;
        std::cout << "Test 14: ByteBuffer::get(double) is not functioning normally" << std::endl;
    }
    
    // Test char*
    // do stuff
    std::string stringA = "Hello!";
    int bytes = 7;
    
    char* cstr = new char[stringA.length() + 1];
    strcpy(cstr, stringA.c_str());
    
    buf.put(cstr, bytes);
    
    if (buf.used() != bytes) {
        passedAllTests = false;
        std::cout << "Test 15: ByteBuffer::put(char*) is not functioning normally" << std::endl;
    }
    
    // Flip
    buf.flip();
    
    char result[bytes];
    buf.get(result, bytes);
    
    buf.compact();
    buf.flip();
    
    if (buf.used() != 0 && ::strcmp(result, cstr) != 0) {
        passedAllTests = false;
        std::cout << "Test 16: ByteBuffer::get(double) is not functioning normally" << std::endl;
    }
    
    /*
     Test Inputs:
     void positionWrite(int length);
     void positionRead(int length);
     void put(char* c, int length);
     void get(char* location, int length);
     */
    
    // Position Write
    bool temp = true;
    try {
        buf.positionWrite(-5);
    } catch (const char*){
        temp = false;
    }
    
    if (temp) {
        passedAllTests = false;
        std::cout << "Test 17: Position Write Failed Test" << std::endl;
    }
    
    // Position Read
    temp = true;
    try {
        buf.positionRead(-10);
    } catch (const char*){
        temp = false;
    }
    
    if (temp) {
        passedAllTests = false;
        std::cout << "Test 18: Position Read Failed Test" << std::endl;
    }
    
    // put(char*)
    temp = true;
    try {
        buf.put(cstr, -5);
    } catch (const char*){
        temp = false;
    }
    
    if (temp) {
        passedAllTests = false;
        std::cout << "Test 19: put(char*)" << std::endl;
    }
    
    // put(char*)
    temp = true;
    try {
        buf.put(nullptr, bytes);
    } catch (const char*){
        temp = false;
    }
    
    if (temp) {
        passedAllTests = false;
        std::cout << "Test 20: put(char*)" << std::endl;
    }
    
    buf.put(cstr, bytes);
    
    // get(char*)
    temp = true;
    try {
        buf.get(nullptr, 1);
    } catch (const char*){
        temp = false;
    }
    
    if (temp) {
        passedAllTests = false;
        std::cout << "Test 21: get(char*)" << std::endl;
    }
    
    // get(char*)
    temp = true;
    try {
        buf.put(cstr, -10);
    } catch (const char*){
        temp = false;
    }
    
    if (temp) {
        passedAllTests = false;
        std::cout << "Test 22: get(char*)" << std::endl;
    }
    // get(char*)
    temp = true;
    try {
        buf.put(cstr, 1025*1025);
    } catch (const char*){
        temp = false;
    }
    
    if (temp) {
        passedAllTests = false;
        std::cout << "Test 23: get(char*)" << std::endl;
    }
    
    
    /*
     Attempt to overflow buffer for all put methods
     */
    ByteBuffer tempB = ByteBuffer(1);
    
    // int
    temp = true;
    try {
        tempB.put('C');
        tempB.put('C');
    } catch (const char*) {
        temp = false;
    }
    
    if (temp) {
        passedAllTests = false;
        std::cout << "Test 24: Buffer Overflow test failed" << std::endl;
    }
    
    tempB.clear();
    
    // int
    temp = true;
    try {
        tempB.put('C');
        tempB.put('C');
        
    } catch (const char*) {
        temp = false;
    }
    
    if (temp) {
        passedAllTests = false;
        std::cout << "Test 25: Buffer Overflow test failed for int" << std::endl;
    }
    
    tempB.clear();
    
    // long
    temp = true;
    try {
        tempB.putLong(234);
        
    } catch (const char*) {
        temp = false;
    }
    
    if (temp) {
        passedAllTests = false;
        std::cout << "Test 26: Buffer Overflow test failed for long" << std::endl;
    }
    
    tempB.clear();
    
    // double
    temp = true;
    try {
        tempB.putDouble(235.325);
        
    } catch (const char*) {
        temp = false;
    }
    
    if (temp) {
        passedAllTests = false;
        std::cout << "Test 27: Buffer Overflow test failed for double" << std::endl;
    }
    
    tempB.clear();
    
    // byte array
    temp = true;
    try {
        tempB.put(cstr, bytes);
        
    } catch (const char*) {
        temp = false;
    }
    
    if (temp) {
        passedAllTests = false;
        std::cout << "Test 28: Buffer Overflow test failed for byte array" << std::endl;
    }
    
    tempB.clear();
    
    // Finish Testing
    if (passedAllTests == true) {
        std::cout << "ByteBuffer Passed All Tests" << std::endl;
    } else {
        std::cout << "ByteBuffer Failed one or multiple Tests" << std::endl;
    }
    
    std::cout << "Testing ByteBuffer Terminating\n\n";
    delete [] cstr;
    return 0;
}
