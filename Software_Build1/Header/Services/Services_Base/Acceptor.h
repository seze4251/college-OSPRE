//
//  Acceptor.h
//  Acceptor
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef ACCEPTOR_H
#define ACCEPTOR

#include "Service.h"

// NOTE:  This class is derived from Service and not Service_Internal good or bad?
class Acceptor : public Service {
public:
    // Constructor
    Acceptor(Selector &sel, std::string hostName, int port);
    
    void handleRead();
    void handleWrite();
    
    int cfd;
    
private:
    int port;
    std::string hostName;
    int fd;
};

#endif
