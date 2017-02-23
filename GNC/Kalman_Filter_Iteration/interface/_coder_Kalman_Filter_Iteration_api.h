/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_Kalman_Filter_Iteration_api.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 21-Feb-2017 11:34:43
 */

#ifndef _CODER_KALMAN_FILTER_ITERATION_API_H
#define _CODER_KALMAN_FILTER_ITERATION_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_Kalman_Filter_Iteration_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void Kalman_Filter_Iteration(real_T x_hat_0[6], real_T phi[36], real_T
  P_0[36], real_T Y[3], real_T X_ref[6], real_T R[9], real_T X_est[6], real_T
  x_hat[6], real_T P[36], real_T y[3]);
extern void Kalman_Filter_Iteration_api(const mxArray *prhs[6], const mxArray
  *plhs[4]);
extern void Kalman_Filter_Iteration_atexit(void);
extern void Kalman_Filter_Iteration_initialize(void);
extern void Kalman_Filter_Iteration_terminate(void);
extern void Kalman_Filter_Iteration_xil_terminate(void);

#endif

/*
 * File trailer for _coder_Kalman_Filter_Iteration_api.h
 *
 * [EOF]
 */
