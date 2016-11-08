#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUF_SIZE 500

int
main(int argc, char *argv[])
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    
    int sfd, s; //File Descriptors
    
    struct sockaddr_storage peer_addr;
    socklen_t peer_addr_len;
    ssize_t nread;
    char buf[BUF_SIZE];
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    //Old
    //hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    //New
    hints.ai_socktype = SOCK_STREAM; // Stream Socket
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    //Dad thinks hints structure should be null
    //Node is a Hostname
    
    s = getaddrinfo(NULL, argv[1], &hints, &result);
    
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    
    /* getaddrinfo() returns a list of address structures.
     Try each address until we successfully bind(2).
     If socket(2) (or bind(2)) fails, we (close the socket
     and) try the next address. */
    
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype,
                     rp->ai_protocol);
        if (sfd == -1)
            continue;
        
        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;                  /* Success */
        
        close(sfd);
    }
    
    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }
    
    // Listen on socket
    
    if (listen(sfd, 50) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    //Accept call
    int cfd;
    struct sockaddr_in other_addr;
    
    peer_addr_len = sizeof(struct sockaddr_in);
    cfd = accept(sfd, (struct sockaddr *) &other_addr,
                 &peer_addr_len);
    printf("CFD: %d",cfd);
    
    freeaddrinfo(result);           /* No longer needed */
    
    /* Read datagrams and echo them back to sender */
    
    while (1)  {
        // peer_addr_len = sizeof(struct sockaddr_storage);
        nread = read(cfd, buf, BUF_SIZE);
        if (nread == -1) {
            printf("read failed\n");
            continue;               /* Ignore failed request */
        }
        
        printf("Recived Message: %s\n",buf);
        
        int nwrite = write(cfd, buf, nread);
        printf("nwrite = %d, nread = %zd\n",nwrite, nread);
        
        if (nwrite != nread) {
            fprintf(stderr, "Error sending response\n");
        }
        else {
            break;
        }
        
    }
}



