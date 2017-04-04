//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: chaccum.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "chaccum.h"
#include "analyzeImage_emxutil.h"
#include "exp.h"
#include "log.h"
#include "multithresh.h"
#include "hypot.h"
#include "imfilter.h"
#include "convn.h"
#include "all.h"

// Function Declarations
static void parseInputs(double varargin_2_data[], int varargin_2_size[2]);

// Function Definitions

//
// Arguments    : double varargin_2_data[]
//                int varargin_2_size[2]
// Return Type  : void
//
static void parseInputs(double varargin_2_data[], int varargin_2_size[2])
{
  if (varargin_2_size[1] == 2) {
    if (varargin_2_data[0] == varargin_2_data[1]) {
      varargin_2_size[0] = 1;
      varargin_2_size[1] = 1;
    }
  } else {
    varargin_2_size[0] = 1;
    varargin_2_size[1] = 1;
  }
}

//
// Arguments    : const emxArray_boolean_T *varargin_1
//                const double varargin_2_data[]
//                const int varargin_2_size[2]
//                emxArray_creal_T *accumMatrix
//                emxArray_real32_T *gradientImg
// Return Type  : void
//
void chaccum(const emxArray_boolean_T *varargin_1, const double varargin_2_data[],
             const int varargin_2_size[2], emxArray_creal_T *accumMatrix,
             emxArray_real32_T *gradientImg)
{
  emxArray_boolean_T *A;
  int i6;
  int loop_ub;
  int radiusRangeIn_size[2];
  emxArray_boolean_T *b_A;
  double radiusRangeIn_data[2];
  emxArray_int8_T *c_A;
  int ii;
  int idx;
  int i7;
  boolean_T flat;
  emxArray_real32_T *s;
  int finalSize[2];
  double pad[2];
  emxArray_real32_T *d_A;
  emxArray_real32_T *a;
  emxArray_real_T *b_a;
  emxArray_real32_T *Gx;
  emxArray_real32_T *Gy;
  emxArray_real_T *result;
  int ixstart;
  int n;
  float t;
  emxArray_real32_T *y;
  boolean_T exitg1;
  emxArray_real_T *threshRaw;
  emxArray_real32_T *b_y;
  emxArray_real32_T *threshout;
  float edgeThresh;
  emxArray_boolean_T *x;
  double sigma_b_squared[256];
  float maxA;
  double omega[256];
  emxArray_int32_T *b_ii;
  double mu[256];
  emxArray_int32_T *jj;
  double ndbl;
  emxArray_real32_T *uniqueVals;
  boolean_T isDegenerate;
  double idxSum;
  double idxNum;
  boolean_T guard1 = false;
  emxArray_real_T *Ey;
  emxArray_real_T *Ex;
  emxArray_int32_T *ndx;
  short siz[2];
  emxArray_real_T *radiusRange;
  double apnd;
  double absb;
  emxArray_creal_T *Opca;
  emxArray_creal_T *r3;
  double xcStep;
  int b_varargin_1;
  int N;
  int M;
  int i;
  emxArray_real_T *Ex_chunk;
  emxArray_real_T *Ey_chunk;
  emxArray_real_T *idxE_chunk;
  emxArray_real32_T *xc;
  emxArray_real32_T *yc;
  emxArray_creal_T *w;
  emxArray_boolean_T *inside;
  emxArray_boolean_T *rows_to_keep;
  emxArray_int32_T *xckeep;
  emxArray_int32_T *yckeep;
  emxArray_creal_T *wkeep;
  emxArray_creal_T *r4;
  double b_i;
  double u1;
  emxInit_boolean_T(&A, 2);
  i6 = A->size[0] * A->size[1];
  A->size[0] = varargin_1->size[0];
  A->size[1] = varargin_1->size[1];
  emxEnsureCapacity((emxArray__common *)A, i6, sizeof(boolean_T));
  loop_ub = varargin_1->size[0] * varargin_1->size[1];
  for (i6 = 0; i6 < loop_ub; i6++) {
    A->data[i6] = varargin_1->data[i6];
  }

  radiusRangeIn_size[0] = 1;
  radiusRangeIn_size[1] = varargin_2_size[1];
  loop_ub = varargin_2_size[0] * varargin_2_size[1];
  for (i6 = 0; i6 < loop_ub; i6++) {
    radiusRangeIn_data[i6] = varargin_2_data[i6];
  }

  emxInit_boolean_T1(&b_A, 1);
  emxInit_int8_T(&c_A, 2);
  parseInputs(radiusRangeIn_data, radiusRangeIn_size);
  i6 = c_A->size[0] * c_A->size[1];
  c_A->size[0] = A->size[0];
  c_A->size[1] = A->size[1];
  emxEnsureCapacity((emxArray__common *)c_A, i6, sizeof(signed char));
  loop_ub = A->size[1];
  for (i6 = 0; i6 < loop_ub; i6++) {
    idx = A->size[0];
    for (i7 = 0; i7 < idx; i7++) {
      c_A->data[i7 + c_A->size[0] * i6] = (signed char)A->data[i7 + A->size[0] *
        i6];
    }
  }

  ii = c_A->data[0];
  i6 = b_A->size[0];
  b_A->size[0] = A->size[0] * A->size[1];
  emxEnsureCapacity((emxArray__common *)b_A, i6, sizeof(boolean_T));
  loop_ub = A->size[0] * A->size[1];
  emxFree_int8_T(&c_A);
  for (i6 = 0; i6 < loop_ub; i6++) {
    b_A->data[i6] = (A->data[i6] == ii);
  }

  flat = all(b_A);
  emxFree_boolean_T(&b_A);
  if (flat) {
    i6 = accumMatrix->size[0] * accumMatrix->size[1];
    accumMatrix->size[0] = A->size[0];
    accumMatrix->size[1] = A->size[1];
    emxEnsureCapacity((emxArray__common *)accumMatrix, i6, sizeof(creal_T));
    loop_ub = A->size[0] * A->size[1];
    for (i6 = 0; i6 < loop_ub; i6++) {
      accumMatrix->data[i6].re = 0.0;
      accumMatrix->data[i6].im = 0.0;
    }

    i6 = gradientImg->size[0] * gradientImg->size[1];
    gradientImg->size[0] = A->size[0];
    gradientImg->size[1] = A->size[1];
    emxEnsureCapacity((emxArray__common *)gradientImg, i6, sizeof(float));
    loop_ub = A->size[0] * A->size[1];
    for (i6 = 0; i6 < loop_ub; i6++) {
      gradientImg->data[i6] = 0.0F;
    }
  } else {
    emxInit_real32_T(&s, 2);
    i6 = s->size[0] * s->size[1];
    s->size[0] = A->size[0];
    s->size[1] = A->size[1];
    emxEnsureCapacity((emxArray__common *)s, i6, sizeof(float));
    loop_ub = A->size[0] * A->size[1];
    for (i6 = 0; i6 < loop_ub; i6++) {
      s->data[i6] = A->data[i6];
    }

    finalSize[0] = s->size[0];
    pad[0] = 3.0;
    finalSize[1] = s->size[1];
    pad[1] = 3.0;
    emxInit_real32_T(&d_A, 2);
    if ((s->size[0] == 0) || (s->size[1] == 0)) {
      i6 = d_A->size[0] * d_A->size[1];
      d_A->size[0] = s->size[0];
      d_A->size[1] = s->size[1];
      emxEnsureCapacity((emxArray__common *)d_A, i6, sizeof(float));
      loop_ub = s->size[0] * s->size[1];
      for (i6 = 0; i6 < loop_ub; i6++) {
        d_A->data[i6] = s->data[i6];
      }
    } else {
      emxInit_real32_T(&a, 2);
      emxInit_real_T(&b_a, 2);
      padImage(s, pad, a);
      i6 = b_a->size[0] * b_a->size[1];
      b_a->size[0] = a->size[0];
      b_a->size[1] = a->size[1];
      emxEnsureCapacity((emxArray__common *)b_a, i6, sizeof(double));
      loop_ub = a->size[0] * a->size[1];
      for (i6 = 0; i6 < loop_ub; i6++) {
        b_a->data[i6] = a->data[i6];
      }

      emxFree_real32_T(&a);
      emxInit_real_T(&result, 2);
      convn(b_a, result);
      emxFree_real_T(&b_a);
      if (4 > (short)finalSize[0] + 3) {
        i6 = 0;
        i7 = 0;
      } else {
        i6 = 3;
        i7 = (short)finalSize[0] + 3;
      }

      if (4 > (short)finalSize[1] + 3) {
        ixstart = 0;
        ii = 0;
      } else {
        ixstart = 3;
        ii = (short)finalSize[1] + 3;
      }

      n = d_A->size[0] * d_A->size[1];
      d_A->size[0] = i7 - i6;
      d_A->size[1] = ii - ixstart;
      emxEnsureCapacity((emxArray__common *)d_A, n, sizeof(float));
      loop_ub = ii - ixstart;
      for (ii = 0; ii < loop_ub; ii++) {
        idx = i7 - i6;
        for (n = 0; n < idx; n++) {
          d_A->data[n + d_A->size[0] * ii] = (float)result->data[(i6 + n) +
            result->size[0] * (ixstart + ii)];
        }
      }

      emxFree_real_T(&result);
    }

    emxFree_real32_T(&s);
    emxInit_real32_T(&Gx, 2);
    emxInit_real32_T(&Gy, 2);
    imfilter(d_A, Gx);
    b_imfilter(d_A, Gy);
    b_hypot(Gx, Gy, gradientImg);
    ixstart = 1;
    n = gradientImg->size[0] * gradientImg->size[1];
    t = gradientImg->data[0];
    if (gradientImg->size[0] * gradientImg->size[1] > 1) {
      if (rtIsNaNF(gradientImg->data[0])) {
        ii = 2;
        exitg1 = false;
        while ((!exitg1) && (ii <= n)) {
          ixstart = ii;
          if (!rtIsNaNF(gradientImg->data[ii - 1])) {
            t = gradientImg->data[ii - 1];
            exitg1 = true;
          } else {
            ii++;
          }
        }
      }

      if (ixstart < gradientImg->size[0] * gradientImg->size[1]) {
        while (ixstart + 1 <= n) {
          if (gradientImg->data[ixstart] > t) {
            t = gradientImg->data[ixstart];
          }

          ixstart++;
        }
      }
    }

    emxInit_real32_T(&y, 2);
    i6 = y->size[0] * y->size[1];
    y->size[0] = gradientImg->size[0];
    y->size[1] = gradientImg->size[1];
    emxEnsureCapacity((emxArray__common *)y, i6, sizeof(float));
    loop_ub = gradientImg->size[0] * gradientImg->size[1];
    for (i6 = 0; i6 < loop_ub; i6++) {
      y->data[i6] = gradientImg->data[i6] / t;
    }

    emxInit_real_T(&threshRaw, 2);
    if ((y->size[0] == 0) || (y->size[1] == 0)) {
      emxInit_real32_T(&threshout, 2);
      getDegenerateThresholds(y, threshout);
      edgeThresh = threshout->data[0];
      emxFree_real32_T(&threshout);
    } else {
      emxInit_real32_T(&b_y, 2);
      i6 = b_y->size[0] * b_y->size[1];
      b_y->size[0] = y->size[0];
      b_y->size[1] = y->size[1];
      emxEnsureCapacity((emxArray__common *)b_y, i6, sizeof(float));
      loop_ub = y->size[0] * y->size[1];
      for (i6 = 0; i6 < loop_ub; i6++) {
        b_y->data[i6] = y->data[i6];
      }

      getpdf(b_y, sigma_b_squared, &edgeThresh, &maxA, &flat);
      emxFree_real32_T(&b_y);
      if (flat) {
        if (rtIsNaNF(edgeThresh)) {
          edgeThresh = 1.0F;
        }
      } else {
        memcpy(&omega[0], &sigma_b_squared[0], sizeof(double) << 8);
        for (ixstart = 0; ixstart < 255; ixstart++) {
          omega[ixstart + 1] += omega[ixstart];
        }

        for (i6 = 0; i6 < 256; i6++) {
          mu[i6] = sigma_b_squared[i6] * (1.0 + (double)i6);
        }

        for (ixstart = 0; ixstart < 255; ixstart++) {
          mu[ixstart + 1] += mu[ixstart];
        }

        for (ixstart = 0; ixstart < 256; ixstart++) {
          ndbl = mu[255] * omega[ixstart] - mu[ixstart];
          sigma_b_squared[ixstart] = ndbl * ndbl / (omega[ixstart] * (1.0 -
            omega[ixstart]));
        }

        ixstart = 1;
        ndbl = sigma_b_squared[0];
        if (rtIsNaN(sigma_b_squared[0])) {
          ii = 2;
          exitg1 = false;
          while ((!exitg1) && (ii < 257)) {
            ixstart = ii;
            if (!rtIsNaN(sigma_b_squared[ii - 1])) {
              ndbl = sigma_b_squared[ii - 1];
              exitg1 = true;
            } else {
              ii++;
            }
          }
        }

        if (ixstart < 256) {
          while (ixstart + 1 < 257) {
            if (sigma_b_squared[ixstart] > ndbl) {
              ndbl = sigma_b_squared[ixstart];
            }

            ixstart++;
          }
        }

        flat = ((!rtIsInf(ndbl)) && (!rtIsNaN(ndbl)));
        emxInit_real32_T(&threshout, 2);
        emxInit_real32_T(&uniqueVals, 2);
        if (flat) {
          idxSum = 0.0;
          idxNum = 0.0;
          for (ii = 0; ii < 256; ii++) {
            if (sigma_b_squared[ii] == ndbl) {
              idxSum += 1.0 + (double)ii;
              idxNum++;
            }
          }

          i6 = threshRaw->size[0] * threshRaw->size[1];
          threshRaw->size[0] = 1;
          threshRaw->size[1] = 1;
          emxEnsureCapacity((emxArray__common *)threshRaw, i6, sizeof(double));
          threshRaw->data[0] = idxSum / idxNum - 1.0;
          map2OriginalScale(threshRaw, edgeThresh, maxA, threshout);
        } else {
          checkForDegenerateInput(y, &isDegenerate, uniqueVals);
          b_getDegenerateThresholds(uniqueVals, threshout);
          i6 = threshRaw->size[0] * threshRaw->size[1];
          threshRaw->size[0] = 1;
          threshRaw->size[1] = threshout->size[1];
          emxEnsureCapacity((emxArray__common *)threshRaw, i6, sizeof(double));
          loop_ub = threshout->size[0] * threshout->size[1];
          for (i6 = 0; i6 < loop_ub; i6++) {
            threshRaw->data[i6] = threshout->data[i6];
          }

          checkForDegenerateInput(y, &isDegenerate, uniqueVals);
          if (isDegenerate) {
            b_getDegenerateThresholds(uniqueVals, threshout);
          } else {
            map2OriginalScale(threshRaw, edgeThresh, maxA, threshout);
          }
        }

        emxFree_real32_T(&uniqueVals);
        edgeThresh = threshout->data[0];
        emxFree_real32_T(&threshout);
      }
    }

    emxFree_real32_T(&y);
    emxInit_boolean_T(&x, 2);
    t *= edgeThresh;
    i6 = x->size[0] * x->size[1];
    x->size[0] = gradientImg->size[0];
    x->size[1] = gradientImg->size[1];
    emxEnsureCapacity((emxArray__common *)x, i6, sizeof(boolean_T));
    loop_ub = gradientImg->size[0] * gradientImg->size[1];
    for (i6 = 0; i6 < loop_ub; i6++) {
      x->data[i6] = (gradientImg->data[i6] > t);
    }

    emxInit_int32_T(&b_ii, 1);
    emxInit_int32_T(&jj, 1);
    n = x->size[0] * x->size[1];
    idx = 0;
    i6 = b_ii->size[0];
    b_ii->size[0] = n;
    emxEnsureCapacity((emxArray__common *)b_ii, i6, sizeof(int));
    i6 = jj->size[0];
    jj->size[0] = n;
    emxEnsureCapacity((emxArray__common *)jj, i6, sizeof(int));
    if (n == 0) {
      i6 = b_ii->size[0];
      b_ii->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)b_ii, i6, sizeof(int));
      i6 = jj->size[0];
      jj->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)jj, i6, sizeof(int));
    } else {
      ii = 1;
      ixstart = 1;
      exitg1 = false;
      while ((!exitg1) && (ixstart <= x->size[1])) {
        guard1 = false;
        if (x->data[(ii + x->size[0] * (ixstart - 1)) - 1]) {
          idx++;
          b_ii->data[idx - 1] = ii;
          jj->data[idx - 1] = ixstart;
          if (idx >= n) {
            exitg1 = true;
          } else {
            guard1 = true;
          }
        } else {
          guard1 = true;
        }

        if (guard1) {
          ii++;
          if (ii > x->size[0]) {
            ii = 1;
            ixstart++;
          }
        }
      }

      if (n == 1) {
        if (idx == 0) {
          i6 = b_ii->size[0];
          b_ii->size[0] = 0;
          emxEnsureCapacity((emxArray__common *)b_ii, i6, sizeof(int));
          i6 = jj->size[0];
          jj->size[0] = 0;
          emxEnsureCapacity((emxArray__common *)jj, i6, sizeof(int));
        }
      } else {
        i6 = b_ii->size[0];
        if (1 > idx) {
          b_ii->size[0] = 0;
        } else {
          b_ii->size[0] = idx;
        }

        emxEnsureCapacity((emxArray__common *)b_ii, i6, sizeof(int));
        i6 = jj->size[0];
        if (1 > idx) {
          jj->size[0] = 0;
        } else {
          jj->size[0] = idx;
        }

        emxEnsureCapacity((emxArray__common *)jj, i6, sizeof(int));
      }
    }

    emxFree_boolean_T(&x);
    emxInit_real_T1(&Ey, 1);
    i6 = Ey->size[0];
    Ey->size[0] = b_ii->size[0];
    emxEnsureCapacity((emxArray__common *)Ey, i6, sizeof(double));
    loop_ub = b_ii->size[0];
    for (i6 = 0; i6 < loop_ub; i6++) {
      Ey->data[i6] = b_ii->data[i6];
    }

    emxFree_int32_T(&b_ii);
    emxInit_real_T1(&Ex, 1);
    i6 = Ex->size[0];
    Ex->size[0] = jj->size[0];
    emxEnsureCapacity((emxArray__common *)Ex, i6, sizeof(double));
    loop_ub = jj->size[0];
    for (i6 = 0; i6 < loop_ub; i6++) {
      Ex->data[i6] = jj->data[i6];
    }

    emxFree_int32_T(&jj);
    for (i6 = 0; i6 < 2; i6++) {
      siz[i6] = (short)gradientImg->size[i6];
    }

    emxInit_int32_T(&ndx, 1);
    i6 = ndx->size[0];
    ndx->size[0] = Ey->size[0];
    emxEnsureCapacity((emxArray__common *)ndx, i6, sizeof(int));
    loop_ub = Ey->size[0];
    for (i6 = 0; i6 < loop_ub; i6++) {
      ndx->data[i6] = (int)Ey->data[i6] + siz[0] * ((int)Ex->data[i6] - 1);
    }

    emxInit_real_T(&radiusRange, 2);
    if (radiusRangeIn_size[1] > 1) {
      if (rtIsNaN(radiusRangeIn_data[0]) || rtIsNaN(radiusRangeIn_data[1])) {
        i6 = radiusRange->size[0] * radiusRange->size[1];
        radiusRange->size[0] = 1;
        radiusRange->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)radiusRange, i6, sizeof(double));
        radiusRange->data[0] = rtNaN;
      } else if (radiusRangeIn_data[1] < radiusRangeIn_data[0]) {
        i6 = radiusRange->size[0] * radiusRange->size[1];
        radiusRange->size[0] = 1;
        radiusRange->size[1] = 0;
        emxEnsureCapacity((emxArray__common *)radiusRange, i6, sizeof(double));
      } else if ((rtIsInf(radiusRangeIn_data[0]) || rtIsInf(radiusRangeIn_data[1]))
                 && (radiusRangeIn_data[0] == radiusRangeIn_data[1])) {
        i6 = radiusRange->size[0] * radiusRange->size[1];
        radiusRange->size[0] = 1;
        radiusRange->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)radiusRange, i6, sizeof(double));
        radiusRange->data[0] = rtNaN;
      } else {
        ndbl = std::floor((radiusRangeIn_data[1] - radiusRangeIn_data[0]) / 0.5
                          + 0.5);
        apnd = radiusRangeIn_data[0] + ndbl * 0.5;
        idxSum = apnd - radiusRangeIn_data[1];
        idxNum = std::abs(radiusRangeIn_data[0]);
        absb = std::abs(radiusRangeIn_data[1]);
        if ((idxNum > absb) || rtIsNaN(absb)) {
          absb = idxNum;
        }

        if (std::abs(idxSum) < 4.4408920985006262E-16 * absb) {
          ndbl++;
          apnd = radiusRangeIn_data[1];
        } else if (idxSum > 0.0) {
          apnd = radiusRangeIn_data[0] + (ndbl - 1.0) * 0.5;
        } else {
          ndbl++;
        }

        if (ndbl >= 0.0) {
          n = (int)ndbl;
        } else {
          n = 0;
        }

        i6 = radiusRange->size[0] * radiusRange->size[1];
        radiusRange->size[0] = 1;
        radiusRange->size[1] = n;
        emxEnsureCapacity((emxArray__common *)radiusRange, i6, sizeof(double));
        if (n > 0) {
          radiusRange->data[0] = radiusRangeIn_data[0];
          if (n > 1) {
            radiusRange->data[n - 1] = apnd;
            ii = (n - 1) / 2;
            for (ixstart = 1; ixstart < ii; ixstart++) {
              ndbl = (double)ixstart * 0.5;
              radiusRange->data[ixstart] = radiusRangeIn_data[0] + ndbl;
              radiusRange->data[(n - ixstart) - 1] = apnd - ndbl;
            }

            if (ii << 1 == n - 1) {
              radiusRange->data[ii] = (radiusRangeIn_data[0] + apnd) / 2.0;
            } else {
              ndbl = (double)ii * 0.5;
              radiusRange->data[ii] = radiusRangeIn_data[0] + ndbl;
              radiusRange->data[ii + 1] = apnd - ndbl;
            }
          }
        }
      }
    } else {
      i6 = radiusRange->size[0] * radiusRange->size[1];
      radiusRange->size[0] = 1;
      radiusRange->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)radiusRange, i6, sizeof(double));
      radiusRange->data[0] = radiusRangeIn_data[0];
    }

    if (radiusRange->size[1] > 1) {
      i6 = threshRaw->size[0] * threshRaw->size[1];
      threshRaw->size[0] = 1;
      threshRaw->size[1] = radiusRange->size[1];
      emxEnsureCapacity((emxArray__common *)threshRaw, i6, sizeof(double));
      loop_ub = radiusRange->size[0] * radiusRange->size[1];
      for (i6 = 0; i6 < loop_ub; i6++) {
        threshRaw->data[i6] = radiusRange->data[i6];
      }

      b_log(threshRaw);
      ndbl = threshRaw->data[threshRaw->size[1] - 1] - threshRaw->data[0];
      idxSum = threshRaw->data[0];
      i6 = threshRaw->size[0] * threshRaw->size[1];
      threshRaw->size[0] = 1;
      emxEnsureCapacity((emxArray__common *)threshRaw, i6, sizeof(double));
      loop_ub = threshRaw->size[1];
      for (i6 = 0; i6 < loop_ub; i6++) {
        threshRaw->data[threshRaw->size[0] * i6] = (threshRaw->data
          [threshRaw->size[0] * i6] - idxSum) / ndbl * 2.0 * 3.1415926535897931
          - 3.1415926535897931;
      }
    } else {
      i6 = threshRaw->size[0] * threshRaw->size[1];
      threshRaw->size[0] = 1;
      threshRaw->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)threshRaw, i6, sizeof(double));
      threshRaw->data[0] = 0.0;
    }

    for (i6 = 0; i6 < 2; i6++) {
      finalSize[i6] = threshRaw->size[i6];
    }

    emxInit_creal_T(&Opca, 2);
    emxInit_creal_T(&r3, 2);
    i6 = Opca->size[0] * Opca->size[1];
    Opca->size[0] = 1;
    Opca->size[1] = finalSize[1];
    emxEnsureCapacity((emxArray__common *)Opca, i6, sizeof(creal_T));
    i6 = r3->size[0] * r3->size[1];
    r3->size[0] = 1;
    r3->size[1] = threshRaw->size[1];
    emxEnsureCapacity((emxArray__common *)r3, i6, sizeof(creal_T));
    loop_ub = threshRaw->size[0] * threshRaw->size[1];
    for (i6 = 0; i6 < loop_ub; i6++) {
      r3->data[i6].re = threshRaw->data[i6] * 0.0;
      r3->data[i6].im = threshRaw->data[i6];
    }

    b_exp(r3);
    loop_ub = r3->size[1];
    for (i6 = 0; i6 < loop_ub; i6++) {
      Opca->data[Opca->size[0] * i6] = r3->data[r3->size[0] * i6];
    }

    emxFree_creal_T(&r3);
    i6 = Opca->size[0] * Opca->size[1];
    Opca->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)Opca, i6, sizeof(creal_T));
    ii = Opca->size[0];
    ixstart = Opca->size[1];
    loop_ub = ii * ixstart;
    for (i6 = 0; i6 < loop_ub; i6++) {
      ndbl = Opca->data[i6].re;
      idxSum = Opca->data[i6].im;
      idxNum = 6.2831853071795862 * radiusRange->data[i6];
      if (idxSum == 0.0) {
        Opca->data[i6].re = ndbl / idxNum;
        Opca->data[i6].im = 0.0;
      } else if (ndbl == 0.0) {
        Opca->data[i6].re = 0.0;
        Opca->data[i6].im = idxSum / idxNum;
      } else {
        Opca->data[i6].re = ndbl / idxNum;
        Opca->data[i6].im = idxSum / idxNum;
      }
    }

    xcStep = std::floor(1.0E+6 / (double)radiusRange->size[1]);
    b_varargin_1 = Ex->size[0];
    N = d_A->size[1];
    M = d_A->size[0];
    i6 = accumMatrix->size[0] * accumMatrix->size[1];
    accumMatrix->size[0] = d_A->size[0];
    accumMatrix->size[1] = d_A->size[1];
    emxEnsureCapacity((emxArray__common *)accumMatrix, i6, sizeof(creal_T));
    loop_ub = d_A->size[0] * d_A->size[1];
    emxFree_real32_T(&d_A);
    for (i6 = 0; i6 < loop_ub; i6++) {
      accumMatrix->data[i6].re = 0.0;
      accumMatrix->data[i6].im = 0.0;
    }

    i6 = (int)(((double)Ex->size[0] + (xcStep - 1.0)) / xcStep);
    i = 0;
    emxInit_real_T1(&Ex_chunk, 1);
    emxInit_real_T1(&Ey_chunk, 1);
    emxInit_real_T1(&idxE_chunk, 1);
    emxInit_real32_T(&xc, 2);
    emxInit_real32_T(&yc, 2);
    emxInit_creal_T(&w, 2);
    emxInit_boolean_T(&inside, 2);
    emxInit_boolean_T1(&rows_to_keep, 1);
    emxInit_int32_T(&xckeep, 1);
    emxInit_int32_T(&yckeep, 1);
    emxInit_creal_T1(&wkeep, 1);
    emxInit_creal_T(&r4, 2);
    while (i <= i6 - 1) {
      b_i = 1.0 + (double)i * xcStep;
      ndbl = (b_i + xcStep) - 1.0;
      u1 = b_varargin_1;
      if (ndbl < u1) {
        u1 = ndbl;
      }

      if (rtIsNaN(b_i)) {
        i7 = threshRaw->size[0] * threshRaw->size[1];
        threshRaw->size[0] = 1;
        threshRaw->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)threshRaw, i7, sizeof(double));
        threshRaw->data[0] = rtNaN;
      } else if (u1 < b_i) {
        i7 = threshRaw->size[0] * threshRaw->size[1];
        threshRaw->size[0] = 1;
        threshRaw->size[1] = 0;
        emxEnsureCapacity((emxArray__common *)threshRaw, i7, sizeof(double));
      } else if ((rtIsInf(b_i) || rtIsInf(u1)) && (b_i == u1)) {
        i7 = threshRaw->size[0] * threshRaw->size[1];
        threshRaw->size[0] = 1;
        threshRaw->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)threshRaw, i7, sizeof(double));
        threshRaw->data[0] = rtNaN;
      } else if (b_i == b_i) {
        i7 = threshRaw->size[0] * threshRaw->size[1];
        threshRaw->size[0] = 1;
        threshRaw->size[1] = (int)(u1 - b_i) + 1;
        emxEnsureCapacity((emxArray__common *)threshRaw, i7, sizeof(double));
        loop_ub = (int)(u1 - b_i);
        for (i7 = 0; i7 <= loop_ub; i7++) {
          threshRaw->data[threshRaw->size[0] * i7] = b_i + (double)i7;
        }
      } else {
        ndbl = std::floor((u1 - b_i) + 0.5);
        apnd = b_i + ndbl;
        idxSum = apnd - u1;
        idxNum = std::abs(b_i);
        absb = std::abs(u1);
        if ((idxNum > absb) || rtIsNaN(absb)) {
          absb = idxNum;
        }

        if (std::abs(idxSum) < 4.4408920985006262E-16 * absb) {
          ndbl++;
          apnd = u1;
        } else if (idxSum > 0.0) {
          apnd = b_i + (ndbl - 1.0);
        } else {
          ndbl++;
        }

        if (ndbl >= 0.0) {
          n = (int)ndbl;
        } else {
          n = 0;
        }

        i7 = threshRaw->size[0] * threshRaw->size[1];
        threshRaw->size[0] = 1;
        threshRaw->size[1] = n;
        emxEnsureCapacity((emxArray__common *)threshRaw, i7, sizeof(double));
        if (n > 0) {
          threshRaw->data[0] = b_i;
          if (n > 1) {
            threshRaw->data[n - 1] = apnd;
            ii = (n - 1) / 2;
            for (ixstart = 1; ixstart < ii; ixstart++) {
              threshRaw->data[ixstart] = b_i + (double)ixstart;
              threshRaw->data[(n - ixstart) - 1] = apnd - (double)ixstart;
            }

            if (ii << 1 == n - 1) {
              threshRaw->data[ii] = (b_i + apnd) / 2.0;
            } else {
              threshRaw->data[ii] = b_i + (double)ii;
              threshRaw->data[ii + 1] = apnd - (double)ii;
            }
          }
        }
      }

      i7 = Ex_chunk->size[0];
      Ex_chunk->size[0] = threshRaw->size[1];
      emxEnsureCapacity((emxArray__common *)Ex_chunk, i7, sizeof(double));
      i7 = Ey_chunk->size[0];
      Ey_chunk->size[0] = threshRaw->size[1];
      emxEnsureCapacity((emxArray__common *)Ey_chunk, i7, sizeof(double));
      i7 = idxE_chunk->size[0];
      idxE_chunk->size[0] = threshRaw->size[1];
      emxEnsureCapacity((emxArray__common *)idxE_chunk, i7, sizeof(double));
      ixstart = (int)b_i - 1;
      for (idx = 0; idx < threshRaw->size[1]; idx++) {
        Ex_chunk->data[idx] = Ex->data[ixstart];
        Ey_chunk->data[idx] = Ey->data[ixstart];
        idxE_chunk->data[idx] = ndx->data[ixstart];
        ixstart++;
      }

      i7 = xc->size[0] * xc->size[1];
      xc->size[0] = idxE_chunk->size[0];
      xc->size[1] = radiusRange->size[1];
      emxEnsureCapacity((emxArray__common *)xc, i7, sizeof(float));
      i7 = yc->size[0] * yc->size[1];
      yc->size[0] = idxE_chunk->size[0];
      yc->size[1] = radiusRange->size[1];
      emxEnsureCapacity((emxArray__common *)yc, i7, sizeof(float));
      i7 = w->size[0] * w->size[1];
      w->size[0] = idxE_chunk->size[0];
      w->size[1] = radiusRange->size[1];
      emxEnsureCapacity((emxArray__common *)w, i7, sizeof(creal_T));
      i7 = inside->size[0] * inside->size[1];
      inside->size[0] = idxE_chunk->size[0];
      inside->size[1] = radiusRange->size[1];
      emxEnsureCapacity((emxArray__common *)inside, i7, sizeof(boolean_T));
      i7 = rows_to_keep->size[0];
      rows_to_keep->size[0] = idxE_chunk->size[0];
      emxEnsureCapacity((emxArray__common *)rows_to_keep, i7, sizeof(boolean_T));
      loop_ub = idxE_chunk->size[0];
      for (i7 = 0; i7 < loop_ub; i7++) {
        rows_to_keep->data[i7] = false;
      }

      for (ixstart = 0; ixstart < radiusRange->size[1]; ixstart++) {
        for (ii = 0; ii < idxE_chunk->size[0]; ii++) {
          t = (float)Ex_chunk->data[ii] + (float)-radiusRange->data[ixstart] *
            (Gx->data[(int)idxE_chunk->data[ii] - 1] / gradientImg->data[(int)
             idxE_chunk->data[ii] - 1]);
          if (t > 0.0F) {
            xc->data[ii + xc->size[0] * ixstart] = t + 0.5F;
          } else if (t < 0.0F) {
            xc->data[ii + xc->size[0] * ixstart] = t - 0.5F;
          } else {
            xc->data[ii + xc->size[0] * ixstart] = 0.0F;
          }

          t = (float)Ey_chunk->data[ii] + (float)-radiusRange->data[ixstart] *
            (Gy->data[(int)idxE_chunk->data[ii] - 1] / gradientImg->data[(int)
             idxE_chunk->data[ii] - 1]);
          if (t > 0.0F) {
            yc->data[ii + yc->size[0] * ixstart] = t + 0.5F;
          } else if (t < 0.0F) {
            yc->data[ii + yc->size[0] * ixstart] = t - 0.5F;
          } else {
            yc->data[ii + yc->size[0] * ixstart] = 0.0F;
          }

          w->data[ii + w->size[0] * ixstart] = Opca->data[Opca->size[0] *
            ixstart];
          inside->data[ii + inside->size[0] * ixstart] = ((xc->data[ii +
            xc->size[0] * ixstart] >= 1.0F) && ((double)xc->data[ii + xc->size[0]
            * ixstart] <= N) && (yc->data[ii + yc->size[0] * ixstart] >= 1.0F) &&
            ((double)yc->data[ii + yc->size[0] * ixstart] < M));
          if (inside->data[ii + inside->size[0] * ixstart]) {
            rows_to_keep->data[ii] = true;
          }
        }
      }

      i7 = xckeep->size[0];
      xckeep->size[0] = xc->size[0] * xc->size[1];
      emxEnsureCapacity((emxArray__common *)xckeep, i7, sizeof(int));
      i7 = yckeep->size[0];
      yckeep->size[0] = yc->size[0] * yc->size[1];
      emxEnsureCapacity((emxArray__common *)yckeep, i7, sizeof(int));
      i7 = wkeep->size[0];
      wkeep->size[0] = w->size[0] * w->size[1];
      emxEnsureCapacity((emxArray__common *)wkeep, i7, sizeof(creal_T));
      n = -1;
      for (ixstart = 0; ixstart < radiusRange->size[1]; ixstart++) {
        for (ii = 0; ii < idxE_chunk->size[0]; ii++) {
          if (rows_to_keep->data[ii] && inside->data[ii + inside->size[0] *
              ixstart]) {
            n++;
            xckeep->data[n] = (int)xc->data[ii + xc->size[0] * ixstart];
            yckeep->data[n] = (int)yc->data[ii + yc->size[0] * ixstart];
            wkeep->data[n] = w->data[ii + w->size[0] * ixstart];
          }
        }
      }

      i7 = r4->size[0] * r4->size[1];
      r4->size[0] = M;
      r4->size[1] = N;
      emxEnsureCapacity((emxArray__common *)r4, i7, sizeof(creal_T));
      loop_ub = M * N;
      for (i7 = 0; i7 < loop_ub; i7++) {
        r4->data[i7].re = 0.0;
        r4->data[i7].im = 0.0;
      }

      for (idx = 0; idx + 1 <= n + 1; idx++) {
        r4->data[(yckeep->data[idx] + r4->size[0] * (xckeep->data[idx] - 1)) - 1]
          .re += wkeep->data[idx].re;
        r4->data[(yckeep->data[idx] + r4->size[0] * (xckeep->data[idx] - 1)) - 1]
          .im += wkeep->data[idx].im;
      }

      i7 = accumMatrix->size[0] * accumMatrix->size[1];
      emxEnsureCapacity((emxArray__common *)accumMatrix, i7, sizeof(creal_T));
      ixstart = accumMatrix->size[0];
      ii = accumMatrix->size[1];
      loop_ub = ixstart * ii;
      for (i7 = 0; i7 < loop_ub; i7++) {
        accumMatrix->data[i7].re += r4->data[i7].re;
        accumMatrix->data[i7].im += r4->data[i7].im;
      }

      i++;
    }

    emxFree_int32_T(&ndx);
    emxFree_real_T(&threshRaw);
    emxFree_real_T(&Ex);
    emxFree_real_T(&Ey);
    emxFree_creal_T(&r4);
    emxFree_real32_T(&Gy);
    emxFree_real32_T(&Gx);
    emxFree_creal_T(&wkeep);
    emxFree_int32_T(&yckeep);
    emxFree_int32_T(&xckeep);
    emxFree_boolean_T(&rows_to_keep);
    emxFree_boolean_T(&inside);
    emxFree_creal_T(&w);
    emxFree_real32_T(&yc);
    emxFree_real32_T(&xc);
    emxFree_real_T(&idxE_chunk);
    emxFree_real_T(&Ey_chunk);
    emxFree_real_T(&Ex_chunk);
    emxFree_creal_T(&Opca);
    emxFree_real_T(&radiusRange);
  }

  emxFree_boolean_T(&A);
}

//
// File trailer for chaccum.cpp
//
// [EOF]
//
