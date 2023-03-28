//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: airspy_channelize_terminate.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 28-Mar-2023 15:24:09
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
