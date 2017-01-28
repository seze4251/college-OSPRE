//
//  MessageID.h
//  MessageID
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#ifndef MESSAGEID_H
#define MESSAGEID_H

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
    E_SpacecraftStatus = 14
};

#endif
