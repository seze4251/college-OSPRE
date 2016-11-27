//
//  Spacecraft.h
//  Spacecraft
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include "Server.h"
#include "ErrorCode.h"

class Spacecraft : public Server {
public:
    Spacecraft(int localPort);
    ~Spacecraft();
    
private:
    
};

#endif
