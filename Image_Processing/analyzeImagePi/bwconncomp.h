//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bwconncomp.h
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 14-Feb-2017 14:49:57
//
#ifndef BWCONNCOMP_H
#define BWCONNCOMP_H

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
extern void bwconncomp(const boolean_T varargin_1[809600], double
  *CC_Connectivity, double CC_ImageSize[2], double *CC_NumObjects,
  emxArray_real_T *CC_RegionIndices, emxArray_int32_T *CC_RegionLengths);

#endif

//
// File trailer for bwconncomp.h
//
// [EOF]
//
