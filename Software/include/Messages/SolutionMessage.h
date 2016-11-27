//
//  SolutionMessage.h
//  SolutionMessage
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef SOLUTIONMESSAGE_H
#define SOLUTIONMESSAGE_H

#include "Message.h"

class SolutionMessage : public Message {
public:
    MessageID getMessageID() {return I_SolutionMessage;}
};  

#endif
