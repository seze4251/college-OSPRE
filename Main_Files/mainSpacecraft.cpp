//
//  mainSpacecraft.cpp
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <unistd.h>
#include <iostream>
#include <exception>

#include "Spacecraft.h"

int main(int, char**) {
    int serverPort = 7500;
    std::string host("localhost");
    
    std::cout << "Spacecraft Application Starting\n";
    Spacecraft sc(host, serverPort);
    
    try {
        sc.open();
        std::cout << "Spacecraft Initalized\n";
        sc.run();
        
    } catch (const char* exception) {
        std::cerr << "Spacecraft: Error: " << exception << std::endl;
        
    } catch(std::exception &exception) {
        std::cerr << "Spacecraft: Standard exception: " << exception.what() << '\n';
        
    } catch (...) {
        std::cout << "Spacecraft: Exception of unknown type caught" << std::endl;
        throw;
    }
    
    std::cout << "Spacecraft Application Terminating\n";
    return 0;
}
