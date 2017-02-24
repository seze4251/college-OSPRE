//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: hypot.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 14-Feb-2017 14:22:46
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "hypot.h"
#include "analyzeImage_emxutil.h"

// Function Declarations
static float rt_hypotf_snf(float u0, float u1);

// Function Definitions

//
// Arguments    : float u0
//                float u1
// Return Type  : float
//
static float rt_hypotf_snf(float u0, float u1)
{
  float y;
  float a;
  float b;
  a = std::abs(u0);
  b = std::abs(u1);
  if (a < b) {
    a /= b;
    y = b * std::sqrt(a * a + 1.0F);
  } else if (a > b) {
    b /= a;
    y = a * std::sqrt(b * b + 1.0F);
  } else if (rtIsNaNF(b)) {
    y = b;
  } else {
    y = a * 1.41421354F;
  }

  return y;
}

//
// Arguments    : const emxArray_real32_T *x
//                const emxArray_real32_T *y
//                emxArray_real32_T *r
// Return Type  : void
//
void b_hypot(const emxArray_real32_T *x, const emxArray_real32_T *y,
             emxArray_real32_T *r)
{
  int n;
  int c;
  int i8;
  if (x->size[0] <= y->size[0]) {
    n = x->size[0];
  } else {
    n = y->size[0];
  }

  if (x->size[1] <= y->size[1]) {
    c = x->size[1];
  } else {
    c = y->size[1];
  }

  i8 = r->size[0] * r->size[1];
  r->size[0] = (short)n;
  r->size[1] = (short)c;
  emxEnsureCapacity((emxArray__common *)r, i8, (int)sizeof(float));
  n = x->size[0] * x->size[1];
  for (c = 0; c + 1 <= n; c++) {
    r->data[c] = rt_hypotf_snf(x->data[c], y->data[c]);
  }
}

//
// File trailer for hypot.cpp
//
// [EOF]
//
