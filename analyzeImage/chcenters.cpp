//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: chcenters.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 25-Jan-2017 16:02:21
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "chcenters.h"
#include "analyzeImage_emxutil.h"
#include "sort1.h"
#include "round1.h"
#include "regionprops.h"
#include "imregionalmax.h"
#include "imhmax.h"
#include "medfilt2.h"

// Function Declarations
static double rt_hypotd_snf(double u0, double u1);

// Function Definitions

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_hypotd_snf(double u0, double u1)
{
  double y;
  double a;
  double b;
  a = std::abs(u0);
  b = std::abs(u1);
  if (a < b) {
    a /= b;
    y = b * std::sqrt(a * a + 1.0);
  } else if (a > b) {
    b /= a;
    y = a * std::sqrt(b * b + 1.0);
  } else if (rtIsNaN(b)) {
    y = b;
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

//
// Arguments    : const creal_T varargin_1[809600]
//                double varargin_2
//                emxArray_real_T *centers
//                emxArray_real_T *metric
// Return Type  : void
//
void chcenters(const creal_T varargin_1[809600], double varargin_2,
               emxArray_real_T *centers, emxArray_real_T *metric)
{
  int i11;
  static double accumMatrixRe[809600];
  int k;
  static boolean_T bw[809600];
  boolean_T flat;
  boolean_T exitg1;
  static double Hd[809600];
  double absxk;
  int exponent;
  static double b_Hd[809600];
  emxArray_struct_T *s;
  double b_absxk;
  int idx;
  int i12;
  emxArray_real_T *x;
  emxArray_real_T *b_x;
  int b_idx;
  emxArray_real_T *b_varargin_1;
  int loop_ub;
  emxArray_real_T *b_varargin_2;
  emxArray_int32_T *c_idx;
  emxArray_real_T *b_metric;
  emxArray_int32_T *b_sortIdx;
  emxArray_int32_T *iidx;
  emxArray_real_T *b_centers;
  i11 = centers->size[0] * centers->size[1];
  centers->size[0] = 0;
  centers->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)centers, i11, (int)sizeof(double));
  i11 = metric->size[0] * metric->size[1];
  metric->size[0] = 0;
  metric->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)metric, i11, (int)sizeof(double));
  for (k = 0; k < 809600; k++) {
    accumMatrixRe[k] = rt_hypotd_snf(varargin_1[k].re, varargin_1[k].im);
  }

  for (i11 = 0; i11 < 809600; i11++) {
    bw[i11] = (accumMatrixRe[i11] == accumMatrixRe[0]);
  }

  flat = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 809600)) {
    if (!bw[k]) {
      flat = false;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (!flat) {
    medfilt2(accumMatrixRe, Hd);
    absxk = std::abs(varargin_2);
    if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk))) {
      if (absxk <= 2.2250738585072014E-308) {
        absxk = 4.94065645841247E-324;
      } else {
        frexp(absxk, &exponent);
        absxk = std::ldexp(1.0, exponent - 53);
      }
    } else {
      absxk = rtNaN;
    }

    absxk = varargin_2 - absxk;
    memcpy(&b_Hd[0], &Hd[0], 809600U * sizeof(double));
    emxInit_struct_T(&s, 1);
    if (absxk >= 0.0) {
      b_absxk = absxk;
    } else {
      b_absxk = 0.0;
    }

    imhmax(b_Hd, b_absxk, Hd);
    imregionalmax(Hd, bw);
    regionprops(bw, accumMatrixRe, s);
    if (!(s->size[0] == 0)) {
      i11 = centers->size[0] * centers->size[1];
      centers->size[0] = s->size[0];
      centers->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)centers, i11, (int)sizeof(double));
      for (idx = 0; idx < s->size[0]; idx++) {
        for (i11 = 0; i11 < 2; i11++) {
          centers->data[idx + centers->size[0] * i11] = s->data[idx].
            WeightedCentroid[i11];
        }
      }

      i11 = centers->size[0];
      i12 = (int)((1.0 + (-1.0 - (double)centers->size[0])) / -1.0);
      idx = 0;
      emxInit_real_T(&x, 2);
      emxInit_real_T(&b_x, 2);
      while (idx <= i12 - 1) {
        b_idx = i11 - idx;
        if (rtIsNaN(centers->data[b_idx - 1]) || rtIsNaN(centers->data[(b_idx +
              centers->size[0]) - 1])) {
          exponent = x->size[0] * x->size[1];
          x->size[0] = centers->size[0];
          x->size[1] = centers->size[1];
          emxEnsureCapacity((emxArray__common *)x, exponent, (int)sizeof(double));
          loop_ub = centers->size[0] * centers->size[1];
          for (exponent = 0; exponent < loop_ub; exponent++) {
            x->data[exponent] = centers->data[exponent];
          }

          for (k = 0; k < 2; k++) {
            for (exponent = b_idx; exponent < centers->size[0]; exponent++) {
              x->data[(exponent + x->size[0] * k) - 1] = x->data[exponent +
                x->size[0] * k];
            }
          }

          if (1 > centers->size[0] - 1) {
            loop_ub = 0;
          } else {
            loop_ub = centers->size[0] - 1;
          }

          exponent = b_x->size[0] * b_x->size[1];
          b_x->size[0] = loop_ub;
          b_x->size[1] = 2;
          emxEnsureCapacity((emxArray__common *)b_x, exponent, (int)sizeof
                            (double));
          for (exponent = 0; exponent < 2; exponent++) {
            for (k = 0; k < loop_ub; k++) {
              b_x->data[k + b_x->size[0] * exponent] = x->data[k + x->size[0] *
                exponent];
            }
          }

          exponent = x->size[0] * x->size[1];
          x->size[0] = b_x->size[0];
          x->size[1] = 2;
          emxEnsureCapacity((emxArray__common *)x, exponent, (int)sizeof(double));
          for (exponent = 0; exponent < 2; exponent++) {
            loop_ub = b_x->size[0];
            for (k = 0; k < loop_ub; k++) {
              x->data[k + x->size[0] * exponent] = b_x->data[k + b_x->size[0] *
                exponent];
            }
          }

          exponent = centers->size[0] * centers->size[1];
          centers->size[0] = x->size[0];
          centers->size[1] = 2;
          emxEnsureCapacity((emxArray__common *)centers, exponent, (int)sizeof
                            (double));
          loop_ub = x->size[0] * x->size[1];
          for (exponent = 0; exponent < loop_ub; exponent++) {
            centers->data[exponent] = x->data[exponent];
          }
        }

        idx++;
      }

      emxFree_real_T(&b_x);
      emxFree_real_T(&x);
      if (!(centers->size[0] == 0)) {
        emxInit_real_T1(&b_varargin_1, 1);
        loop_ub = centers->size[0];
        i11 = b_varargin_1->size[0];
        b_varargin_1->size[0] = loop_ub;
        emxEnsureCapacity((emxArray__common *)b_varargin_1, i11, (int)sizeof
                          (double));
        for (i11 = 0; i11 < loop_ub; i11++) {
          b_varargin_1->data[i11] = centers->data[i11 + centers->size[0]];
        }

        emxInit_real_T1(&b_varargin_2, 1);
        b_round(b_varargin_1);
        loop_ub = centers->size[0];
        i11 = b_varargin_2->size[0];
        b_varargin_2->size[0] = loop_ub;
        emxEnsureCapacity((emxArray__common *)b_varargin_2, i11, (int)sizeof
                          (double));
        for (i11 = 0; i11 < loop_ub; i11++) {
          b_varargin_2->data[i11] = centers->data[i11];
        }

        emxInit_int32_T(&c_idx, 1);
        b_round(b_varargin_2);
        i11 = c_idx->size[0];
        c_idx->size[0] = b_varargin_1->size[0];
        emxEnsureCapacity((emxArray__common *)c_idx, i11, (int)sizeof(int));
        loop_ub = b_varargin_1->size[0];
        for (i11 = 0; i11 < loop_ub; i11++) {
          c_idx->data[i11] = (int)b_varargin_1->data[i11] + 736 * ((int)
            b_varargin_2->data[i11] - 1);
        }

        emxFree_real_T(&b_varargin_2);
        i11 = b_varargin_1->size[0];
        b_varargin_1->size[0] = c_idx->size[0];
        emxEnsureCapacity((emxArray__common *)b_varargin_1, i11, (int)sizeof
                          (double));
        loop_ub = c_idx->size[0];
        for (i11 = 0; i11 < loop_ub; i11++) {
          b_varargin_1->data[i11] = Hd[c_idx->data[i11] - 1];
        }

        emxInit_real_T(&b_metric, 2);
        i11 = b_metric->size[0] * b_metric->size[1];
        b_metric->size[0] = c_idx->size[0];
        b_metric->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)b_metric, i11, (int)sizeof(double));
        loop_ub = c_idx->size[0];
        emxFree_int32_T(&c_idx);
        for (i11 = 0; i11 < loop_ub; i11++) {
          b_metric->data[i11] = b_varargin_1->data[i11];
        }

        emxFree_real_T(&b_varargin_1);
        emxInit_int32_T1(&b_sortIdx, 2);
        emxInit_int32_T1(&iidx, 2);
        sort(b_metric, iidx);
        i11 = b_sortIdx->size[0] * b_sortIdx->size[1];
        b_sortIdx->size[0] = iidx->size[0];
        b_sortIdx->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)b_sortIdx, i11, (int)sizeof(int));
        loop_ub = iidx->size[0] * iidx->size[1];
        for (i11 = 0; i11 < loop_ub; i11++) {
          b_sortIdx->data[i11] = iidx->data[i11];
        }

        emxFree_int32_T(&iidx);
        i11 = metric->size[0] * metric->size[1];
        metric->size[0] = b_metric->size[0];
        metric->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)metric, i11, (int)sizeof(double));
        loop_ub = b_metric->size[0] * b_metric->size[1];
        for (i11 = 0; i11 < loop_ub; i11++) {
          metric->data[i11] = b_metric->data[i11];
        }

        emxFree_real_T(&b_metric);
        emxInit_real_T(&b_centers, 2);
        k = b_sortIdx->size[0];
        i11 = b_centers->size[0] * b_centers->size[1];
        b_centers->size[0] = k;
        b_centers->size[1] = 2;
        emxEnsureCapacity((emxArray__common *)b_centers, i11, (int)sizeof(double));
        for (i11 = 0; i11 < 2; i11++) {
          for (i12 = 0; i12 < k; i12++) {
            b_centers->data[i12 + b_centers->size[0] * i11] = centers->data
              [(b_sortIdx->data[i12] + centers->size[0] * i11) - 1];
          }
        }

        emxFree_int32_T(&b_sortIdx);
        i11 = centers->size[0] * centers->size[1];
        centers->size[0] = b_centers->size[0];
        centers->size[1] = b_centers->size[1];
        emxEnsureCapacity((emxArray__common *)centers, i11, (int)sizeof(double));
        loop_ub = b_centers->size[1];
        for (i11 = 0; i11 < loop_ub; i11++) {
          k = b_centers->size[0];
          for (i12 = 0; i12 < k; i12++) {
            centers->data[i12 + centers->size[0] * i11] = b_centers->data[i12 +
              b_centers->size[0] * i11];
          }
        }

        emxFree_real_T(&b_centers);
      }
    }

    emxFree_struct_T(&s);
  }
}

//
// File trailer for chcenters.cpp
//
// [EOF]
//
