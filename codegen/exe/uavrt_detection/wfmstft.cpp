//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: wfmstft.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "wfmstft.h"
#include "eml_int_forloop_overflow_check.h"
#include "mean.h"
#include "movSumProdOrMean.h"
#include "quickselect.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cmath>

// Function Declarations
static void gt(coder::array<boolean_T, 2U> &in1,
               const coder::array<double, 2U> &in2,
               const coder::array<double, 2U> &in3);

// Function Definitions
//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void gt(coder::array<boolean_T, 2U> &in1,
               const coder::array<double, 2U> &in2,
               const coder::array<double, 2U> &in3)
{
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in3.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3.size(0);
  }
  in1.set_size(loop_ub, in1.size(1));
  if (in3.size(1) == 1) {
    b_loop_ub = in2.size(1);
  } else {
    b_loop_ub = in3.size(1);
  }
  in1.set_size(in1.size(0), b_loop_ub);
  stride_0_0 = (in2.size(0) != 1);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_0 = (in3.size(0) != 1);
  stride_1_1 = (in3.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (int i{0}; i < b_loop_ub; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] =
          (in2[i1 * stride_0_0 + in2.size(0) * aux_0_1] >
           in3[i1 * stride_1_0 + in3.size(0) * aux_1_1]);
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
}

//
// This block calculates a three window moving mean of the power
// spectral density of the waveform and then thresholds that
// moving mean for values greater than 10x the median. This
// thresholding step reduced the energy from very high power
// pulses that might be in the signal from affecting the PSD
// estimate. It is assumed here that low signal power pulses will
// only marginally affect the psd estimate.
// coder.varsize('magSqrd','movMeanMagSqrd','medMovMeanMagSqrd','medMovMeanMagSqrdMat','magSqrdMask')
//
// Arguments    : void
// Return Type  : void
//
void wfmstft::updatepsd()
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      -1,                  // iFirst
      -1,                  // iLast
      155,                 // lineNo
      21,                  // colNo
      "magSqrd",           // aName
      "wfmstft/updatepsd", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/wfmstft.m", // pName
      0                                            // checkKind
  };
  static rtEqualityCheckInfo g_emlrtECI{
      1,                   // nDims
      154,                 // lineNo
      27,                  // colNo
      "wfmstft/updatepsd", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/wfmstft.m" // pName
  };
  static rtEqualityCheckInfo h_emlrtECI{
      2,                   // nDims
      154,                 // lineNo
      27,                  // colNo
      "wfmstft/updatepsd", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/wfmstft.m" // pName
  };
  coder::array<double, 2U> magSqrd;
  coder::array<double, 2U> movMeanMagSqrd;
  coder::array<double, 1U> xv;
  coder::array<double, 1U> yv;
  coder::array<boolean_T, 2U> r;
  double varargin_1;
  int b_loop_ub;
  int len;
  int loop_ub;
  int loop_ub_tmp;
  int midm1;
  int nx;
  int outsize_idx_0;
  int stride;
  boolean_T overflow;
  nx = S.size(0) * S.size(1);
  movMeanMagSqrd.set_size(S.size(0), S.size(1));
  if (nx > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  for (midm1 = 0; midm1 < nx; midm1++) {
    movMeanMagSqrd[midm1] = rt_hypotd_snf(S[midm1].re, S[midm1].im);
  }
  magSqrd.set_size(movMeanMagSqrd.size(0), movMeanMagSqrd.size(1));
  loop_ub_tmp = movMeanMagSqrd.size(0) * movMeanMagSqrd.size(1);
  for (midm1 = 0; midm1 < loop_ub_tmp; midm1++) {
    varargin_1 = movMeanMagSqrd[midm1];
    magSqrd[midm1] = varargin_1 * varargin_1;
  }
  movMeanMagSqrd.set_size(magSqrd.size(0), magSqrd.size(1));
  loop_ub = magSqrd.size(0) * magSqrd.size(1);
  for (midm1 = 0; midm1 < loop_ub; midm1++) {
    movMeanMagSqrd[midm1] = 0.0;
  }
  nx = magSqrd.size(1);
  stride = magSqrd.size(0);
  if (magSqrd.size(0) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  if (magSqrd.size(0) - 1 >= 0) {
    outsize_idx_0 = magSqrd.size(1);
    b_loop_ub = magSqrd.size(1);
    overflow = (magSqrd.size(1) > 2147483646);
  }
  for (int j{0}; j < stride; j++) {
    xv.set_size(outsize_idx_0);
    for (midm1 = 0; midm1 < b_loop_ub; midm1++) {
      xv[midm1] = 0.0;
    }
    if (overflow) {
      coder::check_forloop_overflow_error();
    }
    for (midm1 = 0; midm1 < nx; midm1++) {
      xv[midm1] = magSqrd[j + midm1 * stride];
    }
    coder::vmovfun(xv, magSqrd.size(1), yv);
    len = yv.size(0);
    if (yv.size(0) > 2147483646) {
      coder::check_forloop_overflow_error();
    }
    for (midm1 = 0; midm1 < len; midm1++) {
      movMeanMagSqrd[j + midm1 * stride] = yv[midm1];
    }
  }
  if ((movMeanMagSqrd.size(0) == 0) || (movMeanMagSqrd.size(1) == 0)) {
    yv.set_size(movMeanMagSqrd.size(0));
    loop_ub = movMeanMagSqrd.size(0);
    for (midm1 = 0; midm1 < loop_ub; midm1++) {
      yv[midm1] = rtNaN;
    }
  } else {
    int n;
    boolean_T b_overflow;
    yv.set_size(movMeanMagSqrd.size(0));
    loop_ub = movMeanMagSqrd.size(0);
    for (midm1 = 0; midm1 < loop_ub; midm1++) {
      yv[midm1] = 0.0;
    }
    nx = movMeanMagSqrd.size(1);
    stride = movMeanMagSqrd.size(0);
    if (movMeanMagSqrd.size(0) > 2147483646) {
      coder::check_forloop_overflow_error();
    }
    loop_ub = movMeanMagSqrd.size(1);
    overflow = (movMeanMagSqrd.size(1) > 2147483646);
    n = movMeanMagSqrd.size(1);
    b_overflow = (movMeanMagSqrd.size(1) > 2147483646);
    for (int j{0}; j < stride; j++) {
      xv.set_size(nx);
      for (midm1 = 0; midm1 < loop_ub; midm1++) {
        xv[midm1] = 0.0;
      }
      if (overflow) {
        coder::check_forloop_overflow_error();
      }
      for (midm1 = 0; midm1 < nx; midm1++) {
        xv[midm1] = movMeanMagSqrd[j + midm1 * stride];
      }
      if (b_overflow) {
        coder::check_forloop_overflow_error();
      }
      midm1 = 0;
      int exitg1;
      do {
        exitg1 = 0;
        if (midm1 <= n - 1) {
          if (std::isnan(xv[midm1])) {
            yv[j] = rtNaN;
            exitg1 = 1;
          } else {
            midm1++;
          }
        } else {
          if (n <= 4) {
            if (n == 1) {
              yv[j] = xv[0];
            } else if (n == 2) {
              if (((xv[0] < 0.0) != (xv[1] < 0.0)) || std::isinf(xv[0])) {
                yv[j] = (xv[0] + xv[1]) / 2.0;
              } else {
                yv[j] = xv[0] + (xv[1] - xv[0]) / 2.0;
              }
            } else if (n == 3) {
              if (xv[0] < xv[1]) {
                if (xv[1] < xv[2]) {
                  outsize_idx_0 = 1;
                } else if (xv[0] < xv[2]) {
                  outsize_idx_0 = 2;
                } else {
                  outsize_idx_0 = 0;
                }
              } else if (xv[0] < xv[2]) {
                outsize_idx_0 = 0;
              } else if (xv[1] < xv[2]) {
                outsize_idx_0 = 2;
              } else {
                outsize_idx_0 = 1;
              }
              yv[j] = xv[outsize_idx_0];
            } else {
              if (xv[0] < xv[1]) {
                if (xv[1] < xv[2]) {
                  len = 0;
                  outsize_idx_0 = 1;
                  b_loop_ub = 2;
                } else if (xv[0] < xv[2]) {
                  len = 0;
                  outsize_idx_0 = 2;
                  b_loop_ub = 1;
                } else {
                  len = 2;
                  outsize_idx_0 = 0;
                  b_loop_ub = 1;
                }
              } else if (xv[0] < xv[2]) {
                len = 1;
                outsize_idx_0 = 0;
                b_loop_ub = 2;
              } else if (xv[1] < xv[2]) {
                len = 1;
                outsize_idx_0 = 2;
                b_loop_ub = 0;
              } else {
                len = 2;
                outsize_idx_0 = 1;
                b_loop_ub = 0;
              }
              if (xv[len] < xv[3]) {
                if (xv[3] < xv[b_loop_ub]) {
                  if (((xv[outsize_idx_0] < 0.0) != (xv[3] < 0.0)) ||
                      std::isinf(xv[outsize_idx_0])) {
                    yv[j] = (xv[outsize_idx_0] + xv[3]) / 2.0;
                  } else {
                    yv[j] =
                        xv[outsize_idx_0] + (xv[3] - xv[outsize_idx_0]) / 2.0;
                  }
                } else if (((xv[outsize_idx_0] < 0.0) !=
                            (xv[b_loop_ub] < 0.0)) ||
                           std::isinf(xv[outsize_idx_0])) {
                  yv[j] = (xv[outsize_idx_0] + xv[b_loop_ub]) / 2.0;
                } else {
                  yv[j] = xv[outsize_idx_0] +
                          (xv[b_loop_ub] - xv[outsize_idx_0]) / 2.0;
                }
              } else if (((xv[len] < 0.0) != (xv[outsize_idx_0] < 0.0)) ||
                         std::isinf(xv[len])) {
                yv[j] = (xv[len] + xv[outsize_idx_0]) / 2.0;
              } else {
                yv[j] = xv[len] + (xv[outsize_idx_0] - xv[len]) / 2.0;
              }
            }
          } else {
            midm1 = n >> 1;
            if ((n & 1) == 0) {
              varargin_1 = coder::internal::quickselect(xv, midm1 + 1, n, len,
                                                        b_loop_ub);
              yv[j] = varargin_1;
              if (midm1 < len) {
                double b;
                b = coder::internal::quickselect(xv, midm1, b_loop_ub - 1, len,
                                                 outsize_idx_0);
                if (((varargin_1 < 0.0) != (b < 0.0)) ||
                    std::isinf(varargin_1)) {
                  yv[j] = (varargin_1 + b) / 2.0;
                } else {
                  yv[j] = varargin_1 + (b - varargin_1) / 2.0;
                }
              }
            } else {
              yv[j] = coder::internal::quickselect(xv, midm1 + 1, n,
                                                   outsize_idx_0, len);
            }
          }
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
  }
  // transpose(median(transpose(movMeanMagSqrd)));%median(rand(80,32767),2);
  coder::repmat(yv, static_cast<double>(magSqrd.size(1)), movMeanMagSqrd);
  loop_ub = movMeanMagSqrd.size(0) * movMeanMagSqrd.size(1);
  for (midm1 = 0; midm1 < loop_ub; midm1++) {
    movMeanMagSqrd[midm1] = 10.0 * movMeanMagSqrd[midm1];
  }
  if ((magSqrd.size(0) != movMeanMagSqrd.size(0)) &&
      ((magSqrd.size(0) != 1) && (movMeanMagSqrd.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(magSqrd.size(0), movMeanMagSqrd.size(0),
                                g_emlrtECI);
  }
  if ((magSqrd.size(1) != movMeanMagSqrd.size(1)) &&
      ((magSqrd.size(1) != 1) && (movMeanMagSqrd.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(magSqrd.size(1), movMeanMagSqrd.size(1),
                                h_emlrtECI);
  }
  if ((magSqrd.size(0) == movMeanMagSqrd.size(0)) &&
      (magSqrd.size(1) == movMeanMagSqrd.size(1))) {
    r.set_size(magSqrd.size(0), magSqrd.size(1));
    for (midm1 = 0; midm1 < loop_ub_tmp; midm1++) {
      r[midm1] = (magSqrd[midm1] > movMeanMagSqrd[midm1]);
    }
  } else {
    gt(r, magSqrd, movMeanMagSqrd);
  }
  len = r.size(0) * r.size(1) - 1;
  for (outsize_idx_0 = 0; outsize_idx_0 <= len; outsize_idx_0++) {
    if (r[outsize_idx_0]) {
      midm1 = magSqrd.size(0) * magSqrd.size(1) - 1;
      if (outsize_idx_0 > midm1) {
        rtDynamicBoundsError(outsize_idx_0, 0, midm1, ab_emlrtBCI);
      }
      magSqrd[outsize_idx_0] = rtNaN;
    }
  }
  varargin_1 = dt;
  varargin_1 = varargin_1 * varargin_1 / T;
  coder::mean(magSqrd, yv);
  psd.set_size(yv.size(0));
  loop_ub = yv.size(0);
  for (midm1 = 0; midm1 < loop_ub; midm1++) {
    psd[midm1] = varargin_1 * yv[midm1];
  }
  // use median to exclude outliers from short pulses
}

//
// File trailer for wfmstft.cpp
//
// [EOF]
//
