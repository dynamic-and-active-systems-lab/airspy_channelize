//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: _coder_airspy_channelize_mex.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 28-Mar-2023 15:24:09
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
                           nullptr, "UTF-8", true);
  return emlrtRootTLSGlobal;
}

//
// File trailer for _coder_airspy_channelize_mex.cpp
//
// [EOF]
//
