//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_airspy_channelize_api.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Apr-2023 15:58:05
//

// Include Files
#include "_coder_airspy_channelize_api.h"
#include "_coder_airspy_channelize_mex.h"
#include "coder_array_mex.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal{nullptr};

emlrtContext emlrtContextGlobal{
    true,                                                 // bFirstTime
    false,                                                // bInitialized
    131626U,                                              // fVersionInfo
    nullptr,                                              // fErrorFunction
    "airspy_channelize",                                  // fFunctionName
    nullptr,                                              // fRTCallStack
    false,                                                // bDebugMode
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, // fSigWrd
    nullptr                                               // fSigMem
};

// Function Declarations
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               coder::array<int32_T, 2U> &ret);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *channelsUsed,
                             const char_T *identifier,
                             coder::array<int32_T, 2U> &y);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId,
                             coder::array<int32_T, 2U> &y);

// Function Definitions
//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
//                coder::array<int32_T, 2U> &ret
// Return Type  : void
//
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               coder::array<int32_T, 2U> &ret)
{
  static const int32_T dims[2]{1, -1};
  int32_T iv[2];
  const boolean_T bv[2]{false, true};
  emlrtCheckVsBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"int32",
                            false, 2U, (void *)&dims[0], &bv[0], &iv[0]);
  ret.prealloc(iv[0] * iv[1]);
  ret.set_size(iv[0], iv[1]);
  ret.set(static_cast<int32_T *>(emlrtMxGetData(src)), ret.size(0),
          ret.size(1));
  emlrtDestroyArray(&src);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *channelsUsed
//                const char_T *identifier
//                coder::array<int32_T, 2U> &y
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *channelsUsed,
                             const char_T *identifier,
                             coder::array<int32_T, 2U> &y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  emlrt_marshallIn(sp, emlrtAlias(channelsUsed), &thisId, y);
  emlrtDestroyArray(&channelsUsed);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                coder::array<int32_T, 2U> &y
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId,
                             coder::array<int32_T, 2U> &y)
{
  b_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

//
// Arguments    : const mxArray *prhs
// Return Type  : void
//
void airspy_channelize_api(const mxArray *prhs)
{
  coder::array<int32_T, 2U> channelsUsed;
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  // Marshall function inputs
  channelsUsed.no_free();
  emlrt_marshallIn(&st, emlrtAlias(prhs), "channelsUsed", channelsUsed);
  // Invoke the target function
  airspy_channelize(channelsUsed);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

//
// Arguments    : void
// Return Type  : void
//
void airspy_channelize_atexit()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  airspy_channelize_xil_terminate();
  airspy_channelize_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void airspy_channelize_initialize()
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
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void airspy_channelize_terminate()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

//
// File trailer for _coder_airspy_channelize_api.cpp
//
// [EOF]
//
