//
//  testExternalBuilder.cpp
//
//  Created by Seth on 02/14/2017.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <iostream>

#include "External_Builder.h"

int main(int argc, char **argv) {
    std::cout << "\nTesting ExternalBuilder Starting\n";
    bool passedAllTests = true;
    
    
    
    if (passedAllTests == true) {
        std::cout << "ExternalBuilder Passed All Tests" << std::endl;
    } else {
        std::cout << "ExternalBuilder Failed one or multiple Tests" << std::endl;
    }

    std::cout << "Testing ExternalBuilder Terminating\n\n";
    return 0;
}
