//
//  WatchDogService.cpp
//  WatchDogService
//
//  Created by Seth on 11/27/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include "WatchDogService.h"
#include <unistd.h>

WatchDogService::WatchDogService(Selector &sel, std::string hostName, int portNumber) : ServiceInternal(sel), fd(-1) { }

WatchDogService::~WatchDogService() {
    
}

void WatchDogService::handleRead() {
    //int numRead = ::read(fd, readbuf); // you need to create this read() it usese a a ByteBuffer.
    
 /*
    if (numRead == 0) {
        // handle error case
    }
  */
    
    // determine if you have a complete message
    // if yes, pass it to the parser to extract that message
    // keep extracting messages until you've extracted all of them.
    // protected methods of internal service
    
    // ^^ Belongs in Internal Service
    // All Below belongs in internal Service
    // Belongs in WatchDogService
    // for each message do what you are supposed to do with that message.
    // Virtual Method of InternalService
    
    // Do I have data to write!
    // Tell Selector that I am interested in writing
    
}

void WatchDogService::handleWrite() {
    
    
    // After written, Tell selector no longer interested if no more data to write
    
}

void WatchDogService::close() {
    if (fd != -1) {
        ::close(fd);
        fd = -1;
    }
    readbuf.clear();
    writebuf.clear();
}



