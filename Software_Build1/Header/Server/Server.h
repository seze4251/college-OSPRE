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
#include <vector>

class Server {
public:
    // Constructors
    Server(int localPort);
    Server(int localPort, std::vector<int> *serverPorts, char **serverHosts);
    
    //Destructor
    virtual ~Server();
    
    //Public Methods
    ErrorCode run();
    
private:
    Selector sel;
    TimeoutManager timeout
};

#endif
