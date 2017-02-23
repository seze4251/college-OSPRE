//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Position_From_Moon_Range_rtwutil.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 21-Feb-2017 11:45:08
//

// Include Files
#include "Position_From_Moon_Range.h"
#include "Position_From_Moon_Range_rtwutil.h"
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
// File trailer for Position_From_Moon_Range_rtwutil.cpp
//
// [EOF]
//
