//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: imregionalmax.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 25-Jan-2017 16:02:21
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "imregionalmax.h"
#include "bsxfun.h"
#include "isequal.h"
#include "analyzeImage_rtwutil.h"

// Function Definitions

//
// Arguments    : const double varargin_1[809600]
//                boolean_T BW[809600]
// Return Type  : void
//
void imregionalmax(const double varargin_1[809600], boolean_T BW[809600])
{
  int np_ImageNeighborLinearOffsets[9];
  int np_NeighborSubscriptOffsets[18];
  int ck;
  boolean_T continuePropagation;
  static boolean_T bwpre[809600];
  static boolean_T imParams_bw[809600];
  int iv3[18];
  int a[9];
  int i;
  short pixelsPerImPage[2];
  short iv4[2];
  int pind;
  int r;
  signed char subs[2];
  int imnhSubs[18];
  signed char b_subs[2];
  int pixelSub[2];
  int y;
  int secondInd;
  int firstInd;
  boolean_T out_[736];
  int av[9];
  double pixel;
  int x;
  boolean_T exitg9;
  short b_pixelSub[2];
  int c_pixelSub[2];
  boolean_T isInside[9];
  int d_pixelSub[2];
  int trueCount;
  int b_trueCount;
  int e_pixelSub[2];
  boolean_T exitg8;
  boolean_T exitg6;
  int c_trueCount;
  int imnhInds_data[9];
  int b_imnhInds_data[9];
  double imnh_data[9];
  boolean_T exitg4;
  int d_trueCount;
  boolean_T exitg7;
  int c_imnhInds_data[9];
  boolean_T exitg5;
  boolean_T exitg2;
  int d_imnhInds_data[9];
  boolean_T exitg3;
  boolean_T exitg1;
  for (ck = 0; ck < 809600; ck++) {
    BW[ck] = true;
  }

  continuePropagation = true;
  while (continuePropagation) {
    memcpy(&bwpre[0], &BW[0], 809600U * sizeof(boolean_T));
    memcpy(&imParams_bw[0], &BW[0], 809600U * sizeof(boolean_T));
    memcpy(&iv3[0], &np_NeighborSubscriptOffsets[0], 18U * sizeof(int));
    for (i = 0; i < 9; i++) {
      a[i] = np_ImageNeighborLinearOffsets[i];
    }

    //  Process pixels with full neighborhood
    //  Process pixels with partial neighborhood
    //  Process pixels with full neighborhood
    //  Process pixels with partial neighborhood
    pixelsPerImPage[0] = 1;
    pixelsPerImPage[1] = 736;
    for (ck = 0; ck < 2; ck++) {
      iv4[ck] = (short)(364 * ck + 735);
    }

    i = 0;
    for (pind = 0; pind < 9; pind++) {
      r = (int)rt_remd_snf((1.0 + (double)pind) - 1.0, 3.0) + 1;
      subs[1] = (signed char)((int)(((double)(pind - r) + 1.0) / 3.0) + 1);
      subs[0] = (signed char)r;
      b_subs[0] = (signed char)r;
      b_subs[1] = (signed char)(subs[1] - 1);
      for (ck = 0; ck < 2; ck++) {
        iv3[i + 9 * ck] = subs[ck];
        pixelSub[ck] = b_subs[ck] * pixelsPerImPage[ck];
      }

      a[i] = pixelSub[0] + pixelSub[1];
      i++;
    }

    for (ck = 0; ck < 9; ck++) {
      a[ck] -= 738;
    }

    memcpy(&imnhSubs[0], &iv3[0], 18U * sizeof(int));
    i = 0;
    for (ck = 0; ck <= 10; ck += 9) {
      for (y = 0; y < 9; y++) {
        iv3[ck + y] = imnhSubs[i + y] - 2;
      }

      i += 9;
    }

    for (i = 0; i < 9; i++) {
      np_ImageNeighborLinearOffsets[i] = a[i];
    }

    memcpy(&np_NeighborSubscriptOffsets[0], &iv3[0], 18U * sizeof(int));
    for (secondInd = 1; secondInd + 1 <= iv4[1]; secondInd++) {
      for (firstInd = 1; firstInd + 1 <= iv4[0]; firstInd++) {
        pind = secondInd * 736 + firstInd;
        for (i = 0; i < 9; i++) {
          av[i] = (a[i] + pind) + 1;
        }

        pixel = varargin_1[pind];
        continuePropagation = imParams_bw[pind];
        if (imParams_bw[pind]) {
          //  Pixel has not already been set as non-max
          ck = 0;
          exitg9 = false;
          while ((!exitg9) && (ck < 9)) {
            if (varargin_1[av[ck] - 1] > pixel) {
              //  Set pixel to zero if any neighbor is greater
              continuePropagation = false;
              exitg9 = true;
            } else if ((varargin_1[av[ck] - 1] == pixel) && (!imParams_bw[av[ck]
                        - 1])) {
              //  Set pixel to zero if any equal neighbor is already set to zero 
              continuePropagation = false;
              exitg9 = true;
            } else {
              ck++;
            }
          }
        }

        out_[firstInd] = continuePropagation;
      }

      memcpy(&BW[secondInd * 736], &out_[0], 736U * sizeof(boolean_T));
    }

    for (firstInd = 0; firstInd < 736; firstInd++) {
      for (i = 0; i < 9; i++) {
        av[i] = (a[i] + firstInd) + 1;
      }

      r = firstInd - 736 * (firstInd / 736);
      ck = firstInd - r;
      if (ck >= 0) {
        y = ck;
      } else {
        y = -ck;
      }

      i = y / 736;
      x = y - i * 736;
      if ((x > 0) && (x >= 368)) {
        i++;
      }

      if (ck < 0) {
        i = -i;
      }

      b_pixelSub[1] = (short)(i + 1);
      b_pixelSub[0] = (short)(r + 1);
      for (ck = 0; ck < 2; ck++) {
        pixelSub[ck] = b_pixelSub[ck];
      }

      bsxfun(iv3, pixelSub, imnhSubs);
      for (i = 0; i < 9; i++) {
        isInside[i] = true;
      }

      trueCount = 0;
      for (x = 0; x < 9; x++) {
        ck = 0;
        exitg8 = false;
        while ((!exitg8) && (ck < 2)) {
          if ((imnhSubs[x + 9 * ck] < 1) || (imnhSubs[x + 9 * ck] > 736 + 364 *
               ck)) {
            isInside[x] = false;
            exitg8 = true;
          } else {
            ck++;
          }
        }

        if (isInside[x]) {
          trueCount++;
        }
      }

      ck = 0;
      for (i = 0; i < 9; i++) {
        if (isInside[i]) {
          imnhInds_data[ck] = av[i];
          ck++;
        }
      }

      for (ck = 0; ck < trueCount; ck++) {
        imnh_data[ck] = varargin_1[imnhInds_data[ck] - 1];
      }

      pixel = varargin_1[firstInd];
      continuePropagation = imParams_bw[firstInd];
      if (imParams_bw[firstInd]) {
        //  Pixel has not already been set as non-max
        ck = 0;
        exitg7 = false;
        while ((!exitg7) && (ck <= trueCount - 1)) {
          if (imnh_data[ck] > pixel) {
            //  Set pixel to zero if any neighbor is greater
            continuePropagation = false;
            exitg7 = true;
          } else if ((imnh_data[ck] == pixel) && (!imParams_bw[imnhInds_data[ck]
                      - 1])) {
            //  Set pixel to zero if any equal neighbor is already set to zero
            continuePropagation = false;
            exitg7 = true;
          } else {
            ck++;
          }
        }
      }

      BW[firstInd] = continuePropagation;
    }

    for (secondInd = iv4[1] + 1; secondInd < 1101; secondInd++) {
      for (firstInd = 0; firstInd < 736; firstInd++) {
        pind = (secondInd - 1) * 736 + firstInd;
        for (i = 0; i < 9; i++) {
          av[i] = (a[i] + pind) + 1;
        }

        r = pind - 736 * (pind / 736);
        ck = pind - r;
        y = ck / 736;
        x = ck - y * 736;
        if ((x > 0) && (x >= 368)) {
          y++;
        }

        c_pixelSub[1] = y + 1;
        c_pixelSub[0] = r + 1;
        for (ck = 0; ck < 2; ck++) {
          pixelSub[ck] = c_pixelSub[ck];
        }

        bsxfun(iv3, pixelSub, imnhSubs);
        for (i = 0; i < 9; i++) {
          isInside[i] = true;
        }

        b_trueCount = 0;
        for (x = 0; x < 9; x++) {
          ck = 0;
          exitg6 = false;
          while ((!exitg6) && (ck < 2)) {
            if ((imnhSubs[x + 9 * ck] < 1) || (imnhSubs[x + 9 * ck] > 736 + 364 *
                 ck)) {
              isInside[x] = false;
              exitg6 = true;
            } else {
              ck++;
            }
          }

          if (isInside[x]) {
            b_trueCount++;
          }
        }

        ck = 0;
        for (i = 0; i < 9; i++) {
          if (isInside[i]) {
            b_imnhInds_data[ck] = av[i];
            ck++;
          }
        }

        for (ck = 0; ck < b_trueCount; ck++) {
          imnh_data[ck] = varargin_1[b_imnhInds_data[ck] - 1];
        }

        pixel = varargin_1[pind];
        continuePropagation = imParams_bw[pind];
        if (imParams_bw[pind]) {
          //  Pixel has not already been set as non-max
          ck = 0;
          exitg5 = false;
          while ((!exitg5) && (ck <= b_trueCount - 1)) {
            if (imnh_data[ck] > pixel) {
              //  Set pixel to zero if any neighbor is greater
              continuePropagation = false;
              exitg5 = true;
            } else if ((imnh_data[ck] == pixel) &&
                       (!imParams_bw[b_imnhInds_data[ck] - 1])) {
              //  Set pixel to zero if any equal neighbor is already set to zero 
              continuePropagation = false;
              exitg5 = true;
            } else {
              ck++;
            }
          }
        }

        BW[pind] = continuePropagation;
      }
    }

    for (secondInd = 1; secondInd < 1101; secondInd++) {
      pind = (secondInd - 1) * 736;
      for (i = 0; i < 9; i++) {
        av[i] = (a[i] + pind) + 1;
      }

      r = pind - 736 * (pind / 736);
      ck = pind - r;
      if (ck >= 0) {
        y = ck;
      } else {
        y = -ck;
      }

      i = y / 736;
      x = y - i * 736;
      if ((x > 0) && (x >= 368)) {
        i++;
      }

      if (ck < 0) {
        i = -i;
      }

      d_pixelSub[1] = i + 1;
      d_pixelSub[0] = r + 1;
      for (ck = 0; ck < 2; ck++) {
        pixelSub[ck] = d_pixelSub[ck];
      }

      bsxfun(iv3, pixelSub, imnhSubs);
      for (i = 0; i < 9; i++) {
        isInside[i] = true;
      }

      c_trueCount = 0;
      for (x = 0; x < 9; x++) {
        ck = 0;
        exitg4 = false;
        while ((!exitg4) && (ck < 2)) {
          if ((imnhSubs[x + 9 * ck] < 1) || (imnhSubs[x + 9 * ck] > 736 + 364 *
               ck)) {
            isInside[x] = false;
            exitg4 = true;
          } else {
            ck++;
          }
        }

        if (isInside[x]) {
          c_trueCount++;
        }
      }

      ck = 0;
      for (i = 0; i < 9; i++) {
        if (isInside[i]) {
          c_imnhInds_data[ck] = av[i];
          ck++;
        }
      }

      for (ck = 0; ck < c_trueCount; ck++) {
        imnh_data[ck] = varargin_1[c_imnhInds_data[ck] - 1];
      }

      pixel = varargin_1[pind];
      continuePropagation = imParams_bw[pind];
      if (imParams_bw[pind]) {
        //  Pixel has not already been set as non-max
        ck = 0;
        exitg3 = false;
        while ((!exitg3) && (ck <= c_trueCount - 1)) {
          if (imnh_data[ck] > pixel) {
            //  Set pixel to zero if any neighbor is greater
            continuePropagation = false;
            exitg3 = true;
          } else if ((imnh_data[ck] == pixel) &&
                     (!imParams_bw[c_imnhInds_data[ck] - 1])) {
            //  Set pixel to zero if any equal neighbor is already set to zero
            continuePropagation = false;
            exitg3 = true;
          } else {
            ck++;
          }
        }
      }

      BW[pind] = continuePropagation;
    }

    for (secondInd = 1; secondInd < 1101; secondInd++) {
      firstInd = iv4[0] + 1;
      while (firstInd <= 736) {
        pind = (secondInd - 1) * 736 + 735;
        for (i = 0; i < 9; i++) {
          av[i] = (a[i] + pind) + 1;
        }

        r = pind - 736 * (pind / 736);
        ck = pind - r;
        if (ck >= 0) {
          y = ck;
        } else {
          y = -ck;
        }

        i = y / 736;
        x = y - i * 736;
        if ((x > 0) && (x >= 368)) {
          i++;
        }

        if (ck < 0) {
          i = -i;
        }

        e_pixelSub[1] = i + 1;
        e_pixelSub[0] = r + 1;
        for (ck = 0; ck < 2; ck++) {
          pixelSub[ck] = e_pixelSub[ck];
        }

        bsxfun(iv3, pixelSub, imnhSubs);
        for (i = 0; i < 9; i++) {
          isInside[i] = true;
        }

        d_trueCount = 0;
        for (x = 0; x < 9; x++) {
          ck = 0;
          exitg2 = false;
          while ((!exitg2) && (ck < 2)) {
            if ((imnhSubs[x + 9 * ck] < 1) || (imnhSubs[x + 9 * ck] > 736 + 364 *
                 ck)) {
              isInside[x] = false;
              exitg2 = true;
            } else {
              ck++;
            }
          }

          if (isInside[x]) {
            d_trueCount++;
          }
        }

        ck = 0;
        for (i = 0; i < 9; i++) {
          if (isInside[i]) {
            d_imnhInds_data[ck] = av[i];
            ck++;
          }
        }

        for (ck = 0; ck < d_trueCount; ck++) {
          imnh_data[ck] = varargin_1[d_imnhInds_data[ck] - 1];
        }

        pixel = varargin_1[pind];
        continuePropagation = imParams_bw[pind];
        if (imParams_bw[pind]) {
          //  Pixel has not already been set as non-max
          ck = 0;
          exitg1 = false;
          while ((!exitg1) && (ck <= d_trueCount - 1)) {
            if (imnh_data[ck] > pixel) {
              //  Set pixel to zero if any neighbor is greater
              continuePropagation = false;
              exitg1 = true;
            } else if ((imnh_data[ck] == pixel) &&
                       (!imParams_bw[d_imnhInds_data[ck] - 1])) {
              //  Set pixel to zero if any equal neighbor is already set to zero 
              continuePropagation = false;
              exitg1 = true;
            } else {
              ck++;
            }
          }
        }

        BW[pind] = continuePropagation;
        firstInd = 737;
      }
    }

    continuePropagation = !isequal(bwpre, BW);
  }
}

//
// File trailer for imregionalmax.cpp
//
// [EOF]
//
