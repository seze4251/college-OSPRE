//
//  Server.h
//  Server
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SERVER_H
#define SERVER_H

#include "ErrorCode.h"
#include "Selector.h"
#include "TimeoutManager.h"

class Server {
public:
    // Constructors
    Server();

    //Destructor
    virtual ~Server();
    
    //Public Methods
    ErrorCode run();
    
    Selector& getSelector();
    
private:
    Selector sel;
    TimeoutManager timeout;
    
    void handleTimeout();
    ErrorCode run2();
};

#endif
