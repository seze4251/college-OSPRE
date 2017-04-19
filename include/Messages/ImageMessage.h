//
//  ImageMessage.h
//  ImageMessage
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef IMAGEMESSAGE_H
#define IMAGEMESSAGE_H

#define IMAGE_SIZE 38937600

#include "Message.h"
#include "Server.h"

class ImageMessage : public Message {
public:
    ImageMessage() : Message(getMessageID(), time(0)), point(PEM_NA){
        image = new char[IMAGE_SIZE];
        imageBufferSize = IMAGE_SIZE;
        currentImageSize = 0;
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
    
    void update(PointEarthMoon point, int currentImageSize, double* pix_deg, double* estimatedPosition, double* moonEphem, int cameraWidth, int cameraHeight, time_t satTime, int* cropCoords) {
        this->timeStamp = satTime;
        this->point = point;
        this->currentImageSize = currentImageSize;
        memcpy(this->pix_deg, pix_deg, 2 * sizeof(double));
        memcpy(this->estimatedPosition, estimatedPosition, 3 * sizeof(double));
        memcpy(this->moonEphem, moonEphem, 3 * sizeof(double));
        memcpy(this->cropCoords, cropCoords, 2 * sizeof(int));
        this->cameraWidth = cameraWidth;
        this->cameraHeight = cameraHeight;
    }
    
    void resizeImageArray(int newSize) {
        if (imageBufferSize >= newSize) {
            return;
        }
        
        delete[] image;
        image = new char[newSize];
        imageBufferSize = newSize;
        fprintf(Server::getAppl()->getLogFileID(), "Resizing Image Message (imageBufferSize) from: %d, to %d (newSize) b/c it is bigger than expected\n", imageBufferSize, newSize);
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
    int cropCoords[2];
    
    // Do not send these variable below
    int currentImageSize;
    int imageBufferSize;
    
private:
    char* image;
};

#endif
