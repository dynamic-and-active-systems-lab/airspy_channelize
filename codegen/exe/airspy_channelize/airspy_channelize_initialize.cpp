//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: airspy_channelize_initialize.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 28-Mar-2023 15:24:09
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
