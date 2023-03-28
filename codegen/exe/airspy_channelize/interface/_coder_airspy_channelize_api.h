//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: _coder_airspy_channelize_api.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 28-Mar-2023 15:24:09
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
