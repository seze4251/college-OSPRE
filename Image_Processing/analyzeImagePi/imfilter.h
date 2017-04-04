//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: imfilter.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
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
extern void b_imfilter(const emxArray_real32_T *varargin_1, emxArray_real32_T *b);
extern void imfilter(const emxArray_real32_T *varargin_1, emxArray_real32_T *b);
extern void padImage(const emxArray_real32_T *a_tmp, const double pad[2],
                     emxArray_real32_T *a);

#endif

//
// File trailer for imfilter.h
//
// [EOF]
//
