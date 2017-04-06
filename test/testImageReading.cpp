/* Anthony Torres
OSPRE
testImageReading.cpp

*/

// Include Files
#include "../Image_Processing/analyzeImagePi/rt_nonfinite.h"
#include "testImageReading.h"
#include "../Image_Processing/analyzeImagePi/analyzeImage_terminate.h"
#include "../Image_Processing/analyzeImagePi/analyzeImage_emxAPI.h"
#include "../Image_Processing/analyzeImagePi/analyzeImage_initialize.h"

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

// Add timing functionality
#include <ctime>

// Function Declarations
static void argInit_1x2_real_T(double result[2]);
static emxArray_uint8_T *argInit_d3120xd4160x3_uint8_T(unsigned char*);
static double argInit_real_T();
static unsigned char argInit_uint8_T();
static void main_imageRead();


// 
// Arguments    : double result[2]
// Return Type  : void
// Purpose : Creates empty 1x2 array
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
  result = emxCreateND_uint8_T(3, *(int (*)[3])&iv5[0]);

  //Initalize temp variables
  Vec3b intensity;

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

  result->data = imInput;
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
static void main_imageRead()
{
  emxArray_uint8_T *imIn;
  unsigned char* imInC = new unsigned char[402936000];

  double imgWidth = 4160; double imgHeight = 3120;


  // Load image with OpenCV
  std::cout << "Reading image with OpenCV" << std::endl;
  Mat image;
  Vec3b intensity;
  image = imread("0p0flat.jpg", IMREAD_COLOR);
  std::cout << "Displaying image..." << std::endl;
  cv::namedWindow("Direct Image from OpenCV", WINDOW_NORMAL);
  cv::imshow("Direct Image from OpenCV", image);
  cv::waitKey(0);
  std::cout << "...finished image display" << std::endl;

  int counter = 0;
  // Loop through image and convert
  std::cout << "Converting image to unsigned char[]" << std::endl;
  for(int i=0; i< image.cols; i++){
    for(int j=0; j < image.rows; j++){
      intensity = image.at<Vec3b>(j,i);
      uchar blue = intensity.val[0];
      uchar green = intensity.val[1];
      uchar red = intensity.val[2];
      *(imInC + counter) = red;
      *(imInC + counter + image.cols*image.rows) = green;
      *(imInC + counter + 2*image.cols*image.rows) = blue;
      counter++;
    }
  }
  std::cout << "Finished image conversion" << std::endl;
  // Initialize function input argument 'imIn'.
  std::cout << "Translating image into emxArray" << std::endl;
  imIn = argInit_d3120xd4160x3_uint8_T(imInC);
  std::cout << "Finished image translation" << std::endl;

  // Initialize function input argument 'radiusRangeGuess'.
  // Initialize function input argument 'pxDeg'.
  // Call the entry-point 'analyzeImage'.
  //argInit_1x2_real_T(dv1);
  //argInit_1x2_real_T(dv2);

  std::cout << "Displaying emxArray image..." << std::endl;
  cv::Mat tempMat = cv::Mat((int)imgHeight, (int)imgWidth, CV_8UC3, (imIn->data));

  cv::namedWindow("Image After Conversion", WINDOW_NORMAL);
  cv::imshow("Image After Conversion", tempMat);
  //cv::resizeWindow("Display frame", 600, 600);
  cv::waitKey(0);
  std::cout << "...finished emxArray display. Writing image to \"errorImage-main.bmp\"" << std::endl;

  imwrite("/home/anthony/Github/OSPRE/Image_Processing/analyzeImagePi/errorImage-Main.bmp", tempMat);

  std::cout << "Starting analyze image call" << std::endl;

  emxDestroyArray_uint8_T(imIn);

  return;
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
  main_imageRead();

  // Terminate the application.
  // You do not need to do this more than one time.
  //analyzeImage_terminate();
  return 0;
}