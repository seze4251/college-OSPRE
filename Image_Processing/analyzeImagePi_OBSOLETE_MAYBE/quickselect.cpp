//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: quickselect.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "quickselect.h"
#include "sort3.h"

// Function Declarations
static void med3(double v_data[], int nv, int ia, int ib);
static void medmed(double v_data[], int nv, int ia);
static int pivot(double v_data[], int *ip, int ia, int ib);
static int thirdOfFive(const double v_data[], int ia, int ib);

// Function Definitions

//
// Arguments    : double v_data[]
//                int nv
//                int ia
//                int ib
// Return Type  : void
//
static void med3(double v_data[], int nv, int ia, int ib)
{
  int ic;
  int unusedU0;
  int jc;
  int unusedU1;
  double tmp;
  if (nv >= 3) {
    ic = ia + (nv - 1) / 2;
    sort3(ia, v_data[ia - 1], ic, v_data[ic - 1], ib, v_data[ib - 1], &unusedU0,
          &jc, &unusedU1);
    if (jc > ia) {
      tmp = v_data[ia - 1];
      v_data[ia - 1] = v_data[jc - 1];
      v_data[jc - 1] = tmp;
    }
  }
}

//
// Arguments    : double v_data[]
//                int nv
//                int ia
// Return Type  : void
//
static void medmed(double v_data[], int nv, int ia)
{
  int ngroupsof5;
  int nlast;
  int k;
  int i1;
  int destidx;
  double tmp;
  while (nv > 1) {
    ngroupsof5 = nv / 5;
    nlast = nv - ngroupsof5 * 5;
    nv = ngroupsof5;
    for (k = 0; k + 1 <= ngroupsof5; k++) {
      i1 = ia + k * 5;
      i1 = thirdOfFive(v_data, i1, i1 + 4) - 1;
      destidx = (ia + k) - 1;
      tmp = v_data[destidx];
      v_data[destidx] = v_data[i1];
      v_data[i1] = tmp;
    }

    if (nlast > 0) {
      i1 = ia + ngroupsof5 * 5;
      i1 = thirdOfFive(v_data, i1, (i1 + nlast) - 1) - 1;
      destidx = (ia + ngroupsof5) - 1;
      tmp = v_data[destidx];
      v_data[destidx] = v_data[i1];
      v_data[i1] = tmp;
      nv = ngroupsof5 + 1;
    }
  }
}

//
// Arguments    : double v_data[]
//                int *ip
//                int ia
//                int ib
// Return Type  : int
//
static int pivot(double v_data[], int *ip, int ia, int ib)
{
  int reps;
  double vref;
  int k;
  double vk;
  vref = v_data[*ip - 1];
  v_data[*ip - 1] = v_data[ib - 1];
  v_data[ib - 1] = vref;
  *ip = ia;
  reps = 0;
  for (k = ia - 1; k + 1 < ib; k++) {
    vk = v_data[k];
    if (v_data[k] == vref) {
      v_data[k] = v_data[*ip - 1];
      v_data[*ip - 1] = vk;
      reps++;
      (*ip)++;
    } else {
      if (v_data[k] < vref) {
        v_data[k] = v_data[*ip - 1];
        v_data[*ip - 1] = vk;
        (*ip)++;
      }
    }
  }

  v_data[ib - 1] = v_data[*ip - 1];
  v_data[*ip - 1] = vref;
  return reps;
}

//
// Arguments    : const double v_data[]
//                int ia
//                int ib
// Return Type  : int
//
static int thirdOfFive(const double v_data[], int ia, int ib)
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
//                int n
//                int vlen
//                double *vn
//                int *nfirst
//                int *nlast
// Return Type  : void
//
void quickselect(double v_data[], int n, int vlen, double *vn, int *nfirst, int *
                 nlast)
{
  int ipiv;
  int ia;
  int ib;
  int oldnv;
  boolean_T checkspeed;
  boolean_T isslow;
  boolean_T exitg1;
  int reps;
  boolean_T guard1 = false;
  if (n > vlen) {
    *vn = rtNaN;
    *nfirst = 0;
    *nlast = 0;
  } else {
    ipiv = n;
    ia = 1;
    ib = vlen;
    *nfirst = 1;
    *nlast = vlen;
    oldnv = vlen;
    checkspeed = false;
    isslow = false;
    exitg1 = false;
    while ((!exitg1) && (ia < ib)) {
      reps = pivot(v_data, &ipiv, ia, ib);
      *nlast = ipiv;
      guard1 = false;
      if (n <= ipiv) {
        *nfirst = ipiv - reps;
        if (n >= *nfirst) {
          exitg1 = true;
        } else {
          ib = ipiv - 1;
          guard1 = true;
        }
      } else {
        ia = ipiv + 1;
        guard1 = true;
      }

      if (guard1) {
        reps = (ib - ia) + 1;
        if (checkspeed) {
          isslow = (reps > oldnv / 2);
          oldnv = reps;
        }

        checkspeed = !checkspeed;
        if (isslow) {
          medmed(v_data, reps, ia);
        } else {
          med3(v_data, reps, ia, ib);
        }

        ipiv = ia;
        *nfirst = ia;
        *nlast = ib;
      }
    }

    *vn = v_data[*nlast - 1];
  }
}

//
// File trailer for quickselect.cpp
//
// [EOF]
//
