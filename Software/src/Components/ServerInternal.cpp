//
//  ServerInternal.cpp
//  ServerInternal
//
//  Created by Seth on 01/17/2017.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>

#include "ServerInternal.h"

// Constructors
ServerInternal::ServerInternal() : accept(getSelector()) {
    
}

//Destructor
ServerInternal::~ServerInternal() {
    
}

// Public Methods
void ServerInternal::handleMessage(Message* msg) {
    
    switch (msg->iden) {
        case I_CaptureImageRequest:
            handleCaptureImageRequest((CaptureImageRequest*) msg);
            break;
            
        case I_DataRequest:
            handleDataRequest((DataRequest*) msg);
            break;
            
        case I_EphemerisMessage:
            handleEphemerisMessage((EphemerisMessage*) msg);
            break;
            
        case I_ImageAdjustment:
            handleImageAdjustment((ImageAdjustment*) msg);
            break;
            
        case I_ImageMessage:
            handleImageMessage((ImageMessage*) msg);
            break;
            
        case I_OSPREStatus:
            handleOSPREStatus((OSPREStatus*) msg);
            break;
            
        case I_PointingRequest:
            handlePointingRequest((PointingRequest*) msg);
            break;
            
        case I_ProccessHealthAndStatusRequest:
            std::cout << "Entering handleProccessHealthAndStatusRequest" << std::endl;
            handleProccessHealthAndStatusRequest((ProccessHealthAndStatusRequest*) msg);
            break;
            
        case I_ProccessHealthAndStatusResponse:
            handleProccessHealthAndStatusResponse((ProccessHealthAndStatusResponse*) msg);
            break;
            
        case I_SolutionMessage:
            handleSolutionMessage((SolutionMessage*) msg);
            break;
            
        default:
            std::cerr << "ServerInternal::handleMessage(): Unknown Message Type Recived: " << msg->iden << std::endl;
            //TODO:: FIGURE OUT WAY TO THROW EXCEPTION OR CLOSE CONNECTION
            std::cerr << "Fatal Error: Closing Connection" << std::endl;
            //closeConnection();
            // NEED TO UNCOMMENT THIS OUT
    }
}


