//
//  ServiceExternal.h
//  ServiceExternal
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SERVICEEXTERNAL_H
#define SERVICEEXTERNAL_H
#include <string>
#include <iostream>
#include <vector>

#include "Service.h"
#include "External_Builder.h"
#include "External_Parser.h"
#include "ByteBuffer.h"

class ServiceExternal : public Service {
public:
    // Service Virtual Methods
    virtual void handleRead();
    virtual void handleWrite();
    virtual bool isConnected();
    virtual void closeConnection() { return fd != -1 ? true : false; }
    
protected:
    
private:
    int fd;
    ByteBuffer readbuf;
    ByteBuffer writebuf;
    External_Builder build;
    External_Parser parse;
    
    
};

#endif
