//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: chradiiphcode.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "chradiiphcode.h"
#include "analyzeImage_emxutil.h"
#include "log.h"
#include "round.h"

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
  int i31;
  emxArray_real_T *b_varargin_2;
  short siz[2];
  emxArray_creal_T *x;
  emxArray_real_T *r11;
  int nx;
  double lnR_data[2];
  double b;
  emxInit_real_T1(&b_varargin_1, 1);
  loop_ub = varargin_1->size[0];
  i31 = b_varargin_1->size[0];
  b_varargin_1->size[0] = loop_ub;
  emxEnsureCapacity((emxArray__common *)b_varargin_1, i31, sizeof(double));
  for (i31 = 0; i31 < loop_ub; i31++) {
    b_varargin_1->data[i31] = varargin_1->data[i31 + varargin_1->size[0]];
  }

  emxInit_real_T1(&b_varargin_2, 1);
  b_round(b_varargin_1);
  loop_ub = varargin_1->size[0];
  i31 = b_varargin_2->size[0];
  b_varargin_2->size[0] = loop_ub;
  emxEnsureCapacity((emxArray__common *)b_varargin_2, i31, sizeof(double));
  for (i31 = 0; i31 < loop_ub; i31++) {
    b_varargin_2->data[i31] = varargin_1->data[i31];
  }

  b_round(b_varargin_2);
  for (i31 = 0; i31 < 2; i31++) {
    siz[i31] = (short)varargin_2->size[i31];
  }

  i31 = b_varargin_1->size[0];
  emxEnsureCapacity((emxArray__common *)b_varargin_1, i31, sizeof(double));
  loop_ub = b_varargin_1->size[0];
  for (i31 = 0; i31 < loop_ub; i31++) {
    b_varargin_1->data[i31] = (int)b_varargin_1->data[i31] + siz[0] * ((int)
      b_varargin_2->data[i31] - 1);
  }

  emxFree_real_T(&b_varargin_2);
  emxInit_creal_T1(&x, 1);
  i31 = x->size[0];
  x->size[0] = b_varargin_1->size[0];
  emxEnsureCapacity((emxArray__common *)x, i31, sizeof(creal_T));
  loop_ub = b_varargin_1->size[0];
  for (i31 = 0; i31 < loop_ub; i31++) {
    x->data[i31] = varargin_2->data[(int)b_varargin_1->data[i31] - 1];
  }

  loop_ub = b_varargin_1->size[0];
  i31 = r_estimated->size[0];
  r_estimated->size[0] = loop_ub;
  emxEnsureCapacity((emxArray__common *)r_estimated, i31, sizeof(double));
  for (loop_ub = 0; loop_ub + 1 <= b_varargin_1->size[0]; loop_ub++) {
    r_estimated->data[loop_ub] = rt_atan2d_snf(x->data[loop_ub].im, x->
      data[loop_ub].re);
  }

  emxFree_creal_T(&x);
  emxFree_real_T(&b_varargin_1);
  emxInit_real_T(&r11, 2);
  i31 = r11->size[0] * r11->size[1];
  r11->size[0] = 1;
  r11->size[1] = varargin_3_size[1];
  emxEnsureCapacity((emxArray__common *)r11, i31, sizeof(double));
  loop_ub = varargin_3_size[0] * varargin_3_size[1];
  for (i31 = 0; i31 < loop_ub; i31++) {
    r11->data[i31] = varargin_3_data[i31];
  }

  b_log(r11);
  nx = r11->size[1];
  loop_ub = r11->size[0] * r11->size[1];
  for (i31 = 0; i31 < loop_ub; i31++) {
    lnR_data[i31] = r11->data[i31];
  }

  emxFree_real_T(&r11);
  b = lnR_data[nx - 1] - lnR_data[0];
  i31 = r_estimated->size[0];
  emxEnsureCapacity((emxArray__common *)r_estimated, i31, sizeof(double));
  loop_ub = r_estimated->size[0];
  for (i31 = 0; i31 < loop_ub; i31++) {
    r_estimated->data[i31] = (r_estimated->data[i31] + 3.1415926535897931) /
      6.2831853071795862 * b + lnR_data[0];
  }

  nx = r_estimated->size[0];
  for (loop_ub = 0; loop_ub + 1 <= nx; loop_ub++) {
    r_estimated->data[loop_ub] = std::exp(r_estimated->data[loop_ub]);
  }
}

//
// File trailer for chradiiphcode.cpp
//
// [EOF]
//
