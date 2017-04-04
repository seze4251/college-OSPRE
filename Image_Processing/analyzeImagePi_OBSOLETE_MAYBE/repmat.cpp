//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: repmat.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "repmat.h"
#include "analyzeImage_emxutil.h"

// Function Definitions

//
// Arguments    : const double varargin_1[2]
//                emxArray_real32_T *b
// Return Type  : void
//
void b_repmat(const double varargin_1[2], emxArray_real32_T *b)
{
  int i10;
  int loop_ub;
  i10 = b->size[0] * b->size[1];
  b->size[0] = (short)(int)varargin_1[0];
  b->size[1] = (short)(int)varargin_1[1];
  emxEnsureCapacity((emxArray__common *)b, i10, sizeof(float));
  loop_ub = (short)(int)varargin_1[0] * (short)(int)varargin_1[1];
  for (i10 = 0; i10 < loop_ub; i10++) {
    b->data[i10] = 0.0F;
  }
}

//
// Arguments    : const double varargin_1[2]
//                emxArray_uint8_T *b
// Return Type  : void
//
void repmat(const double varargin_1[2], emxArray_uint8_T *b)
{
  int i4;
  int loop_ub;
  i4 = b->size[0] * b->size[1];
  b->size[0] = (short)(int)varargin_1[0];
  b->size[1] = (short)(int)varargin_1[1];
  emxEnsureCapacity((emxArray__common *)b, i4, sizeof(unsigned char));
  loop_ub = (short)(int)varargin_1[0] * (short)(int)varargin_1[1];
  for (i4 = 0; i4 < loop_ub; i4++) {
    b->data[i4] = 0;
  }
}

//
// File trailer for repmat.cpp
//
// [EOF]
//
