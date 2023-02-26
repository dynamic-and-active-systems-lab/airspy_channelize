//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_airspy_channelize_mex.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 26-Feb-2023 12:01:14
//

// Include Files
#include "_coder_airspy_channelize_mex.h"
#include "_coder_airspy_channelize_api.h"

// Function Definitions
//
// Arguments    : int32_T nlhs
//                int32_T nrhs
//                const mxArray *prhs[1]
// Return Type  : void
//
void airspy_channelize_mexFunction(int32_T nlhs, int32_T nrhs,
                                   const mxArray *prhs[1])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  st.tls = emlrtRootTLSGlobal;
  // Check for proper number of arguments.
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4,
                        17, "airspy_channelize");
  }
  if (nlhs > 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 17,
                        "airspy_channelize");
  }
  // Call the function.
  airspy_channelize_api(prhs[0]);
}

//
// Arguments    : int32_T nlhs
//                mxArray *plhs[]
//                int32_T nrhs
//                const mxArray *prhs[]
// Return Type  : void
//
void mexFunction(int32_T nlhs, mxArray *[], int32_T nrhs, const mxArray *prhs[])
{
  mexAtExit(&airspy_channelize_atexit);
  // Module initialization.
  airspy_channelize_initialize();
  // Dispatch the entry-point.
  airspy_channelize_mexFunction(nlhs, nrhs, prhs);
  // Module termination.
  airspy_channelize_terminate();
}

//
// Arguments    : void
// Return Type  : emlrtCTX
//
emlrtCTX mexFunctionCreateRootTLS()
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal, nullptr, 1,
                           nullptr, (const char_T *)"windows-1252", true);
  return emlrtRootTLSGlobal;
}

//
// File trailer for _coder_airspy_channelize_mex.cpp
//
// [EOF]
//
