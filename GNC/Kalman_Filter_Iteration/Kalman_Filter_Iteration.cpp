//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Kalman_Filter_Iteration.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 28-Feb-2017 11:46:21
//

// Include Files
#include "Kalman_Filter_Iteration.h"
#include "Position_From_Angles_Slew.h"
#include "Position_From_Earth_Range.h"
#include "Position_From_Moon_Range.h"
#include "Quaternion_To_Attitude.h"

// Function Definitions

//
// Time Update
// Arguments    : const double x_hat_0[6]
//                const double phi[36]
//                const double P_0[36]
//                const double Y[3]
//                const double X_ref[6]
//                const double R[9]
//                double X_est[6]
//                double x_hat[6]
//                double P[36]
//                double y[3]
// Return Type  : void
//
void Kalman_Filter_Iteration(const double x_hat_0[6], const double phi[36],
  const double P_0[36], const double Y[3], const double X_ref[6], const double
  R[9], double X_est[6], double x_hat[6], double P[36], double y[3])
{
  double b_phi[36];
  int p2;
  double x_bar[6];
  double a[18];
  int p3;
  double b_a[9];
  int i;
  double P_bar[36];
  double x[9];
  double absx11;
  double absx21;
  static const signed char c_a[18] = { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0 };

  double absx31;
  static const signed char b[18] = { 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0 };

  int itmp;
  double c[9];
  double b_y[3];
  double K[18];
  signed char I[36];
  signed char b_I[36];
  double c_I[36];
  double b_K[36];

  //  Kalman_Filter_Iteration Function
  //   Calculates the state vector of the next measurement given the Kalman
  //   filter initial conditions of the previous measurement.
  //
  //   Author:   Cameron Maywood
  //   Created:  11/04/2016
  //   Modified: 12/10/2016
  //             __________________________________________________________
  //   Inputs:  |   x_hat_0   |   Initial reference trajectory deviance    |
  //            |     phi     |   Next state transition matrix             |
  //            |     P_0     |   Initial covariance matrix                |
  //            |      Y      |   Next state observation                   |
  //            |    X_ref    |   Next spacecraft 3-body reference state   |
  //            |      R      |   Next state error covariance              |
  //            |_____________|____________________________________________|
  //   Outputs: |    X_est    |   New estimated spacecraft state vector    |
  //            |    x_hat    |   New reference trajectory deviation       |
  //            |      P      |   New covariance matrix                    |
  //            |      y      |   Residuals matrix                         |
  //            |_____________|____________________________________________|
  //
  for (p2 = 0; p2 < 6; p2++) {
    x_bar[p2] = 0.0;
    for (p3 = 0; p3 < 6; p3++) {
      b_phi[p2 + 6 * p3] = 0.0;
      for (i = 0; i < 6; i++) {
        b_phi[p2 + 6 * p3] += phi[p2 + 6 * i] * P_0[i + 6 * p3];
      }

      x_bar[p2] += phi[p2 + 6 * p3] * x_hat_0[p3];
    }

    for (p3 = 0; p3 < 6; p3++) {
      P_bar[p2 + 6 * p3] = 0.0;
      for (i = 0; i < 6; i++) {
        P_bar[p2 + 6 * p3] += b_phi[p2 + 6 * i] * phi[p3 + 6 * i];
      }
    }
  }

  //  Observation Deviation, Observation State Matrix, Gain Matrix
  for (i = 0; i < 3; i++) {
    y[i] = Y[i] - X_ref[i];
    for (p2 = 0; p2 < 6; p2++) {
      a[i + 3 * p2] = 0.0;
      for (p3 = 0; p3 < 6; p3++) {
        a[i + 3 * p2] += (double)c_a[i + 3 * p3] * P_bar[p3 + 6 * p2];
      }
    }

    for (p2 = 0; p2 < 3; p2++) {
      absx11 = 0.0;
      for (p3 = 0; p3 < 6; p3++) {
        absx11 += a[i + 3 * p3] * (double)b[p3 + 6 * p2];
      }

      b_a[i + 3 * p2] = absx11 + R[i + 3 * p2];
    }
  }

  memcpy(&x[0], &b_a[0], 9U * sizeof(double));
  i = 0;
  p2 = 3;
  p3 = 6;
  absx11 = std::abs(b_a[0]);
  absx21 = std::abs(b_a[1]);
  absx31 = std::abs(b_a[2]);
  if ((absx21 > absx11) && (absx21 > absx31)) {
    i = 3;
    p2 = 0;
    x[0] = b_a[1];
    x[1] = b_a[0];
    x[3] = b_a[4];
    x[4] = b_a[3];
    x[6] = b_a[7];
    x[7] = b_a[6];
  } else {
    if (absx31 > absx11) {
      i = 6;
      p3 = 0;
      x[0] = b_a[2];
      x[2] = b_a[0];
      x[3] = b_a[5];
      x[5] = b_a[3];
      x[6] = b_a[8];
      x[8] = b_a[6];
    }
  }

  absx11 = x[1] / x[0];
  x[1] /= x[0];
  absx21 = x[2] / x[0];
  x[2] /= x[0];
  x[4] -= absx11 * x[3];
  x[5] -= absx21 * x[3];
  x[7] -= absx11 * x[6];
  x[8] -= absx21 * x[6];
  if (std::abs(x[5]) > std::abs(x[4])) {
    itmp = p2;
    p2 = p3;
    p3 = itmp;
    x[1] = absx21;
    x[2] = absx11;
    absx11 = x[4];
    x[4] = x[5];
    x[5] = absx11;
    absx11 = x[7];
    x[7] = x[8];
    x[8] = absx11;
  }

  absx11 = x[5] / x[4];
  x[5] /= x[4];
  x[8] -= absx11 * x[7];
  absx11 = (x[5] * x[1] - x[2]) / x[8];
  absx21 = -(x[1] + x[7] * absx11) / x[4];
  c[i] = ((1.0 - x[3] * absx21) - x[6] * absx11) / x[0];
  c[i + 1] = absx21;
  c[i + 2] = absx11;
  absx11 = -x[5] / x[8];
  absx21 = (1.0 - x[7] * absx11) / x[4];
  c[p2] = -(x[3] * absx21 + x[6] * absx11) / x[0];
  c[p2 + 1] = absx21;
  c[p2 + 2] = absx11;
  absx11 = 1.0 / x[8];
  absx21 = -x[7] * absx11 / x[4];
  c[p3] = -(x[3] * absx21 + x[6] * absx11) / x[0];
  c[p3 + 1] = absx21;
  c[p3 + 2] = absx11;
  for (p2 = 0; p2 < 6; p2++) {
    for (p3 = 0; p3 < 3; p3++) {
      a[p2 + 6 * p3] = 0.0;
      for (i = 0; i < 6; i++) {
        a[p2 + 6 * p3] += P_bar[p2 + 6 * i] * (double)b[i + 6 * p3];
      }
    }

    for (p3 = 0; p3 < 3; p3++) {
      K[p2 + 6 * p3] = 0.0;
      for (i = 0; i < 3; i++) {
        K[p2 + 6 * p3] += a[p2 + 6 * i] * c[i + 3 * p3];
      }
    }
  }

  //  Measurement Update
  for (p2 = 0; p2 < 3; p2++) {
    absx11 = 0.0;
    for (p3 = 0; p3 < 6; p3++) {
      absx11 += (double)c_a[p2 + 3 * p3] * x_bar[p3];
    }

    b_y[p2] = y[p2] - absx11;
  }

  for (p2 = 0; p2 < 6; p2++) {
    absx11 = 0.0;
    for (p3 = 0; p3 < 3; p3++) {
      absx11 += K[p2 + 6 * p3] * b_y[p3];
    }

    x_hat[p2] = x_bar[p2] + absx11;
  }

  for (p2 = 0; p2 < 36; p2++) {
    I[p2] = 0;
  }

  for (i = 0; i < 6; i++) {
    I[i + 6 * i] = 1;
  }

  for (p2 = 0; p2 < 36; p2++) {
    b_I[p2] = 0;
  }

  for (i = 0; i < 6; i++) {
    b_I[i + 6 * i] = 1;
    for (p2 = 0; p2 < 6; p2++) {
      absx11 = 0.0;
      for (p3 = 0; p3 < 3; p3++) {
        absx11 += K[i + 6 * p3] * (double)c_a[p3 + 3 * p2];
      }

      b_phi[i + 6 * p2] = (double)I[i + 6 * p2] - absx11;
    }

    for (p2 = 0; p2 < 6; p2++) {
      c_I[i + 6 * p2] = 0.0;
      for (p3 = 0; p3 < 6; p3++) {
        c_I[i + 6 * p2] += b_phi[i + 6 * p3] * P_bar[p3 + 6 * p2];
      }
    }
  }

  for (p2 = 0; p2 < 6; p2++) {
    for (p3 = 0; p3 < 6; p3++) {
      absx11 = 0.0;
      for (i = 0; i < 3; i++) {
        absx11 += K[p3 + 6 * i] * (double)c_a[i + 3 * p2];
      }

      b_phi[p2 + 6 * p3] = (double)b_I[p3 + 6 * p2] - absx11;
    }

    for (p3 = 0; p3 < 3; p3++) {
      a[p2 + 6 * p3] = 0.0;
      for (i = 0; i < 3; i++) {
        a[p2 + 6 * p3] += K[p2 + 6 * i] * R[i + 3 * p3];
      }
    }
  }

  for (p2 = 0; p2 < 6; p2++) {
    for (p3 = 0; p3 < 6; p3++) {
      P_bar[p2 + 6 * p3] = 0.0;
      for (i = 0; i < 6; i++) {
        P_bar[p2 + 6 * p3] += c_I[p2 + 6 * i] * b_phi[i + 6 * p3];
      }

      b_K[p2 + 6 * p3] = 0.0;
      for (i = 0; i < 3; i++) {
        b_K[p2 + 6 * p3] += a[p2 + 6 * i] * K[p3 + 6 * i];
      }
    }
  }

  //  Updated Estimate
  for (i = 0; i < 6; i++) {
    for (p2 = 0; p2 < 6; p2++) {
      P[p2 + 6 * i] = P_bar[p2 + 6 * i] + b_K[p2 + 6 * i];
    }

    X_est[i] = X_ref[i] + x_hat[i];
  }
}

//
// File trailer for Kalman_Filter_Iteration.cpp
//
// [EOF]
//
