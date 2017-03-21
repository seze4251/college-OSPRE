//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Position_From_Angles_Slew.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 21-Mar-2017 13:20:47
//

// Include Files
#include "Kalman_Filter_Iteration.h"
#include "Position_From_Angles_Slew.h"
#include "Position_From_Earth_Range.h"
#include "Position_From_Moon_Range.h"
#include "Quaternion_To_Attitude.h"
#include "State_Error.h"
#include "norm.h"
#include "sind.h"
#include "cosd.h"

// Function Definitions

//
// %% Calculates the spacecraft ECI position vector utilizing the angles
// %% method. This method takes the slew rate of the spacecraft between
// %% pictures into account and outputs the positions at the times of both
// %% images.
//
//    Author:   Cameron Maywood
//    Created:  10/31/2016
//    Modified: 11/06/2016
//              _________________________________________________________
//    Inputs:  |    r_E_M    |   Moon ECI position vector                |
//             |    q_E      |   Spacecraft-Earth quaternion             |
//             |    q_M      |   Spacecraft-Moon quaternion              |
//             |    alpha    |   Horizontal quaternion error angle       |
//             |    beta     |   Vertical quaternion error angle         |
//             |    vel      |   Spacecraft ECI velocity vector          |
//             |    time     |   Time between Earth and Moon images      |
//             |_____________|___________________________________________|
//    Outputs: |   r_E_SC1   |   First spacecraft ECI position vector    |
//             |   r_E_SC2   |   Second spacecraft ECI position vector   |
//             |_____________|___________________________________________|
// Arguments    : const double r_E_M[3]
//                const double q_E[4]
//                const double q_M[4]
//                double alpha_M
//                double beta_M
//                double alpha_E
//                double beta_E
//                const double vel[3]
//                double time
//                double r_E_SC1[3]
//                double r_E_SC2[3]
// Return Type  : void
//
void Position_From_Angles_Slew(const double r_E_M[3], const double q_E[4], const
  double q_M[4], double alpha_M, double beta_M, double alpha_E, double beta_E,
  const double vel[3], double time, double r_E_SC1[3], double r_E_SC2[3])
{
  double d0;
  double d1;
  double c;
  double d_E_M;
  double theta_int;
  double y;
  double d2;
  double d3;
  double d4;
  double d5;
  double d6;
  double d7;
  double b[3];
  double dv0[9];
  int i0;
  int k;
  double dv1[9];
  double a[3];
  double r_SC_M[3];

  //
  //  Earth Quaternion error rotation matrix
  //  Spacecraft-Earth attitude unit vector
  d0 = alpha_E;
  cosd(&d0);
  d1 = beta_E;
  cosd(&d1);
  c = alpha_E;
  sind(&c);
  d_E_M = alpha_E;
  cosd(&d_E_M);
  theta_int = beta_E;
  sind(&theta_int);
  y = alpha_E;
  sind(&y);
  d2 = beta_E;
  cosd(&d2);
  d3 = alpha_E;
  cosd(&d3);
  d4 = alpha_E;
  sind(&d4);
  d5 = beta_E;
  sind(&d5);
  d6 = beta_E;
  sind(&d6);
  d7 = beta_E;
  cosd(&d7);
  Quaternion_To_Attitude(q_E, b);
  dv0[0] = d0 * d1;
  dv0[3] = -c;
  dv0[6] = d_E_M * theta_int;
  dv0[1] = y * d2;
  dv0[4] = d3;
  dv0[7] = d4 * d5;
  dv0[2] = -d6;
  dv0[5] = 0.0;
  dv0[8] = d7;
  for (i0 = 0; i0 < 3; i0++) {
    r_E_SC1[i0] = 0.0;
    for (k = 0; k < 3; k++) {
      r_E_SC1[i0] += dv0[i0 + 3 * k] * b[k];
    }
  }

  //  Moon Quaternion error rotation matrix
  //  Spacecraft-Moon attitude unit vector
  d0 = alpha_M;
  cosd(&d0);
  d1 = beta_M;
  cosd(&d1);
  c = alpha_M;
  sind(&c);
  d_E_M = alpha_M;
  cosd(&d_E_M);
  theta_int = beta_M;
  sind(&theta_int);
  y = alpha_M;
  sind(&y);
  d2 = beta_M;
  cosd(&d2);
  d3 = alpha_M;
  cosd(&d3);
  d4 = alpha_M;
  sind(&d4);
  d5 = beta_M;
  sind(&d5);
  d6 = beta_M;
  sind(&d6);
  d7 = beta_M;
  cosd(&d7);
  Quaternion_To_Attitude(q_M, b);
  dv1[0] = d0 * d1;
  dv1[3] = -c;
  dv1[6] = d_E_M * theta_int;
  dv1[1] = y * d2;
  dv1[4] = d3;
  dv1[7] = d4 * d5;
  dv1[2] = -d6;
  dv1[5] = 0.0;
  dv1[8] = d7;

  //  Angle between inteception of both spacecraft unit vectors
  c = 0.0;
  for (k = 0; k < 3; k++) {
    r_SC_M[k] = 0.0;
    for (i0 = 0; i0 < 3; i0++) {
      r_SC_M[k] += dv1[k + 3 * i0] * b[i0];
    }

    c += r_E_SC1[k] * r_SC_M[k];
    a[k] = -r_E_M[k];
  }

  theta_int = 57.295779513082323 * std::acos(c);

  //  Earth-Moon distance
  d_E_M = norm(r_E_M);

  //  Angle between Earth and spacecraft
  c = 0.0;
  for (k = 0; k < 3; k++) {
    c += a[k] * -r_SC_M[k];
  }

  //  ECI position vector to inteception point
  d0 = 57.295779513082323 * std::acos(c / d_E_M);
  sind(&d0);
  d1 = theta_int;
  sind(&d1);
  y = d_E_M * d0 / d1;

  //  Posiriont vector from spacecraft at first picture to spacecraft at second
  //  picture
  //  Angle between spacecraft transient position vector and Moon-Spacecraft
  //  unit vector
  c = 0.0;
  for (k = 0; k < 3; k++) {
    d_E_M = time * vel[k];
    c += -d_E_M * -r_SC_M[k];
    b[k] = -d_E_M;
    r_E_SC2[k] = d_E_M;
  }

  //  Position vector from spacecraft at first position to interception point
  d0 = 57.295779513082323 * std::acos(c / norm(b));
  sind(&d0);
  sind(&theta_int);
  d_E_M = norm(r_E_SC2) * d0 / theta_int;

  //  ECI position vectors to both spacecraft positions
  for (i0 = 0; i0 < 3; i0++) {
    c = y * -r_E_SC1[i0] - d_E_M * -r_E_SC1[i0];
    r_E_SC1[i0] = c;
    r_E_SC2[i0] += c;
  }
}

//
// File trailer for Position_From_Angles_Slew.cpp
//
// [EOF]
//