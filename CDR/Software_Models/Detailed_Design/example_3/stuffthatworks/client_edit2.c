#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/select.h>
#include <signal.h>
#include <errno.h>

#define BUF_SIZE 500

typedef enum { false, true } bool;

// 1. Modify this code to use TCP/IP non blocking sockets
// 2. Use main loop Select() to decide when read is availble and write

int main(int argc, char *argv[]) {
    
    if (argc < 3) {
        fprintf(stderr, "Usage: %s host port msg...\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    
    /* Obtain address(es) matching host/port */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; // TCP Stream Socket
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */
    
    int s = getaddrinfo(argv[1], argv[2], &hints, &result);
    
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    
    /* getaddrinfo() returns a list of address structures.
     Try each address until we successfully connect(2).
     If socket(2) (or connect(2)) fails, we (close the socket
     and) try the next address. */
    
    int sfd;
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        // Open Socket
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        
        // Check to see if socket opens
        if (sfd == -1)
            continue;
        
        // Attempt to connect socket
        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
            printf("Connected\n");
        break;                  /* Success */
        
        close(sfd);
    }
    
    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not Connect\n");
        exit(EXIT_FAILURE);
    }
    
    int  len = strlen(argv[3]) + 1, nread, nwrite;
    char buf[BUF_SIZE];
    bool written = false;
    fd_set readFds, writeFds;
    
    while(1) {
        FD_ZERO(&readFds);
        FD_ZERO(&writeFds);
        
        // If written = false - want to write, else want to read
        if (written == false) {
            FD_SET(sfd, &writeFds);
        } else {
            FD_SET(sfd, &readFds);
        }
        
        int numSelect = select(FD_SETSIZE, &readFds, &writeFds, NULL, NULL);
        
        if (numSelect == -1) { // Error Case
            
            if (errno == EINTR) {
                printf("11111\n");
                continue;
            } else { // (Disconnected Socket?)
                printf("222222\n");
                perror("select(): ");
                fprintf(stderr, "Application exiting\n");
                break;
            }
            
        } else if (numSelect == 0) { //Time Out (Disconnected Socket?) (NormallY)
            printf("333333\n");
            perror("select(): ");
            fprintf(stderr, "Application exiting\n");
            break;
        }
        
        // Handling data events
        if  (FD_ISSET(sfd, &readFds) != 0) {
            written = false;
            nread = read(sfd, buf, BUF_SIZE);
            
            if ((nread == -1) || (nread == 0)) {
                perror("read(): ");
                printf("nread: %d, Server ended connection, closing socket and trying to reconnect\n", nread);
                close(sfd);
                
                for (rp = result; rp != NULL; rp = rp->ai_next) {
                    // Open Socket
                    sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
                    
                    // Check to see if socket opens
                    if (sfd == -1)
                        continue;
                    
                    // Attempt to connect socket
                    if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
                        printf("Connected\n");
                    break;                  /* Success */
                    
                    close(sfd);
                }
                
                if (rp == NULL) {               /* No address succeeded */
                    fprintf(stderr, "Could not Reconnect Socket\n");
                    break;
                }
                
            } else {
                fprintf(stdout, "Bytes Recived: %d,  Message: <%s>\n", nread, buf);
            }
        }
        
        if (FD_ISSET(sfd, &writeFds) != 0) {
            if (write(sfd, argv[3], len) != len) {
                fprintf(stderr, "partial/failed write\n");
                exit(EXIT_FAILURE);
            }
            written = true;
        }
    }
    
    // Cleanup
    if (sfd > 0) {
        close(sfd);
    }
    freeaddrinfo(result);
}
