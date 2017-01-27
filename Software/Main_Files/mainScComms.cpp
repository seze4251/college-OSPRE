//
//  mainScComms.cpp
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <unistd.h>
#include <iostream>

#include "ScComms.h"

int main(int argc, char **argv) {
    int serverPort = 7000;
    std::string host("localhost");
    
    std::cout << "ScComms Application Starting\n";
    ScComms comms(host, serverPort);
    
    std::cout << "ScComms Initalized\n";
    comms.open();
    std::cout << "Open Call Made Sucessfully" << std::endl;
    comms.run();
    std::cout << "ScComms Application Terminating\n";
    return 0;
}
