//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: State_Error.cpp
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
#include <stdio.h>
#include "../../include/Exception/OSPRE_Exceptions.h"

// Function Definitions

//
// Arguments    : const double X_ref[6]
//                const double X_est[6]
//                double posError[3]
//                double velError[3]
// Return Type  : void
//
void State_Error(const double X_ref[6], const double X_est[6], double posError[3],
                 double velError[3])
{

  // INPUT EXCEPTIONS
  if (sqrt(pow(X_ref[0], 2) + pow(X_ref[1], 2) + pow(X_ref[2], 2)) < 6378.137) {
      char logString[100];
      sprintf(logString, "ERROR: State_Error(). Reference state cannot be within the radius of Earth.\n");
      throw InvalidInputs(logString);
  }
  if (sqrt(pow(X_est[0], 2) + pow(X_est[1], 2) + pow(X_est[2], 2)) < 6378.137) {
      char logString[100];
      sprintf(logString, "ERROR: State_Error(). Estimated state cannot be within the radius of Earth.\n");
      throw InvalidInputs(logString);
  }

  int i;

  //  State Error Function
  //   Calculates the state error given the reference state and estimated
  //   state.
  //
  //   Author:   Cameron Maywood
  //   Created:  3/9/2017
  //   Modified: 3/9/2017
  //             _________________________________________________
  //   Inputs:  |     X_ref     |   Spacecraft reference state.   |
  //            |     X_est     |   Spacecraft estimated state.   |
  //            |_______________|_________________________________|
  //   Outputs: |    posError   |   Spacecraft position error.    |
  //            |    velError   |   Spacecraft velocity error.    |
  //            |_______________|_________________________________|
  for (i = 0; i < 3; i++) {
    posError[i] = X_ref[i] - X_est[i];
    velError[i] = X_ref[i + 3] - X_est[i + 3];
  }
}

//
// File trailer for State_Error.cpp
//
// [EOF]
//
