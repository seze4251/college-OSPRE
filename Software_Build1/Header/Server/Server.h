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
    virtual ErrorCode handleMessages() = 0;
    
private:
    int localPort; // Port Number that Server Port Listens on
    std::vector<int> *serverPorts; // List of Port Numbers to connect to
    char **serverHosts; // List of Hostnames corresponding with PortNumbers to connect to
    std::vector<int> fds; //list of file descriptors where the first file descriptor is always the Server Socket
    Selector sel;
    ByteBuffer bread;
    ByteBuffer bwrite;
    Builder build;
    Parser parse;
    TimeoutManager timeout;
    
    // Private Methods
    ErrorCode openServerSocket();
    ErrorCode connectToServer(int serverPort, char *serverHosts);
    
};

#endif
