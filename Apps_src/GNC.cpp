//
//  GNC.cpp
//  GNC
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <exception>
#include <stdio.h>

#include "Kalman_Filter_Iteration.h"
#include "Position_From_Angles_Slew.h"
#include "Position_From_Earth_Range.h"
#include "Position_From_Moon_Range.h"
#include "Quaternion_To_Attitude.h"
#include "Kalman_Filter_Iteration_terminate.h"
#include "Kalman_Filter_Iteration_initialize.h"
#include "Earth_SC_Moon_Angle.cpp"
#include "State_Error.cpp"
#include "norm.cpp"
#include "GNC.h"
#include "Service.h"

GNC::GNC(std::string hostName, int localPort) : ServerInternal(hostName, localPort, P_GNC), pollTime(0) {
    setAppl(this);
    
    // Set pointers to services to NULL
    scComms = nullptr;
    cameraController = nullptr;
    
    // Initialize Pointing Destination
    point = PEM_Earth;
    
    // Allocate Memory for Messages to Send
    processHealthMessage = new ProcessHealthAndStatusResponse();
    captureImageMessage = new CaptureImageRequest();
    solutionMessage = new SolutionMessage();
    pointRequest = new PointingRequest();
    
    // Initialize localError to healthy
    localError = PE_AllHealthy;
    
    logFile = nullptr;
    
    //**************************************
    // Initialize All GNC Specific App Members
    //**************************************
    
    // From Config File
    range_EarthRangeCutoff = -1;
    range_AnglesCutoff = -1;
    r_E_SC[0] = -1;
    r_E_SC[1] = -1;
    r_E_SC[2] = -1;
    velSC[0] = -1;
    velSC[1] = -1;
    velSC[2] = -1;
    
    for (int i = 0; i < 36; i++) {
        phi[i] = -1;
        P[i] = -1;
    }
    
    for (int i = 0; i < 9; i++) {
        R[i] = -1;
    }
    
    for (int i = 0; i < 6; i++) {
        X_hat[i] = -1;
        X_ref[i] = -1;
    }
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
    
    // Read in OSPRE CONFIG File
    readOSPREServerConfigFile();
    fprintf(logFile, "File Input: Read OSPRE Config File\n");
    
    // Open Results File
    std::string resultFileName = testDIR + "/OSPRE_Results/gncResults.txt";
    resultFile = fopen(resultFileName.c_str(), "a+");
    
    // Log Application Starting
    fprintf(resultFile, "\n\nNew GNC Run: Time = %ld\n", time(0));
    
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
        localError = PE_notConnected;
    }
    
    // Connect to Camera Controller
    if(connectToAppl(hostName, 10000, &cameraController) == true) {
        fprintf(logFile, "Connection: Connected to Camera Controller\n");
    } else {
        fprintf(logFile, "Error: Unable to Connect to CameraController\n");
        localError = PE_notConnected;
    }
    
    // Read Reference Trajectory File
    fprintf(logFile, "Reading Reference Trajectory: Attempting to Read Reference Trajectory\n");
    try {
        read_referencTraj("Text_Data/Skyfire_J2000_7_ECI_Epsecs.txt");
        fprintf(logFile, "Reference Trajectory First Row: time = %f X=%f Y=%f Z=%f V_X=%f V_Y=%f V_Z=%f \n", ref_traj.time.front(), ref_traj.X.front(), ref_traj.Y.front(), ref_traj.Z.front(), ref_traj.VX.front(), ref_traj.VY.front(), ref_traj.VZ.front());
        fprintf(logFile, "Reference Trajectory Last Row: time = %f X=%f Y=%f Z=%f V_X=%f V_Y=%f V_Z=%f \n", ref_traj.time.back(), ref_traj.X.back(), ref_traj.Y.back(), ref_traj.Z.back(), ref_traj.VX.back(), ref_traj.VY.back(), ref_traj.VZ.back());
    } catch (const char* e) {
        fprintf(logFile, "Error: ReadReferenceTrajectory Exception Caught: %s\n",e);
        throw;
        
    } catch(std::exception &exception) {
        fprintf(logFile, "Error: ReadReferenceTrajectory Exception Caught: %s\n", exception.what());
        throw;
        
    } catch (...) {
        fprintf(logFile, "Error: ReadReferenceTrajectory Unknown Type of Exception Caught\n");
        throw;
    }
    
    // Read Config File
    fprintf(logFile, "Reading Config File: Attempting to Configuration File\n");
    try {
        read_ConfigFile("Text_Data/GNC_Config.txt");
        fprintf(logFile, "Config File: Initial Pos: (%f,%f,%f), Earth Range Cutoff: %f, Angles Cutoff: %f\n", r_E_SC[0], r_E_SC[1], r_E_SC[2], range_EarthRangeCutoff, range_AnglesCutoff);
    } catch (const char* e) {
        fprintf(logFile, "Error: read_ConfigFile Exception Caught: %s\n",e);
        throw;
        
    } catch(std::exception &exception) {
        fprintf(logFile, "Error: read_ConfigFile Exception Caught: %s\n", exception.what());
        throw;
        
    } catch (...) {
        fprintf(logFile, "Error: read_ConfigFile Unknown Type of Exception Caught\n");
        throw;
    }
    
    flushLog();
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
            localError = PE_notConnected;
        }
    }
    
    // Connect to Camera Controller
    
    if (cameraController == nullptr || cameraController->isConnected() == false) {
        if(connectToAppl(hostName, 10000, &cameraController) == true) {
            fprintf(logFile, "Connection: Connected to CameraController\n");
        } else {
            fprintf(logFile, "Error: Unable to Connect to CameraController\n");
            localError = PE_notConnected;
        }
    }
    
    
    // Send Timed Capture Image Requests to Camera
    time_t currentTime = time(NULL);
    
    // Send Poll
    if (currentTime > pollTime) {
        if ((scComms != nullptr) && (scComms -> isConnected())) {
            pointRequest->update(point);
            scComms -> sendMessage(pointRequest);
            fprintf(logFile, "Sent Message: Pointing Request to ScComms\n");
        }
        
        if ((cameraController != nullptr) && (cameraController->isConnected())) {
            if (liveMode == true) {
                // LIVE MODE
                captureImageMessage->update(point, r_E_SC);
                cameraController -> sendMessage(captureImageMessage);
                fprintf(logFile, "Sent Message: CaptureImageMessage to CameraController, Live Version\n");
            } else {
                // SIM MODE
                DataMessage* tempMessage = circBuf.getNextSimMessage();
                if (tempMessage == nullptr) {
                    fprintf(logFile, "gnc::HandleTimeOut(): No More SIM Messages to Test\n");
                    pollTime = currentTime + 20;
                    flushLog();
                    return;
                }
                captureImageMessage->update(point, r_E_SC);
                captureImageMessage->timeStamp = tempMessage->satTime;
                cameraController -> sendMessage(captureImageMessage);
                fprintf(logFile, "Sent Message: CaptureImageMessage to CameraController, SIM Version (Altered Timestamp)\n");
            }
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

// ******************************************************
// TODO: Figure out deal with inputs to Camerons function
// ** CONST in Func means that you cannot update value in Kalman Filter funciton **
// We have a problem if we are not setting the values outside of kalman filter funciton and the value is CONST in your function
// Not Currently Setting:
// ------------------------------
// double x_hat[6] (reference trajectory deviance)
// double phi[36] (state transition matrix)  <----- CONST in Func
// double P[36] (covariance matrix)
// double R[9] (state error covariance)     <----- CONST in Func

// Currently Setting:
// ------------------------------
// double X_ref[6] (Reference Trajectory from input file)  <----- CONST in Func
// double Y[3] (Position from 1 of 3 methods)     <----- CONST in Func

// OUTPUT
// ------------------------------
// double X_est [6] (Position and Velocity Output)
// ******************************************************

void GNC::kalmanFilterWrapper(double* Y, double satTime, double* ephem) {
    if (liveMode == false) {
        // SIM MODE
        // Read in Data from file
        fprintf(logFile, "Getting Kalman Filter Data in Sim Mode");
        readInInitialKalmanFilterTraj();
        
    } else {
        // Live Mode
        fprintf(logFile, "Getting Kalman Filter Data in Sim Mode");
        get_Reference_Trajectory(X_ref, ref_traj, satTime);
        fprintf(logFile, "ComputeSolution: Reference Trajectory Results: [0] %f (km), [1] %f (km), [2] %f (km), [3] %f (km/s), [4] %f (km/s), [5] %f (km/s) \n", X_ref[0], X_ref[1], X_ref[2], X_ref[3], X_ref[4], X_ref[5]);
    }
    
    // Perform Kalman Filter Call
    std::cout << "Start: Kalman Filter Call" << std::endl;
    double X_est[6];
    Kalman_Filter_Iteration(X_hat, phi, P, Y, R, X_ref, satTime, X_est);
    std::cout << "End: Kalman Filter Call" << std::endl;
    
    // Log Output from Kalman Filter to log and results file
    fprintf(logFile, "ComputeSolution(): Kalman Filter Results: X =  %f (km), Y = %f (km), Z = %f (km), V_X =  %f (km/s), V_Y = %f (km/s), V_Z = %f (km/s),\n", X_est[0], X_est[1], X_est[2], X_est[3], X_est[4], X_est[5]);
    
    fprintf(resultFile, "ComputeSolution(): Kalman Filter Results: Time: %f X =  %f Y = %f, Z = %f, V_X =  %f V_Y = %f, V_Z = %f,\n", satTime, X_est[0], X_est[1], X_est[2], X_est[3], X_est[4], X_est[5]);
    
    // Find E/Sc/M Angle and Log it
    double earthScMoonAngle = Earth_SC_Moon_Angle(X_est, ephem);
    fprintf(logFile, "Compute Solution: Earth Spacecraft Moon Angle = %f (deg)\n", earthScMoonAngle);
    fprintf(resultFile, "Compute Solution: Earth Spacecraft Moon Angle = %f\n", earthScMoonAngle);
    
    // Find Error in State and Log Outputs
    double positionError[3];
    double velocityError[3];
    State_Error(X_ref, X_est, positionError, velocityError);
    fprintf(logFile, "Compute Solution: Position Error: X_e = %f (km), Y_e = %f (km), Z_e = %f (km)\n Velocity Error: VX_e = %f (km/s), VY_e = %f (km/s), VZ_e = %f (km/s) \n", positionError[0], positionError[1], positionError[2], velocityError[0], velocityError[1], velocityError[2]);
    fprintf(resultFile, "Compute Solution: Position Error: X_e = %f, Y_e = %f, Z_e = %f\n Velocity Error: VX_e = %f, VY_e = %f, VZ_e = %f\n", positionError[0], positionError[1], positionError[2], velocityError[0], velocityError[1], velocityError[2]);
    
    // Update Solution Message
    std::cout << "Updating Solution Message" << std::endl;
    solutionMessage->update(X_est, positionError, X_est+3, velocityError, earthScMoonAngle);
    
    // Update Stored Velocity and Stored Position in live mode only
    if (liveMode == true) {
        memcpy(velSC, X_est+3, 3* sizeof(double));
        memcpy(r_E_SC, X_est, 3*sizeof(double));
    }
    
    if (scComms != nullptr) {
        std::cout << "Sending Solution Message" << std::endl;
        scComms -> sendMessage(solutionMessage);
        fprintf(logFile, "Sent Message: SolutionMessage to ScComms\n");
    }
}


// ******************************************************
// TODO: Figure out deal with inputs to Camerons function
// ** CONST in Func means that you cannot update value in Kalman Filter funciton **
// We have a problem if we are not setting the values outside of kalman filter funciton and the value is CONST in your function
// Not Currently Setting:
// ------------------------------
// double x_hat[6] (reference trajectory deviance)
// double phi[36] (state transition matrix)  <----- CONST in Func
// double P[36] (covariance matrix)
// double R[9] (state error covariance)     <----- CONST in Func

// Currently Setting:
// ------------------------------
// double X_ref[6] (Reference Trajectory from input file)  <----- CONST in Func
// double Y[3] (Position from 1 of 3 methods)     <----- CONST in Func

// OUTPUT
// ------------------------------
// double X_est [6] (Position and Velocity Output)
// ******************************************************

void GNC::computeSolution(DataMessage* dataMessage, ProcessedImageMessage* procMessage) {
    if (norm(r_E_SC) < range_EarthRangeCutoff) {
        std::cout << "Start: Earth Ranging" << std::endl;
        fprintf(logFile, "ComputeSolution: Earth Ranging\n");
        
        // Set Pointing
        point = PEM_Earth;
        
        // Perform Earth Ranging
        fprintf(logFile, "ComputeSolution: Earth Ranging: INPUTS: quat: [%f, %f, %f, %f],\n alpha = %f, beta = %f, theta = %f \n", dataMessage->quat[0], dataMessage->quat[1], dataMessage->quat[2], dataMessage->quat[3], procMessage->alpha, procMessage->beta, procMessage->theta);
        double earthRangePosition[3];
        Position_From_Earth_Range(dataMessage->quat, procMessage->alpha, procMessage->beta, procMessage->theta, earthRangePosition);
        
        // Log Position Earth Range Output
        fprintf(logFile, "ComputeSolution: Calculated Earth Range: Kalman Filter Call Inputs: Time: %ld r_earth[0] = %f (km), r_earth[1] = %f (km), r_earth[2] = %f (km)\n", dataMessage->satTime, earthRangePosition[0], earthRangePosition[1], earthRangePosition[2]);
        
        // Call Kalman Filter Iteration Wrapper Function With Proper Inputs
        std::cout << "Start: Kalman Filter From Earth Range" << std::endl;
        kalmanFilterWrapper(earthRangePosition, (double) dataMessage->satTime, dataMessage->ephem);
        std::cout << "END: Kalman Filter From Earth Range" << std::endl;
        
    } else if ( norm(r_E_SC) < range_AnglesCutoff) {
        // Angles Method to find Position
        // Change Pointing
        if (procMessage->point == PEM_Earth) {
            
            std::cout << "Start: Angles Method First Picture" << std::endl;
            fprintf(logFile, "ComputeSolution: Angles Method, First Image, Saving Data and Leaving Angles Method\n");
            point = PEM_Moon;
            memcpy((void*) &dataMessage_FirstImage, (void*) dataMessage, sizeof(DataMessage));
            memcpy((void*) &procMessage_FirstImage, (void*) procMessage, sizeof(ProcessedImageMessage));
            return;
        }
        
        fprintf(logFile, "ComputeSolution: Angles Method, Second Image, Computing Solution\n");
        
        // Point back at earth
        point = PEM_Earth;
        
        // ASSUMPTION: dataMessage_FirstImage / procMessage_FirstImage == First Image == Point at Earth
        // ASSUMPTION: dataMessage / procMessage == Second Image == Pointing at Moon
        
        double pictureOnePosition[3];
        double pictureTwoPosition[3];
        std::cout << "Start: Position From ANGLES" << std::endl;
        Position_From_Angles_Slew(dataMessage->ephem, dataMessage_FirstImage.quat, dataMessage->quat, procMessage->alpha, procMessage->beta, procMessage_FirstImage.alpha, procMessage_FirstImage.beta, velSC, (double) (procMessage->timeStamp - procMessage_FirstImage.timeStamp), pictureOnePosition, pictureTwoPosition);
        std::cout << "END: Position From ANGLES" << std::endl;
        
        // First Kalman Filter Call
        std::cout << "Start: Angles First Kalman Filter Call" << std::endl;
        kalmanFilterWrapper(pictureOnePosition, (double) procMessage_FirstImage.timeStamp, dataMessage_FirstImage.ephem);
        std::cout << "END: Angles First Kalman Filter Call" << std::endl;
        
        // Second Kalman Filter Call
        std::cout << "Start: Angles Second Kalman Filter Call" << std::endl;
        kalmanFilterWrapper(pictureTwoPosition, (double) procMessage->timeStamp, dataMessage->ephem);
        std::cout << "End: Angles Second Kalman Filter Call" << std::endl;
        
    } else {
        // Moon Ranging to find Position
        std::cout << "Start: Moon Ranging" << std::endl;
        fprintf(logFile, "ComputeSolution: Moon Ranging\n");
        
        // Set Pointing
        point = PEM_Moon;
        
        // Log Inputs to Moon Range
        fprintf(logFile, "ComputeSolution: Moon Ranging: INPUTS: quat: [%f, %f, %f, %f],\n alpha = %f, beta = %f, theta = %f \n", dataMessage->quat[0], dataMessage->quat[1], dataMessage->quat[2], dataMessage->quat[3], procMessage->alpha, procMessage->beta, procMessage->theta);
        
        // Get Moon Range
        std::cout << "Start: MOON RANGING: Position From Moon Range" << std::endl;
        double moonRangePosition[3];
        Position_From_Moon_Range(dataMessage->ephem, dataMessage->quat, procMessage->alpha, procMessage->alpha, procMessage->theta, moonRangePosition);
        std::cout << "End: MOON RANGING: Position From Moon Range" << std::endl;
        
        // Log Outputs for Moon Range
        fprintf(logFile, "ComputeSolution: Earth Range: Kalman Filter Call Inputs: Time: %ld R[0] = %f, R[1] = %f, R[2] = %f\n", dataMessage->satTime, moonRangePosition[0], moonRangePosition[1], moonRangePosition[2]);
        
        std::cout << "Start: Moon Ranging Kalman Filter Call" << std::endl;
        kalmanFilterWrapper(moonRangePosition, (double) dataMessage->satTime, dataMessage->ephem);
        std::cout << "End: Moon Ranging Kalman Filter Call" << std::endl;
        
    }
    
    std::cout << "Ending Compute Solution" << std::endl;
}

void GNC::read_ConfigFile(std::string config_file) {
    std::ifstream file(config_file);
    
    if (!file) {
        fprintf(logFile, "Error: read Config File File %s could not be opened for reading\n", config_file.c_str());
        throw "File Could Not Be Opened for Reading";
    }
    
    std::string line;
    std::getline(file, line);
    file >> r_E_SC[0];
    file >> r_E_SC[1];
    file >> r_E_SC[2];
    
    std::getline(file, line);
    std::getline(file, line);
    file >> range_EarthRangeCutoff;
    
    std::getline(file, line);
    std::getline(file, line);
    file >> range_AnglesCutoff;
}
// Read Reference Trajectory
void GNC::read_referencTraj(std::string ref_trajectory_file) {
    std::ifstream file(ref_trajectory_file);
    
    if (!file) {
        fprintf(logFile, "Error: ReadReference Trajectory: File %s could not be opened for reading\n", ref_trajectory_file.c_str());
        throw "File Could Not Be Opened for Reading";
    }
    
    double number;
    int column = 1;
    
    while(file){
        file >> number;
        if(column == 1){
            ref_traj.time.push_back(number);
            ++column;
        }
        else if(column == 2){
            ref_traj.X.push_back(number);
            ++column;
        }
        else if(column == 3){
            ref_traj.Y.push_back(number);
            ++column;
        }
        else if(column == 4){
            ref_traj.Z.push_back(number);
            ++column;
        }
        else if(column == 5){
            ref_traj.VX.push_back(number);
            ++column;
        }
        else if(column == 6){
            ref_traj.VY.push_back(number);
            ++column;
        }
        else{
            ref_traj.VZ.push_back(number);
            column = 1;
        }
    }
}

void GNC::readInInitialKalmanFilterTraj() {
    fprintf(logFile, "Reading in Kalman Filter Inital Trajectory\n");
    std::ifstream file(testDIR + "/Test_Data/KalmanFilter_InitialState.txt");
    
    if (!file) {
        fprintf(logFile, "Error: readInInitialKalmanFilterTraj: File %s could not be opened for reading\n", std::string(testDIR + "/Test_Data/KalmanFilter_InitialState.txt").c_str());
        throw "File Could Not Be Opened for Reading";
    }
    
    std::string line;
    char hold;
    
    // Read in X_hat
    std::getline(file, line);
    fprintf(logFile, "X_hat = [");
    for (int i = 0; i < 6; i++) {
        file >> X_hat[i];
        file >> hold;
        fprintf(logFile, "%f ", X_hat[i]);
    }
    fprintf(logFile, "]\n");
    
    std::getline(file, line);
    
    // Read in Phi
    fprintf(logFile, "phi = [");
    for (int i = 0; i < 36; i++) {
        file >> phi[i];
        file >> hold;
        fprintf(logFile, "%f ", phi[i]);
    }
    fprintf(logFile, "]\n");
    
    std::getline(file, line);
    
    // Read in P
    fprintf(logFile, "P = [");
    for (int i = 0; i < 36; i++) {
        file >> P[i];
        file >> hold;
        fprintf(logFile, "%f ", P[i]);
    }
    fprintf(logFile, "]\n");
    
    std::getline(file, line);
    
    // Read in R
    fprintf(logFile, "R = [");
    for (int i = 0; i < 9; i++) {
        file >> R[i];
        file >> hold;
        fprintf(logFile, "%f ", R[i]);
    }
    fprintf(logFile, "]\n");
    
    std::getline(file, line);
    
    // Read in X_ref
    fprintf(logFile, "X_ref = [");
    for (int i = 0; i < 6; i++) {
        file >> X_ref[i];
        file >> hold;
        fprintf(logFile, "%f ", X_ref[i]);
    }
    fprintf(logFile, "]\n");
}


//*******************************
//
// Message Handlers: Supported by GNC
//
//********************************
/*
 Send Status to WatchDog
 */
void GNC::handleProcessHealthAndStatusRequest(ProcessHealthAndStatusRequest* msg, ServiceInternal* service) {
    fprintf(logFile, "Received Message: ProcessHealthAndStatusRequest from WatchDog\n");
    msg->print(logFile);
    
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
    //msg->print(logFile);
    
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
    msg->print(logFile);
    
    std::cout << "STARTING: Handle Processed Image Message" << std::endl;
    DataMessage* scData;
    std::cout << "Attempting to Find Data Message" << std::endl;
    
    try {
        scData = circBuf.get(msg->timeStamp);
        fprintf(logFile, "HandleProcessedImageMessage: Corresponding Data Message Found\n");
    } catch (const char* exception) {
        fprintf(logFile, "Error: Data Message Not Received, Exception: %s\n", exception);
        return;
    }
    
    std::cout << "Attempting to Compute Solution" << std::endl;
    // Compute Solution and Update Solution Message
    try {
        fprintf(logFile, "HandleProcessedImageMessage: Calling Compute Solution\n");
        std::cout << "Starting Compute Solution" << std::endl;
        computeSolution(scData, msg);
        std::cout << "Ending Compute Solution" << std::endl;
        
    } catch (InvalidInputs &e) {
        fprintf(logFile, "Error: HandleProcessedImageMessage() InvalidInputs Exception Caught: %s\n", e.what());
        localError = PE_InvalidInputs;
        return;
        
    } catch (InvalidOutput &e) {
        fprintf(logFile, "Error: HandleProcessedImageMessage() InvalidOutput Exception Caught: %s\n", e.what());
        localError = PE_InvalidOutput;
        return;
        
    } catch(std::exception &exception) {
        fprintf(logFile, "Error: HandleProcessedImageMessage() Exception Caught: %s\n", exception.what());
        localError = PE_NotHealthy;
        throw;
        
    } catch (...) {
        fprintf(logFile, "Error: HandleProcessedImageMessage() Unknown Type of Exception Caught\n");
        throw;
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

