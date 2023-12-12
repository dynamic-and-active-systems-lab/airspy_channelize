//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: combineVectorElements.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "combineVectorElements.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const array<boolean_T, 1U> &x
// Return Type  : int
//
namespace coder {
int combineVectorElements(const array<boolean_T, 1U> &x)
{
  int vlen;
  int y;
  vlen = x.size(0);
  if (x.size(0) == 0) {
    y = 0;
  } else {
    y = x[0];
    if (x.size(0) > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int k{2}; k <= vlen; k++) {
      y += x[k - 1];
    }
  }
  return y;
}

} // namespace coder

//
// File trailer for combineVectorElements.cpp
//
// [EOF]
//
