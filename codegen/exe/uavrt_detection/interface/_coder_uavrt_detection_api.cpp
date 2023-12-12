//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_uavrt_detection_api.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "_coder_uavrt_detection_api.h"
#include "_coder_uavrt_detection_mex.h"
#include "coder_array_mex.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal{nullptr};

static coder::array<char_T, 2U> globalThresholdCachePath;

static uint32_T globalThresholdCachePath_guard;

emlrtContext emlrtContextGlobal{
    true,                                                 // bFirstTime
    false,                                                // bInitialized
    131643U,                                              // fVersionInfo
    nullptr,                                              // fErrorFunction
    "uavrt_detection",                                    // fFunctionName
    nullptr,                                              // fRTCallStack
    false,                                                // bDebugMode
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, // fSigWrd
    nullptr                                               // fSigMem
};

// Function Declarations
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               coder::array<char_T, 2U> &ret);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *b_nullptr,
                             const char_T *identifier,
                             coder::array<char_T, 2U> &y);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId,
                             coder::array<char_T, 2U> &y);

static const mxArray *emlrt_marshallOut(const emlrtStack *sp,
                                        const coder::array<char_T, 2U> &u);

static void uavrt_detection_once();

// Function Definitions
//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
//                coder::array<char_T, 2U> &ret
// Return Type  : void
//
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               coder::array<char_T, 2U> &ret)
{
  static const int32_T dims[2]{1, -1};
  int32_T iv[2];
  boolean_T bv[2]{false, true};
  emlrtCheckVsBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "char", false, 2U,
                            (const void *)&dims[0], &bv[0], &iv[0]);
  ret.set_size(iv[0], iv[1]);
  emlrtImportArrayR2015b((emlrtConstCTX)sp, src, &ret[0], 1, false);
  emlrtDestroyArray(&src);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *b_nullptr
//                const char_T *identifier
//                coder::array<char_T, 2U> &y
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *b_nullptr,
                             const char_T *identifier,
                             coder::array<char_T, 2U> &y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  emlrt_marshallIn(sp, emlrtAlias(b_nullptr), &thisId, y);
  emlrtDestroyArray(&b_nullptr);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                coder::array<char_T, 2U> &y
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId,
                             coder::array<char_T, 2U> &y)
{
  b_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

//
// Arguments    : const emlrtStack *sp
//                const coder::array<char_T, 2U> &u
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const emlrtStack *sp,
                                        const coder::array<char_T, 2U> &u)
{
  const mxArray *m;
  const mxArray *y;
  int32_T iv[2];
  y = nullptr;
  iv[0] = 1;
  iv[1] = u.size(1);
  m = emlrtCreateCharArray(2, &iv[0]);
  emlrtInitCharArrayR2013a((emlrtConstCTX)sp, u.size(1), m, &u[0]);
  emlrtAssign(&y, m);
  return y;
}

//
// Arguments    : void
// Return Type  : void
//
static void uavrt_detection_once()
{
  globalThresholdCachePath_guard = 0U;
}

//
// Arguments    : const emlrtStack *sp
// Return Type  : void
//
void MEXGlobalSyncInFunction(const emlrtStack *sp)
{
  const mxArray *tmp;
  // Marshall in global variables
  tmp = emlrtGetGlobalVariable("globalThresholdCachePath");
  if (tmp != nullptr) {
    emlrt_marshallIn(sp, tmp, "globalThresholdCachePath",
                     globalThresholdCachePath);
    globalThresholdCachePath_guard = 1U;
  }
}

//
// Arguments    : const emlrtStack *sp
//                boolean_T skipDirtyCheck
// Return Type  : void
//
void MEXGlobalSyncOutFunction(const emlrtStack *sp, boolean_T skipDirtyCheck)
{
  // Marshall out global variables
  if (skipDirtyCheck || (globalThresholdCachePath_guard != 0U)) {
    emlrtPutGlobalVariable("globalThresholdCachePath",
                           emlrt_marshallOut(sp, globalThresholdCachePath));
  }
}

//
// Arguments    : const mxArray * const prhs[2]
// Return Type  : void
//
void uavrt_detection_api(const mxArray *const prhs[2])
{
  coder::array<char_T, 2U> configPath;
  coder::array<char_T, 2U> thresholdCachePath;
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  // Marshall function inputs
  emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "configPath", configPath);
  emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "thresholdCachePath",
                   thresholdCachePath);
  // Marshall in global variables
  MEXGlobalSyncInFunction(&st);
  // Invoke the target function
  uavrt_detection(configPath, thresholdCachePath);
  // Marshall out global variables
  MEXGlobalSyncOutFunction(&st, true);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

//
// Arguments    : void
// Return Type  : void
//
void uavrt_detection_atexit()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  uavrt_detection_xil_terminate();
  uavrt_detection_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void uavrt_detection_initialize()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, nullptr);
  emlrtEnterRtStackR2012b(&st);
  if (emlrtFirstTimeR2012b(emlrtRootTLSGlobal)) {
    uavrt_detection_once();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void uavrt_detection_terminate()
{
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

//
// File trailer for _coder_uavrt_detection_api.cpp
//
// [EOF]
//
