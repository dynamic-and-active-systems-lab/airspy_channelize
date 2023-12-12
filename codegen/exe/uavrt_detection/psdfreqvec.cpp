//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: psdfreqvec.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "psdfreqvec.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cfloat>
#include <cmath>

// Function Declarations
static double rt_remd_snf(double u0, double u1);

// Function Definitions
//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_remd_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1) || std::isinf(u0)) {
    y = rtNaN;
  } else if (std::isinf(u1)) {
    y = u0;
  } else if ((u1 != 0.0) && (u1 != std::trunc(u1))) {
    double q;
    q = std::abs(u0 / u1);
    if (!(std::abs(q - std::floor(q + 0.5)) > DBL_EPSILON * q)) {
      y = 0.0 * u0;
    } else {
      y = std::fmod(u0, u1);
    }
  } else {
    y = std::fmod(u0, u1);
  }
  return y;
}

//
// Arguments    : double varargin_2
//                double varargin_4
//                array<double, 1U> &w
// Return Type  : void
//
namespace coder {
void psdfreqvec(double varargin_2, double varargin_4, array<double, 1U> &w)
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      -1,              // iFirst
      -1,              // iLast
      74,              // lineNo
      8,               // colNo
      "",              // aName
      "frequencygrid", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/shared/siglib/psdfreqvec.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      -1,              // iFirst
      -1,              // iLast
      75,              // lineNo
      8,               // colNo
      "",              // aName
      "frequencygrid", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/shared/siglib/psdfreqvec.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      -1,              // iFirst
      -1,              // iLast
      80,              // lineNo
      4,               // colNo
      "",              // aName
      "frequencygrid", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/shared/siglib/psdfreqvec.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      -1,              // iFirst
      -1,              // iLast
      78,              // lineNo
      8,               // colNo
      "",              // aName
      "frequencygrid", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/shared/siglib/psdfreqvec.m", // pName
      0 // checkKind
  };
  static rtDoubleCheckInfo s_emlrtDCI{
      74,              // lineNo
      8,               // colNo
      "frequencygrid", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/shared/siglib/psdfreqvec.m", // pName
      1 // checkKind
  };
  static rtDoubleCheckInfo t_emlrtDCI{
      80,              // lineNo
      4,               // colNo
      "frequencygrid", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/shared/siglib/psdfreqvec.m", // pName
      1 // checkKind
  };
  static rtDoubleCheckInfo u_emlrtDCI{
      78,              // lineNo
      8,               // colNo
      "frequencygrid", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/shared/siglib/psdfreqvec.m", // pName
      1 // checkKind
  };
  array<double, 2U> w1;
  double Fs1;
  double Nyq;
  double freq_res;
  double half_res;
  double x;
  int loop_ub;
  boolean_T isNPTSodd;
  if (std::isnan(varargin_4)) {
    Fs1 = 6.2831853071795862;
  } else {
    Fs1 = varargin_4;
  }
  freq_res = Fs1 / varargin_2;
  if (std::isnan(varargin_2 - 1.0)) {
    w1.set_size(1, 1);
    w1[0] = rtNaN;
  } else if (varargin_2 - 1.0 < 0.0) {
    w1.set_size(w1.size(0), 0);
  } else {
    w1.set_size(1, static_cast<int>(varargin_2 - 1.0) + 1);
    loop_ub = static_cast<int>(varargin_2 - 1.0);
    for (int i{0}; i <= loop_ub; i++) {
      w1[i] = i;
    }
  }
  w1.set_size(1, w1.size(1));
  loop_ub = w1.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    w1[i] = freq_res * w1[i];
  }
  Nyq = Fs1 / 2.0;
  half_res = freq_res / 2.0;
  x = rt_remd_snf(varargin_2, 2.0);
  if (std::isnan(x)) {
    ab_rtErrorWithMessageID(lb_emlrtRTEI.fName, lb_emlrtRTEI.lineNo);
  }
  isNPTSodd = (x != 0.0);
  if (isNPTSodd) {
    x = (varargin_2 + 1.0) / 2.0;
  } else {
    x = varargin_2 / 2.0 + 1.0;
  }
  if (std::isnan(rt_remd_snf(x, 2.0))) {
    ab_rtErrorWithMessageID(lb_emlrtRTEI.fName, lb_emlrtRTEI.lineNo);
  }
  if (isNPTSodd) {
    if (x != static_cast<int>(std::floor(x))) {
      rtIntegerError(x, s_emlrtDCI);
    }
    if ((static_cast<int>(x) < 1) || (static_cast<int>(x) > w1.size(1))) {
      rtDynamicBoundsError(static_cast<int>(x), 1, w1.size(1), ab_emlrtBCI);
    }
    w1[static_cast<int>(x) - 1] = Nyq - half_res;
    if ((static_cast<int>(static_cast<unsigned int>(x) + 1U) < 1) ||
        (static_cast<int>(static_cast<unsigned int>(x) + 1U) > w1.size(1))) {
      rtDynamicBoundsError(static_cast<int>(static_cast<unsigned int>(x) + 1U),
                           1, w1.size(1), bb_emlrtBCI);
    }
    w1[static_cast<int>(static_cast<unsigned int>(x))] = Nyq + half_res;
  } else {
    if (x != static_cast<int>(std::floor(x))) {
      rtIntegerError(x, u_emlrtDCI);
    }
    if ((static_cast<int>(x) < 1) || (static_cast<int>(x) > w1.size(1))) {
      rtDynamicBoundsError(static_cast<int>(x), 1, w1.size(1), db_emlrtBCI);
    }
    w1[static_cast<int>(x) - 1] = Nyq;
  }
  if (varargin_2 != static_cast<int>(std::floor(varargin_2))) {
    rtIntegerError(varargin_2, t_emlrtDCI);
  }
  if ((static_cast<int>(varargin_2) < 1) ||
      (static_cast<int>(varargin_2) > w1.size(1))) {
    rtDynamicBoundsError(static_cast<int>(varargin_2), 1, w1.size(1),
                         cb_emlrtBCI);
  }
  w1[static_cast<int>(varargin_2) - 1] = Fs1 - freq_res;
  w.set_size(w1.size(1));
  loop_ub = w1.size(1);
  for (int i{0}; i < loop_ub; i++) {
    w[i] = w1[i];
  }
}

} // namespace coder

//
// File trailer for psdfreqvec.cpp
//
// [EOF]
//
