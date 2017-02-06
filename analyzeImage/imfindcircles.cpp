//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: imfindcircles.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 25-Jan-2017 16:02:21
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "imfindcircles.h"
#include "analyzeImage_emxutil.h"
#include "log.h"
#include "round1.h"
#include "chcenters.h"
#include "chaccum.h"

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
// Arguments    : const boolean_T varargin_1[809600]
//                const double varargin_2[2]
//                double varargin_4
//                emxArray_real_T *centers
//                emxArray_real_T *r_estimated
// Return Type  : void
//
void imfindcircles(const boolean_T varargin_1[809600], const double varargin_2[2],
                   double varargin_4, emxArray_real_T *centers, emxArray_real_T *
                   r_estimated)
{
  int lnR_size[2];
  double lnR_data[2];
  int i2;
  static creal_T accumMatrix[809600];
  static float gradientImg[809600];
  boolean_T y;
  int k;
  boolean_T exitg2;
  emxArray_real_T *b_centers;
  boolean_T b0;
  emxArray_real_T *metric;
  emxArray_boolean_T *x;
  emxArray_int32_T *ii;
  int nx;
  int idx;
  boolean_T exitg1;
  boolean_T guard1 = false;
  emxArray_real_T *idx2Keep;
  emxArray_real_T *cenPhase;
  emxArray_real_T *b_varargin_2;
  emxArray_creal_T *b_x;
  emxArray_real_T *r0;
  double b;
  if (varargin_2[0] == varargin_2[1]) {
    lnR_size[0] = 1;
    lnR_size[1] = 1;
    lnR_data[0] = varargin_2[0];
  } else {
    lnR_size[0] = 1;
    lnR_size[1] = 2;
    for (i2 = 0; i2 < 2; i2++) {
      lnR_data[i2] = varargin_2[i2];
    }
  }

  i2 = centers->size[0] * centers->size[1];
  centers->size[0] = 0;
  centers->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)centers, i2, (int)sizeof(double));
  i2 = r_estimated->size[0] * r_estimated->size[1];
  r_estimated->size[0] = 0;
  r_estimated->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)r_estimated, i2, (int)sizeof(double));
  chaccum(varargin_1, lnR_data, lnR_size, accumMatrix, gradientImg);
  y = false;
  k = 0;
  exitg2 = false;
  while ((!exitg2) && (k < 809600)) {
    if (((accumMatrix[k].re == 0.0) && (accumMatrix[k].im == 0.0)) || (rtIsNaN
         (accumMatrix[k].re) || rtIsNaN(accumMatrix[k].im))) {
      b0 = true;
    } else {
      b0 = false;
    }

    if (!b0) {
      y = true;
      exitg2 = true;
    } else {
      k++;
    }
  }

  if (y) {
    emxInit_real_T(&b_centers, 2);
    emxInit_real_T(&metric, 2);
    chcenters(accumMatrix, 1.0 - varargin_4, b_centers, metric);
    i2 = centers->size[0] * centers->size[1];
    centers->size[0] = b_centers->size[0];
    centers->size[1] = b_centers->size[1];
    emxEnsureCapacity((emxArray__common *)centers, i2, (int)sizeof(double));
    k = b_centers->size[0] * b_centers->size[1];
    for (i2 = 0; i2 < k; i2++) {
      centers->data[i2] = b_centers->data[i2];
    }

    if (!((b_centers->size[0] == 0) || (b_centers->size[1] == 0))) {
      emxInit_boolean_T(&x, 2);
      i2 = x->size[0] * x->size[1];
      x->size[0] = metric->size[0];
      x->size[1] = metric->size[1];
      emxEnsureCapacity((emxArray__common *)x, i2, (int)sizeof(boolean_T));
      k = metric->size[0] * metric->size[1];
      for (i2 = 0; i2 < k; i2++) {
        x->data[i2] = (metric->data[i2] >= 1.0 - varargin_4);
      }

      emxInit_int32_T(&ii, 1);
      nx = x->size[0] * x->size[1];
      idx = 0;
      i2 = ii->size[0];
      ii->size[0] = nx;
      emxEnsureCapacity((emxArray__common *)ii, i2, (int)sizeof(int));
      k = 1;
      exitg1 = false;
      while ((!exitg1) && (k <= nx)) {
        guard1 = false;
        if (x->data[k - 1]) {
          idx++;
          ii->data[idx - 1] = k;
          if (idx >= nx) {
            exitg1 = true;
          } else {
            guard1 = true;
          }
        } else {
          guard1 = true;
        }

        if (guard1) {
          k++;
        }
      }

      emxFree_boolean_T(&x);
      if (nx == 1) {
        if (idx == 0) {
          i2 = ii->size[0];
          ii->size[0] = 0;
          emxEnsureCapacity((emxArray__common *)ii, i2, (int)sizeof(int));
        }
      } else {
        i2 = ii->size[0];
        if (1 > idx) {
          ii->size[0] = 0;
        } else {
          ii->size[0] = idx;
        }

        emxEnsureCapacity((emxArray__common *)ii, i2, (int)sizeof(int));
      }

      emxInit_real_T1(&idx2Keep, 1);
      i2 = idx2Keep->size[0];
      idx2Keep->size[0] = ii->size[0];
      emxEnsureCapacity((emxArray__common *)idx2Keep, i2, (int)sizeof(double));
      k = ii->size[0];
      for (i2 = 0; i2 < k; i2++) {
        idx2Keep->data[i2] = ii->data[i2];
      }

      k = b_centers->size[1];
      i2 = centers->size[0] * centers->size[1];
      centers->size[0] = idx2Keep->size[0];
      centers->size[1] = k;
      emxEnsureCapacity((emxArray__common *)centers, i2, (int)sizeof(double));
      for (i2 = 0; i2 < k; i2++) {
        nx = idx2Keep->size[0];
        for (idx = 0; idx < nx; idx++) {
          centers->data[idx + centers->size[0] * i2] = b_centers->data[((int)
            idx2Keep->data[idx] + b_centers->size[0] * i2) - 1];
        }
      }

      if (idx2Keep->size[0] == 0) {
        i2 = centers->size[0] * centers->size[1];
        centers->size[0] = 0;
        centers->size[1] = 0;
        emxEnsureCapacity((emxArray__common *)centers, i2, (int)sizeof(double));
      } else if (lnR_size[1] == 1) {
        nx = idx2Keep->size[0];
        i2 = r_estimated->size[0] * r_estimated->size[1];
        r_estimated->size[0] = nx;
        r_estimated->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)r_estimated, i2, (int)sizeof
                          (double));
        if (!(nx == 0)) {
          nx = idx2Keep->size[0];
          for (k = 1; k <= nx; k++) {
            r_estimated->data[k - 1] = lnR_data[0];
          }
        }
      } else {
        emxInit_real_T1(&cenPhase, 1);
        k = idx2Keep->size[0];
        i2 = cenPhase->size[0];
        cenPhase->size[0] = k;
        emxEnsureCapacity((emxArray__common *)cenPhase, i2, (int)sizeof(double));
        for (i2 = 0; i2 < k; i2++) {
          cenPhase->data[i2] = centers->data[i2 + centers->size[0]];
        }

        emxInit_real_T1(&b_varargin_2, 1);
        b_round(cenPhase);
        k = idx2Keep->size[0];
        i2 = b_varargin_2->size[0];
        b_varargin_2->size[0] = k;
        emxEnsureCapacity((emxArray__common *)b_varargin_2, i2, (int)sizeof
                          (double));
        for (i2 = 0; i2 < k; i2++) {
          b_varargin_2->data[i2] = centers->data[i2];
        }

        b_round(b_varargin_2);
        i2 = ii->size[0];
        ii->size[0] = cenPhase->size[0];
        emxEnsureCapacity((emxArray__common *)ii, i2, (int)sizeof(int));
        k = cenPhase->size[0];
        for (i2 = 0; i2 < k; i2++) {
          ii->data[i2] = (int)cenPhase->data[i2] + 736 * ((int)
            b_varargin_2->data[i2] - 1);
        }

        emxFree_real_T(&b_varargin_2);
        emxInit_creal_T(&b_x, 1);
        i2 = b_x->size[0];
        b_x->size[0] = ii->size[0];
        emxEnsureCapacity((emxArray__common *)b_x, i2, (int)sizeof(creal_T));
        k = ii->size[0];
        for (i2 = 0; i2 < k; i2++) {
          b_x->data[i2] = accumMatrix[ii->data[i2] - 1];
        }

        k = ii->size[0];
        i2 = cenPhase->size[0];
        cenPhase->size[0] = k;
        emxEnsureCapacity((emxArray__common *)cenPhase, i2, (int)sizeof(double));
        for (k = 0; k + 1 <= ii->size[0]; k++) {
          cenPhase->data[k] = rt_atan2d_snf(b_x->data[k].im, b_x->data[k].re);
        }

        emxFree_creal_T(&b_x);
        emxInit_real_T(&r0, 2);
        i2 = r0->size[0] * r0->size[1];
        r0->size[0] = 1;
        r0->size[1] = 2;
        emxEnsureCapacity((emxArray__common *)r0, i2, (int)sizeof(double));
        for (i2 = 0; i2 < 2; i2++) {
          r0->data[i2] = lnR_data[i2];
        }

        b_log(r0);
        lnR_size[1] = r0->size[1];
        k = r0->size[0] * r0->size[1];
        for (i2 = 0; i2 < k; i2++) {
          lnR_data[i2] = r0->data[i2];
        }

        emxFree_real_T(&r0);
        b = lnR_data[lnR_size[1] - 1] - lnR_data[0];
        i2 = cenPhase->size[0];
        emxEnsureCapacity((emxArray__common *)cenPhase, i2, (int)sizeof(double));
        k = cenPhase->size[0];
        for (i2 = 0; i2 < k; i2++) {
          cenPhase->data[i2] = (cenPhase->data[i2] + 3.1415926535897931) /
            6.2831853071795862 * b + lnR_data[0];
        }

        i2 = idx2Keep->size[0];
        idx2Keep->size[0] = cenPhase->size[0];
        emxEnsureCapacity((emxArray__common *)idx2Keep, i2, (int)sizeof(double));
        k = cenPhase->size[0];
        for (i2 = 0; i2 < k; i2++) {
          idx2Keep->data[i2] = cenPhase->data[i2];
        }

        for (k = 0; k + 1 <= cenPhase->size[0]; k++) {
          idx2Keep->data[k] = std::exp(idx2Keep->data[k]);
        }

        emxFree_real_T(&cenPhase);
        i2 = r_estimated->size[0] * r_estimated->size[1];
        r_estimated->size[0] = idx2Keep->size[0];
        r_estimated->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)r_estimated, i2, (int)sizeof
                          (double));
        k = idx2Keep->size[0];
        for (i2 = 0; i2 < k; i2++) {
          r_estimated->data[i2] = idx2Keep->data[i2];
        }
      }

      emxFree_int32_T(&ii);
      emxFree_real_T(&idx2Keep);
    }

    emxFree_real_T(&metric);
    emxFree_real_T(&b_centers);
  }
}

//
// File trailer for imfindcircles.cpp
//
// [EOF]
//
