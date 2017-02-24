//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mergesort.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 14-Feb-2017 14:22:46
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "mergesort.h"
#include "analyzeImage_emxutil.h"

// Function Definitions

//
// Arguments    : emxArray_int32_T *idx
//                const emxArray_real32_T *x
//                int n
// Return Type  : void
//
void b_mergesort(emxArray_int32_T *idx, const emxArray_real32_T *x, int n)
{
  emxArray_int32_T *iwork;
  int k;
  boolean_T p;
  int i;
  int i2;
  int j;
  int pEnd;
  int b_p;
  int q;
  int qEnd;
  int kEnd;
  emxInit_int32_T(&iwork, 1);
  k = iwork->size[0];
  iwork->size[0] = idx->size[0];
  emxEnsureCapacity((emxArray__common *)iwork, k, (int)sizeof(int));
  for (k = 1; k <= n - 1; k += 2) {
    if ((x->data[k - 1] <= x->data[k]) || rtIsNaNF(x->data[k])) {
      p = true;
    } else {
      p = false;
    }

    if (p) {
      idx->data[k - 1] = k;
      idx->data[k] = k + 1;
    } else {
      idx->data[k - 1] = k + 1;
      idx->data[k] = k;
    }
  }

  if ((n & 1) != 0) {
    idx->data[n - 1] = n;
  }

  i = 2;
  while (i < n) {
    i2 = i << 1;
    j = 1;
    for (pEnd = 1 + i; pEnd < n + 1; pEnd = qEnd + i) {
      b_p = j;
      q = pEnd - 1;
      qEnd = j + i2;
      if (qEnd > n + 1) {
        qEnd = n + 1;
      }

      k = 0;
      kEnd = qEnd - j;
      while (k + 1 <= kEnd) {
        if ((x->data[idx->data[b_p - 1] - 1] <= x->data[idx->data[q] - 1]) ||
            rtIsNaNF(x->data[idx->data[q] - 1])) {
          p = true;
        } else {
          p = false;
        }

        if (p) {
          iwork->data[k] = idx->data[b_p - 1];
          b_p++;
          if (b_p == pEnd) {
            while (q + 1 < qEnd) {
              k++;
              iwork->data[k] = idx->data[q];
              q++;
            }
          }
        } else {
          iwork->data[k] = idx->data[q];
          q++;
          if (q + 1 == qEnd) {
            while (b_p < pEnd) {
              k++;
              iwork->data[k] = idx->data[b_p - 1];
              b_p++;
            }
          }
        }

        k++;
      }

      for (k = 0; k + 1 <= kEnd; k++) {
        idx->data[(j + k) - 1] = iwork->data[k];
      }

      j = qEnd;
    }

    i = i2;
  }

  emxFree_int32_T(&iwork);
}

//
// File trailer for mergesort.cpp
//
// [EOF]
//
