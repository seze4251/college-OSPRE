//
//  GNC.cpp
//  GNC
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>
#include <exception>
#include <stdio.h>

#include "main.h"
#include "Kalman_Filter_Iteration.h"
#include "Position_From_Angles_Slew.h"
#include "Position_From_Earth_Range.h"
#include "Position_From_Moon_Range.h"
#include "Quaternion_To_Attitude.h"
#include "Kalman_Filter_Iteration_terminate.h"
#include "Kalman_Filter_Iteration_initialize.h"
#include "GNC.h"
#include "Service.h"

GNC::GNC(std::string hostName, int localPort) : ServerInternal(hostName, localPort, P_GNC), pollTime(0) {
    setAppl(this);
    
    // Set pointers to services to NULL
    scComms = nullptr;
    cameraController = nullptr;
    
    // Initialize Pointing Destination
    point = PEM_NA;
    
    // Allocate Memory for Messages to Send
    processHealthMessage = new ProcessHealthAndStatusResponse();
    captureImageMessage = new CaptureImageRequest();
    solutionMessage = new SolutionMessage();
    pointRequest = new PointingRequest();
    
    // Initialize localError to healthy
    localError = PE_AllHealthy;
    
    // Application Specific Member Initializations
    readReferenceTrajectory();
    
    // Initialize All GNC specific app members
    
    /*
     // GNC Specific Members
     double x_hat[6];
     double phi[36];
     double P[36];
     double dv0[3];
     double dv1[6];
     double dv2[9];
     double X_est[6];
     double covariance[36];
     double trajectoryDev[6];
     
     // From Config File
     double range_EarthRangeCutoff;
     double range_AnglesCutoff;
     
     // Spacecraft Position
     double r_E_SC[3];
     double velSC[3];
     
     // From Estimated range from earth
     double range_estimate;
     */
    
    
    logFile = nullptr;
}

GNC::~GNC() {
    //Free Messages from Memory
    delete processHealthMessage;
    delete captureImageMessage;
    delete solutionMessage;
    delete pointRequest;
    
    // Close Log File
    if (logFile)
        fclose(logFile);
}

void GNC::open() {
    // Create File Name
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    
    rawtime = time(0);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80, "./log/GNCLog_%d-%m-%Y.log",timeinfo);
    
    // Open Log File
    logFile = fopen(buffer, "a+");
    
    // Log Application Starting
    fprintf(logFile, "GNC Application Started, Time = %ld\n", time(0));
    
    // Set Timeout to 1 minute
    setTimeoutTime(10, 0);
    
    //Acceptor
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
    }
    
    // Connect to Camera Controller
    if(connectToAppl(hostName, 10000, &cameraController) == true) {
        fprintf(logFile, "Connection: Connected to Camera Controller\n");
    } else {
        fprintf(logFile, "Error: Unable to Connect to CameraController\n");
    }
}

/*
 1. Need to check that all connections are still open
 2. Need to Send Timed Pointing Requests to the Spacecraft
 3. Need to Send Timed Capture Image Requests to the Camera
 */
void GNC::handleTimeout() {
    // Check all connections are still open
    //Acceptor
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
        }
    }
    
    // Connect to Camera Controller
    
    if (cameraController == nullptr || cameraController->isConnected() == false) {
        if(connectToAppl(hostName, 10000, &cameraController) == true) {
            fprintf(logFile, "Connection: Connected to CameraController\n");
        } else {
            fprintf(logFile, "Error: Unable to Connect to CameraController\n");
        }
    }
    
    
    // Send Timed Capture Image Requests to Camera
    time_t currentTime = time(NULL);
    
    // Send Poll
    if (currentTime > pollTime) {
        if (point == PEM_NA) {
            point = PEM_Earth;
        } else if (point == PEM_Earth) {
            point = PEM_Moon;
        } else {
            point = PEM_Earth;
        }
        
        if ((scComms != nullptr) && (scComms -> isConnected())) {
            pointRequest->update(point);
            scComms -> sendMessage(pointRequest);
            fprintf(logFile, "Sent Message: Pointing Request to ScComms\n");
        }
        
        if ((cameraController != nullptr) && (cameraController->isConnected())) {
            captureImageMessage->update(point, r_E_SC);
            cameraController -> sendMessage(captureImageMessage);
            fprintf(logFile, "Sent Message: CaptureImageMessage to CameraController\n");
        }
        
        pollTime = currentTime + 20;
    }
    flushLog();
}

// *******************************
//
// Application Functionality:
//
// ********************************

// TODO: Waiting On Cameron to Complete
void GNC::computeSolution(DataMessage* dataMessage, ProcessedImageMessage* procMessage) {
    
    if (range_estimate < range_EarthRangeCutoff) {
        // Earth Ranging to find Position
        Position_From_Earth_Range(dataMessage->quat, procMessage->alpha, procMessage->beta, procMessage->theta, r_E_SC);
        
        Kalman_Filter_Iteration(x_hat, phi, P, dv0, dv1, dv2, X_est);
        
    } else if ( range_estimate < range_AnglesCutoff) {
        // Angles Method to find Position
        
        // Get Data Message1
        DataMessage dataMessage1;
        
        // Determine which Data Message has Moon Ephemeris
        double* moonEphem;
        
        // Determine which Data Message has Moon and Earth Quat
        double* moonQuat;
        double* earthQuat;
        
        double r_E_SC1[3]; // OUTPUT(ECI Position of First Picture)
        double r_E_SC2[3]; // OUTPUT(ECI Position of Second Picture)
        
        Position_From_Angles_Slew(moonEphem, earthQuat, moonQuat, procMessage->alpha, procMessage->beta, velSC, procMessage->theta, r_E_SC1, r_E_SC2);
        
        // Kalman Filter Position 1
        Kalman_Filter_Iteration(x_hat, phi, P, dv0, dv1, dv2, X_est);        // 'x_hat_0'. -> Trajectory Dev
        
        // Kalman Filter Position 2
        Kalman_Filter_Iteration(x_hat, phi, P, dv0, dv1, dv2, X_est);
        
        
    } else {
        // Moon Ranging to find Position
        Position_From_Moon_Range(dataMessage->ephem, dataMessage->quat, procMessage->alpha, procMessage->alpha, procMessage->theta, r_E_SC);
        
        Kalman_Filter_Iteration(x_hat, phi, P, dv0, dv1, dv2, X_est);
        
    }
    
    // Function Definitions
    
    //
    // Spacecraft-Moon position vector
    // Arguments    : const double r_E_SC[3]
    //                const double r_E_M[3]
    // Return Type  : double
    //
    double Earth_SC_Moon_Angle(const double r_E_SC[3], const double r_E_M[3])
    {
        double c;
        double r_SC_M[3];
        double r_SC_E[3];
        int k;
        double b_r_SC_M;
        
        //  Earth-Spacecraft-Moon Angle Function
        //   Calculates the Earth-Spacecraft-Moon angle from the spacecraft and moon
        //   positions.
        //
        //   Author:   Cameron Maywood
        //   Created:  3/8/2017
        //   Modified: 3/8/2017
        //             _____________________________________________________________
        //   Inputs:  |          r_E_SC         |  Spacecraft ECI position vector   |
        //            |          r_E_M          |  Moon ECI position vector         |
        //            |_________________________|___________________________________|
        //   Outputs: |   angle_Earth_SC_Moon   |   Earth-spacecraft-moon angle     |
        //            |_________________________|___________________________________|
        //  Spacecraft-Earth position vector
        //  Earth-spacecraft-Moon angle
        c = 0.0;
        for (k = 0; k < 3; k++) {
            b_r_SC_M = r_E_M[k] - r_E_SC[k];
            c += b_r_SC_M * -r_E_SC[k];
            r_SC_M[k] = b_r_SC_M;
            r_SC_E[k] = -r_E_SC[k];
        }
        
        return 57.295779513082323 * std::acos(c / (norm(r_SC_M) * norm(r_SC_E)));
    }
    
    //
    // File trailer for Earth_SC_Moon_Angle.cpp
    //
    // [EOF]
    //
    
    // Send Solution Message
    
    // TEMPORARY FIX:
    // Need Outputs from Cameron
    double positionError[3] {1000, 1000, 1000}; // km
    double velocityError[3] {0.250, 0.250, 0.250}; // km/s
    double earthScMoonAngle {180};
    
    // Update Solution Message
    solutionMessage->update(X_est, positionError, X_est+3, velocityError, earthScMoonAngle);
}

//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: State_Error.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 09-Mar-2017 13:26:09
//

// Include Files
#include "Kalman_Filter_Iteration.h"
#include "Position_From_Angles_Slew.h"
#include "Position_From_Earth_Range.h"
#include "Position_From_Moon_Range.h"
#include "Quaternion_To_Attitude.h"
#include "State_Error.h"

// Function Definitions

//
// Arguments    : const double X_ref[6]
//                const double X_est[6]
//                double posError[3]
//                double velError[3]
// Return Type  : void
//
void State_Error(const double X_ref[6], const double X_est[6], double posError[3],
                 double velError[3])
{
    int i;
    
    //  State Error Function
    //   Calculates the state error given the reference state and estimated
    //   state.
    //
    //   Author:   Cameron Maywood
    //   Created:  3/9/2017
    //   Modified: 3/9/2017
    //             _________________________________________________
    //   Inputs:  |     X_ref     |   Spacecraft reference state.   |
    //            |     X_est     |   Spacecraft estimated state.   |
    //            |_______________|_________________________________|
    //   Outputs: |    posError   |   Spacecraft position error.    |
    //            |    velError   |   Spacecraft velocity error.    |
    //            |_______________|_________________________________|
    for (i = 0; i < 3; i++) {
        posError[i] = X_ref[i] - X_est[i];
        velError[i] = X_ref[i + 3] - X_est[i + 3];
    }
}

//
// File trailer for State_Error.cpp
//
// [EOF]
//

struct reference_struct {
    
    vector<double> time;
    vector<double> X;
    vector<double> Y;
    vector<double> Z;
    vector<double> VX;
    vector<double> VY;
    vector<double> VZ;
};

int read_referencTraj(){
    
    reference_struct ref_traj;
    
    using namespace std;
    
    vector<double> time;
    vector<double> X;
    vector<double> Y;
    vector<double> Z;
    vector<double> VX;
    vector<double> VY;
    vector<double> VZ;
    
    double number;
    int column = 1;
    
    ifstream file("Skyfire_J2000_7_ECI_Epsecs_Short.txt");
    if(file.is_open()){
        while(file >> number){
            if(column == 1){
                ref_traj.time.push_back(number);
                ++column;
            }
            else if(column == 2){
                X.push_back(number);
                ++column;
            }
            else if(column == 3){
                Y.push_back(number);
                ++column;
            }
            else if(column == 4){
                Z.push_back(number);
                ++column;
            }
            else if(column == 5){
                VX.push_back(number);
                ++column;
            }
            else if(column == 6){
                VY.push_back(number);
                ++column;
            }
            else{
                VZ.push_back(number);
                column = 1;
            }
        }
    }
    
    for(int i = 0; i < X.size(); ++i){
        cout << time[i] << '\n';
    }
    
}



void GNC::readReferenceTrajectory() {
    std::cout << "Need To Implement: readReferenceTrajectory" << std::endl;
    //fprintf(logFile, "Need To Implement: readReferenceTrajectory\n");
}

// *******************************
//
// Message Handlers: Supported by GNC
//
// ********************************

/*
 Send Status to WatchDog
 */
void GNC::handleProcessHealthAndStatusRequest(ProcessHealthAndStatusRequest* msg, ServiceInternal* service) {
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
 1. Store the Data Message in circular buffer
 */
void GNC::handleDataMessage(DataMessage* msg, ServiceInternal* service) {
    fprintf(logFile, "Received Message: DataMessage from ScComms\n");
    
    // Put Data Into Circular Buffer
    circBuf.put(msg);
}

/*
 1. Get Spacecraft Data Message
 2. Call Compute
 3. Send a Solution Message
 */
void GNC::handleProcessedImageMessage(ProcessedImageMessage* msg, ServiceInternal* service) {
    fprintf(logFile, "Received Message: ProcessedImageMessage from ScComms\n");
    
    DataMessage* scData;
    try {
        scData = circBuf.get(msg->timeStamp);
    } catch (const char* exception) {
        fprintf(logFile, "Error: Data Message Not Received, Exception: %s\n", exception);
    }
    
    // Compute Solution and Update Solution Message
    try {
        computeSolution(scData, msg);
        
    } catch(std::exception &exception) {
        fprintf(logFile, "Error: HandleProcessedImageMessage() Exception Caught: %s\n", exception.what());
        localError = PE_invalidData;
        
    } catch (...) {
        fprintf(logFile, "Error: HandleProcessedImageMessage() Unknown Type of Exception Caught\n");
        throw;
    }
    
    // Send Solution Message
    if (scComms != nullptr) {
        scComms -> sendMessage(solutionMessage);
        fprintf(logFile, "Sent Message: SolutionMessage to ScComms\n");
    }
}


// *******************************
//
// Message Handlers: Not Supported by GNC
//
// ********************************
void GNC::handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: OSPRE Status, Closing Connection\n");
    service->closeConnection();
}
void GNC::handleProcessHealthAndStatusResponse(ProcessHealthAndStatusResponse* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: ResponseMessage, Closing Connection\n");
    service->closeConnection();
}
void GNC::handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: CaptureImageRequest, Closing Connection\n");
    service->closeConnection();
}
void GNC::handleImageAdjustment(ImageAdjustment* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: ImageAdjustmentMessage, Closing Connection\n");
    service->closeConnection();
}
void GNC::handleImageMessage(ImageMessage* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: ImageMessage, Closing Connection\n");
    service->closeConnection();
}
void GNC::handlePointingRequest(PointingRequest* msg, ServiceInternal* service) {
    fprintf(logFile, "Error: Invalid Message Recived: PointingRequest, Closing Connection\n");
    service->closeConnection();
}
void GNC::handleSolutionMessage(SolutionMessage* msg, ServiceInternal* service){
    fprintf(logFile, "Error: Invalid Message Recived: SolutionMessage, Closing Connection\n");
    service->closeConnection();
}

