//
//  mainCameraController.cpp
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <exception>

#include "CameraController.h"

int main(int, char**) {
    int serverPort = 10000;
    std::string host("localhost");
    
    std::cout << "CameraController Application Starting\n";
    CameraController controller(host, serverPort);
    
    FILE* logFile;
    
    try {
        controller.open();
        logFile = controller.getLogFileID();
        std::cout << "CameraController Running\n";
        controller.run();
        
    } catch (const char* exception) {
        fprintf(logFile, "Error: Const Char* Exception Caught: %s\n", exception);
        
    } catch(std::exception &exception) {
fprintf(logFile, "Error: Standard Exception Caught: %s\n", exception.what());
        
    } catch (...) {
        fprintf(logFile, "Error: Unknown Type Of Exception Caught, Application Terminating \n");
        fflush(logFile);
        throw;
    }
    
    fprintf(logFile, "Application Terminating \n");
    fflush(logFile);
    std::cout << "CameraController Application Terminating\n";
    return 0;
}
