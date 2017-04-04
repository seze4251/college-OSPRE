//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sort1.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 14-Feb-2017 14:49:57
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "sort1.h"
#include "analyzeImage_emxutil.h"
#include "sortIdx.h"

// Function Definitions

//
// Arguments    : emxArray_real_T *x
//                emxArray_int32_T *idx
// Return Type  : void
//
void sort(emxArray_real_T *x, emxArray_int32_T *idx)
{
  int iv6[2];
  int b;
  int i;
  emxArray_real_T *b_x;
  emxArray_int32_T *b_idx;
  double x4[4];
  int idx4[4];
  emxArray_int32_T *iwork;
  int preSortLevel;
  emxArray_real_T *xwork;
  int nNaNs;
  int ib;
  int k;
  int wOffset;
  signed char perm[4];
  int nNonNaN;
  int i4;
  int nBlocks;
  int b_iwork[256];
  double b_xwork[256];
  int bLen;
  int bLen2;
  int nPairs;
  int exitg1;
  for (b = 0; b < 2; b++) {
    iv6[b] = x->size[b];
  }

  b = idx->size[0] * idx->size[1];
  idx->size[0] = iv6[0];
  idx->size[1] = 1;
  emxEnsureCapacity((emxArray__common *)idx, b, (int)sizeof(int));
  i = iv6[0];
  for (b = 0; b < i; b++) {
    idx->data[b] = 0;
  }

  emxInit_real_T1(&b_x, 1);
  i = x->size[0];
  b = b_x->size[0];
  b_x->size[0] = i;
  emxEnsureCapacity((emxArray__common *)b_x, b, (int)sizeof(double));
  for (b = 0; b < i; b++) {
    b_x->data[b] = x->data[b];
  }

  emxInit_int32_T(&b_idx, 1);
  i = idx->size[0];
  b = b_idx->size[0];
  b_idx->size[0] = i;
  emxEnsureCapacity((emxArray__common *)b_idx, b, (int)sizeof(int));
  for (b = 0; b < i; b++) {
    b_idx->data[b] = idx->data[b];
  }

  b = x->size[0];
  for (i = 0; i < 4; i++) {
    x4[i] = 0.0;
    idx4[i] = 0;
  }

  emxInit_int32_T(&iwork, 1);
  preSortLevel = idx->size[0];
  i = iwork->size[0];
  iwork->size[0] = preSortLevel;
  emxEnsureCapacity((emxArray__common *)iwork, i, (int)sizeof(int));
  i = iwork->size[0];
  preSortLevel = iwork->size[0];
  iwork->size[0] = i;
  emxEnsureCapacity((emxArray__common *)iwork, preSortLevel, (int)sizeof(int));
  for (preSortLevel = 0; preSortLevel < i; preSortLevel++) {
    iwork->data[preSortLevel] = 0;
  }

  emxInit_real_T1(&xwork, 1);
  preSortLevel = x->size[0];
  i = xwork->size[0];
  xwork->size[0] = preSortLevel;
  emxEnsureCapacity((emxArray__common *)xwork, i, (int)sizeof(double));
  i = xwork->size[0];
  preSortLevel = xwork->size[0];
  xwork->size[0] = i;
  emxEnsureCapacity((emxArray__common *)xwork, preSortLevel, (int)sizeof(double));
  for (preSortLevel = 0; preSortLevel < i; preSortLevel++) {
    xwork->data[preSortLevel] = 0.0;
  }

  nNaNs = 0;
  ib = 0;
  for (k = 0; k + 1 <= b; k++) {
    if (rtIsNaN(b_x->data[k])) {
      b_idx->data[(b - nNaNs) - 1] = k + 1;
      xwork->data[(b - nNaNs) - 1] = b_x->data[k];
      nNaNs++;
    } else {
      ib++;
      idx4[ib - 1] = k + 1;
      x4[ib - 1] = b_x->data[k];
      if (ib == 4) {
        i = k - nNaNs;
        if (x4[0] >= x4[1]) {
          preSortLevel = 1;
          ib = 2;
        } else {
          preSortLevel = 2;
          ib = 1;
        }

        if (x4[2] >= x4[3]) {
          wOffset = 3;
          i4 = 4;
        } else {
          wOffset = 4;
          i4 = 3;
        }

        if (x4[preSortLevel - 1] >= x4[wOffset - 1]) {
          if (x4[ib - 1] >= x4[wOffset - 1]) {
            perm[0] = (signed char)preSortLevel;
            perm[1] = (signed char)ib;
            perm[2] = (signed char)wOffset;
            perm[3] = (signed char)i4;
          } else if (x4[ib - 1] >= x4[i4 - 1]) {
            perm[0] = (signed char)preSortLevel;
            perm[1] = (signed char)wOffset;
            perm[2] = (signed char)ib;
            perm[3] = (signed char)i4;
          } else {
            perm[0] = (signed char)preSortLevel;
            perm[1] = (signed char)wOffset;
            perm[2] = (signed char)i4;
            perm[3] = (signed char)ib;
          }
        } else if (x4[preSortLevel - 1] >= x4[i4 - 1]) {
          if (x4[ib - 1] >= x4[i4 - 1]) {
            perm[0] = (signed char)wOffset;
            perm[1] = (signed char)preSortLevel;
            perm[2] = (signed char)ib;
            perm[3] = (signed char)i4;
          } else {
            perm[0] = (signed char)wOffset;
            perm[1] = (signed char)preSortLevel;
            perm[2] = (signed char)i4;
            perm[3] = (signed char)ib;
          }
        } else {
          perm[0] = (signed char)wOffset;
          perm[1] = (signed char)i4;
          perm[2] = (signed char)preSortLevel;
          perm[3] = (signed char)ib;
        }

        b_idx->data[i - 3] = idx4[perm[0] - 1];
        b_idx->data[i - 2] = idx4[perm[1] - 1];
        b_idx->data[i - 1] = idx4[perm[2] - 1];
        b_idx->data[i] = idx4[perm[3] - 1];
        b_x->data[i - 3] = x4[perm[0] - 1];
        b_x->data[i - 2] = x4[perm[1] - 1];
        b_x->data[i - 1] = x4[perm[2] - 1];
        b_x->data[i] = x4[perm[3] - 1];
        ib = 0;
      }
    }
  }

  preSortLevel = x->size[0] - 1;
  wOffset = preSortLevel - nNaNs;
  if (ib > 0) {
    for (i = 0; i < 4; i++) {
      perm[i] = 0;
    }

    if (ib == 1) {
      perm[0] = 1;
    } else if (ib == 2) {
      if (x4[0] >= x4[1]) {
        perm[0] = 1;
        perm[1] = 2;
      } else {
        perm[0] = 2;
        perm[1] = 1;
      }
    } else if (x4[0] >= x4[1]) {
      if (x4[1] >= x4[2]) {
        perm[0] = 1;
        perm[1] = 2;
        perm[2] = 3;
      } else if (x4[0] >= x4[2]) {
        perm[0] = 1;
        perm[1] = 3;
        perm[2] = 2;
      } else {
        perm[0] = 3;
        perm[1] = 1;
        perm[2] = 2;
      }
    } else if (x4[0] >= x4[2]) {
      perm[0] = 2;
      perm[1] = 1;
      perm[2] = 3;
    } else if (x4[1] >= x4[2]) {
      perm[0] = 2;
      perm[1] = 3;
      perm[2] = 1;
    } else {
      perm[0] = 3;
      perm[1] = 2;
      perm[2] = 1;
    }

    for (k = 1; k <= ib; k++) {
      b_idx->data[(wOffset - ib) + k] = idx4[perm[k - 1] - 1];
      b_x->data[(wOffset - ib) + k] = x4[perm[k - 1] - 1];
    }
  }

  i = nNaNs >> 1;
  for (k = 1; k <= i; k++) {
    preSortLevel = b_idx->data[wOffset + k];
    b_idx->data[wOffset + k] = b_idx->data[b - k];
    b_idx->data[b - k] = preSortLevel;
    b_x->data[wOffset + k] = xwork->data[b - k];
    b_x->data[b - k] = xwork->data[wOffset + k];
  }

  if ((nNaNs & 1) != 0) {
    b_x->data[(wOffset + i) + 1] = xwork->data[(wOffset + i) + 1];
  }

  b = x->size[0];
  nNonNaN = b - nNaNs;
  preSortLevel = 2;
  if (nNonNaN > 1) {
    b = x->size[0];
    if (b >= 256) {
      nBlocks = nNonNaN >> 8;
      if (nBlocks > 0) {
        for (wOffset = 1; wOffset <= nBlocks; wOffset++) {
          i4 = ((wOffset - 1) << 8) - 1;
          for (b = 0; b < 6; b++) {
            bLen = 1 << (b + 2);
            bLen2 = bLen << 1;
            nPairs = 256 >> (b + 3);
            for (k = 1; k <= nPairs; k++) {
              preSortLevel = i4 + (k - 1) * bLen2;
              for (i = 1; i <= bLen2; i++) {
                b_iwork[i - 1] = b_idx->data[preSortLevel + i];
                b_xwork[i - 1] = b_x->data[preSortLevel + i];
              }

              ib = 0;
              i = bLen;
              do {
                exitg1 = 0;
                preSortLevel++;
                if (b_xwork[ib] >= b_xwork[i]) {
                  b_idx->data[preSortLevel] = b_iwork[ib];
                  b_x->data[preSortLevel] = b_xwork[ib];
                  if (ib + 1 < bLen) {
                    ib++;
                  } else {
                    exitg1 = 1;
                  }
                } else {
                  b_idx->data[preSortLevel] = b_iwork[i];
                  b_x->data[preSortLevel] = b_xwork[i];
                  if (i + 1 < bLen2) {
                    i++;
                  } else {
                    i = preSortLevel - ib;
                    while (ib + 1 <= bLen) {
                      b_idx->data[(i + ib) + 1] = b_iwork[ib];
                      b_x->data[(i + ib) + 1] = b_xwork[ib];
                      ib++;
                    }

                    exitg1 = 1;
                  }
                }
              } while (exitg1 == 0);
            }
          }
        }

        i = nBlocks << 8;
        preSortLevel = nNonNaN - i;
        if (preSortLevel > 0) {
          merge_block(b_idx, b_x, i, preSortLevel, 2, iwork, xwork);
        }

        preSortLevel = 8;
      }
    }

    merge_block(b_idx, b_x, 0, nNonNaN, preSortLevel, iwork, xwork);
  }

  if ((nNaNs > 0) && (nNonNaN > 0)) {
    for (k = 0; k + 1 <= nNaNs; k++) {
      xwork->data[k] = b_x->data[nNonNaN + k];
      iwork->data[k] = b_idx->data[nNonNaN + k];
    }

    for (k = nNonNaN - 1; k + 1 > 0; k--) {
      b_x->data[nNaNs + k] = b_x->data[k];
      b_idx->data[nNaNs + k] = b_idx->data[k];
    }

    for (k = 0; k + 1 <= nNaNs; k++) {
      b_x->data[k] = xwork->data[k];
      b_idx->data[k] = iwork->data[k];
    }
  }

  emxFree_real_T(&xwork);
  emxFree_int32_T(&iwork);
  i = b_idx->size[0];
  for (b = 0; b < i; b++) {
    idx->data[b] = b_idx->data[b];
  }

  emxFree_int32_T(&b_idx);
  i = b_x->size[0];
  for (b = 0; b < i; b++) {
    x->data[b] = b_x->data[b];
  }

  emxFree_real_T(&b_x);
}

//
// File trailer for sort1.cpp
//
// [EOF]
//
