/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_analyzeImage_api.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 02-Apr-2017 22:04:47
 */

/* Include Files */
#include "tmwtypes.h"
#include "_coder_analyzeImage_api.h"
#include "_coder_analyzeImage_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131450U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "analyzeImage",                      /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_uint8_T *y);
static const mxArray *b_emlrt_marshallOut(const real_T u);
static real_T (*c_emlrt_marshallIn(const mxArray *radiusRangeGuess, const char_T
  *identifier))[2];
static real_T (*d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId))[2];
static real_T e_emlrt_marshallIn(const mxArray *sensVal, const char_T
  *identifier);
static void emlrt_marshallIn(const mxArray *imIn, const char_T *identifier,
  emxArray_uint8_T *y);
static const mxArray *emlrt_marshallOut(const real_T u_data[], const int32_T
  u_size[2]);
static void emxFree_uint8_T(emxArray_uint8_T **pEmxArray);
static void emxInit_uint8_T(emxArray_uint8_T **pEmxArray, int32_T numDimensions,
  boolean_T doPush);
static real_T f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static void g_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_uint8_T *ret);
static real_T (*h_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId))[2];
static real_T i_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId);

/* Function Definitions */

/*
 * Arguments    : const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                emxArray_uint8_T *y
 * Return Type  : void
 */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_uint8_T *y)
{
  g_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const real_T u
 * Return Type  : const mxArray *
 */
static const mxArray *b_emlrt_marshallOut(const real_T u)
{
  const mxArray *y;
  const mxArray *m1;
  y = NULL;
  m1 = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m1);
  return y;
}

/*
 * Arguments    : const mxArray *radiusRangeGuess
 *                const char_T *identifier
 * Return Type  : real_T (*)[2]
 */
static real_T (*c_emlrt_marshallIn(const mxArray *radiusRangeGuess, const char_T
  *identifier))[2]
{
  real_T (*y)[2];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(emlrtAlias(radiusRangeGuess), &thisId);
  emlrtDestroyArray(&radiusRangeGuess);
  return y;
}
/*
 * Arguments    : const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[2]
 */
  static real_T (*d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
  parentId))[2]
{
  real_T (*y)[2];
  y = h_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const mxArray *sensVal
 *                const char_T *identifier
 * Return Type  : real_T
 */
static real_T e_emlrt_marshallIn(const mxArray *sensVal, const char_T
  *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = f_emlrt_marshallIn(emlrtAlias(sensVal), &thisId);
  emlrtDestroyArray(&sensVal);
  return y;
}

/*
 * Arguments    : const mxArray *imIn
 *                const char_T *identifier
 *                emxArray_uint8_T *y
 * Return Type  : void
 */
static void emlrt_marshallIn(const mxArray *imIn, const char_T *identifier,
  emxArray_uint8_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(emlrtAlias(imIn), &thisId, y);
  emlrtDestroyArray(&imIn);
}

/*
 * Arguments    : const real_T u_data[]
 *                const int32_T u_size[2]
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const real_T u_data[], const int32_T
  u_size[2])
{
  const mxArray *y;
  const mxArray *m0;
  static const int32_T iv0[2] = { 0, 0 };

  y = NULL;
  m0 = emlrtCreateNumericArray(2, iv0, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m0, (void *)&u_data[0]);
  emlrtSetDimensions((mxArray *)m0, *(int32_T (*)[2])&u_size[0], 2);
  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : emxArray_uint8_T **pEmxArray
 * Return Type  : void
 */
static void emxFree_uint8_T(emxArray_uint8_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_uint8_T *)NULL) {
    if (((*pEmxArray)->data != (uint8_T *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex((void *)(*pEmxArray)->data);
    }

    emlrtFreeMex((void *)(*pEmxArray)->size);
    emlrtFreeMex((void *)*pEmxArray);
    *pEmxArray = (emxArray_uint8_T *)NULL;
  }
}

/*
 * Arguments    : emxArray_uint8_T **pEmxArray
 *                int32_T numDimensions
 *                boolean_T doPush
 * Return Type  : void
 */
static void emxInit_uint8_T(emxArray_uint8_T **pEmxArray, int32_T numDimensions,
  boolean_T doPush)
{
  emxArray_uint8_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_uint8_T *)emlrtMallocMex(sizeof(emxArray_uint8_T));
  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(emlrtRootTLSGlobal, (void *)pEmxArray,
      (void (*)(void *))emxFree_uint8_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (uint8_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex((uint32_T)(sizeof(int32_T)
    * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T
 */
static real_T f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  real_T y;
  y = i_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                emxArray_uint8_T *ret
 * Return Type  : void
 */
static void g_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_uint8_T *ret)
{
  static const int32_T dims[3] = { 3120, 4160, 3 };

  const boolean_T bv0[3] = { true, true, false };

  int32_T iv1[3];
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "uint8", false, 3U,
    dims, &bv0[0], iv1);
  ret->size[0] = iv1[0];
  ret->size[1] = iv1[1];
  ret->size[2] = iv1[2];
  ret->allocatedSize = ret->size[0] * ret->size[1] * ret->size[2];
  ret->data = (uint8_T *)mxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[2]
 */
static real_T (*h_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId))[2]
{
  real_T (*ret)[2];
  static const int32_T dims[2] = { 1, 2 };

  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 2U,
    dims);
  ret = (real_T (*)[2])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * Arguments    : const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
  static real_T i_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 0U,
    &dims);
  ret = *(real_T *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const mxArray * const prhs[6]
 *                const mxArray *plhs[6]
 * Return Type  : void
 */
void analyzeImage_api(const mxArray * const prhs[6], const mxArray *plhs[6])
{
  real_T (*centerPt_data)[2];
  emxArray_uint8_T *imIn;
  real_T (*radiusRangeGuess)[2];
  real_T sensVal;
  real_T (*pxDeg)[2];
  real_T imgWidth;
  real_T imgHeight;
  int32_T centerPt_size[2];
  real_T radius;
  real_T numCirc;
  real_T alpha;
  real_T beta;
  real_T theta;
  centerPt_data = (real_T (*)[2])mxMalloc(sizeof(real_T [2]));
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_uint8_T(&imIn, 3, true);

  /* Marshall function inputs */
  emlrt_marshallIn(emlrtAlias((const mxArray *)prhs[0]), "imIn", imIn);
  radiusRangeGuess = c_emlrt_marshallIn(emlrtAlias((const mxArray *)prhs[1]),
    "radiusRangeGuess");
  sensVal = e_emlrt_marshallIn(emlrtAliasP((const mxArray *)prhs[2]), "sensVal");
  pxDeg = c_emlrt_marshallIn(emlrtAlias((const mxArray *)prhs[3]), "pxDeg");
  imgWidth = e_emlrt_marshallIn(emlrtAliasP((const mxArray *)prhs[4]),
    "imgWidth");
  imgHeight = e_emlrt_marshallIn(emlrtAliasP((const mxArray *)prhs[5]),
    "imgHeight");

  /* Invoke the target function */
  analyzeImage(imIn, *radiusRangeGuess, sensVal, *pxDeg, imgWidth, imgHeight,
               *centerPt_data, centerPt_size, &radius, &numCirc, &alpha, &beta,
               &theta);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(*centerPt_data, centerPt_size);
  plhs[1] = b_emlrt_marshallOut(radius);
  plhs[2] = b_emlrt_marshallOut(numCirc);
  plhs[3] = b_emlrt_marshallOut(alpha);
  plhs[4] = b_emlrt_marshallOut(beta);
  plhs[5] = b_emlrt_marshallOut(theta);
  imIn->canFreeData = false;
  emxFree_uint8_T(&imIn);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void analyzeImage_atexit(void)
{
  mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  analyzeImage_xil_terminate();
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void analyzeImage_initialize(void)
{
  mexFunctionCreateRootTLS();
  emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, 0);
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void analyzeImage_terminate(void)
{
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_analyzeImage_api.c
 *
 * [EOF]
 */
