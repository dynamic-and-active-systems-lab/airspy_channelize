//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: getLocalTime.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 28-Mar-2023 15:24:09
//

#ifndef GETLOCALTIME_H
#define GETLOCALTIME_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace b_time {
double getLocalTime(double &t_tm_sec, double &t_tm_min, double &t_tm_hour,
                    double &t_tm_mday, double &t_tm_mon, double &t_tm_year,
                    boolean_T &t_tm_isdst);

}
} // namespace internal
} // namespace coder

#endif
//
// File trailer for getLocalTime.h
//
// [EOF]
//
