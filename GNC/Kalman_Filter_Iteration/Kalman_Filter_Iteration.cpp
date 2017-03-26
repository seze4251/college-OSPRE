//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Kalman_Filter_Iteration.cpp
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
#include <stdio.h>
#include "../../include/Exception/OSPRE_Exceptions.h"

// Function Definitions

void get_Reference_Trajectory(double X_ref[6], Reference_Trajectory ref_traj, double time) {
    
    // Create array of differences between current time and reference trajectory times
    int ref_traj_size = sizeof(ref_traj.time)/sizeof(ref_traj.time[0]);
    double time_diff [ref_traj_size];
    for(int i = 0; i < ref_traj_size; i++){
        time_diff[i] = std::abs(time - ref_traj.time[i]);
    }
    
    // Find smallest time difference and index of smallest time difference
    double smallest = time_diff[0];
    int smallest_index = 0;
    for(int i = 1; i < ref_traj_size; i++){
        if(time_diff[i] < smallest){
            smallest = time_diff[i];
            smallest_index = i;
        }
    }
    
    // Use closest reference trajectory
    X_ref[0] = ref_traj.X[smallest_index];
    X_ref[1] = ref_traj.Y[smallest_index];
    X_ref[2] = ref_traj.Z[smallest_index];
    X_ref[3] = ref_traj.VX[smallest_index];
    X_ref[4] = ref_traj.VY[smallest_index];
    X_ref[5] = ref_traj.VZ[smallest_index];
}


//
// Time Update
// Arguments    : double x_hat[6]
//                const double phi[36]
//                double P[36]
//                const double Y[3]
//                const double X_ref[6]
//                const double R[9]
//                double X_est[6]
// Return Type  : void
//
void Kalman_Filter_Iteration(double x_hat[6], const double phi[36], double P[36], const double Y[3], const double R[9], double X_ref[6], double time, double X_est[6])
{
    
    // INPUT EXCEPTIONS
    if (sqrt(pow(X_ref[0], 2) + pow(X_ref[1], 2) + pow(X_ref[2], 2)) < 6378.137) {
        char logString[100];
        sprintf(logString, "ERROR IN: Kalman_Filter_Iteration.cpp\nReference state cannot be within the radius of Earth.");
        throw InvalidInputs(logString);
    }
    
    double b_phi[36];
    int p3;
    double x_bar[6];
    double a[18];
    int p2;
    double b_a[9];
    int p1;
    double x[9];
    double P_bar[36];
    double absx11;
    static const signed char c_a[18] = { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0 };
    
    double absx21;
    double absx31;
    static const signed char b[18] = { 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 0 };
    
    int itmp;
    double c[9];
    double b_Y[3];
    double K[18];
    signed char I[36];
    signed char b_I[36];
    double c_I[36];
    double d_I[36];
    
    //  Kalman_Filter_Iteration Function
    //   Calculates the state vector of the next measurement given the Kalman
    //   filter initial conditions of the previous measurement.
    //
    //   Author:   Cameron Maywood
    //   Created:  11/04/2016
    //   Modified: 12/10/2016
    //             __________________________________________________________
    //   Inputs:  |   x_hat_0   |   Initial reference trajectory deviance    |
    //            |     phi     |   Next state transition matrix             |
    //            |     P_0     |   Initial covariance matrix                |
    //            |      Y      |   Next state observation                   |
    //            |    X_ref    |   Next spacecraft 3-body reference state   |
    //            |      R      |   Next state error covariance              |
    //            |_____________|____________________________________________|
    //   Outputs: |    X_est    |   New estimated spacecraft state vector    |
    //            |    x_hat    |   New reference trajectory deviation       |
    //            |      P      |   New covariance matrix                    |
    //            |      y      |   Residuals matrix                         |
    //            |_____________|____________________________________________|
    //
    for (p3 = 0; p3 < 6; p3++) {
        x_bar[p3] = 0.0;
        for (p2 = 0; p2 < 6; p2++) {
            b_phi[p3 + 6 * p2] = 0.0;
            for (p1 = 0; p1 < 6; p1++) {
                b_phi[p3 + 6 * p2] += phi[p3 + 6 * p1] * P[p1 + 6 * p2];
            }
            
            x_bar[p3] += phi[p3 + 6 * p2] * x_hat[p2];
        }
        
        for (p2 = 0; p2 < 6; p2++) {
            P_bar[p3 + 6 * p2] = 0.0;
            for (p1 = 0; p1 < 6; p1++) {
                P_bar[p3 + 6 * p2] += b_phi[p3 + 6 * p1] * phi[p2 + 6 * p1];
            }
        }
    }
    
    //  Observation Deviation, Observation State Matrix, Gain Matrix
    for (p3 = 0; p3 < 3; p3++) {
        for (p2 = 0; p2 < 6; p2++) {
            a[p3 + 3 * p2] = 0.0;
            for (p1 = 0; p1 < 6; p1++) {
                a[p3 + 3 * p2] += (double)c_a[p3 + 3 * p1] * P_bar[p1 + 6 * p2];
            }
        }
        
        for (p2 = 0; p2 < 3; p2++) {
            absx11 = 0.0;
            for (p1 = 0; p1 < 6; p1++) {
                absx11 += a[p3 + 3 * p1] * (double)b[p1 + 6 * p2];
            }
            
            b_a[p3 + 3 * p2] = absx11 + R[p3 + 3 * p2];
        }
    }
    
    memcpy(&x[0], &b_a[0], 9U * sizeof(double));
    p1 = 0;
    p2 = 3;
    p3 = 6;
    absx11 = std::abs(b_a[0]);
    absx21 = std::abs(b_a[1]);
    absx31 = std::abs(b_a[2]);
    if ((absx21 > absx11) && (absx21 > absx31)) {
        p1 = 3;
        p2 = 0;
        x[0] = b_a[1];
        x[1] = b_a[0];
        x[3] = b_a[4];
        x[4] = b_a[3];
        x[6] = b_a[7];
        x[7] = b_a[6];
    } else {
        if (absx31 > absx11) {
            p1 = 6;
            p3 = 0;
            x[0] = b_a[2];
            x[2] = b_a[0];
            x[3] = b_a[5];
            x[5] = b_a[3];
            x[6] = b_a[8];
            x[8] = b_a[6];
        }
    }
    
    absx11 = x[1] / x[0];
    x[1] /= x[0];
    absx21 = x[2] / x[0];
    x[2] /= x[0];
    x[4] -= absx11 * x[3];
    x[5] -= absx21 * x[3];
    x[7] -= absx11 * x[6];
    x[8] -= absx21 * x[6];
    if (std::abs(x[5]) > std::abs(x[4])) {
        itmp = p2;
        p2 = p3;
        p3 = itmp;
        x[1] = absx21;
        x[2] = absx11;
        absx11 = x[4];
        x[4] = x[5];
        x[5] = absx11;
        absx11 = x[7];
        x[7] = x[8];
        x[8] = absx11;
    }
    
    absx11 = x[5] / x[4];
    x[5] /= x[4];
    x[8] -= absx11 * x[7];
    absx11 = (x[5] * x[1] - x[2]) / x[8];
    absx21 = -(x[1] + x[7] * absx11) / x[4];
    c[p1] = ((1.0 - x[3] * absx21) - x[6] * absx11) / x[0];
    c[p1 + 1] = absx21;
    c[p1 + 2] = absx11;
    absx11 = -x[5] / x[8];
    absx21 = (1.0 - x[7] * absx11) / x[4];
    c[p2] = -(x[3] * absx21 + x[6] * absx11) / x[0];
    c[p2 + 1] = absx21;
    c[p2 + 2] = absx11;
    absx11 = 1.0 / x[8];
    absx21 = -x[7] * absx11 / x[4];
    c[p3] = -(x[3] * absx21 + x[6] * absx11) / x[0];
    c[p3 + 1] = absx21;
    c[p3 + 2] = absx11;
    for (p3 = 0; p3 < 6; p3++) {
        for (p2 = 0; p2 < 3; p2++) {
            a[p3 + 6 * p2] = 0.0;
            for (p1 = 0; p1 < 6; p1++) {
                a[p3 + 6 * p2] += P_bar[p3 + 6 * p1] * (double)b[p1 + 6 * p2];
            }
        }
        
        for (p2 = 0; p2 < 3; p2++) {
            K[p3 + 6 * p2] = 0.0;
            for (p1 = 0; p1 < 3; p1++) {
                K[p3 + 6 * p2] += a[p3 + 6 * p1] * c[p1 + 3 * p2];
            }
        }
    }
    
    //  Measurement Update
    for (p3 = 0; p3 < 3; p3++) {
        absx11 = 0.0;
        for (p2 = 0; p2 < 6; p2++) {
            absx11 += (double)c_a[p3 + 3 * p2] * x_bar[p2];
        }
        
        b_Y[p3] = (Y[p3] - X_ref[p3]) - absx11;
    }
    
    for (p3 = 0; p3 < 6; p3++) {
        absx11 = 0.0;
        for (p2 = 0; p2 < 3; p2++) {
            absx11 += K[p3 + 6 * p2] * b_Y[p2];
        }
        
        x_hat[p3] = x_bar[p3] + absx11;
    }
    
    for (p3 = 0; p3 < 36; p3++) {
        I[p3] = 0;
    }
    
    for (p1 = 0; p1 < 6; p1++) {
        I[p1 + 6 * p1] = 1;
    }
    
    for (p3 = 0; p3 < 36; p3++) {
        b_I[p3] = 0;
    }
    
    for (p1 = 0; p1 < 6; p1++) {
        b_I[p1 + 6 * p1] = 1;
        for (p3 = 0; p3 < 6; p3++) {
            absx11 = 0.0;
            for (p2 = 0; p2 < 3; p2++) {
                absx11 += K[p1 + 6 * p2] * (double)c_a[p2 + 3 * p3];
            }
            
            c_I[p1 + 6 * p3] = (double)I[p1 + 6 * p3] - absx11;
        }
        
        for (p3 = 0; p3 < 6; p3++) {
            d_I[p1 + 6 * p3] = 0.0;
            for (p2 = 0; p2 < 6; p2++) {
                d_I[p1 + 6 * p3] += c_I[p1 + 6 * p2] * P_bar[p2 + 6 * p3];
            }
        }
    }
    
    for (p3 = 0; p3 < 6; p3++) {
        for (p2 = 0; p2 < 6; p2++) {
            absx11 = 0.0;
            for (p1 = 0; p1 < 3; p1++) {
                absx11 += K[p2 + 6 * p1] * (double)c_a[p1 + 3 * p3];
            }
            
            c_I[p3 + 6 * p2] = (double)b_I[p2 + 6 * p3] - absx11;
        }
        
        for (p2 = 0; p2 < 3; p2++) {
            a[p3 + 6 * p2] = 0.0;
            for (p1 = 0; p1 < 3; p1++) {
                a[p3 + 6 * p2] += K[p3 + 6 * p1] * R[p1 + 3 * p2];
            }
        }
    }
    
    for (p3 = 0; p3 < 6; p3++) {
        for (p2 = 0; p2 < 6; p2++) {
            b_phi[p3 + 6 * p2] = 0.0;
            for (p1 = 0; p1 < 6; p1++) {
                b_phi[p3 + 6 * p2] += d_I[p3 + 6 * p1] * c_I[p1 + 6 * p2];
            }
            
            P_bar[p3 + 6 * p2] = 0.0;
            for (p1 = 0; p1 < 3; p1++) {
                P_bar[p3 + 6 * p2] += a[p3 + 6 * p1] * K[p2 + 6 * p1];
            }
        }
    }
    
    //  Updated Estimate
    for (p1 = 0; p1 < 6; p1++) {
        for (p3 = 0; p3 < 6; p3++) {
            P[p3 + 6 * p1] = b_phi[p3 + 6 * p1] + P_bar[p3 + 6 * p1];
        }
        
        X_est[p1] = X_ref[p1] + x_hat[p1];
    }
    
    // OUTPUT EXCEPTIONS
    if (sqrt(pow(X_est[0], 2) + pow(X_est[1], 2) + pow(X_est[2], 2)) < 6378.137) {
        char logString[100];
        sprintf(logString, "ERROR IN: Kalman_Filter_Iteration.cpp\nEstimated state cannot be within the radius of Earth.");
        throw InvalidOutput(logString);
    }
}




//
// File trailer for Kalman_Filter_Iteration.cpp
//
// [EOF]
//
