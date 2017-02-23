//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: main.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 21-Feb-2017 11:45:08
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
#include "Position_From_Moon_Range.h"
#include "main.h"
#include "Position_From_Moon_Range_terminate.h"
#include "Position_From_Moon_Range_initialize.h"

// Function Declarations
static void argInit_3x1_real_T(double result[3]);
static void argInit_4x1_real_T(double result[4]);
static double argInit_real_T();
static void main_Position_From_Moon_Range();

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
static void main_Position_From_Moon_Range()
{
  double dv0[3];
  double dv1[4];
  double r_E_SC[3];

  // Initialize function 'Position_From_Moon_Range' input arguments.
  // Initialize function input argument 'r_E_M'.
  // Initialize function input argument 'q_M'.
  // Call the entry-point 'Position_From_Moon_Range'.
  argInit_3x1_real_T(dv0);
  argInit_4x1_real_T(dv1);
  Position_From_Moon_Range(dv0, dv1, argInit_real_T(), argInit_real_T(),
    argInit_real_T(), r_E_SC);
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
  Position_From_Moon_Range_initialize();

  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_Position_From_Moon_Range();

  // Terminate the application.
  // You do not need to do this more than one time.
  Position_From_Moon_Range_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
