//
//  Selector.h
//  Selector
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include "Selector.h"

Selector::Selector() {
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
}


Selector::~Selector(){
    
}


ErrorCode Selector::select() {
    
}


ErrorCode Selector::select(timeval* timeout) {
    
}


ErrorCode Selector::selectNow() {
    
}


ErrorCode Selector::zeroFDs() {
    FD_ZERO(&readFds);
    FD_ZERO(&writeFds);
}


ErrorCode Selector::registerForReadEvents(std::vector &fds) {
    for (auto &element: serverPorts) {
        FD_SET(element, &readFds);
    }
}


ErrorCode Selector::registerForWriteEvents(std::vector &fds) {
    for (auto &element: fds) {
        FD_SET(element, &writeFds);
    }
}





