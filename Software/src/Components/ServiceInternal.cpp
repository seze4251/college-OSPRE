//
//  WatchDogClientHandler.cpp
//  WatchDogClientHandler
//
//  Created by Seth on 11/27/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <iostream>
#include <unistd.h>

#include "ServiceInternal.h"

void ServiceInternal::handleRead() {
    int length = readbuf.remaining();
    
    if (length == 0) {
        std::cout << "No Room to read into buffer" << std::endl;
        // TODO:: Throw Exception
        // Process Messages!!1
        // Errorcase: Buffer to small to handle size of 1 message
        return;
    }
    
    char* buf = readbuf.getBuffer();
    
    int amountRead = ::read(fd, buf, length);
    readbuf.positionRead(amountRead);
    // Handle All Messages
    
    Message* msg = nullptr;
    
    while (true) {
        msg = parse.parseMessage();
        
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
                handleProccessHealthAndStatusRequest((ProccessHealthAndStatusRequest*) msg);
                break;
                
            case I_ProccessHealthAndStatusResponse:
                handleProccessHealthAndStatusResponse((ProccessHealthAndStatusResponse*) msg);
                break;
                
            case I_SolutionMessage:
                handleSolutionMessage((SolutionMessage*) msg);
                break;
                
            default:
                std::cerr << "ServiceInternal::handleRead(): Unknown Message Type Recived: " << msg->iden << std::endl;
                std::cerr << "Fatal Error: Exiting" << std::endl;
                exit(-1);
        }
    }
    
    
    // determine if you have a complete message
    // if yes, pass it to the parser to extract that message
    // keep extracting messages until you've extracted all of them.
    // protected methods of internal service
    
    // ^^ Belongs in Internal Service
    // All Below belongs in internal Service
    // Belongs in WatchDogService
    // for each message do what you are supposed to do with that message.
    // Virtual Method of InternalService
    
    // Do I have data to write!
    // Tell Selector that I am interested in writing
    
}

void ServiceInternal::handleWrite() {
    int length = writebuf.used();
    
    if (length == 0) {
        std::cout << "Nothing Left to Write to Socket" << std::endl;
        getSelector().noInterestInWrite(fd);
        return;
    }
    
    writebuf.flip();
    char* buf = writebuf.getBuffer();
    
    int amountWritten = write(fd, buf, length);
    
    if (amountWritten == length) {
        writebuf.clear();
        getSelector().noInterestInWrite(fd);
    } else {
        // Compact Buffer and keep the interest in writing with selector
        writebuf.positionWrite(amountWritten);
        writebuf.compact();
        writebuf.flip();
    }
}

