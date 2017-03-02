//
//  Server.h
//  Server
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#include <iostream>
#include <sys/time.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/select.h>
#include <signal.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <ctime>

#include "Server.h"

Server* Server::appl;
void signalHandler(int);

Server::Server() {
    signal(SIGTERM, signalHandler);
    signal(SIGPIPE, SIG_IGN);
    t_val.tv_sec = 5;
    t_val.tv_usec = 0;
    flushTime = 0;
}

Server::~Server() {
    
}

void signalHandler(int) {
    fprintf(Server::getAppl()->logFile, "SIG_TERM: Program Terminated by User n");
    fflush(Server::getAppl()->logFile);
    fclose(Server::getAppl()->logFile);
    exit(0);
}

Selector& Server::getSelector() {
    return sel;
}

Server* Server::getAppl() {
    return appl;
}

void Server::setAppl(Server* srv) {
    appl = srv;
}

void Server::handleTimeout() {
    std::cout << "Server::handleTimeout() I should do something here" << std::endl;
}

void Server::setTimeoutTime(int sec, int micro) {
    t_val.tv_sec = sec;
    t_val.tv_usec = micro;
}

void Server::flushLog() {
    int tempTime = time(0);
    
    if ((tempTime - flushTime) > 10) {
        fflush(logFile);
        flushTime = tempTime;
    }
}

int Server::run() {
    bool terminateFlag = false;
    timeval tempTimeVal;
    
    while (terminateFlag == false) {
        tempTimeVal = t_val;
        if (sel.select(&tempTimeVal) == -1) {
            throw "Server::run() select() error";
            break;
        }
        
        handleTimeout();
    }
    
    return 0;
}

/*
// in the file you are registering the signal handler
 #include <signal.h>
 
 //before the function where you want to register the handler
 extern bool flag = false;
 
 void signalHandler(int) {
    flag = true;
 }

 //register the signal handler
 signal(SIGTERM, signalHandler);
 
 //check flag to see if the signal has been received. If non-fatal then reset the flag back to false.
 if (flag == true) {
    flag = false;
    doSomething();  // possibly break out of your mainloop()
 }
 
 // Notes: signalHandler() will get called upon receipt of this signal. It can happen anytime at any point in time. You want to do the very minimum inside a signal handler.
 // Also, between the time the flag is checked and the time it is reset to false, the signalHandler() might have been invoked again.
*/
