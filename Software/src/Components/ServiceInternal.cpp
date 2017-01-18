//
//  WatchDogClientHandler.cpp
//  WatchDogClientHandler
//
//  Created by Seth on 11/27/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#include "ServiceInternal.h"

void ServiceInternal::registerCallback(void (*messageCallBackFunc)(Message*)) {
    std::cout << "ServiceInternal registerCallback()" << std::endl;
    messageCallBack = messageCallBackFunc;
}

int ServiceInternal::parseAndProcessMessages() {
    Message* msg = nullptr;
    int count = 0;
    // Flip Buffer
    readbuf.flip();
    
    while (true) {
        msg = parse.parseMessage();
        if (msg == nullptr) {
            break;
        }
        
        (*messageCallBack)(msg);
        count++;
    }
    //Move Read Position
    readbuf.compact();
    writebuf.flip();
    return count;
}

void ServiceInternal::handleRead() {
    std::cout << "Entering ServiceInternal::handleRead()" << std::endl;
    int length = readbuf.remaining();
    
    if (length == 0) {
        std::cout << "ServiceInternal::handleRead(): No room to read into buffer" << std::endl;
        
        if (parseAndProcessMessages() == 0) {
            std::cerr << "ServiceInternal::handleRead(): Message is big for buffer" << std::endl;
            closeConnection();
        }
        return;
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
    
    ///**************
    //TEMP
    readbuf.printBuffer();
    //TEMP
    //********************
    
    // Handle All Messages
    int messagesParsed = parseAndProcessMessages();
    std::cout << "ServiceInternal::handleRead(): messagesParsed: " << messagesParsed << std::endl;
}

void ServiceInternal::handleWrite() {
    std::cout << "Entering ServiceInternal::handleWrite()" << std::endl;
    int length = writebuf.used();
    
    if (length == 0) {
        std::cout << "Nothing Left to Write to Socket" << std::endl;
        getSelector().noInterestInWrite(fd);
        return;
    }
    
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
}

