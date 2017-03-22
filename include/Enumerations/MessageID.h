//
//  MessageID.h
//  MessageID
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#ifndef MESSAGEID_H
#define MESSAGEID_H

#include <stdio.h>

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

static void printMessageID(MessageID ID, FILE* logFile) {
    fprintf(logFile, "Printing Message ID Enumeration:\n");
    
    switch (ID) {
        case NA:
            fprintf(logFile, "Message Type N/A\n");
            break;
            
        case I_CaptureImageRequest:
            fprintf(logFile, "Capture Image Request Message\n");
            break;
            
        case I_DataMessage:
            fprintf(logFile, "Data Message\n");
            break;
            
        case I_ImageAdjustment:
            fprintf(logFile, "Image Adjustment Message\n");
            break;
            
        case I_ImageMessage:
            fprintf(logFile, "Image Message\n");
            break;
            
        case I_OSPREStatus:
            fprintf(logFile, "OSPRE Status Message\n");
            break;
            
        case I_PointingRequest:
            fprintf(logFile, "Pointing Request Message\n");
            break;
            
        case I_ProcessHealthAndStatusRequest:
            fprintf(logFile, "Process Health and Status Request Message\n");
            break;
            
        case I_ProcessHealthAndStatusResponse:
            fprintf(logFile, "Process Health and Status Response Message\n");
            break;
            
        case I_SolutionMessage:
            fprintf(logFile, "Solution Message\n");
            break;
            
        case E_OSPREStatus:
            fprintf(logFile, "External OSPRE Status Message\n");
            break;
            
        case E_PointingRequest:
            fprintf(logFile, "External Pointing Request Message\n");
            break;
            
        case E_SolutionMessage:
            fprintf(logFile, "External Solution Message\n");
            break;
            
        case E_SpacecraftDataMessage:
            fprintf(logFile, "External Spacecraft Data Message\n");
            break;
            
        default:
            fprintf(logFile, "Error: Unknown Value of Message ID\n");
            break;
    }
}

#endif
