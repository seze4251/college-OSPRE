//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: isequal.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 25-Jan-2017 16:02:21
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "isequal.h"

// Function Definitions

//
// Arguments    : const boolean_T varargin_1[809600]
//                const boolean_T varargin_2[809600]
// Return Type  : boolean_T
//
boolean_T isequal(const boolean_T varargin_1[809600], const boolean_T
                  varargin_2[809600])
{
  boolean_T p;
  boolean_T b_p;
  int k;
  boolean_T exitg1;
  p = false;
  b_p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 809600)) {
    if (varargin_1[k] != varargin_2[k]) {
      b_p = false;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (b_p) {
    p = true;
  }

  return p;
}

//
// File trailer for isequal.cpp
//
// [EOF]
//
