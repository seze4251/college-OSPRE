//
//  GNC.h
//  GNC
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef GNC_H
#define GNC_H

#include "Server.h"

class GNC : public Server {
public:
    GNC(int localPort);
    ~GNC();
    virtual void handleTimeout();
private:
    
};

#endif
