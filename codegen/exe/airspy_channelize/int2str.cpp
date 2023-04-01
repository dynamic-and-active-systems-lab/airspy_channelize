//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: int2str.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Apr-2023 16:45:43
//

// Include Files
#include "int2str.h"
#include "airspy_channelize_rtwutil.h"
#include "airspy_channelize_types.h"
#include "rt_nonfinite.h"
#include "omp.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo i_emlrtRTEI{
    41,           // lineNo
    "callSprintf" // fName
};

static rtRunTimeErrorInfo j_emlrtRTEI{
    42,           // lineNo
    "callSprintf" // fName
};

static rtRunTimeErrorInfo k_emlrtRTEI{
    43,           // lineNo
    "callSprintf" // fName
};

// Function Declarations
static void rtErrorWithMessageID(const int i, const char *aFcnName,
                                 int aLineNum);

// Function Definitions
//
// Arguments    : const int i
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void rtErrorWithMessageID(const int i, const char *aFcnName,
                                 int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "Call to C sprintf failed with status ") << i) << ".";
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
// Arguments    : double xin
//                char s_data[]
//                int s_size[2]
// Return Type  : void
//
namespace coder {
void int2str(double xin, char s_data[], int s_size[2])
{
  char st[311];
  if (xin == 0.0) {
    s_size[0] = 1;
    s_size[1] = 1;
    s_data[0] = '0';
  } else if (std::isinf(xin)) {
    s_size[0] = 1;
    s_size[1] = 3;
    s_data[0] = 'I';
    s_data[1] = 'n';
    s_data[2] = 'f';
  } else if (std::isnan(xin)) {
    s_size[0] = 1;
    s_size[1] = 3;
    s_data[0] = 'N';
    s_data[1] = 'a';
    s_data[2] = 'N';
  } else {
    int resCount;
    resCount = sprintf(&st[0], "%.0f", xin);
    if (resCount < 0) {
      rtErrorWithMessageID(resCount, i_emlrtRTEI.fName, i_emlrtRTEI.lineNo);
    }
    if (resCount > 310) {
      c_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
    }
    if (resCount >
        static_cast<int>(std::floor(std::log10(std::abs(xin))) + 1.0)) {
      c_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
    }
    s_size[0] = 1;
    s_size[1] = resCount;
    if (resCount - 1 >= 0) {
      std::copy(&st[0], &st[resCount], &s_data[0]);
    }
  }
}

//
// Arguments    : int xin
//                char s_data[]
//                int s_size[2]
// Return Type  : void
//
void int2str(int xin, char s_data[], int s_size[2])
{
  double b_xin;
  int resCount;
  char st[12];
  resCount = sprintf(&st[0], "%d", xin);
  if (resCount < 0) {
    rtErrorWithMessageID(resCount, i_emlrtRTEI.fName, i_emlrtRTEI.lineNo);
  }
  if (resCount > 11) {
    c_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
  }
  if (xin == 0) {
    b_xin = 1.0;
  } else {
    b_xin = std::floor(std::log10(std::abs(static_cast<double>(xin)))) + 1.0;
  }
  if (resCount > static_cast<int>(b_xin)) {
    c_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
  }
  s_size[0] = 1;
  s_size[1] = resCount;
  if (resCount - 1 >= 0) {
    std::copy(&st[0], &st[resCount], &s_data[0]);
  }
}

} // namespace coder

//
// File trailer for int2str.cpp
//
// [EOF]
//
