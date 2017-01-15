//
//  ImageProcessor.h
//  ImageProcessor
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef IMAPGEPROCESSOR_H
#define IMAPGEPROCESSOR_H

#include <string>

#include "Server.h"
#include "WatchDogService.h"
#include "Acceptor.h"
#include "ProcessID.h"

class ImageProcessor : public Server {
public:
    ImageProcessor(std::string hostName, int localPort, int watchDogPort);
    ~ImageProcessor();
    virtual void handleTimeout();
    bool open();
    static void handleImageProcessorConnections(int fd);
    
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

