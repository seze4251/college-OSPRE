//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: imhist.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 14-Feb-2017 14:49:57
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "imhist.h"

// Function Definitions

//
// Arguments    : const emxArray_uint8_T *varargin_1
//                double yout[256]
// Return Type  : void
//
void b_imhist(const emxArray_uint8_T *varargin_1, double yout[256])
{
  double localBins1[256];
  double localBins2[256];
  double localBins3[256];
  int i;
  memset(&yout[0], 0, sizeof(double) << 8);
  memset(&localBins1[0], 0, sizeof(double) << 8);
  memset(&localBins2[0], 0, sizeof(double) << 8);
  memset(&localBins3[0], 0, sizeof(double) << 8);
  for (i = 0; i + 4 <= varargin_1->size[0]; i += 4) {
    localBins1[varargin_1->data[i]]++;
    localBins2[varargin_1->data[i + 1]]++;
    localBins3[varargin_1->data[i + 2]]++;
    yout[varargin_1->data[i + 3]]++;
  }

  while (i + 1 <= varargin_1->size[0]) {
    yout[varargin_1->data[i]]++;
    i++;
  }

  for (i = 0; i < 256; i++) {
    yout[i] = ((yout[i] + localBins1[i]) + localBins2[i]) + localBins3[i];
  }
}

//
// Arguments    : const unsigned char varargin_1[809600]
//                double yout[256]
// Return Type  : void
//
void imhist(const unsigned char varargin_1[809600], double yout[256])
{
  double localBins1[256];
  double localBins2[256];
  double localBins3[256];
  int i;
  memset(&yout[0], 0, sizeof(double) << 8);
  memset(&localBins1[0], 0, sizeof(double) << 8);
  memset(&localBins2[0], 0, sizeof(double) << 8);
  memset(&localBins3[0], 0, sizeof(double) << 8);
  for (i = 0; i + 4 <= 809600; i += 4) {
    localBins1[varargin_1[i]]++;
    localBins2[varargin_1[i + 1]]++;
    localBins3[varargin_1[i + 2]]++;
    yout[varargin_1[i + 3]]++;
  }

  while (i + 1 <= 809600) {
    yout[varargin_1[i]]++;
    i++;
  }

  for (i = 0; i < 256; i++) {
    yout[i] = ((yout[i] + localBins1[i]) + localBins2[i]) + localBins3[i];
  }
}

//
// File trailer for imhist.cpp
//
// [EOF]
//
