/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_Quaternion_To_Attitude_api.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 21-Feb-2017 11:45:49
 */

#ifndef _CODER_QUATERNION_TO_ATTITUDE_API_H
#define _CODER_QUATERNION_TO_ATTITUDE_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_Quaternion_To_Attitude_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void Quaternion_To_Attitude(real_T q[4], real_T r_SC_body[3]);
extern void Quaternion_To_Attitude_api(const mxArray *prhs[1], const mxArray
  *plhs[1]);
extern void Quaternion_To_Attitude_atexit(void);
extern void Quaternion_To_Attitude_initialize(void);
extern void Quaternion_To_Attitude_terminate(void);
extern void Quaternion_To_Attitude_xil_terminate(void);

#endif

/*
 * File trailer for _coder_Quaternion_To_Attitude_api.h
 *
 * [EOF]
 */
