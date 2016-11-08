int bind(int sockfd, const struct sockaddr *addr,
         socklen_t addrlen);



int bind(int sockfd, const struct sockaddr_in *addr, socklen_t addrlen);



int bind(int sockfd, sas *addr, socklen_t addrlen);

sockaddr_in * seth;

sockaddr_in howard;

= new sockaddr_in;

(sockaddr*) seth;


union {
     sockaddr a;
     sockaddr_in b;
     sockaddr_un c;
} sas;


int connect(int sockfd, const struct sockaddr *addr,
            socklen_t addrlen);








int socket(int domain, int type, int protocol);

int getaddrinfo(const char *node, const char *service,
                const struct addrinfo *hints,
                struct addrinfo **res);

void freeaddrinfo(struct addrinfo *res);

const char *gai_strerror(int errcode);


int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);


