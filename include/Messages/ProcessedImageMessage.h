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
    
    void print(FILE* logFile) {
        fprintf(logFile, "Printing Processed Image Message\n");
        printMessageHeader(logFile);
        fprintf(logFile, "alpha = %f, beta = %f, theta = %f, Pixel Error = %f, TimeStep = %ld\n", alpha, beta, theta, pixel_error, timeStamp);
        printEarthMoon(point, logFile);
    }
    
    // Specific Data Members
    double alpha;
    double beta;
    double theta;
    double pixel_error;
    PointEarthMoon point;
};

#endif
