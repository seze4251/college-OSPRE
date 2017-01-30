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
    PE_CC_requestTimeOut,
    PE_CC_notConnected,
    
    // ImageProcessor
    PE_IP_requestTimeOut,
    PE_IP_notConnected,
    
    // GNC
    PE_GNC_requestTimeOut,
    PE_GNC_notConnected,
    
    // SC_Comms
    PE_ScC_requestTimeOut,
    PE_ScC_notConnected,
    
    // WatchDog
    PE_WD_requestTimeOut,
    PE_WD_notConnected,
};

#endif
