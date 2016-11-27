//
//  CameraController.h
//  CameraController
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "Server.h"
#include "ErrorCode.h"

class CameraController : public Server {
public:
    CameraController(int localPort);
    ~CameraController();
    
private:
    
};

#endif
