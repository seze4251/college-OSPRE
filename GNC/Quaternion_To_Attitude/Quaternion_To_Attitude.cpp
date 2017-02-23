//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Quaternion_To_Attitude.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 21-Feb-2017 11:45:49
//

// Include Files
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
  int i0;
  int i1;
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
  for (i0 = 0; i0 < 3; i0++) {
    r_SC_body[i0] = 0.0;
    for (i1 = 0; i1 < 3; i1++) {
      r_SC_body[i0] += b_q[i0 + 3 * i1] * (double)b[i1];
    }
  }
}

//
// File trailer for Quaternion_To_Attitude.cpp
//
// [EOF]
//
