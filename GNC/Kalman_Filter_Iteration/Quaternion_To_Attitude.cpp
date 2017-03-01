//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Quaternion_To_Attitude.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 28-Feb-2017 11:46:21
//

// Include Files
#include "Kalman_Filter_Iteration.h"
#include "Position_From_Angles_Slew.h"
#include "Position_From_Earth_Range.h"
#include "Position_From_Moon_Range.h"
#include "Quaternion_To_Attitude.h"

// Function Definitions

//
// %% Calculates the spacecraft attitude unit vector in ECI.
//
//  Inputs:   q   Quaternion  (vector)
//
//  Author:   Cameron Maywood
//  Created:  9/29/2016
//  Modified: 9/29/2016
//
//
// %% Direct cosine matrix from quaternion
// Arguments    : const double q[4]
//                double r_SC_body[3]
// Return Type  : void
//
void Quaternion_To_Attitude(const double q[4], double r_SC_body[3])
{
  double b_q[9];
  int i1;
  int i2;
  static const signed char b[3] = { 1, 0, 0 };

  // %% Initial ECI frame (assumed to be pointing in the inertial X-axis direction) 
  // %% Spacecraft attitude vector in ECI
  b_q[0] = ((q[0] * q[0] + q[1] * q[1]) - q[2] * q[2]) - q[3] * q[3];
  b_q[3] = 2.0 * (q[1] * q[2] - q[3] * q[0]);
  b_q[6] = 2.0 * (q[1] * q[3] + q[2] * q[0]);
  b_q[1] = 2.0 * (q[1] * q[2] + q[3] * q[0]);
  b_q[4] = ((q[0] * q[0] - q[1] * q[1]) + q[2] * q[2]) - q[3] * q[3];
  b_q[7] = 2.0 * (q[2] * q[3] - q[1] * q[0]);
  b_q[2] = 2.0 * (q[1] * q[3] - q[2] * q[0]);
  b_q[5] = 2.0 * (q[2] * q[3] + q[1] * q[0]);
  b_q[8] = ((q[0] * q[0] - q[1] * q[1]) - q[2] * q[2]) + q[3] * q[3];
  for (i1 = 0; i1 < 3; i1++) {
    r_SC_body[i1] = 0.0;
    for (i2 = 0; i2 < 3; i2++) {
      r_SC_body[i1] += b_q[i1 + 3 * i2] * (double)b[i2];
    }
  }
}

//
// File trailer for Quaternion_To_Attitude.cpp
//
// [EOF]
//
