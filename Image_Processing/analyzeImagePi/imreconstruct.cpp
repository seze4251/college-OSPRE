//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: imreconstruct.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "imreconstruct.h"
#include "imregionalmax.h"
#include "regionprops.h"
#include "analyzeImage_emxutil.h"
#include "analyzeImage_rtwutil.h"

// Function Definitions

//
// Arguments    : emxArray_uint8_T *marker
//                const emxArray_uint8_T *mask
// Return Type  : void
//
void imreconstruct(emxArray_uint8_T *marker, const emxArray_uint8_T *mask)
{
  int ak;
  short np_ImageSize[2];
  int i;
  boolean_T np_Neighborhood[9];
  static const boolean_T nhConn[9] = { false, true, false, true, true, true,
    false, true, false };

  short loffsets[5];
  int imnhInds_[5];
  signed char soffsets[10];
  int imnhSubs[10];
  int pixelsPerImPage[2];
  double y;
  int indx;
  int numPixels;
  int pInd;
  int bk;
  emxArray_int32_T *locationStack;
  short k[2];
  signed char subs[2];
  signed char b_subs[2];
  int stackTop;
  int pixelSub[2];
  int b_pixelSub[2];
  int trueCount;
  boolean_T isInside[5];
  int c_pixelSub[2];
  boolean_T exitg1;
  unsigned char minval;
  int imnhInds_data[5];
  for (ak = 0; ak < 2; ak++) {
    np_ImageSize[ak] = (short)marker->size[ak];
  }

  for (ak = 0; ak < 9; ak++) {
    np_Neighborhood[ak] = nhConn[ak];
  }

  for (i = 0; i < 5; i++) {
    loffsets[i] = (short)imnhInds_[i];
  }

  for (ak = 0; ak < 10; ak++) {
    soffsets[ak] = (signed char)imnhSubs[ak];
  }

  //  Process pixels with full neighborhood
  //  Process pixels with partial neighborhood
  //  Process pixels with full neighborhood
  //  Process pixels with partial neighborhood
  pixelsPerImPage[0] = 1;
  pixelsPerImPage[1] = np_ImageSize[0];
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
          soffsets[indx + 5 * ak] = subs[ak];
          k[ak] = (short)(b_subs[ak] * pixelsPerImPage[ak]);
        }

        loffsets[indx] = (short)(k[0] + k[1]);
        indx++;
      }
    }

    for (ak = 0; ak < 2; ak++) {
      k[ak] = (short)((2 - ak) * pixelsPerImPage[ak]);
    }

    indx = k[0] + k[1];
    for (ak = 0; ak < 5; ak++) {
      loffsets[ak] -= (short)indx;
    }

    for (ak = 0; ak < 10; ak++) {
      imnhSubs[ak] = soffsets[ak];
    }

    ak = 0;
    for (i = 0; i <= 6; i += 5) {
      for (indx = 0; indx < 5; indx++) {
        soffsets[i + indx] = (signed char)(imnhSubs[ak + indx] - 2);
      }

      ak += 5;
    }
  }

  numPixels = marker->size[0] * marker->size[1];
  for (pInd = 0; pInd + 1 <= numPixels; pInd++) {
    for (i = 0; i < 5; i++) {
      imnhInds_[i] = (loffsets[i] + pInd) + 1;
    }

    if (np_ImageSize[0] == 0) {
      bk = 0;
    } else {
      bk = pInd - np_ImageSize[0] * div_s32(pInd, (int)np_ImageSize[0]);
    }

    i = pInd - bk;
    if (np_ImageSize[0] == 0) {
      if (i == 0) {
        ak = 0;
      } else if (i < 0) {
        ak = MIN_int32_T;
      } else {
        ak = MAX_int32_T;
      }
    } else if (np_ImageSize[0] == 1) {
      ak = i;
    } else {
      if (i >= 0) {
        indx = i;
      } else if (i == MIN_int32_T) {
        indx = MAX_int32_T;
      } else {
        indx = -i;
      }

      ak = div_s32(indx, (int)np_ImageSize[0]);
      indx -= ak * np_ImageSize[0];
      if ((indx > 0) && (indx >= (np_ImageSize[0] >> 1) + (np_ImageSize[0] & 1)))
      {
        ak++;
      }

      if (i < 0) {
        ak = -ak;
      }
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
        imnhSubs[i + indx] = soffsets[ak + indx] + pixelsPerImPage[bk];
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
        if ((imnhSubs[ak + 5 * indx] < 1) || (imnhSubs[ak + 5 * indx] >
             np_ImageSize[indx])) {
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

    minval = marker->data[imnhInds_data[0] - 1];
    if (trueCount > 1) {
      for (indx = 1; indx + 1 <= trueCount; indx++) {
        if (marker->data[imnhInds_data[indx] - 1] > minval) {
          minval = marker->data[imnhInds_data[indx] - 1];
        }
      }
    }

    if (minval < mask->data[pInd]) {
    } else {
      minval = mask->data[pInd];
    }

    marker->data[pInd] = minval;
  }

  emxInit_int32_T1(&locationStack, 2);
  ak = locationStack->size[0] * locationStack->size[1];
  locationStack->size[0] = 1;
  locationStack->size[1] = numPixels << 1;
  emxEnsureCapacity((emxArray__common *)locationStack, ak, sizeof(int));
  stackTop = -1;
  for (pInd = numPixels - 1; pInd + 1 > 0; pInd--) {
    for (i = 0; i < 5; i++) {
      imnhInds_[i] = (loffsets[i] + pInd) + 1;
    }

    if (np_ImageSize[0] == 0) {
      bk = 0;
    } else {
      bk = pInd - np_ImageSize[0] * div_s32(pInd, (int)np_ImageSize[0]);
    }

    i = pInd - bk;
    if (np_ImageSize[0] == 0) {
      if (i == 0) {
        ak = 0;
      } else if (i < 0) {
        ak = MIN_int32_T;
      } else {
        ak = MAX_int32_T;
      }
    } else if (np_ImageSize[0] == 1) {
      ak = i;
    } else {
      if (i >= 0) {
        indx = i;
      } else if (i == MIN_int32_T) {
        indx = MAX_int32_T;
      } else {
        indx = -i;
      }

      ak = div_s32(indx, (int)np_ImageSize[0]);
      indx -= ak * np_ImageSize[0];
      if ((indx > 0) && (indx >= (np_ImageSize[0] >> 1) + (np_ImageSize[0] & 1)))
      {
        ak++;
      }

      if (i < 0) {
        ak = -ak;
      }
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
        imnhSubs[i + indx] = soffsets[ak + indx] + pixelsPerImPage[bk];
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
        if ((imnhSubs[ak + 5 * indx] < 1) || (imnhSubs[ak + 5 * indx] >
             np_ImageSize[indx])) {
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

    minval = marker->data[imnhInds_data[0] - 1];
    if (trueCount > 1) {
      for (indx = 1; indx + 1 <= trueCount; indx++) {
        if (marker->data[imnhInds_data[indx] - 1] > minval) {
          minval = marker->data[imnhInds_data[indx] - 1];
        }
      }
    }

    if (minval < mask->data[pInd]) {
    } else {
      minval = mask->data[pInd];
    }

    marker->data[pInd] = minval;
    ak = 0;
    exitg1 = false;
    while ((!exitg1) && (ak <= trueCount - 1)) {
      if ((marker->data[imnhInds_data[ak] - 1] < marker->data[pInd]) &&
          (marker->data[imnhInds_data[ak] - 1] < mask->data[imnhInds_data[ak] -
           1])) {
        stackTop++;
        locationStack->data[stackTop] = pInd + 1;
        exitg1 = true;
      } else {
        ak++;
      }
    }
  }

  while (stackTop + 1 > 0) {
    pInd = locationStack->data[stackTop] - 1;
    stackTop--;
    for (i = 0; i < 5; i++) {
      imnhInds_[i] = (loffsets[i] + pInd) + 1;
    }

    if (np_ImageSize[0] == 0) {
      bk = 0;
    } else {
      bk = pInd - np_ImageSize[0] * div_s32(pInd, (int)np_ImageSize[0]);
    }

    i = pInd - bk;
    if (np_ImageSize[0] == 0) {
      if (i == 0) {
        ak = 0;
      } else if (i < 0) {
        ak = MIN_int32_T;
      } else {
        ak = MAX_int32_T;
      }
    } else if (np_ImageSize[0] == 1) {
      ak = i;
    } else {
      if (i >= 0) {
        indx = i;
      } else if (i == MIN_int32_T) {
        indx = MAX_int32_T;
      } else {
        indx = -i;
      }

      ak = div_s32(indx, (int)np_ImageSize[0]);
      indx -= ak * np_ImageSize[0];
      if ((indx > 0) && (indx >= (np_ImageSize[0] >> 1) + (np_ImageSize[0] & 1)))
      {
        ak++;
      }

      if (i < 0) {
        ak = -ak;
      }
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
        imnhSubs[i + indx] = soffsets[ak + indx] + pixelsPerImPage[bk];
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
        if ((imnhSubs[ak + 5 * indx] < 1) || (imnhSubs[ak + 5 * indx] >
             np_ImageSize[indx])) {
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
      if ((marker->data[imnhInds_data[ak] - 1] < marker->data[pInd]) &&
          (marker->data[imnhInds_data[ak] - 1] != mask->data[imnhInds_data[ak] -
           1])) {
        if (marker->data[pInd] < mask->data[imnhInds_data[ak] - 1]) {
          minval = marker->data[pInd];
        } else {
          minval = mask->data[imnhInds_data[ak] - 1];
        }

        marker->data[imnhInds_data[ak] - 1] = minval;
        stackTop++;
        locationStack->data[stackTop] = imnhInds_data[ak];
      }
    }
  }

  emxFree_int32_T(&locationStack);
}

//
// File trailer for imreconstruct.cpp
//
// [EOF]
//
