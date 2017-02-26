//
//  Server.h
//  Server
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SERVER_H
#define SERVER_H

#include "Selector.h"
#include "Acceptor.h"

class Server {
public:
    // Constructors
    Server();

    //Destructor
    virtual ~Server();
    
    //Public Methods
    int run();
    Selector& getSelector();
    
    static Server* getAppl();
    FILE* getLogFileID() { return logFile;}
    
protected:
    static void setAppl(Server* srv);
    static Server* appl;
    virtual void handleTimeout() = 0;
    void setTimeoutTime(int sec, int micro);
    void flushLog();
    timeval t_val;
    FILE* logFile;
    
private:
    Selector sel;
    int flushTime;
};

#endif
