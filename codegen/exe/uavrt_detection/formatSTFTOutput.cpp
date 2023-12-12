//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: formatSTFTOutput.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "formatSTFTOutput.h"
#include "eml_int_forloop_overflow_check.h"
#include "iseven.h"
#include "rt_nonfinite.h"
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

// Variable Definitions
static rtRunTimeErrorInfo
    fc_emlrtRTEI{
        38,          // lineNo
        48,          // colNo
        "circshift", // fName
        "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/elmat/"
        "circshift.m" // pName
    };

static rtBoundsCheckInfo x_emlrtBCI{
    -1,           // iFirst
    -1,           // iLast
    16,           // lineNo
    13,           // colNo
    "",           // aName
    "centerfreq", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/+signal/+internal/"
    "+spectral/centerfreq.m", // pName
    0                         // checkKind
};

static rtDoubleCheckInfo p_emlrtDCI{
    16,           // lineNo
    13,           // colNo
    "centerfreq", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/+signal/+internal/"
    "+spectral/centerfreq.m", // pName
    1                         // checkKind
};

static rtBoundsCheckInfo y_emlrtBCI{
    -1,           // iFirst
    -1,           // iLast
    13,           // lineNo
    13,           // colNo
    "",           // aName
    "centerfreq", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/+signal/+internal/"
    "+spectral/centerfreq.m", // pName
    0                         // checkKind
};

static rtDoubleCheckInfo q_emlrtDCI{
    13,           // lineNo
    13,           // colNo
    "centerfreq", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/+signal/+internal/"
    "+spectral/centerfreq.m", // pName
    1                         // checkKind
};

static rtRunTimeErrorInfo ad_emlrtRTEI{
    41,    // lineNo
    9,     // colNo
    "rem", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/+scalar/"
    "rem.m" // pName
};

// Function Declarations
static void rtDivisionByZeroError(const rtRunTimeErrorInfo &aInfo);

static void rtErrorWithMessageID(const char *r, const char *r1,
                                 const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const rtRunTimeErrorInfo &aInfo
// Return Type  : void
//
static void rtDivisionByZeroError(const rtRunTimeErrorInfo &aInfo)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Division by zero detected.\nEarly termination due to division "
               "by zero.";
  outStream << "\n";
  ((((outStream << "Error in ") << aInfo.fName) << " (line ") << aInfo.lineNo)
      << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *r
//                const char *r1
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void rtErrorWithMessageID(const char *r, const char *r1,
                                 const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((((outStream << "Invalid shift argument: must be a finite, real, integer "
                   "vector with entries between -intmax(\'")
     << r)
    << "\') and intmax(\'")
   << r1)
      << "\').";
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
// Arguments    : array<creal32_T, 2U> &S
//                const array<double, 1U> &F
//                array<double, 1U> &Fout
// Return Type  : void
//
namespace coder {
namespace b_signal {
namespace internal {
namespace stft {
void formatSTFTOutput(array<creal32_T, 2U> &S, const array<double, 1U> &F,
                      array<double, 1U> &Fout)
{
  array<creal32_T, 2U> buffer;
  double p;
  int b_i;
  int vlend2;
  if (signalwavelet::internal::iseven(static_cast<double>(S.size(0)))) {
    int vspread;
    p = static_cast<double>(S.size(0)) / 2.0 - 1.0;
    vspread = 1;
    if (S.size(0) != 1) {
      vspread = 0;
    }
    if (static_cast<int>(p) != p) {
      rtErrorWithMessageID("int32", "int32", fc_emlrtRTEI.fName,
                           fc_emlrtRTEI.lineNo);
    }
    if ((S.size(0) != 0) && (S.size(1) != 0) &&
        ((S.size(0) != 1) || (S.size(1) != 1))) {
      int i2;
      int ib;
      int npages;
      int ns;
      int pageroot;
      boolean_T shiftright;
      if (p < 0.0) {
        ns = 1;
        shiftright = false;
      } else {
        ns = static_cast<int>(p);
        shiftright = true;
      }
      if (S.size(vspread) <= 1) {
        ns = 0;
      } else {
        if (ns > S.size(vspread)) {
          unsigned int u;
          u = static_cast<unsigned int>(S.size(vspread));
          if (u == 0U) {
            rtDivisionByZeroError(ad_emlrtRTEI);
          } else {
            b_i = static_cast<int>(static_cast<unsigned int>(ns) / u);
          }
          ns -= S.size(vspread) * b_i;
        }
        if (ns > (S.size(vspread) >> 1)) {
          ns = S.size(vspread) - ns;
          shiftright = !shiftright;
        }
      }
      if ((S.size(0) == 0) || (S.size(1) == 0)) {
        pageroot = 0;
      } else {
        vlend2 = S.size(0);
        pageroot = S.size(1);
        if (vlend2 >= pageroot) {
          pageroot = vlend2;
        }
      }
      vlend2 = pageroot / 2;
      buffer.set_size(1, vlend2);
      for (b_i = 0; b_i < vlend2; b_i++) {
        buffer[b_i].re = 0.0F;
        buffer[b_i].im = 0.0F;
      }
      b_i = S.size(vspread);
      i2 = S.size(vspread);
      ib = 1;
      for (int k{0}; k < vspread; k++) {
        ib *= S.size(0);
      }
      npages = 1;
      vlend2 = vspread + 2;
      for (int k{vlend2}; k < 3; k++) {
        npages *= S.size(1);
      }
      vlend2 = ib * S.size(vspread);
      if ((S.size(vspread) > 1) && (ns > 0)) {
        if (npages > 2147483646) {
          check_forloop_overflow_error();
        }
        for (int i{0}; i < npages; i++) {
          pageroot = i * vlend2;
          if (ib > 2147483646) {
            check_forloop_overflow_error();
          }
          for (vspread = 0; vspread < ib; vspread++) {
            int i1;
            i1 = pageroot + vspread;
            if (shiftright) {
              int b_i1;
              for (int k{0}; k < ns; k++) {
                buffer[k] = S[i1 + ((k + b_i) - ns) * ib];
              }
              b_i1 = ns + 1;
              for (int k{i2}; k >= b_i1; k--) {
                S[i1 + (k - 1) * ib] = S[i1 + ((k - ns) - 1) * ib];
              }
              for (int k{0}; k < ns; k++) {
                S[i1 + k * ib] = buffer[k];
              }
            } else {
              int b_i1;
              for (int k{0}; k < ns; k++) {
                buffer[k] = S[i1 + k * ib];
              }
              b_i1 = (b_i - ns) - 1;
              for (int k{0}; k <= b_i1; k++) {
                S[i1 + k * ib] = S[i1 + (k + ns) * ib];
              }
              for (int k{0}; k < ns; k++) {
                S[i1 + ((k + b_i) - ns) * ib] = buffer[k];
              }
            }
          }
        }
      }
    }
  } else if (S.size(0) > 1) {
    int npages;
    int vspread;
    vlend2 = static_cast<int>(static_cast<unsigned int>(S.size(0)) >> 1) - 1;
    npages = S.size(1) - 1;
    vspread = S.size(0);
    if ((vlend2 + 1) << 1 == S.size(0)) {
      int i2;
      i2 = 1;
      if (S.size(1) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int i{0}; i <= npages; i++) {
        int i1;
        int ib;
        i1 = i2;
        i2 += vspread;
        ib = i1 + vlend2;
        for (int k{0}; k <= vlend2; k++) {
          float xtmp_im;
          float xtmp_re;
          int pageroot;
          pageroot = (i1 + k) - 1;
          xtmp_re = S[pageroot].re;
          xtmp_im = S[pageroot].im;
          b_i = ib + k;
          S[pageroot] = S[b_i];
          S[b_i].re = xtmp_re;
          S[b_i].im = xtmp_im;
        }
      }
    } else {
      int i2;
      i2 = 1;
      if (S.size(1) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int i{0}; i <= npages; i++) {
        float xtmp_im;
        float xtmp_re;
        int i1;
        int ib;
        i1 = i2;
        i2 += vspread;
        ib = i1 + vlend2;
        xtmp_re = S[ib].re;
        xtmp_im = S[ib].im;
        for (int k{0}; k <= vlend2; k++) {
          int b_i1;
          b_i = ib + k;
          b_i1 = (i1 + k) - 1;
          S[b_i] = S[b_i1];
          S[b_i1] = S[b_i + 1];
        }
        ib = (ib + vlend2) + 1;
        S[ib].re = xtmp_re;
        S[ib].im = xtmp_im;
      }
    }
  }
  if (signalwavelet::internal::iseven(static_cast<double>(F.size(0)))) {
    p = static_cast<double>(F.size(0)) / 2.0;
    if (p != std::floor(p)) {
      rtIntegerError(p, q_emlrtDCI);
    }
    if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > F.size(0))) {
      rtDynamicBoundsError(static_cast<int>(p), 1, F.size(0), y_emlrtBCI);
    }
    p = F[static_cast<int>(p) - 1];
    Fout.set_size(F.size(0));
    vlend2 = F.size(0);
    for (b_i = 0; b_i < vlend2; b_i++) {
      Fout[b_i] = F[b_i] - p;
    }
  } else {
    p = (static_cast<double>(F.size(0)) + 1.0) / 2.0;
    if (p != std::floor(p)) {
      rtIntegerError(p, p_emlrtDCI);
    }
    if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > F.size(0))) {
      rtDynamicBoundsError(static_cast<int>(p), 1, F.size(0), x_emlrtBCI);
    }
    p = F[static_cast<int>(p) - 1];
    Fout.set_size(F.size(0));
    vlend2 = F.size(0);
    for (b_i = 0; b_i < vlend2; b_i++) {
      Fout[b_i] = F[b_i] - p;
    }
  }
}

//
// Arguments    : array<creal_T, 3U> &S
//                const array<double, 1U> &F
//                array<double, 1U> &Fout
// Return Type  : void
//
void formatSTFTOutput(array<creal_T, 3U> &S, const array<double, 1U> &F,
                      array<double, 1U> &Fout)
{
  array<creal_T, 2U> buffer;
  double xtmp_re;
  int b_i;
  int lowerDim;
  if (signalwavelet::internal::iseven(static_cast<double>(S.size(0)))) {
    int vlend2;
    xtmp_re = static_cast<double>(S.size(0)) / 2.0 - 1.0;
    vlend2 = 1;
    if (S.size(0) != 1) {
      vlend2 = 0;
    } else if ((S.size(1) == 1) && (S.size(2) != 1)) {
      vlend2 = 2;
    }
    if (static_cast<int>(xtmp_re) != xtmp_re) {
      rtErrorWithMessageID("int32", "int32", fc_emlrtRTEI.fName,
                           fc_emlrtRTEI.lineNo);
    }
    if ((S.size(0) != 0) && (S.size(1) != 0) && (S.size(2) != 0) &&
        ((S.size(0) != 1) || (S.size(1) != 1) || (S.size(2) != 1))) {
      int i2;
      int ib;
      int npages;
      int ns;
      int vspread;
      boolean_T shiftright;
      if (xtmp_re < 0.0) {
        ns = 1;
        shiftright = false;
      } else {
        ns = static_cast<int>(xtmp_re);
        shiftright = true;
      }
      if (S.size(vlend2) <= 1) {
        ns = 0;
      } else {
        if (ns > S.size(vlend2)) {
          unsigned int u;
          u = static_cast<unsigned int>(S.size(vlend2));
          if (u == 0U) {
            rtDivisionByZeroError(ad_emlrtRTEI);
          } else {
            b_i = static_cast<int>(static_cast<unsigned int>(ns) / u);
          }
          ns -= S.size(vlend2) * b_i;
        }
        if (ns > (S.size(vlend2) >> 1)) {
          ns = S.size(vlend2) - ns;
          shiftright = !shiftright;
        }
      }
      lowerDim = S.size(0);
      if ((S.size(0) > 0) && ((S.size(1) == 0) || (S.size(1) > S.size(0)))) {
        lowerDim = S.size(1);
      }
      if ((lowerDim > 0) && ((S.size(2) == 0) || (S.size(2) > lowerDim))) {
        lowerDim = S.size(2);
      }
      lowerDim /= 2;
      buffer.set_size(1, lowerDim);
      for (b_i = 0; b_i < lowerDim; b_i++) {
        buffer[b_i].re = 0.0;
        buffer[b_i].im = 0.0;
      }
      b_i = S.size(vlend2);
      i2 = S.size(vlend2);
      ib = 1;
      for (int k{0}; k < vlend2; k++) {
        ib *= S.size(k);
      }
      npages = 1;
      lowerDim = vlend2 + 2;
      for (int k{lowerDim}; k < 4; k++) {
        npages *= S.size(k - 1);
      }
      vspread = ib * S.size(vlend2);
      if ((S.size(vlend2) > 1) && (ns > 0)) {
        if (npages > 2147483646) {
          check_forloop_overflow_error();
        }
        for (int i{0}; i < npages; i++) {
          lowerDim = i * vspread;
          if (ib > 2147483646) {
            check_forloop_overflow_error();
          }
          for (vlend2 = 0; vlend2 < ib; vlend2++) {
            int i1;
            i1 = lowerDim + vlend2;
            if (shiftright) {
              int b_i1;
              for (int k{0}; k < ns; k++) {
                buffer[k] = S[i1 + ((k + b_i) - ns) * ib];
              }
              b_i1 = ns + 1;
              for (int k{i2}; k >= b_i1; k--) {
                S[i1 + (k - 1) * ib] = S[i1 + ((k - ns) - 1) * ib];
              }
              for (int k{0}; k < ns; k++) {
                S[i1 + k * ib] = buffer[k];
              }
            } else {
              int b_i1;
              for (int k{0}; k < ns; k++) {
                buffer[k] = S[i1 + k * ib];
              }
              b_i1 = (b_i - ns) - 1;
              for (int k{0}; k <= b_i1; k++) {
                S[i1 + k * ib] = S[i1 + (k + ns) * ib];
              }
              for (int k{0}; k < ns; k++) {
                S[i1 + ((k + b_i) - ns) * ib] = buffer[k];
              }
            }
          }
        }
      }
    }
  } else if (S.size(0) > 1) {
    int npages;
    int vlend2;
    int vspread;
    vlend2 = static_cast<int>(static_cast<unsigned int>(S.size(0)) >> 1) - 1;
    npages = S.size(1) * S.size(2);
    vspread = S.size(0);
    if ((vlend2 + 1) << 1 == S.size(0)) {
      int i2;
      i2 = 1;
      if (npages > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int i{0}; i < npages; i++) {
        int i1;
        int ib;
        i1 = i2;
        i2 += vspread;
        ib = i1 + vlend2;
        for (int k{0}; k <= vlend2; k++) {
          double xtmp_im;
          lowerDim = (i1 + k) - 1;
          xtmp_re = S[lowerDim].re;
          xtmp_im = S[lowerDim].im;
          b_i = ib + k;
          S[lowerDim] = S[b_i];
          S[b_i].re = xtmp_re;
          S[b_i].im = xtmp_im;
        }
      }
    } else {
      int i2;
      i2 = 1;
      if (npages > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int i{0}; i < npages; i++) {
        double xtmp_im;
        int i1;
        int ib;
        i1 = i2;
        i2 += vspread;
        ib = i1 + vlend2;
        xtmp_re = S[ib].re;
        xtmp_im = S[ib].im;
        for (int k{0}; k <= vlend2; k++) {
          int b_i1;
          b_i = ib + k;
          b_i1 = (i1 + k) - 1;
          S[b_i] = S[b_i1];
          S[b_i1] = S[b_i + 1];
        }
        ib = (ib + vlend2) + 1;
        S[ib].re = xtmp_re;
        S[ib].im = xtmp_im;
      }
    }
  }
  if (signalwavelet::internal::iseven(static_cast<double>(F.size(0)))) {
    xtmp_re = static_cast<double>(F.size(0)) / 2.0;
    if (xtmp_re != std::floor(xtmp_re)) {
      rtIntegerError(xtmp_re, q_emlrtDCI);
    }
    if ((static_cast<int>(xtmp_re) < 1) ||
        (static_cast<int>(xtmp_re) > F.size(0))) {
      rtDynamicBoundsError(static_cast<int>(xtmp_re), 1, F.size(0), y_emlrtBCI);
    }
    xtmp_re = F[static_cast<int>(xtmp_re) - 1];
    Fout.set_size(F.size(0));
    lowerDim = F.size(0);
    for (b_i = 0; b_i < lowerDim; b_i++) {
      Fout[b_i] = F[b_i] - xtmp_re;
    }
  } else {
    xtmp_re = (static_cast<double>(F.size(0)) + 1.0) / 2.0;
    if (xtmp_re != std::floor(xtmp_re)) {
      rtIntegerError(xtmp_re, p_emlrtDCI);
    }
    if ((static_cast<int>(xtmp_re) < 1) ||
        (static_cast<int>(xtmp_re) > F.size(0))) {
      rtDynamicBoundsError(static_cast<int>(xtmp_re), 1, F.size(0), x_emlrtBCI);
    }
    xtmp_re = F[static_cast<int>(xtmp_re) - 1];
    Fout.set_size(F.size(0));
    lowerDim = F.size(0);
    for (b_i = 0; b_i < lowerDim; b_i++) {
      Fout[b_i] = F[b_i] - xtmp_re;
    }
  }
}

} // namespace stft
} // namespace internal
} // namespace b_signal
} // namespace coder

//
// File trailer for formatSTFTOutput.cpp
//
// [EOF]
//
