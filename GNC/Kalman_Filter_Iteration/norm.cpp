//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: norm.cpp
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
#include "norm.h"

// Function Definitions

//
// Arguments    : const double x[3]
// Return Type  : double
//
double norm(const double x[3])
{
  double y;
  double scale;
  int k;
  double absxk;
  double t;
  y = 0.0;
  scale = 2.2250738585072014E-308;
  for (k = 0; k < 3; k++) {
    absxk = std::abs(x[k]);
    if (absxk > scale) {
      t = scale / absxk;
      y = 1.0 + y * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * std::sqrt(y);
}

//
// File trailer for norm.cpp
//
// [EOF]
//
