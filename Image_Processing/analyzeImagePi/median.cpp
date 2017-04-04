//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: median.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "median.h"
#include "sort3.h"
#include "quickselect.h"

// Function Declarations
static double med01234(const double v_data[], int vlen);

// Function Definitions

//
// Arguments    : const double v_data[]
//                int vlen
// Return Type  : double
//
static double med01234(const double v_data[], int vlen)
{
  double m;
  int b_j1;
  int j2;
  int j3;
  if (vlen == 1) {
    m = v_data[0];
  } else if (vlen == 2) {
    if (((v_data[0] < 0.0) && (v_data[1] >= 0.0)) || rtIsInf(v_data[0]) ||
        rtIsInf(v_data[1])) {
      m = (v_data[0] + v_data[1]) / 2.0;
    } else {
      m = v_data[0] + (v_data[1] - v_data[0]) / 2.0;
    }
  } else if (vlen == 3) {
    if (v_data[0] < v_data[1]) {
      if (v_data[1] < v_data[2]) {
        j2 = 1;
      } else if (v_data[0] < v_data[2]) {
        j2 = 2;
      } else {
        j2 = 0;
      }
    } else if (v_data[0] < v_data[2]) {
      j2 = 0;
    } else if (v_data[1] < v_data[2]) {
      j2 = 2;
    } else {
      j2 = 1;
    }

    m = v_data[j2];
  } else {
    sort3(1, v_data[0], 2, v_data[1], 3, v_data[2], &b_j1, &j2, &j3);
    if (v_data[b_j1 - 1] < v_data[3]) {
      if (v_data[3] < v_data[j3 - 1]) {
        if (((v_data[j2 - 1] < 0.0) && (v_data[3] >= 0.0)) || rtIsInf(v_data[j2
             - 1]) || rtIsInf(v_data[3])) {
          m = (v_data[j2 - 1] + v_data[3]) / 2.0;
        } else {
          m = v_data[j2 - 1] + (v_data[3] - v_data[j2 - 1]) / 2.0;
        }
      } else if (((v_data[j2 - 1] < 0.0) && (v_data[j3 - 1] >= 0.0)) || rtIsInf
                 (v_data[j2 - 1]) || rtIsInf(v_data[j3 - 1])) {
        m = (v_data[j2 - 1] + v_data[j3 - 1]) / 2.0;
      } else {
        m = v_data[j2 - 1] + (v_data[j3 - 1] - v_data[j2 - 1]) / 2.0;
      }
    } else if (((v_data[b_j1 - 1] < 0.0) && (v_data[j2 - 1] >= 0.0)) || rtIsInf
               (v_data[b_j1 - 1]) || rtIsInf(v_data[j2 - 1])) {
      m = (v_data[b_j1 - 1] + v_data[j2 - 1]) / 2.0;
    } else {
      m = v_data[b_j1 - 1] + (v_data[j2 - 1] - v_data[b_j1 - 1]) / 2.0;
    }
  }

  return m;
}

//
// Arguments    : const double x_data[]
//                const int x_size[1]
// Return Type  : double
//
double median(const double x_data[], const int x_size[1])
{
  double y;
  int n;
  int k;
  int exitg1;
  int midm1;
  int unusedU3;
  double v_data[625];
  int ilast;
  double a;
  if (x_size[0] == 0) {
    y = rtNaN;
  } else {
    n = x_size[0];
    k = 0;
    do {
      exitg1 = 0;
      if (k + 1 <= n) {
        if (rtIsNaN(x_data[k])) {
          y = x_data[k];
          exitg1 = 1;
        } else {
          k++;
        }
      } else {
        if (n <= 4) {
          y = med01234(x_data, n);
        } else {
          midm1 = n >> 1;
          if ((n & 1) == 0) {
            k = x_size[0];
            for (unusedU3 = 0; unusedU3 < k; unusedU3++) {
              v_data[unusedU3] = x_data[unusedU3];
            }

            quickselect(v_data, midm1 + 1, n, &y, &k, &ilast);
            if (midm1 < k) {
              quickselect(v_data, midm1, ilast - 1, &a, &k, &unusedU3);
              if (((a < 0.0) && (y >= 0.0)) || rtIsInf(a) || rtIsInf(y)) {
                y = (a + y) / 2.0;
              } else {
                y = a + (y - a) / 2.0;
              }
            }
          } else {
            k = x_size[0];
            for (unusedU3 = 0; unusedU3 < k; unusedU3++) {
              v_data[unusedU3] = x_data[unusedU3];
            }

            quickselect(v_data, midm1 + 1, n, &y, &k, &unusedU3);
          }
        }

        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return y;
}

//
// File trailer for median.cpp
//
// [EOF]
//
