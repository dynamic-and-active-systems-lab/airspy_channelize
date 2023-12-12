//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection_terminate.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "uavrt_detection_terminate.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "omp.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void uavrt_detection_terminate()
{
  omp_destroy_nest_lock(&uavrt_detection_nestLockGlobal);
  isInitialized_uavrt_detection = false;
}

//
// File trailer for uavrt_detection_terminate.cpp
//
// [EOF]
//
