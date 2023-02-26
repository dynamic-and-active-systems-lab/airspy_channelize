//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: plus.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 26-Feb-2023 11:45:56
//

// Include Files
#include "plus.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const creal_T a
//                double b
// Return Type  : creal_T
//
namespace coder {
namespace matlab {
namespace internal {
namespace coder {
namespace doubledouble {
creal_T plus(const creal_T a, double b)
{
  creal_T c;
  double ahi;
  double b_slo;
  double bb;
  double shi;
  double slo;
  int trueCount;
  shi = a.re + b;
  bb = shi - a.re;
  slo = (a.re - (shi - bb)) + (b - bb);
  trueCount = 0;
  if (std::isnan(slo)) {
    trueCount = 1;
  }
  for (int i{0}; i < trueCount; i++) {
    slo = 0.0;
  }
  bb = a.im - a.im;
  b_slo = (a.im - (a.im - bb)) + (0.0 - bb);
  trueCount = 0;
  if (std::isnan(b_slo)) {
    trueCount = 1;
  }
  for (int i{0}; i < trueCount; i++) {
    b_slo = 0.0;
  }
  ahi = shi;
  if (a.im != 0.0) {
    slo += a.im;
    ahi = shi + slo;
    slo -= ahi - shi;
  }
  if (std::isnan(slo)) {
    slo = 0.0;
  }
  bb = ahi;
  if (b_slo != 0.0) {
    slo += b_slo;
    bb = ahi + slo;
    slo -= bb - ahi;
  }
  if (std::isnan(slo)) {
    slo = 0.0;
  }
  c.re = bb;
  c.im = slo;
  return c;
}

} // namespace doubledouble
} // namespace coder
} // namespace internal
} // namespace matlab
} // namespace coder

//
// File trailer for plus.cpp
//
// [EOF]
//
