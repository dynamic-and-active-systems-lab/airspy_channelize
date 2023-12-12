//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: colon.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "colon.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : double a
//                double b
//                array<double, 2U> &y
// Return Type  : void
//
namespace coder {
void eml_float_colon(double a, double b, array<double, 2U> &y)
{
  static rtRunTimeErrorInfo bd_emlrtRTEI{
      419,               // lineNo
      15,                // colNo
      "assert_pmaxsize", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/ops/colon.m" // pName
  };
  double apnd;
  double cdiff;
  double ndbl;
  int n;
  ndbl = std::floor((b - a) + 0.5);
  apnd = a + ndbl;
  cdiff = apnd - b;
  if (std::abs(cdiff) <
      4.4408920985006262E-16 * std::fmax(std::abs(a), std::abs(b))) {
    ndbl++;
    apnd = b;
  } else if (cdiff > 0.0) {
    apnd = a + (ndbl - 1.0);
  } else {
    ndbl++;
  }
  if (ndbl >= 0.0) {
    n = static_cast<int>(ndbl);
  } else {
    n = 0;
  }
  if (ndbl > 2.147483647E+9) {
    m_rtErrorWithMessageID(bd_emlrtRTEI.fName, bd_emlrtRTEI.lineNo);
  }
  y.set_size(1, n);
  if (n > 0) {
    y[0] = a;
    if (n > 1) {
      int nm1d2;
      y[n - 1] = apnd;
      nm1d2 = (n - 1) / 2;
      for (int k{0}; k <= nm1d2 - 2; k++) {
        y[k + 1] = a + (static_cast<double>(k) + 1.0);
        y[(n - k) - 2] = apnd - (static_cast<double>(k) + 1.0);
      }
      if (nm1d2 << 1 == n - 1) {
        y[nm1d2] = (a + apnd) / 2.0;
      } else {
        y[nm1d2] = a + static_cast<double>(nm1d2);
        y[nm1d2 + 1] = apnd - static_cast<double>(nm1d2);
      }
    }
  }
}

//
// Arguments    : int a
//                array<int, 2U> &y
// Return Type  : void
//
void eml_integer_colon_dispatcher(int a, array<int, 2U> &y)
{
  int n;
  if (a > 5800321) {
    n = 0;
  } else {
    unsigned int u;
    if (a < 0) {
      u = 5800321U - static_cast<unsigned int>(a);
    } else {
      u = static_cast<unsigned int>(5800321 - a);
    }
    n = static_cast<int>(u) + 1;
  }
  y.set_size(1, n);
  if (n > 0) {
    int yk;
    y[0] = a;
    yk = a;
    if (n > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int k{2}; k <= n; k++) {
      yk++;
      y[k - 1] = yk;
    }
  }
}

//
// Arguments    : int a
//                int b
//                array<int, 2U> &y
// Return Type  : void
//
void eml_integer_colon_dispatcher(int a, int b, array<int, 2U> &y)
{
  static rtRunTimeErrorInfo bd_emlrtRTEI{
      291,                            // lineNo
      9,                              // colNo
      "integer_colon_length_nonnegd", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/ops/colon.m" // pName
  };
  int bma;
  if (b < a) {
    bma = 0;
  } else {
    bma = b - a;
    if (bma < 0) {
      i_rtErrorWithMessageID(bd_emlrtRTEI.fName, bd_emlrtRTEI.lineNo);
    }
    bma++;
  }
  y.set_size(1, bma);
  if (bma > 0) {
    int yk;
    y[0] = a;
    yk = a;
    if (bma > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int k{2}; k <= bma; k++) {
      yk++;
      y[k - 1] = yk;
    }
  }
}

} // namespace coder

//
// File trailer for colon.cpp
//
// [EOF]
//
