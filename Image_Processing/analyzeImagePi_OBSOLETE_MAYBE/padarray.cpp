//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: padarray.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "padarray.h"
#include "repmat.h"
#include "analyzeImage_emxutil.h"

// Function Definitions

//
// Arguments    : const emxArray_uint8_T *varargin_1
//                emxArray_uint8_T *b
// Return Type  : void
//
void padarray(const emxArray_uint8_T *varargin_1, emxArray_uint8_T *b)
{
  int i2;
  short sizeB[2];
  double b_sizeB[2];
  int i;
  int j;
  int i3;
  if ((varargin_1->size[0] == 0) || (varargin_1->size[1] == 0)) {
    for (i2 = 0; i2 < 2; i2++) {
      sizeB[i2] = (short)((short)varargin_1->size[i2] + 2);
    }

    b_sizeB[0] = sizeB[0];
    b_sizeB[1] = sizeB[1];
    repmat(b_sizeB, b);
  } else {
    for (i2 = 0; i2 < 2; i2++) {
      sizeB[i2] = (short)((short)varargin_1->size[i2] + 2);
    }

    i2 = b->size[0] * b->size[1];
    b->size[0] = sizeB[0];
    b->size[1] = sizeB[1];
    emxEnsureCapacity((emxArray__common *)b, i2, sizeof(unsigned char));
    i2 = b->size[0];
    for (i = 0; i < i2; i++) {
      b->data[i] = 0;
    }

    i2 = b->size[1];
    for (j = varargin_1->size[1] + 1; j + 1 <= i2; j++) {
      i3 = b->size[0];
      for (i = 0; i < i3; i++) {
        b->data[i + b->size[0] * j] = 0;
      }
    }

    for (j = 0; j < varargin_1->size[1]; j++) {
      b->data[b->size[0] * (j + 1)] = 0;
    }

    for (j = 0; j < varargin_1->size[1]; j++) {
      i2 = b->size[0];
      for (i = varargin_1->size[0] + 1; i + 1 <= i2; i++) {
        b->data[i + b->size[0] * (j + 1)] = 0;
      }
    }

    for (j = 0; j < varargin_1->size[1]; j++) {
      for (i = 0; i < varargin_1->size[0]; i++) {
        b->data[(i + b->size[0] * (j + 1)) + 1] = varargin_1->data[i +
          varargin_1->size[0] * j];
      }
    }
  }
}

//
// File trailer for padarray.cpp
//
// [EOF]
//
