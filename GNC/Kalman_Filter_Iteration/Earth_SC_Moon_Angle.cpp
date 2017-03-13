#include "norm.h"

// Function Definitions

//
// Spacecraft-Moon position vector
// Arguments    : const double r_E_SC[3]
//                const double r_E_M[3]
// Return Type  : double
//
double Earth_SC_Moon_Angle(const double r_E_SC[3], const double r_E_M[3])
{
  double c;
  double r_SC_M[3];
  double r_SC_E[3];
  int k;
  double b_r_SC_M;

  //  Earth-Spacecraft-Moon Angle Function
  //   Calculates the Earth-Spacecraft-Moon angle from the spacecraft and moon
  //   positions.
  //
  //   Author:   Cameron Maywood
  //   Created:  3/8/2017
  //   Modified: 3/8/2017
  //             _____________________________________________________________
  //   Inputs:  |          r_E_SC         |  Spacecraft ECI position vector   |
  //            |          r_E_M          |  Moon ECI position vector         |
  //            |_________________________|___________________________________|
  //   Outputs: |   angle_Earth_SC_Moon   |   Earth-spacecraft-moon angle     |
  //            |_________________________|___________________________________|
  //  Spacecraft-Earth position vector
  //  Earth-spacecraft-Moon angle
  c = 0.0;
  for (k = 0; k < 3; k++) {
    b_r_SC_M = r_E_M[k] - r_E_SC[k];
    c += b_r_SC_M * -r_E_SC[k];
    r_SC_M[k] = b_r_SC_M;
    r_SC_E[k] = -r_E_SC[k];
  }

  return 57.295779513082323 * std::acos(c / (norm(r_SC_M) * norm(r_SC_E)));
}

//
// File trailer for Earth_SC_Moon_Angle.cpp
//
// [EOF]
//
