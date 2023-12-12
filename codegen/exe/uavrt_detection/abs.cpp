//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: abs.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "abs.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const array<creal_T, 2U> &x
//                array<double, 2U> &y
// Return Type  : void
//
namespace coder {
void b_abs(const array<creal_T, 2U> &x, array<double, 2U> &y)
{
  int nx;
  nx = x.size(0) * x.size(1);
  y.set_size(x.size(0), x.size(1));
  if (nx > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nx; k++) {
    y[k] = rt_hypotd_snf(x[k].re, x[k].im);
  }
}

} // namespace coder

//
// File trailer for abs.cpp
//
// [EOF]
//
