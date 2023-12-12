//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: stft.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "stft.h"
#include "FFTImplementationCallback.h"
#include "computeDFT.h"
#include "eml_int_forloop_overflow_check.h"
#include "formatSTFTOutput.h"
#include "indexShapeCheck.h"
#include "psdfreqvec.h"
#include "rt_nonfinite.h"
#include "stickyStruct.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "validateattributes.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Variable Definitions
static rtEqualityCheckInfo c_emlrtECI{
    -1,               // nDims
    34,               // lineNo
    9,                // colNo
    "getSTFTColumns", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/+signal/+internal/"
    "+stft/getSTFTColumns.m" // pName
};

static rtBoundsCheckInfo d_emlrtBCI{
    -1,               // iFirst
    -1,               // iLast
    34,               // lineNo
    15,               // colNo
    "",               // aName
    "getSTFTColumns", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/+signal/+internal/"
    "+stft/getSTFTColumns.m", // pName
    0                         // checkKind
};

static rtBoundsCheckInfo e_emlrtBCI{
    -1,               // iFirst
    -1,               // iLast
    34,               // lineNo
    46,               // colNo
    "",               // aName
    "getSTFTColumns", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/+signal/+internal/"
    "+stft/getSTFTColumns.m", // pName
    0                         // checkKind
};

static rtDoubleCheckInfo c_emlrtDCI{
    34,               // lineNo
    46,               // colNo
    "getSTFTColumns", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/+signal/+internal/"
    "+stft/getSTFTColumns.m", // pName
    1                         // checkKind
};

static rtBoundsCheckInfo f_emlrtBCI{
    -1,               // iFirst
    -1,               // iLast
    34,               // lineNo
    27,               // colNo
    "",               // aName
    "getSTFTColumns", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/+signal/+internal/"
    "+stft/getSTFTColumns.m", // pName
    0                         // checkKind
};

static rtDoubleCheckInfo d_emlrtDCI{
    34,               // lineNo
    27,               // colNo
    "getSTFTColumns", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/+signal/+internal/"
    "+stft/getSTFTColumns.m", // pName
    1                         // checkKind
};

static rtRunTimeErrorInfo db_emlrtRTEI{
    336,                 // lineNo
    5,                   // colNo
    "verifyDataAndTime", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/+signal/+internal/"
    "+stft/stftParser.m" // pName
};

static rtRunTimeErrorInfo eb_emlrtRTEI{
    318,                 // lineNo
    5,                   // colNo
    "verifyDataAndTime", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/+signal/+internal/"
    "+stft/stftParser.m" // pName
};

static rtBoundsCheckInfo g_emlrtBCI{
    -1,                                                             // iFirst
    -1,                                                             // iLast
    278,                                                            // lineNo
    14,                                                             // colNo
    "",                                                             // aName
    "computeSTFT",                                                  // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/stft.m", // pName
    0                                                               // checkKind
};

static rtBoundsCheckInfo h_emlrtBCI{
    -1,                                                             // iFirst
    -1,                                                             // iLast
    278,                                                            // lineNo
    12,                                                             // colNo
    "",                                                             // aName
    "computeSTFT",                                                  // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/stft.m", // pName
    0                                                               // checkKind
};

static rtBoundsCheckInfo i_emlrtBCI{
    -1,                                                             // iFirst
    -1,                                                             // iLast
    277,                                                            // lineNo
    14,                                                             // colNo
    "",                                                             // aName
    "computeSTFT",                                                  // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/stft.m", // pName
    0                                                               // checkKind
};

static rtBoundsCheckInfo j_emlrtBCI{
    -1,                                                             // iFirst
    -1,                                                             // iLast
    277,                                                            // lineNo
    12,                                                             // colNo
    "",                                                             // aName
    "computeSTFT",                                                  // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/stft.m", // pName
    0                                                               // checkKind
};

static rtDoubleCheckInfo e_emlrtDCI{
    14,               // lineNo
    30,               // colNo
    "getSTFTColumns", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/+signal/+internal/"
    "+stft/getSTFTColumns.m", // pName
    1                         // checkKind
};

static rtDoubleCheckInfo f_emlrtDCI{
    14,               // lineNo
    30,               // colNo
    "getSTFTColumns", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/+signal/+internal/"
    "+stft/getSTFTColumns.m", // pName
    4                         // checkKind
};

static rtDoubleCheckInfo g_emlrtDCI{
    14,               // lineNo
    5,                // colNo
    "getSTFTColumns", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/+signal/+internal/"
    "+stft/getSTFTColumns.m", // pName
    1                         // checkKind
};

static rtRunTimeErrorInfo gb_emlrtRTEI{
    14,                 // lineNo
    37,                 // colNo
    "validatepositive", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/+valattr/"
    "validatepositive.m" // pName
};

// Function Declarations
static void l_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

static void rtErrorWithMessageID(const long i, const char *aFcnName,
                                 int aLineNum);

static void t_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void v_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *r
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void l_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "Expected ") << r) << " to be positive.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const long i
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void rtErrorWithMessageID(const long i, const char *aFcnName,
                                 int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "Input signal length must be greater than or equal to the "
                 "window length, ")
   << i)
      << ".";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void t_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Colon operands must be in range of the data type and exactly "
               "representable without loss of precision.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void v_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Input signal must have at least 2 samples.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const array<creal32_T, 2U> &x
//                double varargin_1
//                const array<double, 1U> &varargin_3
//                double varargin_5
//                double varargin_7
//                array<creal32_T, 2U> &varargout_1
//                array<float, 1U> &varargout_2
//                array<float, 1U> &varargout_3
// Return Type  : void
//
namespace coder {
void stft(const array<creal32_T, 2U> &x, double varargin_1,
          const array<double, 1U> &varargin_3, double varargin_5,
          double varargin_7, array<creal32_T, 2U> &varargout_1,
          array<float, 1U> &varargout_2, array<float, 1U> &varargout_3)
{
  static rtRunTimeErrorInfo bd_emlrtRTEI{
      398,          // lineNo
      5,            // colNo
      "checkrange", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/ops/colon.m" // pName
  };
  internal::j_stickyStruct obj;
  array<creal32_T, 2U> c;
  array<creal32_T, 2U> xin;
  array<double, 1U> b_f;
  array<double, 1U> f;
  array<float, 2U> y;
  double hopSize;
  double nCol;
  float b_varargin_3;
  int iv[2];
  int bcoef;
  int csz_idx_0;
  int i;
  int i1;
  int i2;
  int iCol;
  int k;
  boolean_T exitg1;
  boolean_T p;
  validateattributes(varargin_3);
  validateattributes(static_cast<double>(varargin_3.size(0)));
  validateattributes(varargin_5, static_cast<double>(varargin_3.size(0)));
  b_validateattributes(varargin_7, static_cast<double>(varargin_3.size(0)));
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= x.size(1) - 1)) {
    if ((!std::isinf(x[k].re)) && (!std::isinf(x[k].im)) &&
        ((!std::isnan(x[k].re)) && (!std::isnan(x[k].im)))) {
      k++;
    } else {
      p = false;
      exitg1 = true;
    }
  }
  if (!p) {
    j_rtErrorWithMessageID("X", bb_emlrtRTEI.fName, bb_emlrtRTEI.lineNo);
  }
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= x.size(1) - 1)) {
    if ((!std::isnan(x[k].re)) && (!std::isnan(x[k].im))) {
      k++;
    } else {
      p = false;
      exitg1 = true;
    }
  }
  if (!p) {
    i_rtErrorWithMessageID("X", ab_emlrtRTEI.fName, ab_emlrtRTEI.lineNo);
  }
  if (x.size(1) == 0) {
    h_rtErrorWithMessageID("X", y_emlrtRTEI.fName, y_emlrtRTEI.lineNo);
  }
  if (x.size(1) < 2) {
    v_rtErrorWithMessageID(eb_emlrtRTEI.fName, eb_emlrtRTEI.lineNo);
  }
  if (varargin_3.size(0) > x.size(1)) {
    rtErrorWithMessageID(static_cast<long>(varargin_3.size(0)),
                         db_emlrtRTEI.fName, db_emlrtRTEI.lineNo);
  }
  if (std::isinf(varargin_1) || std::isnan(varargin_1)) {
    j_rtErrorWithMessageID("sample rate", bb_emlrtRTEI.fName,
                           bb_emlrtRTEI.lineNo);
  }
  if (varargin_1 <= 0.0) {
    l_rtErrorWithMessageID("sample rate", gb_emlrtRTEI.fName,
                           gb_emlrtRTEI.lineNo);
  }
  obj.value.set_size(varargin_3.size(0));
  bcoef = varargin_3.size(0);
  for (i = 0; i < bcoef; i++) {
    obj.value[i] = static_cast<float>(varargin_3[i]);
  }
  hopSize = static_cast<double>(varargin_3.size(0)) - varargin_5;
  nCol = std::trunc((static_cast<double>(x.size(1)) - varargin_5) / hopSize);
  xin.set_size(varargin_3.size(0), xin.size(1));
  if (!(nCol >= 0.0)) {
    rtNonNegativeError(nCol, f_emlrtDCI);
  }
  if (nCol != static_cast<int>(nCol)) {
    rtIntegerError(nCol, e_emlrtDCI);
  }
  i = static_cast<int>(nCol);
  xin.set_size(xin.size(0), static_cast<int>(nCol));
  if (nCol != static_cast<int>(nCol)) {
    rtIntegerError(nCol, g_emlrtDCI);
  }
  bcoef = varargin_3.size(0) * static_cast<int>(nCol);
  for (i1 = 0; i1 < bcoef; i1++) {
    xin[i1].re = 0.0F;
    xin[i1].im = 0.0F;
  }
  if (nCol - 1.0 < 0.0) {
    y.set_size(y.size(0), 0);
  } else {
    if (!(nCol - 1.0 <= 3.4028234663852886E+38)) {
      t_rtErrorWithMessageID(bd_emlrtRTEI.fName, bd_emlrtRTEI.lineNo);
    }
    y.set_size(1, static_cast<int>(nCol - 1.0) + 1);
    bcoef = static_cast<int>(nCol - 1.0);
    for (i1 = 0; i1 <= bcoef; i1++) {
      y[i1] = static_cast<float>(i1);
    }
  }
  for (iCol = 0; iCol < i; iCol++) {
    double d;
    nCol = hopSize * ((static_cast<double>(iCol) + 1.0) - 1.0);
    d = static_cast<double>(varargin_3.size(0)) + nCol;
    if (nCol + 1.0 > d) {
      i1 = 1;
      i2 = 0;
    } else {
      if (nCol + 1.0 != static_cast<int>(std::floor(nCol + 1.0))) {
        rtIntegerError(nCol + 1.0, d_emlrtDCI);
      }
      if ((static_cast<int>(nCol + 1.0) < 1) ||
          (static_cast<int>(nCol + 1.0) > x.size(1))) {
        rtDynamicBoundsError(static_cast<int>(nCol + 1.0), 1, x.size(1),
                             f_emlrtBCI);
      }
      i1 = static_cast<int>(nCol + 1.0);
      if (d != static_cast<int>(std::floor(d))) {
        rtIntegerError(d, c_emlrtDCI);
      }
      if ((static_cast<int>(d) < 1) || (static_cast<int>(d) > x.size(1))) {
        rtDynamicBoundsError(static_cast<int>(d), 1, x.size(1), e_emlrtBCI);
      }
      i2 = static_cast<int>(d);
    }
    if ((iCol + 1 < 1) || (iCol + 1 > xin.size(1))) {
      rtDynamicBoundsError(iCol + 1, 1, xin.size(1), d_emlrtBCI);
    }
    bcoef = i2 - i1;
    i2 = bcoef + 1;
    rtSubAssignSizeCheck(xin.size(), 1, &i2, 1, c_emlrtECI);
    for (i2 = 0; i2 <= bcoef; i2++) {
      xin[i2 + xin.size(0) * iCol] = x[(i1 + i2) - 1];
    }
  }
  y.set_size(1, y.size(1));
  b_varargin_3 =
      static_cast<float>(static_cast<double>(varargin_3.size(0)) / 2.0);
  bcoef = y.size(1) - 1;
  for (i = 0; i <= bcoef; i++) {
    y[i] = (y[i] * static_cast<float>(hopSize) + b_varargin_3) /
           static_cast<float>(varargin_1);
  }
  if (xin.size(0) == 1) {
    csz_idx_0 = obj.value.size(0);
  } else if (obj.value.size(0) == 1) {
    csz_idx_0 = xin.size(0);
  } else if (obj.value.size(0) == xin.size(0)) {
    csz_idx_0 = obj.value.size(0);
  } else {
    u_rtErrorWithMessageID(cb_emlrtRTEI.fName, cb_emlrtRTEI.lineNo);
  }
  c.set_size(csz_idx_0, xin.size(1));
  if ((csz_idx_0 != 0) && (xin.size(1) != 0)) {
    bcoef = (xin.size(1) != 1);
    i = xin.size(1) - 1;
    csz_idx_0 = (obj.value.size(0) != 1);
    for (k = 0; k <= i; k++) {
      iCol = bcoef * k;
      i1 = c.size(0) - 1;
      for (int b_k{0}; b_k <= i1; b_k++) {
        b_varargin_3 = obj.value[csz_idx_0 * b_k];
        i2 = csz_idx_0 * b_k;
        c[b_k + c.size(0) * k].re =
            b_varargin_3 * xin[i2 + xin.size(0) * iCol].re;
        c[b_k + c.size(0) * k].im =
            b_varargin_3 * xin[i2 + xin.size(0) * iCol].im;
      }
    }
  }
  computeDFT(c, varargin_7, varargin_1, varargout_1, f);
  b_signal::internal::stft::formatSTFTOutput(varargout_1, f, b_f);
  if (varargout_1.size(0) < 1) {
    bcoef = 0;
  } else {
    if (b_f.size(0) < 1) {
      rtDynamicBoundsError(1, 1, b_f.size(0), j_emlrtBCI);
    }
    if (varargout_1.size(0) > b_f.size(0)) {
      rtDynamicBoundsError(varargout_1.size(0), 1, b_f.size(0), i_emlrtBCI);
    }
    bcoef = varargout_1.size(0);
  }
  iv[0] = 1;
  iv[1] = bcoef;
  internal::indexShapeCheck(b_f.size(0), iv);
  varargout_2.set_size(bcoef);
  for (i = 0; i < bcoef; i++) {
    varargout_2[i] = static_cast<float>(b_f[i]);
  }
  if (varargout_1.size(1) < 1) {
    bcoef = 0;
  } else {
    if (y.size(1) < 1) {
      rtDynamicBoundsError(1, 1, y.size(1), h_emlrtBCI);
    }
    if (varargout_1.size(1) > y.size(1)) {
      rtDynamicBoundsError(varargout_1.size(1), 1, y.size(1), g_emlrtBCI);
    }
    bcoef = varargout_1.size(1);
  }
  varargout_3.set_size(bcoef);
  for (i = 0; i < bcoef; i++) {
    varargout_3[i] = y[i];
  }
}

//
// Arguments    : const array<creal_T, 2U> &x
//                double varargin_1
//                const array<double, 1U> &varargin_3
//                double varargin_5
//                double varargin_7
//                array<creal_T, 3U> &varargout_1
//                array<double, 1U> &varargout_2
//                array<double, 1U> &varargout_3
// Return Type  : void
//
void stft(const array<creal_T, 2U> &x, double varargin_1,
          const array<double, 1U> &varargin_3, double varargin_5,
          double varargin_7, array<creal_T, 3U> &varargout_1,
          array<double, 1U> &varargout_2, array<double, 1U> &varargout_3)
{
  array<creal_T, 3U> b_c;
  array<creal_T, 3U> xin;
  array<creal_T, 2U> b_wrappedData;
  array<creal_T, 2U> wrappedData;
  array<creal_T, 1U> b_x;
  array<double, 2U> costab;
  array<double, 2U> sintab;
  array<double, 2U> sintabinv;
  array<double, 2U> y;
  array<double, 1U> b_f;
  array<double, 1U> f;
  double hopSize;
  double nCol;
  int b_xin[3];
  int c[2];
  int b_bcoef;
  int bcoef;
  int c_tmp;
  int csz_idx_0;
  int i;
  int i1;
  int i2;
  int i3;
  int iCol;
  int k;
  int loop_ub;
  boolean_T exitg1;
  boolean_T useRadix2;
  validateattributes(varargin_3);
  validateattributes(static_cast<double>(varargin_3.size(0)));
  validateattributes(varargin_5, static_cast<double>(varargin_3.size(0)));
  b_validateattributes(varargin_7, static_cast<double>(varargin_3.size(0)));
  useRadix2 = true;
  loop_ub = x.size(0) * x.size(1);
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= loop_ub - 1)) {
    if ((!std::isinf(x[k].re)) && (!std::isinf(x[k].im)) &&
        ((!std::isnan(x[k].re)) && (!std::isnan(x[k].im)))) {
      k++;
    } else {
      useRadix2 = false;
      exitg1 = true;
    }
  }
  if (!useRadix2) {
    j_rtErrorWithMessageID("X", bb_emlrtRTEI.fName, bb_emlrtRTEI.lineNo);
  }
  useRadix2 = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= loop_ub - 1)) {
    if ((!std::isnan(x[k].re)) && (!std::isnan(x[k].im))) {
      k++;
    } else {
      useRadix2 = false;
      exitg1 = true;
    }
  }
  if (!useRadix2) {
    i_rtErrorWithMessageID("X", ab_emlrtRTEI.fName, ab_emlrtRTEI.lineNo);
  }
  if ((x.size(0) == 0) || (x.size(1) == 0)) {
    h_rtErrorWithMessageID("X", y_emlrtRTEI.fName, y_emlrtRTEI.lineNo);
  }
  if (x.size(0) == 1) {
    wrappedData.set_size(x.size(1), 1);
    loop_ub = x.size(1);
    for (i = 0; i < loop_ub; i++) {
      wrappedData[i] = x[i];
    }
  } else {
    wrappedData.set_size(x.size(0), x.size(1));
    for (i = 0; i < loop_ub; i++) {
      wrappedData[i] = x[i];
    }
  }
  if (wrappedData.size(0) < 2) {
    v_rtErrorWithMessageID(eb_emlrtRTEI.fName, eb_emlrtRTEI.lineNo);
  }
  if (varargin_3.size(0) > wrappedData.size(0)) {
    rtErrorWithMessageID(static_cast<long>(varargin_3.size(0)),
                         db_emlrtRTEI.fName, db_emlrtRTEI.lineNo);
  }
  if (std::isinf(varargin_1) || std::isnan(varargin_1)) {
    j_rtErrorWithMessageID("sample rate", bb_emlrtRTEI.fName,
                           bb_emlrtRTEI.lineNo);
  }
  if (varargin_1 <= 0.0) {
    l_rtErrorWithMessageID("sample rate", gb_emlrtRTEI.fName,
                           gb_emlrtRTEI.lineNo);
  }
  hopSize = static_cast<double>(varargin_3.size(0)) - varargin_5;
  nCol = std::trunc((static_cast<double>(wrappedData.size(0)) - varargin_5) /
                    hopSize);
  xin.set_size(varargin_3.size(0), xin.size(1), xin.size(2));
  if (!(nCol >= 0.0)) {
    rtNonNegativeError(nCol, f_emlrtDCI);
  }
  if (nCol != static_cast<int>(nCol)) {
    rtIntegerError(nCol, e_emlrtDCI);
  }
  i = static_cast<int>(nCol);
  xin.set_size(xin.size(0), static_cast<int>(nCol), wrappedData.size(1));
  if (nCol != static_cast<int>(nCol)) {
    rtIntegerError(nCol, g_emlrtDCI);
  }
  loop_ub = varargin_3.size(0) * static_cast<int>(nCol) * wrappedData.size(1);
  for (i1 = 0; i1 < loop_ub; i1++) {
    xin[i1].re = 0.0;
    xin[i1].im = 0.0;
  }
  if (nCol - 1.0 < 0.0) {
    y.set_size(y.size(0), 0);
  } else {
    y.set_size(1, static_cast<int>(nCol - 1.0) + 1);
    loop_ub = static_cast<int>(nCol - 1.0);
    for (i1 = 0; i1 <= loop_ub; i1++) {
      y[i1] = i1;
    }
  }
  if (static_cast<int>(nCol) - 1 >= 0) {
    c[1] = wrappedData.size(1);
    bcoef = wrappedData.size(1);
  }
  for (iCol = 0; iCol < i; iCol++) {
    double d;
    nCol = hopSize * ((static_cast<double>(iCol) + 1.0) - 1.0);
    d = static_cast<double>(varargin_3.size(0)) + nCol;
    if (nCol + 1.0 > d) {
      i1 = 0;
      i2 = 0;
    } else {
      if (nCol + 1.0 != static_cast<int>(std::floor(nCol + 1.0))) {
        rtIntegerError(nCol + 1.0, d_emlrtDCI);
      }
      if ((static_cast<int>(nCol + 1.0) < 1) ||
          (static_cast<int>(nCol + 1.0) > wrappedData.size(0))) {
        rtDynamicBoundsError(static_cast<int>(nCol + 1.0), 1,
                             wrappedData.size(0), f_emlrtBCI);
      }
      i1 = static_cast<int>(nCol + 1.0) - 1;
      if (d != static_cast<int>(std::floor(d))) {
        rtIntegerError(d, c_emlrtDCI);
      }
      if ((static_cast<int>(d) < 1) ||
          (static_cast<int>(d) > wrappedData.size(0))) {
        rtDynamicBoundsError(static_cast<int>(d), 1, wrappedData.size(0),
                             e_emlrtBCI);
      }
      i2 = static_cast<int>(d);
    }
    if ((iCol + 1 < 1) || (iCol + 1 > xin.size(1))) {
      rtDynamicBoundsError(iCol + 1, 1, xin.size(1), d_emlrtBCI);
    }
    b_xin[0] = xin.size(0);
    b_xin[1] = 1;
    b_xin[2] = xin.size(2);
    c_tmp = i2 - i1;
    c[0] = c_tmp;
    rtSubAssignSizeCheck(&b_xin[0], 3, &c[0], 2, c_emlrtECI);
    b_wrappedData.set_size(c_tmp, wrappedData.size(1));
    for (i2 = 0; i2 < bcoef; i2++) {
      for (i3 = 0; i3 < c_tmp; i3++) {
        b_wrappedData[i3 + b_wrappedData.size(0) * i2] =
            wrappedData[(i1 + i3) + wrappedData.size(0) * i2];
      }
    }
    b_xin[0] = xin.size(0);
    loop_ub = xin.size(2);
    b_bcoef = b_xin[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      for (i2 = 0; i2 < b_bcoef; i2++) {
        xin[(i2 + xin.size(0) * iCol) + xin.size(0) * xin.size(1) * i1] =
            b_wrappedData[i2 + b_xin[0] * i1];
      }
    }
  }
  y.set_size(1, y.size(1));
  nCol = static_cast<double>(varargin_3.size(0)) / 2.0;
  loop_ub = y.size(1) - 1;
  for (i = 0; i <= loop_ub; i++) {
    y[i] = (y[i] * hopSize + nCol) / varargin_1;
  }
  if (xin.size(0) == 1) {
    csz_idx_0 = varargin_3.size(0);
  } else if (varargin_3.size(0) == 1) {
    csz_idx_0 = xin.size(0);
  } else if (varargin_3.size(0) == xin.size(0)) {
    csz_idx_0 = varargin_3.size(0);
  } else {
    u_rtErrorWithMessageID(cb_emlrtRTEI.fName, cb_emlrtRTEI.lineNo);
  }
  b_c.set_size(csz_idx_0, xin.size(1), xin.size(2));
  if ((csz_idx_0 != 0) && (xin.size(1) != 0)) {
    b_bcoef = (xin.size(2) != 1);
    i = xin.size(2) - 1;
    bcoef = (xin.size(1) != 1);
    csz_idx_0 = (varargin_3.size(0) != 1);
    for (k = 0; k <= i; k++) {
      loop_ub = b_bcoef * k;
      i1 = b_c.size(1) - 1;
      for (c_tmp = 0; c_tmp <= i1; c_tmp++) {
        iCol = bcoef * c_tmp;
        i2 = b_c.size(0) - 1;
        for (int b_k{0}; b_k <= i2; b_k++) {
          nCol = varargin_3[csz_idx_0 * b_k];
          i3 = csz_idx_0 * b_k;
          b_c[(b_k + b_c.size(0) * c_tmp) + b_c.size(0) * b_c.size(1) * k].re =
              nCol * xin[(i3 + xin.size(0) * iCol) +
                         xin.size(0) * xin.size(1) * loop_ub]
                         .re;
          b_c[(b_k + b_c.size(0) * c_tmp) + b_c.size(0) * b_c.size(1) * k].im =
              nCol * xin[(i3 + xin.size(0) * iCol) +
                         xin.size(0) * xin.size(1) * loop_ub]
                         .im;
        }
      }
    }
  }
  if (b_c.size(0) > varargin_7) {
    if (!(varargin_7 >= 0.0)) {
      rtNonNegativeError(varargin_7, i_emlrtDCI);
    }
    i = static_cast<int>(std::floor(varargin_7));
    if (varargin_7 != i) {
      rtIntegerError(varargin_7, h_emlrtDCI);
    }
    csz_idx_0 = static_cast<int>(varargin_7);
    xin.set_size(csz_idx_0, b_c.size(1), b_c.size(2));
    if (csz_idx_0 != i) {
      rtIntegerError(varargin_7, j_emlrtDCI);
    }
    loop_ub = csz_idx_0 * b_c.size(1) * b_c.size(2);
    for (i = 0; i < loop_ub; i++) {
      xin[i].re = 0.0;
      xin[i].im = 0.0;
    }
    i = static_cast<int>(static_cast<double>(b_c.size(1)) *
                         static_cast<double>(b_c.size(2)));
    for (iCol = 0; iCol < i; iCol++) {
      loop_ub = b_c.size(0);
      c[0] = b_c.size(0);
      c_tmp = b_c.size(1) * b_c.size(2);
      if ((static_cast<int>(static_cast<unsigned int>(iCol) + 1U) < 1) ||
          (static_cast<int>(static_cast<unsigned int>(iCol) + 1U) > c_tmp)) {
        rtDynamicBoundsError(
            static_cast<int>(static_cast<unsigned int>(iCol) + 1U), 1, c_tmp,
            k_emlrtBCI);
      }
      b_x.set_size(b_c.size(0));
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_x[i1] = b_c[i1 + c[0] * iCol];
      }
      if (!(varargin_7 >= 1.0)) {
        b_rtErrorWithMessageID(1, kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
      }
      if (b_c.size(0) == 1) {
        wrappedData.set_size(1, csz_idx_0);
        for (i1 = 0; i1 < csz_idx_0; i1++) {
          wrappedData[i1].re = 0.0;
          wrappedData[i1].im = 0.0;
        }
      } else {
        wrappedData.set_size(csz_idx_0, 1);
        for (i1 = 0; i1 < csz_idx_0; i1++) {
          wrappedData[i1].re = 0.0;
          wrappedData[i1].im = 0.0;
        }
      }
      i1 = static_cast<int>(static_cast<unsigned int>(b_c.size(0)) /
                            static_cast<unsigned int>(varargin_7));
      bcoef = i1 * csz_idx_0;
      b_bcoef = b_c.size(0) - bcoef;
      if (b_bcoef > 2147483646) {
        check_forloop_overflow_error();
      }
      for (k = 0; k < b_bcoef; k++) {
        i2 = wrappedData.size(0) * wrappedData.size(1);
        if ((k + 1 < 1) || (k + 1 > i2)) {
          rtDynamicBoundsError(k + 1, 1, i2, n_emlrtBCI);
        }
        i3 = (bcoef + k) + 1;
        useRadix2 = ((i3 < 1) || (i3 > b_c.size(0)));
        if (useRadix2) {
          rtDynamicBoundsError(i3, 1, b_c.size(0), m_emlrtBCI);
        }
        wrappedData[k].re = b_x[i3 - 1].re;
        if (k + 1 > i2) {
          rtDynamicBoundsError(k + 1, 1, i2, n_emlrtBCI);
        }
        wrappedData[k].im = b_x[i3 - 1].im;
      }
      i2 = b_bcoef + 1;
      for (k = i2; k <= csz_idx_0; k++) {
        i3 = wrappedData.size(0) * wrappedData.size(1);
        if ((k < 1) || (k > i3)) {
          rtDynamicBoundsError(k, 1, i3, o_emlrtBCI);
        }
        wrappedData[k - 1].re = 0.0;
        if (k > i3) {
          rtDynamicBoundsError(k, 1, i3, o_emlrtBCI);
        }
        wrappedData[k - 1].im = 0.0;
      }
      if (i1 > 2147483646) {
        check_forloop_overflow_error();
      }
      for (loop_ub = 0; loop_ub < i1; loop_ub++) {
        bcoef = loop_ub * csz_idx_0;
        for (k = 0; k < csz_idx_0; k++) {
          i2 = wrappedData.size(0) * wrappedData.size(1);
          if (k + 1 > i2) {
            rtDynamicBoundsError(k + 1, 1, i2, r_emlrtBCI);
          }
          i3 = (bcoef + k) + 1;
          useRadix2 = ((i3 < 1) || (i3 > b_c.size(0)));
          if (useRadix2) {
            rtDynamicBoundsError(i3, 1, b_c.size(0), q_emlrtBCI);
          }
          wrappedData[k].re = wrappedData[k].re + b_x[i3 - 1].re;
          if (k + 1 > i2) {
            rtDynamicBoundsError(k + 1, 1, i2, p_emlrtBCI);
          }
          wrappedData[k].im = wrappedData[k].im + b_x[i3 - 1].im;
        }
      }
      if ((iCol + 1 < 1) || (iCol + 1 > c_tmp)) {
        rtDynamicBoundsError(iCol + 1, 1, c_tmp, l_emlrtBCI);
      }
      bcoef = wrappedData.size(0) * wrappedData.size(1);
      rtSubAssignSizeCheck(xin.size(), 1, &bcoef, 1, d_emlrtECI);
      c[0] = xin.size(0);
      for (i1 = 0; i1 < bcoef; i1++) {
        xin[i1 + c[0] * iCol] = wrappedData[i1];
      }
    }
  } else {
    xin.set_size(b_c.size(0), b_c.size(1), b_c.size(2));
    loop_ub = b_c.size(0) * b_c.size(1) * b_c.size(2);
    for (i = 0; i < loop_ub; i++) {
      xin[i] = b_c[i];
    }
  }
  if (xin.size(0) == 1) {
    w_rtErrorWithMessageID(hb_emlrtRTEI.fName, hb_emlrtRTEI.lineNo);
  }
  if ((!(varargin_7 >= 0.0)) || (!(varargin_7 == std::floor(varargin_7)))) {
    x_rtErrorWithMessageID(ib_emlrtRTEI.fName, ib_emlrtRTEI.lineNo);
  }
  if (!(varargin_7 <= 2.147483647E+9)) {
    y_rtErrorWithMessageID(jb_emlrtRTEI.fName, jb_emlrtRTEI.lineNo);
  }
  if ((xin.size(0) == 0) || (xin.size(1) == 0) ||
      (static_cast<int>(varargin_7) == 0)) {
    varargout_1.set_size(static_cast<int>(varargin_7), xin.size(1),
                         xin.size(2));
    loop_ub = static_cast<int>(varargin_7) * xin.size(1) * xin.size(2);
    for (i = 0; i < loop_ub; i++) {
      varargout_1[i].re = 0.0;
      varargout_1[i].im = 0.0;
    }
  } else {
    useRadix2 = ((static_cast<int>(varargin_7) > 0) &&
                 ((static_cast<int>(varargin_7) &
                   (static_cast<int>(varargin_7) - 1)) == 0));
    bcoef = internal::fft::FFTImplementationCallback::get_algo_sizes(
        static_cast<int>(varargin_7), useRadix2, b_bcoef);
    internal::fft::FFTImplementationCallback::generate_twiddle_tables(
        b_bcoef, useRadix2, costab, sintab, sintabinv);
    if (useRadix2) {
      internal::fft::FFTImplementationCallback::r2br_r2dit_trig(
          xin, static_cast<int>(varargin_7), costab, sintab, varargout_1);
    } else {
      internal::fft::FFTImplementationCallback::dobluesteinfft(
          xin, bcoef, static_cast<int>(varargin_7), costab, sintab, sintabinv,
          varargout_1);
    }
  }
  psdfreqvec(varargin_7, varargin_1, f);
  b_signal::internal::stft::formatSTFTOutput(varargout_1, f, b_f);
  if (varargout_1.size(0) < 1) {
    loop_ub = 0;
  } else {
    if (b_f.size(0) < 1) {
      rtDynamicBoundsError(1, 1, b_f.size(0), j_emlrtBCI);
    }
    if (varargout_1.size(0) > b_f.size(0)) {
      rtDynamicBoundsError(varargout_1.size(0), 1, b_f.size(0), i_emlrtBCI);
    }
    loop_ub = varargout_1.size(0);
  }
  c[0] = 1;
  c[1] = loop_ub;
  internal::indexShapeCheck(b_f.size(0), c);
  varargout_2.set_size(loop_ub);
  for (i = 0; i < loop_ub; i++) {
    varargout_2[i] = b_f[i];
  }
  if (varargout_1.size(1) < 1) {
    loop_ub = 0;
  } else {
    if (y.size(1) < 1) {
      rtDynamicBoundsError(1, 1, y.size(1), h_emlrtBCI);
    }
    if (varargout_1.size(1) > y.size(1)) {
      rtDynamicBoundsError(varargout_1.size(1), 1, y.size(1), g_emlrtBCI);
    }
    loop_ub = varargout_1.size(1);
  }
  varargout_3.set_size(loop_ub);
  for (i = 0; i < loop_ub; i++) {
    varargout_3[i] = y[i];
  }
}

} // namespace coder

//
// File trailer for stft.cpp
//
// [EOF]
//
