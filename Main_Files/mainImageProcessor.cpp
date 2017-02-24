//
//  mainImageProcessor.cpp
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <exception>

#include "ImageProcessor.h"

int main(int, char**) {
    int serverPort = 8000;
    std::string host("localhost");
    
    std::cout << "ImageProcessor Application Starting\n";
    ImageProcessor proc(host, serverPort);
    
    FILE* fid = proc.getLogFileID();
    
    try {
        proc.open();
        std::cout << "ImageProcessor Running\n";
        proc.run();
        
    } catch (const char* exception) {
                fprintf(logFile, "Error: Const Char* Exception Caught: %s\n", exception);
        
    } catch(std::exception &exception) {
fprintf(logFile, "Error: Standard Exception Caught: %s\n", exception.what());
        
    } catch (...) {
        fprintf(logFile, "Error: Unknown Type Of Exception Caught, Application Terminating \n");
        throw;
    }
    
    fprintf(logFile, "Application Terminating \n");
    std::cout << "ImageProcessor Application Terminating\n";
    return 0;
}
