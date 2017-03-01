//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: tand.cpp
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
#include "tand.h"
#include "sind.h"
#include "Kalman_Filter_Iteration_rtwutil.h"

// Function Definitions

//
// Arguments    : double *x
// Return Type  : void
//
void tand(double *x)
{
  double absx;
  signed char n;
  *x = rt_remd(*x, 360.0);
  absx = std::abs(*x);
  if (absx > 180.0) {
    if (*x > 0.0) {
      *x -= 360.0;
    } else {
      *x += 360.0;
    }

    absx = std::abs(*x);
  }

  if (absx <= 45.0) {
    *x *= 0.017453292519943295;
    n = 0;
  } else if (absx <= 135.0) {
    if (*x > 0.0) {
      *x = 0.017453292519943295 * (*x - 90.0);
      n = 1;
    } else {
      *x = 0.017453292519943295 * (*x + 90.0);
      n = -1;
    }
  } else if (*x > 0.0) {
    *x = 0.017453292519943295 * (*x - 180.0);
    n = 2;
  } else {
    *x = 0.017453292519943295 * (*x + 180.0);
    n = -2;
  }

  *x = std::tan(*x);
  if ((n == 1) || (n == -1)) {
    *x = -(1.0 / *x);
  }
}

//
// File trailer for tand.cpp
//
// [EOF]
//
