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
#include <stdio.h>

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

// Add timing functionality
#include <ctime>

// Namespaces
using namespace cv;

// Function Declarations
static void main_analyzeImage();
static void argInit_736x1100x3_uint8_T(unsigned char);

// Function Definitions

// This initializes an empty image with dims 736x1100
// Unused but it may be useful for decyphering how Matlab handles images
//
/*
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
 } */

//
// Call analyzeImage
//
// Arguments    : void
// Return Type  : void
//
static void main_analyzeImage(unsigned char uv3[2428800])
{
    // Initialize variables
    //  static unsigned char uv3[2428800];
    double dv3[2] = {157, 167};
    double centerPt_data[2];
    int centerPt_size[2];
    double radius;
    double numCirc;
    double sensVal = 0.99;
    double alpha = -1; double beta = -1; double theta = -1;
    double pxDeg[2] = {67, 67};
    int imgWidth = 4160; int imgHeight = 3120; // These need to be updated to retrieve them from CameraController
    
    std::clock_t start;
    
    // Initialize function 'analyzeImage' input arguments.
    // Initialize function input argument 'imIn'.
    // Initialize function input argument 'radiusRangeGuess'.
    // Call the entry-point 'analyzeImage'.
    std::cout << "Starting Analyze Image Call" << std::endl;
    start = std::clock();
    analyzeImage(uv3, dv3, sensVal, centerPt_data, centerPt_size, &radius,
                 &numCirc, &alpha, &beta, &theta, pxDeg, imgWidth, imgHeight);
    std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
    std::cout << "Finished Analyze Image Call" << std::endl;
    
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
int main(int argc, char** argv)
{
    // Get image
    Mat image;
    image = imread(argv[1], IMREAD_COLOR);
    
    // Initialize blank image
    unsigned char imIn[2428800];
    Vec3b intensity;
    
    if(!image.data){
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    
    //  unsigned char* dataMat = image.data;
    
    int counter = 0;
    // Loop through image and convert
    for (int i=0; i < image.cols; i++){
        for (int j=0; j < image.rows; j++){
            intensity = image.at<Vec3b>(j,i);
            uchar blue = intensity.val[0];
            uchar green = intensity.val[1];
            uchar red = intensity.val[2];
            imIn[counter] = red;
            imIn[counter + 809600] = green;
            imIn[counter + 2*809600] = blue;
            counter++;
        }
    }
    
    std::cout << "Image Values" << std::endl;
    printf("%04x", imIn[23342]);
    
    // Initialize the application.
    // You do not need to do this more than one time.
    //analyzeImage_initialize();
    
    // Invoke the entry-point functions.
    // You can call entry-point functions multiple times.
    main_analyzeImage(imIn);
    
    // Terminate the application.
    // You do not need to do this more than one time.
    // analyzeImage_terminate();
    return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//