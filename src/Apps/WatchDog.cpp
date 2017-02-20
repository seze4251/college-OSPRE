//
//  WatchDog.cpp
//  WatchDog
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>
#include <unistd.h>

#include "WatchDog.h"

WatchDog::WatchDog(std::string hostName, int localPort) : ServerInternal(hostName, localPort, P_WatchDog), pollProcess(0), pollStatus(0) {
    std::cout<< " WatchDog Constructor called" << std::endl;
    setAppl(this);
    scComms = nullptr;
    gnc = nullptr;
    imageProc = nullptr;
    cameraControl = nullptr;
    
    // Allocate Memory for Messages to Send
    processHealthRequestMessage = new ProcessHealthAndStatusRequest();
    ospreStatusMessage = new OSPREStatus();
    
    // Set Received to False
    healthyScComms = false;
    healthyScGnc = false;
    healthyImageProc = false;
    healthyCameraControl = false;
}

WatchDog::~WatchDog() {
    //Free Messages from Memory
    delete processHealthRequestMessage;
    delete ospreStatusMessage;
    
}

// TODO: Update error vector based on what processes aren't connected
void WatchDog::open() {
    // Set Timeout
    setTimeoutTime(1, 0);
    
    //Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            std::cerr << "WatchDog Server Socket Failed To Open, ScComms Exiting" << std::endl;
            exit(-1);
        }
        std::cout << "WatchDog Server Socket Opened" << std::endl;
    }
    
    // Connect to ScComms
    if(connectToAppl(hostName, 7000, &scComms) == true) {
        //   std::cout << "WatchDog: Connected to ScComms" << std::endl;
    } else {
        std::cout << "WatchDog: Failure to Connect to ScComms" << std::endl;
    }
    
    // Connect to GNC
    if(connectToAppl(hostName, 9000, &gnc) == true) {
        //   std::cout << "WatchDog: Connected to GNC" << std::endl;
    } else {
        std::cout << "WatchDog: Failure to Connect to GNC" << std::endl;
    }
    
    // Connect to Image Processor
    if(connectToAppl(hostName, 8000, &imageProc) == true) {
        //  std::cout << "WatchDog: Connected to Image Processor" << std::endl;
    } else {
        std::cout << "WatchDog: Failure to Connect to Image Processor" << std::endl;
    }
    
    // Connect to Camera Controller
    if(connectToAppl(hostName, 10000, &cameraControl) == true) {
        //   std::cout << "WatchDog: Connected to Camera Controller" << std::endl;
    } else {
        std::cout << "WatchDog: Failure to Connect to Camera Controller" << std::endl;
    }
}

// TODO: Need to Scatter Poll time and OSPRE Status
/*
 1. Need to send out a poll at timed intervals
 2. Need to check that all processes have responded to the poll
 3. Need to send OSPRE Status Message to ScComms at timed intervals
 4. Need to check that all connections are still open
 */
void WatchDog::handleTimeout() {
    // Attempt to connect to all connections
    this->open();
    
    // std::cout<< "WatchDog::handleTimeout() " << std::endl;
    time_t currentTime = time(NULL);
    
    if (currentTime > pollProcess) {
        // Send ScComms Health and Status Message
        processHealthRequestMessage->update();
        
        if ((scComms != nullptr) && (scComms->isConnected())) {
            scComms -> sendMessage(processHealthRequestMessage);
        }
        
        // Send GNC Health and Status Message
        if ((gnc != nullptr) && (gnc->isConnected())) {
            gnc -> sendMessage(processHealthRequestMessage);
        }
        
        // Send Image Processor Health and Status Message
        if ((imageProc != nullptr) && (imageProc->isConnected())) {
            imageProc -> sendMessage(processHealthRequestMessage);
            
        }
        
        // Send Camera Controller Health and Status Message
        if ((cameraControl != nullptr) && (cameraControl->isConnected())) {
            cameraControl -> sendMessage(processHealthRequestMessage);
        }
        
        // Update Poll Process Time
        pollProcess = currentTime + 30;
        pollStatus = currentTime + 15;
        
    } else if (currentTime > pollStatus ) {
        // Send OSPRE Status Message
        if ((scComms != nullptr) && (scComms->isConnected())) {
            
            if ((healthyScComms == true) && (healthyScGnc == true) && (healthyImageProc == true) &&(healthyCameraControl == true)) {
                ospreStatusMessage->totalHealth = PE_AllHealthy;
            } else {
                ospreStatusMessage->totalHealth = PE_NotHealthy;
            }
            
            std::cout << std::endl;
            ospreStatusMessage->print();
            std::cout << "\nSending OSPRE STATUS\n" << std::endl;
            
            scComms->sendMessage(ospreStatusMessage);
            
            // Set Received to False
            healthyScComms = false;
            healthyScGnc = false;
            healthyImageProc = false;
            healthyCameraControl = false;
            
            // Reset OSPRE Status
            std::cout << "\n\nPre Send OSPRE Status Message Error: " << ospreStatusMessage->error.size() << " PID Size: " << ospreStatusMessage->pID.size() << std::endl;
            ospreStatusMessage->clear();
            std::cout << "Post Send OSPRE Status Message Error: " << ospreStatusMessage->error.size() << " PID Size: " << ospreStatusMessage->pID.size() << std::endl << std::endl;
            
            // Update Poll OSPRE Status Message Time
            pollProcess = currentTime + 10;
            pollStatus = pollProcess + 1;
        }
    }
}

// *******************************
//
// Message Handlers: Supported By WatchDog
//
// ********************************

/*
 When a response message is recived, diagnose if there are any issues with the processess and store them for the creation of the OSPRE status message
 */
void WatchDog::handleProcessHealthAndStatusResponse(ProcessHealthAndStatusResponse* msg, ServiceInternal* service) {
    //Determine which client sent the message
    if (service == cameraControl) {
        std::cout<< "Recived Response Message from CC" << std::endl;
        if (msg->error == PE_AllHealthy) {
            healthyCameraControl = true;
            
        } else {
            ospreStatusMessage->numProblemProcesses++;
            ospreStatusMessage->update(msg->error, P_CameraController);
        }
        
    } else if(service == scComms) {
        std::cout<< "Recived Response Message from scComms" << std::endl;
        if (msg->error == PE_AllHealthy) {
            healthyScComms = true;
            
        } else {
            ospreStatusMessage->numProblemProcesses++;
            ospreStatusMessage->update(msg->error, P_ScComms);
        }
        
    } else if(service == gnc) {
        std::cout<< "Recived Response Message from gnc" << std::endl;
        std::cout << "Printing gnc Response Message" << std::endl;
        msg->print();
        if (msg->error == PE_AllHealthy) {
            healthyScGnc = true;
        } else {
            ospreStatusMessage->numProblemProcesses++;
            ospreStatusMessage->update(msg->error, P_GNC);
        }
        
    } else if(service == imageProc) {
        std::cout<< "Recived Response Message from IP" << std::endl;
        std::cout << "Printing Image Processor Response Message" << std::endl;
        msg->print();
        if (msg->error == PE_AllHealthy) {
            healthyImageProc = true;
        } else {
            ospreStatusMessage->numProblemProcesses++;
            ospreStatusMessage->update(msg->error, P_ImageProcessor);
        }
        
    } else {
        std::cerr << "WatchDogClientHandler::handleProcessHealthAndStatusResponse: Client Response Message Not Expected" << std::endl;
        std::cerr << "Closing Connection" << std::endl;
        service->closeConnection();
    }
}

void WatchDog::handleDataMessage(DataMessage* msg, ServiceInternal* service) {
    // std::cout << "WatchDog::handleDataMessage() Ignoring Data Message" << std::endl;
}

// *******************************
//
// Message Handlers: Not Supported By WatchDog
//
// ********************************
void WatchDog::handleProcessHealthAndStatusRequest(ProcessHealthAndStatusRequest* msg, ServiceInternal* service) {
    std::cout << "WatchDog::handleProcessHealthAndStatusRequest():  Not Supported for WatchDog" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
    
}
void WatchDog::handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service) {
    std::cerr << "WatchDog::handleCaptureImageRequest() Not Supported for WatchDog" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void WatchDog::handleImageAdjustment(ImageAdjustment* msg, ServiceInternal* service) {
    std::cerr << "WatchDog::handleImageAdjustment() Not Supported for WatchDog" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void WatchDog::handleImageMessage(ImageMessage* msg, ServiceInternal* service) {
    std::cerr << "WatchDog::handleImageMessage() Not Supported for WatchDog" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void WatchDog::handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service) {
    std::cerr << "WatchDog::handleOSPREStatus() Not Supported for WatchDog" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void WatchDog::handlePointingRequest(PointingRequest* msg, ServiceInternal* service) {
    std::cerr << "WatchDog::handlePointingRequest() Not Supported for WatchDog" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}
void WatchDog::handleSolutionMessage(SolutionMessage* msg, ServiceInternal* service){
    std::cerr << "WatchDog::handleSolutionMessage() Not Supported for WatchDog" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}

void WatchDog::handleProcessedImageMessage(ProcessedImageMessage* msg, ServiceInternal* service) {
    std::cerr << "WatchDog::handleProcessedImageMessage() Not Supported for WatchDog" << std::endl;
    std::cerr << "Closing Connection" << std::endl;
    service->closeConnection();
}






