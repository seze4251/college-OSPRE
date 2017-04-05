//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: multithresh.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//
#ifndef MULTITHRESH_H
#define MULTITHRESH_H

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
extern void b_getDegenerateThresholds(const emxArray_real32_T *uniqueVals,
  emxArray_real32_T *thresh);
extern void checkForDegenerateInput(const emxArray_real32_T *A, boolean_T
  *isDegenerate, emxArray_real32_T *uniqueVals);
extern void getDegenerateThresholds(const emxArray_real32_T *uniqueVals,
  emxArray_real32_T *thresh);
extern void getpdf(emxArray_real32_T *A, double p[256], float *minA, float *maxA,
                   boolean_T *emptyp);
extern void map2OriginalScale(const emxArray_real_T *thresh, float minA, float
  maxA, emxArray_real32_T *sclThresh);

#endif

//
// File trailer for multithresh.h
//
// [EOF]
//
