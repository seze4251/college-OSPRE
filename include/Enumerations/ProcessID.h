//
//  ProcessID.h
//  ProcessID
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#ifndef PROCESSID_H
#define PROCESSID_H

#include <stdio.h>

enum ProcessID {
    P_NA = -1,
    P_CameraController = 1,
    P_ScComms = 2,
    P_GNC = 3,
    P_ImageProcessor = 4,
    P_WatchDog = 5,
    P_Spacecraft = 6,
};

static void printProcessID(ProcessID p, FILE* logFile) {
    fprintf(logFile, "Printing ProcessID Enumeration:\n");
    switch (p) {
        case P_NA:
            fprintf(logFile, "Process is N/A\n");
            break;
        case P_CameraController:
            fprintf(logFile, "Camera Controller\n");
            break;
        case P_ScComms:
            fprintf(logFile, "ScComms\n");
            break;
        case P_GNC:
            fprintf(logFile, "GNC\n");
            break;
        case P_ImageProcessor:
            fprintf(logFile, "Image Processor\n");
            break;
        case P_WatchDog:
            fprintf(logFile, "WatchDog\n");
            break;
        case P_Spacecraft:
            fprintf(logFile, "Spacecraft\n");
            break;
        default:
            fprintf(logFile, "Invalid value for Process ID\n");
            throw "Invalid value for Process ID";
            break;
    }
}

#endif
