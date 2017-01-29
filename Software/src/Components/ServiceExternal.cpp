//
//  ServiceExternal.cpp
//  ServiceExternal
//
//  Created by Seth on 1/29/2017.
//  Copyright © 2016 Seth. All rights reserved.
//


#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#include "ServiceExternal.h"


// Constructor
ServiceExternal::ServiceExternal(Selector& sel, int fd, int buffSize) : Service(sel), fd(fd), readbuf(buffSize), writebuf(buffSize), build(writebuf), parse(readbuf) {
    std::cout << "ServiceExternal Constructor Called" << std::endl;
}

// Destructor
ServiceExternal::~ServiceExternal() {
    
}

//Initialize InternalService Methods
bool ServiceExternal::open(int fd) {
  // ServiceInternal Code, Need to implement for ServiceExternal
    /*
    std::cout << "Service Internal Open(int fd)" << std::endl;
    this->fd = fd;
    getSelector().registerService(fd, this);
    getSelector().interestInRead(fd);
    return true;
     */
    return false;
}

bool ServiceExternal::open(std::string hostName, int portNumber) {
    // Service Internal Code, Need to implement for ServiceExternal
  /*
    fd = Service::connectToServer(hostName.c_str(), portNumber);
    
    if (fd == -1) {
        return false;
    }
    
    getSelector().registerService(fd, this);
    getSelector().interestInRead(fd);
    return true;
   */
    return false;
}


// Virtual Methods from Server
void ServiceExternal::handleRead() {
    // Service Internal Code, need to implement for Service External
    /*
    std::cout << "Entering ServiceInternal::handleRead()" << std::endl;
    int length = readbuf.remaining();
    
    if (length == 0) {
        std::cout << "ServiceInternal::handleRead(): No room to read into buffer" << std::endl;
    }
    
    char* buf = readbuf.getBuffer();
    int amountRead = -1;
    
    while (amountRead < 0) {
        amountRead = ::read(fd, buf, length);
        std::cout << "handleRead(): Amount Read: " << amountRead << std::endl;
        
        // ToDo: Revisit code confiriming MANPAGE on read error conditions
        if (amountRead == 0) {
            std::cerr << "ServiceInternal::handleRead(): read() returned 0, closing connection" << std::endl;
            closeConnection();
            return;
            
        } else if (amountRead == -1) {
            if (errno == EINTR) {
                continue;
            } else {
                perror("Error: ");
                closeConnection();
                return;
            }
        }
    }
    
    readbuf.positionRead(amountRead);
    
    ///-**************
    //TEMP
    readbuf.printBuffer();
    //TEMP
    //-********************
    
    Message* msg = nullptr;
    int count = 0;
    
    // Flip Buffer
    readbuf.flip();
    
    while (true) {
        msg = parse.parseMessage();
        if (msg == nullptr) {
            break;
        }
        
        (*messageCallBack)(msg, this);
        count++;
    }
    
    //Compact and flip buffer
    readbuf.compact();
    readbuf.flip();
    
    if (count == 0) {
        std::cerr << "ServiceInternal::handleRead(): Message is big for buffer" << std::endl;
        closeConnection();
        return;
    }
    
    std::cout << "ServiceInternal::handleRead(): messagesParsed: " << count << std::endl;
    */
}



void ServiceExternal::handleWrite() {
    // ServiceInternalCode, need to implement for ServiceExternal
 /*
  std::cout << "Entering ServiceInternal::handleWrite()" << std::endl;
    int length = writebuf.used();
    std::cout << "handleWrite int length: " << length << std::endl;
    
    if (length == 0) {
        std::cout << "Nothing Left to Write to Socket" << std::endl;
        getSelector().noInterestInWrite(fd);
        return;
    }
    
    
    std::cout << "ServiceInternal::handleWrite(): Printing Write Buffer" << std::endl;
    writebuf.printBuffer();
    
    
    writebuf.flip();
    
    char* buf = writebuf.getBuffer();
    
    int amountWritten = write(fd, buf, length);
    std::cout << "Wrote " << amountWritten << " Bytes" << std::endl;
    if (amountWritten == length) {
        writebuf.clear();
        getSelector().noInterestInWrite(fd);
    } else {
        // Compact Buffer and keep the interest in writing with selector
        writebuf.positionWrite(amountWritten);
        writebuf.compact();
        writebuf.flip();
    }
  */
}

void ServiceExternal::closeConnection() {
    if (fd != -1) {
        getSelector().unregisterService(fd);
        ::close(fd);
        fd = -1;
    }
    readbuf.clear();
    writebuf.clear();
}

//Send Message Functions

void ServiceExternal::sendDataMessage() {
    
}

void ServiceExternal::sendSolutionMessage() {
    
}






