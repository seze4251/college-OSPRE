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
    }
    
    ~ImageMessage() {
        delete image;
    }
    
    MessageID getMessageID() { return I_ImageMessage; }
    

    void update(char* image, PointEarthMoon point) {
        timeStamp = time(0);
        this->point = point;
        this->image = image;
    }
    
    // Specific Data Members
    PointEarthMoon point;
    char* image;
};

#endif
