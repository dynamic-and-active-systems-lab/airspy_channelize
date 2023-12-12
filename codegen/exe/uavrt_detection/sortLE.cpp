//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sortLE.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "sortLE.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const array<double, 2U> &v
//                const array<int, 2U> &dir
//                int idx1
//                int idx2
// Return Type  : boolean_T
//
namespace coder {
namespace internal {
boolean_T sortLE(const array<double, 2U> &v, const array<int, 2U> &dir,
                 int idx1, int idx2)
{
  int k;
  boolean_T exitg1;
  boolean_T p;
  p = true;
  if (dir.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= dir.size(1) - 1)) {
    double v1;
    double v2;
    v1 = v[(idx1 + v.size(0) * (dir[k] - 1)) - 1];
    v2 = v[(idx2 + v.size(0) * (dir[k] - 1)) - 1];
    if ((v1 == v2) || (std::isnan(v1) && std::isnan(v2))) {
      k++;
    } else {
      if ((!(v1 <= v2)) && (!std::isnan(v2))) {
        p = false;
      }
      exitg1 = true;
    }
  }
  return p;
}

} // namespace internal
} // namespace coder

//
// File trailer for sortLE.cpp
//
// [EOF]
//
