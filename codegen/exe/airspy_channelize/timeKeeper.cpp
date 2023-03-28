//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: timeKeeper.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 28-Mar-2023 15:24:09
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
static void g_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void g_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
// Arguments    : double &outTime_tv_nsec
// Return Type  : double
//
namespace coder {
namespace internal {
namespace b_time {
namespace impl {
double timeKeeper(double &outTime_tv_nsec)
{
  static rtRunTimeErrorInfo i_emlrtRTEI{
      11,          // lineNo
      "timeKeeper" // fName
  };
  double outTime_tv_sec;
  if (!savedTime_not_empty) {
    g_rtErrorWithMessageID(i_emlrtRTEI.fName, i_emlrtRTEI.lineNo);
  }
  outTime_tv_sec = savedTime.tv_sec;
  outTime_tv_nsec = savedTime.tv_nsec;
  return outTime_tv_sec;
}

//
// Arguments    : double newTime_tv_sec
//                double newTime_tv_nsec
// Return Type  : void
//
void timeKeeper(double newTime_tv_sec, double newTime_tv_nsec)
{
  if (!savedTime_not_empty) {
    coderTimespec b_timespec;
    int status;
    if (!freq_not_empty) {
      freq_not_empty = true;
      status = coderInitTimeFunctions(&freq);
      if (status != 0) {
        rtErrorWithMessageID(std::string(&cv[0], 22), status, f_emlrtRTEI.fName,
                             f_emlrtRTEI.lineNo);
      }
    }
    status = coderTimeClockGettimeMonotonic(&b_timespec, freq);
    if (status != 0) {
      rtErrorWithMessageID(std::string(&cv1[0], 30), status, f_emlrtRTEI.fName,
                           f_emlrtRTEI.lineNo);
    }
    savedTime_not_empty = true;
  }
  savedTime.tv_sec = newTime_tv_sec;
  savedTime.tv_nsec = newTime_tv_nsec;
}

//
// Arguments    : void
// Return Type  : void
//
} // namespace impl
} // namespace b_time
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
