//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Position_From_Moon_Range.h
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 28-Feb-2017 11:46:21
//
#ifndef POSITION_FROM_MOON_RANGE_H
#define POSITION_FROM_MOON_RANGE_H

// Include Files
#include <cmath>
#include <float.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "Kalman_Filter_Iteration_types.h"

// Function Declarations
extern void Position_From_Moon_Range(const double r_E_M[3], const double q_M[4],
  double alpha, double beta, double theta, double r_E_SC[3]);

#endif

//
// File trailer for Position_From_Moon_Range.h
//
// [EOF]
//
