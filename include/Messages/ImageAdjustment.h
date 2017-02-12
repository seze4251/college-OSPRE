//
//  ImageAdjustment.h
//  ImageAdjustment
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

// To be determined if we need this

#ifndef IMAGEADJUSTMENT_H
#define IMAGEADJUSTMENT_H

#include "Message.h"

class ImageAdjustment : public Message {
public:
    ImageAdjustment() : Message(getMessageID(), time(0)) {}
    
    MessageID getMessageID() { return I_ImageAdjustment; }
    
    void print() {
        printMessageHeader();
    }
};

#endif
