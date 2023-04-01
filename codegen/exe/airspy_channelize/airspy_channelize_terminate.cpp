//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: airspy_channelize_terminate.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Apr-2023 16:45:43
//

// Include Files
#include "airspy_channelize_terminate.h"
#include "airspy_channelize_data.h"
#include "rt_nonfinite.h"
#include "omp.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void airspy_channelize_terminate()
{
  omp_destroy_nest_lock(&airspy_channelize_nestLockGlobal);
  isInitialized_airspy_channelize = false;
}

//
// File trailer for airspy_channelize_terminate.cpp
//
// [EOF]
//
