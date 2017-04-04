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
// #include <sys/select.h>
#include <signal.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <ctime>
#include <fstream>

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
    fprintf(Server::getAppl()->logFile, "SIG_TERM: Program Terminated by User \n");
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

void Server::readOSPREServerConfigFile() {
    std::ifstream file("Text_Data/OSPRE_Server_Config.txt");
    
    if (!file) {
        fprintf(logFile, "Error: read Config File: Text_Data/OSPRE_Server_Config.txt could not be opened for reading\n");
        throw "Server Config File Could Not Be Opened for Reading";
    }
    
    std::string line;
    int holder;
    std::getline(file, line);
    
    // Read in bool to determine whether we are in config mode or live mode
    file >> holder;
    if (holder == 1) {
        liveMode = true;
        fprintf(logFile, "MODE Choice: OSPRE in LIVE mode\n");
        return;
    } else if (holder == 2) {
        liveMode = false;
        fprintf(logFile, "MODE Choice: OSPRE in SIM mode\n");
        
    } else {
        throw "ServerInternal::readOSPREServerConfigFile, invalid mode input, please put 1 or 2";
    }
    
    std::getline(file, line);
    std::getline(file, line);
    
    file >> testDIR;
    
    if (testDIR.empty() == true) {
        fprintf(logFile, "Error: ServerInternal::readOSPREServerConfigFile() test dir string is empty");
        throw "ServerInternal::readOSPREServerConfigFile() test dir string is empty";
    }
}




