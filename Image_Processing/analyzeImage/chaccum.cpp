//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: chaccum.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 14-Feb-2017 14:49:57
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "chaccum.h"
#include "analyzeImage_emxutil.h"
#include "log.h"
#include "multithresh.h"
#include "imfilter.h"
#include "convn.h"
#include "all.h"

// Function Declarations
static void parseInputs(double varargin_2_data[], int varargin_2_size[2]);
static float rt_hypotf_snf(float u0, float u1);

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
// Arguments    : float u0
//                float u1
// Return Type  : float
//
static float rt_hypotf_snf(float u0, float u1)
{
  float y;
  float a;
  float b;
  a = std::abs(u0);
  b = std::abs(u1);
  if (a < b) {
    a /= b;
    y = b * std::sqrt(a * a + 1.0F);
  } else if (a > b) {
    b /= a;
    y = a * std::sqrt(b * b + 1.0F);
  } else if (rtIsNaNF(b)) {
    y = b;
  } else {
    y = a * 1.41421354F;
  }

  return y;
}

//
// Arguments    : const boolean_T varargin_1[809600]
//                const double varargin_2_data[]
//                const int varargin_2_size[2]
//                creal_T accumMatrix[809600]
//                float gradientImg[809600]
// Return Type  : void
//
void chaccum(const boolean_T varargin_1[809600], const double varargin_2_data[],
             const int varargin_2_size[2], creal_T accumMatrix[809600], float
             gradientImg[809600])
{
  static boolean_T A[809600];
  int radiusRangeIn_size[2];
  int ixstart;
  int i3;
  double radiusRangeIn_data[2];
  static signed char b_A[809600];
  static boolean_T c_A[809600];
  int jj;
  static float d_A[809600];
  static float a[820652];
  static double b_a[820652];
  static const double dv0[36] = { 0.0047877655273893928, 0.011645882737980777,
    0.018163192368528008, 0.018163192368528008, 0.011645882737980777,
    0.0047877655273893928, 0.011645882737980777, 0.028327741609508444,
    0.044180611448322686, 0.044180611448322686, 0.028327741609508444,
    0.011645882737980777, 0.018163192368528008, 0.044180611448322686,
    0.068905119753439215, 0.068905119753439215, 0.044180611448322686,
    0.018163192368528008, 0.018163192368528008, 0.044180611448322686,
    0.068905119753439215, 0.068905119753439215, 0.044180611448322686,
    0.018163192368528008, 0.011645882737980777, 0.028327741609508444,
    0.044180611448322686, 0.044180611448322686, 0.028327741609508444,
    0.011645882737980777, 0.0047877655273893928, 0.011645882737980777,
    0.018163192368528008, 0.018163192368528008, 0.011645882737980777,
    0.0047877655273893928 };

  static double result[820652];
  static float Gx[809600];
  static float Gy[809600];
  float t;
  boolean_T exitg2;
  emxArray_int32_T *ii;
  emxArray_int32_T *b_jj;
  float edgeThresh;
  int idx;
  boolean_T exitg1;
  boolean_T guard1 = false;
  emxArray_real_T *Ey;
  emxArray_real_T *Ex;
  emxArray_int32_T *ndx;
  emxArray_real_T *radiusRange;
  double ndbl;
  double apnd;
  double cdiff;
  emxArray_real_T *lnR;
  double absa;
  double absb;
  int idxkeep;
  emxArray_creal_T *Opca;
  emxArray_creal_T *y;
  emxArray_creal_T *r1;
  double xcStep;
  int b_varargin_1;
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
  double b_i;
  double minval;
  static creal_T out[809600];
  memcpy(&A[0], &varargin_1[0], 809600U * sizeof(boolean_T));
  radiusRangeIn_size[0] = 1;
  radiusRangeIn_size[1] = varargin_2_size[1];
  ixstart = varargin_2_size[0] * varargin_2_size[1];
  for (i3 = 0; i3 < ixstart; i3++) {
    radiusRangeIn_data[i3] = varargin_2_data[i3];
  }

  parseInputs(radiusRangeIn_data, radiusRangeIn_size);
  for (i3 = 0; i3 < 1100; i3++) {
    for (jj = 0; jj < 736; jj++) {
      b_A[jj + 736 * i3] = (signed char)A[jj + 736 * i3];
    }
  }

  for (i3 = 0; i3 < 809600; i3++) {
    c_A[i3] = (A[i3] == b_A[0]);
  }

  if (all(c_A)) {
    memset(&accumMatrix[0], 0, 809600U * sizeof(creal_T));
    memset(&gradientImg[0], 0, 809600U * sizeof(float));
  } else {
    for (i3 = 0; i3 < 809600; i3++) {
      d_A[i3] = A[i3];
    }

    padImage(d_A, a);
    for (i3 = 0; i3 < 820652; i3++) {
      b_a[i3] = a[i3];
    }

    convn(b_a, dv0, result);
    for (i3 = 0; i3 < 1100; i3++) {
      for (jj = 0; jj < 736; jj++) {
        d_A[jj + 736 * i3] = (float)result[(jj + 742 * (3 + i3)) + 3];
      }
    }

    imfilter(d_A, Gx);
    b_imfilter(d_A, Gy);
    for (ixstart = 0; ixstart < 809600; ixstart++) {
      gradientImg[ixstart] = rt_hypotf_snf(Gx[ixstart], Gy[ixstart]);
    }

    ixstart = 1;
    t = gradientImg[0];
    if (rtIsNaNF(gradientImg[0])) {
      jj = 2;
      exitg2 = false;
      while ((!exitg2) && (jj < 809601)) {
        ixstart = jj;
        if (!rtIsNaNF(gradientImg[jj - 1])) {
          t = gradientImg[jj - 1];
          exitg2 = true;
        } else {
          jj++;
        }
      }
    }

    if (ixstart < 809600) {
      while (ixstart + 1 < 809601) {
        if (gradientImg[ixstart] > t) {
          t = gradientImg[ixstart];
        }

        ixstart++;
      }
    }

    for (i3 = 0; i3 < 809600; i3++) {
      d_A[i3] = gradientImg[i3] / t;
    }

    emxInit_int32_T(&ii, 1);
    emxInit_int32_T(&b_jj, 1);
    edgeThresh = multithresh(d_A);
    t *= edgeThresh;
    idx = 0;
    i3 = ii->size[0];
    ii->size[0] = 809600;
    emxEnsureCapacity((emxArray__common *)ii, i3, (int)sizeof(int));
    i3 = b_jj->size[0];
    b_jj->size[0] = 809600;
    emxEnsureCapacity((emxArray__common *)b_jj, i3, (int)sizeof(int));
    ixstart = 1;
    jj = 1;
    exitg1 = false;
    while ((!exitg1) && (jj <= 1100)) {
      guard1 = false;
      if (gradientImg[(ixstart + 736 * (jj - 1)) - 1] > t) {
        idx++;
        ii->data[idx - 1] = ixstart;
        b_jj->data[idx - 1] = jj;
        if (idx >= 809600) {
          exitg1 = true;
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }

      if (guard1) {
        ixstart++;
        if (ixstart > 736) {
          ixstart = 1;
          jj++;
        }
      }
    }

    i3 = ii->size[0];
    if (1 > idx) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = idx;
    }

    emxEnsureCapacity((emxArray__common *)ii, i3, (int)sizeof(int));
    emxInit_real_T1(&Ey, 1);
    i3 = b_jj->size[0];
    if (1 > idx) {
      b_jj->size[0] = 0;
    } else {
      b_jj->size[0] = idx;
    }

    emxEnsureCapacity((emxArray__common *)b_jj, i3, (int)sizeof(int));
    i3 = Ey->size[0];
    Ey->size[0] = ii->size[0];
    emxEnsureCapacity((emxArray__common *)Ey, i3, (int)sizeof(double));
    ixstart = ii->size[0];
    for (i3 = 0; i3 < ixstart; i3++) {
      Ey->data[i3] = ii->data[i3];
    }

    emxFree_int32_T(&ii);
    emxInit_real_T1(&Ex, 1);
    i3 = Ex->size[0];
    Ex->size[0] = b_jj->size[0];
    emxEnsureCapacity((emxArray__common *)Ex, i3, (int)sizeof(double));
    ixstart = b_jj->size[0];
    for (i3 = 0; i3 < ixstart; i3++) {
      Ex->data[i3] = b_jj->data[i3];
    }

    emxFree_int32_T(&b_jj);
    emxInit_int32_T(&ndx, 1);
    i3 = ndx->size[0];
    ndx->size[0] = Ey->size[0];
    emxEnsureCapacity((emxArray__common *)ndx, i3, (int)sizeof(int));
    ixstart = Ey->size[0];
    for (i3 = 0; i3 < ixstart; i3++) {
      ndx->data[i3] = (int)Ey->data[i3] + 736 * ((int)Ex->data[i3] - 1);
    }

    emxInit_real_T(&radiusRange, 2);
    if (radiusRangeIn_size[1] > 1) {
      if (rtIsNaN(radiusRangeIn_data[0]) || rtIsNaN(radiusRangeIn_data[1])) {
        i3 = radiusRange->size[0] * radiusRange->size[1];
        radiusRange->size[0] = 1;
        radiusRange->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)radiusRange, i3, (int)sizeof
                          (double));
        radiusRange->data[0] = rtNaN;
      } else if (radiusRangeIn_data[1] < radiusRangeIn_data[0]) {
        i3 = radiusRange->size[0] * radiusRange->size[1];
        radiusRange->size[0] = 1;
        radiusRange->size[1] = 0;
        emxEnsureCapacity((emxArray__common *)radiusRange, i3, (int)sizeof
                          (double));
      } else if ((rtIsInf(radiusRangeIn_data[0]) || rtIsInf(radiusRangeIn_data[1]))
                 && (radiusRangeIn_data[0] == radiusRangeIn_data[1])) {
        i3 = radiusRange->size[0] * radiusRange->size[1];
        radiusRange->size[0] = 1;
        radiusRange->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)radiusRange, i3, (int)sizeof
                          (double));
        radiusRange->data[0] = rtNaN;
      } else {
        ndbl = std::floor((radiusRangeIn_data[1] - radiusRangeIn_data[0]) / 0.5
                          + 0.5);
        apnd = radiusRangeIn_data[0] + ndbl * 0.5;
        cdiff = apnd - radiusRangeIn_data[1];
        absa = std::abs(radiusRangeIn_data[0]);
        absb = std::abs(radiusRangeIn_data[1]);
        if ((absa >= absb) || rtIsNaN(absb)) {
          absb = absa;
        }

        if (std::abs(cdiff) < 4.4408920985006262E-16 * absb) {
          ndbl++;
          apnd = radiusRangeIn_data[1];
        } else if (cdiff > 0.0) {
          apnd = radiusRangeIn_data[0] + (ndbl - 1.0) * 0.5;
        } else {
          ndbl++;
        }

        if (ndbl >= 0.0) {
          idxkeep = (int)ndbl;
        } else {
          idxkeep = 0;
        }

        i3 = radiusRange->size[0] * radiusRange->size[1];
        radiusRange->size[0] = 1;
        radiusRange->size[1] = idxkeep;
        emxEnsureCapacity((emxArray__common *)radiusRange, i3, (int)sizeof
                          (double));
        if (idxkeep > 0) {
          radiusRange->data[0] = radiusRangeIn_data[0];
          if (idxkeep > 1) {
            radiusRange->data[idxkeep - 1] = apnd;
            jj = (idxkeep - 1) / 2;
            for (ixstart = 1; ixstart < jj; ixstart++) {
              ndbl = (double)ixstart * 0.5;
              radiusRange->data[ixstart] = radiusRangeIn_data[0] + ndbl;
              radiusRange->data[(idxkeep - ixstart) - 1] = apnd - ndbl;
            }

            if (jj << 1 == idxkeep - 1) {
              radiusRange->data[jj] = (radiusRangeIn_data[0] + apnd) / 2.0;
            } else {
              ndbl = (double)jj * 0.5;
              radiusRange->data[jj] = radiusRangeIn_data[0] + ndbl;
              radiusRange->data[jj + 1] = apnd - ndbl;
            }
          }
        }
      }
    } else {
      i3 = radiusRange->size[0] * radiusRange->size[1];
      radiusRange->size[0] = 1;
      radiusRange->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)radiusRange, i3, (int)sizeof(double));
      radiusRange->data[0] = radiusRangeIn_data[0];
    }

    emxInit_real_T(&lnR, 2);
    if (radiusRange->size[1] > 1) {
      i3 = lnR->size[0] * lnR->size[1];
      lnR->size[0] = 1;
      lnR->size[1] = radiusRange->size[1];
      emxEnsureCapacity((emxArray__common *)lnR, i3, (int)sizeof(double));
      ixstart = radiusRange->size[0] * radiusRange->size[1];
      for (i3 = 0; i3 < ixstart; i3++) {
        lnR->data[i3] = radiusRange->data[i3];
      }

      b_log(lnR);
      ndbl = lnR->data[lnR->size[1] - 1] - lnR->data[0];
      cdiff = lnR->data[0];
      i3 = lnR->size[0] * lnR->size[1];
      lnR->size[0] = 1;
      emxEnsureCapacity((emxArray__common *)lnR, i3, (int)sizeof(double));
      ixstart = lnR->size[1];
      for (i3 = 0; i3 < ixstart; i3++) {
        lnR->data[lnR->size[0] * i3] = (lnR->data[lnR->size[0] * i3] - cdiff) /
          ndbl * 2.0 * 3.1415926535897931 - 3.1415926535897931;
      }
    } else {
      i3 = lnR->size[0] * lnR->size[1];
      lnR->size[0] = 1;
      lnR->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)lnR, i3, (int)sizeof(double));
      lnR->data[0] = 0.0;
    }

    for (i3 = 0; i3 < 2; i3++) {
      radiusRangeIn_size[i3] = lnR->size[i3];
    }

    emxInit_creal_T1(&Opca, 2);
    emxInit_creal_T1(&y, 2);
    i3 = Opca->size[0] * Opca->size[1];
    Opca->size[0] = 1;
    Opca->size[1] = radiusRangeIn_size[1];
    emxEnsureCapacity((emxArray__common *)Opca, i3, (int)sizeof(creal_T));
    i3 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = lnR->size[1];
    emxEnsureCapacity((emxArray__common *)y, i3, (int)sizeof(creal_T));
    ixstart = lnR->size[0] * lnR->size[1];
    for (i3 = 0; i3 < ixstart; i3++) {
      y->data[i3].re = lnR->data[i3] * 0.0;
      y->data[i3].im = lnR->data[i3];
    }

    emxInit_creal_T1(&r1, 2);
    i3 = r1->size[0] * r1->size[1];
    r1->size[0] = 1;
    r1->size[1] = y->size[1];
    emxEnsureCapacity((emxArray__common *)r1, i3, (int)sizeof(creal_T));
    ixstart = y->size[0] * y->size[1];
    for (i3 = 0; i3 < ixstart; i3++) {
      r1->data[i3] = y->data[i3];
    }

    for (ixstart = 0; ixstart + 1 <= y->size[1]; ixstart++) {
      if (r1->data[ixstart].im == 0.0) {
        cdiff = std::exp(r1->data[ixstart].re);
        ndbl = 0.0;
      } else if (rtIsInf(r1->data[ixstart].im) && rtIsInf(r1->data[ixstart].re) &&
                 (r1->data[ixstart].re < 0.0)) {
        cdiff = 0.0;
        ndbl = 0.0;
      } else {
        ndbl = std::exp(r1->data[ixstart].re / 2.0);
        cdiff = ndbl * (ndbl * std::cos(r1->data[ixstart].im));
        ndbl *= ndbl * std::sin(r1->data[ixstart].im);
      }

      r1->data[ixstart].re = cdiff;
      r1->data[ixstart].im = ndbl;
    }

    emxFree_creal_T(&y);
    ixstart = r1->size[1];
    for (i3 = 0; i3 < ixstart; i3++) {
      Opca->data[Opca->size[0] * i3] = r1->data[r1->size[0] * i3];
    }

    emxFree_creal_T(&r1);
    i3 = Opca->size[0] * Opca->size[1];
    Opca->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)Opca, i3, (int)sizeof(creal_T));
    ixstart = Opca->size[0];
    jj = Opca->size[1];
    ixstart *= jj;
    for (i3 = 0; i3 < ixstart; i3++) {
      ndbl = Opca->data[i3].re;
      cdiff = Opca->data[i3].im;
      absa = 6.2831853071795862 * radiusRange->data[i3];
      if (cdiff == 0.0) {
        Opca->data[i3].re = ndbl / absa;
        Opca->data[i3].im = 0.0;
      } else if (ndbl == 0.0) {
        Opca->data[i3].re = 0.0;
        Opca->data[i3].im = cdiff / absa;
      } else {
        Opca->data[i3].re = ndbl / absa;
        Opca->data[i3].im = cdiff / absa;
      }
    }

    xcStep = std::floor(1.0E+6 / (double)radiusRange->size[1]);
    b_varargin_1 = Ex->size[0];
    memset(&accumMatrix[0], 0, 809600U * sizeof(creal_T));
    i3 = (int)(((double)Ex->size[0] + (xcStep - 1.0)) / xcStep);
    i = 0;
    emxInit_real_T1(&Ex_chunk, 1);
    emxInit_real_T1(&Ey_chunk, 1);
    emxInit_real_T1(&idxE_chunk, 1);
    emxInit_real32_T(&xc, 2);
    emxInit_real32_T(&yc, 2);
    emxInit_creal_T1(&w, 2);
    emxInit_boolean_T(&inside, 2);
    emxInit_boolean_T1(&rows_to_keep, 1);
    emxInit_int32_T(&xckeep, 1);
    emxInit_int32_T(&yckeep, 1);
    emxInit_creal_T(&wkeep, 1);
    while (i <= i3 - 1) {
      b_i = 1.0 + (double)i * xcStep;
      ndbl = (b_i + xcStep) - 1.0;
      if (ndbl <= b_varargin_1) {
        minval = ndbl;
      } else {
        minval = b_varargin_1;
      }

      if (rtIsNaN(b_i) || rtIsNaN(minval)) {
        jj = lnR->size[0] * lnR->size[1];
        lnR->size[0] = 1;
        lnR->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)lnR, jj, (int)sizeof(double));
        lnR->data[0] = rtNaN;
      } else if (minval < b_i) {
        jj = lnR->size[0] * lnR->size[1];
        lnR->size[0] = 1;
        lnR->size[1] = 0;
        emxEnsureCapacity((emxArray__common *)lnR, jj, (int)sizeof(double));
      } else if ((rtIsInf(b_i) || rtIsInf(minval)) && (b_i == minval)) {
        jj = lnR->size[0] * lnR->size[1];
        lnR->size[0] = 1;
        lnR->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)lnR, jj, (int)sizeof(double));
        lnR->data[0] = rtNaN;
      } else if (b_i == b_i) {
        jj = lnR->size[0] * lnR->size[1];
        lnR->size[0] = 1;
        lnR->size[1] = (int)(minval - b_i) + 1;
        emxEnsureCapacity((emxArray__common *)lnR, jj, (int)sizeof(double));
        ixstart = (int)(minval - b_i);
        for (jj = 0; jj <= ixstart; jj++) {
          lnR->data[lnR->size[0] * jj] = b_i + (double)jj;
        }
      } else {
        ndbl = std::floor((minval - b_i) + 0.5);
        apnd = b_i + ndbl;
        cdiff = apnd - minval;
        absa = std::abs(b_i);
        absb = std::abs(minval);
        if ((absa >= absb) || rtIsNaN(absb)) {
          absb = absa;
        }

        if (std::abs(cdiff) < 4.4408920985006262E-16 * absb) {
          ndbl++;
          apnd = minval;
        } else if (cdiff > 0.0) {
          apnd = b_i + (ndbl - 1.0);
        } else {
          ndbl++;
        }

        if (ndbl >= 0.0) {
          idxkeep = (int)ndbl;
        } else {
          idxkeep = 0;
        }

        jj = lnR->size[0] * lnR->size[1];
        lnR->size[0] = 1;
        lnR->size[1] = idxkeep;
        emxEnsureCapacity((emxArray__common *)lnR, jj, (int)sizeof(double));
        if (idxkeep > 0) {
          lnR->data[0] = b_i;
          if (idxkeep > 1) {
            lnR->data[idxkeep - 1] = apnd;
            jj = (idxkeep - 1) / 2;
            for (ixstart = 1; ixstart < jj; ixstart++) {
              lnR->data[ixstart] = b_i + (double)ixstart;
              lnR->data[(idxkeep - ixstart) - 1] = apnd - (double)ixstart;
            }

            if (jj << 1 == idxkeep - 1) {
              lnR->data[jj] = (b_i + apnd) / 2.0;
            } else {
              lnR->data[jj] = b_i + (double)jj;
              lnR->data[jj + 1] = apnd - (double)jj;
            }
          }
        }
      }

      jj = Ex_chunk->size[0];
      Ex_chunk->size[0] = lnR->size[1];
      emxEnsureCapacity((emxArray__common *)Ex_chunk, jj, (int)sizeof(double));
      jj = Ey_chunk->size[0];
      Ey_chunk->size[0] = lnR->size[1];
      emxEnsureCapacity((emxArray__common *)Ey_chunk, jj, (int)sizeof(double));
      jj = idxE_chunk->size[0];
      idxE_chunk->size[0] = lnR->size[1];
      emxEnsureCapacity((emxArray__common *)idxE_chunk, jj, (int)sizeof(double));
      ixstart = (int)b_i - 1;
      for (idx = 0; idx < lnR->size[1]; idx++) {
        Ex_chunk->data[idx] = Ex->data[ixstart];
        Ey_chunk->data[idx] = Ey->data[ixstart];
        idxE_chunk->data[idx] = ndx->data[ixstart];
        ixstart++;
      }

      jj = xc->size[0] * xc->size[1];
      xc->size[0] = idxE_chunk->size[0];
      xc->size[1] = radiusRange->size[1];
      emxEnsureCapacity((emxArray__common *)xc, jj, (int)sizeof(float));
      jj = yc->size[0] * yc->size[1];
      yc->size[0] = idxE_chunk->size[0];
      yc->size[1] = radiusRange->size[1];
      emxEnsureCapacity((emxArray__common *)yc, jj, (int)sizeof(float));
      jj = w->size[0] * w->size[1];
      w->size[0] = idxE_chunk->size[0];
      w->size[1] = radiusRange->size[1];
      emxEnsureCapacity((emxArray__common *)w, jj, (int)sizeof(creal_T));
      jj = inside->size[0] * inside->size[1];
      inside->size[0] = idxE_chunk->size[0];
      inside->size[1] = radiusRange->size[1];
      emxEnsureCapacity((emxArray__common *)inside, jj, (int)sizeof(boolean_T));
      jj = rows_to_keep->size[0];
      rows_to_keep->size[0] = idxE_chunk->size[0];
      emxEnsureCapacity((emxArray__common *)rows_to_keep, jj, (int)sizeof
                        (boolean_T));
      ixstart = idxE_chunk->size[0];
      for (jj = 0; jj < ixstart; jj++) {
        rows_to_keep->data[jj] = false;
      }

      for (ixstart = 0; ixstart < radiusRange->size[1]; ixstart++) {
        for (jj = 0; jj < idxE_chunk->size[0]; jj++) {
          t = (float)Ex_chunk->data[jj] + (float)-radiusRange->data[ixstart] *
            (Gx[(int)idxE_chunk->data[jj] - 1] / gradientImg[(int)
             idxE_chunk->data[jj] - 1]);
          if (t > 0.0F) {
            xc->data[jj + xc->size[0] * ixstart] = t + 0.5F;
          } else if (t < 0.0F) {
            xc->data[jj + xc->size[0] * ixstart] = t - 0.5F;
          } else {
            xc->data[jj + xc->size[0] * ixstart] = 0.0F;
          }

          t = (float)Ey_chunk->data[jj] + (float)-radiusRange->data[ixstart] *
            (Gy[(int)idxE_chunk->data[jj] - 1] / gradientImg[(int)
             idxE_chunk->data[jj] - 1]);
          if (t > 0.0F) {
            yc->data[jj + yc->size[0] * ixstart] = t + 0.5F;
          } else if (t < 0.0F) {
            yc->data[jj + yc->size[0] * ixstart] = t - 0.5F;
          } else {
            yc->data[jj + yc->size[0] * ixstart] = 0.0F;
          }

          w->data[jj + w->size[0] * ixstart] = Opca->data[Opca->size[0] *
            ixstart];
          inside->data[jj + inside->size[0] * ixstart] = ((xc->data[jj +
            xc->size[0] * ixstart] >= 1.0F) && (xc->data[jj + xc->size[0] *
            ixstart] <= 1100.0F) && (yc->data[jj + yc->size[0] * ixstart] >=
            1.0F) && (yc->data[jj + yc->size[0] * ixstart] < 736.0F));
          if (inside->data[jj + inside->size[0] * ixstart]) {
            rows_to_keep->data[jj] = true;
          }
        }
      }

      jj = xckeep->size[0];
      xckeep->size[0] = xc->size[0] * xc->size[1];
      emxEnsureCapacity((emxArray__common *)xckeep, jj, (int)sizeof(int));
      jj = yckeep->size[0];
      yckeep->size[0] = yc->size[0] * yc->size[1];
      emxEnsureCapacity((emxArray__common *)yckeep, jj, (int)sizeof(int));
      jj = wkeep->size[0];
      wkeep->size[0] = w->size[0] * w->size[1];
      emxEnsureCapacity((emxArray__common *)wkeep, jj, (int)sizeof(creal_T));
      idxkeep = -1;
      for (ixstart = 0; ixstart < radiusRange->size[1]; ixstart++) {
        for (jj = 0; jj < idxE_chunk->size[0]; jj++) {
          if (rows_to_keep->data[jj] && inside->data[jj + inside->size[0] *
              ixstart]) {
            idxkeep++;
            xckeep->data[idxkeep] = (int)xc->data[jj + xc->size[0] * ixstart];
            yckeep->data[idxkeep] = (int)yc->data[jj + yc->size[0] * ixstart];
            wkeep->data[idxkeep] = w->data[jj + w->size[0] * ixstart];
          }
        }
      }

      memset(&out[0], 0, 809600U * sizeof(creal_T));
      for (idx = 0; idx + 1 <= idxkeep + 1; idx++) {
        out[(yckeep->data[idx] + 736 * (xckeep->data[idx] - 1)) - 1].re +=
          wkeep->data[idx].re;
        out[(yckeep->data[idx] + 736 * (xckeep->data[idx] - 1)) - 1].im +=
          wkeep->data[idx].im;
      }

      for (jj = 0; jj < 809600; jj++) {
        accumMatrix[jj].re += out[jj].re;
        accumMatrix[jj].im += out[jj].im;
      }

      i++;
    }

    emxFree_int32_T(&ndx);
    emxFree_real_T(&Ex);
    emxFree_real_T(&Ey);
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
    emxFree_real_T(&lnR);
    emxFree_real_T(&radiusRange);
  }
}

//
// File trailer for chaccum.cpp
//
// [EOF]
//
