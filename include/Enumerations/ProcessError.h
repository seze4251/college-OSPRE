//
//  ProcessError.h
//  ProcessError
//
//  Created by Seth on 01/21/2016
//  Copyright © 2016 Seth. All rights reserved.
//

#ifndef PROCESSERROR_H
#define PROCESSERROR_H

#include <stdio.h>

enum ProcessError {
    // Process Error Not Defined
    PE_NA = -1,
    
    // All Processes are healthy or not healthy
    PE_AllHealthy = 0,
    PE_NotHealthy = 1,
    
    // Individual Errors
    PE_requestTimeOut = 2,
    PE_notConnected = 3,
    PE_InvalidInputs = 4,
    PE_InvalidOutputs = 5,
    PE_IP_InvalidPosition = 6,
    PE_IP_noBodyInImage = 7,
    PE_CC_InvalidFileName = 8,
    PE_CC_InvalidImageDimensions = 9,
    PE_CC_angularVelocityToHigh = 10,
    PE_invalidData = 11,
    PE_divideByZero = 12,
    PE_SleepMode = 13
};

static void printProcessError(ProcessError p, FILE* logFile) {
    fprintf(logFile, "Printing ProcessError Enumeration:\n");
    switch (p) {
        case PE_NA:
            fprintf(logFile, "Error: N/A\n");
            break;
        case PE_AllHealthy:
            fprintf(logFile, "OSPRE is Healthy\n");
            break;
        case PE_NotHealthy:
            fprintf(logFile, "OSPRE is Sick\n");
            break;
        case PE_requestTimeOut:
            fprintf(logFile, "Error: Request Time Out\n");
            break;
        case PE_notConnected:
            fprintf(logFile, "Error: Process Not Connected\n");
            break;
        case PE_InvalidInputs:
            fprintf(logFile, "Error: Invalid Inputs\n");
            break;
        case PE_InvalidOutputs:
            fprintf(logFile, "Error: Invalid Outputs\n");
            break;
        case PE_IP_InvalidPosition:
            fprintf(logFile, "Error: Invalid Position\n");
            break;
        case PE_IP_noBodyInImage:
            fprintf(logFile, "Error: No Body In Image\n");
            break;
        case PE_CC_InvalidFileName:
            fprintf(logFile, "Error: Invalid File Name\n");
            break;
        case PE_CC_InvalidImageDimensions:
            fprintf(logFile, "Error: Invalid Image Dimensions\n");
            break;
        case PE_CC_angularVelocityToHigh:
            fprintf(logFile, "Error: Angular Velocity To High to Capture Image\n");
            break;
        case PE_invalidData:
            fprintf(logFile, "Error: Invalid Data\n");
            break;
        case PE_divideByZero:
            fprintf(logFile, "Error: Divide By 0\n");
            break;
        case PE_SleepMode:
            fprintf(logFile, "Error: Sleep Mode\n");
            break;
        default:
            fprintf(logFile, "Error: Unknown Value of Process Error\n");
            throw "Error: Unknown Value of Process Error";"
            break;
    }
}


#endif








