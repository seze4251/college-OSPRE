/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_Earth_SC_Moon_Angle_api.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 09-Mar-2017 10:09:18
 */

#ifndef _CODER_EARTH_SC_MOON_ANGLE_API_H
#define _CODER_EARTH_SC_MOON_ANGLE_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_Earth_SC_Moon_Angle_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern real_T Earth_SC_Moon_Angle(real_T r_E_SC[3], real_T r_E_M[3]);
extern void Earth_SC_Moon_Angle_api(const mxArray *prhs[2], const mxArray *plhs
  [1]);
extern void Earth_SC_Moon_Angle_atexit(void);
extern void Earth_SC_Moon_Angle_initialize(void);
extern void Earth_SC_Moon_Angle_terminate(void);
extern void Earth_SC_Moon_Angle_xil_terminate(void);
extern void Kalman_Filter_Iteration(real_T x_hat[6], real_T phi[36], real_T P[36],
  real_T Y[3], real_T X_ref[6], real_T R[9], real_T X_est[6]);
extern void Kalman_Filter_Iteration_api(const mxArray *prhs[6], const mxArray
  *plhs[3]);
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
extern void State_Error(real_T X_ref[6], real_T X_est[6], real_T posError[3],
  real_T velError[3]);
extern void State_Error_api(const mxArray *prhs[2], const mxArray *plhs[2]);

#endif

/*
 * File trailer for _coder_Earth_SC_Moon_Angle_api.h
 *
 * [EOF]
 */
