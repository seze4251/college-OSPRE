//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cosd.cpp
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
#include "cosd.h"
#include "sind.h"
#include "Earth_SC_Moon_Angle_rtwutil.h"

// Function Definitions

//
// Arguments    : double *x
// Return Type  : void
//
void cosd(double *x)
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

  if (n == 0) {
    *x = std::cos(*x);
  } else if (n == 1) {
    *x = -std::sin(*x);
  } else if (n == -1) {
    *x = std::sin(*x);
  } else {
    *x = -std::cos(*x);
  }
}

//
// File trailer for cosd.cpp
//
// [EOF]
//
