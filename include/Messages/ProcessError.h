//
//  ProcessError.h
//  ProcessError
//
//  Created by Seth on 01/21/2016
//  Copyright © 2016 Seth. All rights reserved.
//

#ifndef PROCESSERROR_H
#define PROCESSERROR_H

enum ProcessError {
    PE_NA = -1,
    
    // CameraController
    PE_CC_requestTimeOut = 1,
    PE_CC_notConnected = 2,
    
    // ImageProcessor
    PE_IP_requestTimeOut = 3,
    PE_IP_notConnected= 4,
    
    // GNC
    PE_GNC_requestTimeOut = 5,
    PE_GNC_notConnected = 6,
    
    // SC_Comms
    PE_ScC_requestTimeOut = 7,
    PE_ScC_notConnected = 8,
    
    // WatchDog
    PE_WD_requestTimeOut = 9,
    PE_WD_notConnected = 10,
};

#endif
