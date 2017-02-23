//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Position_From_Moon_Range.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 21-Feb-2017 11:45:08
//

// Include Files
#include "Position_From_Moon_Range.h"
#include "sind.h"
#include "cosd.h"
#include "tand.h"

// Function Definitions

//
// %% Calculates the spacecraft position vector in ECI.
//
//  Inputs:   r_E_M   Moon ECI position vector            (km)
//            q_M     Spacecraft_Moon quaternion          (vector)
//            alpha   Horizontal quaternion error angle   (deg)
//            beta    Vertical quaternion error angle     (deg)
//            theta   Moon angular diameter               (deg)
//
//  Author:   Cameron Maywood
//  Created:  9/29/2016
//  Modified: 9/29/2016
//
//
// %% Moon radius, km
// Arguments    : const double r_E_M[3]
//                const double q_M[4]
//                double alpha
//                double beta
//                double theta
//                double r_E_SC[3]
// Return Type  : void
//
void Position_From_Moon_Range(const double r_E_M[3], const double q_M[4], double
  alpha, double beta, double theta, double r_E_SC[3])
{
  double b_q_M[9];
  int i0;
  double r_SC_M[3];
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
  b_q_M[0] = ((q_M[0] * q_M[0] + q_M[1] * q_M[1]) - q_M[2] * q_M[2]) - q_M[3] *
    q_M[3];
  b_q_M[3] = 2.0 * (q_M[1] * q_M[2] - q_M[3] * q_M[0]);
  b_q_M[6] = 2.0 * (q_M[1] * q_M[3] + q_M[2] * q_M[0]);
  b_q_M[1] = 2.0 * (q_M[1] * q_M[2] + q_M[3] * q_M[0]);
  b_q_M[4] = ((q_M[0] * q_M[0] - q_M[1] * q_M[1]) + q_M[2] * q_M[2]) - q_M[3] *
    q_M[3];
  b_q_M[7] = 2.0 * (q_M[2] * q_M[3] - q_M[1] * q_M[0]);
  b_q_M[2] = 2.0 * (q_M[1] * q_M[3] - q_M[2] * q_M[0]);
  b_q_M[5] = 2.0 * (q_M[2] * q_M[3] + q_M[1] * q_M[0]);
  b_q_M[8] = ((q_M[0] * q_M[0] - q_M[1] * q_M[1]) - q_M[2] * q_M[2]) + q_M[3] *
    q_M[3];
  for (i0 = 0; i0 < 3; i0++) {
    r_SC_M[i0] = 0.0;
    for (i1 = 0; i1 < 3; i1++) {
      r_SC_M[i0] += b_q_M[i0 + 3 * i1] * (double)b[i1];
    }
  }

  // %% Initialize r_M_SC
  // %% X component of Moon-SC position vector
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
  r_E_SC[0] = 1738.1 / d0 * (r_SC_M[1] * d1 - d2 * (r_SC_M[0] * d3 + r_SC_M[2] *
    d4));

  // %% Y component of Moon-SC position vector
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
  r_E_SC[1] = -1738.1 / d0 * (r_SC_M[1] * d1 + d2 * (r_SC_M[0] * d3 + r_SC_M[2] *
    d4));

  // %% Z component of Moon-SC position vector
  d0 = theta / 2.0;
  tand(&d0);
  d1 = beta;
  cosd(&d1);
  d2 = beta;
  sind(&d2);
  r_E_SC[2] = 1738.1 / d0 * (-r_SC_M[2] * d1 + r_SC_M[0] * d2);

  // %% ECI position vector
  for (i0 = 0; i0 < 3; i0++) {
    r_E_SC[i0] += r_E_M[i0];
  }
}

//
// File trailer for Position_From_Moon_Range.cpp
//
// [EOF]
//
