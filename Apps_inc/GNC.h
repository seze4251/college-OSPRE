//
//  GNC.h
//  GNC
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef GNC_H
#define GNC_H

#include <string>
#include <ctime>
#include <vector>
#include <stdio.h>

#include "ServerInternal.h"
#include "ProcessID.h"
#include "PointEarthMoon.h"
#include "CircularBuffer.h"
#include "OSPRE_Exceptions.h"
#include "Referance_Trajectory.h"

class GNC : public ServerInternal {
public:
    // Constructor
    GNC(std::string hostName, int localPort);
    
    // Destructor
    ~GNC();
    
    // Opens GNC Connections
    virtual void open();
    
    virtual void handleTimeout();
    
    // Message Handlers
    virtual void handleCaptureImageRequest(CaptureImageRequest* msg, ServiceInternal* service);
    virtual void handleDataMessage(DataMessage* msg, ServiceInternal* service);
    virtual void handleImageAdjustment(ImageAdjustment* msg, ServiceInternal* service);
    virtual void handleImageMessage(ImageMessage* msg, ServiceInternal* service);
    virtual void handleOSPREStatus(OSPREStatus* msg, ServiceInternal* service);
    virtual void handlePointingRequest(PointingRequest* msg, ServiceInternal* service);
    virtual void handleProcessHealthAndStatusRequest(ProcessHealthAndStatusRequest* msg, ServiceInternal* service);
    virtual void handleProcessHealthAndStatusResponse(ProcessHealthAndStatusResponse* msg, ServiceInternal* service);
    virtual void handleSolutionMessage(SolutionMessage* msg, ServiceInternal* service);
    virtual void handleProcessedImageMessage(ProcessedImageMessage* msg, ServiceInternal* service);
    
private:
    // Result File
    FILE* resultFile;
    
    // Internal Members  for System Architecture
    time_t pollTime;
    ServiceInternal* scComms;
    ServiceInternal* cameraController;
    
    // Pointer To Hold Messages that Are being sent
    ProcessHealthAndStatusResponse* processHealthMessage;
    PointingRequest* pointRequest;
    CaptureImageRequest* captureImageMessage;
    SolutionMessage* solutionMessage;
    
    // Process Error
    ProcessError localError;
    
    // Buffer to hold Data Messages
    CircularBuffer circBuf;
    
    // Where Spacecraft is currently pointing (Earth or Moon)
    PointEarthMoon point;
    
    // Reference trajectory
    Reference_Trajectory ref_traj;
    
    // From Config File
    double range_EarthRangeCutoff;
    double range_AnglesCutoff;
    
    // Saved Data TBD
    
    // Outputs
    double r_E_SC[3];
    double velSC[3];
    
    // From Angles Method
    DataMessage dataMessage_FirstImage;
    ProcessedImageMessage procMessage_FirstImage;
    
    // Applicaiton Functionality
    void kalmanFilterWrapper(double* x_hat, double* phi, double* P, double* Y, double* R, double satTime, double* ephem);
    void computeSolution(DataMessage*, ProcessedImageMessage*);
    double norm(double*);
    double Earth_SC_Moon_Angle(const double r_E_SC[3], const double r_E_M[3]);
    void State_Error(const double X_ref[6], const double X_est[6], double posError[3], double velError[3]);
    void read_referencTraj(std::string);
    void read_ConfigFile(std::string);
};

#endif



