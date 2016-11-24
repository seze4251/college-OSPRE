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
    I_CaptureImageRequest = 0;
    I_DataRequest = 1;
    I_EphemerisMessage = 2;
    I_ImageAdjustment = 3;
    I_ImageMessage = 4;
    I_OSPREStatus = 5;
    I_PointingRequest = 6;
    I_ProccessHealthAndStatusRequest = 7;
    I_ProccessHealthAndStatusResponse = 8;
    I_SolutionMessage = 9;
    E_OSPREStatus = 10;
    E_PointingRequest = 11;
    E_SolutionMessage = 12;
    E_SpacecraftStatus = 13;
};

#endif
