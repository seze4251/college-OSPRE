//
//  CameraController.cpp
//  CameraController
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>
#include <stdio.h>

#include "CameraController.h"
#include "Service.h"

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


CameraController::CameraController(std::string hostName, int localPort, bool readImageFile) : ServerInternal(hostName, localPort, P_CameraController), pollTime(0), readImageFile(readImageFile) {
    setAppl(this);
    
    // Set pointers to services to NULL
    imageProc = nullptr;
    scComms = nullptr;
    
    // Allocate Memory for Messages to Send
    imageMessage = new ImageMessage();
    processHealthMessage = new ProcessHealthAndStatusResponse();
    
    // Initialize localError to healthy
    localError = PE_AllHealthy;
    logFile = nullptr;
}

CameraController::~CameraController() {
    //Free Messages from Memory
    delete imageMessage;
    delete processHealthMessage;
    
    // Close Log File
    if (logFile)
        fclose(logFile);
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************


void CameraController::open() {
    // Create File Name
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    
    rawtime = time(0);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80,"./log/CameraControllerLog_%d-%m-%Y.log",timeinfo);
    
    // Open Log File
    logFile = fopen(buffer, "a+");
    
    // Log Application Starting
    fprintf(logFile, "Camera Controller Application Started, Time = %ld\n", time(0));
    
    // Read in OSPRE CONFIG File
    readOSPREServerConfigFile();
    
    // Set Timeout to 1 minute
    setTimeoutTime(60, 0);
    
    //Open Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            fprintf(logFile, "Error: Unable to Open Acceptor, Exiting...\n");
            exit(-1);
        }
        fprintf(logFile, "Connection: Server Socket Opened\n");
    }
    
    //Connect to ScComms
    if(connectToAppl(hostName, 7000, &scComms) == true) {
        fprintf(logFile, "Connection: Connected to ScComms\n");
    } else {
        fprintf(logFile, "Error: Unable to Connect to ScComms\n");
        localError = PE_notConnected;
    }
    
    // Connect to ImageProcessing
    if(connectToAppl(hostName, 8000, &imageProc) == true) {
        fprintf(logFile, "Connection: Connected to Image Processing\n");
    } else {
        fprintf(logFile, "Error: Unable to Connect to ImageProcessor\n");
        localError = PE_notConnected;
    }
}

/*
 1. Need to check that all connections are still open
 2. Check to make sure that Camera is still connected
 */
void CameraController::handleTimeout() {
    //Open Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            fprintf(logFile, "Error: Unable to Open Acceptor, Exiting...\n");
            exit(-1);
        }
        fprintf(logFile, "Connection: Server Socket Opened\n");
    }
    
    //Connect to ScComms
    if (scComms == nullptr || scComms->isConnected() == false) {
        if(connectToAppl(hostName, 7000, &scComms) == true) {
            fprintf(logFile, "Connection: Connected to ScComms\n");
        } else {
            fprintf(logFile, "Error: Unable to Connect to ScComms\n");
            localError = PE_notConnected;
        }
    }
    
    // Connect to ImageProcessing
    if (imageProc == nullptr || imageProc->isConnected() == false) {
        if(connectToAppl(hostName, 8000, &imageProc) == true) {
            fprintf(logFile, "Connection: Connected to Image Processing\n");
        } else {
            fprintf(logFile, "Error: Unable to Connect to ImageProcessing\n");
            localError = PE_notConnected;
        }
    }
    flushLog();
    // Check to make sure that Camera is still available <- ping camera
}

// *******************************
//
// Application Functionality:
//
// ********************************
void CameraController::readImage(std::string imgFilename) {
    // Get image
    fprintf(logFile, "Read Image: Starting Image Read\n");
    cv::Mat image;
    image = cv::imread(imgFilename, cv::IMREAD_COLOR);
    
    
    if(!image.data){
        fprintf(logFile, "Read Image ERROR: Could not open or find the image\n");
        return;
    } else {
        fprintf(logFile, "Read Image: Image Name Valid\n");
    }
    
    // Allocate variables
    unsigned char* imIn = (unsigned char*) imageMessage->getImagePointer(); // <--- Change this to be compatible with msg
    cv::Vec3b intensity;
    
    int counter = 0;
    // Loop through image and convert
    for (int i = 0; i < image.cols; i++) {
        for (int j = 0; j < image.rows; j++) {
            intensity = image.at<cv::Vec3b>(j, i);
            uchar blue = intensity.val[0];
            uchar green = intensity.val[1];
            uchar red = intensity.val[2];
            imIn[counter] = red;
            imIn[counter + 809600] = green;
            imIn[counter + 2 * 809600] = blue;
            counter++;
        }
    }
    
    imageMessage -> currentImageSize = 2428800;
    fprintf(logFile, "Read Image: Finished Image Read\n");
}



//TODO: Waiting on Dylan for how to implement, might not need
void CameraController::adjustCameraSettings(ImageAdjustment* msg) {
    fprintf(logFile, "TODO: Need To Implement adjustCameraSettings\n");
}

// TODO: Waiting on Dylan for Implementation
void CameraController::captureImage() {
    fprintf(logFile, "TODO: Need to Implement CaptureImage\n");
}

//TODO: Needs Implementation
bool CameraController::canCaptureImage(CaptureImageRequest* msg) {
    fprintf(logFile, "TODO: Need to Implement canCaptureImage()\n");
    return false;
}


// *******************************
//
// Message Handlers: Supported By Camera Controller
//
// ********************************

/*
 Determine Process Status
 Send Status to WatchDog
 */
void CameraController::handleProcessHealthAndStatusRequest(ProcessHealthAndStatusRequest* msg, ServiceInternal* service) {
    fprintf(logFile, "Received Message: ProcessHealthAndStatusRequest from WatchDog\n");
    
    // Update ProcessHealthAndStatusResponse Message
    processHealthMessage->update(localError);
    
    // Send Status Message
    service->sendMessage(processHealthMessage);
    fprintf(logFile, "Sent Message: StatusAndHealthResponse to WatchDog\n");
    
    // Reset Error Enum
    localError = PE_AllHealthy;
}

/*
 CameraController::handleCaptureImageRequest() Logic
 Determine if Camera Controller can Take a picture
 If Can:
 Take A Picture / Load A Picture
 Send Image Message to Image Processor
 If Cannot:
 Send WatchDog Reason why Camera Controller Cannot Take Picture
 Optional: Send Message to GNC stating that data cannot be gathered at this time, I can do this but do I need to?
 */

void CameraController::handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service) {
    fprintf(logFile, "Received Message: CaptureImageRequest from GNC\n");
    msg->print(logFile);
    // FOR FUTURE IMPLEMENTATION:
    // TODO HERE:
    // Test to see if Camera Controller can take image and if not throw an exception:
    // CameraController::canCaptureImage(CaptureImageRequest* msg)
    // Take an Image
    // void CameraController::captureImage()
    // Send the Image the same as done below
    
    
    // TODO: Update readImage call to not be hardcoded
    try {
        if (data.sleep == false) {
            readImage("Images/samplePic.jpg");
        } else {
            localError = PE_SleepMode;
        }
        
    } catch (InvalidFileName &e) {
        fprintf(logFile, "Error: readImage() InvalidFileName Exception Caught: %s\n", e.what());
        localError = PE_CC_InvalidFileName;
        
    } catch (InvalidImageDimensions &e) {
        fprintf(logFile, "Error: readImage() InvalidImageDimensions Exception Caught: %s\n", e.what());
        localError = PE_CC_InvalidImageDimensions;
        
    } catch(std::exception &exception) {
        fprintf(logFile, "Error: readImage() Exception Caught: %s\n", exception.what());
        localError = PE_NotHealthy;
        throw;
        
    } catch (...) {
        fprintf(logFile, "Error: readImage() Unknown Type of Exception Caught\n");
        throw;
    }
    
    // TODO: Need to get these parameters from somewhere, maybe config file?
    // Update Image Message
    //********************************
    //TEMP TEMP Need to fix when readimage function is created
    int currentImageSize = IMAGE_SIZE;
    double pix_deg[2] {67, 67};
    int cameraWidth = 4160;
    int cameraHeight = 3120;
    imageMessage->update(msg->point, currentImageSize, pix_deg, msg->estimatedPosition, data.ephem, cameraWidth, cameraHeight, data.satTime);
    //TEMP TEMP Need to fix when readimage function is created
    //******************************
    
    // Send Image Message to Image Processor
    if (imageProc != nullptr) {
        imageProc->sendMessage(imageMessage);
        fprintf(logFile, "Sent Message: ImageMessage to ImageProcessor\n");
    }
}

void CameraController::handleDataMessage(DataMessage* msg, ServiceInternal* service) {
    fprintf(logFile, "Received Message: DataMessage from ScComms\n");
    //msg->print(logFile);
    data.update(msg->ephem, msg->quat, msg->angularVelocity, msg->satTime, msg->sunAngle, msg->sleep);
}

// TODO: Decide is this Needed?
void CameraController::handleImageAdjustment(ImageAdjustment* msg, ServiceInternal* service) {
    fprintf(logFile, "ERROR:Received Message: ImageAdjustmentMessage, NOT SUPPORTED\n");
    msg->print(logFile);
    throw "RECIVED IMAGE ADJUSTMENT MESSAGE, NOT SUPPORTED YET!!";
    adjustCameraSettings(msg);
}


// *******************************
//
// Message Handlers: Not Supported By Camera Controller
//
// ********************************
void CameraController::handleProcessHealthAndStatusResponse(ProcessHealthAndStatusResponse* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: ProcessHealthAndStatusResponse, Closing Connection\n");
    service->closeConnection();
}

void CameraController::handleImageMessage(ImageMessage* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: ImageMessage, Closing Connection\n");
    service->closeConnection();
}
void CameraController::handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: OSPREStatus, Closing Connection\n");
    service->closeConnection();
}
void CameraController::handlePointingRequest(PointingRequest* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: PointingRequest, Closing Connection\n");
    service->closeConnection();
}
void CameraController::handleSolutionMessage(SolutionMessage* msg, ServiceInternal* service){
    fprintf(logFile, "Error: Invalid Message Recived: SolutionMessage, Closing Connection\n");
    service->closeConnection();
}
void CameraController::handleProcessedImageMessage(ProcessedImageMessage* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: ProcessedImageMessage, Closing Connection\n");
    service->closeConnection();
}

