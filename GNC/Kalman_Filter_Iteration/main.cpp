//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: main.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 09-Mar-2017 10:09:18
//

//***********************************************************************
// This automatically generated example C main file shows how to call
// entry-point functions that MATLAB Coder generated. You must customize
// this file for your application. Do not modify this file directly.
// Instead, make a copy of this file, modify it, and integrate it into
// your development environment.
//
// This file initializes entry-point function arguments to a default
// size and value before calling the entry-point functions. It does
// not store or use any values returned from the entry-point functions.
// If necessary, it does pre-allocate memory for returned values.
// You can use this file as a starting point for a main function that
// you can deploy in your application.
//
// After you copy the file, and before you deploy it, you must make the
// following changes:
// * For variable-size function arguments, change the example sizes to
// the sizes that your application requires.
// * Change the example values of function arguments to the values that
// your application requires.
// * If the entry-point functions return values, store these values or
// otherwise use them as required by your application.
//
//***********************************************************************
// Include Files
#include "Earth_SC_Moon_Angle.h"
#include "Kalman_Filter_Iteration.h"
#include "Position_From_Angles_Slew.h"
#include "Position_From_Earth_Range.h"
#include "Position_From_Moon_Range.h"
#include "Quaternion_To_Attitude.h"
#include "State_Error.h"
#include "main.h"
#include "Earth_SC_Moon_Angle_terminate.h"
#include "Earth_SC_Moon_Angle_initialize.h"

// Function Declarations
static void argInit_3x1_real_T(double result[3]);
static void argInit_3x3_real_T(double result[9]);
static void argInit_4x1_real_T(double result[4]);
static void argInit_6x1_real_T(double result[6]);
static void argInit_6x6_real_T(double result[36]);
static double argInit_real_T();
static void main_Earth_SC_Moon_Angle();
static void main_Kalman_Filter_Iteration();
static void main_Position_From_Angles_Slew();
static void main_Position_From_Earth_Range();
static void main_Position_From_Moon_Range();
static void main_Quaternion_To_Attitude();
static void main_State_Error();

// Function Definitions

//
// Arguments    : double result[3]
// Return Type  : void
//
static void argInit_3x1_real_T(double result[3])
{
  int idx0;

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 3; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0] = argInit_real_T();
  }
}

//
// Arguments    : double result[9]
// Return Type  : void
//
static void argInit_3x3_real_T(double result[9])
{
  int idx0;
  int idx1;

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 3; idx0++) {
    for (idx1 = 0; idx1 < 3; idx1++) {
      // Set the value of the array element.
      // Change this value to the value that the application requires.
      result[idx0 + 3 * idx1] = argInit_real_T();
    }
  }
}

//
// Arguments    : double result[4]
// Return Type  : void
//
static void argInit_4x1_real_T(double result[4])
{
  int idx0;

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 4; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0] = argInit_real_T();
  }
}

//
// Arguments    : double result[6]
// Return Type  : void
//
static void argInit_6x1_real_T(double result[6])
{
  int idx0;

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 6; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0] = argInit_real_T();
  }
}

//
// Arguments    : double result[36]
// Return Type  : void
//
static void argInit_6x6_real_T(double result[36])
{
  int idx0;
  int idx1;

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 6; idx0++) {
    for (idx1 = 0; idx1 < 6; idx1++) {
      // Set the value of the array element.
      // Change this value to the value that the application requires.
      result[idx0 + 6 * idx1] = argInit_real_T();
    }
  }
}

//
// Arguments    : void
// Return Type  : double
//
static double argInit_real_T()
{
  return 0.0;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_Earth_SC_Moon_Angle()
{
  double dv0[3];
  double dv1[3];
  double angle_Earth_SC_Moon;

  // Initialize function 'Earth_SC_Moon_Angle' input arguments.
  // Initialize function input argument 'r_E_SC'.
  // Initialize function input argument 'r_E_M'.
  // Call the entry-point 'Earth_SC_Moon_Angle'.
  argInit_3x1_real_T(dv0);
  argInit_3x1_real_T(dv1);
  angle_Earth_SC_Moon = Earth_SC_Moon_Angle(dv0, dv1);
}

//
// Arguments    : void
// Return Type  : void
//
static void main_Kalman_Filter_Iteration()
{
  double x_hat[6];
  double phi[36];
  double P[36];
  double dv2[3];
  double dv3[6];
  double dv4[9];
  double X_est[6];

  // Initialize function 'Kalman_Filter_Iteration' input arguments.
  // Initialize function input argument 'x_hat'.
  argInit_6x1_real_T(x_hat);

  // Initialize function input argument 'phi'.
  argInit_6x6_real_T(phi);

  // Initialize function input argument 'P'.
  argInit_6x6_real_T(P);

  // Initialize function input argument 'Y'.
  // Initialize function input argument 'X_ref'.
  // Initialize function input argument 'R'.
  // Call the entry-point 'Kalman_Filter_Iteration'.
  argInit_3x1_real_T(dv2);
  argInit_6x1_real_T(dv3);
  argInit_3x3_real_T(dv4);
  Kalman_Filter_Iteration(x_hat, phi, P, dv2, dv3, dv4, X_est);
}

//
// Arguments    : void
// Return Type  : void
//
static void main_Position_From_Angles_Slew()
{
  double dv5[3];
  double dv6[4];
  double dv7[4];
  double dv8[3];
  double r_E_SC1[3];
  double r_E_SC2[3];

  // Initialize function 'Position_From_Angles_Slew' input arguments.
  // Initialize function input argument 'r_E_M'.
  // Initialize function input argument 'q_E'.
  // Initialize function input argument 'q_M'.
  // Initialize function input argument 'vel'.
  // Call the entry-point 'Position_From_Angles_Slew'.
  argInit_3x1_real_T(dv5);
  argInit_4x1_real_T(dv6);
  argInit_4x1_real_T(dv7);
  argInit_3x1_real_T(dv8);
  Position_From_Angles_Slew(dv5, dv6, dv7, argInit_real_T(), argInit_real_T(),
    dv8, argInit_real_T(), r_E_SC1, r_E_SC2);
}

//
// Arguments    : void
// Return Type  : void
//
static void main_Position_From_Earth_Range()
{
  double dv9[4];
  double r_E_SC[3];

  // Initialize function 'Position_From_Earth_Range' input arguments.
  // Initialize function input argument 'q_E'.
  // Call the entry-point 'Position_From_Earth_Range'.
  argInit_4x1_real_T(dv9);
  Position_From_Earth_Range(dv9, argInit_real_T(), argInit_real_T(),
    argInit_real_T(), r_E_SC);
}

//
// Arguments    : void
// Return Type  : void
//
static void main_Position_From_Moon_Range()
{
  double dv10[3];
  double dv11[4];
  double r_E_SC[3];

  // Initialize function 'Position_From_Moon_Range' input arguments.
  // Initialize function input argument 'r_E_M'.
  // Initialize function input argument 'q_M'.
  // Call the entry-point 'Position_From_Moon_Range'.
  argInit_3x1_real_T(dv10);
  argInit_4x1_real_T(dv11);
  Position_From_Moon_Range(dv10, dv11, argInit_real_T(), argInit_real_T(),
    argInit_real_T(), r_E_SC);
}

//
// Arguments    : void
// Return Type  : void
//
static void main_Quaternion_To_Attitude()
{
  double dv12[4];
  double r_SC_body[3];

  // Initialize function 'Quaternion_To_Attitude' input arguments.
  // Initialize function input argument 'q'.
  // Call the entry-point 'Quaternion_To_Attitude'.
  argInit_4x1_real_T(dv12);
  Quaternion_To_Attitude(dv12, r_SC_body);
}

//
// Arguments    : void
// Return Type  : void
//
static void main_State_Error()
{
  double dv13[6];
  double dv14[6];
  double posError[3];
  double velError[3];

  // Initialize function 'State_Error' input arguments.
  // Initialize function input argument 'X_ref'.
  // Initialize function input argument 'X_est'.
  // Call the entry-point 'State_Error'.
  argInit_6x1_real_T(dv13);
  argInit_6x1_real_T(dv14);
  State_Error(dv13, dv14, posError, velError);
}

//
// Arguments    : int argc
//                const char * const argv[]
// Return Type  : int
//
int main(int, const char * const [])
{
  // Initialize the application.
  // You do not need to do this more than one time.
  Earth_SC_Moon_Angle_initialize();

  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_Earth_SC_Moon_Angle();
  main_Kalman_Filter_Iteration();
  main_Position_From_Angles_Slew();
  main_Position_From_Earth_Range();
  main_Position_From_Moon_Range();
  main_Quaternion_To_Attitude();
  main_State_Error();

  // Terminate the application.
  // You do not need to do this more than one time.
  Earth_SC_Moon_Angle_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
