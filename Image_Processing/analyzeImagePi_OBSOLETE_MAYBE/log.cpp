//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: log.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "log.h"

// Function Definitions

//
// Arguments    : emxArray_real_T *x
// Return Type  : void
//
void b_log(emxArray_real_T *x)
{
  int nx;
  int k;
  nx = x->size[1];
  for (k = 0; k + 1 <= nx; k++) {
    x->data[k] = std::log(x->data[k]);
  }
}

//
// File trailer for log.cpp
//
// [EOF]
//
