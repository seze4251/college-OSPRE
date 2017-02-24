//
//  main_WatchDog.cpp
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <unistd.h>
#include <iostream>
#include <exception>
#include <stdio.h>

#include "WatchDog.h"

int main(int, char**) {
    int serverPort = 5000;
    std::string host("localhost");
    
    std::cout << "WatchDog Application Starting\n";
    WatchDog dog(host, serverPort);
    
    FILE* logFile = dog.getLogFileID();
    
    try {
        dog.open();
        std::cout << "WatchDog Running\n";
        dog.run();
        
    } catch (const char* exception) {
        fprintf(logFile, "Error: Const Char* Exception Caught: %s\n", exception);
        
    } catch(std::exception &exception) {
        fprintf(logFile, "Error: Standard Exception Caught: %s\n", exception.what());
        
    } catch (...) {
        fprintf(logFile, "Error: Unknown Type Of Exception Caught, Application Terminating \n");
        throw;
    }
    
    fprintf(logFile, "Application Terminating \n");
    std::cout << "WatchDog Application Terminating\n";
    return 0;
}



