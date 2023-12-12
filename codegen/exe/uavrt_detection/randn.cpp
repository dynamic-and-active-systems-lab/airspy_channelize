//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: randn.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "randn.h"
#include "eml_rand_mt19937ar.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : creal_T r[1000]
// Return Type  : void
//
namespace coder {
void complexLike(creal_T r[1000])
{
  double im;
  double re;
  for (int k{0}; k < 1000; k++) {
    re = eml_rand_mt19937ar(state);
    im = eml_rand_mt19937ar(state);
    r[k].re = re;
    r[k].im = im;
  }
  for (int k{0}; k < 1000; k++) {
    double ai;
    im = r[k].re;
    ai = r[k].im;
    if (ai == 0.0) {
      re = im / 1.4142135623730951;
      im = 0.0;
    } else if (im == 0.0) {
      re = 0.0;
      im = ai / 1.4142135623730951;
    } else {
      re = im / 1.4142135623730951;
      im = ai / 1.4142135623730951;
    }
    r[k].re = re;
    r[k].im = im;
  }
}

//
// Arguments    : double varargin_1
//                unsigned int varargin_2
//                array<creal_T, 2U> &r
// Return Type  : void
//
void complexLike(double varargin_1, unsigned int varargin_2,
                 array<creal_T, 2U> &r)
{
  static rtDoubleCheckInfo s_emlrtDCI{
      29,                            // lineNo
      34,                            // colNo
      "eml_rand_mt19937ar_stateful", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/randfun/private/"
      "eml_rand_mt19937ar_stateful.m", // pName
      4                                // checkKind
  };
  double im;
  double re;
  int loop_ub;
  if ((varargin_1 != std::floor(varargin_1)) || std::isinf(varargin_1) ||
      (varargin_1 < -2.147483648E+9) || (varargin_1 > 2.147483647E+9)) {
    b_rtErrorWithMessageID(MIN_int32_T, nb_emlrtRTEI.fName,
                           nb_emlrtRTEI.lineNo);
  }
  if (varargin_2 > 2147483647U) {
    b_rtErrorWithMessageID(MIN_int32_T, nb_emlrtRTEI.fName,
                           nb_emlrtRTEI.lineNo);
  }
  if (varargin_1 <= 0.0) {
    re = 0.0;
  } else {
    re = varargin_1;
  }
  if (varargin_2 <= 0U) {
    re = 0.0;
  } else {
    re *= static_cast<double>(varargin_2);
  }
  if (!(re <= 2.147483647E+9)) {
    m_rtErrorWithMessageID(p_emlrtRTEI.fName, p_emlrtRTEI.lineNo);
  }
  if (!(varargin_1 >= 0.0)) {
    rtNonNegativeError(varargin_1, s_emlrtDCI);
  }
  r.set_size(static_cast<int>(varargin_1), static_cast<int>(varargin_2));
  loop_ub = static_cast<int>(varargin_1) * static_cast<int>(varargin_2);
  for (int k{0}; k < loop_ub; k++) {
    re = eml_rand_mt19937ar(state);
    im = eml_rand_mt19937ar(state);
    r[k].re = re;
    r[k].im = im;
  }
  for (int k{0}; k < loop_ub; k++) {
    double ai;
    im = r[k].re;
    ai = r[k].im;
    if (ai == 0.0) {
      re = im / 1.4142135623730951;
      im = 0.0;
    } else if (im == 0.0) {
      re = 0.0;
      im = ai / 1.4142135623730951;
    } else {
      re = im / 1.4142135623730951;
      im = ai / 1.4142135623730951;
    }
    r[k].re = re;
    r[k].im = im;
  }
}

//
// Arguments    : double r[1000]
// Return Type  : void
//
void randn(double r[1000])
{
  for (int k{0}; k < 1000; k++) {
    r[k] = eml_rand_mt19937ar(state);
  }
}

//
// Arguments    : double varargin_1
//                unsigned int varargin_2
//                array<double, 2U> &r
// Return Type  : void
//
void randn(double varargin_1, unsigned int varargin_2, array<double, 2U> &r)
{
  static rtDoubleCheckInfo s_emlrtDCI{
      37,                            // lineNo
      34,                            // colNo
      "eml_rand_mt19937ar_stateful", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/randfun/private/"
      "eml_rand_mt19937ar_stateful.m", // pName
      4                                // checkKind
  };
  int i;
  if (!(varargin_1 >= 0.0)) {
    rtNonNegativeError(varargin_1, s_emlrtDCI);
  }
  r.set_size(static_cast<int>(varargin_1), static_cast<int>(varargin_2));
  i = static_cast<int>(varargin_1) * static_cast<int>(varargin_2);
  for (int k{0}; k < i; k++) {
    r[k] = eml_rand_mt19937ar(state);
  }
}

} // namespace coder

//
// File trailer for randn.cpp
//
// [EOF]
//
