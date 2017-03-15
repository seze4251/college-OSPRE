//
//  ProcessError.h
//  ProcessError
//
//  Created by Seth on 01/21/2016
//  Copyright © 2016 Seth. All rights reserved.
//

#ifndef PROCESSERROR_H
#define PROCESSERROR_H

#include "iostream"

enum ProcessError {
    // Process Error Not Defined
    PE_NA = -1,
    
    // All Processes are healthy or not healthy
    PE_AllHealthy = 0,
    PE_NotHealthy = 1,
    
    // Individual Errors
    PE_requestTimeOut = 2,
    PE_notConnected = 3,
    PE_IP_noBodyInImage = 4,
    PE_CC_angularVelocityToHigh = 5,
    PE_invalidData = 6,
    PE_divideByZero = 7,
    PE_SleepMode = 8
};

static void printProcessError(ProcessError p) {
    switch (p) {
        case PE_NA:
            std::cout << "Error: N/A";
            break;
        case PE_AllHealthy:
            std::cout << "OSPRE is Healthy" << std::endl;
            break;
        case PE_NotHealthy:
            std::cout << "OSPRE is Sick" << std::endl;
            break;
        case PE_requestTimeOut:
            std::cout << "Error: Request Time Out" << std::endl;
            break;
        case PE_notConnected:
            std::cout << "Error: Process Not Connected" << std::endl;
            break;
        case PE_IP_noBodyInImage:
            std::cout << "Error: No Body In Image" << std::endl;
            break;
        case PE_CC_angularVelocityToHigh:
            std::cout << "Error: Angular Velocity To High to Capture Image" << std::endl;
            break;
        case PE_invalidData:
            std::cout << "Error: Invalid Data" << std::endl;
            break;
        case PE_divideByZero:
            std::cout << "Error: Divide By 0" << std::endl;
            break;
        case PE_SleepMode:
            std::cout << "Error: Sleep Mode" << std::endl;
            break;
        default:
            std::cout << "Error: Unknown Value of Process Error" << std::endl;
            break;
    }
}


#endif

// Case 1:
// All good -> 0

// Case 2: GNC is down b/c of unknown reason
// PE_GEN_ProcessDown -> Process ID GNC -> Reason/Unknown

// ProcessID, ReasonCode









