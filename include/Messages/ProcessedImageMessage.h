//
//  ProcessedImageMessage.h
//  ProcessedImageMessage
//
//  Created by Seth on 1/26/2017.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef PROCESSEDIMAGEMESSAGE_H
#define PROCESSEDIMAGEMESSAGE_H

#include <vector>
#include <iostream>

#include "Message.h"

class ProcessedImageMessage : public Message {
public:
    ProcessedImageMessage() : Message(getMessageID(), time(0)){}
    
    MessageID getMessageID() {return I_ProcessedImageMessage;}
    
    void update(double alpha, double beta, double theta, double pixel_error, PointEarthMoon point, time_t timeStamp) {
        this->timeStamp = timeStamp;
        this->alpha = alpha;
        this->beta = beta;
        this->theta = theta;
        this->pixel_error = pixel_error;
        this->point = point;
    }
    
    void print() {
        printMessageHeader();
        std::cout<< "alpha = " << alpha  << " beta = " << beta << " theta = " << theta << std::endl;
        std::cout << "Pixel Error = " << pixel_error << "TimeStamp = " << timeStamp << std::endl;
        printEarthMoon(point);
    }
    
    // Specific Data Members
    double alpha;
    double beta;
    double theta;
    double pixel_error;
    PointEarthMoon point;
};

#endif
