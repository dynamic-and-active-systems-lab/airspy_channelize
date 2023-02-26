//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: validator_check_size.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 26-Feb-2023 09:39:03
//

// Include Files
#include "validator_check_size.h"
#include "airspy_channelize_data.h"
#include "airspy_channelize_rtwutil.h"
#include "airspy_channelize_types.h"
#include "int2str.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "omp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
static void h_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void h_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "Number of elements must not change. Use [] as one of the size inputs "
         "to automatically calculate the appropriate size for that di"
         "mension.";
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
// Arguments    : const ::coder::array<int, 2U> &in
//                ::coder::array<int, 2U> &out
// Return Type  : void
//
namespace coder {
namespace internal {
void validator_check_size(const ::coder::array<int, 2U> &in,
                          ::coder::array<int, 2U> &out)
{
  static rtRunTimeErrorInfo o_emlrtRTEI{
      143,                   // lineNo
      "validator_check_size" // fName
  };
  int sizes_idx_1;
  char b_tmp_data[10];
  char tmp_data[10];
  boolean_T b;
  boolean_T b1;
  b = (in.size(1) == 1);
  b1 = (in.size(1) == 0);
  if (b) {
    sizes_idx_1 = 1;
  } else {
    sizes_idx_1 = in.size(1);
  }
  if ((!b1) && (!b) && (in.size(1) != sizes_idx_1)) {
    int b_tmp_size[2];
    int tmp_size[2];
    int2str(static_cast<double>(in.size(1)), tmp_data, tmp_size);
    int2str(sizes_idx_1, b_tmp_data, b_tmp_size);
    rtErrorWithMessageID(std::string(&tmp_data[0], tmp_size[1]),
                         std::string(&b_tmp_data[0], b_tmp_size[1]), "2",
                         h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
  }
  if (b) {
    out.set_size(1, sizes_idx_1);
    for (int u1{0}; u1 < sizes_idx_1; u1++) {
      out[u1] = in[0];
    }
  } else if (b1) {
    if (sizes_idx_1 != 0) {
      h_rtErrorWithMessageID(o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
    }
    out.set_size(1, 0);
  } else {
    int u0;
    int u1;
    u1 = 1;
    if (in.size(1) > 1) {
      u1 = in.size(1);
    }
    u0 = in.size(1);
    if (u0 >= u1) {
      u1 = u0;
    }
    if (sizes_idx_1 > u1) {
      f_rtErrorWithMessageID(f_emlrtRTEI.fName, f_emlrtRTEI.lineNo);
    }
    if (sizes_idx_1 != in.size(1)) {
      g_rtErrorWithMessageID(g_emlrtRTEI.fName, g_emlrtRTEI.lineNo);
    }
    out.set_size(1, sizes_idx_1);
    for (u1 = 0; u1 < sizes_idx_1; u1++) {
      out[u1] = in[u1];
    }
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for validator_check_size.cpp
//
// [EOF]
//
