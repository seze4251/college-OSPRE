//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Position_From_Earth_Range.cpp
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
  double r_SC_E[3];
  double d8;
  double d9;
  double d10;
  double d11;
  double d12;

  // %% Spacecraft-Moon attitude unit vector
  Quaternion_To_Attitude(q_E, r_SC_E);

  // %% Initialize r_E_SC
  // %% X component of ECI position vector
  d8 = theta / 2.0;
  tand(&d8);
  d9 = alpha;
  sind(&d9);
  d10 = alpha;
  cosd(&d10);
  d11 = beta;
  cosd(&d11);
  d12 = beta;
  sind(&d12);
  r_E_SC[0] = 6378.137 / d8 * (r_SC_E[1] * d9 - d10 * (r_SC_E[0] * d11 + r_SC_E
    [2] * d12));

  // %% Y component of ECI position vector
  d8 = theta / 2.0;
  tand(&d8);
  d9 = alpha;
  cosd(&d9);
  d10 = alpha;
  sind(&d10);
  d11 = beta;
  cosd(&d11);
  d12 = beta;
  sind(&d12);
  r_E_SC[1] = -6378.137 / d8 * (r_SC_E[1] * d9 + d10 * (r_SC_E[0] * d11 +
    r_SC_E[2] * d12));

  // %% Z component of ECI position vector
  d8 = theta / 2.0;
  tand(&d8);
  d9 = beta;
  cosd(&d9);
  d10 = beta;
  sind(&d10);
  r_E_SC[2] = 6378.137 / d8 * (-r_SC_E[2] * d9 + r_SC_E[0] * d10);
}

//
// File trailer for Position_From_Earth_Range.cpp
//
// [EOF]
//
