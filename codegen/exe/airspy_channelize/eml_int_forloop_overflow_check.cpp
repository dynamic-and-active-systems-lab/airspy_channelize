//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: eml_int_forloop_overflow_check.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Apr-2023 16:55:28
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

// Variable Definitions
static rtRunTimeErrorInfo o_emlrtRTEI{
    87,                            // lineNo
    "check_forloop_overflow_error" // fName
};

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
void b_check_forloop_overflow_error()
{
  d_rtErrorWithMessageID("int32", o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
}

//
// Arguments    : void
// Return Type  : void
//
void check_forloop_overflow_error()
{
  d_rtErrorWithMessageID("uint32", o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
}

} // namespace coder

//
// File trailer for eml_int_forloop_overflow_check.cpp
//
// [EOF]
//
