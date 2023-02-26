//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: timeKeeper.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 26-Feb-2023 11:45:56
//

#ifndef TIMEKEEPER_H
#define TIMEKEEPER_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace time {
namespace impl {
void timeKeeper(double newTime_tv_sec, double newTime_tv_nsec);

void timeKeeper(double *outTime_tv_sec, double *outTime_tv_nsec);

} // namespace impl
} // namespace time
} // namespace internal
} // namespace coder
void savedTime_not_empty_init();

#endif
//
// File trailer for timeKeeper.h
//
// [EOF]
//
