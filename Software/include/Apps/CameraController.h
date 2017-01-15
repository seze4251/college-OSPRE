//
//  CameraController.h
//  CameraController
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <string>

#include "Server.h"
#include "WatchDogService.h"
#include "Acceptor.h"
#include "ProcessID.h"

class CameraController : public Server {
public:
    CameraController(std::string hostName, int localPort, int watchDogPort);
    ~CameraController();
    virtual void handleTimeout();
    bool open();
    static void handleCameraControllerConnections(int fd);
    
    ProcessID p_ID;
private:
    Acceptor accept;
    time_t pollTime;
    WatchDogService watchDog;
    
    //Acceptor Port and Host
    std::string hostName;
    int localPort;
};

#endif
