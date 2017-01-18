//
//  ServiceInternal.h
//  ServiceInternal
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SERVICEINTERNAL_H
#define SERVICEINTERNAL_H
#include <string>
#include <iostream> 

#include "Service.h"
#include "Builder.h"
#include "Parser.h"
#include "ByteBuffer.h"


class ServiceInternal : public Service {
public:
    ServiceInternal(Selector& sel, int fd = -1) : Service(sel), fd(fd), readbuf(1024*1024), writebuf(1024*1024), build(writebuf), parse(readbuf) {
        std::cout << "ServiceInternal Constructor Called" << std::endl;
    }
    
    void handleRead();
    void handleWrite();
    
    void registerCallback(void (*messageCallBackFunc)(Message*));
    
protected:
    int fd;
    ByteBuffer readbuf;
    ByteBuffer writebuf;
    Builder build;
    Parser parse;

private:
    int parseAndProcessMessages();
    void (*messageCallBack)(Message*);

    
};

#endif
