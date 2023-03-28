//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: plus.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 28-Mar-2023 15:24:09
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
  double shi_tmp;
  double slo;
  shi_tmp = a.re + b;
  bb = shi_tmp - a.re;
  slo = (a.re - (shi_tmp - bb)) + (b - bb);
  if (std::isnan(slo)) {
    slo = 0.0;
  }
  bb = a.im - a.im;
  b_slo = (a.im - (a.im - bb)) + (0.0 - bb);
  if (std::isnan(b_slo)) {
    b_slo = 0.0;
  }
  ahi = shi_tmp;
  if (a.im != 0.0) {
    slo += a.im;
    ahi = shi_tmp + slo;
    slo -= ahi - shi_tmp;
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
