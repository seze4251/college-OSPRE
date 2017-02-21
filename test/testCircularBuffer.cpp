//
//  testCircularBuffer.cpp
//
//  Created by Seth on 02/14/2017.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <iostream>

#include "DataMessage.h"
#include "CircularBuffer.h"

/*
 Test Constructor
 Test Two Methods in Nominal Case
 void put(DataMessage* msg);
 DataMessage* get(time_t timeStamp);
 Edge Cases:
 Bad Input:
 void put(DataMessage* msg);
 1. NULL input
 2. Negative timeStamp
 DataMessage* get(time_t timeStamp);
 1. Negative TimeStamp Input
 More Complicated Test Cases:
 void put(DataMessage* msg);
 1. overflow message and see if it rewrites old messages
 DataMessage* get(time_t timeStamp);
 1. Try and find a timestamp that is not in the buffer
 */

int main(int argc, char **argv) {
    std::cout << "\nTesting CircularBuffer Starting\n";
    bool passedAllTests = true;
    
    CircularBuffer circBuf_Norm = CircularBuffer();
    CircularBuffer circBuf_Small = CircularBuffer(3);
    
    // Test Constructor
    bool test = true;
    try {
        CircularBuffer circ_Test = CircularBuffer(-10);
    } catch (const char*) {
        test = false;
    }
    
    if (test) {
        passedAllTests = false;
        std::cout << "Test 1: Circular Buffer lets you call constructor with a negative number Bad" << std::endl;
    }
    
    
    /* Test Two Methods in Nominal Case
     void put(DataMessage* msg);
     DataMessage* get(time_t timeStamp);
     */
    
    DataMessage msg1 = DataMessage();
    double ephem[3]{1, 2, 3};
    double quat[4] {4, 5, 6, 7};
    double angularVelocity[3]{0.1, 0.2, 0.3};
    double satTime = time(0), sunAngle = 3;
    bool sleep = false;
    msg1.update(ephem, quat, angularVelocity, satTime, sunAngle, sleep);
    
    // Nominal Put Test
    test = false;
    try {
        circBuf_Norm.put(&msg1);
    } catch (const char*) {
        test = true;
    }
    
    if (test) {
        passedAllTests = false;
        std::cout << "Test 2: Circular Buffer is not functioning normally" << std::endl;
    }
    
    // Nominal Get Test
    test = false;
    try {
        DataMessage* msg1Point = circBuf_Norm.get(satTime);
    } catch (const char*) {
        test = true;
    }
    
    if (test) {
        passedAllTests = false;
        std::cout << "Test 3: Circular Buffer get is not functioning normally" << std::endl;
    }
    
    /* Edge Cases
     Bad Input:
     void put(DataMessage* msg);
     1. NULL input
     2. Negative timeStamp
     DataMessage* get(time_t timeStamp);
     1. Negative TimeStamp Input
     */
    
    // Put Method Test
    test = true;
    try {
        circBuf_Norm.put(nullptr);
    } catch (const char*) {
        test = false;
    }
    
    if (test) {
        passedAllTests = false;
        std::cout << "Test 4: CircularBuffer:put() does not catch nullptr input" << std::endl;
    }
    
    test = true;
    msg1.timeStamp = -10;
    try {
        circBuf_Norm.put(&msg1);
    } catch (const char*) {
        test = false;
    }
    
    if (test) {
        passedAllTests = false;
        std::cout << "Test 5: CircularBuffer:put() does not catch negative timeStamp input" << std::endl;
    }
    
    // Get Method Tests
    test = true;
    try {
        DataMessage* msg1Point = circBuf_Norm.get(-10042);
    } catch (const char*) {
        test = false;
    }
    
    if (test) {
        passedAllTests = false;
        std::cout << "Test 6: CircularBuffer:get() does not catch negative timeStamp input" << std::endl;
    }
    
    
    /*
     Edge Cases
     More Complicated Test Cases:
     void put(DataMessage* msg);
     1. overflow message and see if it rewrites old messages
     DataMessage* get(time_t timeStamp);
     1. Try and find a timestamp that is not in the buffer
     */
    
    // Find TimeStamp that is not in the buffer!
    test = true;
    try {
        DataMessage* msg1Point = circBuf_Norm.get(time(0));
    } catch (const char*) {
        test = false;
    }
    
    if (test) {
        passedAllTests = false;
        std::cout << "Test 7: CircularBuffer:get() does not throw exception when DataMessage does not exist within buffer" << std::endl;
    }
    
    // Overflow Message Buffer
    msg1.timeStamp = 1;
    circBuf_Small.put(&msg1);
    
    msg1.timeStamp = 2;
    circBuf_Small.put(&msg1);
    
    msg1.timeStamp = 3;
    circBuf_Small.put(&msg1);
    
    test = false;
    try {
        DataMessage* msg1Point = circBuf_Norm.get(1);
        msg1Point = circBuf_Norm.get(2);
        msg1Point = circBuf_Norm.get(3);
    } catch (const char*) {
        test = true;
    }
    
    if (test) {
        passedAllTests = false;
        std::cout << "Test 8: One of the messages put into the buffer was not found" << std::endl;
    }
    
    
    msg1.timeStamp = 4;
    circBuf_Small.put(&msg1);
    
    test = true;
    try {
        DataMessage* msg1Point = circBuf_Norm.get(1);
    } catch (const char*) {
        test = false;
    }
    
    if (test) {
        passedAllTests = false;
        std::cout << "Test 9: Message was able to be found when it did not exist in buffer" << std::endl;
    }
    
    test = false;
    try {
        DataMessage* msg1Point = circBuf_Norm.get(2);
        msg1Point = circBuf_Norm.get(3);
        msg1Point = circBuf_Norm.get(4);
    } catch (const char*) {
        test = true;
    }
    
    if (test) {
        passedAllTests = false;
        std::cout << "Test 10: One or more of the messages in the buffer was not able to be found" << std::endl;
    }
    
    
    if (passedAllTests == true) {
        std::cout << "CircularBuffer Passed All Tests" << std::endl;
    } else {
        std::cout << "CircularBuffer Failed one or multiple Tests" << std::endl;
    }
    
    std::cout << "Testing CircularBuffer Terminating\n";
    return 0;
}












