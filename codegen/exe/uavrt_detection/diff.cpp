//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: diff.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "diff.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"

// Variable Definitions
static rtRunTimeErrorInfo wb_emlrtRTEI{
    51,     // lineNo
    19,     // colNo
    "diff", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/datafun/diff.m" // pName
};

// Function Definitions
//
// Arguments    : const array<double, 1U> &x
//                array<double, 1U> &y
// Return Type  : void
//
namespace coder {
void diff(const array<double, 1U> &x, array<double, 1U> &y)
{
  int dimSize;
  dimSize = x.size(0);
  if (x.size(0) == 0) {
    y.set_size(0);
  } else {
    int u0;
    u0 = x.size(0) - 1;
    if (u0 > 1) {
      u0 = 1;
    }
    if (u0 < 1) {
      y.set_size(0);
    } else {
      double work_data;
      if (x.size(0) == 1) {
        w_rtErrorWithMessageID(wb_emlrtRTEI.fName, wb_emlrtRTEI.lineNo);
      }
      y.set_size(x.size(0) - 1);
      work_data = x[0];
      if (x.size(0) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (u0 = 2; u0 <= dimSize; u0++) {
        double tmp2;
        tmp2 = work_data;
        work_data = x[u0 - 1];
        y[u0 - 2] = work_data - tmp2;
      }
    }
  }
}

//
// Arguments    : const array<double, 2U> &x
//                array<double, 2U> &y
// Return Type  : void
//
void diff(const array<double, 2U> &x, array<double, 2U> &y)
{
  int dimSize;
  dimSize = x.size(0);
  if (x.size(0) == 0) {
    y.set_size(0, 1);
  } else {
    int u0;
    u0 = x.size(0) - 1;
    if (u0 > 1) {
      u0 = 1;
    }
    if (u0 < 1) {
      y.set_size(0, 1);
    } else {
      double work_data;
      if (x.size(0) == 1) {
        w_rtErrorWithMessageID(wb_emlrtRTEI.fName, wb_emlrtRTEI.lineNo);
      }
      y.set_size(x.size(0) - 1, 1);
      work_data = x[0];
      if (x.size(0) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (u0 = 2; u0 <= dimSize; u0++) {
        double d;
        double tmp1;
        tmp1 = x[u0 - 1];
        d = tmp1;
        tmp1 -= work_data;
        work_data = d;
        y[u0 - 2] = tmp1;
      }
    }
  }
}

} // namespace coder

//
// File trailer for diff.cpp
//
// [EOF]
//
