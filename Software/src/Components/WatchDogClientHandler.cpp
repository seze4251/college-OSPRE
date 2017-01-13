//
//  WatchDogClientHandler.cpp
//  WatchDogClientHandler
//
//  Created by Seth on 11/27/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <WatchDogClientHandler.h>
#include <iostream>

WatchDogClientHandler::WatchDogClientHandler(Selector &sel, int fd) : ServiceInternal(sel), fd(fd), sel(sel) {
    std::cout << "WatchDogClientHandler Constructor " << std::endl;
    getSelector().registerService(fd, this);
    getSelector().interestInRead(fd);

}

WatchDogClientHandler::~WatchDogClientHandler() {
    
}

void WatchDogClientHandler::sendStatusRequestMessage() {
    
}


void WatchDogClientHandler::handleRead() {
    std::cout << "WatchDogClientHandler handleRead " << std::endl;
}

void WatchDogClientHandler::handleWrite() {
    std::cout << "WatchDogClientHandler handleWrite " << std::endl;
}
