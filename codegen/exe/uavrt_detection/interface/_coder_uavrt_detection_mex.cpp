//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_uavrt_detection_mex.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "_coder_uavrt_detection_mex.h"
#include "_coder_uavrt_detection_api.h"

// Function Definitions
//
// Arguments    : int32_T nlhs
//                mxArray *plhs[]
//                int32_T nrhs
//                const mxArray *prhs[]
// Return Type  : void
//
void mexFunction(int32_T nlhs, mxArray *[], int32_T nrhs, const mxArray *prhs[])
{
  mexAtExit(&uavrt_detection_atexit);
  // Module initialization.
  uavrt_detection_initialize();
  // Dispatch the entry-point.
  uavrt_detection_mexFunction(nlhs, nrhs, prhs);
  // Module termination.
  uavrt_detection_terminate();
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
// Arguments    : int32_T nlhs
//                int32_T nrhs
//                const mxArray *prhs[2]
// Return Type  : void
//
void uavrt_detection_mexFunction(int32_T nlhs, int32_T nrhs,
                                 const mxArray *prhs[2])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  st.tls = emlrtRootTLSGlobal;
  // Check for proper number of arguments.
  if (nrhs != 2) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 2, 4,
                        15, "uavrt_detection");
  }
  if (nlhs > 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 15,
                        "uavrt_detection");
  }
  // Call the function.
  uavrt_detection_api(prhs);
}

//
// File trailer for _coder_uavrt_detection_mex.cpp
//
// [EOF]
//
