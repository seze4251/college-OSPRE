//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: analyzeImage.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "analyzeImage_emxutil.h"
#include "imfindcircles.h"
#include "sum.h"
#include "imreconstruct.h"
#include "padarray.h"
// #include "isfinite.h"
// #include "imhist.h"
#include "analyzeImage_rtwutil.h"

//
#include <stdio.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <ctime>
#include "../../include/Exception/OSPRE_Exceptions.h"

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

// Function Definitions

//
// Set up eval variables
// Arguments    : const emxArray_uint8_T *imIn
//                const double radiusRangeGuess[2]
//                double sensVal
//                const double pxDeg[2]
//                double imgWidth
//                double imgHeight
//                double centerPt_data[]
//                int centerPt_size[2]
//                double *radius
//                double *numCirc
//                double *alpha
//                double *beta
//                double *theta
// Return Type  : void
//
void analyzeImage(const emxArray_uint8_T *imIn, const double
                  radiusRangeGuess[2], double sensVal, const double pxDeg[2], double imgWidth,
                  double imgHeight, double centerPt_data[], int centerPt_size[2], double *radius,
                  double *numCirc, double *alpha, double *beta, double *theta, int rectCoords[2])
{
  short origSize[3];
  int i0;
  emxArray_uint8_T *im;
  double sizeI;
  int i;
  emxArray_boolean_T *bw;
  double idx2;
  static const double b[3] = { 0.29893602129377539, 0.58704307445112125,
    0.11402090425510336 };

  unsigned char u0;
  emxArray_real_T *centers;
  emxArray_real_T *radii;
  short sizeOutput[2];
  emxArray_uint8_T *maskPad;
  double b_centers[2];
  emxArray_uint8_T *markerPad;
  emxArray_uint8_T *r0;
  int mtmp;
  emxArray_uint8_T *r1;
  int i1;
  emxArray_uint8_T *r2;
  int idx_size_idx_0;
  // short idx_data[8320];
  short idx_data[8384];
  short i2;
  // short tmp_data[4160];
  // short b_tmp_data[4160];
  // boolean_T b_idx_data[4160];
  short tmp_data[4192];
  short b_tmp_data[4192];
  boolean_T b_idx_data[4192];

  int idx_size[1];
  int b_idx_size[1];

  // Temporary variables for angular diameter calculation
  int xCenter = imgWidth/2;
  int yCenter = imgHeight/2;
  double thetaX, thetaY;

  //  Anthony Torres
  //  OSPRE
  //  analyzeImage.m
  //  Created: 1/13/17
  //  Modified: 1/13/17
  //  Preprocessing section
  for (i0 = 0; i0 < 3; i0++) {
    origSize[i0] = (short)imIn->size[i0];
  }

  emxInit_uint8_T(&im, 2);
  i0 = im->size[0] * im->size[1];
  im->size[0] = origSize[0];
  im->size[1] = origSize[1];
  emxEnsureCapacity((emxArray__common *)im, i0, sizeof(unsigned char));
  sizeI = (double)(imIn->size[0] * imIn->size[1]) * 3.0 / 3.0;
  for (i = 0; i < (int)sizeI; i++) {
    origSize[0] = imIn->data[i];
    origSize[1] = imIn->data[(int)((1.0 + (double)i) + sizeI) - 1];
    origSize[2] = imIn->data[(int)((1.0 + (double)i) + 2.0 * sizeI) - 1];
    idx2 = 0.0;
    for (i0 = 0; i0 < 3; i0++) {
      idx2 += (double)origSize[i0] * b[i0];
    }

    idx2 = rt_roundd_snf(idx2);
    if (idx2 < 256.0) {
      u0 = (unsigned char)idx2;
    } else {
      u0 = MAX_uint8_T;
    }

    im->data[i] = u0;
  }

  emxInit_boolean_T(&bw, 2);

  //  Convert to BW, hreshold, and fill image
  //------------------Beginning of BW conversion--------------

  i0 = bw->size[0] * bw->size[1];
  bw->size[0] = im->size[0];
  bw->size[1] = im->size[1];
  emxEnsureCapacity((emxArray__common *)bw, i0, (int)sizeof(boolean_T));
  i = im->size[0] * im->size[1];
  for (i0 = 0; i0 < i; i0++) {
    bw->data[i0] = (im->data[i0] > 63.75);
  }

  if (!((bw->size[0] == 0) || (bw->size[1] == 0))) {
    i0 = im->size[0] * im->size[1];
    im->size[0] = bw->size[0];
    im->size[1] = bw->size[1];
    emxEnsureCapacity((emxArray__common *)im, i0, (int)sizeof(unsigned char));
    i = bw->size[0] * bw->size[1];
    for (i0 = 0; i0 < i; i0++) {
      im->data[i0] = bw->data[i0];
    }

    for (i0 = 0; i0 < 2; i0++) {
      sizeOutput[i0] = (short)((short)bw->size[i0] + 2);
    }

    emxInit_uint8_T(&maskPad, 2);
    i0 = maskPad->size[0] * maskPad->size[1];
    maskPad->size[0] = sizeOutput[0];
    maskPad->size[1] = sizeOutput[1];
    emxEnsureCapacity((emxArray__common *)maskPad, i0, (int)sizeof(unsigned char));
    for (i0 = 0; i0 < 2; i0++) {
      sizeOutput[i0] = (short)((short)bw->size[i0] + 2);
    }

    emxInit_uint8_T(&markerPad, 2);
    emxInit_uint8_T(&r0, 2);
    i0 = markerPad->size[0] * markerPad->size[1];
    markerPad->size[0] = sizeOutput[0];
    markerPad->size[1] = sizeOutput[1];
    emxEnsureCapacity((emxArray__common *)markerPad, i0, (int)sizeof(unsigned
      char));
    padarray(im, r0);
    i = r0->size[1];
    for (i0 = 0; i0 < i; i0++) {
      mtmp = r0->size[0];
      for (i1 = 0; i1 < mtmp; i1++) {
        maskPad->data[i1 + maskPad->size[0] * i0] = r0->data[i1 + r0->size[0] *
          i0];
      }
    }

    emxFree_uint8_T(&r0);
    emxInit_uint8_T(&r1, 2);
    i0 = r1->size[0] * r1->size[1];
    r1->size[0] = im->size[0];
    r1->size[1] = im->size[1];
    emxEnsureCapacity((emxArray__common *)r1, i0, (int)sizeof(unsigned char));
    i = im->size[0] * im->size[1];
    for (i0 = 0; i0 < i; i0++) {
      r1->data[i0] = MAX_uint8_T;
    }

    emxInit_uint8_T(&r2, 2);
    padarray(r1, r2);
    i = r2->size[1];
    emxFree_uint8_T(&r1);
    for (i0 = 0; i0 < i; i0++) {
      mtmp = r2->size[0];
      for (i1 = 0; i1 < mtmp; i1++) {
        markerPad->data[i1 + markerPad->size[0] * i0] = r2->data[i1 + r2->size[0]
          * i0];
      }
    }

    emxFree_uint8_T(&r2);
    for (i0 = 0; i0 < 2; i0++) {
      sizeOutput[i0] = (short)markerPad->size[i0];
    }

    mtmp = sizeOutput[0];
    if (sizeOutput[1] > sizeOutput[0]) {
      mtmp = sizeOutput[1];
    }

    idx_size_idx_0 = mtmp - 2;
    i = (mtmp - 2) << 1;
    for (i0 = 0; i0 < i; i0++) {
      idx_data[i0] = 0;
    }

    for (mtmp = 0; mtmp < 2; mtmp++) {
      i0 = markerPad->size[mtmp] - 2;
      i = (short)((short)i0 - 1);
      for (i1 = 0; i1 <= i; i1++) {
        tmp_data[i1] = (short)i1;
      }

      i2 = (short)((short)(markerPad->size[mtmp] - 1) - 2);
      i = i2;
      for (i1 = 0; i1 <= i; i1++) {
        b_tmp_data[i1] = (short)(2 + i1);
      }

      i = (short)((short)i0 - 1) + 1;
      for (i0 = 0; i0 < i; i0++) {
        idx_data[tmp_data[i0] + idx_size_idx_0 * mtmp] = b_tmp_data[i0];
      }
    }

    i0 = maskPad->size[0] * maskPad->size[1];
    emxEnsureCapacity((emxArray__common *)maskPad, i0, (int)sizeof(unsigned char));
    mtmp = maskPad->size[0];
    i = maskPad->size[1];
    i *= mtmp;
    for (i0 = 0; i0 < i; i0++) {
      maskPad->data[i0] = (unsigned char)(255U - maskPad->data[i0]);
    }

    i0 = markerPad->size[0] * markerPad->size[1];
    emxEnsureCapacity((emxArray__common *)markerPad, i0, (int)sizeof(unsigned
      char));
    mtmp = markerPad->size[0];
    i = markerPad->size[1];
    i *= mtmp;
    for (i0 = 0; i0 < i; i0++) {
      markerPad->data[i0] = (unsigned char)(255U - markerPad->data[i0]);
    }

    imreconstruct(markerPad, maskPad);
    i0 = markerPad->size[0] * markerPad->size[1];
    emxEnsureCapacity((emxArray__common *)markerPad, i0, (int)sizeof(unsigned
      char));
    mtmp = markerPad->size[0];
    i = markerPad->size[1];
    i *= mtmp;
    emxFree_uint8_T(&maskPad);
    for (i0 = 0; i0 < i; i0++) {
      markerPad->data[i0] = (unsigned char)(255U - markerPad->data[i0]);
    }

    idx_size[0] = idx_size_idx_0;
    for (i0 = 0; i0 < idx_size_idx_0; i0++) {
      b_idx_data[i0] = (idx_data[i0] != 0);
    }

    sizeI = sum(b_idx_data, idx_size);
    b_idx_size[0] = idx_size_idx_0;
    for (i0 = 0; i0 < idx_size_idx_0; i0++) {
      b_idx_data[i0] = (idx_data[i0 + idx_size_idx_0] != 0);
    }

    idx2 = sum(b_idx_data, b_idx_size);
    sizeOutput[0] = (short)(markerPad->size[0] - 2);
    sizeOutput[1] = (short)(markerPad->size[1] - 2);
    i0 = bw->size[0] * bw->size[1];
    bw->size[0] = sizeOutput[0];
    bw->size[1] = sizeOutput[1];
    emxEnsureCapacity((emxArray__common *)bw, i0, (int)sizeof(boolean_T));
    for (i = 0; i < (int)sizeI; i++) {
      for (mtmp = 0; mtmp < (int)idx2; mtmp++) {
        bw->data[i + bw->size[0] * mtmp] = (markerPad->data[(idx_data[i] +
          markerPad->size[0] * (idx_data[mtmp + idx_size_idx_0] - 1)) - 1] != 0);
      }
    }

    emxFree_uint8_T(&markerPad);
    i0 = bw->size[0] * bw->size[1];
    emxEnsureCapacity((emxArray__common *)bw, i0, (int)sizeof(boolean_T));
  }

  emxFree_uint8_T(&im);
  emxInit_real_T(&centers, 2);
  emxInit_real_T(&radii, 2);

  //------------------End of BW conversion--------------

  //  Analyze image to find center point and radius
  //  Find circle fit through CHT
  imfindcircles(bw, radiusRangeGuess, sensVal, centers, radii);

  //  Check for valid find
  emxFree_boolean_T(&bw);
  if ((centers->size[0] == 0) || (centers->size[1] == 0)) {
    // // warning('No centers!')
    // centerPt_size[0] = 1;
    // centerPt_size[1] = 1;
    // centerPt_data[0] = rtNaN;
    // *radius = rtNaN;
    // *numCirc = rtNaN;
    // *alpha = rtNaN;
    // *beta = rtNaN;
    // *theta = rtNaN;
    // If no objects throw error
    char logString[50];
    sprintf(logString,"Exception Time = %ld, Expected to find celestial body but did not find anything; \
            radius guess: [%f %f], sensVal: %f", time(0), radiusRangeGuess[0], radiusRangeGuess[1],
            sensVal);

    // Output image to file
    //cv::Mat tempMat = cv::Mat((int)imgHeight, (int)imgWidth, CV_8UC3, (imIn->data));
    //cv::imshow("image", tempMat);
    //cv::waitKey(0);

    //imwrite("/home/anthony/Github/OSPRE/Image_Processing/analyzeImagePi/errorImage2.bmp", tempMat);

    std::cout << "------------NO BODY IN IMAGE----------" << std::endl;
    std::cout << "Exception time " << time(0) << std::endl;
    std::cout << "Radius Guess: " << radiusRangeGuess[0] << ", " << radiusRangeGuess[1] << std::endl;
    std::cout << "SensVal: " << sensVal << std::endl;

    emxFree_real_T(&radii);
    emxFree_real_T(&centers);

    throw NoBodyInImage(logString);
  } else {
    centers->data[0] = centers->data[0] + rectCoords[0];
    centers->data[1] = centers->data[1] + rectCoords[1];
    //  Return found information
    b_centers[0] = centers->data[0];
    b_centers[1] = centers->data[1];
    centerPt_size[0] = 1;
    centerPt_size[1] = 2;
    for (i0 = 0; i0 < 2; i0++) {
      centerPt_data[i0] = b_centers[i0];
    }

    *alpha = (centers->data[0] - imgWidth / 2.0) / pxDeg[0];
    *beta = (centers->data[1] - imgHeight / 2.0) / pxDeg[1];
    *radius = radii->data[0];
    *theta = 2.0 * radii->data[0] / ((pxDeg[0] + pxDeg[1]) / 2.0);
    if ((radii->size[0] == 0) || (radii->size[1] == 0)) {
      i = 0;
    } else {
      mtmp = radii->size[0];
      i = radii->size[1];
      if(mtmp >= i){
        i = mtmp;
      }
    }

    double validAlpha = imgWidth/pxDeg[0];
    double validBeta = imgHeight/pxDeg[1];
    double validTheta = radiusRangeGuess[1]*(pxDeg[0] + pxDeg[1]); // Calculate average valid theta
    double validThetaDelta = (radiusRangeGuess[1]-radiusRangeGuess[0])*(pxDeg[0] + pxDeg[1])*0.5; // Calculate the change in theta to calculate valide range space
    // TODO:
    // - combine this into it's own function
    if(*alpha > validAlpha || *alpha < -validAlpha){
      // throw alpha out of range
      char logString[50];
      sprintf(logString, "Exception Time = %ld, Invalid alpha found; alpha: %f \
              radius guess: [%f %f], sensVal: %f", time(0), *alpha, radiusRangeGuess[0], radiusRangeGuess[1],
              sensVal);
      emxFree_real_T(&radii);
      emxFree_real_T(&centers);
      throw InvalidAlphaBetaTheta(logString);
    }
    if(*beta > validBeta || *beta < -validBeta){
      // throw beta out of range
      char logString[50];
      sprintf(logString,"Exception Time = %ld, Invalid beta found; beta: %f \
              radius guess: [%f %f], sensVal: %f", time(0), *beta, radiusRangeGuess[0], radiusRangeGuess[1],
              sensVal);
      emxFree_real_T(&radii);
      emxFree_real_T(&centers);
      throw InvalidAlphaBetaTheta(logString);
    }
    if(*theta > (validTheta + validThetaDelta) || *theta < (-validTheta - validThetaDelta)){
      // throw theta out of range error
      char logString[50];
      sprintf(logString,"Exception Time = %ld, Invalid theta found; theta: %f \
              radius guess: [%f %f], sensVal: %f", time(0), *theta, radiusRangeGuess[0], radiusRangeGuess[1],
              sensVal);
      emxFree_real_T(&radii);
      emxFree_real_T(&centers);
      throw InvalidAlphaBetaTheta(logString);
    }

    *numCirc = i;
  }

  emxFree_real_T(&radii);
  emxFree_real_T(&centers);
}

//
// File trailer for analyzeImage.cpp
//
// [EOF]
//
