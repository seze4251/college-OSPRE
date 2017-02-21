//
//  testSpacecraft.cpp
//
//  Created by Seth on 02/14/2017.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <iostream>

#include "Spacecraft.h"

int main(int argc, char **argv) {
    std::cout << "\nTesting Spacecraft Starting\n";
    bool passedAllTests = true;
    
    
    
    if (passedAllTests == true) {
        std::cout << "Spacecraft Passed All Tests" << std::endl;
    } else {
        std::cout << "Spacecraft Failed one or multiple Tests" << std::endl;
    }

    std::cout << "Testing Spacecraft Terminating\n\n";
    return 0;
}
