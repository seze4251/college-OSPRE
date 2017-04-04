//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: imregionalmax.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "imregionalmax.h"
#include "isrow.h"
#include "bsxfun.h"
#include "regionprops.h"
#include "isequal.h"
#include "analyzeImage_emxutil.h"
#include "analyzeImage_rtwutil.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *varargin_1
//                emxArray_boolean_T *BW
// Return Type  : void
//
void imregionalmax(const emxArray_real_T *varargin_1, emxArray_boolean_T *BW)
{
  int i;
  short np_ImageSize[2];
  short imSize[2];
  int loop_ub;
  boolean_T continuePropagation;
  emxArray_boolean_T *bwpre;
  emxArray_boolean_T *imParams_bw;
  int loffsets[9];
  int np_ImageNeighborLinearOffsets[9];
  short pixelsPerImPage[2];
  int indx;
  int pind;
  signed char subs[2];
  int r;
  signed char b_subs[2];
  int pixelSub[2];
  int imnhSubs[18];
  int np_NeighborSubscriptOffsets[18];
  int secondInd;
  int u0;
  int u1;
  int firstInd;
  int minval;
  boolean_T out__data[3123];
  int av[9];
  int imnh_size_idx_1;
  double imnh_data[81];
  double pixel;
  boolean_T exitg1;
  double b_pixelSub[2];
  boolean_T isInside[9];
  int c_pixelSub[2];
  int imnhInds_data[9];
  int tmp_data[9];
  int d_pixelSub[2];
  int b_imnhInds_data[9];
  int e_pixelSub[2];
  int c_imnhInds_data[9];
  int d_imnhInds_data[9];
  for (i = 0; i < 2; i++) {
    np_ImageSize[i] = (short)varargin_1->size[i];
  }

  for (i = 0; i < 2; i++) {
    imSize[i] = (short)varargin_1->size[i];
  }

  i = BW->size[0] * BW->size[1];
  BW->size[0] = imSize[0];
  BW->size[1] = imSize[1];
  emxEnsureCapacity((emxArray__common *)BW, i, sizeof(boolean_T));
  loop_ub = imSize[0] * imSize[1];
  for (i = 0; i < loop_ub; i++) {
    BW->data[i] = true;
  }

  continuePropagation = true;
  emxInit_boolean_T(&bwpre, 2);
  emxInit_boolean_T(&imParams_bw, 2);
  while (continuePropagation) {
    i = bwpre->size[0] * bwpre->size[1];
    bwpre->size[0] = BW->size[0];
    bwpre->size[1] = BW->size[1];
    emxEnsureCapacity((emxArray__common *)bwpre, i, sizeof(boolean_T));
    loop_ub = BW->size[0] * BW->size[1];
    for (i = 0; i < loop_ub; i++) {
      bwpre->data[i] = BW->data[i];
    }

    i = imParams_bw->size[0] * imParams_bw->size[1];
    imParams_bw->size[0] = BW->size[0];
    imParams_bw->size[1] = BW->size[1];
    emxEnsureCapacity((emxArray__common *)imParams_bw, i, sizeof(boolean_T));
    loop_ub = BW->size[0] * BW->size[1];
    for (i = 0; i < loop_ub; i++) {
      imParams_bw->data[i] = BW->data[i];
    }

    for (i = 0; i < 9; i++) {
      loffsets[i] = np_ImageNeighborLinearOffsets[i];
    }

    //  Process pixels with full neighborhood
    //  Process pixels with partial neighborhood
    //  Process pixels with full neighborhood
    //  Process pixels with partial neighborhood
    pixelsPerImPage[0] = 1;
    pixelsPerImPage[1] = np_ImageSize[0];
    for (i = 0; i < 2; i++) {
      imSize[i] = (short)((short)(np_ImageSize[i] + 2) - 3);
    }

    indx = 0;
    for (pind = 0; pind < 9; pind++) {
      r = (int)rt_remd_snf((1.0 + (double)pind) - 1.0, 3.0) + 1;
      b_subs[1] = (signed char)((int)(((double)(pind - r) + 1.0) / 3.0) + 1);
      b_subs[0] = (signed char)r;
      subs[0] = (signed char)r;
      subs[1] = (signed char)(b_subs[1] - 1);
      for (i = 0; i < 2; i++) {
        np_NeighborSubscriptOffsets[indx + 9 * i] = b_subs[i];
        pixelSub[i] = subs[i] * pixelsPerImPage[i];
      }

      loffsets[indx] = (short)pixelSub[0] + (short)pixelSub[1];
      indx++;
    }

    subs[0] = 2;
    subs[1] = 1;
    for (i = 0; i < 2; i++) {
      pixelSub[i] = subs[i] * pixelsPerImPage[i];
    }

    for (i = 0; i < 9; i++) {
      loffsets[i] = (loffsets[i] - (short)pixelSub[1]) - 2;
    }

    memcpy(&imnhSubs[0], &np_NeighborSubscriptOffsets[0], 18U * sizeof(int));
    indx = 0;
    for (loop_ub = 0; loop_ub <= 10; loop_ub += 9) {
      for (i = 0; i < 9; i++) {
        np_NeighborSubscriptOffsets[loop_ub + i] = imnhSubs[indx + i] - 2;
      }

      indx += 9;
    }

    for (i = 0; i < 9; i++) {
      np_ImageNeighborLinearOffsets[i] = loffsets[i];
    }

    for (secondInd = 1; secondInd + 1 <= imSize[1]; secondInd++) {
      loop_ub = BW->size[0];
      for (firstInd = 1; firstInd + 1 <= imSize[0]; firstInd++) {
        pind = secondInd * np_ImageSize[0] + firstInd;
        for (i = 0; i < 9; i++) {
          av[i] = (loffsets[i] + pind) + 1;
        }

        if (isrow(varargin_1)) {
          r = 1;
          imnh_size_idx_1 = 9;
          for (i = 0; i < 9; i++) {
            imnh_data[i] = varargin_1->data[av[i] - 1];
          }
        } else {
          r = 9;
          imnh_size_idx_1 = 1;
          for (i = 0; i < 9; i++) {
            imnh_data[i] = varargin_1->data[av[i] - 1];
          }
        }

        pixel = varargin_1->data[pind];
        continuePropagation = imParams_bw->data[pind];
        if (imParams_bw->data[pind]) {
          //  Pixel has not already been set as non-max
          indx = 0;
          exitg1 = false;
          while ((!exitg1) && (indx <= r * imnh_size_idx_1 - 1)) {
            if (imnh_data[indx] > pixel) {
              //  Set pixel to zero if any neighbor is greater
              continuePropagation = false;
              exitg1 = true;
            } else if ((imnh_data[indx] == pixel) && (!imParams_bw->data[av[indx]
                        - 1])) {
              //  Set pixel to zero if any equal neighbor is already set to zero 
              continuePropagation = false;
              exitg1 = true;
            } else {
              indx++;
            }
          }
        }

        out__data[firstInd] = continuePropagation;
      }

      for (i = 0; i < loop_ub; i++) {
        BW->data[i + BW->size[0] * secondInd] = out__data[i];
      }
    }

    u0 = np_ImageSize[0];
    u1 = np_ImageSize[0];
    if (u0 < u1) {
      u1 = u0;
    }

    if (np_ImageSize[1] > 1) {
      minval = 1;
    } else {
      minval = np_ImageSize[1];
    }

    secondInd = 0;
    while (secondInd <= (signed char)minval - 1) {
      for (firstInd = 0; firstInd + 1 <= u1; firstInd++) {
        for (i = 0; i < 9; i++) {
          av[i] = (loffsets[i] + firstInd) + 1;
        }

        if (np_ImageSize[0] == 0) {
          r = 0;
        } else {
          r = firstInd - np_ImageSize[0] * div_s32(firstInd, (int)np_ImageSize[0]);
        }

        loop_ub = firstInd - r;
        if (np_ImageSize[0] == 0) {
          if (loop_ub == 0) {
            i = 0;
          } else if (loop_ub < 0) {
            i = MIN_int32_T;
          } else {
            i = MAX_int32_T;
          }
        } else if (np_ImageSize[0] == 1) {
          i = loop_ub;
        } else {
          if (loop_ub >= 0) {
            indx = loop_ub;
          } else {
            indx = -loop_ub;
          }

          i = div_s32(indx, (int)np_ImageSize[0]);
          indx -= i * np_ImageSize[0];
          if ((indx > 0) && (indx >= (np_ImageSize[0] >> 1) + (np_ImageSize[0] &
                1))) {
            i++;
          }

          if (loop_ub < 0) {
            i = -i;
          }
        }

        b_pixelSub[1] = i + 1;
        b_pixelSub[0] = (double)r + 1.0;
        for (i = 0; i < 2; i++) {
          pixelSub[i] = (int)b_pixelSub[i];
        }

        bsxfun(np_NeighborSubscriptOffsets, pixelSub, imnhSubs);
        for (i = 0; i < 9; i++) {
          isInside[i] = true;
        }

        loop_ub = 0;
        for (i = 0; i < 9; i++) {
          indx = 0;
          exitg1 = false;
          while ((!exitg1) && (indx < 2)) {
            if ((imnhSubs[i + 9 * indx] < 1) || (imnhSubs[i + 9 * indx] >
                 np_ImageSize[indx])) {
              isInside[i] = false;
              exitg1 = true;
            } else {
              indx++;
            }
          }

          if (isInside[i]) {
            loop_ub++;
          }
        }

        indx = 0;
        for (i = 0; i < 9; i++) {
          if (isInside[i]) {
            imnhInds_data[indx] = av[i];
            indx++;
          }
        }

        if (isrow(varargin_1)) {
          for (i = 0; i < loop_ub; i++) {
            tmp_data[i] = imnhInds_data[i];
          }

          r = 1;
          imnh_size_idx_1 = loop_ub;
          for (i = 0; i < loop_ub; i++) {
            imnh_data[i] = varargin_1->data[tmp_data[i] - 1];
          }
        } else {
          r = loop_ub;
          imnh_size_idx_1 = 1;
          for (i = 0; i < loop_ub; i++) {
            imnh_data[i] = varargin_1->data[imnhInds_data[i] - 1];
          }
        }

        pixel = varargin_1->data[firstInd];
        continuePropagation = imParams_bw->data[firstInd];
        if (imParams_bw->data[firstInd]) {
          //  Pixel has not already been set as non-max
          indx = 0;
          exitg1 = false;
          while ((!exitg1) && (indx <= r * imnh_size_idx_1 - 1)) {
            if (imnh_data[indx] > pixel) {
              //  Set pixel to zero if any neighbor is greater
              continuePropagation = false;
              exitg1 = true;
            } else if ((imnh_data[indx] == pixel) && (!imParams_bw->
                        data[imnhInds_data[indx] - 1])) {
              //  Set pixel to zero if any equal neighbor is already set to zero 
              continuePropagation = false;
              exitg1 = true;
            } else {
              indx++;
            }
          }
        }

        BW->data[firstInd] = continuePropagation;
      }

      secondInd = 1;
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
      for (firstInd = 0; firstInd + 1 <= u1; firstInd++) {
        pind = (u0 - 1) * np_ImageSize[0] + firstInd;
        for (i = 0; i < 9; i++) {
          av[i] = (loffsets[i] + pind) + 1;
        }

        if (np_ImageSize[0] == 0) {
          r = 0;
        } else {
          r = pind - np_ImageSize[0] * div_s32(pind, (int)np_ImageSize[0]);
        }

        loop_ub = pind - r;
        if (np_ImageSize[0] == 0) {
          if (loop_ub == 0) {
            i = 0;
          } else if (loop_ub < 0) {
            i = MIN_int32_T;
          } else {
            i = MAX_int32_T;
          }
        } else if (np_ImageSize[0] == 1) {
          i = loop_ub;
        } else {
          if (loop_ub >= 0) {
            indx = loop_ub;
          } else if (loop_ub == MIN_int32_T) {
            indx = MAX_int32_T;
          } else {
            indx = -loop_ub;
          }

          i = div_s32(indx, (int)np_ImageSize[0]);
          indx -= i * np_ImageSize[0];
          if ((indx > 0) && (indx >= (np_ImageSize[0] >> 1) + (np_ImageSize[0] &
                1))) {
            i++;
          }

          if (loop_ub < 0) {
            i = -i;
          }
        }

        c_pixelSub[1] = i + 1;
        c_pixelSub[0] = r + 1;
        for (i = 0; i < 2; i++) {
          pixelSub[i] = c_pixelSub[i];
        }

        bsxfun(np_NeighborSubscriptOffsets, pixelSub, imnhSubs);
        for (i = 0; i < 9; i++) {
          isInside[i] = true;
        }

        loop_ub = 0;
        for (i = 0; i < 9; i++) {
          indx = 0;
          exitg1 = false;
          while ((!exitg1) && (indx < 2)) {
            if ((imnhSubs[i + 9 * indx] < 1) || (imnhSubs[i + 9 * indx] >
                 np_ImageSize[indx])) {
              isInside[i] = false;
              exitg1 = true;
            } else {
              indx++;
            }
          }

          if (isInside[i]) {
            loop_ub++;
          }
        }

        indx = 0;
        for (i = 0; i < 9; i++) {
          if (isInside[i]) {
            b_imnhInds_data[indx] = av[i];
            indx++;
          }
        }

        if (isrow(varargin_1)) {
          for (i = 0; i < loop_ub; i++) {
            tmp_data[i] = b_imnhInds_data[i];
          }

          r = 1;
          imnh_size_idx_1 = loop_ub;
          for (i = 0; i < loop_ub; i++) {
            imnh_data[i] = varargin_1->data[tmp_data[i] - 1];
          }
        } else {
          r = loop_ub;
          imnh_size_idx_1 = 1;
          for (i = 0; i < loop_ub; i++) {
            imnh_data[i] = varargin_1->data[b_imnhInds_data[i] - 1];
          }
        }

        pixel = varargin_1->data[pind];
        continuePropagation = imParams_bw->data[pind];
        if (imParams_bw->data[pind]) {
          //  Pixel has not already been set as non-max
          indx = 0;
          exitg1 = false;
          while ((!exitg1) && (indx <= r * imnh_size_idx_1 - 1)) {
            if (imnh_data[indx] > pixel) {
              //  Set pixel to zero if any neighbor is greater
              continuePropagation = false;
              exitg1 = true;
            } else if ((imnh_data[indx] == pixel) && (!imParams_bw->
                        data[b_imnhInds_data[indx] - 1])) {
              //  Set pixel to zero if any equal neighbor is already set to zero 
              continuePropagation = false;
              exitg1 = true;
            } else {
              indx++;
            }
          }
        }

        BW->data[pind] = continuePropagation;
      }

      u0++;
    }

    if (np_ImageSize[0] > 1) {
      minval = 1;
    } else {
      minval = np_ImageSize[0];
    }

    u0 = np_ImageSize[1];
    u1 = np_ImageSize[1];
    if (u0 < u1) {
      u1 = u0;
    }

    for (secondInd = 1; secondInd <= u1; secondInd++) {
      firstInd = 0;
      while (firstInd <= (signed char)minval - 1) {
        pind = (secondInd - 1) * np_ImageSize[0];
        for (i = 0; i < 9; i++) {
          av[i] = (loffsets[i] + pind) + 1;
        }

        if (np_ImageSize[0] == 0) {
          r = 0;
        } else {
          r = pind - np_ImageSize[0] * div_s32(pind, (int)np_ImageSize[0]);
        }

        loop_ub = pind - r;
        if (np_ImageSize[0] == 0) {
          if (loop_ub == 0) {
            i = 0;
          } else if (loop_ub < 0) {
            i = MIN_int32_T;
          } else {
            i = MAX_int32_T;
          }
        } else if (np_ImageSize[0] == 1) {
          i = loop_ub;
        } else {
          if (loop_ub >= 0) {
            indx = loop_ub;
          } else if (loop_ub == MIN_int32_T) {
            indx = MAX_int32_T;
          } else {
            indx = -loop_ub;
          }

          i = div_s32(indx, (int)np_ImageSize[0]);
          indx -= i * np_ImageSize[0];
          if ((indx > 0) && (indx >= (np_ImageSize[0] >> 1) + (np_ImageSize[0] &
                1))) {
            i++;
          }

          if (loop_ub < 0) {
            i = -i;
          }
        }

        d_pixelSub[1] = i + 1;
        d_pixelSub[0] = r + 1;
        for (i = 0; i < 2; i++) {
          pixelSub[i] = d_pixelSub[i];
        }

        bsxfun(np_NeighborSubscriptOffsets, pixelSub, imnhSubs);
        for (i = 0; i < 9; i++) {
          isInside[i] = true;
        }

        loop_ub = 0;
        for (i = 0; i < 9; i++) {
          indx = 0;
          exitg1 = false;
          while ((!exitg1) && (indx < 2)) {
            if ((imnhSubs[i + 9 * indx] < 1) || (imnhSubs[i + 9 * indx] >
                 np_ImageSize[indx])) {
              isInside[i] = false;
              exitg1 = true;
            } else {
              indx++;
            }
          }

          if (isInside[i]) {
            loop_ub++;
          }
        }

        indx = 0;
        for (i = 0; i < 9; i++) {
          if (isInside[i]) {
            c_imnhInds_data[indx] = av[i];
            indx++;
          }
        }

        if (isrow(varargin_1)) {
          for (i = 0; i < loop_ub; i++) {
            tmp_data[i] = c_imnhInds_data[i];
          }

          r = 1;
          imnh_size_idx_1 = loop_ub;
          for (i = 0; i < loop_ub; i++) {
            imnh_data[i] = varargin_1->data[tmp_data[i] - 1];
          }
        } else {
          r = loop_ub;
          imnh_size_idx_1 = 1;
          for (i = 0; i < loop_ub; i++) {
            imnh_data[i] = varargin_1->data[c_imnhInds_data[i] - 1];
          }
        }

        pixel = varargin_1->data[pind];
        continuePropagation = imParams_bw->data[pind];
        if (imParams_bw->data[pind]) {
          //  Pixel has not already been set as non-max
          indx = 0;
          exitg1 = false;
          while ((!exitg1) && (indx <= r * imnh_size_idx_1 - 1)) {
            if (imnh_data[indx] > pixel) {
              //  Set pixel to zero if any neighbor is greater
              continuePropagation = false;
              exitg1 = true;
            } else if ((imnh_data[indx] == pixel) && (!imParams_bw->
                        data[c_imnhInds_data[indx] - 1])) {
              //  Set pixel to zero if any equal neighbor is already set to zero 
              continuePropagation = false;
              exitg1 = true;
            } else {
              indx++;
            }
          }
        }

        BW->data[pind] = continuePropagation;
        firstInd = 1;
      }
    }

    u0 = (short)(imSize[0] + 1);
    if (!(u0 > 1)) {
      u0 = 1;
    }

    loop_ub = np_ImageSize[0];
    u1 = np_ImageSize[0];
    if (loop_ub < u1) {
      u1 = loop_ub;
    }

    loop_ub = np_ImageSize[1];
    minval = np_ImageSize[1];
    if (loop_ub < minval) {
      minval = loop_ub;
    }

    for (secondInd = 1; secondInd <= minval; secondInd++) {
      for (firstInd = u0; firstInd <= u1; firstInd++) {
        pind = ((secondInd - 1) * np_ImageSize[0] + firstInd) - 1;
        for (i = 0; i < 9; i++) {
          av[i] = (loffsets[i] + pind) + 1;
        }

        if (np_ImageSize[0] == 0) {
          r = 0;
        } else {
          r = pind - np_ImageSize[0] * div_s32(pind, (int)np_ImageSize[0]);
        }

        loop_ub = pind - r;
        if (np_ImageSize[0] == 0) {
          if (loop_ub == 0) {
            i = 0;
          } else if (loop_ub < 0) {
            i = MIN_int32_T;
          } else {
            i = MAX_int32_T;
          }
        } else if (np_ImageSize[0] == 1) {
          i = loop_ub;
        } else {
          if (loop_ub >= 0) {
            indx = loop_ub;
          } else if (loop_ub == MIN_int32_T) {
            indx = MAX_int32_T;
          } else {
            indx = -loop_ub;
          }

          i = div_s32(indx, (int)np_ImageSize[0]);
          indx -= i * np_ImageSize[0];
          if ((indx > 0) && (indx >= (np_ImageSize[0] >> 1) + (np_ImageSize[0] &
                1))) {
            i++;
          }

          if (loop_ub < 0) {
            i = -i;
          }
        }

        e_pixelSub[1] = i + 1;
        e_pixelSub[0] = r + 1;
        for (i = 0; i < 2; i++) {
          pixelSub[i] = e_pixelSub[i];
        }

        bsxfun(np_NeighborSubscriptOffsets, pixelSub, imnhSubs);
        for (i = 0; i < 9; i++) {
          isInside[i] = true;
        }

        loop_ub = 0;
        for (i = 0; i < 9; i++) {
          indx = 0;
          exitg1 = false;
          while ((!exitg1) && (indx < 2)) {
            if ((imnhSubs[i + 9 * indx] < 1) || (imnhSubs[i + 9 * indx] >
                 np_ImageSize[indx])) {
              isInside[i] = false;
              exitg1 = true;
            } else {
              indx++;
            }
          }

          if (isInside[i]) {
            loop_ub++;
          }
        }

        indx = 0;
        for (i = 0; i < 9; i++) {
          if (isInside[i]) {
            d_imnhInds_data[indx] = av[i];
            indx++;
          }
        }

        if (isrow(varargin_1)) {
          for (i = 0; i < loop_ub; i++) {
            tmp_data[i] = d_imnhInds_data[i];
          }

          r = 1;
          imnh_size_idx_1 = loop_ub;
          for (i = 0; i < loop_ub; i++) {
            imnh_data[i] = varargin_1->data[tmp_data[i] - 1];
          }
        } else {
          r = loop_ub;
          imnh_size_idx_1 = 1;
          for (i = 0; i < loop_ub; i++) {
            imnh_data[i] = varargin_1->data[d_imnhInds_data[i] - 1];
          }
        }

        pixel = varargin_1->data[pind];
        continuePropagation = imParams_bw->data[pind];
        if (imParams_bw->data[pind]) {
          //  Pixel has not already been set as non-max
          indx = 0;
          exitg1 = false;
          while ((!exitg1) && (indx <= r * imnh_size_idx_1 - 1)) {
            if (imnh_data[indx] > pixel) {
              //  Set pixel to zero if any neighbor is greater
              continuePropagation = false;
              exitg1 = true;
            } else if ((imnh_data[indx] == pixel) && (!imParams_bw->
                        data[d_imnhInds_data[indx] - 1])) {
              //  Set pixel to zero if any equal neighbor is already set to zero 
              continuePropagation = false;
              exitg1 = true;
            } else {
              indx++;
            }
          }
        }

        BW->data[pind] = continuePropagation;
      }
    }

    continuePropagation = !isequal(bwpre, BW);
  }

  emxFree_boolean_T(&imParams_bw);
  emxFree_boolean_T(&bwpre);
}

//
// File trailer for imregionalmax.cpp
//
// [EOF]
//
