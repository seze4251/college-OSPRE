//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: main.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 14-Feb-2017 14:49:57
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
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "main.h"
#include "analyzeImage_terminate.h"
#include "analyzeImage_initialize.h"

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

// Namespaces
using namespace cv;

// Function Declarations
static void argInit_1x2_real_T(double result[2]);
static void argInit_736x1100x3_uint8_T(unsigned char result[2428800]);
static double argInit_real_T();
static unsigned char argInit_uint8_T();
static void main_analyzeImage();

// Function Definitions

//
// Arguments    : double result[2]
// Return Type  : void
//
static void argInit_1x2_real_T(double result[2])
{
  int idx1;

  // Loop over the array to initialize each element.
  for (idx1 = 0; idx1 < 2; idx1++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx1] = argInit_real_T();
  }
}

//
// Arguments    : unsigned char result[2428800]
// Return Type  : void
//
static void argInit_736x1100x3_uint8_T(unsigned char result[2428800])
{
  int idx0;
  int idx1;
  int idx2;

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 736; idx0++) {
    for (idx1 = 0; idx1 < 1100; idx1++) {
      for (idx2 = 0; idx2 < 3; idx2++) {
        // Set the value of the array element.
        // Change this value to the value that the application requires.
        result[(idx0 + 736 * idx1) + 809600 * idx2] = argInit_uint8_T();
      }
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
// Return Type  : unsigned char
//
static unsigned char argInit_uint8_T()
{
  return 0;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_analyzeImage(unsigned char uv3[2428800])
{
//  static unsigned char uv3[2428800];
  double dv3[2] = {157, 167};
  double centerPt_data[2];
  int centerPt_size[2];
  double radius;
  double numCirc;
  double sensVal = 0.99;

  // Initialize function 'analyzeImage' input arguments.
  // Initialize function input argument 'imIn'.
  // Initialize function input argument 'radiusRangeGuess'.
  // Call the entry-point 'analyzeImage'.
//  argInit_736x1100x3_uint8_T(uv3);
//  argInit_1x2_real_T(dv3);
std::cout << "Starting Analyze Image Call" << std::endl;
  analyzeImage(uv3, dv3, sensVal, centerPt_data, centerPt_size, &radius,
               &numCirc);
std::cout << "Finished Analyze Image Call" << std::endl;

  // Print info
  if(!numCirc){
    std::cout << "No objects found" << std::endl;
  } else {
    std::cout << "Found " << numCirc << " object(s)!" << std::endl;
  }
}

//
// Arguments    : int argc
//                const char * const argv[]
// Return Type  : int
//
int main(int argc, char** argv)
{
  // Get image
  Mat image;
  image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
  
  if(!image.data){
    std::cout << "Could not open or find the image" << std::endl;
    return -1;
  }

  unsigned char* dataMat = image.data;

  // Initialize the application.
  // You do not need to do this more than one time.
  analyzeImage_initialize();

  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_analyzeImage(dataMat);

  // Terminate the application.
  // You do not need to do this more than one time.
  analyzeImage_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
