//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sort1.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
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
  int bLen;
  int iv6[2];
  int ib;
  emxArray_int32_T *b_idx;
  emxArray_real_T *b_x;
  int b;
  int i;
  emxArray_int32_T *iwork;
  double x4[4];
  int idx4[4];
  emxArray_real_T *xwork;
  int nNaNs;
  int k;
  int wOffset;
  signed char perm[4];
  int nNonNaN;
  int i3;
  int i4;
  int nBlocks;
  int bLen2;
  int nPairs;
  int b_iwork[256];
  double b_xwork[256];
  int exitg1;
  for (bLen = 0; bLen < 2; bLen++) {
    iv6[bLen] = x->size[bLen];
  }

  bLen = idx->size[0] * idx->size[1];
  idx->size[0] = iv6[0];
  idx->size[1] = 1;
  emxEnsureCapacity((emxArray__common *)idx, bLen, sizeof(int));
  ib = iv6[0];
  for (bLen = 0; bLen < ib; bLen++) {
    idx->data[bLen] = 0;
  }

  emxInit_int32_T(&b_idx, 1);
  ib = idx->size[0];
  bLen = b_idx->size[0];
  b_idx->size[0] = ib;
  emxEnsureCapacity((emxArray__common *)b_idx, bLen, sizeof(int));
  for (bLen = 0; bLen < ib; bLen++) {
    b_idx->data[bLen] = idx->data[bLen];
  }

  emxInit_real_T1(&b_x, 1);
  ib = x->size[0];
  bLen = b_x->size[0];
  b_x->size[0] = ib;
  emxEnsureCapacity((emxArray__common *)b_x, bLen, sizeof(double));
  for (bLen = 0; bLen < ib; bLen++) {
    b_x->data[bLen] = x->data[bLen];
  }

  bLen = x->size[0];
  b = x->size[0];
  for (i = 0; i < 4; i++) {
    x4[i] = 0.0;
    idx4[i] = 0;
  }

  emxInit_int32_T(&iwork, 1);
  i = idx->size[0];
  ib = iwork->size[0];
  iwork->size[0] = i;
  emxEnsureCapacity((emxArray__common *)iwork, ib, sizeof(int));
  ib = iwork->size[0];
  i = iwork->size[0];
  iwork->size[0] = ib;
  emxEnsureCapacity((emxArray__common *)iwork, i, sizeof(int));
  for (i = 0; i < ib; i++) {
    iwork->data[i] = 0;
  }

  emxInit_real_T1(&xwork, 1);
  i = x->size[0];
  ib = xwork->size[0];
  xwork->size[0] = i;
  emxEnsureCapacity((emxArray__common *)xwork, ib, sizeof(double));
  ib = xwork->size[0];
  i = xwork->size[0];
  xwork->size[0] = ib;
  emxEnsureCapacity((emxArray__common *)xwork, i, sizeof(double));
  for (i = 0; i < ib; i++) {
    xwork->data[i] = 0.0;
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
          ib = 1;
          wOffset = 2;
        } else {
          ib = 2;
          wOffset = 1;
        }

        if (x4[2] >= x4[3]) {
          i3 = 3;
          i4 = 4;
        } else {
          i3 = 4;
          i4 = 3;
        }

        if (x4[ib - 1] >= x4[i3 - 1]) {
          if (x4[wOffset - 1] >= x4[i3 - 1]) {
            perm[0] = (signed char)ib;
            perm[1] = (signed char)wOffset;
            perm[2] = (signed char)i3;
            perm[3] = (signed char)i4;
          } else if (x4[wOffset - 1] >= x4[i4 - 1]) {
            perm[0] = (signed char)ib;
            perm[1] = (signed char)i3;
            perm[2] = (signed char)wOffset;
            perm[3] = (signed char)i4;
          } else {
            perm[0] = (signed char)ib;
            perm[1] = (signed char)i3;
            perm[2] = (signed char)i4;
            perm[3] = (signed char)wOffset;
          }
        } else if (x4[ib - 1] >= x4[i4 - 1]) {
          if (x4[wOffset - 1] >= x4[i4 - 1]) {
            perm[0] = (signed char)i3;
            perm[1] = (signed char)ib;
            perm[2] = (signed char)wOffset;
            perm[3] = (signed char)i4;
          } else {
            perm[0] = (signed char)i3;
            perm[1] = (signed char)ib;
            perm[2] = (signed char)i4;
            perm[3] = (signed char)wOffset;
          }
        } else {
          perm[0] = (signed char)i3;
          perm[1] = (signed char)i4;
          perm[2] = (signed char)ib;
          perm[3] = (signed char)wOffset;
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

  wOffset = (b - nNaNs) - 1;
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
    ib = b_idx->data[wOffset + k];
    b_idx->data[wOffset + k] = b_idx->data[b - k];
    b_idx->data[b - k] = ib;
    b_x->data[wOffset + k] = xwork->data[b - k];
    b_x->data[b - k] = xwork->data[wOffset + k];
  }

  if ((nNaNs & 1) != 0) {
    b_x->data[(wOffset + i) + 1] = xwork->data[(wOffset + i) + 1];
  }

  nNonNaN = bLen - nNaNs;
  ib = 2;
  if (nNonNaN > 1) {
    if (bLen >= 256) {
      nBlocks = nNonNaN >> 8;
      if (nBlocks > 0) {
        for (i3 = 1; i3 <= nBlocks; i3++) {
          i4 = ((i3 - 1) << 8) - 1;
          for (b = 0; b < 6; b++) {
            bLen = 1 << (b + 2);
            bLen2 = bLen << 1;
            nPairs = 256 >> (b + 3);
            for (k = 1; k <= nPairs; k++) {
              ib = i4 + (k - 1) * bLen2;
              for (i = 1; i <= bLen2; i++) {
                b_iwork[i - 1] = b_idx->data[ib + i];
                b_xwork[i - 1] = b_x->data[ib + i];
              }

              wOffset = 0;
              i = bLen;
              do {
                exitg1 = 0;
                ib++;
                if (b_xwork[wOffset] >= b_xwork[i]) {
                  b_idx->data[ib] = b_iwork[wOffset];
                  b_x->data[ib] = b_xwork[wOffset];
                  if (wOffset + 1 < bLen) {
                    wOffset++;
                  } else {
                    exitg1 = 1;
                  }
                } else {
                  b_idx->data[ib] = b_iwork[i];
                  b_x->data[ib] = b_xwork[i];
                  if (i + 1 < bLen2) {
                    i++;
                  } else {
                    i = ib - wOffset;
                    while (wOffset + 1 <= bLen) {
                      b_idx->data[(i + wOffset) + 1] = b_iwork[wOffset];
                      b_x->data[(i + wOffset) + 1] = b_xwork[wOffset];
                      wOffset++;
                    }

                    exitg1 = 1;
                  }
                }
              } while (exitg1 == 0);
            }
          }
        }

        ib = nBlocks << 8;
        i = nNonNaN - ib;
        if (i > 0) {
          merge_block(b_idx, b_x, ib, i, 2, iwork, xwork);
        }

        ib = 8;
      }
    }

    merge_block(b_idx, b_x, 0, nNonNaN, ib, iwork, xwork);
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
  ib = b_idx->size[0];
  for (bLen = 0; bLen < ib; bLen++) {
    idx->data[bLen] = b_idx->data[bLen];
  }

  emxFree_int32_T(&b_idx);
  ib = b_x->size[0];
  for (bLen = 0; bLen < ib; bLen++) {
    x->data[bLen] = b_x->data[bLen];
  }

  emxFree_real_T(&b_x);
}

//
// File trailer for sort1.cpp
//
// [EOF]
//
