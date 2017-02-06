//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: quickselect.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 25-Jan-2017 16:02:21
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "quickselect.h"
#include "sort3.h"

// Function Declarations
static int b_thirdOfFive(const double v_data[], int ia, int ib);

// Function Definitions

//
// Arguments    : const double v_data[]
//                int ia
//                int ib
// Return Type  : int
//
static int b_thirdOfFive(const double v_data[], int ia, int ib)
{
  int im;
  int b_j1;
  int j3;
  int j4;
  int j5;
  double v4;
  double v5;
  if ((ia == ib) || (ia + 1 == ib)) {
    im = ia;
  } else if ((ia + 2 == ib) || (ia + 3 == ib)) {
    sort3(ia, v_data[ia - 1], ia + 1, v_data[ia], ia + 2, v_data[ia + 1], &b_j1,
          &im, &j3);
  } else {
    sort3(ia, v_data[ia - 1], ia + 1, v_data[ia], ia + 2, v_data[ia + 1], &b_j1,
          &im, &j3);
    j4 = ia;
    j5 = ia + 1;
    v4 = v_data[ia + 2];
    v5 = v_data[ia + 3];
    if (v_data[ia + 3] < v_data[ia + 2]) {
      j4 = ia + 1;
      j5 = ia;
      v5 = v_data[ia + 2];
      v4 = v_data[ia + 3];
    }

    if (v5 < v_data[b_j1 - 1]) {
      im = b_j1;
    } else if (v5 < v_data[im - 1]) {
      im = j5 + 3;
    } else {
      if (!(v4 < v_data[im - 1])) {
        if (v4 < v_data[j3 - 1]) {
          im = j4 + 3;
        } else {
          im = j3;
        }
      }
    }
  }

  return im;
}

//
// Arguments    : double v_data[]
//                int v_size[1]
//                int n
//                int vlen
//                double *vn
//                int *nfirst
//                int *nlast
// Return Type  : void
//
void quickselect(double v_data[], int v_size[1], int n, int vlen, double *vn,
                 int *nfirst, int *nlast)
{
  int ipiv;
  int ia;
  int ib;
  int oldnv;
  boolean_T checkspeed;
  boolean_T isslow;
  boolean_T exitg1;
  int ngroupsof5;
  int ic;
  int destidx;
  double vref;
  double b_v_data[25];
  int ilast;
  int k;
  double vk;
  boolean_T guard1 = false;
  if (n > vlen) {
    *vn = rtNaN;
    *nfirst = 0;
    *nlast = 0;
  } else {
    ipiv = n - 1;
    ia = 1;
    ib = vlen - 1;
    *nfirst = 1;
    *nlast = vlen;
    oldnv = vlen;
    checkspeed = false;
    isslow = false;
    exitg1 = false;
    while ((!exitg1) && (ia < ib + 1)) {
      ngroupsof5 = v_size[0];
      ic = v_size[0];
      for (destidx = 0; destidx < ic; destidx++) {
        b_v_data[destidx] = v_data[destidx];
      }

      vref = v_data[ipiv];
      b_v_data[ipiv] = v_data[ib];
      b_v_data[ib] = v_data[ipiv];
      ilast = ia - 1;
      ic = -1;
      for (k = ia - 1; k + 1 <= ib; k++) {
        vk = b_v_data[k];
        if (b_v_data[k] == vref) {
          b_v_data[k] = b_v_data[ilast];
          b_v_data[ilast] = vk;
          ic++;
          ilast++;
        } else {
          if (b_v_data[k] < vref) {
            b_v_data[k] = b_v_data[ilast];
            b_v_data[ilast] = vk;
            ilast++;
          }
        }
      }

      b_v_data[ib] = b_v_data[ilast];
      b_v_data[ilast] = v_data[ipiv];
      v_size[0] = ngroupsof5;
      for (destidx = 0; destidx < ngroupsof5; destidx++) {
        v_data[destidx] = b_v_data[destidx];
      }

      *nlast = ilast + 1;
      guard1 = false;
      if (n <= ilast + 1) {
        *nfirst = ilast - ic;
        if (n >= *nfirst) {
          exitg1 = true;
        } else {
          ib = ilast - 1;
          guard1 = true;
        }
      } else {
        ia = ilast + 2;
        guard1 = true;
      }

      if (guard1) {
        ilast = (ib - ia) + 2;
        if (checkspeed) {
          isslow = (ilast > oldnv / 2);
          oldnv = ilast;
        }

        checkspeed = !checkspeed;
        if (isslow) {
          while (ilast > 1) {
            ngroupsof5 = ilast / 5;
            *nlast = ilast - ngroupsof5 * 5;
            ilast = ngroupsof5;
            for (k = 0; k + 1 <= ngroupsof5; k++) {
              ic = ia + k * 5;
              ic = b_thirdOfFive(v_data, ic, ic + 4) - 1;
              destidx = (ia + k) - 1;
              vref = v_data[destidx];
              v_data[destidx] = v_data[ic];
              v_data[ic] = vref;
            }

            if (*nlast > 0) {
              ic = ia + ngroupsof5 * 5;
              ic = b_thirdOfFive(v_data, ic, (ic + *nlast) - 1) - 1;
              destidx = (ia + ngroupsof5) - 1;
              vref = v_data[destidx];
              v_data[destidx] = v_data[ic];
              v_data[ic] = vref;
              ilast = ngroupsof5 + 1;
            }
          }
        } else {
          if (ilast >= 3) {
            ic = ia + (ilast - 1) / 2;
            sort3(ia, b_v_data[ia - 1], ic, b_v_data[ic - 1], ib + 1,
                  b_v_data[ib], &destidx, &ngroupsof5, &ilast);
            if (ngroupsof5 > ia) {
              v_data[ia - 1] = b_v_data[ngroupsof5 - 1];
              v_data[ngroupsof5 - 1] = b_v_data[ia - 1];
            }
          }
        }

        ipiv = ia - 1;
        *nfirst = ia;
        *nlast = ib + 1;
      }
    }

    *vn = v_data[*nlast - 1];
  }
}

//
// Arguments    : const double v[25]
//                int ia
//                int ib
// Return Type  : int
//
int thirdOfFive(const double v[25], int ia, int ib)
{
  int im;
  int b_j1;
  int j3;
  int j4;
  int j5;
  double v4;
  double v5;
  if ((ia == ib) || (ia + 1 == ib)) {
    im = ia;
  } else if ((ia + 2 == ib) || (ia + 3 == ib)) {
    sort3(ia, v[ia - 1], ia + 1, v[ia], ia + 2, v[ia + 1], &b_j1, &im, &j3);
  } else {
    sort3(ia, v[ia - 1], ia + 1, v[ia], ia + 2, v[ia + 1], &b_j1, &im, &j3);
    j4 = ia;
    j5 = ia + 1;
    v4 = v[ia + 2];
    v5 = v[ia + 3];
    if (v[ia + 3] < v[ia + 2]) {
      j4 = ia + 1;
      j5 = ia;
      v5 = v[ia + 2];
      v4 = v[ia + 3];
    }

    if (v5 < v[b_j1 - 1]) {
      im = b_j1;
    } else if (v5 < v[im - 1]) {
      im = j5 + 3;
    } else {
      if (!(v4 < v[im - 1])) {
        if (v4 < v[j3 - 1]) {
          im = j4 + 3;
        } else {
          im = j3;
        }
      }
    }
  }

  return im;
}

//
// File trailer for quickselect.cpp
//
// [EOF]
//
