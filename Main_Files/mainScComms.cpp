//
//  mainScComms.cpp
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <stdio.h>
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
    
    FILE* fid = comms.getLogFileID();
    
    try {
        comms.open();
        std::cout << "ScComms Running\n";
        comms.run();
        
    } catch (const char* exception) {
        fprintf(logFile, "Error: Const Char* Exception Caught: %s\n", exception);
        
    } catch(std::exception &exception) {
fprintf(logFile, "Error: Standard Exception Caught: %s\n", exception.what());
        
    } catch (...) {
        fprintf(logFile, "Error: Unknown Type Of Exception Caught, Application Terminating \n");
        throw;
    }
    
    fprintf(logFile, "Application Terminating \n");
    std::cout << "ScComms Application Terminating\n";
    return 0;
}




