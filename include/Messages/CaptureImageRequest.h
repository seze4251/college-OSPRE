//
//  CaptureImageRequest.h
//  CaptureImageRequest
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef CAPTUREIMAGEREQUEST_H
#define CAPTUREIMAGEREQUEST_H
#include <iostream>

#include "Message.h"

class CaptureImageRequest : public Message {
public:
    
    CaptureImageRequest() : Message(getMessageID(), time(0)), point(PEM_NA) { }
    
    virtual MessageID getMessageID() { return I_CaptureImageRequest; }
    
    void update(PointEarthMoon point, double* estimatedPosition) {
        this->timeStamp = time(0);
        this->point = point;
        memcpy(this->estimatedPosition, estimatedPosition, 3 * sizeof(double));
    }
    
    void print() {
        printMessageHeader();
        
        std::cout << "Estimated Position = ";
        for (int i = 0; i < 3; i++) {
            std::cout << estimatedPosition[i] << " ";
        }
        std::cout << " (km)" << std::endl;
        
        printEarthMoon(point);
    }
    
    // Specific Data Members
    PointEarthMoon point;
    double estimatedPosition[3];
};

#endif
