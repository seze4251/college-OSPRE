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
    
    // Applicaiton Functionality
    void computeSolution(DataMessage*, ProcessedImageMessage*);
    void read_referencTraj(std::string);
    
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
    
    // GNC Specific Members
    double x_hat[6];
    double phi[36];
    double P[36];
    double Y[3];
    double R[9];
    double X_est[6];
    double covariance[36];
    double trajectoryDev[6];
    
    // Reference trajectory
    Reference_Trajectory ref_traj;
    
    // From Config File
    double range_EarthRangeCutoff;
    double range_AnglesCutoff;
    
    // Spacecraft Position
    double r_E_SC[3];
    double velSC[3];
    
    // From Estimated range from earth
    double range_estimate;
};

#endif



