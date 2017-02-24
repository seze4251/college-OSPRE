//
//  mainGNC.cpp
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "GNC.h"

int main(int, char**) {
    int serverPort = 9000;
    std::string host("localhost");
    
    std::cout << "GNC Application Starting\n";
    GNC gnc(host, serverPort);
    
    FILE* fid = gnc.getLogFileID();
    
    try {
        gnc.open();
        std::cout << "GNC Running\n";
        gnc.run();
        
    } catch (const char* exception) {
                fprintf(logFile, "Error: Const Char* Exception Caught: %s\n", exception);
        
    } catch(std::exception &exception) {
fprintf(logFile, "Error: Standard Exception Caught: %s\n", exception.what());
        
    } catch (...) {
        fprintf(logFile, "Error: Unknown Type Of Exception Caught, Application Terminating \n");
        throw;
    }
    
    fprintf(logFile, "Application Terminating \n");
    std::cout << "GNC Application Terminating\n";
    return 0;
}
