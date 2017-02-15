//
//  ProcessID.h
//  ProcessID
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#ifndef PROCESSID_H
#define PROCESSID_H

#include "iostream"

enum ProcessID {
    P_NA = -1,
    P_CameraController = 1,
    P_ScComms = 2,
    P_GNC = 3,
    P_ImageProcessor = 4,
    P_WatchDog = 5,
    P_Spacecraft = 6,
};

static void printProcessID(ProcessID p) {
    switch (p) {
        case P_NA:
            std::cout << "Process is N/A";
            break;
        case P_CameraController:
            std::cout << "Camera Controller" << std::endl;
            break;
        case P_ScComms:
            std::cout << "ScComms" << std::endl;
            break;
        case P_GNC:
            std::cout << "GNC" << std::endl;
            break;
        case P_ImageProcessor:
            std::cout << "Image Processor" << std::endl;
            break;
        case P_WatchDog:
            std::cout << "WatchDog" << std::endl;
            break;
        case P_Spacecraft:
            std::cout << "Spacecraft" << std::endl;
            break;
        default:
            std::cout << "Invalid value for Process ID" << std::endl;
            break;
    }
}

#endif
