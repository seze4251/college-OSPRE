//
//  main_WatchDog.cpp
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <unistd.h>
#include <iostream>
#include <exception>

#include "WatchDog.h"

int main(int, char**) {
    int serverPort = 5000;
    std::string host("localhost");
    
    std::cout << "WatchDog Application Starting\n";
    WatchDog dog(host, serverPort);
    
    try {
        dog.open();
        std::cout << "WatchDog Initalized\n";
        dog.run();
        
    } catch (const char* exception) {
        std::cerr << "WatchDog: Error: " << exception << std::endl;
        
    } catch(std::exception &exception) {
        std::cerr << "WatchDog: Standard exception: " << exception.what() << '\n';
        
    } catch (...) {
        std::cout << "WatchDog: Exception of unknown type caught" << std::endl;
        throw;
    }
    
    std::cout << "WatchDog Application Terminating\n";
    return 0;
}
