//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: quickselect.h
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 14-Feb-2017 14:49:57
//
#ifndef QUICKSELECT_H
#define QUICKSELECT_H

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
extern void quickselect(double v_data[], int v_size[1], int n, int vlen, double *
  vn, int *nfirst, int *nlast);
extern int thirdOfFive(const double v[25], int ia, int ib);

#endif

//
// File trailer for quickselect.h
//
// [EOF]
//
