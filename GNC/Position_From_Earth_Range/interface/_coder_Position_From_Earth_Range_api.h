/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_Position_From_Earth_Range_api.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 21-Feb-2017 11:44:14
 */

#ifndef _CODER_POSITION_FROM_EARTH_RANGE_API_H
#define _CODER_POSITION_FROM_EARTH_RANGE_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_Position_From_Earth_Range_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void Position_From_Earth_Range(real_T q_E[4], real_T alpha, real_T beta,
  real_T theta, real_T r_E_SC[3]);
extern void Position_From_Earth_Range_api(const mxArray *prhs[4], const mxArray *
  plhs[1]);
extern void Position_From_Earth_Range_atexit(void);
extern void Position_From_Earth_Range_initialize(void);
extern void Position_From_Earth_Range_terminate(void);
extern void Position_From_Earth_Range_xil_terminate(void);

#endif

/*
 * File trailer for _coder_Position_From_Earth_Range_api.h
 *
 * [EOF]
 */
