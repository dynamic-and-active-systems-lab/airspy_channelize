//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: airspy_channelize_data.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 11-Dec-2023 13:33:03
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
extern rtBoundsCheckInfo emlrtBCI;
extern rtRunTimeErrorInfo d_emlrtRTEI;
extern rtEqualityCheckInfo emlrtECI;
extern rtBoundsCheckInfo b_emlrtBCI;
extern rtBoundsCheckInfo c_emlrtBCI;
extern rtDoubleCheckInfo emlrtDCI;
extern rtBoundsCheckInfo d_emlrtBCI;
extern rtRunTimeErrorInfo e_emlrtRTEI;
extern rtRunTimeErrorInfo f_emlrtRTEI;
extern rtRunTimeErrorInfo g_emlrtRTEI;
extern const char cv[22];
extern const char cv1[30];
extern boolean_T isInitialized_airspy_channelize;

#endif
//
// File trailer for airspy_channelize_data.h
//
// [EOF]
//
