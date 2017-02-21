//
//  testCircularBuffer.cpp
//
//  Created by Seth on 02/14/2017.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <iostream>

#include "CircularBuffer.h"

int main(int argc, char **argv) {
    std::cout << "\nTesting CircularBuffer Starting\n";
    bool passedAllTests = true;
    
    
    
    if (passedAllTests == true) {
        std::cout << "CircularBuffer Passed All Tests" << std::endl;
    } else {
        std::cout << "CircularBuffer Failed one or multiple Tests" << std::endl;
    }

    std::cout << "Testing CircularBuffer Terminating\n";
    return 0;
}
