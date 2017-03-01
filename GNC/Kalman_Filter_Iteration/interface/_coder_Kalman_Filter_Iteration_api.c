/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_Kalman_Filter_Iteration_api.c
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 28-Feb-2017 11:46:21
 */

/* Include Files */
#include "tmwtypes.h"
#include "_coder_Kalman_Filter_Iteration_api.h"
#include "_coder_Kalman_Filter_Iteration_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131435U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "Kalman_Filter_Iteration",           /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[6];
static const mxArray *b_emlrt_marshallOut(const real_T u[36]);
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *phi,
  const char_T *identifier))[36];
static const mxArray *c_emlrt_marshallOut(const real_T u[3]);
static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[36];
static const mxArray *d_emlrt_marshallOut(const real_T u[3]);
static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Y, const
  char_T *identifier))[3];
static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *x_hat_0,
  const char_T *identifier))[6];
static const mxArray *emlrt_marshallOut(const real_T u[6]);
static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[3];
static real_T (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *R, const
  char_T *identifier))[9];
static real_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[9];
static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *q_E,
  const char_T *identifier))[4];
static real_T (*j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[4];
static real_T k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *alpha,
  const char_T *identifier);
static real_T l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static real_T (*m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[6];
static real_T (*n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[36];
static real_T (*o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3];
static real_T (*p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[9];
static real_T (*q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[4];
static real_T r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);

/* Function Definitions */

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[6]
 */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[6]
{
  real_T (*y)[6];
  y = m_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
/*
 * Arguments    : const real_T u[36]
 * Return Type  : const mxArray *
 */
  static const mxArray *b_emlrt_marshallOut(const real_T u[36])
{
  const mxArray *y;
  const mxArray *m1;
  static const int32_T iv2[2] = { 0, 0 };

  static const int32_T iv3[2] = { 6, 6 };

  y = NULL;
  m1 = emlrtCreateNumericArray(2, iv2, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m1, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m1, *(int32_T (*)[2])&iv3[0], 2);
  emlrtAssign(&y, m1);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *phi
 *                const char_T *identifier
 * Return Type  : real_T (*)[36]
 */
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *phi,
  const char_T *identifier))[36]
{
  real_T (*y)[36];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(phi), &thisId);
  emlrtDestroyArray(&phi);
  return y;
}
/*
 * Arguments    : const real_T u[3]
 * Return Type  : const mxArray *
 */
  static const mxArray *c_emlrt_marshallOut(const real_T u[3])
{
  const mxArray *y;
  const mxArray *m2;
  static const int32_T iv4[1] = { 0 };

  static const int32_T iv5[1] = { 3 };

  y = NULL;
  m2 = emlrtCreateNumericArray(1, iv4, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m2, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m2, *(int32_T (*)[1])&iv5[0], 1);
  emlrtAssign(&y, m2);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[36]
 */
static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[36]
{
  real_T (*y)[36];
  y = n_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
/*
 * Arguments    : const real_T u[3]
 * Return Type  : const mxArray *
 */
  static const mxArray *d_emlrt_marshallOut(const real_T u[3])
{
  const mxArray *y;
  const mxArray *m3;
  static const int32_T iv6[2] = { 0, 0 };

  static const int32_T iv7[2] = { 1, 3 };

  y = NULL;
  m3 = emlrtCreateNumericArray(2, iv6, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m3, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m3, *(int32_T (*)[2])&iv7[0], 2);
  emlrtAssign(&y, m3);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *Y
 *                const char_T *identifier
 * Return Type  : real_T (*)[3]
 */
static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Y, const
  char_T *identifier))[3]
{
  real_T (*y)[3];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = f_emlrt_marshallIn(sp, emlrtAlias(Y), &thisId);
  emlrtDestroyArray(&Y);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *x_hat_0
 *                const char_T *identifier
 * Return Type  : real_T (*)[6]
 */
  static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *x_hat_0,
  const char_T *identifier))[6]
{
  real_T (*y)[6];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(x_hat_0), &thisId);
  emlrtDestroyArray(&x_hat_0);
  return y;
}

/*
 * Arguments    : const real_T u[6]
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const real_T u[6])
{
  const mxArray *y;
  const mxArray *m0;
  static const int32_T iv0[1] = { 0 };

  static const int32_T iv1[1] = { 6 };

  y = NULL;
  m0 = emlrtCreateNumericArray(1, iv0, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m0, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m0, *(int32_T (*)[1])&iv1[0], 1);
  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[3]
 */
static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[3]
{
  real_T (*y)[3];
  y = o_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *R
 *                const char_T *identifier
 * Return Type  : real_T (*)[9]
 */
  static real_T (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *R,
  const char_T *identifier))[9]
{
  real_T (*y)[9];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = h_emlrt_marshallIn(sp, emlrtAlias(R), &thisId);
  emlrtDestroyArray(&R);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[9]
 */
static real_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[9]
{
  real_T (*y)[9];
  y = p_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *q_E
 *                const char_T *identifier
 * Return Type  : real_T (*)[4]
 */
  static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *q_E,
  const char_T *identifier))[4]
{
  real_T (*y)[4];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = j_emlrt_marshallIn(sp, emlrtAlias(q_E), &thisId);
  emlrtDestroyArray(&q_E);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[4]
 */
static real_T (*j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[4]
{
  real_T (*y)[4];
  y = q_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *alpha
 *                const char_T *identifier
 * Return Type  : real_T
 */
  static real_T k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *alpha,
  const char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = l_emlrt_marshallIn(sp, emlrtAlias(alpha), &thisId);
  emlrtDestroyArray(&alpha);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T
 */
static real_T l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = r_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[6]
 */
static real_T (*m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[6]
{
  real_T (*ret)[6];
  static const int32_T dims[1] = { 6 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims);
  ret = (real_T (*)[6])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[36]
 */
  static real_T (*n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[36]
{
  real_T (*ret)[36];
  static const int32_T dims[2] = { 6, 6 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims);
  ret = (real_T (*)[36])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[3]
 */
static real_T (*o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3]
{
  real_T (*ret)[3];
  static const int32_T dims[1] = { 3 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims);
  ret = (real_T (*)[3])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[9]
 */
  static real_T (*p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[9]
{
  real_T (*ret)[9];
  static const int32_T dims[2] = { 3, 3 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims);
  ret = (real_T (*)[9])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[4]
 */
static real_T (*q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[4]
{
  real_T (*ret)[4];
  static const int32_T dims[1] = { 4 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims);
  ret = (real_T (*)[4])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
  static real_T r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, &dims);
  ret = *(real_T *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const mxArray *prhs[6]
 *                const mxArray *plhs[4]
 * Return Type  : void
 */
void Kalman_Filter_Iteration_api(const mxArray *prhs[6], const mxArray *plhs[4])
{
  real_T (*X_est)[6];
  real_T (*x_hat)[6];
  real_T (*P)[36];
  real_T (*y)[3];
  real_T (*x_hat_0)[6];
  real_T (*phi)[36];
  real_T (*P_0)[36];
  real_T (*Y)[3];
  real_T (*X_ref)[6];
  real_T (*R)[9];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  X_est = (real_T (*)[6])mxMalloc(sizeof(real_T [6]));
  x_hat = (real_T (*)[6])mxMalloc(sizeof(real_T [6]));
  P = (real_T (*)[36])mxMalloc(sizeof(real_T [36]));
  y = (real_T (*)[3])mxMalloc(sizeof(real_T [3]));
  prhs[0] = emlrtProtectR2012b(prhs[0], 0, false, -1);
  prhs[1] = emlrtProtectR2012b(prhs[1], 1, false, -1);
  prhs[2] = emlrtProtectR2012b(prhs[2], 2, false, -1);
  prhs[3] = emlrtProtectR2012b(prhs[3], 3, false, -1);
  prhs[4] = emlrtProtectR2012b(prhs[4], 4, false, -1);
  prhs[5] = emlrtProtectR2012b(prhs[5], 5, false, -1);

  /* Marshall function inputs */
  x_hat_0 = emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "x_hat_0");
  phi = c_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "phi");
  P_0 = c_emlrt_marshallIn(&st, emlrtAlias(prhs[2]), "P_0");
  Y = e_emlrt_marshallIn(&st, emlrtAlias(prhs[3]), "Y");
  X_ref = emlrt_marshallIn(&st, emlrtAlias(prhs[4]), "X_ref");
  R = g_emlrt_marshallIn(&st, emlrtAlias(prhs[5]), "R");

  /* Invoke the target function */
  Kalman_Filter_Iteration(*x_hat_0, *phi, *P_0, *Y, *X_ref, *R, *X_est, *x_hat, *
    P, *y);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(*X_est);
  plhs[1] = emlrt_marshallOut(*x_hat);
  plhs[2] = b_emlrt_marshallOut(*P);
  plhs[3] = c_emlrt_marshallOut(*y);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void Kalman_Filter_Iteration_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  Kalman_Filter_Iteration_xil_terminate();
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void Kalman_Filter_Iteration_initialize(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void Kalman_Filter_Iteration_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * Arguments    : const mxArray *prhs[7]
 *                const mxArray *plhs[2]
 * Return Type  : void
 */
void Position_From_Angles_Slew_api(const mxArray *prhs[7], const mxArray *plhs[2])
{
  real_T (*r_E_SC1)[3];
  real_T (*r_E_SC2)[3];
  real_T (*r_E_M)[3];
  real_T (*q_E)[4];
  real_T (*q_M)[4];
  real_T alpha;
  real_T beta;
  real_T (*vel)[3];
  real_T time;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  r_E_SC1 = (real_T (*)[3])mxMalloc(sizeof(real_T [3]));
  r_E_SC2 = (real_T (*)[3])mxMalloc(sizeof(real_T [3]));
  prhs[0] = emlrtProtectR2012b(prhs[0], 0, false, -1);
  prhs[1] = emlrtProtectR2012b(prhs[1], 1, false, -1);
  prhs[2] = emlrtProtectR2012b(prhs[2], 2, false, -1);
  prhs[5] = emlrtProtectR2012b(prhs[5], 5, false, -1);

  /* Marshall function inputs */
  r_E_M = e_emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "r_E_M");
  q_E = i_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "q_E");
  q_M = i_emlrt_marshallIn(&st, emlrtAlias(prhs[2]), "q_M");
  alpha = k_emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "alpha");
  beta = k_emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "beta");
  vel = e_emlrt_marshallIn(&st, emlrtAlias(prhs[5]), "vel");
  time = k_emlrt_marshallIn(&st, emlrtAliasP(prhs[6]), "time");

  /* Invoke the target function */
  Position_From_Angles_Slew(*r_E_M, *q_E, *q_M, alpha, beta, *vel, time,
    *r_E_SC1, *r_E_SC2);

  /* Marshall function outputs */
  plhs[0] = c_emlrt_marshallOut(*r_E_SC1);
  plhs[1] = c_emlrt_marshallOut(*r_E_SC2);
}

/*
 * Arguments    : const mxArray *prhs[4]
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void Position_From_Earth_Range_api(const mxArray *prhs[4], const mxArray *plhs[1])
{
  real_T (*r_E_SC)[3];
  real_T (*q_E)[4];
  real_T alpha;
  real_T beta;
  real_T theta;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  r_E_SC = (real_T (*)[3])mxMalloc(sizeof(real_T [3]));
  prhs[0] = emlrtProtectR2012b(prhs[0], 0, false, -1);

  /* Marshall function inputs */
  q_E = i_emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "q_E");
  alpha = k_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "alpha");
  beta = k_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "beta");
  theta = k_emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "theta");

  /* Invoke the target function */
  Position_From_Earth_Range(*q_E, alpha, beta, theta, *r_E_SC);

  /* Marshall function outputs */
  plhs[0] = d_emlrt_marshallOut(*r_E_SC);
}

/*
 * Arguments    : const mxArray *prhs[5]
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void Position_From_Moon_Range_api(const mxArray *prhs[5], const mxArray *plhs[1])
{
  real_T (*r_E_SC)[3];
  real_T (*r_E_M)[3];
  real_T (*q_M)[4];
  real_T alpha;
  real_T beta;
  real_T theta;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  r_E_SC = (real_T (*)[3])mxMalloc(sizeof(real_T [3]));
  prhs[0] = emlrtProtectR2012b(prhs[0], 0, false, -1);
  prhs[1] = emlrtProtectR2012b(prhs[1], 1, false, -1);

  /* Marshall function inputs */
  r_E_M = e_emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "r_E_M");
  q_M = i_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "q_M");
  alpha = k_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "alpha");
  beta = k_emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "beta");
  theta = k_emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "theta");

  /* Invoke the target function */
  Position_From_Moon_Range(*r_E_M, *q_M, alpha, beta, theta, *r_E_SC);

  /* Marshall function outputs */
  plhs[0] = c_emlrt_marshallOut(*r_E_SC);
}

/*
 * Arguments    : const mxArray *prhs[1]
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void Quaternion_To_Attitude_api(const mxArray *prhs[1], const mxArray *plhs[1])
{
  real_T (*r_SC_body)[3];
  real_T (*q)[4];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  r_SC_body = (real_T (*)[3])mxMalloc(sizeof(real_T [3]));
  prhs[0] = emlrtProtectR2012b(prhs[0], 0, false, -1);

  /* Marshall function inputs */
  q = i_emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "q");

  /* Invoke the target function */
  Quaternion_To_Attitude(*q, *r_SC_body);

  /* Marshall function outputs */
  plhs[0] = c_emlrt_marshallOut(*r_SC_body);
}

/*
 * File trailer for _coder_Kalman_Filter_Iteration_api.c
 *
 * [EOF]
 */
