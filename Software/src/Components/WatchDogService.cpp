


WatchDogService::WatchDogService(std::string hostName, int portNumber) {
    fd = -1;
}

void WatchDogService::handleRead() {
    int numRead = read(fd, readbuf); // you need to create this read() it usese a a ByteBuffer.
    
    
    if (numRead == 0) {
        // handle error case
    }
    
    
    // determine if you have a complete message
    // if yes, pass it to the parser to extract that message
    // keep extracting messages until you've extracted all of them.
    // protected methods of internal service
    
    // ^^ Belongs in Internal Service
    // All Below belongs in internal Service
    // Belongs in WatchDogService
    // for each message do what you are supposed to do with that message.
    // Virtual Method of InternalService
    
    // Do I have data to write!
    // Tell Selector that I am interested in writing
    
}

void WatchDogService::handleWrite() {
    
    
    // After written, Tell selector no longer interested if no more data to write
    
}

void WatchDogService::close() {
    if (fd != -1) {
        close(fd);
        fd = -1;
    }
    readBuf.clear();
    writeBuf.clear();
}

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

