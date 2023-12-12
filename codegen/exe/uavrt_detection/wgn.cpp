//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: wgn.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "wgn.h"
#include "randn.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Variable Definitions
static const char cv[128]{
    '\x00', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\a',   '\b',
    '\t',   '\n',   '\v',   '\f',   '\r',   '\x0e', '\x0f', '\x10', '\x11',
    '\x12', '\x13', '\x14', '\x15', '\x16', '\x17', '\x18', '\x19', '\x1a',
    '\x1b', '\x1c', '\x1d', '\x1e', '\x1f', ' ',    '!',    '\"',   '#',
    '$',    '%',    '&',    '\'',   '(',    ')',    '*',    '+',    ',',
    '-',    '.',    '/',    '0',    '1',    '2',    '3',    '4',    '5',
    '6',    '7',    '8',    '9',    ':',    ';',    '<',    '=',    '>',
    '?',    '@',    'a',    'b',    'c',    'd',    'e',    'f',    'g',
    'h',    'i',    'j',    'k',    'l',    'm',    'n',    'o',    'p',
    'q',    'r',    's',    't',    'u',    'v',    'w',    'x',    'y',
    'z',    '[',    '\\',   ']',    '^',    '_',    '`',    'a',    'b',
    'c',    'd',    'e',    'f',    'g',    'h',    'i',    'j',    'k',
    'l',    'm',    'n',    'o',    'p',    'q',    'r',    's',    't',
    'u',    'v',    'w',    'x',    'y',    'z',    '{',    '|',    '}',
    '~',    '\x7f'};

// Function Declarations
static void sb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void sb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "The required dimensions must be real, integer scalars > 1.";
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
// Arguments    : creal_T y[1000]
// Return Type  : void
//
namespace coder {
void wgn(creal_T y[1000])
{
  static const char b_cv1[7]{'c', 'o', 'm', 'p', 'l', 'e', 'x'};
  static const char a[6]{'l', 'i', 'n', 'e', 'a', 'r'};
  static const char b_cv[6]{'l', 'i', 'n', 'e', 'a', 'r'};
  double noisePower;
  int i;
  char a_data[7];
  char switch_expression_data[6];
  boolean_T result;
  for (i = 0; i < 6; i++) {
    switch_expression_data[i] = cv[static_cast<int>(a[i])];
  }
  result = false;
  i = 0;
  int exitg1;
  do {
    exitg1 = 0;
    if (i < 6) {
      if (b_cv[i] != switch_expression_data[i]) {
        exitg1 = 1;
      } else {
        i++;
      }
    } else {
      result = true;
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  if (result) {
    i = 0;
  } else {
    i = -1;
  }
  if (i == 0) {
    noisePower = 1.0;
  } else {
    noisePower = 0.0012589254117941675;
  }
  for (i = 0; i < 7; i++) {
    a_data[i] = b_cv1[i];
  }
  if (cv[static_cast<int>(a_data[0])] == 'r') {
    double b[1000];
    noisePower = std::sqrt(noisePower);
    randn(b);
    for (i = 0; i < 1000; i++) {
      y[i].re = noisePower * b[i];
      y[i].im = 0.0;
    }
  } else {
    noisePower = std::sqrt(noisePower);
    complexLike(y);
    for (i = 0; i < 1000; i++) {
      y[i].re *= noisePower;
      y[i].im *= noisePower;
    }
  }
}

//
// Arguments    : double varargin_1
//                unsigned int varargin_2
//                double varargin_3
//                array<creal_T, 2U> &y
// Return Type  : void
//
void wgn(double varargin_1, unsigned int varargin_2, double varargin_3,
         array<creal_T, 2U> &y)
{
  static rtRunTimeErrorInfo bd_emlrtRTEI{
      180,                                                      // lineNo
      1,                                                        // colNo
      "wgn",                                                    // fName
      "/Applications/MATLAB_R2023b.app/toolbox/comm/comm/wgn.m" // pName
  };
  static const char b_cv1[7]{'c', 'o', 'm', 'p', 'l', 'e', 'x'};
  static const char a[6]{'l', 'i', 'n', 'e', 'a', 'r'};
  static const char b_cv[6]{'l', 'i', 'n', 'e', 'a', 'r'};
  array<double, 2U> b;
  double noisePower;
  int i;
  int k;
  char a_data[7];
  char switch_expression_data[6];
  boolean_T x[6];
  boolean_T b_y;
  boolean_T exitg1;
  x[0] = (varargin_1 <= 0.0);
  x[1] = (varargin_2 <= 0U);
  x[2] = false;
  x[3] = false;
  x[4] = (varargin_1 - std::floor(varargin_1) != 0.0);
  x[5] = false;
  b_y = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 6)) {
    if (x[k]) {
      b_y = true;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (b_y) {
    sb_rtErrorWithMessageID(bd_emlrtRTEI.fName, bd_emlrtRTEI.lineNo);
  }
  for (k = 0; k < 6; k++) {
    switch_expression_data[k] = cv[static_cast<int>(a[k])];
  }
  b_y = false;
  k = 0;
  int exitg2;
  do {
    exitg2 = 0;
    if (k < 6) {
      if (b_cv[k] != switch_expression_data[k]) {
        exitg2 = 1;
      } else {
        k++;
      }
    } else {
      b_y = true;
      exitg2 = 1;
    }
  } while (exitg2 == 0);
  if (b_y) {
    i = 0;
  } else {
    i = -1;
  }
  if (i == 0) {
    noisePower = varargin_3;
  } else {
    noisePower = rt_powd_snf(10.0, (varargin_3 - 30.0) / 10.0);
  }
  for (i = 0; i < 7; i++) {
    a_data[i] = b_cv1[i];
  }
  if (cv[static_cast<int>(a_data[0])] == 'r') {
    if (noisePower < 0.0) {
      rtErrorWithMessageID("sqrt", ec_emlrtRTEI.fName, ec_emlrtRTEI.lineNo);
    }
    noisePower = std::sqrt(noisePower);
    randn(varargin_1, varargin_2, b);
    y.set_size(b.size(0), b.size(1));
    k = b.size(0) * b.size(1);
    for (i = 0; i < k; i++) {
      y[i].re = noisePower * b[i];
      y[i].im = 0.0;
    }
  } else {
    if (noisePower < 0.0) {
      rtErrorWithMessageID("sqrt", ec_emlrtRTEI.fName, ec_emlrtRTEI.lineNo);
    }
    noisePower = std::sqrt(noisePower);
    complexLike(varargin_1, varargin_2, y);
    k = y.size(0) * y.size(1);
    for (i = 0; i < k; i++) {
      y[i].re = noisePower * y[i].re;
      y[i].im = noisePower * y[i].im;
    }
  }
}

} // namespace coder

//
// File trailer for wgn.cpp
//
// [EOF]
//
