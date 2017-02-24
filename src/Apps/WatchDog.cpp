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
    
    logFile = nullptr;
}

WatchDog::~WatchDog() {
    //Free Messages from Memory
    delete processHealthRequestMessage;
    delete ospreStatusMessage;
    
    // Close Log File
    if (logFile)
        fclose(logFile);
}

// TODO: Update error vector based on what processes aren't connected
void WatchDog::open() {
    // Create File Name
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    
    rawtime = time(0);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80,"./log/WatchDogLog_%d-%m-%Y.log",timeinfo);
    
    // Open Log File
    logFile = fopen(buffer, "a+");
    
    // Log Application Starting
    fprintf(logFile, "WatchDog Application Started, Time = %ld\n", time(0));
    
    // Set Timeout
    setTimeoutTime(1, 0);
    
    //Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            fprintf(logFile, "Error: Unable to Open Acceptor, Exiting...\n");
            exit(-1);
        }
        fprintf(logFile, "Connection: Server Socket Opened\n");
    }
    
    // Connect to ScComms
    if(connectToAppl(hostName, 7000, &scComms) == true) {
        fprintf(logFile, "Connection: Connected to ScComms\n");
    } else {
        fprintf(logFile, "Error: Unable to Connect to ScComms\n");
    }
    
    // Connect to GNC
    if(connectToAppl(hostName, 9000, &gnc) == true) {
        fprintf(logFile, "Connection: Connected to GNC\n");
    } else {
        fprintf(logFile, "Error: Unable to Connect to GNC\n");
    }
    
    // Connect to Image Processor
    if(connectToAppl(hostName, 8000, &imageProc) == true) {
        fprintf(logFile, "Connection: Connected to Image Processor\n");
    } else {
        fprintf(logFile, "Error: Unable to Connect to ImageProcessor\n");
    }
    
    // Connect to Camera Controller
    if(connectToAppl(hostName, 10000, &cameraControl) == true) {
        fprintf(logFile, "Connection: Connected to CameraController\n");
    } else {
        fprintf(logFile, "Error: Unable to Connect to CameraController\n");
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
    //Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            fprintf(logFile, "Error: Unable to Open Acceptor, Exiting...\n");
            exit(-1);
        }
        fprintf(logFile, "Connection: Server Socket Opened\n");
    }
    
    // Connect to ScComms
    if(connectToAppl(hostName, 7000, &scComms) == true) {
        fprintf(logFile, "Connection: Connected to ScComms\n");
    } else {
        fprintf(logFile, "Error: Unable to Connect to ScComms\n");
    }
    
    // Connect to GNC
    if(connectToAppl(hostName, 9000, &gnc) == true) {
        fprintf(logFile, "Connection: Connected to GNC\n");
    } else {
        fprintf(logFile, "Error: Unable to Connect to GNC\n");
    }
    
    // Connect to Image Processor
    if(connectToAppl(hostName, 8000, &imageProc) == true) {
        fprintf(logFile, "Connection: Connected to Image Processor\n");
    } else {
        fprintf(logFile, "Error: Unable to Connect to ImageProcessor\n");
    }
    
    // Connect to Camera Controller
    if(connectToAppl(hostName, 10000, &cameraControl) == true) {
        fprintf(logFile, "Connection: Connected to CameraController\n");
    } else {
        fprintf(logFile, "Error: Unable to Connect to CameraController\n");
    }
    
    time_t currentTime = time(NULL);
    
    if (currentTime > pollProcess) {
        // Send ScComms Health and Status Message
        processHealthRequestMessage->update();
        
        if ((scComms != nullptr) && (scComms->isConnected())) {
            scComms -> sendMessage(processHealthRequestMessage);
            fprintf(logFile, "Sent Message: ProcessHealthAndStatusRequest to ScComms\n");
        }
        
        // Send GNC Health and Status Message
        if ((gnc != nullptr) && (gnc->isConnected())) {
            gnc -> sendMessage(processHealthRequestMessage);
            fprintf(logFile, "Sent Message: ProcessHealthAndStatusRequest to CameraController\n");
        }
        
        // Send Image Processor Health and Status Message
        if ((imageProc != nullptr) && (imageProc->isConnected())) {
            imageProc -> sendMessage(processHealthRequestMessage);
            fprintf(logFile, "Sent Message: ProcessHealthAndStatusRequest to ImageProcessor\n");
        }
        
        // Send Camera Controller Health and Status Message
        if ((cameraControl != nullptr) && (cameraControl->isConnected())) {
            cameraControl -> sendMessage(processHealthRequestMessage);
            fprintf(logFile, "Sent Message: ProcessHealthAndStatusRequest to CameraController\n");
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

            scComms->sendMessage(ospreStatusMessage);
            fprintf(logFile, "Sent Message: OSPRE Status to ScComms\n");
            
            // Set Received to False
            healthyScComms = false;
            healthyScGnc = false;
            healthyImageProc = false;
            healthyCameraControl = false;
            
            // Reset OSPRE Status
            ospreStatusMessage->clear();
            
            // Update Poll OSPRE Status Message Time
            pollProcess = currentTime + 10;
            pollStatus = pollProcess + 1;
        }
    }
}

FILE* WatchDog::getLogFileID() {
    return logFile;
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
        fprintf(logFile, "Received Message: ProcessHealthAndStatusResponse from CameraController\n");
        if (msg->error == PE_AllHealthy) {
            healthyCameraControl = true;
            
        } else {
            fprintf(logFile, "Process Reported Unhealthy: CameraControler ErrorCode: %d\n", msg->error);
            ospreStatusMessage->numProblemProcesses++;
            ospreStatusMessage->update(msg->error, P_CameraController);
        }
        
    } else if(service == scComms) {
        fprintf(logFile, "Received Message: ProcessHealthAndStatusResponse from ScComms\n");
        
        if (msg->error == PE_AllHealthy) {
            healthyScComms = true;
            
        } else {
            fprintf(logFile, "Process Reported Unhealthy: ScComms ErrorCode: %d\n", msg->error);
            ospreStatusMessage->numProblemProcesses++;
            ospreStatusMessage->update(msg->error, P_ScComms);
        }
        
    } else if(service == gnc) {
        fprintf(logFile, "Received Message: ProcessHealthAndStatusResponse from GNC\n");
        if (msg->error == PE_AllHealthy) {
            healthyScGnc = true;
        } else {
            fprintf(logFile, "Process Reported Unhealthy: GNC ErrorCode: %d\n", msg->error);
            ospreStatusMessage->numProblemProcesses++;
            ospreStatusMessage->update(msg->error, P_GNC);
        }
        
    } else if(service == imageProc) {
        fprintf(logFile, "Received Message: ProcessHealthAndStatusResponse from ImageProcessor\n");
        if (msg->error == PE_AllHealthy) {
            healthyImageProc = true;
        } else {
            fprintf(logFile, "Process Reported Unhealthy: Image Processor ErrorCode: %d\n", msg->error);
            ospreStatusMessage->numProblemProcesses++;
            ospreStatusMessage->update(msg->error, P_ImageProcessor);
        }
        
    } else {
        fprintf(logFile, "Error: Response Message Recivied from Unexcpected Client, Closing Connection...\n");
        service->closeConnection();
    }
}

void WatchDog::handleDataMessage(DataMessage* msg, ServiceInternal* service) {}

// *******************************
//
// Message Handlers: Not Supported By WatchDog
//
// ********************************
void WatchDog::handleProcessHealthAndStatusRequest(ProcessHealthAndStatusRequest* msg, ServiceInternal* service) {
fprintf(logFile, "Error: Invalid Message Recived: Request, Closing Connection\n");
    service->closeConnection();
    
}
void WatchDog::handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service) {
fprintf(logFile, "Error: Invalid Message Recived: ImageRequest, Closing Connection\n");
    service->closeConnection();
}

void WatchDog::handleImageAdjustment(ImageAdjustment* msg, ServiceInternal* service) {
fprintf(logFile, "Error: Invalid Message Recived: ImageAdjustment, Closing Connection\n");
    service->closeConnection();
}
void WatchDog::handleImageMessage(ImageMessage* msg, ServiceInternal* service) {
fprintf(logFile, "Error: Invalid Message Recived: ImageMessage, Closing Connection\n");
    service->closeConnection();
}
void WatchDog::handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service) {
fprintf(logFile, "Error: Invalid Message Recived: OSPREStatus, Closing Connection\n");    service->closeConnection();
}
void WatchDog::handlePointingRequest(PointingRequest* msg, ServiceInternal* service) {
fprintf(logFile, "Error: Invalid Message Recived: PointingRequest, Closing Connection\n");
    service->closeConnection();
}
void WatchDog::handleSolutionMessage(SolutionMessage* msg, ServiceInternal* service){
fprintf(logFile, "Error: Invalid Message Recived: SolutionMessage, Closing Connection\n");
    service->closeConnection();
}

void WatchDog::handleProcessedImageMessage(ProcessedImageMessage* msg, ServiceInternal* service) {
fprintf(logFile, "Error: Invalid Message Recived: ProcessedImageMessage, Closing Connection\n");
    service->closeConnection();
}






