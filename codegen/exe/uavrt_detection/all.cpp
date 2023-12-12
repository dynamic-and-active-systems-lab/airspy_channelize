//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: all.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "all.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const array<boolean_T, 2U> &x
//                array<boolean_T, 1U> &y
// Return Type  : void
//
namespace coder {
void all(const array<boolean_T, 2U> &x, array<boolean_T, 1U> &y)
{
  int i1;
  int i2;
  int vstride;
  y.set_size(x.size(0));
  vstride = x.size(0);
  for (i2 = 0; i2 < vstride; i2++) {
    y[i2] = true;
  }
  vstride = x.size(0);
  i2 = (x.size(1) - 1) * x.size(0);
  i1 = 0;
  if (x.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int j{0}; j < vstride; j++) {
    int ix;
    boolean_T exitg1;
    boolean_T overflow;
    i1++;
    i2++;
    if ((vstride == 0) || (i1 > i2)) {
      overflow = false;
    } else {
      overflow = (i2 > MAX_int32_T - vstride);
    }
    if (vstride == 0) {
      cc_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
    }
    if (overflow) {
      check_forloop_overflow_error();
    }
    ix = i1;
    exitg1 = false;
    while ((!exitg1) && (ix <= i2)) {
      if (!x[ix - 1]) {
        y[j] = false;
        exitg1 = true;
      } else {
        ix += vstride;
      }
    }
  }
}

} // namespace coder

//
// File trailer for all.cpp
//
// [EOF]
//
