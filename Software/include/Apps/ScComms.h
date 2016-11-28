//
//  ScComms.h
//  ScComms
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SCCOMMS_H
#define SCCOMMS_H

#include "Server.h"
#include "ErrorCode.h"

class ScComms : public Server {
public:
    ScComms(int localPort);
    ~ScComms();
    
private:
    int fd;
};

#endif
