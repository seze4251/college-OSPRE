//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: isfinite.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 25-Jan-2017 16:02:21
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "isfinite.h"

// Function Definitions

//
// Arguments    : double x
// Return Type  : boolean_T
//
boolean_T b_isfinite(double x)
{
  return (!rtIsInf(x)) && (!rtIsNaN(x));
}

//
// Arguments    : float x
// Return Type  : boolean_T
//
boolean_T c_isfinite(float x)
{
  return (!rtIsInfF(x)) && (!rtIsNaNF(x));
}

//
// File trailer for isfinite.cpp
//
// [EOF]
//
