//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: convn.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 25-Jan-2017 16:02:21
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "convn.h"

// Function Definitions

//
// Arguments    : const double A[813276]
//                const double B[9]
//                double C[813276]
// Return Type  : void
//
void b_convn(const double A[813276], const double B[9], double C[813276])
{
  int j;
  int lastColA;
  int k;
  int b_j;
  int iC;
  int c;
  int iB;
  int i;
  int firstRowA;
  int b_i;
  int a_length;
  int cidx;
  int r;
  memset(&C[0], 0, 813276U * sizeof(double));
  for (j = 0; j < 3; j++) {
    if (j + 1101 < 1102) {
      lastColA = 1101;
    } else {
      lastColA = 1102 - j;
    }

    for (k = (j < 1); k <= lastColA; k++) {
      if (j + k > 1) {
        b_j = (j + k) - 1;
      } else {
        b_j = 0;
      }

      iC = b_j * 738;
      c = k * 738;
      iB = j * 3;
      for (i = 0; i < 3; i++) {
        firstRowA = (i < 1);
        if (i + 738 <= 738) {
          b_i = 738;
        } else {
          b_i = 739 - i;
        }

        a_length = b_i - firstRowA;
        firstRowA += c;
        cidx = iC;
        for (r = 1; r <= a_length; r++) {
          C[cidx] += B[iB] * A[firstRowA];
          firstRowA++;
          cidx++;
        }

        iB++;
        if (i >= 1) {
          iC++;
        }
      }
    }
  }
}

//
// Arguments    : const double A[820652]
//                const double B[36]
//                double C[820652]
// Return Type  : void
//
void convn(const double A[820652], const double B[36], double C[820652])
{
  int j;
  int lastColA;
  int k;
  int b_j;
  int iC;
  int c;
  int iB;
  int i;
  int firstRowA;
  int b_i;
  int a_length;
  int cidx;
  int r;
  memset(&C[0], 0, 820652U * sizeof(double));
  for (j = 0; j < 6; j++) {
    if (j + 1105 < 1108) {
      lastColA = 1105;
    } else {
      lastColA = 1108 - j;
    }

    if (j < 3) {
      k = 3 - j;
    } else {
      k = 0;
    }

    while (k <= lastColA) {
      if (j + k > 3) {
        b_j = (j + k) - 3;
      } else {
        b_j = 0;
      }

      iC = b_j * 742;
      c = k * 742;
      iB = j * 6;
      for (i = 0; i < 6; i++) {
        if (i < 3) {
          firstRowA = 3 - i;
        } else {
          firstRowA = 0;
        }

        if (i + 742 <= 744) {
          b_i = 742;
        } else {
          b_i = 745 - i;
        }

        a_length = b_i - firstRowA;
        firstRowA += c;
        cidx = iC;
        for (r = 1; r <= a_length; r++) {
          C[cidx] += B[iB] * A[firstRowA];
          firstRowA++;
          cidx++;
        }

        iB++;
        if (i >= 3) {
          iC++;
        }
      }

      k++;
    }
  }
}

//
// File trailer for convn.cpp
//
// [EOF]
//
