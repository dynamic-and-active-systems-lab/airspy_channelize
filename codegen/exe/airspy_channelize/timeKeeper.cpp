//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: timeKeeper.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Apr-2023 16:55:28
//

// Include Files
#include "timeKeeper.h"
#include "airspy_channelize_data.h"
#include "airspy_channelize_rtwutil.h"
#include "airspy_channelize_types.h"
#include "rt_nonfinite.h"
#include "coder_posix_time.h"
#include "omp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Variable Definitions
static coderTimespec savedTime;

static boolean_T savedTime_not_empty;

// Function Declarations
static void j_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void j_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "You must call TIC without an output argument before calling "
               "TOC without an input argument.";
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
// Arguments    : double newTime_tv_sec
//                double newTime_tv_nsec
// Return Type  : void
//
namespace coder {
namespace internal {
namespace time {
namespace impl {
void timeKeeper(double newTime_tv_sec, double newTime_tv_nsec)
{
  if (!savedTime_not_empty) {
    coderTimespec b_timespec;
    int status;
    if (!freq_not_empty) {
      freq_not_empty = true;
      status = coderInitTimeFunctions(&freq);
      if (status != 0) {
        rtErrorWithMessageID(std::string(&cv[0], 22), status, l_emlrtRTEI.fName,
                             l_emlrtRTEI.lineNo);
      }
    }
    status = coderTimeClockGettimeMonotonic(&b_timespec, freq);
    if (status != 0) {
      rtErrorWithMessageID(std::string(&cv1[0], 30), status, l_emlrtRTEI.fName,
                           l_emlrtRTEI.lineNo);
    }
    savedTime = b_timespec;
    savedTime_not_empty = true;
  }
  savedTime.tv_sec = newTime_tv_sec;
  savedTime.tv_nsec = newTime_tv_nsec;
}

//
// Arguments    : double *outTime_tv_sec
//                double *outTime_tv_nsec
// Return Type  : void
//
void timeKeeper(double *outTime_tv_sec, double *outTime_tv_nsec)
{
  static rtRunTimeErrorInfo p_emlrtRTEI{
      11,          // lineNo
      "timeKeeper" // fName
  };
  if (!savedTime_not_empty) {
    j_rtErrorWithMessageID(p_emlrtRTEI.fName, p_emlrtRTEI.lineNo);
  }
  *outTime_tv_sec = savedTime.tv_sec;
  *outTime_tv_nsec = savedTime.tv_nsec;
}

//
// Arguments    : void
// Return Type  : void
//
} // namespace impl
} // namespace time
} // namespace internal
} // namespace coder
void savedTime_not_empty_init()
{
  savedTime_not_empty = false;
}

//
// File trailer for timeKeeper.cpp
//
// [EOF]
//
