//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bsxfun.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 14-Feb-2017 14:49:57
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "bsxfun.h"

// Function Definitions

//
// Arguments    : const int a[18]
//                const int b[2]
//                int c[18]
// Return Type  : void
//
void bsxfun(const int a[18], const int b[2], int c[18])
{
  int ak;
  int bk;
  int ck;
  int k;
  ak = 0;
  bk = 0;
  for (ck = 0; ck <= 10; ck += 9) {
    for (k = 0; k < 9; k++) {
      c[ck + k] = a[ak + k] + b[bk];
    }

    ak += 9;
    bk++;
  }
}

//
// File trailer for bsxfun.cpp
//
// [EOF]
//
