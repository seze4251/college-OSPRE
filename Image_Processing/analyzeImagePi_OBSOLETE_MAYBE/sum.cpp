//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sum.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "sum.h"

// Function Definitions

//
// Arguments    : const double x[256]
// Return Type  : double
//
double b_sum(const double x[256])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 255; k++) {
    y += x[k + 1];
  }

  return y;
}

//
// Arguments    : const emxArray_real_T *x
// Return Type  : double
//
double c_sum(const emxArray_real_T *x)
{
  double y;
  int k;
  if (x->size[0] == 0) {
    y = 0.0;
  } else {
    y = x->data[0];
    for (k = 2; k <= x->size[0]; k++) {
      y += x->data[k - 1];
    }
  }

  return y;
}

//
// Arguments    : const boolean_T x_data[]
//                const int x_size[1]
// Return Type  : double
//
double sum(const boolean_T x_data[], const int x_size[1])
{
  double y;
  int k;
  if (x_size[0] == 0) {
    y = 0.0;
  } else {
    y = x_data[0];
    for (k = 2; k <= x_size[0]; k++) {
      y += (double)x_data[k - 1];
    }
  }

  return y;
}

//
// File trailer for sum.cpp
//
// [EOF]
//
