//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: getLocalTime.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Apr-2023 16:55:28
//

// Include Files
#include "getLocalTime.h"
#include "airspy_channelize_data.h"
#include "airspy_channelize_rtwutil.h"
#include "airspy_channelize_types.h"
#include "rt_nonfinite.h"
#include "coder_posix_time.h"
#include <string>

// Function Definitions
//
// Arguments    : double *t_tm_nsec
//                double *t_tm_sec
//                double *t_tm_min
//                double *t_tm_hour
//                double *t_tm_mday
//                double *t_tm_mon
//                double *t_tm_year
//                boolean_T *t_tm_isdst
// Return Type  : void
//
namespace coder {
namespace internal {
namespace time {
void getLocalTime(double *t_tm_nsec, double *t_tm_sec, double *t_tm_min,
                  double *t_tm_hour, double *t_tm_mday, double *t_tm_mon,
                  double *t_tm_year, boolean_T *t_tm_isdst)
{
  static const char fcn[14]{'c', 'o', 'd', 'e', 'r', 'L', 'o',
                            'c', 'a', 'l', 'T', 'i', 'm', 'e'};
  coderTm structTm;
  int status;
  status = coderLocalTime(&structTm);
  if (status != 0) {
    rtErrorWithMessageID(std::string(&fcn[0], 14), status, l_emlrtRTEI.fName,
                         l_emlrtRTEI.lineNo);
  }
  *t_tm_nsec = (double)structTm.tm_nsec;
  *t_tm_sec = structTm.tm_sec;
  *t_tm_min = structTm.tm_min;
  *t_tm_hour = structTm.tm_hour;
  *t_tm_mday = structTm.tm_mday;
  *t_tm_mon = structTm.tm_mon;
  *t_tm_year = structTm.tm_year;
  *t_tm_isdst = (structTm.tm_isdst != 0);
}

} // namespace time
} // namespace internal
} // namespace coder

//
// File trailer for getLocalTime.cpp
//
// [EOF]
//
