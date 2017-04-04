//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: convn.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "convn.h"
#include "analyzeImage_emxutil.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *A
//                emxArray_real_T *C
// Return Type  : void
//
void b_convn(const emxArray_real_T *A, emxArray_real_T *C)
{
  int firstRowA;
  short iv1[2];
  int aidx;
  int cEnd;
  int cEnd1;
  int ma;
  int na;
  int j;
  int lastColA;
  int k;
  int b_j;
  int iC;
  int iA;
  int iB;
  int i;
  int b_i;
  int a_length;
  int r;
  static const signed char iv2[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };

  for (firstRowA = 0; firstRowA < 2; firstRowA++) {
    iv1[firstRowA] = (short)A->size[firstRowA];
  }

  firstRowA = C->size[0] * C->size[1];
  C->size[0] = iv1[0];
  C->size[1] = iv1[1];
  emxEnsureCapacity((emxArray__common *)C, firstRowA, sizeof(double));
  aidx = iv1[0] * iv1[1];
  for (firstRowA = 0; firstRowA < aidx; firstRowA++) {
    C->data[firstRowA] = 0.0;
  }

  cEnd = iv1[1];
  cEnd1 = iv1[0];
  ma = A->size[0];
  na = A->size[1] - 1;
  for (j = 0; j < 3; j++) {
    if (j + na < cEnd) {
      lastColA = na;
    } else {
      lastColA = cEnd - j;
    }

    for (k = (j < 1); k <= lastColA; k++) {
      if (j + k > 1) {
        b_j = (j + k) - 1;
      } else {
        b_j = 0;
      }

      iC = b_j * cEnd1;
      iA = k * ma;
      iB = j * 3;
      for (i = 0; i < 3; i++) {
        firstRowA = (i < 1);
        if (i + ma <= cEnd1) {
          b_i = ma;
        } else {
          b_i = (cEnd1 - i) + 1;
        }

        a_length = b_i - firstRowA;
        aidx = iA + firstRowA;
        firstRowA = iC;
        for (r = 1; r <= a_length; r++) {
          C->data[firstRowA] += (double)iv2[iB] * A->data[aidx];
          aidx++;
          firstRowA++;
        }

        iB++;
        if (i >= 1) {
          iC++;
        }
      }
    }
  }
}

//
// Arguments    : const emxArray_real_T *A
//                emxArray_real_T *C
// Return Type  : void
//
void c_convn(const emxArray_real_T *A, emxArray_real_T *C)
{
  int firstRowA;
  short iv3[2];
  int aidx;
  int cEnd;
  int cEnd1;
  int ma;
  int na;
  int j;
  int lastColA;
  int k;
  int b_j;
  int iC;
  int iA;
  int iB;
  int i;
  int b_i;
  int a_length;
  int r;
  static const signed char iv4[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };

  for (firstRowA = 0; firstRowA < 2; firstRowA++) {
    iv3[firstRowA] = (short)A->size[firstRowA];
  }

  firstRowA = C->size[0] * C->size[1];
  C->size[0] = iv3[0];
  C->size[1] = iv3[1];
  emxEnsureCapacity((emxArray__common *)C, firstRowA, sizeof(double));
  aidx = iv3[0] * iv3[1];
  for (firstRowA = 0; firstRowA < aidx; firstRowA++) {
    C->data[firstRowA] = 0.0;
  }

  cEnd = iv3[1];
  cEnd1 = iv3[0];
  ma = A->size[0];
  na = A->size[1] - 1;
  for (j = 0; j < 3; j++) {
    if (j + na < cEnd) {
      lastColA = na;
    } else {
      lastColA = cEnd - j;
    }

    for (k = (j < 1); k <= lastColA; k++) {
      if (j + k > 1) {
        b_j = (j + k) - 1;
      } else {
        b_j = 0;
      }

      iC = b_j * cEnd1;
      iA = k * ma;
      iB = j * 3;
      for (i = 0; i < 3; i++) {
        firstRowA = (i < 1);
        if (i + ma <= cEnd1) {
          b_i = ma;
        } else {
          b_i = (cEnd1 - i) + 1;
        }

        a_length = b_i - firstRowA;
        aidx = iA + firstRowA;
        firstRowA = iC;
        for (r = 1; r <= a_length; r++) {
          C->data[firstRowA] += (double)iv4[iB] * A->data[aidx];
          aidx++;
          firstRowA++;
        }

        iB++;
        if (i >= 1) {
          iC++;
        }
      }
    }
  }
}

//
// Arguments    : const emxArray_real_T *A
//                emxArray_real_T *C
// Return Type  : void
//
void convn(const emxArray_real_T *A, emxArray_real_T *C)
{
  int firstRowA;
  short iv0[2];
  int aidx;
  int cEnd;
  int cEnd1;
  int ma;
  int na;
  int j;
  int lastColA;
  int k;
  int b_j;
  int iC;
  int iA;
  int iB;
  int i;
  int b_i;
  int a_length;
  int r;
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

  for (firstRowA = 0; firstRowA < 2; firstRowA++) {
    iv0[firstRowA] = (short)A->size[firstRowA];
  }

  firstRowA = C->size[0] * C->size[1];
  C->size[0] = iv0[0];
  C->size[1] = iv0[1];
  emxEnsureCapacity((emxArray__common *)C, firstRowA, sizeof(double));
  aidx = iv0[0] * iv0[1];
  for (firstRowA = 0; firstRowA < aidx; firstRowA++) {
    C->data[firstRowA] = 0.0;
  }

  cEnd = iv0[1] + 2;
  cEnd1 = iv0[0];
  ma = A->size[0];
  na = A->size[1] - 1;
  for (j = 0; j < 6; j++) {
    if (j + na < cEnd) {
      lastColA = na;
    } else {
      lastColA = cEnd - j;
    }

    if (j < 3) {
      k = 3 - j;
    } else {
      k = 0;
    }

    while (k <= lastColA) {
      if (j + k > 3) {
        b_j = (j + k) - 3;
      } else {
        b_j = 0;
      }

      iC = b_j * cEnd1;
      iA = k * ma;
      iB = j * 6;
      for (i = 0; i < 6; i++) {
        if (i < 3) {
          firstRowA = 3 - i;
        } else {
          firstRowA = 0;
        }

        if (i + ma <= cEnd1 + 2) {
          b_i = ma;
        } else {
          b_i = (cEnd1 - i) + 3;
        }

        a_length = b_i - firstRowA;
        aidx = iA + firstRowA;
        firstRowA = iC;
        for (r = 1; r <= a_length; r++) {
          C->data[firstRowA] += dv0[iB] * A->data[aidx];
          aidx++;
          firstRowA++;
        }

        iB++;
        if (i >= 3) {
          iC++;
        }
      }

      k++;
    }
  }
}

//
// File trailer for convn.cpp
//
// [EOF]
//
