//
//  mainSpacecraft.cpp
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <unistd.h>
#include <iostream>

#include "Spacecraft.h"

int main(int argc, char **argv) {
    int serverPort = 6000;
    std::string host("localhost");
    
    std::cout << "Spacecraft Application Starting\n";
    Spacecraft sc(host, serverPort);
    
    std::cout << "Spacecraft Initalized\n";
    sc.open();
    sc.run();
    std::cout << "Spacecraft Application Terminating\n";
    return 0;
}
