//
//  Service.h
//  Service
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SERVICE_H
#define SERVICE_H

#include "Selector.h"

class Service {
public:
    Service(Selector &sharedSel);
    virtual ~Service() {}
    virtual void handleRead() = 0;
    virtual void handleWrite() = 0;
    Selector getSelector() { return sel; }
    
protected:
    int openServerSocket(int portNumber);
    int connectToServer(char *serverHosts, int serverPort);

private:
    Selector &sel;
};

#endif
