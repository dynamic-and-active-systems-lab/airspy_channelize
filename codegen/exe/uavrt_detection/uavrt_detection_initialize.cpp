//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection_initialize.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "uavrt_detection_initialize.h"
#include "CoderTimeAPI.h"
#include "eml_rand_mt19937ar_stateful.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include "timeKeeper.h"
#include "uavrt_detection_data.h"
#include "wfmcsvwrite.h"
#include "coder_array.h"
#include "omp.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void uavrt_detection_initialize()
{
  omp_init_nest_lock(&uavrt_detection_nestLockGlobal);
  globalThresholdCachePath.set_size(1, 1);
  globalThresholdCachePath[0] = 'X';
  filedata_init();
  eml_rand_mt19937ar_stateful_init();
  CoderTimeAPI::callCoderClockGettime_init();
  timeKeeper_init();
  wfmcsvwrite_init();
  isInitialized_uavrt_detection = true;
}

//
// File trailer for uavrt_detection_initialize.cpp
//
// [EOF]
//
