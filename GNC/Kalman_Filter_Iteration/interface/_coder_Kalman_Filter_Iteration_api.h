/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_Kalman_Filter_Iteration_api.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 28-Feb-2017 11:46:21
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
extern void Position_From_Angles_Slew(real_T r_E_M[3], real_T q_E[4], real_T
  q_M[4], real_T alpha, real_T beta, real_T vel[3], real_T time, real_T r_E_SC1
  [3], real_T r_E_SC2[3]);
extern void Position_From_Angles_Slew_api(const mxArray *prhs[7], const mxArray *
  plhs[2]);
extern void Position_From_Earth_Range(real_T q_E[4], real_T alpha, real_T beta,
  real_T theta, real_T r_E_SC[3]);
extern void Position_From_Earth_Range_api(const mxArray *prhs[4], const mxArray *
  plhs[1]);
extern void Position_From_Moon_Range(real_T r_E_M[3], real_T q_M[4], real_T
  alpha, real_T beta, real_T theta, real_T r_E_SC[3]);
extern void Position_From_Moon_Range_api(const mxArray *prhs[5], const mxArray
  *plhs[1]);
extern void Quaternion_To_Attitude(real_T q[4], real_T r_SC_body[3]);
extern void Quaternion_To_Attitude_api(const mxArray *prhs[1], const mxArray
  *plhs[1]);

#endif

/*
 * File trailer for _coder_Kalman_Filter_Iteration_api.h
 *
 * [EOF]
 */
