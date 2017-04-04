//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: main.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
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
#include "analyzeImage_emxAPI.h"
#include "analyzeImage_initialize.h"

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

// Add timing functionality
#include <ctime>

// Namespaces
using namespace cv;

// Function Declarations
static void argInit_1x2_real_T(double result[2]);
static emxArray_uint8_T *argInit_d3120xd4160x3_uint8_T(cv::Mat imageIn);
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
// Arguments    : void
// Return Type  : emxArray_uint8_T *
//
static emxArray_uint8_T *argInit_d3120xd4160x3_uint8_T(cv::Mat imageIn)
{
  emxArray_uint8_T *result;
  static int iv5[3] = { 2, 2, 3 };

  int idx0;
  int idx1;
  int idx2;

  int imgPartitionVal = (result->size[0U])*(result->size[1U]);

  // Set the size of the array.
  // Change this size to the value that the application requires.
  result = emxCreateND_uint8_T(3, *(int (*)[3])&iv5[0]);

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
      for (idx2 = 0; idx2 < 3; idx2++) {
        // Find pixel value
        intensity = imageIn.at<Vec3b>(idx1, idx0);
        // Set the value of the array element.
        // Change this value to the value that the application requires.
        result->data[(idx0 + result->size[0] * idx1) + result->size[0] *
         result->size[1] * idx2] = intensity.val[idx2]; //argInit_uint8_T();

      }
    }
  }

  return result;
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
static void main_analyzeImage()
{
  emxArray_uint8_T *imIn;
  double radiusRangeGuess[2] = {157, 167};
  double pxDeg[2] = {67, 67};
  double centerPt_data[2];
  int centerPt_size[2];
  double radius;
  double numCirc;
  double alpha;
  double beta;
  double theta;

  int imgWidth = 4160; int imgHeight = 3120;
  std::clock_t start;

  // Initialize function 'analyzeImage' input arguments.
  // Load image with OpenCV
  Mat image;
  image = imread(argv[1], IMREAD_COLOR);
  // Initialize function input argument 'imIn'.
  imIn = argInit_d3120xd4160x3_uint8_T(image);

  // Initialize function input argument 'radiusRangeGuess'.
  // Initialize function input argument 'pxDeg'.
  // Call the entry-point 'analyzeImage'.
  argInit_1x2_real_T(dv1);
  argInit_1x2_real_T(dv2);

  std::cout << "Starting analyze image call" << std::endl;
  start = std::clock();
  analyzeImage(   imIn, radiusRangeGuess,
                  sensVal, centerPt_data, centerPt_size,
                  &radius, &numCirc, 
                  &alpha, &beta, &theta,  
                  pxDeg, imgWidth, imgHeight);

  std::cout << "Time: " << (std::clock() - start) /(double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
  std::cout << "Finished analyze image call" << std::endl;

  emxDestroyArray_uint8_T(imIn);
  // Print info
  if(!numCirc){
      std::cout << "No objects found" << std::endl;
  } else {
      std::cout << "Found " << numCirc << " object(s)!" << std::endl;
      std::cout << "Center: " << centerPt_data[0] << ", " << centerPt_data[1] << std::endl;
      std::cout << "Radius: " << radius << std::endl;
      std::cout << "Alpha: " << alpha << " Beta: " << beta << " Theta: " << theta << std::endl;
  }
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
  //analyzeImage_initialize();

  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_analyzeImage();

  // Terminate the application.
  // You do not need to do this more than one time.
  //analyzeImage_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
