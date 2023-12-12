//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fwrite.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "fwrite.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdio>

// Function Definitions
//
// Arguments    : double fileID
//                const array<float, 1U> &x
// Return Type  : double
//
namespace coder {
double b_fwrite(double fileID, const array<float, 1U> &x)
{
  static rtRunTimeErrorInfo
      bd_emlrtRTEI{
          163,           // lineNo
          5,             // colNo
          "getFileStar", // fName
          "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/iofun/"
          "fwrite.m" // pName
      };
  static rtRunTimeErrorInfo
      cd_emlrtRTEI{
          33,       // lineNo
          5,        // colNo
          "fwrite", // fName
          "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/iofun/"
          "fwrite.m" // pName
      };
  std::FILE *f;
  std::FILE *filestar;
  double count;
  boolean_T autoflush;
  if (!(fileID != 0.0)) {
    g_rtErrorWithMessageID(cd_emlrtRTEI.fName, cd_emlrtRTEI.lineNo);
  }
  f = internal::getfilestar(fileID, autoflush);
  filestar = f;
  if (f == nullptr) {
    c_rtErrorWithMessageID(bd_emlrtRTEI.fName, bd_emlrtRTEI.lineNo);
  }
  if ((filestar == nullptr) || (x.size(0) == 0)) {
    count = 0.0;
  } else {
    size_t bytesOutSizet;
    bytesOutSizet = std::fwrite(&(((array<float, 1U> *)&x)->data())[0],
                                sizeof(float), (size_t)x.size(0), filestar);
    count = (double)bytesOutSizet;
    if (((double)bytesOutSizet > 0.0) && autoflush) {
      int status;
      status = std::fflush(filestar);
      if (status != 0) {
        count = 0.0;
      }
    }
  }
  return count;
}

} // namespace coder

//
// File trailer for fwrite.cpp
//
// [EOF]
//
