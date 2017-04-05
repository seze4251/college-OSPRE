//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: imfilter.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "imfilter.h"
#include "analyzeImage_emxutil.h"
#include "convn.h"
#include "repmat.h"

// Function Definitions

//
// Arguments    : const emxArray_real32_T *varargin_1
//                emxArray_real32_T *b
// Return Type  : void
//
void b_imfilter(const emxArray_real32_T *varargin_1, emxArray_real32_T *b)
{
  short finalSize_idx_0;
  double pad[2];
  short finalSize_idx_1;
  emxArray_real32_T *a;
  int i16;
  emxArray_real32_T *r6;
  int loop_ub;
  emxArray_real_T *b_a;
  emxArray_real_T *result;
  int i17;
  int i18;
  int i19;
  int i20;
  int b_loop_ub;
  finalSize_idx_0 = (short)varargin_1->size[0];
  pad[0] = 1.0;
  finalSize_idx_1 = (short)varargin_1->size[1];
  pad[1] = 1.0;
  if ((varargin_1->size[0] == 0) || (varargin_1->size[1] == 0)) {
    i16 = b->size[0] * b->size[1];
    b->size[0] = varargin_1->size[0];
    b->size[1] = varargin_1->size[1];
    emxEnsureCapacity((emxArray__common *)b, i16, sizeof(float));
    loop_ub = varargin_1->size[0] * varargin_1->size[1];
    for (i16 = 0; i16 < loop_ub; i16++) {
      b->data[i16] = varargin_1->data[i16];
    }
  } else {
    emxInit_real32_T(&a, 2);
    emxInit_real32_T(&r6, 2);
    padImage(varargin_1, pad, r6);
    i16 = a->size[0] * a->size[1];
    a->size[0] = r6->size[0];
    a->size[1] = r6->size[1];
    emxEnsureCapacity((emxArray__common *)a, i16, sizeof(float));
    loop_ub = r6->size[0] * r6->size[1];
    for (i16 = 0; i16 < loop_ub; i16++) {
      a->data[i16] = r6->data[i16];
    }

    emxFree_real32_T(&r6);
    emxInit_real_T(&b_a, 2);
    i16 = b_a->size[0] * b_a->size[1];
    b_a->size[0] = a->size[0];
    b_a->size[1] = a->size[1];
    emxEnsureCapacity((emxArray__common *)b_a, i16, sizeof(double));
    loop_ub = a->size[0] * a->size[1];
    for (i16 = 0; i16 < loop_ub; i16++) {
      b_a->data[i16] = a->data[i16];
    }

    emxFree_real32_T(&a);
    emxInit_real_T(&result, 2);
    c_convn(b_a, result);
    emxFree_real_T(&b_a);
    if (2 > finalSize_idx_0 + 1) {
      i16 = 0;
      i17 = 0;
    } else {
      i16 = 1;
      i17 = finalSize_idx_0 + 1;
    }

    if (2 > finalSize_idx_1 + 1) {
      i18 = 0;
      i19 = 0;
    } else {
      i18 = 1;
      i19 = finalSize_idx_1 + 1;
    }

    i20 = b->size[0] * b->size[1];
    b->size[0] = i17 - i16;
    b->size[1] = i19 - i18;
    emxEnsureCapacity((emxArray__common *)b, i20, sizeof(float));
    loop_ub = i19 - i18;
    for (i19 = 0; i19 < loop_ub; i19++) {
      b_loop_ub = i17 - i16;
      for (i20 = 0; i20 < b_loop_ub; i20++) {
        b->data[i20 + b->size[0] * i19] = (float)result->data[(i16 + i20) +
          result->size[0] * (i18 + i19)];
      }
    }

    emxFree_real_T(&result);
  }
}

//
// Arguments    : const emxArray_real32_T *varargin_1
//                emxArray_real32_T *b
// Return Type  : void
//
void imfilter(const emxArray_real32_T *varargin_1, emxArray_real32_T *b)
{
  short finalSize_idx_0;
  double pad[2];
  short finalSize_idx_1;
  emxArray_real32_T *a;
  int i11;
  emxArray_real32_T *r5;
  int loop_ub;
  emxArray_real_T *b_a;
  emxArray_real_T *result;
  int i12;
  int i13;
  int i14;
  int i15;
  int b_loop_ub;
  finalSize_idx_0 = (short)varargin_1->size[0];
  pad[0] = 1.0;
  finalSize_idx_1 = (short)varargin_1->size[1];
  pad[1] = 1.0;
  if ((varargin_1->size[0] == 0) || (varargin_1->size[1] == 0)) {
    i11 = b->size[0] * b->size[1];
    b->size[0] = varargin_1->size[0];
    b->size[1] = varargin_1->size[1];
    emxEnsureCapacity((emxArray__common *)b, i11, sizeof(float));
    loop_ub = varargin_1->size[0] * varargin_1->size[1];
    for (i11 = 0; i11 < loop_ub; i11++) {
      b->data[i11] = varargin_1->data[i11];
    }
  } else {
    emxInit_real32_T(&a, 2);
    emxInit_real32_T(&r5, 2);
    padImage(varargin_1, pad, r5);
    i11 = a->size[0] * a->size[1];
    a->size[0] = r5->size[0];
    a->size[1] = r5->size[1];
    emxEnsureCapacity((emxArray__common *)a, i11, sizeof(float));
    loop_ub = r5->size[0] * r5->size[1];
    for (i11 = 0; i11 < loop_ub; i11++) {
      a->data[i11] = r5->data[i11];
    }

    emxFree_real32_T(&r5);
    emxInit_real_T(&b_a, 2);
    i11 = b_a->size[0] * b_a->size[1];
    b_a->size[0] = a->size[0];
    b_a->size[1] = a->size[1];
    emxEnsureCapacity((emxArray__common *)b_a, i11, sizeof(double));
    loop_ub = a->size[0] * a->size[1];
    for (i11 = 0; i11 < loop_ub; i11++) {
      b_a->data[i11] = a->data[i11];
    }

    emxFree_real32_T(&a);
    emxInit_real_T(&result, 2);
    b_convn(b_a, result);
    emxFree_real_T(&b_a);
    if (2 > finalSize_idx_0 + 1) {
      i11 = 0;
      i12 = 0;
    } else {
      i11 = 1;
      i12 = finalSize_idx_0 + 1;
    }

    if (2 > finalSize_idx_1 + 1) {
      i13 = 0;
      i14 = 0;
    } else {
      i13 = 1;
      i14 = finalSize_idx_1 + 1;
    }

    i15 = b->size[0] * b->size[1];
    b->size[0] = i12 - i11;
    b->size[1] = i14 - i13;
    emxEnsureCapacity((emxArray__common *)b, i15, sizeof(float));
    loop_ub = i14 - i13;
    for (i14 = 0; i14 < loop_ub; i14++) {
      b_loop_ub = i12 - i11;
      for (i15 = 0; i15 < b_loop_ub; i15++) {
        b->data[i15 + b->size[0] * i14] = (float)result->data[(i11 + i15) +
          result->size[0] * (i13 + i14)];
      }
    }

    emxFree_real_T(&result);
  }
}

//
// Arguments    : const emxArray_real32_T *a_tmp
//                const double pad[2]
//                emxArray_real32_T *a
// Return Type  : void
//
void padImage(const emxArray_real32_T *a_tmp, const double pad[2],
              emxArray_real32_T *a)
{
  int i8;
  double sizeA[2];
  double b_sizeA[2];
  short c_sizeA[2];
  int ixstart;
  double varargin_1[2];
  double mtmp;
  int ix;
  boolean_T exitg1;
  int y_size_idx_1;
  int idxDir_size_idx_1;
  short y_data[4163];
  unsigned int idxDir_data[4166];
  int i9;
  short tmp_data[3126];
  int b_idxDir_data[3126];
  int idxA_data[8332];
  short b_tmp_data[4166];
  int c_idxDir_data[4166];
  if ((a_tmp->size[0] == 0) || (a_tmp->size[1] == 0)) {
    for (i8 = 0; i8 < 2; i8++) {
      b_sizeA[i8] = (double)a_tmp->size[i8] + 2.0 * pad[i8];
    }

    sizeA[0] = b_sizeA[0];
    sizeA[1] = b_sizeA[1];
    b_repmat(sizeA, a);
  } else {
    for (i8 = 0; i8 < 2; i8++) {
      b_sizeA[i8] = a_tmp->size[i8];
    }

    sizeA[0] = 2.0 * pad[0];
    sizeA[1] = 2.0 * pad[1];
    c_sizeA[0] = (short)b_sizeA[0];
    c_sizeA[1] = (short)b_sizeA[1];
    for (i8 = 0; i8 < 2; i8++) {
      varargin_1[i8] = sizeA[i8] + (double)c_sizeA[i8];
    }

    ixstart = 1;
    mtmp = varargin_1[0];
    if (rtIsNaN(varargin_1[0])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix < 3)) {
        ixstart = 2;
        if (!rtIsNaN(varargin_1[1])) {
          mtmp = varargin_1[1];
          exitg1 = true;
        } else {
          ix = 3;
        }
      }
    }

    if ((ixstart < 2) && (varargin_1[1] > mtmp)) {
      mtmp = varargin_1[1];
    }

    ix = (int)pad[0];
    y_size_idx_1 = (short)b_sizeA[0];
    ixstart = (short)b_sizeA[0] - 1;
    for (i8 = 0; i8 <= ixstart; i8++) {
      y_data[i8] = (short)(1 + i8);
    }

    idxDir_size_idx_1 = ((int)pad[0] + y_size_idx_1) + (int)pad[0];
    ixstart = (int)pad[0];
    for (i8 = 0; i8 < ixstart; i8++) {
      idxDir_data[i8] = 1U;
    }

    for (i8 = 0; i8 < y_size_idx_1; i8++) {
      i9 = y_data[i8];
      if (!(i9 >= 0)) {
        i9 = 0;
      }

      idxDir_data[i8 + ix] = (unsigned int)i9;
    }

    ixstart = (int)pad[0];
    for (i8 = 0; i8 < ixstart; i8++) {
      idxDir_data[(i8 + ix) + y_size_idx_1] = (unsigned int)(short)b_sizeA[0];
    }

    ixstart = (short)((short)idxDir_size_idx_1 - 1);
    for (i8 = 0; i8 <= ixstart; i8++) {
      tmp_data[i8] = (short)i8;
    }

    for (i8 = 0; i8 < idxDir_size_idx_1; i8++) {
      b_idxDir_data[i8] = (int)idxDir_data[i8];
    }

    ixstart = (short)((short)idxDir_size_idx_1 - 1) + 1;
    for (i8 = 0; i8 < ixstart; i8++) {
      idxA_data[tmp_data[i8]] = b_idxDir_data[i8];
    }

    ix = (int)pad[1];
    y_size_idx_1 = (short)b_sizeA[1];
    ixstart = (short)b_sizeA[1] - 1;
    for (i8 = 0; i8 <= ixstart; i8++) {
      y_data[i8] = (short)(1 + i8);
    }

    idxDir_size_idx_1 = ((int)pad[1] + y_size_idx_1) + (int)pad[1];
    ixstart = (int)pad[1];
    for (i8 = 0; i8 < ixstart; i8++) {
      idxDir_data[i8] = 1U;
    }

    for (i8 = 0; i8 < y_size_idx_1; i8++) {
      i9 = y_data[i8];
      if (!(i9 >= 0)) {
        i9 = 0;
      }

      idxDir_data[i8 + ix] = (unsigned int)i9;
    }

    ixstart = (int)pad[1];
    for (i8 = 0; i8 < ixstart; i8++) {
      idxDir_data[(i8 + ix) + y_size_idx_1] = (unsigned int)(short)b_sizeA[1];
    }

    ixstart = (short)((short)idxDir_size_idx_1 - 1);
    for (i8 = 0; i8 <= ixstart; i8++) {
      b_tmp_data[i8] = (short)i8;
    }

    for (i8 = 0; i8 < idxDir_size_idx_1; i8++) {
      c_idxDir_data[i8] = (int)idxDir_data[i8];
    }

    ixstart = (short)((short)idxDir_size_idx_1 - 1) + 1;
    for (i8 = 0; i8 < ixstart; i8++) {
      idxA_data[b_tmp_data[i8] + (int)mtmp] = c_idxDir_data[i8];
    }

    for (i8 = 0; i8 < 2; i8++) {
      b_sizeA[i8] = (double)a_tmp->size[i8] + 2.0 * pad[i8];
    }

    i8 = a->size[0] * a->size[1];
    a->size[0] = (int)b_sizeA[0];
    a->size[1] = (int)b_sizeA[1];
    emxEnsureCapacity((emxArray__common *)a, i8, sizeof(float));
    i8 = a->size[1];
    for (ixstart = 0; ixstart < i8; ixstart++) {
      i9 = a->size[0];
      for (ix = 0; ix < i9; ix++) {
        a->data[ix + a->size[0] * ixstart] = a_tmp->data[(idxA_data[ix] +
          a_tmp->size[0] * (idxA_data[ixstart + (int)mtmp] - 1)) - 1];
      }
    }
  }
}

//
// File trailer for imfilter.cpp
//
// [EOF]
//
