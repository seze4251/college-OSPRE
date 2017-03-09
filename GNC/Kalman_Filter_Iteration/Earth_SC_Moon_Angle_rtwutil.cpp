//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Earth_SC_Moon_Angle_rtwutil.cpp
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
#include "Earth_SC_Moon_Angle_rtwutil.h"
#include "sind.h"

// Function Definitions

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
double rt_remd(double u0, double u1)
{
  double y;
  double b_u1;
  double tr;
  if (u1 < 0.0) {
    b_u1 = std::ceil(u1);
  } else {
    b_u1 = std::floor(u1);
  }

  if ((u1 != 0.0) && (u1 != b_u1)) {
    tr = u0 / u1;
    if (std::abs(tr - rt_roundd(tr)) <= DBL_EPSILON * std::abs(tr)) {
      y = 0.0;
    } else {
      y = std::fmod(u0, u1);
    }
  } else {
    y = std::fmod(u0, u1);
  }

  return y;
}

//
// Arguments    : double u
// Return Type  : double
//
double rt_roundd(double u)
{
  double y;
  if (std::abs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = std::floor(u + 0.5);
    } else if (u > -0.5) {
      y = 0.0;
    } else {
      y = std::ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

//
// File trailer for Earth_SC_Moon_Angle_rtwutil.cpp
//
// [EOF]
//
