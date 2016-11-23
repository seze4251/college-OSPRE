//
//  Server.h
//  Server
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include "Server.h"
#include <iostream>

#include <sys/time.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/select.h>
#include <signal.h>
#include <errno.h>
#include <sys/ioctl.h>



// Ignores SIG Pipes and opens up Server Socket
Server::Server(int localPort) {
    // Initialize Members
    this -> localPort = port;
    
    fds.reserve(10); // Set capacity to 10 for fds
    signal(SIGPIPE, SIG_IGN);
    
    // Open Server Socket
    handleError(openServerSocket());
}

// Ignores SIG Pipes, opens up Server Socket and attempts to connect to all other connections
Server::Server(int localPort, std::vector<int> *serverPorts, char **serverHosts) {
    // Initialize Members
    this -> localPort = localPort;
    this -> serverPorts = serverPorts;
    this -> serverHosts = serverHosts;
    
    fds.reserve(10); // Set capacity to 10 for fds
    signal(SIGPIPE, SIG_IGN);
    
    // Open Server Socket
    handleError(openServerSocket());
    
    // Connect to all other Servers
    int i = 0;
    for (auto &element: *serverPorts) {
        handleError(connectToServer(element, serverHosts[i]));
    }
}

// Always opens Server Socket on fds[0]
ErrorCode Server::openServerSocket() {
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM; // Stream Socket
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    
    int s = getaddrinfo(NULL, portNumber, &hints, &result);
    
    if (s != 0) {
        return E_GETADDRINFO;
    }
    
    // Bind Server Socket
    int sfd = -1;
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        // printf("family %d, socketType %d, protocol %d\n", rp->ai_family,
        //       rp->ai_socktype, rp->ai_protocol);
        
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
            continue;
        
        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0) {
            break;                  /* Success */
        }
        close(sfd);
    }
    
    // Check to make sure bind to address succeeded
    if (sfd == -1) {
        return E_BIND_UNSUCCESSFUL;
    }
    
    freeaddrinfo(result);
    
    // Listen on Server Socket for incomming connections
    if (listen(sfd, 4) == -1) {
        return E_LISTEN_FAILURE;
    }
    
    fds[0] = sfd;
    return SUCCESS;
}

ErrorCode Server::connectToServer(int serverPort, char *serverHosts) {
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    
    /* Obtain address(es) matching host/port */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; // TCP Stream Socket
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */
    
    
    int s = getaddrinfo(serverHosts, serverPort, &hints, &result);
    
    if (s != 0) {
        return E_GETADDRINFO;
    }
    
    int fd = -1;
    
    while (1) {
        for (rp = result; rp != NULL; rp = rp->ai_next) {
            fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
            
            // Check to see if socket opens
            if (fd == -1) {
                continue;
            }
            
            // Attempt to connect socket
            if (connect(fd, rp->ai_addr, rp->ai_addrlen) != -1) {
                break;
            }
            
            close(fd);
            fd = -1;
        }
        
        if (fd != -1) {
            break;
        }
        
        fprintf(stdout, "failed to connect, sleeping for 10, will try again\n");
        sleep(10);
    }
    
    if (fd == -1) {
        return E_CONNECTION_FAILURE;
    }
    
    freeaddrinfo(result);
    fds.push_back(fd);
}

ErrorCode Server::run() {
    while (1) {
        // Zero Read and Write FDS
        sel.zeroFDs();
        
        // Register for Read and Write Events
        sel.registerForReadEvents(fdsRead);
        sel.registerForWriteEvents(fdsWrite);
        
        // Select call
        handleError(sel.select(&timeout));
        
        // Handle Time Out
        handleError(timeout.handleTimeout);
        
        // Parse / Build Messages
        
        
        // Handle Messages
        handleError(handleMessages());
    }
}


