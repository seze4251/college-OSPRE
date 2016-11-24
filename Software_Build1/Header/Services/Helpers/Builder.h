//
//  Builder.h
//  Builder
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


// Builder will get passed a generic Message type and determine which message it is and build a charecter sting to send the message.  I
#ifndef BUILDER_H
#define BUILDER_H

#include "Internal_Messages.h"
#include "MessageID.h"

class Builder {
public:
    
    //Constructor
    Builder(ByteBuffer &buf);
    
    // Destructor
    ~Builder();
    
    // Public Methods
    void buildCaptureImageRequest(DataRequest &msg);
    void buildDataRequest(DataRequest &msg);
    void buildEphemerisMessage(EphemerisMessage &msg);
    void buildImageAdjustment(ImageAdjustment &msg);
    void buildImageMessage(ImageMessage &msg);
    void buildOSPREStatus(OSPREStatus &msg);
    void buildPointingRequest(PointingRequest &msg);
    void buildProccessHealthAndStatusRequest(ProccessHealthAndStatusRequest &msg);
    void buildProccessHealthAndStatusResponse(ProccessHealthAndStatusResponse &msg);
    void buildSolutionMessage(SolutionMessage &msg);
    
private:
    //Members
    ByteBuffer &buf;
    
    //Methods
    void createHeader(int length, MessageID msgID);
};

#endif
