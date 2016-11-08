//
//  sc.cpp
//  sc
//
//  Created by Seth on 10/31/16.
//  Copyright © 2016 Seth. All rights reserved.
//


#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

class Message {
public:
    int a, b, c;
    double aa, bb, cc;
    std::string name;
    bool status;
    
    Message() {
        status = true;
        name = "Hello";
        a = 1;
        b = 2;
        c = 3;
        aa = 4;
        bb = 5;
        cc = 6;
    }
    
};

class Spacecraft{
    int fd, localport, serverport;
    char hostname[256];
    
    int connectToSCComms(){
        // Open Socket
        std::cout << "Entered connect() attempting to open socket ..." << std::endl;
        
        // Command to open Socket
        fd = socket(AF_INET, SOCK_STREAM, 0);
        
        // Check to see if Socket has been opened sucessfully
        if (fd == -1) {
            std::cerr << "failed to allocate socket\n";
            return -1;
        }
        
        
        // Bind Socket
        //Get computers hostname
        if (gethostname(hostname, sizeof (hostname)) != 0) {
            std::cerr << "Error unable to get hostname, errno = %d\n" << errno;
            return -2;
        }
        
        struct addrinfo *addrs, *addrs_head;
        std::cout << "\n" << hostname << "\n" << std::endl;
        
        int holder = getaddrinfo(hostname, NULL, NULL, &addrs);
        
        std::cout << "foo" << std::endl;
        if ( holder!= 0) {
            
            fprintf(stderr, "getaddrinfo() failed\n errno = %d, holder = %d", errno, holder);
            return -5;
        }
        
        std::cout << "booger" << std::endl;
        
        addrs_head = addrs; // Save the head to free the memory
        
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
            return -3;
        }
        
        sockaddr_in* sin = (sockaddr_in*) addrs->ai_addr;
        sin->sin_port = localport;
        
        
        if (bind(fd, (sockaddr*) sin, sizeof (*sin)) != 0) {
            fprintf(stderr, "bind() failed, errno = %d\n", errno);
            perror("errno = 49: ");
            return -4;
        }
        
        std::cout << "socket openned & bound" << std::endl;
        
        sockaddr * saddr_p, saddr;
        
        saddr_p = & saddr;

        saddr.sa_family = AF_INET; // CORE DUMPING HERE HA WHY???

        bcopy( hostname, saddr.sa_data, strlen(hostname));
        
        
        std::cout << "A" << std::endl;
        
        if (connect(fd, saddr_p, sizeof(saddr)) < 0)
            error("ERROR connecting");

        
        std::cout << "B" << std::endl;

        freeaddrinfo(addrs_head);
        
        std::cout << "C" << std::endl;

        return 0;
    }
    
    void error(std::string str) {
        std::cerr << str;
        exit(0);
    }
    
public:
    Spacecraft(char hostname[], int localport, int serverport) {
        this->localport = localport;
        this->serverport = serverport;
        bcopy(hostname,
              this->hostname,
              strlen(hostname));
    }
    
    int run() {
        // Connect to S/C Comms
        if (connectToSCComms() != 0) {
            fprintf(stderr, "failed to allocate socket\n");
            return -1;
        }
        
        std::cout << "D" << std::endl;

        int n;
        char buffer[256];
        while (1) {
            printf("Please enter the message: ");
            bzero(buffer,256);
            fgets(buffer,sizeof(buffer)-1,stdin);
            n = write(fd, buffer, strlen(buffer));
            if (n < 0) {
                error("ERROR writing to socket");
                return -2;
            }
            
            sleep(2);
        }
    }
};

int main(int argc, char **argv) {
    if (argc != 4) {
        std::cerr << "usage %s hostname, localport, serverport";
        exit(0);
    }
    
    Spacecraft sc(argv[1], atoi(argv[2]), atoi(argv[3]));
    sc.run();
}
