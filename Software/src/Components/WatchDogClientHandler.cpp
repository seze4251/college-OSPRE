//
//  WatchDogClientHandler.cpp
//  WatchDogClientHandler
//
//  Created by Seth on 11/27/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <WatchDogClientHandler.h>

WatchDogClientHandler::WatchDogClientHandler(Selector &sel, std::string hostName, int portNumber) : ServiceInternal(sel), fd(-1) { } 

WatchDogClientHandler::~WatchDogClientHandler() {
    
}
