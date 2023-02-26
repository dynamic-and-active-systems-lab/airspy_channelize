//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_airspy_channelize_api.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 26-Feb-2023 12:32:19
//

#ifndef _CODER_AIRSPY_CHANNELIZE_API_H
#define _CODER_AIRSPY_CHANNELIZE_API_H

// Include Files
#include "coder_array_mex.h"
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void airspy_channelize(coder::array<int32_T, 2U> *channelsUsed);

void airspy_channelize_api(const mxArray *prhs);

void airspy_channelize_atexit();

void airspy_channelize_initialize();

void airspy_channelize_terminate();

void airspy_channelize_xil_shutdown();

void airspy_channelize_xil_terminate();

#endif
//
// File trailer for _coder_airspy_channelize_api.h
//
// [EOF]
//
