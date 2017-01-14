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
    I_DataRequest = 2,
    I_EphemerisMessage = 3,
    I_ImageAdjustment = 4,
    I_ImageMessage = 5,
    I_OSPREStatus = 6,
    I_PointingRequest = 7,
    I_ProccessHealthAndStatusRequest = 8,
    I_ProccessHealthAndStatusResponse = 9,
    I_SolutionMessage = 10,
    E_OSPREStatus = 11,
    E_PointingRequest = 12,
    E_SolutionMessage = 13,
    E_SpacecraftStatus = 14
};

#endif
