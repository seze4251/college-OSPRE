//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: imhmax.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 14-Feb-2017 14:49:57
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "imhmax.h"
#include "imregionalmax.h"
#include "bsxfun.h"
#include "analyzeImage_rtwutil.h"

// Function Definitions

//
// Arguments    : const double I[809600]
//                double H
//                double J[809600]
// Return Type  : void
//
void imhmax(const double I[809600], double H, double J[809600])
{
  int c;
  int av[9];
  int np_NeighborSubscriptOffsets[18];
  int iv2[18];
  short a[9];
  int i;
  int pixelsPerImPage[2];
  int indx;
  int r;
  signed char subs[2];
  int imnhSubs[18];
  signed char b_subs[2];
  short b_c[2];
  int pInd;
  static int locationStack[1619200];
  int stackTop;
  int pixelSub[2];
  int b_pixelSub[2];
  boolean_T isInside[9];
  int c_pixelSub[2];
  int trueCount;
  boolean_T exitg6;
  double mtmp;
  int imnhInds_data[9];
  boolean_T exitg4;
  boolean_T exitg5;
  boolean_T exitg1;
  boolean_T exitg3;
  boolean_T exitg2;
  for (c = 0; c < 809600; c++) {
    J[c] = I[c] - H;
  }

  memcpy(&iv2[0], &np_NeighborSubscriptOffsets[0], 18U * sizeof(int));
  for (i = 0; i < 9; i++) {
    a[i] = (short)av[i];
  }

  //  Process pixels with full neighborhood
  //  Process pixels with partial neighborhood
  //  Process pixels with full neighborhood
  //  Process pixels with partial neighborhood
  pixelsPerImPage[0] = 1;
  pixelsPerImPage[1] = 736;
  indx = 0;
  for (i = 0; i < 9; i++) {
    r = (int)rt_remd_snf((1.0 + (double)i) - 1.0, 3.0) + 1;
    subs[1] = (signed char)((int)(((double)(i - r) + 1.0) / 3.0) + 1);
    subs[0] = (signed char)r;
    b_subs[0] = (signed char)r;
    b_subs[1] = (signed char)(subs[1] - 1);
    for (c = 0; c < 2; c++) {
      iv2[indx + 9 * c] = subs[c];
      b_c[c] = (short)(b_subs[c] * pixelsPerImPage[c]);
    }

    a[indx] = (short)(b_c[0] + b_c[1]);
    indx++;
  }

  for (c = 0; c < 9; c++) {
    a[c] = (short)(a[c] - 738);
  }

  memcpy(&imnhSubs[0], &iv2[0], 18U * sizeof(int));
  indx = 0;
  for (i = 0; i <= 10; i += 9) {
    for (c = 0; c < 9; c++) {
      iv2[i + c] = (signed char)imnhSubs[indx + c] - 2;
    }

    indx += 9;
  }

  for (pInd = 0; pInd < 809600; pInd++) {
    for (i = 0; i < 9; i++) {
      av[i] = (a[i] + pInd) + 1;
    }

    r = pInd - 736 * (pInd / 736);
    c = pInd - r;
    if (c >= 0) {
      indx = c;
    } else {
      indx = -c;
    }

    i = indx / 736;
    indx -= i * 736;
    if ((indx > 0) && (indx >= 368)) {
      i++;
    }

    if (c < 0) {
      i = -i;
    }

    pixelSub[1] = i + 1;
    pixelSub[0] = r + 1;
    for (c = 0; c < 2; c++) {
      pixelsPerImPage[c] = pixelSub[c];
    }

    bsxfun(iv2, pixelsPerImPage, imnhSubs);
    for (i = 0; i < 9; i++) {
      isInside[i] = true;
    }

    trueCount = 0;
    for (c = 0; c < 9; c++) {
      indx = 0;
      exitg6 = false;
      while ((!exitg6) && (indx < 2)) {
        if ((imnhSubs[c + 9 * indx] < 1) || (imnhSubs[c + 9 * indx] > 736 + 364 *
             indx)) {
          isInside[c] = false;
          exitg6 = true;
        } else {
          indx++;
        }
      }

      if (isInside[c]) {
        trueCount++;
      }
    }

    c = 0;
    for (i = 0; i < 9; i++) {
      if (isInside[i]) {
        imnhInds_data[c] = av[i];
        c++;
      }
    }

    indx = 1;
    mtmp = J[imnhInds_data[0] - 1];
    if (trueCount > 1) {
      if (rtIsNaN(J[imnhInds_data[0] - 1])) {
        i = 2;
        exitg5 = false;
        while ((!exitg5) && (i <= trueCount)) {
          indx = i;
          if (!rtIsNaN(J[imnhInds_data[i - 1] - 1])) {
            mtmp = J[imnhInds_data[i - 1] - 1];
            exitg5 = true;
          } else {
            i++;
          }
        }
      }

      if (indx < trueCount) {
        while (indx + 1 <= trueCount) {
          if (J[imnhInds_data[indx] - 1] > mtmp) {
            mtmp = J[imnhInds_data[indx] - 1];
          }

          indx++;
        }
      }
    }

    if ((mtmp <= I[pInd]) || rtIsNaN(I[pInd])) {
      J[pInd] = mtmp;
    } else {
      J[pInd] = I[pInd];
    }
  }

  stackTop = -1;
  for (pInd = 809599; pInd >= 0; pInd += -1) {
    for (i = 0; i < 9; i++) {
      av[i] = (a[i] + pInd) + 1;
    }

    r = pInd - 736 * (pInd / 736);
    c = pInd - r;
    if (c >= 0) {
      indx = c;
    } else {
      indx = -c;
    }

    i = indx / 736;
    indx -= i * 736;
    if ((indx > 0) && (indx >= 368)) {
      i++;
    }

    if (c < 0) {
      i = -i;
    }

    b_pixelSub[1] = i + 1;
    b_pixelSub[0] = r + 1;
    for (c = 0; c < 2; c++) {
      pixelSub[c] = b_pixelSub[c];
    }

    bsxfun(iv2, pixelSub, imnhSubs);
    for (i = 0; i < 9; i++) {
      isInside[i] = true;
    }

    trueCount = 0;
    for (c = 0; c < 9; c++) {
      indx = 0;
      exitg4 = false;
      while ((!exitg4) && (indx < 2)) {
        if ((imnhSubs[c + 9 * indx] < 1) || (imnhSubs[c + 9 * indx] > 736 + 364 *
             indx)) {
          isInside[c] = false;
          exitg4 = true;
        } else {
          indx++;
        }
      }

      if (isInside[c]) {
        trueCount++;
      }
    }

    c = 0;
    for (i = 0; i < 9; i++) {
      if (isInside[i]) {
        imnhInds_data[c] = av[i];
        c++;
      }
    }

    indx = 1;
    mtmp = J[imnhInds_data[0] - 1];
    if (trueCount > 1) {
      if (rtIsNaN(J[imnhInds_data[0] - 1])) {
        i = 2;
        exitg3 = false;
        while ((!exitg3) && (i <= trueCount)) {
          indx = i;
          if (!rtIsNaN(J[imnhInds_data[i - 1] - 1])) {
            mtmp = J[imnhInds_data[i - 1] - 1];
            exitg3 = true;
          } else {
            i++;
          }
        }
      }

      if (indx < trueCount) {
        while (indx + 1 <= trueCount) {
          if (J[imnhInds_data[indx] - 1] > mtmp) {
            mtmp = J[imnhInds_data[indx] - 1];
          }

          indx++;
        }
      }
    }

    if ((mtmp <= I[pInd]) || rtIsNaN(I[pInd])) {
      J[pInd] = mtmp;
    } else {
      J[pInd] = I[pInd];
    }

    c = 0;
    exitg2 = false;
    while ((!exitg2) && (c <= trueCount - 1)) {
      if ((J[imnhInds_data[c] - 1] < J[pInd]) && (J[imnhInds_data[c] - 1] <
           I[imnhInds_data[c] - 1])) {
        stackTop++;
        locationStack[stackTop] = pInd + 1;
        exitg2 = true;
      } else {
        c++;
      }
    }
  }

  while (stackTop + 1 > 0) {
    pInd = locationStack[stackTop] - 1;
    stackTop--;
    for (i = 0; i < 9; i++) {
      av[i] = (a[i] + pInd) + 1;
    }

    r = pInd - 736 * (pInd / 736);
    c = pInd - r;
    if (c >= 0) {
      indx = c;
    } else if (c == MIN_int32_T) {
      indx = MAX_int32_T;
    } else {
      indx = -c;
    }

    i = indx / 736;
    indx -= i * 736;
    if ((indx > 0) && (indx >= 368)) {
      i++;
    }

    if (c < 0) {
      i = -i;
    }

    c_pixelSub[1] = i + 1;
    c_pixelSub[0] = r + 1;
    for (c = 0; c < 2; c++) {
      b_pixelSub[c] = c_pixelSub[c];
    }

    bsxfun(iv2, b_pixelSub, imnhSubs);
    for (i = 0; i < 9; i++) {
      isInside[i] = true;
    }

    trueCount = 0;
    for (c = 0; c < 9; c++) {
      indx = 0;
      exitg1 = false;
      while ((!exitg1) && (indx < 2)) {
        if ((imnhSubs[c + 9 * indx] < 1) || (imnhSubs[c + 9 * indx] > 736 + 364 *
             indx)) {
          isInside[c] = false;
          exitg1 = true;
        } else {
          indx++;
        }
      }

      if (isInside[c]) {
        trueCount++;
      }
    }

    c = 0;
    for (i = 0; i < 9; i++) {
      if (isInside[i]) {
        imnhInds_data[c] = av[i];
        c++;
      }
    }

    for (c = 0; c < trueCount; c++) {
      if ((J[imnhInds_data[c] - 1] < J[pInd]) && (J[imnhInds_data[c] - 1] !=
           I[imnhInds_data[c] - 1])) {
        if ((J[pInd] <= I[imnhInds_data[c] - 1]) || rtIsNaN(I[imnhInds_data[c] -
             1])) {
          J[imnhInds_data[c] - 1] = J[pInd];
        } else {
          J[imnhInds_data[c] - 1] = I[imnhInds_data[c] - 1];
        }

        stackTop++;
        locationStack[stackTop] = imnhInds_data[c];
      }
    }
  }
}

//
// File trailer for imhmax.cpp
//
// [EOF]
//
