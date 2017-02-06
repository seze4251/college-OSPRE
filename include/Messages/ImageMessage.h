//
//  ImageMessage.h
//  ImageMessage
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef IMAGEMESSAGE_H
#define IMAGEMESSAGE_H

#define IMAGE_SIZE 6480000

#include "Message.h"

class ImageMessage : public Message {
public:
    ImageMessage() : Message(getMessageID(), time(0)), point(PEM_NA){
        image = new char[IMAGE_SIZE];
        imageBufferSize = IMAGE_SIZE;
    }
    
    ~ImageMessage() {
        delete image;
    }
    
    MessageID getMessageID() { return I_ImageMessage; }
    
    
    void update(PointEarthMoon point, int currentImageSize) {
        this->timeStamp = time(0);
        this->point = point;
        this->currentImageSize = currentImageSize;
    }
    
    void resizeImageArray(int newSize) {
        if (currentImageSize > newSize) {
            return;
        }
        
        delete image;
        image = new char[newSize];
        imageBufferSize = newSize;
        std::cout << "\n\n\n Resizing Image Message b/c it is bigger than expected \n\n\n";
    }
    
    
    // Specific Data Members
    PointEarthMoon point;
    char* image;
    
    // Do not send these variable below
    int currentImageSize;
    int imageBufferSize;
};

#endif
