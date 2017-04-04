//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: medfilt2.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "medfilt2.h"
#include "analyzeImage_emxutil.h"
#include "imregionalmax.h"
#include "median.h"
#include "isrow.h"
#include "regionprops.h"
#include "analyzeImage_rtwutil.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *varargin_1
//                emxArray_real_T *b
// Return Type  : void
//
void medfilt2(const emxArray_real_T *varargin_1, emxArray_real_T *b)
{
  int i;
  short np_ImageSize[2];
  int indx;
  short loffsets[25];
  int av[25];
  signed char soffsets[50];
  int imnhSubs[50];
  short pixelsPerImPage[2];
  short imSize[2];
  int pind;
  signed char subs[2];
  int r;
  signed char b_subs[2];
  int pixelSub[2];
  int secondInd;
  int u0;
  int u1;
  int firstInd;
  int minval;
  double out__data[3123];
  int bk;
  double imnh_data[625];
  int imnh[1];
  int b_pixelSub[2];
  boolean_T isInside[25];
  int imnhInds_data[25];
  int c_pixelSub[2];
  boolean_T exitg1;
  int tmp_data[25];
  int d_pixelSub[2];
  int e_pixelSub[2];
  if ((varargin_1->size[0] == 0) || (varargin_1->size[1] == 0)) {
    i = b->size[0] * b->size[1];
    b->size[0] = varargin_1->size[0];
    b->size[1] = varargin_1->size[1];
    emxEnsureCapacity((emxArray__common *)b, i, sizeof(double));
    indx = varargin_1->size[0] * varargin_1->size[1];
    for (i = 0; i < indx; i++) {
      b->data[i] = varargin_1->data[i];
    }
  } else {
    for (i = 0; i < 2; i++) {
      np_ImageSize[i] = (short)varargin_1->size[i];
    }

    i = b->size[0] * b->size[1];
    b->size[0] = varargin_1->size[0];
    b->size[1] = varargin_1->size[1];
    emxEnsureCapacity((emxArray__common *)b, i, sizeof(double));
    for (i = 0; i < 25; i++) {
      loffsets[i] = (short)av[i];
    }

    for (i = 0; i < 50; i++) {
      soffsets[i] = (signed char)imnhSubs[i];
    }

    //  Process pixels with full neighborhood
    //  Process pixels with partial neighborhood
    //  Process pixels with full neighborhood
    //  Process pixels with partial neighborhood
    pixelsPerImPage[0] = 1;
    pixelsPerImPage[1] = np_ImageSize[0];
    for (i = 0; i < 2; i++) {
      imSize[i] = (short)((short)(np_ImageSize[i] + 3) - 5);
    }

    indx = 0;
    for (pind = 0; pind < 25; pind++) {
      r = (int)rt_remd_snf((1.0 + (double)pind) - 1.0, 5.0) + 1;
      subs[1] = (signed char)((int)(((double)(pind - r) + 1.0) / 5.0) + 1);
      subs[0] = (signed char)r;
      b_subs[0] = (signed char)r;
      b_subs[1] = (signed char)(subs[1] - 1);
      for (i = 0; i < 2; i++) {
        soffsets[indx + 25 * i] = subs[i];
        pixelSub[i] = b_subs[i] * pixelsPerImPage[i];
      }

      loffsets[indx] = (short)((short)pixelSub[0] + (short)pixelSub[1]);
      indx++;
    }

    subs[0] = 3;
    subs[1] = 2;
    for (i = 0; i < 2; i++) {
      pixelSub[i] = subs[i] * pixelsPerImPage[i];
    }

    for (i = 0; i < 25; i++) {
      loffsets[i] -= (short)((short)pixelSub[1] + 3);
    }

    for (i = 0; i < 50; i++) {
      imnhSubs[i] = soffsets[i];
    }

    indx = 0;
    for (i = 0; i <= 26; i += 25) {
      for (r = 0; r < 25; r++) {
        soffsets[i + r] = (signed char)(imnhSubs[indx + r] - 3);
      }

      indx += 25;
    }

    for (secondInd = 2; secondInd + 1 <= imSize[1]; secondInd++) {
      indx = b->size[0];
      for (firstInd = 3; firstInd <= imSize[0]; firstInd++) {
        pind = secondInd * np_ImageSize[0] + firstInd;
        for (i = 0; i < 25; i++) {
          av[i] = loffsets[i] + pind;
        }

        if (isrow(varargin_1)) {
          bk = 1;
          r = 25;
          for (i = 0; i < 25; i++) {
            imnh_data[i] = varargin_1->data[av[i] - 1];
          }
        } else {
          bk = 25;
          r = 1;
          for (i = 0; i < 25; i++) {
            imnh_data[i] = varargin_1->data[av[i] - 1];
          }
        }

        imnh[0] = bk * r;
        out__data[firstInd - 1] = median(imnh_data, imnh);
      }

      for (i = 0; i < indx; i++) {
        b->data[i + b->size[0] * secondInd] = out__data[i];
      }
    }

    u0 = np_ImageSize[0];
    u1 = np_ImageSize[0];
    if (u0 < u1) {
      u1 = u0;
    }

    if (np_ImageSize[1] > 2) {
      minval = 2;
    } else {
      minval = np_ImageSize[1];
    }

    for (secondInd = 0; secondInd < (signed char)minval; secondInd++) {
      for (firstInd = 1; firstInd <= u1; firstInd++) {
        pind = secondInd * np_ImageSize[0] + firstInd;
        for (i = 0; i < 25; i++) {
          av[i] = loffsets[i] + pind;
        }

        r = pind - np_ImageSize[0] * div_s32(pind - 1, (int)np_ImageSize[0]);
        i = pind - r;
        if (np_ImageSize[0] == 1) {
          bk = i;
        } else {
          if (i >= 0) {
            indx = i;
          } else {
            indx = -i;
          }

          bk = div_s32(indx, (int)np_ImageSize[0]);
          indx -= bk * np_ImageSize[0];
          if ((indx > 0) && (indx >= (np_ImageSize[0] >> 1) + (np_ImageSize[0] &
                1))) {
            bk++;
          }

          if (i < 0) {
            bk = -bk;
          }
        }

        b_pixelSub[1] = bk + 1;
        b_pixelSub[0] = r;
        for (i = 0; i < 2; i++) {
          pixelSub[i] = b_pixelSub[i];
        }

        indx = 0;
        bk = 0;
        for (i = 0; i <= 26; i += 25) {
          for (r = 0; r < 25; r++) {
            imnhSubs[i + r] = soffsets[indx + r] + pixelSub[bk];
          }

          indx += 25;
          bk++;
        }

        for (i = 0; i < 25; i++) {
          isInside[i] = true;
        }

        for (indx = 0; indx < 25; indx++) {
          imnhInds_data[indx] = av[indx];
          i = 0;
          exitg1 = false;
          while ((!exitg1) && (i < 2)) {
            if ((imnhSubs[indx + 25 * i] < 1) || (imnhSubs[indx + 25 * i] >
                 np_ImageSize[i])) {
              isInside[indx] = false;
              imnhInds_data[indx] = 1;
              exitg1 = true;
            } else {
              i++;
            }
          }
        }

        if (isrow(varargin_1)) {
          for (i = 0; i < 25; i++) {
            tmp_data[i] = imnhInds_data[i];
          }

          bk = 1;
          r = 25;
          for (i = 0; i < 25; i++) {
            imnh_data[i] = varargin_1->data[tmp_data[i] - 1];
          }
        } else {
          bk = 25;
          r = 1;
          for (i = 0; i < 25; i++) {
            imnh_data[i] = varargin_1->data[imnhInds_data[i] - 1];
          }
        }

        for (i = 0; i < 25; i++) {
          if (!isInside[i]) {
            imnh_data[i] = 0.0;
          }
        }

        imnh[0] = bk * r;
        b->data[pind - 1] = median(imnh_data, imnh);
      }
    }

    u0 = np_ImageSize[0];
    u1 = np_ImageSize[0];
    if (u0 < u1) {
      u1 = u0;
    }

    u0 = np_ImageSize[1];
    minval = np_ImageSize[1];
    if (u0 < minval) {
      minval = u0;
    }

    u0 = (short)(imSize[1] + 1);
    if (!(u0 > 1)) {
      u0 = 1;
    }

    while (u0 <= minval) {
      for (firstInd = 1; firstInd <= u1; firstInd++) {
        pind = (u0 - 1) * np_ImageSize[0] + firstInd;
        for (i = 0; i < 25; i++) {
          av[i] = loffsets[i] + pind;
        }

        r = pind - np_ImageSize[0] * div_s32(pind - 1, (int)np_ImageSize[0]);
        i = pind - r;
        if (np_ImageSize[0] == 1) {
          bk = i;
        } else {
          if (i >= 0) {
            indx = i;
          } else if (i == MIN_int32_T) {
            indx = MAX_int32_T;
          } else {
            indx = -i;
          }

          bk = div_s32(indx, (int)np_ImageSize[0]);
          indx -= bk * np_ImageSize[0];
          if ((indx > 0) && (indx >= (np_ImageSize[0] >> 1) + (np_ImageSize[0] &
                1))) {
            bk++;
          }

          if (i < 0) {
            bk = -bk;
          }
        }

        c_pixelSub[1] = bk + 1;
        c_pixelSub[0] = r;
        for (i = 0; i < 2; i++) {
          pixelSub[i] = c_pixelSub[i];
        }

        indx = 0;
        bk = 0;
        for (i = 0; i <= 26; i += 25) {
          for (r = 0; r < 25; r++) {
            imnhSubs[i + r] = soffsets[indx + r] + pixelSub[bk];
          }

          indx += 25;
          bk++;
        }

        for (i = 0; i < 25; i++) {
          isInside[i] = true;
        }

        for (indx = 0; indx < 25; indx++) {
          imnhInds_data[indx] = av[indx];
          i = 0;
          exitg1 = false;
          while ((!exitg1) && (i < 2)) {
            if ((imnhSubs[indx + 25 * i] < 1) || (imnhSubs[indx + 25 * i] >
                 np_ImageSize[i])) {
              isInside[indx] = false;
              imnhInds_data[indx] = 1;
              exitg1 = true;
            } else {
              i++;
            }
          }
        }

        if (isrow(varargin_1)) {
          for (i = 0; i < 25; i++) {
            tmp_data[i] = imnhInds_data[i];
          }

          bk = 1;
          r = 25;
          for (i = 0; i < 25; i++) {
            imnh_data[i] = varargin_1->data[tmp_data[i] - 1];
          }
        } else {
          bk = 25;
          r = 1;
          for (i = 0; i < 25; i++) {
            imnh_data[i] = varargin_1->data[imnhInds_data[i] - 1];
          }
        }

        for (i = 0; i < 25; i++) {
          if (!isInside[i]) {
            imnh_data[i] = 0.0;
          }
        }

        imnh[0] = bk * r;
        b->data[pind - 1] = median(imnh_data, imnh);
      }

      u0++;
    }

    if (np_ImageSize[0] > 2) {
      minval = 2;
    } else {
      minval = np_ImageSize[0];
    }

    u0 = np_ImageSize[1];
    u1 = np_ImageSize[1];
    if (u0 < u1) {
      u1 = u0;
    }

    for (secondInd = 1; secondInd <= u1; secondInd++) {
      for (firstInd = 0; firstInd < (signed char)minval; firstInd++) {
        pind = (secondInd - 1) * np_ImageSize[0] + firstInd;
        for (i = 0; i < 25; i++) {
          av[i] = (loffsets[i] + pind) + 1;
        }

        r = pind - np_ImageSize[0] * div_s32(pind, (int)np_ImageSize[0]);
        i = pind - r;
        if (np_ImageSize[0] == 1) {
          bk = i;
        } else {
          if (i >= 0) {
            indx = i;
          } else if (i == MIN_int32_T) {
            indx = MAX_int32_T;
          } else {
            indx = -i;
          }

          bk = div_s32(indx, (int)np_ImageSize[0]);
          indx -= bk * np_ImageSize[0];
          if ((indx > 0) && (indx >= (np_ImageSize[0] >> 1) + (np_ImageSize[0] &
                1))) {
            bk++;
          }

          if (i < 0) {
            bk = -bk;
          }
        }

        d_pixelSub[1] = bk + 1;
        d_pixelSub[0] = r + 1;
        for (i = 0; i < 2; i++) {
          pixelSub[i] = d_pixelSub[i];
        }

        indx = 0;
        bk = 0;
        for (i = 0; i <= 26; i += 25) {
          for (r = 0; r < 25; r++) {
            imnhSubs[i + r] = soffsets[indx + r] + pixelSub[bk];
          }

          indx += 25;
          bk++;
        }

        for (i = 0; i < 25; i++) {
          isInside[i] = true;
        }

        for (indx = 0; indx < 25; indx++) {
          imnhInds_data[indx] = av[indx];
          i = 0;
          exitg1 = false;
          while ((!exitg1) && (i < 2)) {
            if ((imnhSubs[indx + 25 * i] < 1) || (imnhSubs[indx + 25 * i] >
                 np_ImageSize[i])) {
              isInside[indx] = false;
              imnhInds_data[indx] = 1;
              exitg1 = true;
            } else {
              i++;
            }
          }
        }

        if (isrow(varargin_1)) {
          for (i = 0; i < 25; i++) {
            tmp_data[i] = imnhInds_data[i];
          }

          bk = 1;
          r = 25;
          for (i = 0; i < 25; i++) {
            imnh_data[i] = varargin_1->data[tmp_data[i] - 1];
          }
        } else {
          bk = 25;
          r = 1;
          for (i = 0; i < 25; i++) {
            imnh_data[i] = varargin_1->data[imnhInds_data[i] - 1];
          }
        }

        for (i = 0; i < 25; i++) {
          if (!isInside[i]) {
            imnh_data[i] = 0.0;
          }
        }

        imnh[0] = bk * r;
        b->data[pind] = median(imnh_data, imnh);
      }
    }

    u0 = (short)(imSize[0] + 1);
    if (!(u0 > 1)) {
      u0 = 1;
    }

    indx = np_ImageSize[0];
    u1 = np_ImageSize[0];
    if (indx < u1) {
      u1 = indx;
    }

    indx = np_ImageSize[1];
    minval = np_ImageSize[1];
    if (indx < minval) {
      minval = indx;
    }

    for (secondInd = 1; secondInd <= minval; secondInd++) {
      for (firstInd = u0; firstInd <= u1; firstInd++) {
        pind = (secondInd - 1) * np_ImageSize[0] + firstInd;
        for (i = 0; i < 25; i++) {
          av[i] = loffsets[i] + pind;
        }

        r = pind - np_ImageSize[0] * div_s32(pind - 1, (int)np_ImageSize[0]);
        i = pind - r;
        if (np_ImageSize[0] == 1) {
          bk = i;
        } else {
          if (i >= 0) {
            indx = i;
          } else if (i == MIN_int32_T) {
            indx = MAX_int32_T;
          } else {
            indx = -i;
          }

          bk = div_s32(indx, (int)np_ImageSize[0]);
          indx -= bk * np_ImageSize[0];
          if ((indx > 0) && (indx >= (np_ImageSize[0] >> 1) + (np_ImageSize[0] &
                1))) {
            bk++;
          }

          if (i < 0) {
            bk = -bk;
          }
        }

        e_pixelSub[1] = bk + 1;
        e_pixelSub[0] = r;
        for (i = 0; i < 2; i++) {
          pixelSub[i] = e_pixelSub[i];
        }

        indx = 0;
        bk = 0;
        for (i = 0; i <= 26; i += 25) {
          for (r = 0; r < 25; r++) {
            imnhSubs[i + r] = soffsets[indx + r] + pixelSub[bk];
          }

          indx += 25;
          bk++;
        }

        for (i = 0; i < 25; i++) {
          isInside[i] = true;
        }

        for (indx = 0; indx < 25; indx++) {
          imnhInds_data[indx] = av[indx];
          i = 0;
          exitg1 = false;
          while ((!exitg1) && (i < 2)) {
            if ((imnhSubs[indx + 25 * i] < 1) || (imnhSubs[indx + 25 * i] >
                 np_ImageSize[i])) {
              isInside[indx] = false;
              imnhInds_data[indx] = 1;
              exitg1 = true;
            } else {
              i++;
            }
          }
        }

        if (isrow(varargin_1)) {
          for (i = 0; i < 25; i++) {
            tmp_data[i] = imnhInds_data[i];
          }

          bk = 1;
          r = 25;
          for (i = 0; i < 25; i++) {
            imnh_data[i] = varargin_1->data[tmp_data[i] - 1];
          }
        } else {
          bk = 25;
          r = 1;
          for (i = 0; i < 25; i++) {
            imnh_data[i] = varargin_1->data[imnhInds_data[i] - 1];
          }
        }

        for (i = 0; i < 25; i++) {
          if (!isInside[i]) {
            imnh_data[i] = 0.0;
          }
        }

        imnh[0] = bk * r;
        b->data[pind - 1] = median(imnh_data, imnh);
      }
    }
  }
}

//
// File trailer for medfilt2.cpp
//
// [EOF]
//
