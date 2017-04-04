/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_analyzeImage_api.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 14-Feb-2017 14:49:57
 */

#ifndef _CODER_ANALYZEIMAGE_API_H
#define _CODER_ANALYZEIMAGE_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_analyzeImage_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void analyzeImage(uint8_T imIn[2428800], real_T radiusRangeGuess[2],
  real_T sensVal, real_T centerPt_data[], int32_T centerPt_size[2], real_T
  *radius, real_T *numCirc);
extern void analyzeImage_api(const mxArray *prhs[3], const mxArray *plhs[3]);
extern void analyzeImage_atexit(void);
extern void analyzeImage_initialize(void);
extern void analyzeImage_terminate(void);
extern void analyzeImage_xil_terminate(void);

#endif

/*
 * File trailer for _coder_analyzeImage_api.h
 *
 * [EOF]
 */
