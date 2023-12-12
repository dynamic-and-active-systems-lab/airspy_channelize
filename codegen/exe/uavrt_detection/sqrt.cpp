//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sqrt.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "sqrt.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : array<double, 2U> &x
// Return Type  : void
//
namespace coder {
void b_sqrt(array<double, 2U> &x)
{
  int i;
  boolean_T p;
  p = false;
  i = x.size(0) * x.size(1);
  for (int k{0}; k < i; k++) {
    if (p || (x[k] < 0.0)) {
      p = true;
    }
  }
  if (p) {
    rtErrorWithMessageID("sqrt", ec_emlrtRTEI.fName, ec_emlrtRTEI.lineNo);
  }
  if (i > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < i; k++) {
    x[k] = std::sqrt(x[k]);
  }
}

} // namespace coder

//
// File trailer for sqrt.cpp
//
// [EOF]
//
