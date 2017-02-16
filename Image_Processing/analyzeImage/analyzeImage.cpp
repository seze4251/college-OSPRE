//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: analyzeImage.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 14-Feb-2017 14:49:57
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "analyzeImage_emxutil.h"
#include "imfindcircles.h"
#include "sum.h"
#include "imreconstruct.h"
#include "padarray.h"
#include "isfinite.h"
#include "imhist.h"
#include "analyzeImage_rtwutil.h"
//#include <exception>
#include <stdexcept>

// Function Definitions

//
// Preprocessing section
// Arguments    : const unsigned char imIn[2428800]
//                const double radiusRangeGuess[2]
//                double sensVal
//                double centerPt_data[]
//                int centerPt_size[2]
//                double *radius
//                double *numCirc
// Return Type  : void
//
void analyzeImage(const unsigned char imIn[2428800], const double
                  radiusRangeGuess[2], double sensVal, double centerPt_data[],
                  int centerPt_size[2], double *radius, double *numCirc)
{
  static unsigned char im[809600];
  int i;
  unsigned char b_imIn[3];
  double sigma_b_squared[256];
  double num_elems;
  int k;
  int i0;
  double omega[256];
  static const double b[3] = { 0.29893602129377539, 0.58704307445112125,
    0.11402090425510336 };

  double mu[256];
  unsigned char u0;
  double maxval;
  double num_maxval;
  short idx[2200];
  static unsigned char uv0[809600];
  short i1;
  static unsigned char I1[813276];
  static unsigned char b_im[809600];
  short tmp_data[1100];
  static unsigned char uv1[813276];
  short b_tmp_data[1100];
  static unsigned char uv2[813276];
  boolean_T b_idx[1100];
  static boolean_T bw[809600];
  emxArray_real_T *centers;
  emxArray_real_T *radii;
  double b_centers[2];

  //  Anthony Torres
  //  OSPRE
  //  analyzeImage.m
  //  Created: 1/13/17
  //  Modified: 2/16/17

  // First level fail tests
  if (b_imIn == NULL) {
	  throw std::invalid_argument("Image is null!");
  }

  /*
  To Do:
  - Check edge quality
  - Check exposure
  - Perform other image checks
  */
  // Reconstruct image
  for (i = 0; i < 809600; i++) {
    b_imIn[0] = imIn[i];
    b_imIn[1] = imIn[809600 + i];
    b_imIn[2] = imIn[1619200 + i];
    num_elems = 0.0;
    for (i0 = 0; i0 < 3; i0++) {
      num_elems += (double)b_imIn[i0] * b[i0];
    }

    num_elems = rt_roundd_snf(num_elems);
    if (num_elems < 256.0) {
      u0 = (unsigned char)num_elems;
    } else {
      u0 = MAX_uint8_T;
    }

    im[i] = u0;
  }

  //  Convert to BW, hreshold, and fill image
  //-------------- Beginning of BS Conversion -------------
  imhist(im, sigma_b_squared);
  num_elems = 0.0;
  for (k = 0; k < 256; k++) {
    num_elems += sigma_b_squared[k];
  }

  omega[0] = sigma_b_squared[0] / num_elems;
  mu[0] = sigma_b_squared[0] / num_elems;
  for (k = 0; k < 255; k++) {
    num_maxval = sigma_b_squared[k + 1] / num_elems;
    omega[k + 1] = omega[k] + num_maxval;
    mu[k + 1] = mu[k] + num_maxval * (2.0 + (double)k);
  }

  maxval = rtMinusInf;
  for (k = 0; k < 256; k++) {
    num_elems = mu[255] * omega[k] - mu[k];
    num_elems = num_elems * num_elems / (omega[k] * (1.0 - omega[k]));
    if (!((maxval >= num_elems) || rtIsNaN(num_elems))) {
      maxval = num_elems;
    }

    sigma_b_squared[k] = num_elems;
  }

  if (b_isfinite(maxval)) {
    num_elems = 0.0;
    num_maxval = 0.0;
    for (k = 0; k < 256; k++) {
      num_elems += (double)((1 + k) * (sigma_b_squared[k] == maxval));
      num_maxval += (double)(sigma_b_squared[k] == maxval);
    }

    num_elems /= num_maxval;
    num_elems = (num_elems - 1.0) / 255.0;
  } else {
    num_elems = 0.0;
  }

  memset(&idx[0], 0, 2200U * sizeof(short));
  for (k = 0; k < 2; k++) {
    i1 = (short)(364 * k + 735);
    i = i1;
    for (i0 = 0; i0 <= i; i0++) {
      tmp_data[i0] = (short)i0;
    }

    i = 364 * k + 735;
    for (i0 = 0; i0 <= i; i0++) {
      b_tmp_data[i0] = (short)(2 + i0);
    }

    i = i1 + 1;
    for (i0 = 0; i0 < i; i0++) {
      idx[tmp_data[i0] + 1100 * k] = b_tmp_data[i0];
    }
  }

  memset(&uv0[0], 255, 809600U * sizeof(unsigned char));
  padarray(uv0, I1);
  num_elems *= 255.0;
  for (i0 = 0; i0 < 809600; i0++) {
    b_im[i0] = (im[i0] > num_elems);
  }

  padarray(b_im, uv1);
  for (i0 = 0; i0 < 813276; i0++) {
    uv2[i0] = (unsigned char)(255U - uv1[i0]);
    I1[i0] = (unsigned char)(255U - I1[i0]);
  }

  imreconstruct(I1, uv2);
  for (i0 = 0; i0 < 813276; i0++) {
    I1[i0] = (unsigned char)(255U - I1[i0]);
  }

  for (i0 = 0; i0 < 1100; i0++) {
    b_idx[i0] = (idx[i0] != 0);
  }

  num_elems = sum(b_idx);
  for (i0 = 0; i0 < 1100; i0++) {
    b_idx[i0] = (idx[1100 + i0] != 0);
  }

  num_maxval = sum(b_idx);
  for (i = 0; i < (int)num_elems; i++) {
    for (k = 0; k < (int)num_maxval; k++) {
      bw[i + 736 * k] = (I1[(idx[i] + 738 * (idx[1100 + k] - 1)) - 1] != 0);
    }
  }
  //------------ End of BW Conversion -----------------

  // Allocate memory for centers and radii vectors
  emxInit_real_T(&centers, 2);
  emxInit_real_T(&radii, 2);

  //  Analyze image to find center point and radius
  //  Find circle fit through CHT
  imfindcircles(bw, radiusRangeGuess, sensVal, centers, radii);

  //  Check for valid find
  if ((centers->size[0] == 0) || (centers->size[1] == 0)) {
    // If no objects throw error
    throw std::domain_error("No objects found in image");
    //centerPt_size[0] = 1;
    //centerPt_size[1] = 1;
    //centerPt_data[0] = rtNaN;
    //*radius = rtNaN;
    //*numCirc = rtNaN;
  } else {
    //  Return found information
    b_centers[0] = centers->data[0];
    b_centers[1] = centers->data[1];
    centerPt_size[0] = 1;
    centerPt_size[1] = 2;
    for (i0 = 0; i0 < 2; i0++) {
      centerPt_data[i0] = b_centers[i0];
    }

    *radius = radii->data[0];
    if ((radii->size[0] == 0) || (radii->size[1] == 0)) {
      i = 0;
    } else {
      k = radii->size[0];
      i = radii->size[1];
      if (k >= i) {
        i = k;
      }
    }

    *numCirc = i;
  }

  // Free the memory
  emxFree_real_T(&radii);
  emxFree_real_T(&centers);
}

//
// File trailer for analyzeImage.cpp
//
// [EOF]
//
