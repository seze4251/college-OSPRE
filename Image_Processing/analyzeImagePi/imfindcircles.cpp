//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: imfindcircles.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "imfindcircles.h"
#include "analyzeImage_emxutil.h"
#include "chradiiphcode.h"
#include "chcenters.h"
#include "chaccum.h"

// Function Definitions

//
// Arguments    : const emxArray_boolean_T *varargin_1
//                const double varargin_2[2]
//                double varargin_4
//                emxArray_real_T *centers
//                emxArray_real_T *r_estimated
// Return Type  : void
//
void imfindcircles(const emxArray_boolean_T *varargin_1, const double
                   varargin_2[2], double varargin_4, emxArray_real_T *centers,
                   emxArray_real_T *r_estimated)
{
  int radiusRange_size[2];
  int i5;
  double radiusRange_data[2];
  emxArray_creal_T *accumMatrix;
  emxArray_real32_T *gradientImg;
  boolean_T y;
  int ix;
  boolean_T exitg1;
  boolean_T b_accumMatrix;
  emxArray_real_T *b_centers;
  emxArray_real_T *metric;
  emxArray_boolean_T *x;
  emxArray_int32_T *ii;
  int nx;
  int idx;
  emxArray_real_T *idx2Keep;
  if (varargin_2[0] == varargin_2[1]) {
    radiusRange_size[0] = 1;
    radiusRange_size[1] = 1;
    radiusRange_data[0] = varargin_2[0];
  } else {
    radiusRange_size[0] = 1;
    radiusRange_size[1] = 2;
    for (i5 = 0; i5 < 2; i5++) {
      radiusRange_data[i5] = varargin_2[i5];
    }
  }

  emxInit_creal_T(&accumMatrix, 2);
  emxInit_real32_T(&gradientImg, 2);
  i5 = centers->size[0] * centers->size[1];
  centers->size[0] = 0;
  centers->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)centers, i5, sizeof(double));
  i5 = r_estimated->size[0] * r_estimated->size[1];
  r_estimated->size[0] = 0;
  r_estimated->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)r_estimated, i5, sizeof(double));
  chaccum(varargin_1, radiusRange_data, radiusRange_size, accumMatrix,
          gradientImg);
  y = false;
  ix = 0;
  emxFree_real32_T(&gradientImg);
  exitg1 = false;
  while ((!exitg1) && (ix + 1 <= accumMatrix->size[0] * accumMatrix->size[1])) {
    b_accumMatrix = ((accumMatrix->data[ix].re == 0.0) && (accumMatrix->data[ix]
      .im == 0.0));
    if (b_accumMatrix || (rtIsNaN(accumMatrix->data[ix].re) || rtIsNaN
                          (accumMatrix->data[ix].im))) {
      b_accumMatrix = true;
    } else {
      b_accumMatrix = false;
    }

    if (!b_accumMatrix) {
      y = true;
      exitg1 = true;
    } else {
      ix++;
    }
  }

  if (y) {
    emxInit_real_T(&b_centers, 2);
    emxInit_real_T(&metric, 2);
    chcenters(accumMatrix, 1.0 - varargin_4, b_centers, metric);
    i5 = centers->size[0] * centers->size[1];
    centers->size[0] = b_centers->size[0];
    centers->size[1] = b_centers->size[1];
    emxEnsureCapacity((emxArray__common *)centers, i5, sizeof(double));
    ix = b_centers->size[0] * b_centers->size[1];
    for (i5 = 0; i5 < ix; i5++) {
      centers->data[i5] = b_centers->data[i5];
    }

    if (!((b_centers->size[0] == 0) || (b_centers->size[1] == 0))) {
      emxInit_boolean_T(&x, 2);
      i5 = x->size[0] * x->size[1];
      x->size[0] = metric->size[0];
      x->size[1] = metric->size[1];
      emxEnsureCapacity((emxArray__common *)x, i5, sizeof(boolean_T));
      ix = metric->size[0] * metric->size[1];
      for (i5 = 0; i5 < ix; i5++) {
        x->data[i5] = (metric->data[i5] >= 1.0 - varargin_4);
      }

      emxInit_int32_T(&ii, 1);
      nx = x->size[0] * x->size[1];
      idx = 0;
      i5 = ii->size[0];
      ii->size[0] = nx;
      emxEnsureCapacity((emxArray__common *)ii, i5, sizeof(int));
      ix = 1;
      exitg1 = false;
      while ((!exitg1) && (ix <= nx)) {
        if (x->data[ix - 1]) {
          idx++;
          ii->data[idx - 1] = ix;
          if (idx >= nx) {
            exitg1 = true;
          } else {
            ix++;
          }
        } else {
          ix++;
        }
      }

      emxFree_boolean_T(&x);
      if (nx == 1) {
        if (idx == 0) {
          i5 = ii->size[0];
          ii->size[0] = 0;
          emxEnsureCapacity((emxArray__common *)ii, i5, sizeof(int));
        }
      } else {
        i5 = ii->size[0];
        if (1 > idx) {
          ii->size[0] = 0;
        } else {
          ii->size[0] = idx;
        }

        emxEnsureCapacity((emxArray__common *)ii, i5, sizeof(int));
      }

      emxInit_real_T1(&idx2Keep, 1);
      i5 = idx2Keep->size[0];
      idx2Keep->size[0] = ii->size[0];
      emxEnsureCapacity((emxArray__common *)idx2Keep, i5, sizeof(double));
      ix = ii->size[0];
      for (i5 = 0; i5 < ix; i5++) {
        idx2Keep->data[i5] = ii->data[i5];
      }

      emxFree_int32_T(&ii);
      ix = b_centers->size[1];
      i5 = centers->size[0] * centers->size[1];
      centers->size[0] = idx2Keep->size[0];
      centers->size[1] = ix;
      emxEnsureCapacity((emxArray__common *)centers, i5, sizeof(double));
      for (i5 = 0; i5 < ix; i5++) {
        nx = idx2Keep->size[0];
        for (idx = 0; idx < nx; idx++) {
          centers->data[idx + centers->size[0] * i5] = b_centers->data[((int)
            idx2Keep->data[idx] + b_centers->size[0] * i5) - 1];
        }
      }

      nx = idx2Keep->size[0];
      if (nx == 0) {
        i5 = centers->size[0] * centers->size[1];
        centers->size[0] = 0;
        centers->size[1] = 0;
        emxEnsureCapacity((emxArray__common *)centers, i5, sizeof(double));
      } else if (radiusRange_size[1] == 1) {
        nx = idx2Keep->size[0];
        i5 = r_estimated->size[0] * r_estimated->size[1];
        r_estimated->size[0] = nx;
        r_estimated->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)r_estimated, i5, sizeof(double));
        if (!(nx == 0)) {
          nx = idx2Keep->size[0];
          for (ix = 1; ix <= nx; ix++) {
            r_estimated->data[ix - 1] = radiusRange_data[0];
          }
        }
      } else {
        chradiiphcode(centers, accumMatrix, radiusRange_data, radiusRange_size,
                      idx2Keep);
        i5 = r_estimated->size[0] * r_estimated->size[1];
        r_estimated->size[0] = idx2Keep->size[0];
        r_estimated->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)r_estimated, i5, sizeof(double));
        ix = idx2Keep->size[0];
        for (i5 = 0; i5 < ix; i5++) {
          r_estimated->data[i5] = idx2Keep->data[i5];
        }
      }

      emxFree_real_T(&idx2Keep);
    }

    emxFree_real_T(&metric);
    emxFree_real_T(&b_centers);
  }

  emxFree_creal_T(&accumMatrix);
}

//
// File trailer for imfindcircles.cpp
//
// [EOF]
//
