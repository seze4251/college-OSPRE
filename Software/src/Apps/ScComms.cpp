//
//  ScComms.cpp
//  ScComms
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include "ScComms.h"
#include "Service.h" 

ScComms::ScComms(int localPort) : Server() {
    fd = Service::connectToServer("localhost", 5000);
}

ScComms::~ScComms() {
    
}
