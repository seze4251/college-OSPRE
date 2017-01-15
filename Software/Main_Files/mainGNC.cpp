//
//  mainGNC.cpp
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <unistd.h>
#include <iostream>

#include "GNC.h"

int main(int argc, char **argv) {
    int watchDogPort = 5000;
    std::string host("localhost");
    
    std::cout << "GNC Application Starting\n";
    GNC gnc(host, watchDogPort);
    
    std::cout << "GNC Initalized\n";
    gnc.open();
    gnc.run();
    std::cout << "GNC Application Terminating\n";
    return 0;
}
