//
//  Server.h
//  Server
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SERVER_H
#def SERVER_H

#include "ErrorCode.h"
class Server {
public:
    // Constructors
    Server();
    Server(int port);
    Server(int port, char * hostname);
    
    //Destructor
    virtual ~Server();
    
    //Public Methods
    virtual ErrorCode run() = 0;
    
private:
    Selector sel;
    ByteBuffer bread;
    ByteBuffer bwrtie;
    Builder build;
    Parser parse;
    
    ErrorCode init();
    ErrorCode openServerSocket();
    ErrorCode connectToServer();
};


#endif
