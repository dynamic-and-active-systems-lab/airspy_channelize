//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: timeKeeper.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 28-Mar-2023 15:24:09
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
namespace b_time {
namespace impl {
double timeKeeper(double &outTime_tv_nsec);

void timeKeeper(double newTime_tv_sec, double newTime_tv_nsec);

} // namespace impl
} // namespace b_time
} // namespace internal
} // namespace coder
void savedTime_not_empty_init();

#endif
//
// File trailer for timeKeeper.h
//
// [EOF]
//
