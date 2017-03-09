//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Earth_SC_Moon_Angle.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 09-Mar-2017 10:09:18
//

// Include Files
#include "Earth_SC_Moon_Angle.h"
#include "Kalman_Filter_Iteration.h"
#include "Position_From_Angles_Slew.h"
#include "Position_From_Earth_Range.h"
#include "Position_From_Moon_Range.h"
#include "Quaternion_To_Attitude.h"
#include "State_Error.h"
#include "norm.h"

// Function Definitions

//
// Spacecraft-Moon position vector
// Arguments    : const double r_E_SC[3]
//                const double r_E_M[3]
// Return Type  : double
//
double Earth_SC_Moon_Angle(const double r_E_SC[3], const double r_E_M[3])
{
  double c;
  double r_SC_M[3];
  double r_SC_E[3];
  int k;
  double b_r_SC_M;

  //  Earth-Spacecraft-Moon Angle Function
  //   Calculates the Earth-Spacecraft-Moon angle from the spacecraft and moon
  //   positions.
  //
  //   Author:   Cameron Maywood
  //   Created:  3/8/2017
  //   Modified: 3/8/2017
  //             _____________________________________________________________
  //   Inputs:  |          r_E_SC         |  Spacecraft ECI position vector   |
  //            |          r_E_M          |  Moon ECI position vector         |
  //            |_________________________|___________________________________|
  //   Outputs: |   angle_Earth_SC_Moon   |   Earth-spacecraft-moon angle     |
  //            |_________________________|___________________________________|
  //  Spacecraft-Earth position vector
  //  Earth-spacecraft-Moon angle
  c = 0.0;
  for (k = 0; k < 3; k++) {
    b_r_SC_M = r_E_M[k] - r_E_SC[k];
    c += b_r_SC_M * -r_E_SC[k];
    r_SC_M[k] = b_r_SC_M;
    r_SC_E[k] = -r_E_SC[k];
  }

  return 57.295779513082323 * std::acos(c / (norm(r_SC_M) * norm(r_SC_E)));
}

//
// File trailer for Earth_SC_Moon_Angle.cpp
//
// [EOF]
//
