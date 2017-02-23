/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_Position_From_Angles_Slew_api.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 21-Feb-2017 11:42:16
 */

#ifndef _CODER_POSITION_FROM_ANGLES_SLEW_API_H
#define _CODER_POSITION_FROM_ANGLES_SLEW_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_Position_From_Angles_Slew_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void Position_From_Angles_Slew(real_T r_E_M[3], real_T q_E[4], real_T
  q_M[4], real_T alpha, real_T beta, real_T vel[3], real_T time, real_T r_E_SC1
  [3], real_T r_E_SC2[3]);
extern void Position_From_Angles_Slew_api(const mxArray *prhs[7], const mxArray *
  plhs[2]);
extern void Position_From_Angles_Slew_atexit(void);
extern void Position_From_Angles_Slew_initialize(void);
extern void Position_From_Angles_Slew_terminate(void);
extern void Position_From_Angles_Slew_xil_terminate(void);

#endif

/*
 * File trailer for _coder_Position_From_Angles_Slew_api.h
 *
 * [EOF]
 */
