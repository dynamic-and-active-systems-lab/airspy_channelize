//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: interp1.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "interp1.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo
    ac_emlrtRTEI{
        166,            // lineNo
        13,             // colNo
        "interp1_work", // fName
        "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/polyfun/"
        "interp1.m" // pName
    };

static rtRunTimeErrorInfo
    bc_emlrtRTEI{
        208,            // lineNo
        13,             // colNo
        "interp1_work", // fName
        "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/polyfun/"
        "interp1.m" // pName
    };

// Function Declarations
static void ac_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void bc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

namespace coder {
static void interp1Linear(const double y[2], const array<double, 2U> &xi,
                          array<double, 2U> &yi, const double varargin_1[2]);

static void interp1Linear(const array<double, 1U> &y, int nyrows,
                          const array<double, 1U> &xi, array<double, 1U> &yi,
                          const array<double, 1U> &varargin_1);

} // namespace coder
static void kb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void lb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void ac_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Y must have length(X) rows.";
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
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void bc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "A minimum of two data points is required.";
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
// Arguments    : const double y[2]
//                const array<double, 2U> &xi
//                array<double, 2U> &yi
//                const double varargin_1[2]
// Return Type  : void
//
namespace coder {
static void interp1Linear(const double y[2], const array<double, 2U> &xi,
                          array<double, 2U> &yi, const double varargin_1[2])
{
  double maxx;
  double minx;
  double r;
  int ub_loop;
  minx = varargin_1[0];
  maxx = varargin_1[1];
  if (xi.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  ub_loop = xi.size(1) - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(r)

  for (int k = 0; k <= ub_loop; k++) {
    r = xi[k];
    if (std::isnan(r)) {
      yi[k] = rtNaN;
    } else if ((!(r > maxx)) && (!(r < minx))) {
      r = (r - varargin_1[0]) / (varargin_1[1] - varargin_1[0]);
      if (r == 0.0) {
        yi[k] = y[0];
      } else if (r == 1.0) {
        yi[k] = y[1];
      } else if (y[0] == y[1]) {
        yi[k] = y[0];
      } else {
        yi[k] = (1.0 - r) * y[0] + r * y[1];
      }
    }
  }
}

//
// Arguments    : const array<double, 1U> &y
//                int nyrows
//                const array<double, 1U> &xi
//                array<double, 1U> &yi
//                const array<double, 1U> &varargin_1
// Return Type  : void
//
static void interp1Linear(const array<double, 1U> &y, int nyrows,
                          const array<double, 1U> &xi, array<double, 1U> &yi,
                          const array<double, 1U> &varargin_1)
{
  double d;
  double maxx;
  double minx;
  double penx;
  double r;
  int high_i;
  int low_i;
  int low_ip1;
  int mid_i;
  int ub_loop;
  minx = varargin_1[0];
  penx = varargin_1[varargin_1.size(0) - 2];
  maxx = varargin_1[varargin_1.size(0) - 1];
  if (xi.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  ub_loop = xi.size(0) - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    d, high_i, low_i, low_ip1, r, mid_i)

  for (int k = 0; k <= ub_loop; k++) {
    if (std::isnan(xi[k])) {
      yi[k] = rtNaN;
    } else if (xi[k] > maxx) {
      if (nyrows > 1) {
        d = y[nyrows - 1];
        yi[k] = d + (xi[k] - maxx) / (maxx - penx) * (d - y[nyrows - 2]);
      }
    } else if (xi[k] < minx) {
      yi[k] = y[0] + (xi[k] - minx) / (varargin_1[1] - minx) * (y[1] - y[0]);
    } else {
      high_i = varargin_1.size(0);
      low_i = 1;
      low_ip1 = 2;
      while (high_i > low_ip1) {
        mid_i = (low_i >> 1) + (high_i >> 1);
        if (((low_i & 1) == 1) && ((high_i & 1) == 1)) {
          mid_i++;
        }
        if (xi[k] >= varargin_1[mid_i - 1]) {
          low_i = mid_i;
          low_ip1 = mid_i + 1;
        } else {
          high_i = mid_i;
        }
      }
      r = varargin_1[low_i - 1];
      r = (xi[k] - r) / (varargin_1[low_i] - r);
      if (r == 0.0) {
        yi[k] = y[low_i - 1];
      } else if (r == 1.0) {
        yi[k] = y[low_i];
      } else {
        d = y[low_i - 1];
        if (d == y[low_i]) {
          yi[k] = d;
        } else {
          yi[k] = (1.0 - r) * d + r * y[low_i];
        }
      }
    }
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
} // namespace coder
static void kb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "NaN is not an appropriate value for X.";
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
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void lb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "The data abscissae must be distinct and strictly monotonic.";
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
// Arguments    : const double varargin_1[2]
//                const double varargin_2[2]
//                const array<double, 2U> &varargin_3
//                array<double, 2U> &Vq
// Return Type  : void
//
namespace coder {
void interp1(const double varargin_1[2], const double varargin_2[2],
             const array<double, 2U> &varargin_3, array<double, 2U> &Vq)
{
  double x[2];
  double y[2];
  int loop_ub;
  boolean_T b;
  y[0] = varargin_2[0];
  x[0] = varargin_1[0];
  y[1] = varargin_2[1];
  x[1] = varargin_1[1];
  Vq.set_size(1, varargin_3.size(1));
  loop_ub = varargin_3.size(1);
  for (int i{0}; i < loop_ub; i++) {
    Vq[i] = rtNaN;
  }
  b = (varargin_3.size(1) == 0);
  if (!b) {
    loop_ub = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (loop_ub < 2) {
        if (std::isnan(varargin_1[loop_ub])) {
          kb_rtErrorWithMessageID(ac_emlrtRTEI.fName, ac_emlrtRTEI.lineNo);
        } else {
          loop_ub++;
        }
      } else {
        if (varargin_1[1] < 0.0) {
          x[0] = varargin_1[1];
          x[1] = 0.0;
          y[0] = varargin_2[1];
          y[1] = varargin_2[0];
        }
        if (x[1] <= x[0]) {
          lb_rtErrorWithMessageID(bc_emlrtRTEI.fName, bc_emlrtRTEI.lineNo);
        }
        interp1Linear(y, varargin_3, Vq, x);
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
}

//
// Arguments    : const array<double, 1U> &varargin_1
//                const array<double, 1U> &varargin_2
//                const array<double, 1U> &varargin_3
//                array<double, 1U> &Vq
// Return Type  : void
//
void interp1(const array<double, 1U> &varargin_1,
             const array<double, 1U> &varargin_2,
             const array<double, 1U> &varargin_3, array<double, 1U> &Vq)
{
  static rtRunTimeErrorInfo
      bd_emlrtRTEI{
          155,            // lineNo
          15,             // colNo
          "interp1_work", // fName
          "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/polyfun/"
          "interp1.m" // pName
      };
  static rtRunTimeErrorInfo
      cd_emlrtRTEI{
          139,            // lineNo
          23,             // colNo
          "interp1_work", // fName
          "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/polyfun/"
          "interp1.m" // pName
      };
  array<double, 1U> x;
  array<double, 1U> y;
  int n;
  int nx;
  int y_tmp;
  y.set_size(varargin_2.size(0));
  n = varargin_2.size(0);
  for (y_tmp = 0; y_tmp < n; y_tmp++) {
    y[y_tmp] = varargin_2[y_tmp];
  }
  x.set_size(varargin_1.size(0));
  n = varargin_1.size(0);
  for (y_tmp = 0; y_tmp < n; y_tmp++) {
    x[y_tmp] = varargin_1[y_tmp];
  }
  nx = varargin_1.size(0);
  if (varargin_1.size(0) != varargin_2.size(0)) {
    ac_rtErrorWithMessageID(cd_emlrtRTEI.fName, cd_emlrtRTEI.lineNo);
  }
  if (varargin_1.size(0) <= 1) {
    bc_rtErrorWithMessageID(bd_emlrtRTEI.fName, bd_emlrtRTEI.lineNo);
  }
  Vq.set_size(varargin_3.size(0));
  n = varargin_3.size(0);
  for (y_tmp = 0; y_tmp < n; y_tmp++) {
    Vq[y_tmp] = 0.0;
  }
  if (varargin_3.size(0) != 0) {
    int k;
    if (nx > 2147483646) {
      check_forloop_overflow_error();
    }
    k = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (k <= nx - 1) {
        if (std::isnan(varargin_1[k])) {
          kb_rtErrorWithMessageID(ac_emlrtRTEI.fName, ac_emlrtRTEI.lineNo);
        } else {
          k++;
        }
      } else {
        if (varargin_1[1] < varargin_1[0]) {
          double xtmp;
          int nd2;
          y_tmp = nx >> 1;
          for (nd2 = 0; nd2 < y_tmp; nd2++) {
            xtmp = x[nd2];
            n = (nx - nd2) - 1;
            x[nd2] = x[n];
            x[n] = xtmp;
          }
          if (varargin_2.size(0) > 1) {
            n = varargin_2.size(0) - 1;
            nd2 = varargin_2.size(0) >> 1;
            for (k = 0; k < nd2; k++) {
              xtmp = y[k];
              y_tmp = n - k;
              y[k] = y[y_tmp];
              y[y_tmp] = xtmp;
            }
          }
        }
        for (k = 2; k <= nx; k++) {
          if (x[k - 1] <= x[k - 2]) {
            lb_rtErrorWithMessageID(bc_emlrtRTEI.fName, bc_emlrtRTEI.lineNo);
          }
        }
        interp1Linear(y, varargin_2.size(0), varargin_3, Vq, x);
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
}

//
// Arguments    : const double y[2]
//                const array<double, 1U> &xi
//                array<double, 1U> &yi
// Return Type  : void
//
void interp1Linear(const double y[2], const array<double, 1U> &xi,
                   array<double, 1U> &yi)
{
  int ub_loop;
  if (xi.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  ub_loop = xi.size(0) - 1;
#pragma omp parallel for num_threads(omp_get_max_threads())

  for (int k = 0; k <= ub_loop; k++) {
    if (std::isnan(xi[k])) {
      yi[k] = rtNaN;
    } else if (xi[k] > 1.0) {
      yi[k] = y[1] + (xi[k] - 1.0) * y[1];
    } else if (xi[k] < 0.0) {
      yi[k] = xi[k] * y[1];
    } else if (xi[k] == 0.0) {
      yi[k] = 0.0;
    } else if (xi[k] == 1.0) {
      yi[k] = y[1];
    } else if (y[1] == 0.0) {
      yi[k] = 0.0;
    } else {
      yi[k] = (1.0 - xi[k]) * 0.0 + xi[k] * y[1];
    }
  }
}

} // namespace coder

//
// File trailer for interp1.cpp
//
// [EOF]
//
