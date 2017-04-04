//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: exp.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "exp.h"

// Function Definitions

//
// Arguments    : emxArray_creal_T *x
// Return Type  : void
//
void b_exp(emxArray_creal_T *x)
{
  int nx;
  int k;
  double x_re;
  double r;
  nx = x->size[1];
  for (k = 0; k + 1 <= nx; k++) {
    if (x->data[k].im == 0.0) {
      x_re = std::exp(x->data[k].re);
      r = 0.0;
    } else if (rtIsInf(x->data[k].im) && rtIsInf(x->data[k].re) && (x->data[k].
                re < 0.0)) {
      x_re = 0.0;
      r = 0.0;
    } else {
      r = std::exp(x->data[k].re / 2.0);
      x_re = r * (r * std::cos(x->data[k].im));
      r *= r * std::sin(x->data[k].im);
    }

    x->data[k].re = x_re;
    x->data[k].im = r;
  }
}

//
// File trailer for exp.cpp
//
// [EOF]
//
