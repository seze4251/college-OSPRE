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
#include <signal.h>

#define BUF_SIZE 500
typedef enum { false, true } bool;

static int sfd;

//Function Definitions
void init(char* hostName, char* portNumber);
int connectToServer(char* hostName, char* portNumber);
void run(char* hostName, char* portNumber, char * message);
void cleanup();


int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage Error: %s hostname, port number, msg\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    printf("initializing application\n");
    init(argv[1], argv[2]);
    printf("running\n");
    run(argv[1], argv[2], argv[3]);
    printf("cleaning up\n");
    cleanup();
    return 0;
}


void init(char* hostName, char* portNumber) {
     // Ignore signal SIGPIPE as the code will handle client disconnects directly
    signal(SIGPIPE, SIG_IGN);
    sfd = -1;
    sfd = connectToServer(hostName, portNumber);
}


int connectToServer(char* hostName, char* portNumber) {
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    
    /* Obtain address(es) matching host/port */
    memset(&hints, 0, sizeof(struct addrinfo));
    //hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM; // TCP Stream Socket
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */
    
    //int s = getaddrinfo(hostName, portNumber, &hints, &result);
    int s = getaddrinfo(hostName, portNumber, &hints, &result);
    
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    
    int fd;
    
    while (1) {
        for (rp = result; rp != NULL; rp = rp->ai_next) {
            // Open Socket
            printf("family %d, socketType %d, protocol %d\n", rp->ai_family,
                   rp->ai_socktype, rp->ai_protocol);
            
            fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
            
            // Check to see if socket opens
            if (fd == -1) {
                fprintf(stderr, "failed to open socket\n");
                continue;
            }
            
            // **********TEMP********************
            //((struct sockaddr_in*) (rp->ai_addr))->sin_port = 6009;
            
            // printf("attempting to connect to port %d\n", ((struct sockaddr_in*) (rp->ai_addr))->sin_port);
            // **********TEMP********************
            
            // Attempt to connect socket
            if (connect(fd, rp->ai_addr, rp->ai_addrlen) != -1) {
                printf("Connected\n");
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
    
    if (fd == -1) {               /* No address succeeded */
        fprintf(stderr, "Could not Connect\n");
        exit(EXIT_FAILURE);
    }
    
    freeaddrinfo(result);
    return fd;
}


void run(char* hostName, char* portNumber, char * message) {
    int  nread, nwrite, messagelen = strlen(message) + 1;
    char buf[BUF_SIZE];
    bool written = false;
    fd_set readFds, writeFds;
    
    while (1) {
        FD_ZERO(&readFds);
        FD_ZERO(&writeFds);
        
        // If written == false > write, else > read
        if (written == false) {
            FD_SET(sfd, &writeFds);
        } else {
            FD_SET(sfd, &readFds);
        }
        
        int numSelect = select(FD_SETSIZE, &readFds, &writeFds, NULL, NULL);
        
        if (numSelect == -1) { // Handle Error Case
            
            if (errno == EINTR) {
                continue;
            } else {
                perror("select(): ");
                fprintf(stderr, "Application exiting\n");
                return;
            }
            
        } else if (numSelect == 0) { // Handle Time Out Case
            perror("select(): ");
            fprintf(stderr, "Application exiting\n");
            break;
        }
        
        // Handle data events
        if  (FD_ISSET(sfd, &readFds) != 0) {
            written = false;
            nread = read(sfd, buf, BUF_SIZE);
            
            if ((nread == -1) || (nread == 0)) { // Handle Server Disconnection
                perror("read(): ");
                printf("nread: %d, Server ended connection, closing socket and trying to reconnect\n", nread);
                sfd = connectToServer(hostName, portNumber);
            } else {
                fprintf(stdout, "Bytes Recived: %d,  Message: <%s>\n", nread, buf);
            }
        }
        
        if (FD_ISSET(sfd, &writeFds) != 0) {
            if (write(sfd, message, messagelen) != messagelen) {
                fprintf(stderr, "partial/failed write\n");
                exit(EXIT_FAILURE);
            }
            written = true;
        }
    }
    
}


void cleanup() {
    if (sfd > 0) {
        close(sfd);
    }
    
}
