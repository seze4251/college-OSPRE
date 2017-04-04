//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: convn.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//
#ifndef CONVN_H
#define CONVN_H

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
extern void b_convn(const emxArray_real_T *A, emxArray_real_T *C);
extern void c_convn(const emxArray_real_T *A, emxArray_real_T *C);
extern void convn(const emxArray_real_T *A, emxArray_real_T *C);

#endif

//
// File trailer for convn.h
//
// [EOF]
//
