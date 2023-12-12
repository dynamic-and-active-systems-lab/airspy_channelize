//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sub2ind.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "sub2ind.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo
    qc_emlrtRTEI{
        18,        // lineNo
        23,        // colNo
        "sub2ind", // fName
        "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
        "sub2ind.m" // pName
    };

// Function Declarations
namespace coder {
namespace internal {
static boolean_T allinrange(const array<double, 2U> &x, int hi);

}
} // namespace coder
static void ic_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const array<double, 2U> &x
//                int hi
// Return Type  : boolean_T
//
namespace coder {
namespace internal {
static boolean_T allinrange(const array<double, 2U> &x, int hi)
{
  int i;
  int k;
  boolean_T p;
  i = x.size(0) * x.size(1);
  k = 0;
  int exitg1;
  do {
    exitg1 = 0;
    if (k <= i - 1) {
      if ((x[k] >= 1.0) && (x[k] <= hi)) {
        k++;
      } else {
        p = false;
        exitg1 = 1;
      }
    } else {
      p = true;
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  return p;
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
} // namespace internal
} // namespace coder
static void ic_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "The subscript vectors must all be of the same size.";
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
// Arguments    : const int siz[2]
//                const array<double, 2U> &varargin_1
//                const array<double, 2U> &varargin_2
//                array<int, 2U> &idx
// Return Type  : void
//
namespace coder {
namespace internal {
void b_sub2ind(const int siz[2], const array<double, 2U> &varargin_1,
               const array<double, 2U> &varargin_2, array<int, 2U> &idx)
{
  unsigned int b_varargin_1[2];
  unsigned int b_varargin_2[2];
  int k;
  boolean_T exitg1;
  boolean_T p;
  if (!allinrange(varargin_1, siz[0])) {
    hc_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  }
  b_varargin_1[0] = static_cast<unsigned int>(varargin_1.size(0));
  b_varargin_2[0] = static_cast<unsigned int>(varargin_2.size(0));
  b_varargin_1[1] = static_cast<unsigned int>(varargin_1.size(1));
  b_varargin_2[1] = static_cast<unsigned int>(varargin_2.size(1));
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 2)) {
    if (static_cast<int>(b_varargin_1[k]) !=
        static_cast<int>(b_varargin_2[k])) {
      p = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (!p) {
    ic_rtErrorWithMessageID(qc_emlrtRTEI.fName, qc_emlrtRTEI.lineNo);
  }
  if (!allinrange(varargin_2, siz[1])) {
    hc_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  }
  idx.set_size(varargin_1.size(0), varargin_1.size(1));
  k = varargin_1.size(0) * varargin_1.size(1);
  for (int i{0}; i < k; i++) {
    idx[i] = static_cast<int>(varargin_1[i]) +
             siz[0] * (static_cast<int>(varargin_2[i]) - 1);
  }
}

//
// Arguments    : const int siz[2]
//                const array<double, 2U> &varargin_1
//                const array<double, 2U> &varargin_2
//                array<int, 2U> &idx
// Return Type  : void
//
void sub2ind(const int siz[2], const array<double, 2U> &varargin_1,
             const array<double, 2U> &varargin_2, array<int, 2U> &idx)
{
  unsigned int b_varargin_1[2];
  unsigned int b_varargin_2[2];
  int k;
  boolean_T exitg1;
  boolean_T p;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= varargin_1.size(1) - 1)) {
    if ((varargin_1[k] >= 1.0) && (varargin_1[k] <= siz[0])) {
      k++;
    } else {
      hc_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
    }
  }
  b_varargin_1[0] = 1U;
  b_varargin_2[0] = 1U;
  b_varargin_1[1] = static_cast<unsigned int>(varargin_1.size(1));
  b_varargin_2[1] = static_cast<unsigned int>(varargin_2.size(1));
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 2)) {
    if (static_cast<int>(b_varargin_1[k]) !=
        static_cast<int>(b_varargin_2[k])) {
      p = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (!p) {
    ic_rtErrorWithMessageID(qc_emlrtRTEI.fName, qc_emlrtRTEI.lineNo);
  }
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= varargin_2.size(1) - 1)) {
    if ((varargin_2[k] >= 1.0) && (varargin_2[k] <= siz[1])) {
      k++;
    } else {
      hc_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
    }
  }
  idx.set_size(1, varargin_1.size(1));
  k = varargin_1.size(1);
  for (int i{0}; i < k; i++) {
    idx[i] = static_cast<int>(varargin_1[i]) +
             siz[0] * (static_cast<int>(varargin_2[i]) - 1);
  }
}

//
// Arguments    : const int siz[2]
//                const array<double, 1U> &varargin_1
//                const array<double, 1U> &varargin_2
//                array<int, 1U> &idx
// Return Type  : void
//
void sub2ind(const int siz[2], const array<double, 1U> &varargin_1,
             const array<double, 1U> &varargin_2, array<int, 1U> &idx)
{
  unsigned int b_varargin_1[2];
  unsigned int b_varargin_2[2];
  int k;
  boolean_T exitg1;
  boolean_T p;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= varargin_1.size(0) - 1)) {
    if ((varargin_1[k] >= 1.0) && (varargin_1[k] <= siz[0])) {
      k++;
    } else {
      hc_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
    }
  }
  b_varargin_1[0] = static_cast<unsigned int>(varargin_1.size(0));
  b_varargin_1[1] = 1U;
  b_varargin_2[0] = static_cast<unsigned int>(varargin_2.size(0));
  b_varargin_2[1] = 1U;
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 2)) {
    if (static_cast<int>(b_varargin_1[k]) !=
        static_cast<int>(b_varargin_2[k])) {
      p = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (!p) {
    ic_rtErrorWithMessageID(qc_emlrtRTEI.fName, qc_emlrtRTEI.lineNo);
  }
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= varargin_2.size(0) - 1)) {
    if ((varargin_2[k] >= 1.0) && (varargin_2[k] <= siz[1])) {
      k++;
    } else {
      hc_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
    }
  }
  idx.set_size(varargin_1.size(0));
  k = varargin_1.size(0);
  for (int i{0}; i < k; i++) {
    idx[i] = static_cast<int>(varargin_1[i]) +
             siz[0] * (static_cast<int>(varargin_2[i]) - 1);
  }
}

//
// Arguments    : const int siz[2]
//                double varargin_2
// Return Type  : int
//
int sub2ind(const int siz[2], double varargin_2)
{
  if (siz[0] < 1) {
    hc_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  }
  if (!(varargin_2 <= siz[1])) {
    hc_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  }
  return siz[0] * (static_cast<int>(varargin_2) - 1) + 1;
}

} // namespace internal
} // namespace coder

//
// File trailer for sub2ind.cpp
//
// [EOF]
//
