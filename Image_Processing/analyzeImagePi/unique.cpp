//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: unique.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "unique.h"

// Function Definitions

//
// Arguments    : const emxArray_real32_T *b
//                int nb
//                int *nMInf
//                int *nFinite
//                int *nPInf
//                int *nNaN
// Return Type  : void
//
void count_nonfinites(const emxArray_real32_T *b, int nb, int *nMInf, int
                      *nFinite, int *nPInf, int *nNaN)
{
  int k;
  k = 0;
  while ((k + 1 <= nb) && rtIsInfF(b->data[k]) && (b->data[k] < 0.0F)) {
    k++;
  }

  *nMInf = k;
  k = nb;
  while ((k >= 1) && rtIsNaNF(b->data[k - 1])) {
    k--;
  }

  *nNaN = nb - k;
  while ((k >= 1) && rtIsInfF(b->data[k - 1]) && (b->data[k - 1] > 0.0F)) {
    k--;
  }

  *nPInf = (nb - k) - *nNaN;
  *nFinite = k - *nMInf;
}

//
// File trailer for unique.cpp
//
// [EOF]
//
