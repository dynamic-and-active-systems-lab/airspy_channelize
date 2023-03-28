//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: toc.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 28-Mar-2023 15:24:09
//

// Include Files
#include "toc.h"
#include "airspy_channelize_data.h"
#include "airspy_channelize_rtwutil.h"
#include "airspy_channelize_types.h"
#include "rt_nonfinite.h"
#include "timeKeeper.h"
#include "coder_posix_time.h"
#include <string>

// Function Definitions
//
// Arguments    : void
// Return Type  : double
//
namespace coder {
double toc()
{
  coderTimespec b_timespec;
  double tstart_tv_nsec;
  double tstart_tv_sec;
  int status;
  tstart_tv_sec = internal::b_time::impl::timeKeeper(tstart_tv_nsec);
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
  return (b_timespec.tv_sec - tstart_tv_sec) +
         (b_timespec.tv_nsec - tstart_tv_nsec) / 1.0E+9;
}

} // namespace coder

//
// File trailer for toc.cpp
//
// [EOF]
//
