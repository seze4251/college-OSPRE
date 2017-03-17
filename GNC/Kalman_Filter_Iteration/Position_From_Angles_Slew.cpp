//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Position_From_Angles_Slew.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 09-Mar-2017 13:26:09
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
//                double alpha
//                double beta
//                const double vel[3]
//                double time
//                double r_E_SC1[3]
//                double r_E_SC2[3]
// Return Type  : void
//
void Position_From_Angles_Slew(const double r_E_M[3], const double q_E[4],const double q_M[4], double alpha_M, double beta_M, double alpha_E, double beta_E, const double vel[3], double time, double r_E_SC1[3], double r_E_SC2[3])
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
  double ROT_Q[9];
  double b[3];
  int i0;
  int k;
  double a[3];
  double r_SC_M[3];

  //
  //  Quaternion error rotation matrix
  //d0 = alpha;
    
    //*********************
    //TEMP TEMP TEMP CAMERON TEMP
    //**********************
    double alpha;
    double beta;
    //*********************
    //TEMP TEMP TEMP CAMERON TEMP
    //**********************
    
  cosd(&d0);
  d1 = beta;
  cosd(&d1);
  c = alpha;
  sind(&c);
  d_E_M = alpha;
  cosd(&d_E_M);
  theta_int = beta;
  sind(&theta_int);
  y = alpha;
  sind(&y);
  d2 = beta;
  cosd(&d2);
  d3 = alpha;
  cosd(&d3);
  d4 = alpha;
  sind(&d4);
  d5 = beta;
  sind(&d5);
  d6 = beta;
  sind(&d6);
  d7 = beta;
  cosd(&d7);
  ROT_Q[0] = d0 * d1;
  ROT_Q[3] = -c;
  ROT_Q[6] = d_E_M * theta_int;
  ROT_Q[1] = y * d2;
  ROT_Q[4] = d3;
  ROT_Q[7] = d4 * d5;
  ROT_Q[2] = -d6;
  ROT_Q[5] = 0.0;
  ROT_Q[8] = d7;

  //  Spacecraft-Earth attitude unit vector
  Quaternion_To_Attitude(q_E, b);
  for (i0 = 0; i0 < 3; i0++) {
    r_E_SC1[i0] = 0.0;
    for (k = 0; k < 3; k++) {
      r_E_SC1[i0] += ROT_Q[i0 + 3 * k] * b[k];
    }
  }

  //  Spacecraft-Moon attitude unit vector
  Quaternion_To_Attitude(q_M, b);

  //  Angle between inteception of both spacecraft unit vectors
  c = 0.0;
  for (k = 0; k < 3; k++) {
    r_SC_M[k] = 0.0;
    for (i0 = 0; i0 < 3; i0++) {
      r_SC_M[k] += ROT_Q[k + 3 * i0] * b[i0];
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
