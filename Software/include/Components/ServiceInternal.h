//
//  ServiceInternal.h
//  ServiceInternal
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SERVICEINTERNAL_H
#define SERVICEINTERNAL_H

#include "Service.h"
#include "Builder.h"
#include "Parser.h"
#include "ByteBuffer.h"
#include <string>

class ServiceInternal : public Service {
public:
    ServiceInternal(Selector &sel) : Service(sel), readbuf(1024*1024), writebuf(1024*1024), build(writebuf), parse(readbuf) {
    }
    
    
protected:
    std::string hostName;
    int portNumber;
    ByteBuffer readbuf;
    ByteBuffer writebuf;
    Builder build;
    Parser parse;

    
private:

    
};

#endif
