//
//  Spacecraft.h
//  Spacecraft
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include <string>
#include <ctime>


#include "Server.h"
#include "ServiceExternal.h"

class Spacecraft : public Server {
public:
    // Constructor
    Spacecraft(std::string hostName, int localPort);
    
    // Destructor
    ~Spacecraft();
    
    virtual void handleTimeout();
    void open();
    
private:
    time_t pollTime;
    ServiceExternal* scComms;
    
};

#endif

// Connect to ScComms

