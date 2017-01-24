//
//  ImageMessage.h
//  ImageMessage
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef IMAGEMESSAGE_H
#define IMAGEMESSAGE_H

#include "Message.h"

class ImageMessage : public Message {
public:
    ImageMessage() : Message(getMessageID(), time(0)), point(PEM_NA), image(nullptr) {}
    MessageID getMessageID() { return I_ImageMessage; }
    
    //Specific Data Members
    PointEarthMoon point;
    char* image;
};

#endif
