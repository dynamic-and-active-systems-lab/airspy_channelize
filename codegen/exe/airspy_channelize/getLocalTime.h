//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: getLocalTime.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 26-Feb-2023 09:39:03
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
namespace time {
void getLocalTime(double *t_tm_nsec, double *t_tm_sec, double *t_tm_min,
                  double *t_tm_hour, double *t_tm_mday, double *t_tm_mon,
                  double *t_tm_year, boolean_T *t_tm_isdst);

}
} // namespace internal
} // namespace coder

#endif
//
// File trailer for getLocalTime.h
//
// [EOF]
//
