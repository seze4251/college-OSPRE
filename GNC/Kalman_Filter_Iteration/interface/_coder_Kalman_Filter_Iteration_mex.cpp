/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_Kalman_Filter_Iteration_mex.cpp
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 21-Feb-2017 11:34:43
 */

/* Include Files */
#include "_coder_Kalman_Filter_Iteration_api.h"
#include "_coder_Kalman_Filter_Iteration_mex.h"

/* Function Declarations */
static void c_Kalman_Filter_Iteration_mexFu(int32_T nlhs, mxArray *plhs[4],
  int32_T nrhs, const mxArray *prhs[6]);

/* Function Definitions */

/*
 * Arguments    : int32_T nlhs
 *                const mxArray *plhs[4]
 *                int32_T nrhs
 *                const mxArray *prhs[6]
 * Return Type  : void
 */
static void c_Kalman_Filter_Iteration_mexFu(int32_T nlhs, mxArray *plhs[4],
  int32_T nrhs, const mxArray *prhs[6])
{
  int32_T n;
  const mxArray *inputs[6];
  const mxArray *outputs[4];
  int32_T b_nlhs;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 6) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 6, 4,
                        23, "Kalman_Filter_Iteration");
  }

  if (nlhs > 4) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 23,
                        "Kalman_Filter_Iteration");
  }

  /* Temporary copy for mex inputs. */
  for (n = 0; n < nrhs; n++) {
    inputs[n] = prhs[n];
  }

  /* Call the function. */
  Kalman_Filter_Iteration_api(inputs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);

  /* Module termination. */
  Kalman_Filter_Iteration_terminate();
}

/*
 * Arguments    : int32_T nlhs
 *                const mxArray * const plhs[]
 *                int32_T nrhs
 *                const mxArray * const prhs[]
 * Return Type  : void
 */
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(Kalman_Filter_Iteration_atexit);

  /* Initialize the memory manager. */
  /* Module initialization. */
  Kalman_Filter_Iteration_initialize();

  /* Dispatch the entry-point. */
  c_Kalman_Filter_Iteration_mexFu(nlhs, plhs, nrhs, prhs);
}

/*
 * Arguments    : void
 * Return Type  : emlrtCTX
 */
emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/*
 * File trailer for _coder_Kalman_Filter_Iteration_mex.cpp
 *
 * [EOF]
 */
