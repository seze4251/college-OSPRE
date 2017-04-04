//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: imreconstruct.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 14-Feb-2017 14:49:57
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "imreconstruct.h"
#include "imregionalmax.h"
#include "analyzeImage_rtwutil.h"

// Function Definitions

//
// Arguments    : unsigned char marker[813276]
//                const unsigned char mask[813276]
// Return Type  : void
//
void imreconstruct(unsigned char marker[813276], const unsigned char mask[813276])
{
  boolean_T np_Neighborhood[9];
  int ak;
  int imnhInds_[5];
  static const boolean_T nhConn[9] = { false, true, false, true, true, true,
    false, true, false };

  int imnhSubs[10];
  signed char iv5[10];
  short a[5];
  int i;
  int pixelsPerImPage[2];
  double y;
  int indx;
  int pInd;
  static int locationStack[1626552];
  short k[2];
  int stackTop;
  int bk;
  signed char subs[2];
  signed char b_subs[2];
  int pixelSub[2];
  int b_pixelSub[2];
  int c_pixelSub[2];
  boolean_T isInside[5];
  int trueCount;
  boolean_T exitg4;
  unsigned char mtmp;
  int imnhInds_data[5];
  boolean_T exitg3;
  boolean_T exitg1;
  boolean_T exitg2;
  for (ak = 0; ak < 9; ak++) {
    np_Neighborhood[ak] = nhConn[ak];
  }

  for (ak = 0; ak < 10; ak++) {
    iv5[ak] = (signed char)imnhSubs[ak];
  }

  for (i = 0; i < 5; i++) {
    a[i] = (short)imnhInds_[i];
  }

  //  Process pixels with full neighborhood
  //  Process pixels with partial neighborhood
  //  Process pixels with full neighborhood
  //  Process pixels with partial neighborhood
  pixelsPerImPage[0] = 1;
  pixelsPerImPage[1] = 738;
  y = 0.0;
  for (indx = 0; indx < 8; indx++) {
    y += (double)np_Neighborhood[indx + 1];
  }

  if (!(y == 0.0)) {
    indx = 0;
    for (i = 0; i < 9; i++) {
      if (np_Neighborhood[i]) {
        bk = (int)rt_remd_snf((1.0 + (double)i) - 1.0, 3.0) + 1;
        subs[1] = (signed char)((int)(((double)(i - bk) + 1.0) / 3.0) + 1);
        subs[0] = (signed char)bk;
        b_subs[0] = (signed char)bk;
        b_subs[1] = (signed char)(subs[1] - 1);
        for (ak = 0; ak < 2; ak++) {
          iv5[indx + 5 * ak] = subs[ak];
          k[ak] = (short)(b_subs[ak] * pixelsPerImPage[ak]);
        }

        a[indx] = (short)(k[0] + k[1]);
        indx++;
      }
    }

    for (ak = 0; ak < 2; ak++) {
      k[ak] = (short)((2 - ak) * pixelsPerImPage[ak]);
    }

    indx = k[0] + k[1];
    for (ak = 0; ak < 5; ak++) {
      a[ak] = (short)(a[ak] - indx);
    }

    for (ak = 0; ak < 10; ak++) {
      imnhSubs[ak] = iv5[ak];
    }

    ak = 0;
    for (i = 0; i <= 6; i += 5) {
      for (indx = 0; indx < 5; indx++) {
        iv5[i + indx] = (signed char)(imnhSubs[ak + indx] - 2);
      }

      ak += 5;
    }
  }

  for (pInd = 0; pInd < 813276; pInd++) {
    for (i = 0; i < 5; i++) {
      imnhInds_[i] = (a[i] + pInd) + 1;
    }

    bk = pInd - 738 * (pInd / 738);
    i = pInd - bk;
    if (i >= 0) {
      indx = i;
    } else {
      indx = -i;
    }

    ak = indx / 738;
    indx -= ak * 738;
    if ((indx > 0) && (indx >= 369)) {
      ak++;
    }

    if (i < 0) {
      ak = -ak;
    }

    pixelSub[1] = ak + 1;
    pixelSub[0] = bk + 1;
    for (ak = 0; ak < 2; ak++) {
      pixelsPerImPage[ak] = pixelSub[ak];
    }

    ak = 0;
    bk = 0;
    for (i = 0; i <= 6; i += 5) {
      for (indx = 0; indx < 5; indx++) {
        imnhSubs[i + indx] = iv5[ak + indx] + pixelsPerImPage[bk];
      }

      ak += 5;
      bk++;
    }

    for (i = 0; i < 5; i++) {
      isInside[i] = true;
    }

    trueCount = 0;
    for (ak = 0; ak < 5; ak++) {
      indx = 0;
      exitg4 = false;
      while ((!exitg4) && (indx < 2)) {
        if ((imnhSubs[ak + 5 * indx] < 1) || (imnhSubs[ak + 5 * indx] > 738 +
             364 * indx)) {
          isInside[ak] = false;
          exitg4 = true;
        } else {
          indx++;
        }
      }

      if (isInside[ak]) {
        trueCount++;
      }
    }

    indx = 0;
    for (i = 0; i < 5; i++) {
      if (isInside[i]) {
        imnhInds_data[indx] = imnhInds_[i];
        indx++;
      }
    }

    mtmp = marker[imnhInds_data[0] - 1];
    if (trueCount > 1) {
      for (indx = 1; indx + 1 <= trueCount; indx++) {
        if (marker[imnhInds_data[indx] - 1] > mtmp) {
          mtmp = marker[imnhInds_data[indx] - 1];
        }
      }
    }

    if (mtmp <= mask[pInd]) {
      marker[pInd] = mtmp;
    } else {
      marker[pInd] = mask[pInd];
    }
  }

  stackTop = -1;
  for (pInd = 813275; pInd >= 0; pInd += -1) {
    for (i = 0; i < 5; i++) {
      imnhInds_[i] = (a[i] + pInd) + 1;
    }

    bk = pInd - 738 * (pInd / 738);
    i = pInd - bk;
    if (i >= 0) {
      indx = i;
    } else {
      indx = -i;
    }

    ak = indx / 738;
    indx -= ak * 738;
    if ((indx > 0) && (indx >= 369)) {
      ak++;
    }

    if (i < 0) {
      ak = -ak;
    }

    b_pixelSub[1] = ak + 1;
    b_pixelSub[0] = bk + 1;
    for (ak = 0; ak < 2; ak++) {
      pixelsPerImPage[ak] = b_pixelSub[ak];
    }

    ak = 0;
    bk = 0;
    for (i = 0; i <= 6; i += 5) {
      for (indx = 0; indx < 5; indx++) {
        imnhSubs[i + indx] = iv5[ak + indx] + pixelsPerImPage[bk];
      }

      ak += 5;
      bk++;
    }

    for (i = 0; i < 5; i++) {
      isInside[i] = true;
    }

    trueCount = 0;
    for (ak = 0; ak < 5; ak++) {
      indx = 0;
      exitg3 = false;
      while ((!exitg3) && (indx < 2)) {
        if ((imnhSubs[ak + 5 * indx] < 1) || (imnhSubs[ak + 5 * indx] > 738 +
             364 * indx)) {
          isInside[ak] = false;
          exitg3 = true;
        } else {
          indx++;
        }
      }

      if (isInside[ak]) {
        trueCount++;
      }
    }

    indx = 0;
    for (i = 0; i < 5; i++) {
      if (isInside[i]) {
        imnhInds_data[indx] = imnhInds_[i];
        indx++;
      }
    }

    mtmp = marker[imnhInds_data[0] - 1];
    if (trueCount > 1) {
      for (indx = 1; indx + 1 <= trueCount; indx++) {
        if (marker[imnhInds_data[indx] - 1] > mtmp) {
          mtmp = marker[imnhInds_data[indx] - 1];
        }
      }
    }

    if (mtmp <= mask[pInd]) {
      marker[pInd] = mtmp;
    } else {
      marker[pInd] = mask[pInd];
    }

    ak = 0;
    exitg2 = false;
    while ((!exitg2) && (ak <= trueCount - 1)) {
      if ((marker[imnhInds_data[ak] - 1] < marker[pInd]) &&
          (marker[imnhInds_data[ak] - 1] < mask[imnhInds_data[ak] - 1])) {
        stackTop++;
        locationStack[stackTop] = pInd + 1;
        exitg2 = true;
      } else {
        ak++;
      }
    }
  }

  while (stackTop + 1 > 0) {
    pInd = locationStack[stackTop] - 1;
    stackTop--;
    for (i = 0; i < 5; i++) {
      imnhInds_[i] = (a[i] + pInd) + 1;
    }

    bk = pInd - 738 * (pInd / 738);
    i = pInd - bk;
    if (i >= 0) {
      indx = i;
    } else if (i == MIN_int32_T) {
      indx = MAX_int32_T;
    } else {
      indx = -i;
    }

    ak = indx / 738;
    indx -= ak * 738;
    if ((indx > 0) && (indx >= 369)) {
      ak++;
    }

    if (i < 0) {
      ak = -ak;
    }

    c_pixelSub[1] = ak + 1;
    c_pixelSub[0] = bk + 1;
    for (ak = 0; ak < 2; ak++) {
      pixelsPerImPage[ak] = c_pixelSub[ak];
    }

    ak = 0;
    bk = 0;
    for (i = 0; i <= 6; i += 5) {
      for (indx = 0; indx < 5; indx++) {
        imnhSubs[i + indx] = iv5[ak + indx] + pixelsPerImPage[bk];
      }

      ak += 5;
      bk++;
    }

    for (i = 0; i < 5; i++) {
      isInside[i] = true;
    }

    trueCount = 0;
    for (ak = 0; ak < 5; ak++) {
      indx = 0;
      exitg1 = false;
      while ((!exitg1) && (indx < 2)) {
        if ((imnhSubs[ak + 5 * indx] < 1) || (imnhSubs[ak + 5 * indx] > 738 +
             364 * indx)) {
          isInside[ak] = false;
          exitg1 = true;
        } else {
          indx++;
        }
      }

      if (isInside[ak]) {
        trueCount++;
      }
    }

    indx = 0;
    for (i = 0; i < 5; i++) {
      if (isInside[i]) {
        imnhInds_data[indx] = imnhInds_[i];
        indx++;
      }
    }

    for (ak = 0; ak < trueCount; ak++) {
      if ((marker[imnhInds_data[ak] - 1] < marker[pInd]) &&
          (marker[imnhInds_data[ak] - 1] != mask[imnhInds_data[ak] - 1])) {
        if (marker[pInd] <= mask[imnhInds_data[ak] - 1]) {
          marker[imnhInds_data[ak] - 1] = marker[pInd];
        } else {
          marker[imnhInds_data[ak] - 1] = mask[imnhInds_data[ak] - 1];
        }

        stackTop++;
        locationStack[stackTop] = imnhInds_data[ak];
      }
    }
  }
}

//
// File trailer for imreconstruct.cpp
//
// [EOF]
//
