//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: medfilt2.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 14-Feb-2017 14:49:57
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "medfilt2.h"
#include "imregionalmax.h"
#include "quickselect.h"
#include "sort3.h"
#include "analyzeImage_rtwutil.h"

// Function Definitions

//
// Arguments    : const double varargin_1[809600]
//                double b[809600]
// Return Type  : void
//
void medfilt2(const double varargin_1[809600], double b[809600])
{
  int imnhInds_[25];
  int imnhSubs[50];
  signed char iv0[50];
  int i;
  short a[25];
  short pixelsPerImPage[2];
  short iv1[2];
  int indx;
  int ia;
  int ngroupsof5;
  signed char subs[2];
  signed char b_subs[2];
  int pixelSub[2];
  int midm1;
  int secondInd;
  int k;
  double out_[736];
  int firstInd;
  double imnh[25];
  int exitg9;
  int x;
  double vref;
  int ib;
  int ilast;
  int b_pixelSub[2];
  int oldnv;
  boolean_T checkspeed;
  short c_pixelSub[2];
  boolean_T isslow;
  boolean_T exitg10;
  double v[25];
  int d_pixelSub[2];
  boolean_T isInside[25];
  int e_pixelSub[2];
  int imnhInds_data[25];
  int b_imnhInds_data[25];
  double vk;
  double imnh_data[25];
  boolean_T exitg6;
  boolean_T exitg8;
  boolean_T guard1 = false;
  int c_imnhInds_data[25];
  int exitg5;
  int imnh_size[1];
  int exitg7;
  int d_imnhInds_data[25];
  boolean_T exitg4;
  boolean_T exitg2;
  int exitg3;
  int exitg1;
  for (i = 0; i < 50; i++) {
    iv0[i] = (signed char)imnhSubs[i];
  }

  for (i = 0; i < 25; i++) {
    a[i] = (short)imnhInds_[i];
  }

  //  Process pixels with full neighborhood
  //  Process pixels with partial neighborhood
  //  Process pixels with full neighborhood
  //  Process pixels with partial neighborhood
  pixelsPerImPage[0] = 1;
  pixelsPerImPage[1] = 736;
  for (i = 0; i < 2; i++) {
    iv1[i] = (short)(364 * i + 734);
  }

  indx = 0;
  for (ia = 0; ia < 25; ia++) {
    ngroupsof5 = (int)rt_remd_snf((1.0 + (double)ia) - 1.0, 5.0) + 1;
    subs[1] = (signed char)((int)(((double)(ia - ngroupsof5) + 1.0) / 5.0) + 1);
    subs[0] = (signed char)ngroupsof5;
    b_subs[0] = (signed char)ngroupsof5;
    b_subs[1] = (signed char)(subs[1] - 1);
    for (i = 0; i < 2; i++) {
      iv0[indx + 25 * i] = subs[i];
      pixelSub[i] = b_subs[i] * pixelsPerImPage[i];
    }

    a[indx] = (short)(pixelSub[0] + pixelSub[1]);
    indx++;
  }

  for (i = 0; i < 25; i++) {
    a[i] = (short)(a[i] - 1475);
  }

  for (i = 0; i < 50; i++) {
    imnhSubs[i] = iv0[i];
  }

  indx = 0;
  for (midm1 = 0; midm1 <= 26; midm1 += 25) {
    for (k = 0; k < 25; k++) {
      iv0[midm1 + k] = (signed char)(imnhSubs[indx + k] - 3);
    }

    indx += 25;
  }

  for (secondInd = 2; secondInd + 1 <= iv1[1]; secondInd++) {
    for (firstInd = 3; firstInd <= iv1[0]; firstInd++) {
      ia = secondInd * 736 + firstInd;
      for (i = 0; i < 25; i++) {
        imnhInds_[i] = a[i] + ia;
        imnh[i] = varargin_1[(a[i] + ia) - 1];
      }

      k = 0;
      do {
        exitg9 = 0;
        if (k + 1 < 26) {
          if (rtIsNaN(varargin_1[imnhInds_[k] - 1])) {
            vref = varargin_1[imnhInds_[k] - 1];
            exitg9 = 1;
          } else {
            k++;
          }
        } else {
          indx = 12;
          ia = 0;
          ib = 25;
          ilast = 24;
          oldnv = 25;
          checkspeed = false;
          isslow = false;
          exitg10 = false;
          while ((!exitg10) && (ia + 1 < ib)) {
            memcpy(&v[0], &imnh[0], 25U * sizeof(double));
            vref = imnh[indx];
            v[indx] = imnh[ib - 1];
            v[ib - 1] = imnh[indx];
            ilast = ia;
            i = -1;
            for (k = ia; k + 1 < ib; k++) {
              vk = v[k];
              if (v[k] == vref) {
                v[k] = v[ilast];
                v[ilast] = vk;
                i++;
                ilast++;
              } else {
                if (v[k] < vref) {
                  v[k] = v[ilast];
                  v[ilast] = vk;
                  ilast++;
                }
              }
            }

            v[ib - 1] = v[ilast];
            v[ilast] = imnh[indx];
            memcpy(&imnh[0], &v[0], 25U * sizeof(double));
            guard1 = false;
            if (13 <= ilast + 1) {
              if (13 >= ilast - i) {
                exitg10 = true;
              } else {
                ib = ilast;
                guard1 = true;
              }
            } else {
              ia = ilast + 1;
              guard1 = true;
            }

            if (guard1) {
              x = ib - ia;
              if (checkspeed) {
                isslow = (x > oldnv / 2);
                oldnv = x;
              }

              checkspeed = !checkspeed;
              if (isslow) {
                while (x > 1) {
                  ngroupsof5 = x / 5;
                  midm1 = x - ngroupsof5 * 5;
                  x = ngroupsof5;
                  for (k = -1; k + 2 <= ngroupsof5; k++) {
                    indx = (ia + (k + 1) * 5) + 1;
                    indx = thirdOfFive(imnh, indx, indx + 4) - 1;
                    i = (ia + k) + 1;
                    vref = imnh[i];
                    imnh[i] = imnh[indx];
                    imnh[indx] = vref;
                  }

                  if (midm1 > 0) {
                    indx = (ia + ngroupsof5 * 5) + 1;
                    indx = thirdOfFive(imnh, indx, (indx + midm1) - 1) - 1;
                    i = ia + ngroupsof5;
                    vref = imnh[i];
                    imnh[i] = imnh[indx];
                    imnh[indx] = vref;
                    x = ngroupsof5 + 1;
                  }
                }
              } else {
                if (x >= 3) {
                  indx = (ia + (x - 1) / 2) + 1;
                  sort3(ia + 1, v[ia], indx, v[indx - 1], ib, v[ib - 1], &x, &i,
                        &ngroupsof5);
                  if (i > ia + 1) {
                    imnh[ia] = v[i - 1];
                    imnh[i - 1] = v[ia];
                  }
                }
              }

              indx = ia;
              ilast = ib - 1;
            }
          }

          vref = imnh[ilast];
          exitg9 = 1;
        }
      } while (exitg9 == 0);

      out_[firstInd - 1] = vref;
    }

    memcpy(&b[secondInd * 736], &out_[0], 736U * sizeof(double));
  }

  for (secondInd = 0; secondInd < 2; secondInd++) {
    for (firstInd = 0; firstInd < 736; firstInd++) {
      ia = (secondInd * 736 + firstInd) + 1;
      for (i = 0; i < 25; i++) {
        imnhInds_[i] = a[i] + ia;
      }

      ngroupsof5 = ia - 736 * ((ia - 1) / 736);
      indx = ia - ngroupsof5;
      if (indx >= 0) {
        i = indx;
      } else {
        i = -indx;
      }

      midm1 = i / 736;
      x = i - midm1 * 736;
      if ((x > 0) && (x >= 368)) {
        midm1++;
      }

      if (indx < 0) {
        midm1 = -midm1;
      }

      c_pixelSub[1] = (short)(midm1 + 1);
      c_pixelSub[0] = (short)ngroupsof5;
      for (i = 0; i < 2; i++) {
        pixelSub[i] = c_pixelSub[i];
      }

      indx = 0;
      i = 0;
      for (midm1 = 0; midm1 <= 26; midm1 += 25) {
        for (k = 0; k < 25; k++) {
          imnhSubs[midm1 + k] = iv0[indx + k] + pixelSub[i];
        }

        indx += 25;
        i++;
      }

      for (i = 0; i < 25; i++) {
        isInside[i] = true;
      }

      for (midm1 = 0; midm1 < 25; midm1++) {
        b_imnhInds_data[midm1] = imnhInds_[midm1];
        indx = 0;
        exitg8 = false;
        while ((!exitg8) && (indx < 2)) {
          if ((imnhSubs[midm1 + 25 * indx] < 1) || (imnhSubs[midm1 + 25 * indx] >
               736 + 364 * indx)) {
            isInside[midm1] = false;
            b_imnhInds_data[midm1] = 1;
            exitg8 = true;
          } else {
            indx++;
          }
        }
      }

      for (i = 0; i < 25; i++) {
        imnh_data[i] = varargin_1[b_imnhInds_data[i] - 1];
      }

      for (i = 0; i < 25; i++) {
        if (!isInside[i]) {
          imnh_data[i] = 0.0;
        }
      }

      k = 0;
      do {
        exitg7 = 0;
        if (k + 1 <= 25) {
          if (rtIsNaN(imnh_data[k])) {
            vref = imnh_data[k];
            exitg7 = 1;
          } else {
            k++;
          }
        } else {
          imnh_size[0] = 25;
          quickselect(imnh_data, imnh_size, 13, 25, &vref, &indx, &i);
          exitg7 = 1;
        }
      } while (exitg7 == 0);

      b[ia - 1] = vref;
    }
  }

  for (secondInd = iv1[1] + 1; secondInd < 1101; secondInd++) {
    for (firstInd = 0; firstInd < 736; firstInd++) {
      ia = ((secondInd - 1) * 736 + firstInd) + 1;
      for (i = 0; i < 25; i++) {
        imnhInds_[i] = a[i] + ia;
      }

      ngroupsof5 = ia - 736 * ((ia - 1) / 736);
      indx = ia - ngroupsof5;
      i = indx / 736;
      x = indx - i * 736;
      if ((x > 0) && (x >= 368)) {
        i++;
      }

      b_pixelSub[1] = i + 1;
      b_pixelSub[0] = ngroupsof5;
      for (i = 0; i < 2; i++) {
        pixelSub[i] = b_pixelSub[i];
      }

      indx = 0;
      i = 0;
      for (midm1 = 0; midm1 <= 26; midm1 += 25) {
        for (k = 0; k < 25; k++) {
          imnhSubs[midm1 + k] = iv0[indx + k] + pixelSub[i];
        }

        indx += 25;
        i++;
      }

      for (i = 0; i < 25; i++) {
        isInside[i] = true;
      }

      for (midm1 = 0; midm1 < 25; midm1++) {
        imnhInds_data[midm1] = imnhInds_[midm1];
        indx = 0;
        exitg6 = false;
        while ((!exitg6) && (indx < 2)) {
          if ((imnhSubs[midm1 + 25 * indx] < 1) || (imnhSubs[midm1 + 25 * indx] >
               736 + 364 * indx)) {
            isInside[midm1] = false;
            imnhInds_data[midm1] = 1;
            exitg6 = true;
          } else {
            indx++;
          }
        }
      }

      for (i = 0; i < 25; i++) {
        imnh_data[i] = varargin_1[imnhInds_data[i] - 1];
      }

      for (i = 0; i < 25; i++) {
        if (!isInside[i]) {
          imnh_data[i] = 0.0;
        }
      }

      k = 0;
      do {
        exitg5 = 0;
        if (k + 1 <= 25) {
          if (rtIsNaN(imnh_data[k])) {
            vref = imnh_data[k];
            exitg5 = 1;
          } else {
            k++;
          }
        } else {
          imnh_size[0] = 25;
          quickselect(imnh_data, imnh_size, 13, 25, &vref, &indx, &i);
          exitg5 = 1;
        }
      } while (exitg5 == 0);

      b[ia - 1] = vref;
    }
  }

  for (secondInd = 1; secondInd < 1101; secondInd++) {
    for (firstInd = 0; firstInd < 2; firstInd++) {
      ia = (secondInd - 1) * 736 + firstInd;
      for (i = 0; i < 25; i++) {
        imnhInds_[i] = (a[i] + ia) + 1;
      }

      ngroupsof5 = ia - 736 * (ia / 736);
      indx = ia - ngroupsof5;
      if (indx >= 0) {
        i = indx;
      } else {
        i = -indx;
      }

      midm1 = i / 736;
      x = i - midm1 * 736;
      if ((x > 0) && (x >= 368)) {
        midm1++;
      }

      if (indx < 0) {
        midm1 = -midm1;
      }

      d_pixelSub[1] = midm1 + 1;
      d_pixelSub[0] = ngroupsof5 + 1;
      for (i = 0; i < 2; i++) {
        pixelSub[i] = d_pixelSub[i];
      }

      indx = 0;
      i = 0;
      for (midm1 = 0; midm1 <= 26; midm1 += 25) {
        for (k = 0; k < 25; k++) {
          imnhSubs[midm1 + k] = iv0[indx + k] + pixelSub[i];
        }

        indx += 25;
        i++;
      }

      for (i = 0; i < 25; i++) {
        isInside[i] = true;
      }

      for (midm1 = 0; midm1 < 25; midm1++) {
        c_imnhInds_data[midm1] = imnhInds_[midm1];
        indx = 0;
        exitg4 = false;
        while ((!exitg4) && (indx < 2)) {
          if ((imnhSubs[midm1 + 25 * indx] < 1) || (imnhSubs[midm1 + 25 * indx] >
               736 + 364 * indx)) {
            isInside[midm1] = false;
            c_imnhInds_data[midm1] = 1;
            exitg4 = true;
          } else {
            indx++;
          }
        }
      }

      for (i = 0; i < 25; i++) {
        imnh_data[i] = varargin_1[c_imnhInds_data[i] - 1];
      }

      for (i = 0; i < 25; i++) {
        if (!isInside[i]) {
          imnh_data[i] = 0.0;
        }
      }

      k = 0;
      do {
        exitg3 = 0;
        if (k + 1 <= 25) {
          if (rtIsNaN(imnh_data[k])) {
            vref = imnh_data[k];
            exitg3 = 1;
          } else {
            k++;
          }
        } else {
          imnh_size[0] = 25;
          quickselect(imnh_data, imnh_size, 13, 25, &vref, &indx, &i);
          exitg3 = 1;
        }
      } while (exitg3 == 0);

      b[ia] = vref;
    }
  }

  for (secondInd = 1; secondInd < 1101; secondInd++) {
    for (firstInd = iv1[0] + 1; firstInd < 737; firstInd++) {
      ia = (secondInd - 1) * 736 + firstInd;
      for (i = 0; i < 25; i++) {
        imnhInds_[i] = a[i] + ia;
      }

      ngroupsof5 = ia - 736 * ((ia - 1) / 736);
      indx = ia - ngroupsof5;
      if (indx >= 0) {
        i = indx;
      } else {
        i = -indx;
      }

      midm1 = i / 736;
      x = i - midm1 * 736;
      if ((x > 0) && (x >= 368)) {
        midm1++;
      }

      if (indx < 0) {
        midm1 = -midm1;
      }

      e_pixelSub[1] = midm1 + 1;
      e_pixelSub[0] = ngroupsof5;
      for (i = 0; i < 2; i++) {
        pixelSub[i] = e_pixelSub[i];
      }

      indx = 0;
      i = 0;
      for (midm1 = 0; midm1 <= 26; midm1 += 25) {
        for (k = 0; k < 25; k++) {
          imnhSubs[midm1 + k] = iv0[indx + k] + pixelSub[i];
        }

        indx += 25;
        i++;
      }

      for (i = 0; i < 25; i++) {
        isInside[i] = true;
      }

      for (midm1 = 0; midm1 < 25; midm1++) {
        d_imnhInds_data[midm1] = imnhInds_[midm1];
        indx = 0;
        exitg2 = false;
        while ((!exitg2) && (indx < 2)) {
          if ((imnhSubs[midm1 + 25 * indx] < 1) || (imnhSubs[midm1 + 25 * indx] >
               736 + 364 * indx)) {
            isInside[midm1] = false;
            d_imnhInds_data[midm1] = 1;
            exitg2 = true;
          } else {
            indx++;
          }
        }
      }

      for (i = 0; i < 25; i++) {
        imnh_data[i] = varargin_1[d_imnhInds_data[i] - 1];
      }

      for (i = 0; i < 25; i++) {
        if (!isInside[i]) {
          imnh_data[i] = 0.0;
        }
      }

      k = 0;
      do {
        exitg1 = 0;
        if (k + 1 <= 25) {
          if (rtIsNaN(imnh_data[k])) {
            vref = imnh_data[k];
            exitg1 = 1;
          } else {
            k++;
          }
        } else {
          imnh_size[0] = 25;
          quickselect(imnh_data, imnh_size, 13, 25, &vref, &indx, &i);
          exitg1 = 1;
        }
      } while (exitg1 == 0);

      b[ia - 1] = vref;
    }
  }
}

//
// File trailer for medfilt2.cpp
//
// [EOF]
//
