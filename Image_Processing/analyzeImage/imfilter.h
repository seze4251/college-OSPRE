//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: imfilter.h
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 14-Feb-2017 14:49:57
//
#ifndef IMFILTER_H
#define IMFILTER_H

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
extern void b_imfilter(const float varargin_1[809600], float b[809600]);
extern void imfilter(const float varargin_1[809600], float b[809600]);
extern void padImage(const float a_tmp[809600], float a[820652]);

#endif

//
// File trailer for imfilter.h
//
// [EOF]
//
