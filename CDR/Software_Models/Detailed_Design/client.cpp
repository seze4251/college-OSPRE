//
//  client.c
//  client
//
//  Created by Seth on 10/31/16.
//  Copyright © 2016 Seth. All rights reserved.
//


#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, const char **argv) {

    return 0;
    
    // Open Socket
    std::cout << "Open Socket" << std::endl;
    int fd;
    
    // Command to open Socket
    fd = socket(AF_INET, SOCK_STREAM, 0);
    
    // Check to see if Socket has been opened sucessfully
    if (fd == -1) {
        fprintf(stderr, "failed to allocate socket\n");
        return false;
    }

    
    // Bind Socket
    // Create a buffer for hostname
    char hostname[256];
    
    //Get computers hostname
    //Where is function defined?
    if (gethostname(hostname, sizeof (hostname)) != 0) {
        fprintf(stderr, "Error unable to get hostname, errno = %d\n", errno);
        return false;
    }
    
    fprintf(stdout, "hostname is <%s>\n", hostname);
    
    //Where is this struct defined??
    struct addrinfo *addrs, *addrs_head;
    
    // Where is function defined?
    if (getaddrinfo(hostname, NULL, NULL, &addrs) != 0) {
        fprintf(stderr, "getaddrinfo() failed\n");
        return false;
    }
    addrs_head = addrs;
    // iterate through all the alias until we find one that fits our parameters
    
    while (addrs != NULL) {
        if ( (addrs->ai_family == AF_INET) && (addrs->ai_socktype == SOCK_STREAM)
            ) {
            break;
        }
        addrs = addrs->ai_next;
    }
    
    if (addrs == NULL) {
        fprintf(stderr, "No address found\n");
        return false;
    }
    
    sockaddr_in* sin = (sockaddr_in*) addrs->ai_addr;
    sin->sin_port = 5130;
    
    // Where is function located
    if (bind(fd, (sockaddr*) sin, sizeof (*sin)) != 0) {
        fprintf(stderr, "bind() failed, errno = %d\n", errno);
        perror("errno = 49: ");
        return false;
    }

    
    std::cout << "Application Started" << std::endl;
    
    
    std::cout << "socket openned & bound" << std::endl;
    freeaddrinfo(addrs_head);
    
    std::cout << "Application Terminated" << std::endl;
    
    
    
    // Connect Socket
    
    
    // Read / Write to socket
    
    
}
