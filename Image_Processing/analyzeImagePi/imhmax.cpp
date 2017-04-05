//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: imhmax.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "imhmax.h"
#include "imregionalmax.h"
#include "bsxfun.h"
#include "regionprops.h"
#include "analyzeImage_emxutil.h"
#include "isrow.h"
#include "analyzeImage_rtwutil.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *I
//                double H
//                emxArray_real_T *J
// Return Type  : void
//
void imhmax(const emxArray_real_T *I, double H, emxArray_real_T *J)
{
  int c;
  int indx;
  int i;
  short np_ImageSize[2];
  short loffsets[9];
  int av[9];
  int pixelsPerImPage[2];
  signed char subs[2];
  int r;
  signed char b_subs[2];
  short b_c[2];
  int imnhSubs[18];
  int np_NeighborSubscriptOffsets[18];
  int numPixels;
  emxArray_int32_T *locationStack;
  int pInd;
  int stackTop;
  int pixelSub[2];
  int trueCount;
  boolean_T isInside[9];
  int b_pixelSub[2];
  boolean_T exitg1;
  int c_pixelSub[2];
  double mtmp;
  int imnhInds_data[9];
  int tmp_data[9];
  c = J->size[0] * J->size[1];
  J->size[0] = I->size[0];
  J->size[1] = I->size[1];
  emxEnsureCapacity((emxArray__common *)J, c, sizeof(double));
  indx = I->size[0] * I->size[1];
  for (c = 0; c < indx; c++) {
    J->data[c] = I->data[c] - H;
  }

  for (c = 0; c < 2; c++) {
    np_ImageSize[c] = (short)J->size[c];
  }

  for (i = 0; i < 9; i++) {
    loffsets[i] = (short)av[i];
  }

  //  Process pixels with full neighborhood
  //  Process pixels with partial neighborhood
  //  Process pixels with full neighborhood
  //  Process pixels with partial neighborhood
  pixelsPerImPage[0] = 1;
  pixelsPerImPage[1] = np_ImageSize[0];
  indx = 0;
  for (i = 0; i < 9; i++) {
    r = (int)rt_remd_snf((1.0 + (double)i) - 1.0, 3.0) + 1;
    subs[1] = (signed char)((int)(((double)(i - r) + 1.0) / 3.0) + 1);
    subs[0] = (signed char)r;
    b_subs[0] = (signed char)r;
    b_subs[1] = (signed char)(subs[1] - 1);
    for (c = 0; c < 2; c++) {
      np_NeighborSubscriptOffsets[indx + 9 * c] = subs[c];
      b_c[c] = (short)(b_subs[c] * pixelsPerImPage[c]);
    }

    loffsets[indx] = (short)(b_c[0] + b_c[1]);
    indx++;
  }

  subs[0] = 2;
  subs[1] = 1;
  for (c = 0; c < 2; c++) {
    b_c[c] = (short)(subs[c] * pixelsPerImPage[c]);
  }

  for (c = 0; c < 9; c++) {
    loffsets[c] -= (short)(b_c[1] + 2);
  }

  memcpy(&imnhSubs[0], &np_NeighborSubscriptOffsets[0], 18U * sizeof(int));
  indx = 0;
  for (i = 0; i <= 10; i += 9) {
    for (c = 0; c < 9; c++) {
      np_NeighborSubscriptOffsets[i + c] = (signed char)imnhSubs[indx + c] - 2;
    }

    indx += 9;
  }

  numPixels = J->size[0] * J->size[1];
  emxInit_int32_T1(&locationStack, 2);
  if (isrow(J)) {
    for (pInd = 0; pInd + 1 <= numPixels; pInd++) {
      for (i = 0; i < 9; i++) {
        av[i] = (loffsets[i] + pInd) + 1;
      }

      if (np_ImageSize[0] == 0) {
        r = 0;
      } else {
        r = pInd - np_ImageSize[0] * div_s32(pInd, (int)np_ImageSize[0]);
      }

      c = pInd - r;
      if (np_ImageSize[0] == 0) {
        if (c == 0) {
          i = 0;
        } else if (c < 0) {
          i = MIN_int32_T;
        } else {
          i = MAX_int32_T;
        }
      } else if (np_ImageSize[0] == 1) {
        i = c;
      } else {
        if (c >= 0) {
          indx = c;
        } else if (c == MIN_int32_T) {
          indx = MAX_int32_T;
        } else {
          indx = -c;
        }

        i = div_s32(indx, (int)np_ImageSize[0]);
        indx -= i * np_ImageSize[0];
        if ((indx > 0) && (indx >= (np_ImageSize[0] >> 1) + (np_ImageSize[0] & 1)))
        {
          i++;
        }

        if (c < 0) {
          i = -i;
        }
      }

      pixelSub[1] = i + 1;
      pixelSub[0] = r + 1;
      for (c = 0; c < 2; c++) {
        pixelsPerImPage[c] = pixelSub[c];
      }

      bsxfun(np_NeighborSubscriptOffsets, pixelsPerImPage, imnhSubs);
      for (i = 0; i < 9; i++) {
        isInside[i] = true;
      }

      trueCount = 0;
      for (c = 0; c < 9; c++) {
        indx = 0;
        exitg1 = false;
        while ((!exitg1) && (indx < 2)) {
          if ((imnhSubs[c + 9 * indx] < 1) || (imnhSubs[c + 9 * indx] >
               np_ImageSize[indx])) {
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
        tmp_data[c] = imnhInds_data[c];
      }

      indx = 1;
      mtmp = J->data[tmp_data[0] - 1];
      if (trueCount > 1) {
        if (rtIsNaN(mtmp)) {
          i = 2;
          exitg1 = false;
          while ((!exitg1) && (i <= trueCount)) {
            indx = i;
            if (!rtIsNaN(J->data[tmp_data[i - 1] - 1])) {
              mtmp = J->data[tmp_data[i - 1] - 1];
              exitg1 = true;
            } else {
              i++;
            }
          }
        }

        if (indx < trueCount) {
          for (i = indx + 1; i <= trueCount; i++) {
            if (J->data[tmp_data[i - 1] - 1] > mtmp) {
              mtmp = J->data[tmp_data[i - 1] - 1];
            }
          }
        }
      }

      if ((mtmp < I->data[pInd]) || rtIsNaN(I->data[pInd])) {
      } else {
        mtmp = I->data[pInd];
      }

      J->data[pInd] = mtmp;
    }

    c = locationStack->size[0] * locationStack->size[1];
    locationStack->size[0] = 1;
    locationStack->size[1] = numPixels << 1;
    emxEnsureCapacity((emxArray__common *)locationStack, c, sizeof(int));
    stackTop = -1;
    for (pInd = numPixels - 1; pInd + 1 > 0; pInd--) {
      for (i = 0; i < 9; i++) {
        av[i] = (loffsets[i] + pInd) + 1;
      }

      if (np_ImageSize[0] == 0) {
        r = 0;
      } else {
        r = pInd - np_ImageSize[0] * div_s32(pInd, (int)np_ImageSize[0]);
      }

      c = pInd - r;
      if (np_ImageSize[0] == 0) {
        if (c == 0) {
          i = 0;
        } else if (c < 0) {
          i = MIN_int32_T;
        } else {
          i = MAX_int32_T;
        }
      } else if (np_ImageSize[0] == 1) {
        i = c;
      } else {
        if (c >= 0) {
          indx = c;
        } else if (c == MIN_int32_T) {
          indx = MAX_int32_T;
        } else {
          indx = -c;
        }

        i = div_s32(indx, (int)np_ImageSize[0]);
        indx -= i * np_ImageSize[0];
        if ((indx > 0) && (indx >= (np_ImageSize[0] >> 1) + (np_ImageSize[0] & 1)))
        {
          i++;
        }

        if (c < 0) {
          i = -i;
        }
      }

      b_pixelSub[1] = i + 1;
      b_pixelSub[0] = r + 1;
      for (c = 0; c < 2; c++) {
        pixelSub[c] = b_pixelSub[c];
      }

      bsxfun(np_NeighborSubscriptOffsets, pixelSub, imnhSubs);
      for (i = 0; i < 9; i++) {
        isInside[i] = true;
      }

      trueCount = 0;
      for (c = 0; c < 9; c++) {
        indx = 0;
        exitg1 = false;
        while ((!exitg1) && (indx < 2)) {
          if ((imnhSubs[c + 9 * indx] < 1) || (imnhSubs[c + 9 * indx] >
               np_ImageSize[indx])) {
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
        tmp_data[c] = imnhInds_data[c];
      }

      indx = 1;
      mtmp = J->data[tmp_data[0] - 1];
      if (trueCount > 1) {
        if (rtIsNaN(mtmp)) {
          i = 2;
          exitg1 = false;
          while ((!exitg1) && (i <= trueCount)) {
            indx = i;
            if (!rtIsNaN(J->data[tmp_data[i - 1] - 1])) {
              mtmp = J->data[tmp_data[i - 1] - 1];
              exitg1 = true;
            } else {
              i++;
            }
          }
        }

        if (indx < trueCount) {
          for (i = indx + 1; i <= trueCount; i++) {
            if (J->data[tmp_data[i - 1] - 1] > mtmp) {
              mtmp = J->data[tmp_data[i - 1] - 1];
            }
          }
        }
      }

      if ((mtmp < I->data[pInd]) || rtIsNaN(I->data[pInd])) {
      } else {
        mtmp = I->data[pInd];
      }

      J->data[pInd] = mtmp;
      c = 0;
      exitg1 = false;
      while ((!exitg1) && (c <= trueCount - 1)) {
        if ((J->data[imnhInds_data[c] - 1] < J->data[pInd]) && (J->
             data[imnhInds_data[c] - 1] < I->data[imnhInds_data[c] - 1])) {
          stackTop++;
          locationStack->data[stackTop] = pInd + 1;
          exitg1 = true;
        } else {
          c++;
        }
      }
    }
  } else {
    for (pInd = 0; pInd + 1 <= numPixels; pInd++) {
      for (i = 0; i < 9; i++) {
        av[i] = (loffsets[i] + pInd) + 1;
      }

      if (np_ImageSize[0] == 0) {
        r = 0;
      } else {
        r = pInd - np_ImageSize[0] * div_s32(pInd, (int)np_ImageSize[0]);
      }

      c = pInd - r;
      if (np_ImageSize[0] == 0) {
        if (c == 0) {
          i = 0;
        } else if (c < 0) {
          i = MIN_int32_T;
        } else {
          i = MAX_int32_T;
        }
      } else if (np_ImageSize[0] == 1) {
        i = c;
      } else {
        if (c >= 0) {
          indx = c;
        } else if (c == MIN_int32_T) {
          indx = MAX_int32_T;
        } else {
          indx = -c;
        }

        i = div_s32(indx, (int)np_ImageSize[0]);
        indx -= i * np_ImageSize[0];
        if ((indx > 0) && (indx >= (np_ImageSize[0] >> 1) + (np_ImageSize[0] & 1)))
        {
          i++;
        }

        if (c < 0) {
          i = -i;
        }
      }

      pixelSub[1] = i + 1;
      pixelSub[0] = r + 1;
      for (c = 0; c < 2; c++) {
        pixelsPerImPage[c] = pixelSub[c];
      }

      bsxfun(np_NeighborSubscriptOffsets, pixelsPerImPage, imnhSubs);
      for (i = 0; i < 9; i++) {
        isInside[i] = true;
      }

      trueCount = 0;
      for (c = 0; c < 9; c++) {
        indx = 0;
        exitg1 = false;
        while ((!exitg1) && (indx < 2)) {
          if ((imnhSubs[c + 9 * indx] < 1) || (imnhSubs[c + 9 * indx] >
               np_ImageSize[indx])) {
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

      indx = 1;
      mtmp = J->data[imnhInds_data[0] - 1];
      if (trueCount > 1) {
        if (rtIsNaN(mtmp)) {
          i = 2;
          exitg1 = false;
          while ((!exitg1) && (i <= trueCount)) {
            indx = i;
            if (!rtIsNaN(J->data[imnhInds_data[i - 1] - 1])) {
              mtmp = J->data[imnhInds_data[i - 1] - 1];
              exitg1 = true;
            } else {
              i++;
            }
          }
        }

        if (indx < trueCount) {
          while (indx + 1 <= trueCount) {
            if (J->data[imnhInds_data[indx] - 1] > mtmp) {
              mtmp = J->data[imnhInds_data[indx] - 1];
            }

            indx++;
          }
        }
      }

      if ((mtmp < I->data[pInd]) || rtIsNaN(I->data[pInd])) {
      } else {
        mtmp = I->data[pInd];
      }

      J->data[pInd] = mtmp;
    }

    c = locationStack->size[0] * locationStack->size[1];
    locationStack->size[0] = 1;
    locationStack->size[1] = numPixels << 1;
    emxEnsureCapacity((emxArray__common *)locationStack, c, sizeof(int));
    stackTop = -1;
    for (pInd = numPixels - 1; pInd + 1 > 0; pInd--) {
      for (i = 0; i < 9; i++) {
        av[i] = (loffsets[i] + pInd) + 1;
      }

      if (np_ImageSize[0] == 0) {
        r = 0;
      } else {
        r = pInd - np_ImageSize[0] * div_s32(pInd, (int)np_ImageSize[0]);
      }

      c = pInd - r;
      if (np_ImageSize[0] == 0) {
        if (c == 0) {
          i = 0;
        } else if (c < 0) {
          i = MIN_int32_T;
        } else {
          i = MAX_int32_T;
        }
      } else if (np_ImageSize[0] == 1) {
        i = c;
      } else {
        if (c >= 0) {
          indx = c;
        } else if (c == MIN_int32_T) {
          indx = MAX_int32_T;
        } else {
          indx = -c;
        }

        i = div_s32(indx, (int)np_ImageSize[0]);
        indx -= i * np_ImageSize[0];
        if ((indx > 0) && (indx >= (np_ImageSize[0] >> 1) + (np_ImageSize[0] & 1)))
        {
          i++;
        }

        if (c < 0) {
          i = -i;
        }
      }

      b_pixelSub[1] = i + 1;
      b_pixelSub[0] = r + 1;
      for (c = 0; c < 2; c++) {
        pixelSub[c] = b_pixelSub[c];
      }

      bsxfun(np_NeighborSubscriptOffsets, pixelSub, imnhSubs);
      for (i = 0; i < 9; i++) {
        isInside[i] = true;
      }

      trueCount = 0;
      for (c = 0; c < 9; c++) {
        indx = 0;
        exitg1 = false;
        while ((!exitg1) && (indx < 2)) {
          if ((imnhSubs[c + 9 * indx] < 1) || (imnhSubs[c + 9 * indx] >
               np_ImageSize[indx])) {
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

      indx = 1;
      mtmp = J->data[imnhInds_data[0] - 1];
      if (trueCount > 1) {
        if (rtIsNaN(mtmp)) {
          i = 2;
          exitg1 = false;
          while ((!exitg1) && (i <= trueCount)) {
            indx = i;
            if (!rtIsNaN(J->data[imnhInds_data[i - 1] - 1])) {
              mtmp = J->data[imnhInds_data[i - 1] - 1];
              exitg1 = true;
            } else {
              i++;
            }
          }
        }

        if (indx < trueCount) {
          while (indx + 1 <= trueCount) {
            if (J->data[imnhInds_data[indx] - 1] > mtmp) {
              mtmp = J->data[imnhInds_data[indx] - 1];
            }

            indx++;
          }
        }
      }

      if ((mtmp < I->data[pInd]) || rtIsNaN(I->data[pInd])) {
      } else {
        mtmp = I->data[pInd];
      }

      J->data[pInd] = mtmp;
      c = 0;
      exitg1 = false;
      while ((!exitg1) && (c <= trueCount - 1)) {
        if ((J->data[imnhInds_data[c] - 1] < J->data[pInd]) && (J->
             data[imnhInds_data[c] - 1] < I->data[imnhInds_data[c] - 1])) {
          stackTop++;
          locationStack->data[stackTop] = pInd + 1;
          exitg1 = true;
        } else {
          c++;
        }
      }
    }
  }

  while (stackTop + 1 > 0) {
    pInd = locationStack->data[stackTop] - 1;
    stackTop--;
    for (i = 0; i < 9; i++) {
      av[i] = (loffsets[i] + pInd) + 1;
    }

    if (np_ImageSize[0] == 0) {
      r = 0;
    } else {
      r = pInd - np_ImageSize[0] * div_s32(pInd, (int)np_ImageSize[0]);
    }

    c = pInd - r;
    if (np_ImageSize[0] == 0) {
      if (c == 0) {
        i = 0;
      } else if (c < 0) {
        i = MIN_int32_T;
      } else {
        i = MAX_int32_T;
      }
    } else if (np_ImageSize[0] == 1) {
      i = c;
    } else {
      if (c >= 0) {
        indx = c;
      } else if (c == MIN_int32_T) {
        indx = MAX_int32_T;
      } else {
        indx = -c;
      }

      i = div_s32(indx, (int)np_ImageSize[0]);
      indx -= i * np_ImageSize[0];
      if ((indx > 0) && (indx >= (np_ImageSize[0] >> 1) + (np_ImageSize[0] & 1)))
      {
        i++;
      }

      if (c < 0) {
        i = -i;
      }
    }

    c_pixelSub[1] = i + 1;
    c_pixelSub[0] = r + 1;
    for (c = 0; c < 2; c++) {
      b_pixelSub[c] = c_pixelSub[c];
    }

    bsxfun(np_NeighborSubscriptOffsets, b_pixelSub, imnhSubs);
    for (i = 0; i < 9; i++) {
      isInside[i] = true;
    }

    trueCount = 0;
    for (c = 0; c < 9; c++) {
      indx = 0;
      exitg1 = false;
      while ((!exitg1) && (indx < 2)) {
        if ((imnhSubs[c + 9 * indx] < 1) || (imnhSubs[c + 9 * indx] >
             np_ImageSize[indx])) {
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
      if ((J->data[imnhInds_data[c] - 1] < J->data[pInd]) && (J->
           data[imnhInds_data[c] - 1] != I->data[imnhInds_data[c] - 1])) {
        if ((J->data[pInd] < I->data[imnhInds_data[c] - 1]) || rtIsNaN(I->
             data[imnhInds_data[c] - 1])) {
          mtmp = J->data[pInd];
        } else {
          mtmp = I->data[imnhInds_data[c] - 1];
        }

        J->data[imnhInds_data[c] - 1] = mtmp;
        stackTop++;
        locationStack->data[stackTop] = imnhInds_data[c];
      }
    }
  }

  emxFree_int32_T(&locationStack);
}

//
// File trailer for imhmax.cpp
//
// [EOF]
//
