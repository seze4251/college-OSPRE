//
//  Service.cpp
//  Service
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include "Service.h"
#include <iostream>
#include <string>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/select.h>
#include <signal.h>
#include <errno.h>
#include <sys/ioctl.h>

Service::Service(Selector &sharedSel) : sel(sharedSel) {
    std::cout << "Service Constructor \n";
}

int Service::openServerSocket(int portNumber) {
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM; // Stream Socket
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    
    char buf[16];
    sprintf(buf, "%d", portNumber);
    int s = ::getaddrinfo(NULL, buf, &hints, &result);
    
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        return -1;
    }
    
    // Bind Server Socket
    int sfd = -1;
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        // printf("family %d, socketType %d, protocol %d\n", rp->ai_family,
        //       rp->ai_socktype, rp->ai_protocol);
        
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        
        // Set socket to reuse address
        int reuse = 1;
        
        if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0) {
            perror("setsockopt(SO_REUSEADDR) failed");
        }
        
        if (sfd == -1)
            continue;
        
        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0) {
            break;                  /* Success */
        }
        close(sfd);
    }
    
    // Check to make sure bind to address succeeded
    if (sfd == -1) {
        std::cout << "Open Server Socket Failed \n";
        return -1;
    }
    
    freeaddrinfo(result);
    
    // Listen on Server Socket for incomming connections
    if (listen(sfd, 4) == -1) {
        perror("listen");
        std::cout << "Open Server Socket Failed \n";
        return -1;
    }
    
    return sfd;
}

int Service::connectToServer(const char *serverHosts, int serverPort) {
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    
    /* Obtain address(es) matching host/port */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; // TCP Stream Socket
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */
    
    char buf[16];
    sprintf(buf, "%d", serverPort);
    
    int s = ::getaddrinfo(serverHosts, buf, &hints, &result);
    
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        return -1;
    }
    
    int fd = -1;
    
    for (int i =0; i < 1; i++) {
        for (rp = result; rp != NULL; rp = rp->ai_next) {
            fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
            
            // Check to see if socket opens
            if (fd == -1) {
                continue;
            }
            
            // Attempt to connect socket
            if (connect(fd, rp->ai_addr, rp->ai_addrlen) != -1) {
              //  std::cout<< "CONNECTED\n" << std::endl;
                break;
            }
            
            close(fd);
            fd = -1;
        }
        
        if (fd != -1) {
            break;
        }
        
      //  std::cout << "Service::connectToServer(): Failed to connect on " << i+1 << "/1 tries, Sleeping for 1 seconds" << std::endl;
        //sleep(1);
    }
    
    if (fd == -1) {
        fprintf(stderr, "Service::connectToServer(): Could not Connect\n");
        return -1;
    }
    
    freeaddrinfo(result);
    return fd;
}
