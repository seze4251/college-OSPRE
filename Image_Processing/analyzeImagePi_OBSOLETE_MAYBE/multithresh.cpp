//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: multithresh.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "multithresh.h"
#include "analyzeImage_emxutil.h"
#include "nullAssignment.h"
#include "unique.h"
#include "sortIdx.h"
#include "isfinite.h"
#include "sum.h"
#include "imhist.h"
#include "im2uint8.h"

// Function Definitions

//
// Arguments    : const emxArray_real32_T *uniqueVals
//                emxArray_real32_T *thresh
// Return Type  : void
//
void b_getDegenerateThresholds(const emxArray_real32_T *uniqueVals,
  emxArray_real32_T *thresh)
{
  int i25;
  int loop_ub;
  if (uniqueVals->size[1] == 0) {
    i25 = thresh->size[0] * thresh->size[1];
    thresh->size[0] = 1;
    thresh->size[1] = 1;
    emxEnsureCapacity((emxArray__common *)thresh, i25, sizeof(float));
    thresh->data[0] = 1.0F;
  } else {
    i25 = thresh->size[0] * thresh->size[1];
    thresh->size[0] = 1;
    thresh->size[1] = uniqueVals->size[1];
    emxEnsureCapacity((emxArray__common *)thresh, i25, sizeof(float));
    loop_ub = uniqueVals->size[0] * uniqueVals->size[1];
    for (i25 = 0; i25 < loop_ub; i25++) {
      thresh->data[i25] = uniqueVals->data[i25];
    }
  }
}

//
// Arguments    : const emxArray_real32_T *A
//                boolean_T *isDegenerate
//                emxArray_real32_T *uniqueVals
// Return Type  : void
//
void checkForDegenerateInput(const emxArray_real32_T *A, boolean_T *isDegenerate,
  emxArray_real32_T *uniqueVals)
{
  emxArray_real32_T *b;
  emxArray_int32_T *idx;
  int b_A[1];
  emxArray_real32_T c_A;
  int khi;
  int nInf;
  int k;
  int nNaN;
  int nb;
  float x;
  int exitg1;
  float absxk;
  int i23;
  int exponent;
  boolean_T b_isDegenerate;
  emxArray_boolean_T *r8;
  emxArray_boolean_T *r9;
  emxArray_boolean_T *r10;
  emxInit_real32_T1(&b, 1);
  emxInit_int32_T(&idx, 1);
  b_A[0] = A->size[0] * A->size[1];
  c_A = *A;
  c_A.size = (int *)&b_A;
  c_A.numDimensions = 1;
  sortIdx(&c_A, idx);
  khi = A->size[0] * A->size[1];
  nInf = b->size[0];
  b->size[0] = khi;
  emxEnsureCapacity((emxArray__common *)b, nInf, sizeof(float));
  for (k = 0; k + 1 <= A->size[0] * A->size[1]; k++) {
    b->data[k] = A->data[idx->data[k] - 1];
  }

  emxFree_int32_T(&idx);
  count_nonfinites(b, A->size[0] * A->size[1], &k, &khi, &nInf, &nNaN);
  nb = -1;
  if (k > 0) {
    nb = 0;
  }

  khi += k;
  while (k + 1 <= khi) {
    x = b->data[k];
    do {
      exitg1 = 0;
      k++;
      if (k + 1 > khi) {
        exitg1 = 1;
      } else {
        absxk = std::abs(x / 2.0F);
        if ((!rtIsInfF(absxk)) && (!rtIsNaNF(absxk))) {
          if (absxk <= 1.17549435E-38F) {
            absxk = 1.4013E-45F;
          } else {
            std::frexp(absxk, &exponent);
            absxk = std::ldexp(1.0F, exponent - 24);
          }
        } else {
          absxk = ((real32_T)rtNaN);
        }

        if ((std::abs(x - b->data[k]) < absxk) || (rtIsInfF(b->data[k]) &&
             rtIsInfF(x) && ((b->data[k] > 0.0F) == (x > 0.0F)))) {
          b_isDegenerate = true;
        } else {
          b_isDegenerate = false;
        }

        if (!b_isDegenerate) {
          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);

    nb++;
    b->data[nb] = x;
  }

  if (nInf > 0) {
    nb++;
    b->data[nb] = b->data[khi];
  }

  k = khi + nInf;
  for (khi = 1; khi <= nNaN; khi++) {
    nb++;
    b->data[nb] = b->data[(k + khi) - 1];
  }

  nInf = b->size[0];
  if (1 > nb + 1) {
    i23 = -1;
  } else {
    i23 = nb;
  }

  b->size[0] = i23 + 1;
  emxEnsureCapacity((emxArray__common *)b, nInf, sizeof(float));
  nInf = uniqueVals->size[0] * uniqueVals->size[1];
  uniqueVals->size[0] = 1;
  uniqueVals->size[1] = b->size[0];
  emxEnsureCapacity((emxArray__common *)uniqueVals, nInf, sizeof(float));
  khi = b->size[0];
  for (nInf = 0; nInf < khi; nInf++) {
    uniqueVals->data[uniqueVals->size[0] * nInf] = b->data[nInf];
  }

  emxFree_real32_T(&b);
  emxInit_boolean_T(&r8, 2);
  nInf = r8->size[0] * r8->size[1];
  r8->size[0] = 1;
  r8->size[1] = uniqueVals->size[1];
  emxEnsureCapacity((emxArray__common *)r8, nInf, sizeof(boolean_T));
  khi = uniqueVals->size[0] * uniqueVals->size[1];
  for (nInf = 0; nInf < khi; nInf++) {
    r8->data[nInf] = rtIsInfF(uniqueVals->data[nInf]);
  }

  emxInit_boolean_T(&r9, 2);
  nInf = r9->size[0] * r9->size[1];
  r9->size[0] = 1;
  r9->size[1] = uniqueVals->size[1];
  emxEnsureCapacity((emxArray__common *)r9, nInf, sizeof(boolean_T));
  khi = uniqueVals->size[0] * uniqueVals->size[1];
  for (nInf = 0; nInf < khi; nInf++) {
    r9->data[nInf] = rtIsNaNF(uniqueVals->data[nInf]);
  }

  emxInit_boolean_T(&r10, 2);
  nInf = r10->size[0] * r10->size[1];
  r10->size[0] = 1;
  r10->size[1] = r8->size[1];
  emxEnsureCapacity((emxArray__common *)r10, nInf, sizeof(boolean_T));
  khi = r8->size[0] * r8->size[1];
  for (nInf = 0; nInf < khi; nInf++) {
    r10->data[nInf] = (r8->data[nInf] || r9->data[nInf]);
  }

  emxFree_boolean_T(&r9);
  emxFree_boolean_T(&r8);
  nullAssignment(uniqueVals, r10);
  b_isDegenerate = (uniqueVals->size[1] <= 1);
  *isDegenerate = b_isDegenerate;
  emxFree_boolean_T(&r10);
}

//
// Arguments    : const emxArray_real32_T *uniqueVals
//                emxArray_real32_T *thresh
// Return Type  : void
//
void getDegenerateThresholds(const emxArray_real32_T *uniqueVals,
  emxArray_real32_T *thresh)
{
  int i22;
  int loop_ub;
  if ((uniqueVals->size[0] == 0) || (uniqueVals->size[1] == 0)) {
    i22 = thresh->size[0] * thresh->size[1];
    thresh->size[0] = 1;
    thresh->size[1] = 1;
    emxEnsureCapacity((emxArray__common *)thresh, i22, sizeof(float));
    thresh->data[0] = 1.0F;
  } else {
    i22 = thresh->size[0] * thresh->size[1];
    thresh->size[0] = uniqueVals->size[0];
    thresh->size[1] = uniqueVals->size[1];
    emxEnsureCapacity((emxArray__common *)thresh, i22, sizeof(float));
    loop_ub = uniqueVals->size[0] * uniqueVals->size[1];
    for (i22 = 0; i22 < loop_ub; i22++) {
      thresh->data[i22] = uniqueVals->data[i22];
    }
  }
}

//
// Arguments    : emxArray_real32_T *A
//                double p[256]
//                float *minA
//                float *maxA
//                boolean_T *emptyp
// Return Type  : void
//
void getpdf(emxArray_real32_T *A, double p[256], float *minA, float *maxA,
            boolean_T *emptyp)
{
  int idx;
  int N;
  int ix;
  float B;
  boolean_T exitg1;
  emxArray_boolean_T *nans;
  emxArray_int32_T *r7;
  emxArray_real32_T *b_A;
  emxArray_uint8_T *c_A;
  double y;
  *emptyp = true;
  idx = 1;
  N = A->size[0] * A->size[1];
  while ((idx <= N) && (!c_isfinite(A->data[idx - 1]))) {
    idx++;
  }

  if (idx <= N) {
    *minA = A->data[idx - 1];
    *maxA = A->data[idx - 1];
    while (idx + 1 <= N) {
      if ((A->data[idx] < *minA) && c_isfinite(A->data[idx])) {
        *minA = A->data[idx];
      } else {
        if ((A->data[idx] > *maxA) && c_isfinite(A->data[idx])) {
          *maxA = A->data[idx];
        }
      }

      idx++;
    }

    if (!(*minA == *maxA)) {
      B = *maxA - *minA;
      N = A->size[0] * A->size[1];
      emxEnsureCapacity((emxArray__common *)A, N, sizeof(float));
      idx = A->size[0];
      N = A->size[1];
      idx *= N;
      for (N = 0; N < idx; N++) {
        A->data[N] = (A->data[N] - *minA) / B;
      }

      emxInit_boolean_T1(&nans, 1);
      N = nans->size[0];
      nans->size[0] = A->size[0] * A->size[1];
      emxEnsureCapacity((emxArray__common *)nans, N, sizeof(boolean_T));
      idx = A->size[0] * A->size[1];
      for (N = 0; N < idx; N++) {
        nans->data[N] = rtIsNaNF(A->data[N]);
      }

      ix = nans->size[0];
      idx = 0;
      for (N = 0; N < ix; N++) {
        if (!nans->data[N]) {
          idx++;
        }
      }

      if (!(idx == 0)) {
        ix = nans->size[0] - 1;
        idx = 0;
        for (N = 0; N <= ix; N++) {
          if (!nans->data[N]) {
            idx++;
          }
        }

        emxInit_int32_T(&r7, 1);
        N = r7->size[0];
        r7->size[0] = idx;
        emxEnsureCapacity((emxArray__common *)r7, N, sizeof(int));
        idx = 0;
        for (N = 0; N <= ix; N++) {
          if (!nans->data[N]) {
            r7->data[idx] = N + 1;
            idx++;
          }
        }

        emxInit_real32_T1(&b_A, 1);
        N = b_A->size[0];
        b_A->size[0] = r7->size[0];
        emxEnsureCapacity((emxArray__common *)b_A, N, sizeof(float));
        idx = r7->size[0];
        for (N = 0; N < idx; N++) {
          b_A->data[N] = A->data[r7->data[N] - 1];
        }

        emxFree_int32_T(&r7);
        emxInit_uint8_T1(&c_A, 1);
        im2uint8(b_A, c_A);
        b_imhist(c_A, p);
        y = b_sum(p);
        emxFree_real32_T(&b_A);
        emxFree_uint8_T(&c_A);
        for (N = 0; N < 256; N++) {
          p[N] /= y;
        }

        *emptyp = false;
      }

      emxFree_boolean_T(&nans);
    }
  } else {
    idx = 1;
    N = A->size[0] * A->size[1];
    *minA = A->data[0];
    if (A->size[0] * A->size[1] > 1) {
      if (rtIsNaNF(A->data[0])) {
        ix = 2;
        exitg1 = false;
        while ((!exitg1) && (ix <= N)) {
          idx = ix;
          if (!rtIsNaNF(A->data[ix - 1])) {
            *minA = A->data[ix - 1];
            exitg1 = true;
          } else {
            ix++;
          }
        }
      }

      if (idx < A->size[0] * A->size[1]) {
        while (idx + 1 <= N) {
          if (A->data[idx] < *minA) {
            *minA = A->data[idx];
          }

          idx++;
        }
      }
    }

    idx = 1;
    N = A->size[0] * A->size[1];
    *maxA = A->data[0];
    if (A->size[0] * A->size[1] > 1) {
      if (rtIsNaNF(A->data[0])) {
        ix = 2;
        exitg1 = false;
        while ((!exitg1) && (ix <= N)) {
          idx = ix;
          if (!rtIsNaNF(A->data[ix - 1])) {
            *maxA = A->data[ix - 1];
            exitg1 = true;
          } else {
            ix++;
          }
        }
      }

      if (idx < A->size[0] * A->size[1]) {
        while (idx + 1 <= N) {
          if (A->data[idx] > *maxA) {
            *maxA = A->data[idx];
          }

          idx++;
        }
      }
    }
  }
}

//
// Arguments    : const emxArray_real_T *thresh
//                float minA
//                float maxA
//                emxArray_real32_T *sclThresh
// Return Type  : void
//
void map2OriginalScale(const emxArray_real_T *thresh, float minA, float maxA,
  emxArray_real32_T *sclThresh)
{
  double b;
  int i26;
  int loop_ub;
  b = (double)maxA - minA;
  i26 = sclThresh->size[0] * sclThresh->size[1];
  sclThresh->size[0] = 1;
  sclThresh->size[1] = thresh->size[1];
  emxEnsureCapacity((emxArray__common *)sclThresh, i26, sizeof(float));
  loop_ub = thresh->size[0] * thresh->size[1];
  for (i26 = 0; i26 < loop_ub; i26++) {
    sclThresh->data[i26] = (float)(minA + thresh->data[i26] / 255.0 * b);
  }
}

//
// File trailer for multithresh.cpp
//
// [EOF]
//
