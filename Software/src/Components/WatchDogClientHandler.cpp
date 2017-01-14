//
//  WatchDogClientHandler.cpp
//  WatchDogClientHandler
//
//  Created by Seth on 11/27/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <WatchDogClientHandler.h>
#include <iostream>

WatchDogClientHandler::WatchDogClientHandler(Selector &sel, int fd) : ServiceInternal(sel, fd) {
    std::cout << "WatchDogClientHandler Constructor " << std::endl;
    getSelector().registerService(fd, this);
    getSelector().interestInRead(fd);

}

WatchDogClientHandler::~WatchDogClientHandler() {
    
}

void WatchDogClientHandler::sendStatusRequestMessage() {
    // Create Message
    ProccessHealthAndStatusRequest* msg = new ProccessHealthAndStatusRequest();
    // Put Message in Write Buffer
    build.buildProccessHealthAndStatusRequest(*msg);
    // Register Intrest in Write
    getSelector().interestInWrite(fd);
}











