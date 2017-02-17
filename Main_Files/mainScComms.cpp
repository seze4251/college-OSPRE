//
//  mainScComms.cpp
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <unistd.h>
#include <iostream>
#include <exception>

#include "ScComms.h"

int main(int, char**) {
    int serverPort = 7000;
    int externalPort = 7500;
    std::string host("localhost");
    
    std::cout << "ScComms Application Starting\n";
    ScComms comms(host, serverPort, externalPort);
    
    try {
        comms.open();
        std::cout << "ScComms Initalized\n";
        comms.run();
        
    } catch (const char* exception) {
        std::cerr << "ScComms: Error: " << exception << std::endl;
        
    } catch(std::exception &exception) {
        std::cerr << "ScComms: Standard exception: " << exception.what() << '\n';
        
    } catch (...) {
        std::cout << "ScComms: Exception of unknown type caught" << std::endl;
        throw;
    }
    
    std::cout << "ScComms Application Terminating\n";
    return 0;
}


