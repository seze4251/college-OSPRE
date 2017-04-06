//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Position_From_Moon_Range.cpp
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
#include <stdio.h>
#include "../../include/Exception/OSPRE_Exceptions.h"

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

  // INPUT EXCEPTIONS
  if (sqrt(pow(q_M[0], 2) + pow(q_M[1], 2) + pow(q_M[2], 2) + pow(q_M[3], 2)) - 1 > 0.0001) {
      char logString[100];
      sprintf(logString, "ERROR: Position_From_Moon_Range(). Invalid spacecraft-Moon quaternion.\n");
      throw InvalidInputs(logString);
  }
  if (alpha < 0 | alpha > 360) {
      char logString[100];
      sprintf(logString, "ERROR: Position_From_Moon_Range(). Moon alpha angle not in valid range.\n");
      throw InvalidInputs(logString);
  }
  if (beta < 0 | beta > 360) {
      char logString[100];
      sprintf(logString, "ERROR: Position_From_Moon_Range(). Moon beta angle not in valid range.\n");
      throw InvalidInputs(logString);
  }
  if (theta < 0 | theta > 180) {
      char logString[100];
      sprintf(logString, "ERROR: Position_From_Moon_Range(). Moon theta angle not in valid range.\n");
      throw InvalidInputs(logString);
  }

  double r_SC_M[3];
  double d13;
  double d14;
  double d15;
  double d16;
  double d17;
  int i3;

  // %% Spacecraft-Moon attitude unit vector
  Quaternion_To_Attitude(q_M, r_SC_M);

  // %% Initialize r_M_SC
  // %% X component of Moon-SC position vector
  d13 = theta / 2.0;
  tand(&d13);
  d14 = alpha;
  sind(&d14);
  d15 = alpha;
  cosd(&d15);
  d16 = beta;
  cosd(&d16);
  d17 = beta;
  sind(&d17);
  r_E_SC[0] = 1738.1 / d13 * (r_SC_M[1] * d14 - d15 * (r_SC_M[0] * d16 + r_SC_M
    [2] * d17));

  // %% Y component of Moon-SC position vector
  d13 = theta / 2.0;
  tand(&d13);
  d14 = alpha;
  cosd(&d14);
  d15 = alpha;
  sind(&d15);
  d16 = beta;
  cosd(&d16);
  d17 = beta;
  sind(&d17);
  r_E_SC[1] = -1738.1 / d13 * (r_SC_M[1] * d14 + d15 * (r_SC_M[0] * d16 +
    r_SC_M[2] * d17));

  // %% Z component of Moon-SC position vector
  d13 = theta / 2.0;
  tand(&d13);
  d14 = beta;
  cosd(&d14);
  d15 = beta;
  sind(&d15);
  r_E_SC[2] = 1738.1 / d13 * (-r_SC_M[2] * d14 + r_SC_M[0] * d15);

  // %% ECI position vector
  for (i3 = 0; i3 < 3; i3++) {
    r_E_SC[i3] += r_E_M[i3];
  }
}

//
// File trailer for Position_From_Moon_Range.cpp
//
// [EOF]
//
