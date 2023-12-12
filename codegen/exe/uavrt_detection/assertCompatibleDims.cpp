//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: assertCompatibleDims.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "assertCompatibleDims.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const array<double, 2U> &x
//                const array<double, 2U> &y
// Return Type  : void
//
namespace coder {
namespace internal {
void assertCompatibleDims(const array<double, 2U> &x,
                          const array<double, 2U> &y)
{
  if (((x.size(0) != 1) && (y.size(0) != 1) && (x.size(0) != y.size(0))) ||
      ((x.size(1) != 1) && (y.size(1) != 1) && (x.size(1) != y.size(1)))) {
    db_rtErrorWithMessageID(ob_emlrtRTEI.fName, ob_emlrtRTEI.lineNo);
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for assertCompatibleDims.cpp
//
// [EOF]
//
