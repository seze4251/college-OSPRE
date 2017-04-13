//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: analyzeImage.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
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
extern void analyzeImage(const emxArray_uint8_T *imIn, const double
  radiusRangeGuess[2], double sensVal, const double pxDeg[2], double imgWidth,
  double imgHeight, double centerPt_data[], int centerPt_size[2], double *radius,
  double *numCirc, double *alpha, double *beta, double *theta, int rectCoords[2]);


#endif

//
// File trailer for analyzeImage.h
//
// [EOF]
//
