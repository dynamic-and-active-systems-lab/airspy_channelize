//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: eml_int_forloop_overflow_check.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 28-Mar-2023 15:24:09
//

// Include Files
#include "eml_int_forloop_overflow_check.h"
#include "airspy_channelize_types.h"
#include "rt_nonfinite.h"
#include "omp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
static void d_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

// Function Definitions
//
// Arguments    : const char *r
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void d_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "The loop variable of class ") << r)
      << " might overflow on the last iteration of the for loop. This could "
         "lead to an infinite loop.";
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
void check_forloop_overflow_error()
{
  static rtRunTimeErrorInfo i_emlrtRTEI{
      87,                            // lineNo
      "check_forloop_overflow_error" // fName
  };
  d_rtErrorWithMessageID("uint32", i_emlrtRTEI.fName, i_emlrtRTEI.lineNo);
}

} // namespace coder

//
// File trailer for eml_int_forloop_overflow_check.cpp
//
// [EOF]
//
