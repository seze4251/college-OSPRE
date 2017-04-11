//
//  ImageProcessor.cpp
//  ImageProcessor
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>
#include <unistd.h>
#include <exception>
#include <stdio.h>
#include <string>
#include <cmath>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


#include "analyzeImage_emxutil.h"
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "analyzeImage_terminate.h"
#include "analyzeImage_initialize.h"
#include "ImageProcessor.h"
#include "Service.h"
#include "analyzeImage_emxAPI.h"

#define MOON_RADIUS 1736.0
#define EARTH_RADIUS 6371.0

ImageProcessor::ImageProcessor(std::string hostName, int localPort) : ServerInternal(hostName, localPort, P_ImageProcessor), pollTime(0) {
    setAppl(this);
    gnc = nullptr;
    
    // Allocate Memory for Messages to Send
    processedImageMessage = new ProcessedImageMessage;
    processHealthMessage = new ProcessHealthAndStatusResponse();
    
    // Initialize localError to healthy
    localError = PE_AllHealthy;
    
    // Initialize Logfile
    logFile = nullptr;
    
    // Initialize Applicaiton Specific Members
    // Image Processing Specific Members
    sensitivity = -1;
    numCirc = -1;
    alpha = -1;
    beta = -1;
    theta = -1;
    radius = -1;
    pixel_error = -1;
}


ImageProcessor::~ImageProcessor() {
    //Free Messages from Memory
    delete processedImageMessage;
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
void ImageProcessor::open() {
    // Create File Name
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    
    rawtime = time(0);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80,"./log/ImageProcessorLog_%d-%m-%Y.log",timeinfo);
    
    // Open Log File
    logFile = fopen(buffer, "a+");
    
    // Log Application Starting
    fprintf(logFile, "Image Processor Application Started, Time = %ld\n", time(0));
    
    // Read in OSPRE CONFIG File
    readOSPREServerConfigFile();
    fprintf(logFile, "File Input: Read OSPRE Config File\n");
    
    // Open Results File
    std::string resultFileName = testDIR + "/OSPRE_Results/imageProcessorResults.txt";
    resultFile = fopen(resultFileName.c_str(), "a+");
    
    // Log Application Starting
    fprintf(resultFile, "\n\nNew Image Processor Run: Time = %ld\n", time(0));
    
    // Set Timeout to 1 minute
    setTimeoutTime(60, 0);
    
    //Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            fprintf(logFile, "Error: Unable to Open Acceptor, Exiting...\n");
            exit(-1);
        }
        
        fprintf(logFile, "Connection: Server Socket Opened\n");
    }
    
    //Connect to GNC
    if(connectToAppl(hostName, 9000, &gnc) == true) {
        fprintf(logFile, "Connection: Connected to GNC\n");
    } else {
        fprintf(logFile, "Error: Unable to Connect to GNC\n");
        localError = PE_notConnected;
    }
}

/*
 1. Need to check that all connections are still open
 */
void ImageProcessor::handleTimeout() {
    //Acceptor
    if (accept.isConnected() == false) {
        if(accept.open(hostName, localPort) == false) {
            fprintf(logFile, "Error: Unable to Open Acceptor, Exiting...\n");
            exit(-1);
        }
        fprintf(logFile, "Connection: Server Socket Opened\n");
    }
    
    //Connect to GNC
    if (gnc == nullptr || gnc->isConnected() == false) {
        if(connectToAppl(hostName, 9000, &gnc) == true) {
            fprintf(logFile, "Connection: Connected to GNC\n");
        } else {
            fprintf(logFile, "Error: Unable to Connect to GNC\n");
            localError = PE_notConnected;
        }
    }
    
    flushLog();
}

// *******************************
//
// Application Functionality:
//
// ********************************
void ImageProcessor::setImageParameters(PointEarthMoon point, double* pix_deg, double* estPos, double* moonEphem) {
    // estimated Position is a double[3] km, ECI frame
    // Need to Set Variables:
    // double sensitivity;
    // double pxDeg[2]; // Pixel Per Degree
    // double dv3[2]; //Pixel Radius Guess from estimated Position
    
    /*
     NEEDS:
     - position estimation units and reference frame
     - Moon and Earth properties (radius, phase) Phase might not be necessary if we're restricting to only a single trajectory: we can just calculate a
     function that gives phase based on estimated position
     */
    
    if (point == PEM_Earth) {
        // Evaluate on the assumption that we're pointing at the Earth
        //
        // Need to take estimated position, calculate expected angular diameter of celestial body, use image properties to turn this value
        // into an estimated pixel radius
        //
        // Use emperically determined correlation function to determine the necessary sensitivity based on phase of moon and position
        //
        
        double dist = sqrt(pow((moonEphem[0] - estPos[0]),2) + pow((moonEphem[1] - estPos[1]),2) + pow((moonEphem[2] - estPos[2]),2)); // km
        double angDiam = atan(MOON_RADIUS / dist) * 180 / M_PI * 2; // [deg]
        double moonPxDiam[2] = { angDiam*pix_deg[0], angDiam*pix_deg[1] }; // [px], diam of Moon in height and width
        
        // Get radius guess
        calcRadGuess(moonPxDiam, estPos, point, dv3);
        
        // Get analysis sensitivity
        sensitivity = calcSens(moonPxDiam, estPos, point); // This function needs to be emperically determined
        
    } else if (point == PEM_Moon) {
        // Evaluate on the assumption that we're pointing at the Moon
        
        double dist = sqrt(pow(estPos[0],2) + pow(estPos[1], 2) + pow(estPos[2], 2));
        double angDiam = atan(EARTH_RADIUS / dist) * 180 / M_PI * 2; // [deg]
        double earthPxDiam[2] = { angDiam*pix_deg[0], angDiam*pix_deg[1] }; // [px], diam of Earth in height and width
        
        calcRadGuess(earthPxDiam, estPos, point, dv3);
        
        // Get analysis sensitivity
        sensitivity = calcSens(earthPxDiam, estPos, point); // This function needs to be emperically determined
    }
}

/**
 HELPER FUNCTIONS
 */

/*
 calcRadGuess
 TODO:
 - Create emperical function describing estimated radius
 - */
void ImageProcessor::calcRadGuess(double* pxDiam, double* estPos, PointEarthMoon point, double* ans) {
    /*if (point == PEM_Earth) {
     // Plug in estimated position to Earth emperical function
     ans[0] = pxDiam[0] / 2 - 2;
     ans[1] = pxDiam[1] / 2 + 2;
     } else if (point == PEM_Moon) {
     // Plug in estimated position to Moon emperical function
     ans[0] = pxDiam[0] / 2 - 2;
     ans[1] = pxDiam[1] / 2 + 2;
     } */
    
    ans[0] = 157;
    ans[1] = 167;
    
}

double ImageProcessor::calcSens(double* moonPxDiam, double* estimatedPosition, PointEarthMoon point) {
    return (double) 0.97;
    
}


void ImageProcessor::processImage(ImageMessage* msg) {
    setImageParameters(msg->point, msg->pix_deg, msg->estimatedPosition, msg->moonEphem);
    
    
    fprintf(logFile, "Analyze Image: Starting Call to Analyze Image\n");
    fprintf(logFile, "Analyze Image Inputs:\n");
    
    // TEMP HARDCODE
    //**************
    dv3[0] = 58;
    dv3[1] = 63;
    //**************
    
    
    fprintf(logFile, "dv3 = %f  %f, sens = %f, \npix_deg %f  %f, camera Width %d  camera height %d\n", dv3[0], dv3[1], sensitivity, msg->pix_deg[0], msg->pix_deg[1], msg->cameraWidth, msg->cameraHeight);
    // NEW
    emxArray_uint8_T *I;
    emxInitArray_uint8_T(&I, 3);
    cv::Vec3b intensity;
    int sizeimage, counter;
    int rows = msg->cameraWidth;
    int cols = msg->cameraHeight;
    sizeimage = rows*cols;
    I->size[0] = rows;
    I->size[1] = cols;
    I->size[2] = 3;
    
    std::cout << "Starting Conversion to EMX array" << std::endl;
    // Convert image into emxArray
    emxEnsureCapacity((emxArray__common *)I, 0, (int)sizeof(unsigned char));
    try{
        counter = 0;
        for (int i=0; i < cols; i++){
            for (int j=0; j < rows; j++){
                intensity = image.at<cv::Vec3b>(j,i);
                uchar blue = intensity.val[0];
                uchar green = intensity.val[1];
                uchar red = intensity.val[2];
                *(I->data + counter) = red;
                *(I->data + counter + sizeimage) = green;
                *(I->data + counter + 2*sizeimage) = blue;
                counter++;
            }
        }
    } catch(...) {
        fprintf(logFile, "ImageProcessor::processImage() Conversion to EMX array failed");
        throw;
    }
    std::cout << "Finishedit Conversion to EMX array" << std::endl;
        fflush(logFile);
    
    std::cout << "Starting Analyze Image Call" << std::endl;
    
    // TEMP Till I find out why IP is coreing
    analyzeImage(&img_holder, dv3, sensitivity, msg->pix_deg, (double) msg->cameraWidth, (double) msg->cameraHeight, centerPt_data, centerPt_size, &radius, &numCirc, &alpha, &beta, &theta);
    
    std::cout << "Ended Analyze Image call" << std::endl;
    
    fprintf(logFile, "Analyze Image: Ended Call to Analyze Image\n");
    
    if (numCirc) {
        // To Log File
        fprintf(logFile, "Analyze Image: BODY HAS BEEN FOUND!!!!\n");
        fprintf(logFile, "Found %1.2f Object(s)\n", numCirc);
        fprintf(logFile, "Center (%f,%f)\n ", centerPt_data[0],centerPt_data[1]);
        fprintf(logFile, "Radius %f\n", radius);
        fprintf(logFile, "Alpha = %f, Beta = %f,  Theta = %f\n", alpha, beta, theta);
        
        // To Results File
        fprintf(resultFile, "Center (%f,%f), ", centerPt_data[0],centerPt_data[1]);
        fprintf(resultFile, "Radius %f, ", radius);
        fprintf(resultFile, "Alpha = %f, Beta = %f, Theta = %f\n", alpha, beta, theta);
        
    } else {
        fprintf(logFile, "ERROR ERROR:No Bodies found in Image and exception not thrown, Major Error, statement should never print\n");
    }
    
    
    // TEMP
    pixel_error = 0;
    // Update ProcessedImageMessage
    processedImageMessage->update(alpha, beta, theta, pixel_error, msg->point, msg->timeStamp);
}


// *******************************
//
// Message Handlers: Supported by Image Processor
//
// ********************************

/*
 Determine Process Status
 Send Status to WatchDog
 */
void ImageProcessor::handleProcessHealthAndStatusRequest(ProcessHealthAndStatusRequest* msg, ServiceInternal* service) {
    fprintf(logFile, "Received Message: ProcessHealthAndStatusRequest from WatchDog\n");
    msg->print(logFile);
    
    processHealthMessage->update(localError);
    
    // Send Status Message
    service->sendMessage(processHealthMessage);
    fprintf(logFile, "Sent Message: StatusAndHealthResponse to WatchDog\n");
    
    // Reset Error Enum
    localError = PE_AllHealthy;
}

/*
 1. Check Message Integrity
 2. Process Image
 3. Send Processed Image Message to GNC
 4. Send Image Adjustment to Camera Controller
 */
void ImageProcessor::handleImageMessage(ImageMessage* msg, ServiceInternal* service) {
    fprintf(logFile, "Received Message: ImageMessage from CameraController\n");
    msg->print(logFile);
    
    try {
       // fprintf(logFile, "made it start analyze image call\n");
        flushLog();
        processImage(msg);
        
        // temp
        //***************
       // processedImageMessage->update(1, 1, 5, 0, msg->point, msg->timeStamp);
        //***************
        // Send Processed Image Message to GNC
        if (gnc != nullptr) {
            gnc->sendMessage(processedImageMessage);
            fprintf(logFile, "Sent Message: ProcessedImageMessage to GNC\n");
        }
        
        
    } catch (NoBodyInImage &e) {
        fprintf(logFile, "Error: HandleImageMessage() NoBodyInImage Exception Caught: %s\n", e.what());
        localError = PE_IP_noBodyInImage;
        return;
        
    } catch (InvalidInputs &e) {
        fprintf(logFile, "Error: HandleImageMessage() InvalidInputs Exception Caught: %s\n", e.what());
        localError = PE_InvalidInputs;
        return;
        
    } catch (InvalidAlphaBetaTheta &e) {
        fprintf(logFile, "Error: HandleImageMessage() InvalidAlphaBetaTheta Exception Caught: %s\n", e.what());
        localError = PE_InvalidOutputs;
        return;
        
    } catch (InvalidPosition &e) {
        fprintf(logFile, "Error: HandleImageMessage() InvalidPosition Exception Caught: %s\n", e.what());
        localError = PE_IP_InvalidPosition;
        return;
        
    } catch(std::exception &exception) {
        fprintf(logFile, "Error: HandleImageMessage() Exception Caught: %s\n", exception.what());
        localError = PE_NotHealthy;
        throw;
        
    } catch (...) {
        fprintf(logFile, "Error: HandleImageMessage() Unknown Type of Exception Caught\n");
        throw;
    }
}

// *******************************
//
// Message Handlers: Not Supported on Image Processor
//
// ********************************
void ImageProcessor::handleProcessHealthAndStatusResponse(ProcessHealthAndStatusResponse* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: Response, Closing Connection\n");
    service->closeConnection();
}
void ImageProcessor::handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: CaptureImageRequest, Closing Connection\n");
    service->closeConnection();
}

void ImageProcessor::handleDataMessage(DataMessage* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: DataMessage, Closing Connection\n");
    service->closeConnection();
}
void ImageProcessor::handleImageAdjustment(ImageAdjustment* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: ImageAdjustment, Closing Connection\n");
    service->closeConnection();
}
void ImageProcessor::handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: OSPREStatus, Closing Connection\n");
    service->closeConnection();
}
void ImageProcessor::handlePointingRequest(PointingRequest* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: PointingRequest, Closing Connection\n");
    service->closeConnection();
}
void ImageProcessor::handleSolutionMessage(SolutionMessage* msg, ServiceInternal* service){
    fprintf(logFile, "Error: Invalid Message Recived: SolutionMessage, Closing Connection\n");
    service->closeConnection();
}
void ImageProcessor::handleProcessedImageMessage(ProcessedImageMessage* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: ProcessedImageMessage, Closing Connection\n");
    service->closeConnection();
}

