//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: datetime.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Apr-2023 16:55:28
//

// Include Files
#include "datetime.h"
#include "airspy_channelize_types.h"
#include "getLocalTime.h"
#include "plus.h"
#include "rt_nonfinite.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
static void i_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void i_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Year, month, day, hour, minute, and second components must be "
               "integer values when milliseconds is specified.";
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
// Arguments    : void
// Return Type  : void
//
namespace coder {
void datetime::init()
{
  static rtRunTimeErrorInfo p_emlrtRTEI{
      1,                  // lineNo
      "createFromDateVec" // fName
  };
  double b_second;
  double c_tm_hour;
  double c_tm_min;
  double c_tm_mon;
  double c_tm_year;
  double check;
  double fracSecs;
  double shi;
  boolean_T expl_temp;
  internal::time::getLocalTime(&check, &b_second, &c_tm_min, &c_tm_hour, &shi,
                               &c_tm_mon, &c_tm_year, &expl_temp);
  fracSecs = check / 1.0E+6;
  check =
      (((((c_tm_year + c_tm_mon) + shi) + c_tm_hour) + c_tm_min) + b_second) +
      fracSecs;
  if ((!std::isinf(check)) && (!std::isnan(check))) {
    creal_T ahi;
    double wholeSecsFromMillis;
    if ((!(c_tm_year == c_tm_year)) || (!(c_tm_mon == c_tm_mon)) ||
        (!(shi == shi)) || (!(c_tm_hour == c_tm_hour)) ||
        (!(c_tm_min == c_tm_min))) {
      i_rtErrorWithMessageID(p_emlrtRTEI.fName, p_emlrtRTEI.lineNo);
    }
    if (b_second != b_second) {
      i_rtErrorWithMessageID(p_emlrtRTEI.fName, p_emlrtRTEI.lineNo);
    }
    if ((c_tm_mon < 1.0) || (c_tm_mon > 12.0)) {
      wholeSecsFromMillis = std::floor((c_tm_mon - 1.0) / 12.0);
      c_tm_year += wholeSecsFromMillis;
      c_tm_mon = ((c_tm_mon - 1.0) - wholeSecsFromMillis * 12.0) + 1.0;
    }
    if (c_tm_mon < 3.0) {
      c_tm_year--;
      c_tm_mon += 9.0;
    } else {
      c_tm_mon -= 3.0;
    }
    wholeSecsFromMillis =
        ((((((365.0 * c_tm_year + std::floor(c_tm_year / 4.0)) -
             std::floor(c_tm_year / 100.0)) +
            std::floor(c_tm_year / 400.0)) +
           std::floor((153.0 * c_tm_mon + 2.0) / 5.0)) +
          shi) +
         60.0) -
        719529.0;
    check = 1.34217729E+8 * wholeSecsFromMillis;
    check -= check - wholeSecsFromMillis;
    shi = wholeSecsFromMillis * 8.64E+7;
    check = (wholeSecsFromMillis - check) * 8.64E+7 + (check * 8.64E+7 - shi);
    if (std::isnan(check)) {
      check = 0.0;
    }
    if ((fracSecs < 0.0) || (fracSecs >= 1000.0)) {
      wholeSecsFromMillis = std::floor(fracSecs / 1000.0);
      b_second += wholeSecsFromMillis;
      fracSecs -= wholeSecsFromMillis * 1000.0;
    }
    ahi.re = shi;
    ahi.im = check;
    data = matlab::internal::coder::doubledouble::plus(
        matlab::internal::coder::doubledouble::plus(
            matlab::internal::coder::doubledouble::plus(
                ahi, (60.0 * c_tm_hour + c_tm_min) * 60000.0),
            b_second * 1000.0),
        fracSecs);
  } else {
    data.re = check;
    data.im = 0.0;
  }
}

} // namespace coder

//
// File trailer for datetime.cpp
//
// [EOF]
//
