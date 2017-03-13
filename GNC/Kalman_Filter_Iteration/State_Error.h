//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: State_Error.h
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 09-Mar-2017 13:26:09
//
#ifndef STATE_ERROR_H
#define STATE_ERROR_H

// Include Files
#include <cmath>
#include <float.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "Kalman_Filter_Iteration_types.h"

// Function Declarations
extern void State_Error(const double X_ref[6], const double X_est[6], double
  posError[3], double velError[3]);

#endif

//
// File trailer for State_Error.h
//
// [EOF]
//
