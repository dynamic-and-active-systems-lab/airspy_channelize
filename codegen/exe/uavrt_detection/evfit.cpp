//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: evfit.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "evfit.h"
#include "blockedSummation.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
namespace coder {
static double lkeqn(double sigma, const array<double, 1U> &x,
                    double xbarWgtUnc);

}
static void times(coder::array<double, 1U> &in1,
                  const coder::array<double, 1U> &in2,
                  const coder::array<double, 1U> &in3);

static void ub_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void vb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void wb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void xb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : double sigma
//                const array<double, 1U> &x
//                double xbarWgtUnc
// Return Type  : double
//
namespace coder {
static double lkeqn(double sigma, const array<double, 1U> &x, double xbarWgtUnc)
{
  static rtEqualityCheckInfo g_emlrtECI{
      1,                                                          // nDims
      273,                                                        // lineNo
      34,                                                         // colNo
      "lkeqn",                                                    // fName
      "/Applications/MATLAB_R2023b.app/toolbox/stats/eml/evfit.m" // pName
  };
  array<double, 1U> b_x;
  array<double, 1U> wt;
  int nx;
  wt.set_size(x.size(0));
  nx = x.size(0);
  for (int k{0}; k < nx; k++) {
    wt[k] = x[k] / sigma;
  }
  nx = wt.size(0);
  if (wt.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nx; k++) {
    wt[k] = std::exp(wt[k]);
  }
  if ((x.size(0) != wt.size(0)) && ((x.size(0) != 1) && (wt.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(x.size(0), wt.size(0), g_emlrtECI);
  }
  if (x.size(0) == wt.size(0)) {
    b_x.set_size(x.size(0));
    nx = x.size(0);
    for (int k{0}; k < nx; k++) {
      b_x[k] = x[k] * wt[k];
    }
  } else {
    times(b_x, x, wt);
  }
  return (sigma + xbarWgtUnc) -
         blockedSummation(b_x, b_x.size(0)) / blockedSummation(wt, wt.size(0));
}

//
// Arguments    : coder::array<double, 1U> &in1
//                const coder::array<double, 1U> &in2
//                const coder::array<double, 1U> &in3
// Return Type  : void
//
} // namespace coder
static void times(coder::array<double, 1U> &in1,
                  const coder::array<double, 1U> &in2,
                  const coder::array<double, 1U> &in3)
{
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in3.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3.size(0);
  }
  in1.set_size(loop_ub);
  stride_0_0 = (in2.size(0) != 1);
  stride_1_0 = (in3.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = in2[i * stride_0_0] * in3[i * stride_1_0];
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void ub_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Function values at the interval endpoints must differ in sign.";
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
static void vb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Function values at interval endpoints must be finite and real.";
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
static void wb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Second argument must be finite.";
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
static void xb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Unable to reach a maximum likelihood solution.";
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
// Arguments    : const array<double, 1U> &x
//                double parmhat[2]
// Return Type  : void
//
namespace coder {
void evfit(const array<double, 1U> &x, double parmhat[2])
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      -1,                   // iFirst
      -1,                   // iLast
      16,                   // lineNo
      25,                   // colNo
      "",                   // aName
      "rangeWithCensoring", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/stats/stats/+stats/+coder/"
      "+internal/rangeWithCensoring.m", // pName
      0                                 // checkKind
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      -1,                   // iFirst
      -1,                   // iLast
      15,                   // lineNo
      14,                   // colNo
      "",                   // aName
      "rangeWithCensoring", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/stats/stats/+stats/+coder/"
      "+internal/rangeWithCensoring.m", // pName
      0                                 // checkKind
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      -1,                   // iFirst
      -1,                   // iLast
      13,                   // lineNo
      25,                   // colNo
      "",                   // aName
      "rangeWithCensoring", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/stats/stats/+stats/+coder/"
      "+internal/rangeWithCensoring.m", // pName
      0                                 // checkKind
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      -1,                   // iFirst
      -1,                   // iLast
      12,                   // lineNo
      14,                   // colNo
      "",                   // aName
      "rangeWithCensoring", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/stats/stats/+stats/+coder/"
      "+internal/rangeWithCensoring.m", // pName
      0                                 // checkKind
  };
  static rtRunTimeErrorInfo bd_emlrtRTEI{
      218,                                                        // lineNo
      9,                                                          // colNo
      "evfit",                                                    // fName
      "/Applications/MATLAB_R2023b.app/toolbox/stats/eml/evfit.m" // pName
  };
  static rtRunTimeErrorInfo
      cd_emlrtRTEI{
          149,     // lineNo
          9,       // colNo
          "fzero", // fName
          "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/optimfun/"
          "fzero.m" // pName
      };
  static rtRunTimeErrorInfo dd_emlrtRTEI{
      14,    // lineNo
      9,     // colNo
      "log", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/elfun/log.m" // pName
  };
  static rtRunTimeErrorInfo ed_emlrtRTEI{
      227,                                                        // lineNo
      1,                                                          // colNo
      "evfit",                                                    // fName
      "/Applications/MATLAB_R2023b.app/toolbox/stats/eml/evfit.m" // pName
  };
  static rtRunTimeErrorInfo
      fd_emlrtRTEI{
          137,     // lineNo
          9,       // colNo
          "fzero", // fName
          "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/optimfun/"
          "fzero.m" // pName
      };
  static rtRunTimeErrorInfo
      gd_emlrtRTEI{
          127,     // lineNo
          19,      // colNo
          "fzero", // fName
          "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/optimfun/"
          "fzero.m" // pName
      };
  static rtRunTimeErrorInfo hd_emlrtRTEI{
      209,                                                        // lineNo
      9,                                                          // colNo
      "evfit",                                                    // fName
      "/Applications/MATLAB_R2023b.app/toolbox/stats/eml/evfit.m" // pName
  };
  array<double, 1U> x0;
  double rangex;
  double tempMax;
  double tempMin;
  double wgtmeanUnc;
  int k;
  int nx;
  if (x.size(0) == 0) {
    h_rtErrorWithMessageID("X", y_emlrtRTEI.fName, y_emlrtRTEI.lineNo);
  }
  tempMin = rtInf;
  tempMax = rtMinusInf;
  k = x.size(0);
  for (nx = 0; nx < k; nx++) {
    if (nx + 1 > x.size(0)) {
      rtDynamicBoundsError(nx + 1, 1, x.size(0), db_emlrtBCI);
    }
    wgtmeanUnc = x[nx];
    if (wgtmeanUnc > tempMax) {
      if (nx + 1 > x.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, x.size(0), cb_emlrtBCI);
      }
      tempMax = wgtmeanUnc;
    }
    if (nx + 1 > x.size(0)) {
      rtDynamicBoundsError(nx + 1, 1, x.size(0), bb_emlrtBCI);
    }
    if (wgtmeanUnc < tempMin) {
      if (nx + 1 > x.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, x.size(0), ab_emlrtBCI);
      }
      tempMin = wgtmeanUnc;
    }
  }
  rangex = tempMax - tempMin;
  if (std::isinf(rangex) || std::isnan(rangex)) {
    parmhat[0] = rtNaN;
    parmhat[1] = rtNaN;
  } else if (rangex < 2.2250738585072014E-308) {
    parmhat[0] = x[0];
    parmhat[1] = 0.0;
  } else {
    double fb;
    double savefa;
    double savefb;
    double scale;
    double sigmahat;
    double t;
    double upper;
    x0.set_size(x.size(0));
    nx = x.size(0);
    for (k = 0; k < nx; k++) {
      x0[k] = (x[k] - tempMax) / rangex;
    }
    nx = x0.size(0);
    if (x0.size(0) == 1) {
      if ((!std::isinf(x0[0])) && (!std::isnan(x0[0]))) {
        sigmahat = 0.0;
      } else {
        sigmahat = rtNaN;
      }
    } else {
      tempMin =
          blockedSummation(x0, x0.size(0)) / static_cast<double>(x0.size(0));
      if (x0.size(0) > 2147483646) {
        check_forloop_overflow_error();
      }
      sigmahat = 0.0;
      scale = 3.3121686421112381E-170;
      for (k = 0; k < nx; k++) {
        wgtmeanUnc = std::abs(x0[k] - tempMin);
        if (wgtmeanUnc > scale) {
          t = scale / wgtmeanUnc;
          sigmahat = sigmahat * t * t + 1.0;
          scale = wgtmeanUnc;
        } else {
          t = wgtmeanUnc / scale;
          sigmahat += t * t;
        }
      }
      sigmahat = scale * std::sqrt(sigmahat);
      sigmahat /= std::sqrt(static_cast<double>(x0.size(0)) - 1.0);
    }
    sigmahat = 2.4494897427831779 * sigmahat / 3.1415926535897931;
    wgtmeanUnc =
        blockedSummation(x0, x0.size(0)) / static_cast<double>(x.size(0));
    if (lkeqn(sigmahat, x0, wgtmeanUnc) > 0.0) {
      upper = sigmahat;
      sigmahat *= 0.5;
      while (lkeqn(sigmahat, x0, wgtmeanUnc) > 0.0) {
        upper = sigmahat;
        sigmahat *= 0.5;
        if (sigmahat < 2.2250738585072014E-308) {
          xb_rtErrorWithMessageID(hd_emlrtRTEI.fName, hd_emlrtRTEI.lineNo);
        }
      }
    } else {
      upper = 2.0 * sigmahat;
      while (lkeqn(upper, x0, wgtmeanUnc) < 0.0) {
        sigmahat = upper;
        upper *= 2.0;
        if (sigmahat < 2.2250738585072014E-308) {
          xb_rtErrorWithMessageID(bd_emlrtRTEI.fName, bd_emlrtRTEI.lineNo);
        }
      }
    }
    nx = 1;
    if (std::isinf(sigmahat) || std::isnan(sigmahat) ||
        (std::isinf(upper) || std::isnan(upper))) {
      wb_rtErrorWithMessageID(gd_emlrtRTEI.fName, gd_emlrtRTEI.lineNo);
    }
    tempMin = lkeqn(sigmahat, x0, wgtmeanUnc);
    fb = lkeqn(upper, x0, wgtmeanUnc);
    if (std::isinf(tempMin) || std::isnan(tempMin) ||
        (std::isinf(fb) || std::isnan(fb))) {
      vb_rtErrorWithMessageID(fd_emlrtRTEI.fName, fd_emlrtRTEI.lineNo);
    }
    savefa = tempMin;
    savefb = fb;
    if (tempMin == 0.0) {
      upper = sigmahat;
    } else if (!(fb == 0.0)) {
      double c;
      double d;
      double e;
      double fc;
      boolean_T exitg1;
      if ((tempMin > 0.0) == (fb > 0.0)) {
        ub_rtErrorWithMessageID(cd_emlrtRTEI.fName, cd_emlrtRTEI.lineNo);
      }
      fc = fb;
      c = upper;
      e = 0.0;
      d = 0.0;
      exitg1 = false;
      while ((!exitg1) && ((fb != 0.0) && (sigmahat != upper))) {
        double m;
        double toler;
        if ((fb > 0.0) == (fc > 0.0)) {
          c = sigmahat;
          fc = tempMin;
          d = upper - sigmahat;
          e = d;
        }
        if (std::abs(fc) < std::abs(fb)) {
          sigmahat = upper;
          upper = c;
          c = sigmahat;
          tempMin = fb;
          fb = fc;
          fc = tempMin;
        }
        m = 0.5 * (c - upper);
        toler = 2.0E-6 * std::fmax(std::abs(upper), 1.0);
        if ((std::abs(m) <= toler) || (fb == 0.0)) {
          exitg1 = true;
        } else {
          if ((std::abs(e) < toler) || (std::abs(tempMin) <= std::abs(fb))) {
            d = m;
            e = m;
          } else {
            double s;
            s = fb / tempMin;
            if (sigmahat == c) {
              tempMin = 2.0 * m * s;
              scale = 1.0 - s;
            } else {
              scale = tempMin / fc;
              t = fb / fc;
              tempMin = s * (2.0 * m * scale * (scale - t) -
                             (upper - sigmahat) * (t - 1.0));
              scale = (scale - 1.0) * (t - 1.0) * (s - 1.0);
            }
            if (tempMin > 0.0) {
              scale = -scale;
            } else {
              tempMin = -tempMin;
            }
            if ((2.0 * tempMin < 3.0 * m * scale - std::abs(toler * scale)) &&
                (tempMin < std::abs(0.5 * e * scale))) {
              e = d;
              d = tempMin / scale;
            } else {
              d = m;
              e = m;
            }
          }
          sigmahat = upper;
          tempMin = fb;
          if (std::abs(d) > toler) {
            upper += d;
          } else if (upper > c) {
            upper -= toler;
          } else {
            upper += toler;
          }
          fb = lkeqn(upper, x0, wgtmeanUnc);
        }
      }
      if (!(std::abs(fb) <= std::fmax(std::abs(savefa), std::abs(savefb)))) {
        nx = -5;
      }
    }
    if (nx < 0) {
      xb_rtErrorWithMessageID(ed_emlrtRTEI.fName, ed_emlrtRTEI.lineNo);
    }
    nx = x0.size(0);
    for (k = 0; k < nx; k++) {
      x0[k] = x0[k] / upper;
    }
    nx = x0.size(0);
    for (k = 0; k < nx; k++) {
      x0[k] = std::exp(x0[k]);
    }
    tempMin = blockedSummation(x0, x0.size(0)) / static_cast<double>(x.size(0));
    if (tempMin < 0.0) {
      rtErrorWithMessageID("log", dd_emlrtRTEI.fName, dd_emlrtRTEI.lineNo);
    }
    tempMin = std::log(tempMin);
    parmhat[0] = rangex * (upper * tempMin) + tempMax;
    parmhat[1] = rangex * upper;
  }
}

} // namespace coder

//
// File trailer for evfit.cpp
//
// [EOF]
//
