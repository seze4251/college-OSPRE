//
//  ImageMessage.h
//  ImageMessage
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef IMAGEMESSAGE_H
#define IMAGEMESSAGE_H

#define IMAGE_SIZE 2428800

#include "Message.h"

class ImageMessage : public Message {
public:
    ImageMessage() : Message(getMessageID(), time(0)), point(PEM_NA){
        image = new char[IMAGE_SIZE];
        imageBufferSize = IMAGE_SIZE;
    }
    
    ~ImageMessage() {
        delete[] image;
    }
    
    MessageID getMessageID() { return I_ImageMessage; }
    
    void print(FILE* logFile) {
        fprintf(logFile, "Printing Image Message\n");
        printMessageHeader(logFile);
        printEarthMoon(point, logFile);
        fprintf(logFile, "Current Image Size = %d, Total Buffer Size = %d\n", currentImageSize, imageBufferSize);

        fprintf(logFile, "pix_deg = ");
        for (int i = 0; i < 2; i++) {
            fprintf(logFile, " %f", pix_deg[i]);
        }
        fprintf(logFile, " (pix/deg)\n");
        
        fprintf(logFile, "estimatedPosition = ");
        for (int i = 0; i < 3; i++) {
            fprintf(logFile, " %f", estimatedPosition[i]);
        }
        fprintf(logFile, " (km)\n");
        
        fprintf(logFile, "Moon Ephem = ");
        for (int i = 0; i < 3; i++) {
            fprintf(logFile, " %f", moonEphem[i]);
        }
        fprintf(logFile, " (km)\n");
    }
    
    void update(PointEarthMoon point, int currentImageSize, double* pix_deg, double* estimatedPosition, double* moonEphem, int cameraWidth, int cameraHeight, time_t satTime) {
        this->timeStamp = satTime;
        this->point = point;
        this->currentImageSize = currentImageSize;
        memcpy(this->pix_deg, pix_deg, 2 * sizeof(double));
        memcpy(this->estimatedPosition, estimatedPosition, 3 * sizeof(double));
        memcpy(this->moonEphem, moonEphem, 3 * sizeof(double));
        this->cameraWidth = cameraWidth;
        this->cameraHeight = cameraHeight;
    }
    
    void resizeImageArray(int newSize) {
        if (currentImageSize > newSize) {
            return;
        }
        
        delete[] image;
        image = new char[newSize];
        imageBufferSize = newSize;
        std::cout << "\n\n\n Resizing Image Message b/c it is bigger than expected \n\n\n";
    }
    
    char* getImagePointer() {
        return image;
    }
    
    // Specific Data Members
    PointEarthMoon point;
    int cameraWidth;
    int cameraHeight;
    double pix_deg[2]; // Pixel per degree
    double estimatedPosition[3];
    double moonEphem[3];
    
    // Do not send these variable below
    int currentImageSize;
    int imageBufferSize;
    
private:
    char* image;
};

#endif
