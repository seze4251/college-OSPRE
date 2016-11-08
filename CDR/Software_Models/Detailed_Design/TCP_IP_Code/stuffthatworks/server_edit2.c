// To Do:
// What functionallity do I have to add in order to get reasonable model for abstraction? (Main Goal)
// Needed Now:
// 1. Make Sockets NonBlocking - LOW
// 2. handle multiple clients simultaneously - VERY LOW
// 3. Write Buffering (write flags for select) - High
// 4. Implement Timeouts - High
// 5. Client Attempts to reconnect to server when conneciton lost - HIGH
// 6. Find a smarter way to manage if statments - VERY VERY LOW
// 7. Implement application level communications protocol / message builders / message parsers - medium / HIGH
//        For 7: DO I NEED SERVER SUBCLASSES OR NOT?
// 8. break up main in to logical functions - High
//  FOR 8: DO I NEED SERVER SUBCLASSES? / WHAT ARE MY INTERNAL SERVER METHODS

// 9. handle SIGPIPE's so application doesn't exit when the client disconnects - HIGH
// ALL OTHER HIGHS ADD FUNCTIONALITY THAT I NEED TO GET DECENT WORKING MODEL

// Completed 5
// Completed 3


// Make Sockets Nonblocking
// Reorganize code
// Break into logical functions

#include <sys/time.h>
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
#include <sys/ioctl.h>

#define BUF_SIZE 500
typedef enum { false = 0, true = 1} bool;

static int sfd = -1, cfd = -1;

void init() {
    // Ignore signal SIGPIPE as the code will handle client disconnects directly
    signal(SIGPIPE, SIG_IGN);
    
   
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage Error: %s <port number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    init();
    
    // Create addrinfo structure hints on stack and 2 pointers to addrinfo structures
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    
    int s; //File Descriptors (sfd and cfd), return value parameter s
    
    // socklen_t is not really needed can probably cast a int / unsinged int to this type
    socklen_t peer_addr_len;
    
    
    // Zero out hints structure
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; // Stream Socket
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    
    // GETADDRINFO CALL <- need to learn more about
    s = getaddrinfo(NULL, argv[1], &hints, &result);
    
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    
    /* getaddrinfo() returns a list of address structures.
     Try each address until we successfully bind(2).
     If socket(2) (or bind(2)) fails, we (close the socket
     and) try the next address. */
    

    
    // BIND SERVER Socket
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
            continue;
        
        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;                  /* Success */
        
        close(sfd);
    }
    
    // Check to make sure bind to address succeeded
    if (rp == NULL) {
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }
    
    freeaddrinfo(result);           /* No longer needed, result is pointing towards head of Linked List */
    
    // Listen on Server Socket
    if (listen(sfd, 50) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    //Accept Connections on Server Socket
    // This sockaddr structure can be sockaddr_in or sockaddr doesn't matter due to union of structures
    
    int count = 0;
    fd_set readFds, writeFds;
    bool written = true;
    struct timeval timeout;
    char buf[BUF_SIZE];
    int nread, nwrite;
    
    while (1) {
        // Setup readFds & writeFds for select()
        FD_ZERO(&readFds);
        FD_ZERO(&writeFds);
        
        FD_SET(sfd, &readFds);
        
        if (cfd != -1) {
            if (written == true) {
                FD_SET(cfd, &readFds);
            } else {
                FD_SET(cfd, &writeFds);
            }
        }
        
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        
        int numSelect = select(FD_SETSIZE, &readFds, &writeFds, NULL, &timeout);
        
        if (numSelect == -1) { // Error Case
            
            if (errno == EINTR) {
                continue;
            } else {
                perror("select(): ");
                fprintf(stderr, "Application exiting \n");
                break;
            }
            
        } else if (numSelect == 0) { //Time Out Ohhh YEAHH
            fprintf(stderr, "Time Out Occured, I really should do something ... \n");
            continue;
        }
        
        // Handling data events
        if ((cfd != -1) && (FD_ISSET(cfd, &readFds) != 0)) {
            written = false;
            count++;
            nread = read(cfd, buf, BUF_SIZE);
            
            if (nread == -1) {
                perror("read() returned -1: ");
                close(cfd);
                cfd = -1;
            } else if (nread == 0) {
                perror("read() returned 0: ");
                close(cfd);
                cfd = -1;
            } else {
                fprintf(stdout, "Recived Message: <%s>\n", buf);
            }
        }
        
        if ((cfd != -1) && (FD_ISSET(cfd, &writeFds) != 0)) {
            written = true;
            nwrite = write(cfd, buf, nread);
            if (nwrite != nread) {
                fprintf(stderr, "Error sending response\n");
            }
        }
        
        if (FD_ISSET(sfd, &readFds) != 0) {
            struct sockaddr other_addr;
            peer_addr_len = sizeof(struct sockaddr_in);
            
            if (cfd == -1) {
                count = 0; // Reset Count
                written = true;
                cfd = accept(sfd, &other_addr, &peer_addr_len);
                fprintf(stdout, "Received client connection, processing input: %d\n", cfd);
                int opt = 1;
                ioctl(cfd, FIONBIO, &opt);
            } else {
                int temp = accept(sfd, NULL, NULL);
                fprintf(stdout, "Only handling one connection at a time, second connection shutdown");
                close(temp);
                continue;
            }
        }
        
        if ((count == 3) && (cfd != -1)) {
            sleep(1);
            close(cfd);
            printf("Closed Client Connection \n\n");
            cfd = -1;
        }
        
    }
    
    // Clean up
    close(sfd);
    
    if (cfd != -1) {
        close(cfd);
    }
    
}



