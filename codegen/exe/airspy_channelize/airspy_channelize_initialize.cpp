//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: airspy_channelize_initialize.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Apr-2023 15:58:05
//

// Include Files
#include "airspy_channelize_initialize.h"
#include "CoderTimeAPI.h"
#include "airspy_channelize_data.h"
#include "rt_nonfinite.h"
#include "timeKeeper.h"
#include "omp.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void airspy_channelize_initialize()
{
  omp_init_nest_lock(&airspy_channelize_nestLockGlobal);
  savedTime_not_empty_init();
  freq_not_empty_init();
  isInitialized_airspy_channelize = true;
}

//
// File trailer for airspy_channelize_initialize.cpp
//
// [EOF]
//
