//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: im2uint8.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 25-Jan-2017 16:02:21
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "im2uint8.h"
#include "analyzeImage_emxutil.h"

// Function Definitions

//
// Arguments    : const emxArray_real32_T *img
//                emxArray_uint8_T *u
// Return Type  : void
//
void im2uint8(const emxArray_real32_T *img, emxArray_uint8_T *u)
{
  int b_index;
  float val;
  b_index = u->size[0];
  u->size[0] = img->size[0];
  emxEnsureCapacity((emxArray__common *)u, b_index, (int)sizeof(unsigned char));
  for (b_index = 0; b_index < img->size[0]; b_index++) {
    val = img->data[b_index] * 255.0F;
    if (val < 0.0F) {
      u->data[b_index] = 0;
    } else if (val > 255.0F) {
      u->data[b_index] = MAX_uint8_T;
    } else {
      u->data[b_index] = (unsigned char)(val + 0.5F);
    }
  }
}

//
// File trailer for im2uint8.cpp
//
// [EOF]
//
