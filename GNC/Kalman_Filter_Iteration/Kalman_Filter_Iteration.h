//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Kalman_Filter_Iteration.h
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 28-Feb-2017 11:46:21
//
#ifndef KALMAN_FILTER_ITERATION_H
#define KALMAN_FILTER_ITERATION_H

// Include Files
#include <cmath>
#include <float.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "Kalman_Filter_Iteration_types.h"

// Function Declarations
extern void Kalman_Filter_Iteration(const double x_hat_0[6], const double phi[36],
  const double P_0[36], const double Y[3], const double X_ref[6], const double
  R[9], double X_est[6], double x_hat[6], double P[36], double y[3]);

#endif

//
// File trailer for Kalman_Filter_Iteration.h
//
// [EOF]
//
