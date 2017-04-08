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
#include "analyzeImage_emxutil.h"
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
static emxArray_uint8_T *argInit_d3120xd4160x3_uint8_T(unsigned char*);
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
static emxArray_uint8_T *argInit_d3120xd4160x3_uint8_T(unsigned char* imInput)
{
  emxArray_uint8_T *result;
  static int iv5[3] = { 2, 2, 3 };

  int idx0;
  int idx1;
  int idx2;

  //int imgPartitionVal = (result->size[0U])*(result->size[1U]);

  // Set the size of the array.
  // Change this size to the value that the application requires.
  //result = emxCreateND_uint8_T(3, *(int (*)[3])&iv5[0]);
  result = emxCreateWrapperND_uint8_T(imInput, 3, *(int (*)[3])&iv5[0]);

  //Initalize temp variables
  //Vec3b intensity;

  // Loop over the array to initialize each element.
  // for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
  //   for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
  //     for (idx2 = 0; idx2 < 3; idx2++) {
  //       // Set the value of the array element.
  //       // Change this value to the value that the application requires.
  //       result->data[(idx0 + result->size[0] * idx1) + result->size[0] *
  //        result->size[1] * idx2] = *(imInput + idx2*13431200);
  //       // result->data[(idx0 + result->size[0] * idx1) + result->size[0] *
  //       //  result->size[1] * idx2] = *(imInput + (idx0 + result->size[0] * idx1) + result->size[0] *
  //       //  result->size[1] * idx2);

  //     }
  //   }
  // }

  //result->data = imInput;
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
  //Working values for blueMoon.jpg:
  // radiusRangeGuess[2] = {157, 167};
  // sensVal = 0.99;

  emxArray_uint8_T *imIn;
  //double radiusRangeGuess[2] = {157, 167};
  double radiusRangeGuess[2] = {58, 63};
  double pxDeg[2] = {67, 67};
  double centerPt_data[2];
  int centerPt_size[2];
  double radius;
  double numCirc;
  double alpha;
  double beta;
  double theta;
  //double sensVal = 0.99;
  double sensVal = 0.97;

  double imgWidth = 4160; double imgHeight = 3120;
  //double imgWidth = 1100; double imgHeight = 736;
  std::clock_t start;

  //unsigned char* imInC = new unsigned char[2428800];
  unsigned char* imInC = new unsigned char[402936000];

  // Initialize function 'analyzeImage' input arguments.
  // Load image with OpenCV
  std::cout << "Reading image with OpenCV" << std::endl;
  Mat image;
  // Vec3b intensity;
  // image = imread("blueMoon.jpg", IMREAD_COLOR);
  image = imread("0p0flat.jpg", IMREAD_COLOR);
  if(!image.data){
    std::cout << "Could not read image" << std::endl;
    return;
  }
  // cv::namedWindow("Direct Image from OpenCV", WINDOW_NORMAL);
  // cv::imshow("Direct Image from OpenCV", image);
  // //cv::resizeWindow("Display frame", 600, 600);
  // cv::waitKey(0);
  // std::cout << "Finished image read with OpenCV" << std::endl;

  // int counter = 0;
  // // Loop through image and convert
  // std::cout << "Converting image to unsigned char[]" << std::endl;
  // for(int i=0; i< image.cols; i++){
  //   for(int j=0; j < image.rows; j++){
  //     intensity = image.at<Vec3b>(j,i);
  //     uchar blue = intensity.val[0];
  //     uchar green = intensity.val[1];
  //     uchar red = intensity.val[2];
  //     *(imInC + counter) = red;
  //     *(imInC + counter + image.cols*image.rows) = green;
  //     *(imInC + counter + 2*image.cols*image.rows) = blue;
  //     counter++;
  //   }
  // }
  // std::cout << "Finished image conversion" << std::endl;
  // // Initialize function input argument 'imIn'.
  // std::cout << "Translating image into emxArray" << std::endl;
  // imIn = argInit_d3120xd4160x3_uint8_T(imInC);
  // std::cout << "Finished image translation" << std::endl;

  // // Initialize function input argument 'radiusRangeGuess'.
  // // Initialize function input argument 'pxDeg'.
  // // Call the entry-point 'analyzeImage'.
  // //argInit_1x2_real_T(dv1);
  // //argInit_1x2_real_T(dv2);

  // std::cout << "Outputing image" << std::endl;
  // cv::Mat tempMat = cv::Mat((int)imgHeight, (int)imgWidth, CV_8UC3, (imIn->data));

  // cv::namedWindow("Image After Conversion", WINDOW_NORMAL);
  // cv::imshow("Image After Conversion", tempMat);
  // //cv::resizeWindow("Display frame", 600, 600);
  // cv::waitKey(0);

  // imwrite("/home/anthony/Github/OSPRE/Image_Processing/analyzeImagePi/errorImage-Main.bmp", tempMat);

  // std::cout << "Starting analyze image call" << std::endl;
  //return;

  // Tyring something from mathworks.com/matlabcentral/answers/314818-how-matlab-coder-convert-the-image-to-unsinged-char
  std::cout << "Converting image to emxArray" << std::endl;
  emxArray_uint8_T *I;
  emxInitArray_uint8_T(&I, 3);

  Vec3b intensity;
  int sizeimage, counter;
  int rows = image.rows;
  int cols = image.cols;
  sizeimage = rows*cols;
  I->size[0] = rows;
  I->size[1] = cols;
  I->size[2] = 3;

  std::cout << "Converting..." << std::endl;
  emxEnsureCapacity((emxArray__common *)I, 0, (int)sizeof(unsigned char));
  try{
    counter = 0;
    for (int i=0; i < cols; i++){
      for (int j=0; j < rows; j++){
        intensity = image.at<Vec3b>(j,i);
        uchar blue = intensity.val[0];
        uchar green = intensity.val[1];
        uchar red = intensity.val[2];
        *(I->data + counter) = red;
        *(I->data + counter + sizeimage) = green;
        *(I->data + counter + 2*sizeimage) = blue;
        counter++;
      }
    }
  } catch(...) {
    std::cout << "FAILED" << std::endl;
    return;
  }

  std::cout << "\nStarting analyzeImage call" << std::endl;
  try{
    start = std::clock();
    analyzeImage( I, radiusRangeGuess, sensVal,
                  pxDeg, imgWidth, imgHeight, centerPt_data,
                  centerPt_size, &radius, &numCirc,
                  &alpha, &beta, &theta);
      // imIn, radiusRangeGuess,
      //               sensVal, centerPt_data, centerPt_size,
      //               &radius, &numCirc, 
      //               &alpha, &beta, &theta,  
      //               pxDeg, imgWidth, imgHeight);
  } catch(const char*){
    std::cout << "analyzeImage failed" << std::endl;
    std::cout << "Found " << numCirc << " object(s)!" << std::endl;
    std::cout << "Center: " << centerPt_data[0] << ", " << centerPt_data[1] << std::endl;
    std::cout << "Radius: " << radius << std::endl;
    std::cout << "Alpha: " << alpha << " Beta: " << beta << " Theta: " << theta << std::endl;
    return;
  }

  std::cout << "Time: " << (std::clock() - start) /(double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
  std::cout << "Finished analyze image call" << std::endl;
  std::cout << "Found " << numCirc << " object(s)!" << std::endl;
  std::cout << "Center: " << centerPt_data[0] << ", " << centerPt_data[1] << std::endl;
  std::cout << "Radius: " << radius << std::endl;
  std::cout << "Alpha: " << alpha << " Beta: " << beta << " Theta: " << theta << std::endl;

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
