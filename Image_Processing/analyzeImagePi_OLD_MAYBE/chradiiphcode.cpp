//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: chradiiphcode.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 14-Feb-2017 14:22:46
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "chradiiphcode.h"
#include "analyzeImage_emxutil.h"
#include "log.h"
#include "round1.h"

// Function Declarations
static double rt_atan2d_snf(double u0, double u1);

// Function Definitions

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  int b_u0;
  int b_u1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }

    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }

    y = atan2((double)b_u0, (double)b_u1);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

//
// Arguments    : const emxArray_real_T *varargin_1
//                const emxArray_creal_T *varargin_2
//                const double varargin_3_data[]
//                const int varargin_3_size[2]
//                emxArray_real_T *r_estimated
// Return Type  : void
//
void chradiiphcode(const emxArray_real_T *varargin_1, const emxArray_creal_T
                   *varargin_2, const double varargin_3_data[], const int
                   varargin_3_size[2], emxArray_real_T *r_estimated)
{
  emxArray_real_T *b_varargin_1;
  int loop_ub;
  int i21;
  emxArray_real_T *cenPhase;
  short siz[2];
  emxArray_creal_T *x;
  emxArray_real_T *r7;
  int lnR_size_idx_1;
  double lnR_data[2];
  double b;
  emxInit_real_T1(&b_varargin_1, 1);
  loop_ub = varargin_1->size[0];
  i21 = b_varargin_1->size[0];
  b_varargin_1->size[0] = loop_ub;
  emxEnsureCapacity((emxArray__common *)b_varargin_1, i21, (int)sizeof(double));
  for (i21 = 0; i21 < loop_ub; i21++) {
    b_varargin_1->data[i21] = varargin_1->data[i21 + varargin_1->size[0]];
  }

  emxInit_real_T1(&cenPhase, 1);
  b_round(b_varargin_1);
  loop_ub = varargin_1->size[0];
  i21 = cenPhase->size[0];
  cenPhase->size[0] = loop_ub;
  emxEnsureCapacity((emxArray__common *)cenPhase, i21, (int)sizeof(double));
  for (i21 = 0; i21 < loop_ub; i21++) {
    cenPhase->data[i21] = varargin_1->data[i21];
  }

  b_round(cenPhase);
  for (i21 = 0; i21 < 2; i21++) {
    siz[i21] = (short)varargin_2->size[i21];
  }

  i21 = b_varargin_1->size[0];
  emxEnsureCapacity((emxArray__common *)b_varargin_1, i21, (int)sizeof(double));
  loop_ub = b_varargin_1->size[0];
  for (i21 = 0; i21 < loop_ub; i21++) {
    b_varargin_1->data[i21] = (int)b_varargin_1->data[i21] + siz[0] * ((int)
      cenPhase->data[i21] - 1);
  }

  emxInit_creal_T1(&x, 1);
  i21 = x->size[0];
  x->size[0] = b_varargin_1->size[0];
  emxEnsureCapacity((emxArray__common *)x, i21, (int)sizeof(creal_T));
  loop_ub = b_varargin_1->size[0];
  for (i21 = 0; i21 < loop_ub; i21++) {
    x->data[i21] = varargin_2->data[(int)b_varargin_1->data[i21] - 1];
  }

  loop_ub = b_varargin_1->size[0];
  i21 = cenPhase->size[0];
  cenPhase->size[0] = loop_ub;
  emxEnsureCapacity((emxArray__common *)cenPhase, i21, (int)sizeof(double));
  for (loop_ub = 0; loop_ub + 1 <= b_varargin_1->size[0]; loop_ub++) {
    cenPhase->data[loop_ub] = rt_atan2d_snf(x->data[loop_ub].im, x->data[loop_ub]
      .re);
  }

  emxFree_creal_T(&x);
  emxFree_real_T(&b_varargin_1);
  emxInit_real_T(&r7, 2);
  i21 = r7->size[0] * r7->size[1];
  r7->size[0] = 1;
  r7->size[1] = varargin_3_size[1];
  emxEnsureCapacity((emxArray__common *)r7, i21, (int)sizeof(double));
  loop_ub = varargin_3_size[0] * varargin_3_size[1];
  for (i21 = 0; i21 < loop_ub; i21++) {
    r7->data[i21] = varargin_3_data[i21];
  }

  b_log(r7);
  lnR_size_idx_1 = r7->size[1];
  loop_ub = r7->size[0] * r7->size[1];
  for (i21 = 0; i21 < loop_ub; i21++) {
    lnR_data[i21] = r7->data[i21];
  }

  emxFree_real_T(&r7);
  b = lnR_data[lnR_size_idx_1 - 1] - lnR_data[0];
  i21 = cenPhase->size[0];
  emxEnsureCapacity((emxArray__common *)cenPhase, i21, (int)sizeof(double));
  loop_ub = cenPhase->size[0];
  for (i21 = 0; i21 < loop_ub; i21++) {
    cenPhase->data[i21] = (cenPhase->data[i21] + 3.1415926535897931) /
      6.2831853071795862 * b + lnR_data[0];
  }

  i21 = r_estimated->size[0];
  r_estimated->size[0] = cenPhase->size[0];
  emxEnsureCapacity((emxArray__common *)r_estimated, i21, (int)sizeof(double));
  loop_ub = cenPhase->size[0];
  for (i21 = 0; i21 < loop_ub; i21++) {
    r_estimated->data[i21] = cenPhase->data[i21];
  }

  for (loop_ub = 0; loop_ub + 1 <= cenPhase->size[0]; loop_ub++) {
    r_estimated->data[loop_ub] = std::exp(r_estimated->data[loop_ub]);
  }

  emxFree_real_T(&cenPhase);
}

//
// File trailer for chradiiphcode.cpp
//
// [EOF]
//
