//
//  testWatchDog.cpp
//
//  Created by Seth on 02/14/2017.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <iostream>

#include "WatchDog.h"

int main(int argc, char **argv) {
    std::cout << "\nTesting WatchDog Starting\n";
    bool passedAllTests = true;
    
    
    
    if (passedAllTests == true) {
        std::cout << "WatchDog Passed All Tests" << std::endl;
    } else {
        std::cout << "WatchDog Failed one or multiple Tests" << std::endl;
    }
    std::cout << "Testing WatchDog Terminating\n\n";
    return 0;
}
