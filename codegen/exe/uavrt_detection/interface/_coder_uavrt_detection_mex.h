//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_uavrt_detection_mex.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

#ifndef _CODER_UAVRT_DETECTION_MEX_H
#define _CODER_UAVRT_DETECTION_MEX_H

// Include Files
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"

// Function Declarations
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[],
                                     int32_T nrhs, const mxArray *prhs[]);

emlrtCTX mexFunctionCreateRootTLS();

void uavrt_detection_mexFunction(int32_T nlhs, int32_T nrhs,
                                 const mxArray *prhs[2]);

#endif
//
// File trailer for _coder_uavrt_detection_mex.h
//
// [EOF]
//
