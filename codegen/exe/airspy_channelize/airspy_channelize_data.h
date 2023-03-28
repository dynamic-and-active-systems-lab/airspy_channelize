//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: airspy_channelize_data.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 28-Mar-2023 15:24:09
//

#ifndef AIRSPY_CHANNELIZE_DATA_H
#define AIRSPY_CHANNELIZE_DATA_H

// Include Files
#include "airspy_channelize_types.h"
#include "rtwtypes.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Variable Declarations
extern double freq;
extern boolean_T freq_not_empty;
extern omp_nest_lock_t airspy_channelize_nestLockGlobal;
extern rtRunTimeErrorInfo emlrtRTEI;
extern rtRunTimeErrorInfo b_emlrtRTEI;
extern rtBoundsCheckInfo emlrtBCI;
extern rtRunTimeErrorInfo e_emlrtRTEI;
extern rtEqualityCheckInfo emlrtECI;
extern rtBoundsCheckInfo b_emlrtBCI;
extern rtBoundsCheckInfo c_emlrtBCI;
extern rtDoubleCheckInfo emlrtDCI;
extern rtBoundsCheckInfo d_emlrtBCI;
extern rtRunTimeErrorInfo f_emlrtRTEI;
extern rtRunTimeErrorInfo g_emlrtRTEI;
extern rtRunTimeErrorInfo h_emlrtRTEI;
extern const char cv[22];
extern const char cv1[30];
extern boolean_T isInitialized_airspy_channelize;

#endif
//
// File trailer for airspy_channelize_data.h
//
// [EOF]
//
