//
//  CameraController.cpp
//  CameraController
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cmath>
#include <unistd.h>

#include "CameraController.h"
#include "Service.h"

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// OpenCV namespace for laziness
using namespace cv;

#define DOWN_SAMPLE_SIZE 2
#define CROP_SIZE 400

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
    currentImageSize = -1;
    cameraHeight = -1;
    cameraWidth = -1;
    pix_deg[0] = -1;
    pix_deg[1] = -1;
    rectCoords[0] = -1.;
    rectCoords[1] = -1.;
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
    fprintf(logFile, "File Input: Read OSPRE Config File\n");
    
    // Read in list of Image Files
    if (liveMode == false) {
        imageReader.loadImageNames(testDIR);
    }
    
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
    
    // Read Camera Controller Config File
    read_ConfigFile("Text_Data/Camera_Controller_Config.txt");
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
void CameraController::read_ConfigFile(std::string config_file) {
    std::ifstream file(config_file);
    
    if (!file) {
        fprintf(logFile, "Error: read Config File File %s could not be opened for reading\n", config_file.c_str());
        throw "File Could Not Be Opened for Reading";
    }
    
    std::string line;
    std::getline(file, line);
    file >> pix_deg[0];
    file >> pix_deg[1];
}

void CameraController::readImage(std::string imgFilename) {
    // Get image
    fprintf(logFile, "Read Image: Starting Image Read\n");
    
    if (imgFilename.empty() == true) {
        fprintf(logFile, "Read Image: Input is empty string, all images have been read and processed in current test directory\n");
        throw "CameraController::readImage(), image name empty, no more images to read";
    } else {
        fprintf(logFile, "Read Image: Input String: %s\n", imgFilename.c_str());
    }
    
    cv::Mat image, imGray, imGrayDS;
    image = imread(imgFilename);
    
    if(!image.data){
        fprintf(logFile, "Read Image ERROR: Could not open or find the image\n");
        throw InvalidFileName("ReadImage() no Image Name in directory");
    } else {
        fprintf(logFile, "Read Image: Image Name Valid\n");
    }
    
    /**
     Downsample and crop image
     TODO:
     - Change CROP_SIZE to a function with position input
     */
    cvtColor(image, imGray, CV_BGR2GRAY); // Convert to grayscale
    
    if(!imGray.data){
        fprintf(logFile, "Read Image ERROR: could not convert image to grayscale\n");
        throw "CameraController::readImage(), error converting image to grayscale";
    } else {
        fprintf(logFile, "Read Image: Image grayscale conversion success\n");
    }
    
    GaussianBlur(imGray, imGray, Size(9,9), 2, 2); // Smooth image to improve OpenCV circle finding
    
    // pyrDown(imGray, imGray, Size(imGray.cols/DOWN_SAMPLE_SIZE, imGray.rows/DOWN_SAMPLE_SIZE)); // Downsample iamge

    cv::threshold(imGray, imGray, 64, 255, THRESH_BINARY);
    
    
    std::vector<Vec3f> circles;
    HoughCircles(imGray, circles, CV_HOUGH_GRADIENT, 2, image.rows/2, 200, 50); // Find circle
    
    
    if(circles.size() == 0 || !circles.size()){
        fprintf(logFile, "Read Image: Unable to find circles in downsampled image, reverting to full size image\n");
    
        
        currentImageSize = image.cols * image.rows * 3;
        cameraHeight = image.rows;
        cameraWidth = image.cols;
        std::cout << "Printing Image CUrrent Size in CC:  " << currentImageSize << std::endl;
        imageMessage->resizeImageArray(currentImageSize);
        
        
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
                imIn[counter + image.cols * image.rows] = green;
                imIn[counter + 2 * image.cols * image.rows] = blue;
                counter++;
            }
        }
        
        fprintf(logFile, "Read Image: Finished Image Read\n");
        // throw "CameraController:readImage(), no circles found for cropping";
        return;
    } else {
        fprintf(logFile, "Read Image: Successfully cropped image\n");
    }
    
    // Create crop area around found object
    int rectX = cvRound(circles[0][0]) - CROP_SIZE/2;
    int rectY = cvRound(circles[0][1]) - CROP_SIZE/2;
    //int rectCoords[2] = {rectX, rectY};
    imageMessage->cropCoords[0] = rectX;
    imageMessage->cropCoords[1] = rectY;
    cv::Rect myROI(rectX, //x
                   rectY, //y
                   CROP_SIZE, CROP_SIZE);
    
    image = image(myROI);
    
    std::cout << "HERE IN CC WHICH IS BAD!  " << std::endl;
    imageMessage->resizeImageArray(image.cols * image.rows * 3);
    currentImageSize = image.cols * image.rows * 3;
    cameraHeight = image.rows;
    cameraWidth = image.cols;
    
    
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
            imIn[counter + image.cols * image.rows] = green;
            imIn[counter + 2 * image.cols * image.rows] = blue;
            counter++;
        }
    }
    
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
    
    if (liveMode == false) {
        fprintf(logFile, "Received Message: SIM MODE, CaptureImageRequest from GNC, \n");
        msg->print(logFile);
        
        // TODO: Update readImage call to not be hardcoded
        try {
            if (data.sleep == false) {
                std::cout << "Start Read Image" << std::endl;
                readImage(imageReader.getNextImageName());
                std::cout << "Start End Image" << std::endl;
            } else {
                localError = PE_SleepMode;
                return;
            }
            
        } catch (InvalidFileName &e) {
            fprintf(logFile, "Error: readImage() InvalidFileName Exception Caught: %s\n", e.what());
            localError = PE_CC_InvalidFileName;
            return;
            
        } catch (InvalidImageDimensions &e) {
            fprintf(logFile, "Error: readImage() InvalidImageDimensions Exception Caught: %s\n", e.what());
            localError = PE_CC_InvalidImageDimensions;
            return;
            
        } catch(std::exception &exception) {
            fprintf(logFile, "Error: readImage() Exception Caught: %s\n", exception.what());
            localError = PE_NotHealthy;
            throw;
            
        } catch (const char * e) {
            fprintf(logFile, "ERROR: ReadImage: %s\n, Returning to select loop to allow Camera Controller to keep sending data to IP\n", e);
            localError = PE_NoMoreImages;
            return;
        } catch (...) {
            fprintf(logFile, "Error: readImage() Unknown Type of Exception Caught\n");
            throw;
        }
        
        imageMessage->update(msg->point, currentImageSize, pix_deg, msg->estimatedPosition, data.ephem, cameraWidth, cameraHeight, msg->timeStamp);
        
        // Send Image Message to Image Processor
        if ((imageProc != nullptr) && (imageProc->isConnected() == true)) {
            imageProc->sendMessage(imageMessage);
            fprintf(logFile, "Sent Message: ImageMessage to ImageProcessor\n");
        }
        
        
    } else {
        fprintf(logFile, "Received Message: Live MODE, CaptureImageRequest from GNC, \n");
        msg->print(logFile);
        // FOR FUTURE IMPLEMENTATION:
        // TODO HERE:
        // Test to see if Camera Controller can take image and if not throw an exception:
        // CameraController::canCaptureImage(CaptureImageRequest* msg)
        // Take an Image
        // void CameraController::captureImage()
        throw "ImageProcessor::handleCaptureImageRequest() Live Mode not implemented";
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

