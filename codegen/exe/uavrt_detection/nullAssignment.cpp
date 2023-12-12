//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: nullAssignment.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "nullAssignment.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : array<creal_T, 3U> &x
//                const array<int, 2U> &idx
// Return Type  : void
//
namespace coder {
namespace internal {
void nullAssignment(array<creal_T, 3U> &x, const array<int, 2U> &idx)
{
  static rtDoubleCheckInfo s_emlrtDCI{
      451,                       // lineNo
      58,                        // colNo
      "general_null_assignment", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
      "nullAssignment.m", // pName
      4                   // checkKind
  };
  static rtRunTimeErrorInfo bd_emlrtRTEI{
      448,                       // lineNo
      1,                         // colNo
      "general_null_assignment", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
      "nullAssignment.m" // pName
  };
  static rtRunTimeErrorInfo cd_emlrtRTEI{
      81,                // lineNo
      27,                // colNo
      "validate_inputs", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
      "nullAssignment.m" // pName
  };
  array<creal_T, 3U> b_x;
  array<boolean_T, 2U> b;
  int k;
  int loop_ub_tmp;
  int npages;
  int nxout;
  int vlen;
  int vstride;
  boolean_T exitg1;
  boolean_T p;
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= idx.size(1) - 1)) {
    if (idx[k] > x.size(1)) {
      p = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (!p) {
    j_rtErrorWithMessageID(cd_emlrtRTEI.fName, cd_emlrtRTEI.lineNo);
  }
  b_x.set_size(x.size(0), x.size(1), x.size(2));
  loop_ub_tmp = x.size(0) * x.size(1);
  nxout = loop_ub_tmp * x.size(2);
  for (npages = 0; npages < nxout; npages++) {
    b_x[npages] = x[npages];
  }
  vlen = x.size(1);
  b.set_size(1, x.size(1));
  nxout = x.size(1);
  for (npages = 0; npages < nxout; npages++) {
    b[npages] = false;
  }
  nxout = idx.size(1);
  if (idx.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (k = 0; k < nxout; k++) {
    b[idx[k] - 1] = true;
  }
  npages = 0;
  nxout = b.size(1);
  if (b.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (k = 0; k < nxout; k++) {
    npages += b[k];
  }
  nxout = x.size(1) - npages;
  if (nxout > x.size(1)) {
    i_rtErrorWithMessageID(bd_emlrtRTEI.fName, bd_emlrtRTEI.lineNo);
  }
  if (nxout < 0) {
    rtNonNegativeError(static_cast<double>(nxout), s_emlrtDCI);
  }
  x.set_size(x.size(0), nxout, x.size(2));
  vstride = b_x.size(0);
  nxout *= b_x.size(0);
  npages = b_x.size(2);
  if (b_x.size(2) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int i{0}; i < npages; i++) {
    int ix0;
    int iy0;
    ix0 = i * loop_ub_tmp;
    iy0 = i * nxout;
    if (vlen > 2147483646) {
      check_forloop_overflow_error();
    }
    for (k = 0; k < vlen; k++) {
      if ((k + 1 > b.size(1)) || (!b[k])) {
        if (vstride > 2147483646) {
          check_forloop_overflow_error();
        }
        for (int j{0}; j < vstride; j++) {
          x[iy0 + j] = b_x[ix0 + j];
        }
        iy0 += vstride;
      }
      ix0 += vstride;
    }
  }
}

//
// Arguments    : array<double, 1U> &x
//                const array<int, 2U> &idx
// Return Type  : void
//
void nullAssignment(array<double, 1U> &x, const array<int, 2U> &idx)
{
  static rtRunTimeErrorInfo bd_emlrtRTEI{
      181,                      // lineNo
      9,                        // colNo
      "onearg_null_assignment", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
      "nullAssignment.m" // pName
  };
  array<boolean_T, 2U> b;
  int k;
  int k0;
  int nxin;
  int nxout;
  boolean_T exitg1;
  boolean_T p;
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= idx.size(1) - 1)) {
    if (idx[k] > x.size(0)) {
      p = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (!p) {
    j_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
  }
  nxin = x.size(0);
  b.set_size(1, x.size(0));
  nxout = x.size(0);
  for (k0 = 0; k0 < nxout; k0++) {
    b[k0] = false;
  }
  nxout = idx.size(1);
  if (idx.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (k = 0; k < nxout; k++) {
    b[idx[k] - 1] = true;
  }
  k0 = 0;
  nxout = b.size(1);
  if (b.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (k = 0; k < nxout; k++) {
    k0 += b[k];
  }
  nxout = x.size(0) - k0;
  k0 = -1;
  if (x.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (k = 0; k < nxin; k++) {
    if ((k + 1 > b.size(1)) || (!b[k])) {
      k0++;
      x[k0] = x[k];
    }
  }
  if (nxout > x.size(0)) {
    i_rtErrorWithMessageID(bd_emlrtRTEI.fName, bd_emlrtRTEI.lineNo);
  }
  if (nxout < 1) {
    nxout = 0;
  }
  x.set_size(nxout);
}

} // namespace internal
} // namespace coder

//
// File trailer for nullAssignment.cpp
//
// [EOF]
//
