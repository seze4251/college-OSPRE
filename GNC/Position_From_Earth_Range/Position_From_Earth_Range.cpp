//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Position_From_Earth_Range.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 21-Feb-2017 11:44:14
//

// Include Files
#include "Position_From_Earth_Range.h"
#include "sind.h"
#include "cosd.h"
#include "tand.h"

// Function Definitions

//
// %% Calculates the spacecraft position vector in ECI.
//
//  Inputs:   q_E     Spacecraft_Earth quaternion         (vector)
//            alpha   Horizontal quaternion error angle   (deg)
//            beta    Vertical quaternion error angle     (deg)
//            theta   Moon angular diameter               (deg)
//
//  Author:   Cameron Maywood
//  Created:  9/29/2016
//  Modified: 9/29/2016
//
//
// %% Earth radius, km
// Arguments    : const double q_E[4]
//                double alpha
//                double beta
//                double theta
//                double r_E_SC[3]
// Return Type  : void
//
void Position_From_Earth_Range(const double q_E[4], double alpha, double beta,
  double theta, double r_E_SC[3])
{
  double b_q_E[9];
  int i0;
  double r_SC_E[3];
  int i1;
  double d0;
  static const signed char b[3] = { 1, 0, 0 };

  double d1;
  double d2;
  double d3;
  double d4;

  // %% Spacecraft-Moon attitude unit vector
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
  // %% Initial ECI frame (assumed to be pointing in the inertial X-axis direction) 
  // %% Spacecraft attitude vector in ECI
  b_q_E[0] = ((q_E[0] * q_E[0] + q_E[1] * q_E[1]) - q_E[2] * q_E[2]) - q_E[3] *
    q_E[3];
  b_q_E[3] = 2.0 * (q_E[1] * q_E[2] - q_E[3] * q_E[0]);
  b_q_E[6] = 2.0 * (q_E[1] * q_E[3] + q_E[2] * q_E[0]);
  b_q_E[1] = 2.0 * (q_E[1] * q_E[2] + q_E[3] * q_E[0]);
  b_q_E[4] = ((q_E[0] * q_E[0] - q_E[1] * q_E[1]) + q_E[2] * q_E[2]) - q_E[3] *
    q_E[3];
  b_q_E[7] = 2.0 * (q_E[2] * q_E[3] - q_E[1] * q_E[0]);
  b_q_E[2] = 2.0 * (q_E[1] * q_E[3] - q_E[2] * q_E[0]);
  b_q_E[5] = 2.0 * (q_E[2] * q_E[3] + q_E[1] * q_E[0]);
  b_q_E[8] = ((q_E[0] * q_E[0] - q_E[1] * q_E[1]) - q_E[2] * q_E[2]) + q_E[3] *
    q_E[3];
  for (i0 = 0; i0 < 3; i0++) {
    r_SC_E[i0] = 0.0;
    for (i1 = 0; i1 < 3; i1++) {
      r_SC_E[i0] += b_q_E[i0 + 3 * i1] * (double)b[i1];
    }
  }

  // %% Initialize r_E_SC
  // %% X component of ECI position vector
  d0 = theta / 2.0;
  tand(&d0);
  d1 = alpha;
  sind(&d1);
  d2 = alpha;
  cosd(&d2);
  d3 = beta;
  cosd(&d3);
  d4 = beta;
  sind(&d4);
  r_E_SC[0] = 6378.137 / d0 * (r_SC_E[1] * d1 - d2 * (r_SC_E[0] * d3 + r_SC_E[2]
    * d4));

  // %% Y component of ECI position vector
  d0 = theta / 2.0;
  tand(&d0);
  d1 = alpha;
  cosd(&d1);
  d2 = alpha;
  sind(&d2);
  d3 = beta;
  cosd(&d3);
  d4 = beta;
  sind(&d4);
  r_E_SC[1] = -6378.137 / d0 * (r_SC_E[1] * d1 + d2 * (r_SC_E[0] * d3 + r_SC_E[2]
    * d4));

  // %% Z component of ECI position vector
  d0 = theta / 2.0;
  tand(&d0);
  d1 = beta;
  cosd(&d1);
  d2 = beta;
  sind(&d2);
  r_E_SC[2] = 6378.137 / d0 * (-r_SC_E[2] * d1 + r_SC_E[0] * d2);
}

//
// File trailer for Position_From_Earth_Range.cpp
//
// [EOF]
//
