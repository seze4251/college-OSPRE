//
//  External_SolutionMessage.h
//  External_SolutionMessage
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef EXTERNAL_SOLUTIONMESSAGE_H
#define EXTERNAL_SOLUTIONMESSAGE_H

#include "Message.h"

class External_SolutionMessage : public Message {
public:
    MessageID getMessageID() { return E_SolutionMessage; }
};

#endif
