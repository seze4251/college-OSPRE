//
//  Service.h
//  Service
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SERVICE_H
#define SERVICE_H


class Service {
public:
    Service(Selector &sharedSel) {sel = sharedSel;}
    virtual ~Service() {}
    virtual void handleRead() = 0;
    virtual void handleWrite() = 0;
    Selector getSelector() { return sel; }
    
protected:
    openServerSocket();
    connectToServer(int serverPort, char *serverHosts);

private:
    Selector &sel;
    Connector con;
    Acceptor accept;
    
};

#endif
