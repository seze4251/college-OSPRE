//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: chcenters.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "chcenters.h"
#include "analyzeImage_emxutil.h"
#include "sort1.h"
#include "round.h"
#include "regionprops.h"
#include "imregionalmax.h"
#include "imhmax.h"
#include "eps.h"
#include "medfilt2.h"
#include "all.h"

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
// Arguments    : const emxArray_creal_T *varargin_1
//                double varargin_2
//                emxArray_real_T *centers
//                emxArray_real_T *metric
// Return Type  : void
//
void chcenters(const emxArray_creal_T *varargin_1, double varargin_2,
               emxArray_real_T *centers, emxArray_real_T *metric)
{
  int i27;
  emxArray_real_T *accumMatrixRe;
  short b_varargin_1[2];
  int n;
  int k;
  emxArray_boolean_T *b_accumMatrixRe;
  double c_accumMatrixRe;
  int loop_ub;
  boolean_T flat;
  emxArray_real_T *Hd;
  emxArray_real_T *b_Hd;
  emxArray_boolean_T *bw;
  emxArray_struct_T *s;
  int idx;
  int i28;
  emxArray_real_T *x;
  emxArray_real_T *b_x;
  int b_idx;
  emxArray_real_T *c_varargin_1;
  emxArray_real_T *b_varargin_2;
  emxArray_real_T *c_x;
  emxArray_int32_T *b_sortIdx;
  emxArray_int32_T *iidx;
  emxArray_real_T *b_centers;
  i27 = centers->size[0] * centers->size[1];
  centers->size[0] = 0;
  centers->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)centers, i27, sizeof(double));
  i27 = metric->size[0] * metric->size[1];
  metric->size[0] = 0;
  metric->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)metric, i27, sizeof(double));
  for (i27 = 0; i27 < 2; i27++) {
    b_varargin_1[i27] = (short)varargin_1->size[i27];
  }

  emxInit_real_T(&accumMatrixRe, 2);
  i27 = accumMatrixRe->size[0] * accumMatrixRe->size[1];
  accumMatrixRe->size[0] = b_varargin_1[0];
  accumMatrixRe->size[1] = b_varargin_1[1];
  emxEnsureCapacity((emxArray__common *)accumMatrixRe, i27, sizeof(double));
  n = varargin_1->size[0] * varargin_1->size[1];
  for (k = 0; k + 1 <= n; k++) {
    accumMatrixRe->data[k] = rt_hypotd_snf(varargin_1->data[k].re,
      varargin_1->data[k].im);
  }

  emxInit_boolean_T1(&b_accumMatrixRe, 1);
  c_accumMatrixRe = accumMatrixRe->data[0];
  i27 = b_accumMatrixRe->size[0];
  b_accumMatrixRe->size[0] = accumMatrixRe->size[0] * accumMatrixRe->size[1];
  emxEnsureCapacity((emxArray__common *)b_accumMatrixRe, i27, sizeof(boolean_T));
  loop_ub = accumMatrixRe->size[0] * accumMatrixRe->size[1];
  for (i27 = 0; i27 < loop_ub; i27++) {
    b_accumMatrixRe->data[i27] = (accumMatrixRe->data[i27] == c_accumMatrixRe);
  }

  flat = all(b_accumMatrixRe);
  emxFree_boolean_T(&b_accumMatrixRe);
  if (!flat) {
    for (i27 = 0; i27 < 2; i27++) {
      b_varargin_1[i27] = (short)accumMatrixRe->size[i27];
    }

    n = b_varargin_1[0];
    if (b_varargin_1[1] < b_varargin_1[0]) {
      n = b_varargin_1[1];
    }

    emxInit_real_T(&Hd, 2);
    if (n > 5) {
      medfilt2(accumMatrixRe, Hd);
    } else {
      i27 = Hd->size[0] * Hd->size[1];
      Hd->size[0] = accumMatrixRe->size[0];
      Hd->size[1] = accumMatrixRe->size[1];
      emxEnsureCapacity((emxArray__common *)Hd, i27, sizeof(double));
      loop_ub = accumMatrixRe->size[0] * accumMatrixRe->size[1];
      for (i27 = 0; i27 < loop_ub; i27++) {
        Hd->data[i27] = accumMatrixRe->data[i27];
      }
    }

    c_accumMatrixRe = varargin_2 - eps(varargin_2);
    emxInit_real_T(&b_Hd, 2);
    i27 = b_Hd->size[0] * b_Hd->size[1];
    b_Hd->size[0] = Hd->size[0];
    b_Hd->size[1] = Hd->size[1];
    emxEnsureCapacity((emxArray__common *)b_Hd, i27, sizeof(double));
    loop_ub = Hd->size[0] * Hd->size[1];
    for (i27 = 0; i27 < loop_ub; i27++) {
      b_Hd->data[i27] = Hd->data[i27];
    }

    emxInit_boolean_T(&bw, 2);
    emxInit_struct_T(&s, 1);
    if (!(c_accumMatrixRe > 0.0)) {
      c_accumMatrixRe = 0.0;
    }

    imhmax(b_Hd, c_accumMatrixRe, Hd);
    imregionalmax(Hd, bw);
    regionprops(bw, accumMatrixRe, s);
    emxFree_real_T(&b_Hd);
    emxFree_boolean_T(&bw);
    if (!(s->size[0] == 0)) {
      i27 = centers->size[0] * centers->size[1];
      centers->size[0] = s->size[0];
      centers->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)centers, i27, sizeof(double));
      for (idx = 0; idx < s->size[0]; idx++) {
        for (i27 = 0; i27 < 2; i27++) {
          centers->data[idx + centers->size[0] * i27] = s->data[idx].
            WeightedCentroid[i27];
        }
      }

      i27 = centers->size[0];
      i28 = (int)((1.0 + (-1.0 - (double)centers->size[0])) / -1.0);
      idx = 0;
      emxInit_real_T(&x, 2);
      emxInit_real_T(&b_x, 2);
      while (idx <= i28 - 1) {
        b_idx = i27 - idx;
        if (rtIsNaN(centers->data[b_idx - 1]) || rtIsNaN(centers->data[(b_idx +
              centers->size[0]) - 1])) {
          k = x->size[0] * x->size[1];
          x->size[0] = centers->size[0];
          x->size[1] = centers->size[1];
          emxEnsureCapacity((emxArray__common *)x, k, sizeof(double));
          loop_ub = centers->size[0] * centers->size[1];
          for (k = 0; k < loop_ub; k++) {
            x->data[k] = centers->data[k];
          }

          for (n = 0; n < 2; n++) {
            for (k = b_idx; k < centers->size[0]; k++) {
              x->data[(k + x->size[0] * n) - 1] = x->data[k + x->size[0] * n];
            }
          }

          if (1 > centers->size[0] - 1) {
            loop_ub = 0;
          } else {
            loop_ub = centers->size[0] - 1;
          }

          k = b_x->size[0] * b_x->size[1];
          b_x->size[0] = loop_ub;
          b_x->size[1] = 2;
          emxEnsureCapacity((emxArray__common *)b_x, k, sizeof(double));
          for (k = 0; k < 2; k++) {
            for (n = 0; n < loop_ub; n++) {
              b_x->data[n + b_x->size[0] * k] = x->data[n + x->size[0] * k];
            }
          }

          k = x->size[0] * x->size[1];
          x->size[0] = b_x->size[0];
          x->size[1] = 2;
          emxEnsureCapacity((emxArray__common *)x, k, sizeof(double));
          for (k = 0; k < 2; k++) {
            loop_ub = b_x->size[0];
            for (n = 0; n < loop_ub; n++) {
              x->data[n + x->size[0] * k] = b_x->data[n + b_x->size[0] * k];
            }
          }

          k = centers->size[0] * centers->size[1];
          centers->size[0] = x->size[0];
          centers->size[1] = 2;
          emxEnsureCapacity((emxArray__common *)centers, k, sizeof(double));
          loop_ub = x->size[0] * x->size[1];
          for (k = 0; k < loop_ub; k++) {
            centers->data[k] = x->data[k];
          }
        }

        idx++;
      }

      emxFree_real_T(&b_x);
      emxFree_real_T(&x);
      if (!(centers->size[0] == 0)) {
        emxInit_real_T1(&c_varargin_1, 1);
        loop_ub = centers->size[0];
        i27 = c_varargin_1->size[0];
        c_varargin_1->size[0] = loop_ub;
        emxEnsureCapacity((emxArray__common *)c_varargin_1, i27, sizeof(double));
        for (i27 = 0; i27 < loop_ub; i27++) {
          c_varargin_1->data[i27] = centers->data[i27 + centers->size[0]];
        }

        emxInit_real_T1(&b_varargin_2, 1);
        b_round(c_varargin_1);
        loop_ub = centers->size[0];
        i27 = b_varargin_2->size[0];
        b_varargin_2->size[0] = loop_ub;
        emxEnsureCapacity((emxArray__common *)b_varargin_2, i27, sizeof(double));
        for (i27 = 0; i27 < loop_ub; i27++) {
          b_varargin_2->data[i27] = centers->data[i27];
        }

        b_round(b_varargin_2);
        for (i27 = 0; i27 < 2; i27++) {
          b_varargin_1[i27] = (short)Hd->size[i27];
        }

        i27 = c_varargin_1->size[0];
        emxEnsureCapacity((emxArray__common *)c_varargin_1, i27, sizeof(double));
        loop_ub = c_varargin_1->size[0];
        for (i27 = 0; i27 < loop_ub; i27++) {
          c_varargin_1->data[i27] = (int)c_varargin_1->data[i27] + b_varargin_1
            [0] * ((int)b_varargin_2->data[i27] - 1);
        }

        emxFree_real_T(&b_varargin_2);
        emxInit_real_T(&c_x, 2);
        i27 = c_x->size[0] * c_x->size[1];
        c_x->size[0] = c_varargin_1->size[0];
        c_x->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)c_x, i27, sizeof(double));
        loop_ub = c_varargin_1->size[0];
        for (i27 = 0; i27 < loop_ub; i27++) {
          c_x->data[i27] = Hd->data[(int)c_varargin_1->data[i27] - 1];
        }

        emxFree_real_T(&c_varargin_1);
        emxInit_int32_T1(&b_sortIdx, 2);
        emxInit_int32_T1(&iidx, 2);
        sort(c_x, iidx);
        i27 = b_sortIdx->size[0] * b_sortIdx->size[1];
        b_sortIdx->size[0] = iidx->size[0];
        b_sortIdx->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)b_sortIdx, i27, sizeof(int));
        loop_ub = iidx->size[0] * iidx->size[1];
        for (i27 = 0; i27 < loop_ub; i27++) {
          b_sortIdx->data[i27] = iidx->data[i27];
        }

        emxFree_int32_T(&iidx);
        i27 = metric->size[0] * metric->size[1];
        metric->size[0] = c_x->size[0];
        metric->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)metric, i27, sizeof(double));
        loop_ub = c_x->size[0] * c_x->size[1];
        for (i27 = 0; i27 < loop_ub; i27++) {
          metric->data[i27] = c_x->data[i27];
        }

        emxFree_real_T(&c_x);
        emxInit_real_T(&b_centers, 2);
        n = b_sortIdx->size[0];
        i27 = b_centers->size[0] * b_centers->size[1];
        b_centers->size[0] = n;
        b_centers->size[1] = 2;
        emxEnsureCapacity((emxArray__common *)b_centers, i27, sizeof(double));
        for (i27 = 0; i27 < 2; i27++) {
          for (i28 = 0; i28 < n; i28++) {
            b_centers->data[i28 + b_centers->size[0] * i27] = centers->data
              [(b_sortIdx->data[i28] + centers->size[0] * i27) - 1];
          }
        }

        emxFree_int32_T(&b_sortIdx);
        i27 = centers->size[0] * centers->size[1];
        centers->size[0] = b_centers->size[0];
        centers->size[1] = b_centers->size[1];
        emxEnsureCapacity((emxArray__common *)centers, i27, sizeof(double));
        loop_ub = b_centers->size[1];
        for (i27 = 0; i27 < loop_ub; i27++) {
          n = b_centers->size[0];
          for (i28 = 0; i28 < n; i28++) {
            centers->data[i28 + centers->size[0] * i27] = b_centers->data[i28 +
              b_centers->size[0] * i27];
          }
        }

        emxFree_real_T(&b_centers);
      }
    }

    emxFree_struct_T(&s);
    emxFree_real_T(&Hd);
  }

  emxFree_real_T(&accumMatrixRe);
}

//
// File trailer for chcenters.cpp
//
// [EOF]
//
