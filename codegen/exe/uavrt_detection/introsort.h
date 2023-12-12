//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: introsort.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

#ifndef INTROSORT_H
#define INTROSORT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class anonymous_function;

class c_anonymous_function;

} // namespace coder

// Function Declarations
namespace coder {
namespace internal {
void introsort(array<int, 1U> &x, int xend, const anonymous_function &cmp);

void introsort(array<int, 1U> &x, int xend, const c_anonymous_function &cmp);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for introsort.h
//
// [EOF]
//
