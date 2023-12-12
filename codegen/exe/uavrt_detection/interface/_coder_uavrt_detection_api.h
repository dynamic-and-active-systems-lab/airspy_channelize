//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_uavrt_detection_api.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

#ifndef _CODER_UAVRT_DETECTION_API_H
#define _CODER_UAVRT_DETECTION_API_H

// Include Files
#include "coder_array_mex.h"
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void MEXGlobalSyncInFunction(const emlrtStack *sp);

void MEXGlobalSyncOutFunction(const emlrtStack *sp, boolean_T skipDirtyCheck);

void uavrt_detection(coder::array<char_T, 2U> *configPath,
                     coder::array<char_T, 2U> *thresholdCachePath);

void uavrt_detection_api(const mxArray *const prhs[2]);

void uavrt_detection_atexit();

void uavrt_detection_initialize();

void uavrt_detection_terminate();

void uavrt_detection_xil_shutdown();

void uavrt_detection_xil_terminate();

#endif
//
// File trailer for _coder_uavrt_detection_api.h
//
// [EOF]
//
