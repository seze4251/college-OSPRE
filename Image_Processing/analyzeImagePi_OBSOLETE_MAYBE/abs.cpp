//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: abs.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 14-Feb-2017 14:22:46
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "abs.h"
#include "analyzeImage_emxutil.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *x
//                emxArray_real_T *y
// Return Type  : void
//
void b_abs(const emxArray_real_T *x, emxArray_real_T *y)
{
  int x_idx_0;
  int i9;
  x_idx_0 = x->size[0];
  i9 = y->size[0];
  y->size[0] = x_idx_0;
  emxEnsureCapacity((emxArray__common *)y, i9, (int)sizeof(double));
  for (x_idx_0 = 0; x_idx_0 + 1 <= x->size[0]; x_idx_0++) {
    y->data[x_idx_0] = std::abs(x->data[x_idx_0]);
  }
}

//
// File trailer for abs.cpp
//
// [EOF]
//
