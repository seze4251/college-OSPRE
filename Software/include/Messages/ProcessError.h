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
    
    // ImageProcessor
    PE_IP_requestTimeOut,
    
    // GNC
    PE_GNC_requestTimeOut,
    
    // SC_Comms
    PE_ScC_requestTimeOut,
    
    // WatchDog
    PE_WD_requestTimeOut,
};

#endif
