//
//  Builder.h
//  Builder
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#ifndef BUILDER_H
#define BUILDER_H

#include "Internal_Messages.h"
#include "MessageID.h"
#include "ByteBuffer.h"
#include "MessageSizes.h"

class Builder {
public:
    
    //Constructor
    Builder(ByteBuffer &bufParam);
    
    // Destructor
    ~Builder();
    
    // Public Methods
    void buildCaptureImageRequest(CaptureImageRequest &msg);
    void buildDataMessage(DataMessage &msg);
    void buildImageAdjustment(ImageAdjustment &msg);
    void buildImageMessage(ImageMessage &msg);
    void buildOSPREStatus(OSPREStatus &msg);
    void buildPointingRequest(PointingRequest &msg);
    void buildProcessHealthAndStatusRequest(ProcessHealthAndStatusRequest &msg);
    void buildProcessHealthAndStatusResponse(ProcessHealthAndStatusResponse &msg);
    void buildSolutionMessage(SolutionMessage &msg);
    void buildProcessedImageMessage(ProcessedImageMessage &msg);
    
private:
    //Members
    ByteBuffer& buf;
    
    //Methods
    void createHeader(int length, MessageID msgID, time_t timeStamp) ;
};

#endif
