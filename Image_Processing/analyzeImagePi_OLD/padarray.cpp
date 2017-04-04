//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: padarray.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 14-Feb-2017 14:49:57
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "padarray.h"

// Function Definitions

//
// Arguments    : const unsigned char varargin_1[809600]
//                unsigned char b[813276]
// Return Type  : void
//
void padarray(const unsigned char varargin_1[809600], unsigned char b[813276])
{
  int i;
  for (i = 0; i < 738; i++) {
    b[i] = 0;
    b[812538 + i] = 0;
  }

  for (i = 0; i < 1100; i++) {
    b[738 * (i + 1)] = 0;
    b[737 + 738 * (i + 1)] = 0;
    memcpy(&b[i * 738 + 739], &varargin_1[i * 736], 736U * sizeof(unsigned char));
  }
}

//
// File trailer for padarray.cpp
//
// [EOF]
//
