//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: analyzeImage.h
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 14-Feb-2017 14:49:57
//
#ifndef ANALYZEIMAGE_H
#define ANALYZEIMAGE_H

// Include Files
#include <cmath>
#include <float.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "analyzeImage_types.h"

// Function Declarations
extern void analyzeImage(const unsigned char imIn[2428800], const double
  radiusRangeGuess[2], double sensVal, double centerPt_data[], int
  centerPt_size[2], double *radius, double *numCirc,
  double* alpha, double* beta, double* theta,
  double pxDeg[2], int imgWidth, int imgHeight);

#endif

//
// File trailer for analyzeImage.h
//
// [EOF]
//
