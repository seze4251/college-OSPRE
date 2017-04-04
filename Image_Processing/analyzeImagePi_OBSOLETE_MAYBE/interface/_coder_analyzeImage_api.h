/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_analyzeImage_api.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 02-Apr-2017 22:04:47
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

/* Type Definitions */
#ifndef struct_emxArray_uint8_T
#define struct_emxArray_uint8_T

struct emxArray_uint8_T
{
  uint8_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_uint8_T*/

#ifndef typedef_emxArray_uint8_T
#define typedef_emxArray_uint8_T

typedef struct emxArray_uint8_T emxArray_uint8_T;

#endif                                 /*typedef_emxArray_uint8_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void analyzeImage(emxArray_uint8_T *imIn, real_T radiusRangeGuess[2],
  real_T sensVal, real_T pxDeg[2], real_T imgWidth, real_T imgHeight, real_T
  centerPt_data[], int32_T centerPt_size[2], real_T *radius, real_T *numCirc,
  real_T *alpha, real_T *beta, real_T *theta);
extern void analyzeImage_api(const mxArray * const prhs[6], const mxArray *plhs
  [6]);
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
