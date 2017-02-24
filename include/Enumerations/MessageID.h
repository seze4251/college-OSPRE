//
//  MessageID.h
//  MessageID
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#ifndef MESSAGEID_H
#define MESSAGEID_H

#include <iostream>

enum MessageID {
    NA = -1,
    I_CaptureImageRequest = 1,
    I_DataMessage = 2,
    I_ImageAdjustment = 3,
    I_ImageMessage = 4,
    I_OSPREStatus = 5,
    I_PointingRequest = 6,
    I_ProcessHealthAndStatusRequest = 7,
    I_ProcessHealthAndStatusResponse = 8,
    I_SolutionMessage = 9,
    I_ProcessedImageMessage = 10,
    E_OSPREStatus = 11,
    E_PointingRequest = 12,
    E_SolutionMessage = 13,
    E_SpacecraftDataMessage = 14
};

static void printMessageID(MessageID ID) {
    switch (ID) {
        case NA:
            std::cout << "Message Type N/A";
            break;
            
        case I_CaptureImageRequest:
            std::cout << "Capture Image Request Message" << std::endl;
            break;
            
        case I_DataMessage:
            std::cout << "Data Message" << std::endl;
            break;
            
        case I_ImageAdjustment:
            std::cout << "Image Adjustment Message" << std::endl;
            break;
            
        case I_ImageMessage:
            std::cout << "Image Message" << std::endl;
            break;
            
        case I_OSPREStatus:
            std::cout << "OSPRE Status Message" << std::endl;
            break;
            
        case I_PointingRequest:
            std::cout << "Pointing Request Message" << std::endl;
            break;
            
        case I_ProcessHealthAndStatusRequest:
            std::cout << "Process Health and Status Request Message" << std::endl;
            break;
            
        case I_ProcessHealthAndStatusResponse:
            std::cout << "Process Health and Status Response Message";
            break;
            
        case I_SolutionMessage:
            std::cout << "Solution Message" << std::endl;
            break;
            
        case E_OSPREStatus:
            std::cout << "External OSPRE Status Message" << std::endl;
            break;
            
        case E_PointingRequest:
            std::cout << "External Pointing Request Message" << std::endl;
            break;
            
        case E_SolutionMessage:
            std::cout << "External Solution Message" << std::endl;
            break;
            
        case E_SpacecraftDataMessage:
            std::cout << "External Spacecraft Data Message" << std::endl;
            break;
            
        default:
            std::cout << "Error: Unknown Value of Message ID" << std::endl;
            break;
    }
}

#endif
