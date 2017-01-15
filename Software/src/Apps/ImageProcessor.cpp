//
//  ImageProcessor.cpp
//  ImageProcessor
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>

#include "ImageProcessor.h"
#include "Service.h"

ImageProcessor::ImageProcessor(std::string hostName, int portNumber, int watchDogPort) : watchDog(getSelector(), hostName, watchDogPort), accept(getSelector()), pollTime(0), hostName(hostName), localPort(localPort) {
    std::cout<< "ImageProcessor Constructor called" << std::endl;
    setAppl(this);
    accept.registerCallback(ImageProcessor::handleImageProcessorConnections);
    p_ID = P_ImageProcessor;
    watchDog.p_ID = p_ID;
}

ImageProcessor::~ImageProcessor() {
    
}

bool ImageProcessor::open() {
    //WatchDog Service
    if (watchDog.isConnected() == false) {
        watchDog.open();
    }
    
    //Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            std::cerr << "ImageProcessor Server Socket Failed To Open, ImageProcessor Exiting" << std::endl;
            exit(-1);
        }
        std::cout << "ImageProcessor Server Socket Opened" << std::endl;
    }
    
    // Other Services
    // TODO: Change Bool to something more useful
    return true;
}


// Connect to Camera Controller
// Connect to WatchDog

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************


void ImageProcessor::handleTimeout() {
    
}

void ImageProcessor::handleImageProcessorConnections(int fd) {
    
}
