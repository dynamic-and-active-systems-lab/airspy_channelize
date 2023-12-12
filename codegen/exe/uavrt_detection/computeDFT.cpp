//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeDFT.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "computeDFT.h"
#include "FFTImplementationCallback.h"
#include "eml_int_forloop_overflow_check.h"
#include "psdfreqvec.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const array<creal32_T, 2U> &xin
//                double nfft
//                double varargin_1
//                array<creal32_T, 2U> &Xx
//                array<double, 1U> &f
// Return Type  : void
//
namespace coder {
void computeDFT(const array<creal32_T, 2U> &xin, double nfft, double varargin_1,
                array<creal32_T, 2U> &Xx, array<double, 1U> &f)
{
  array<creal32_T, 2U> wrappedData;
  array<creal32_T, 2U> xw;
  array<creal32_T, 1U> x;
  array<float, 2U> costab;
  array<float, 2U> costab1q;
  array<float, 2U> sintab;
  array<float, 2U> sintabinv;
  int N2blue;
  int b_remainder;
  int i;
  int i1;
  int offset;
  boolean_T useRadix2;
  if (xin.size(0) > nfft) {
    int loop_ub_tmp;
    if (!(nfft >= 0.0)) {
      rtNonNegativeError(nfft, i_emlrtDCI);
    }
    i = static_cast<int>(std::floor(nfft));
    if (nfft != i) {
      rtIntegerError(nfft, h_emlrtDCI);
    }
    loop_ub_tmp = static_cast<int>(nfft);
    xw.set_size(loop_ub_tmp, xin.size(1));
    if (loop_ub_tmp != i) {
      rtIntegerError(nfft, j_emlrtDCI);
    }
    offset = loop_ub_tmp * xin.size(1);
    for (i = 0; i < offset; i++) {
      xw[i].re = 0.0F;
      xw[i].im = 0.0F;
    }
    i = xin.size(1);
    for (int j{0}; j < i; j++) {
      int i2;
      if (j + 1 > xin.size(1)) {
        rtDynamicBoundsError(j + 1, 1, xin.size(1), k_emlrtBCI);
      }
      offset = xin.size(0);
      x.set_size(xin.size(0));
      for (i1 = 0; i1 < offset; i1++) {
        x[i1] = xin[i1 + xin.size(0) * j];
      }
      if (!(nfft >= 1.0)) {
        b_rtErrorWithMessageID(1, kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
      }
      if (xin.size(0) == 1) {
        wrappedData.set_size(1, loop_ub_tmp);
        for (i1 = 0; i1 < loop_ub_tmp; i1++) {
          wrappedData[i1].re = 0.0F;
          wrappedData[i1].im = 0.0F;
        }
      } else {
        wrappedData.set_size(loop_ub_tmp, 1);
        for (i1 = 0; i1 < loop_ub_tmp; i1++) {
          wrappedData[i1].re = 0.0F;
          wrappedData[i1].im = 0.0F;
        }
      }
      i1 = static_cast<int>(static_cast<unsigned int>(xin.size(0)) /
                            static_cast<unsigned int>(nfft));
      offset = i1 * loop_ub_tmp;
      b_remainder = xin.size(0) - offset;
      if (b_remainder > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int k{0}; k < b_remainder; k++) {
        N2blue = wrappedData.size(0) * wrappedData.size(1);
        if ((k + 1 < 1) || (k + 1 > N2blue)) {
          rtDynamicBoundsError(k + 1, 1, N2blue, n_emlrtBCI);
        }
        i2 = (offset + k) + 1;
        useRadix2 = ((i2 < 1) || (i2 > xin.size(0)));
        if (useRadix2) {
          rtDynamicBoundsError(i2, 1, xin.size(0), m_emlrtBCI);
        }
        wrappedData[k].re = x[i2 - 1].re;
        if (k + 1 > N2blue) {
          rtDynamicBoundsError(k + 1, 1, N2blue, n_emlrtBCI);
        }
        wrappedData[k].im = x[i2 - 1].im;
      }
      N2blue = b_remainder + 1;
      for (int k{N2blue}; k <= loop_ub_tmp; k++) {
        i2 = wrappedData.size(0) * wrappedData.size(1);
        if ((k < 1) || (k > i2)) {
          rtDynamicBoundsError(k, 1, i2, o_emlrtBCI);
        }
        wrappedData[k - 1].re = 0.0F;
        if (k > i2) {
          rtDynamicBoundsError(k, 1, i2, o_emlrtBCI);
        }
        wrappedData[k - 1].im = 0.0F;
      }
      if (i1 > 2147483646) {
        check_forloop_overflow_error();
      }
      for (b_remainder = 0; b_remainder < i1; b_remainder++) {
        offset = b_remainder * loop_ub_tmp;
        for (int k{0}; k < loop_ub_tmp; k++) {
          N2blue = wrappedData.size(0) * wrappedData.size(1);
          if (k + 1 > N2blue) {
            rtDynamicBoundsError(k + 1, 1, N2blue, r_emlrtBCI);
          }
          i2 = (offset + k) + 1;
          useRadix2 = ((i2 < 1) || (i2 > xin.size(0)));
          if (useRadix2) {
            rtDynamicBoundsError(i2, 1, xin.size(0), q_emlrtBCI);
          }
          wrappedData[k].re = wrappedData[k].re + x[i2 - 1].re;
          if (k + 1 > N2blue) {
            rtDynamicBoundsError(k + 1, 1, N2blue, p_emlrtBCI);
          }
          wrappedData[k].im = wrappedData[k].im + x[i2 - 1].im;
        }
      }
      if (j + 1 > xw.size(1)) {
        rtDynamicBoundsError(j + 1, 1, xw.size(1), l_emlrtBCI);
      }
      offset = wrappedData.size(0) * wrappedData.size(1);
      rtSubAssignSizeCheck(xw.size(), 1, &offset, 1, d_emlrtECI);
      for (i1 = 0; i1 < offset; i1++) {
        xw[i1 + xw.size(0) * j] = wrappedData[i1];
      }
    }
  } else {
    xw.set_size(xin.size(0), xin.size(1));
    offset = xin.size(0) * xin.size(1);
    for (i = 0; i < offset; i++) {
      xw[i] = xin[i];
    }
  }
  if (xw.size(0) == 1) {
    w_rtErrorWithMessageID(hb_emlrtRTEI.fName, hb_emlrtRTEI.lineNo);
  }
  if ((!(nfft >= 0.0)) || (!(nfft == std::floor(nfft)))) {
    x_rtErrorWithMessageID(ib_emlrtRTEI.fName, ib_emlrtRTEI.lineNo);
  }
  if (!(nfft <= 2.147483647E+9)) {
    y_rtErrorWithMessageID(jb_emlrtRTEI.fName, jb_emlrtRTEI.lineNo);
  }
  if ((xw.size(0) == 0) || (xw.size(1) == 0) || (static_cast<int>(nfft) == 0)) {
    Xx.set_size(static_cast<int>(nfft), xw.size(1));
    offset = static_cast<int>(nfft) * xw.size(1);
    for (i = 0; i < offset; i++) {
      Xx[i].re = 0.0F;
      Xx[i].im = 0.0F;
    }
  } else {
    float e;
    useRadix2 =
        ((static_cast<int>(nfft) > 0) &&
         ((static_cast<int>(nfft) & (static_cast<int>(nfft) - 1)) == 0));
    N2blue = internal::fft::FFTImplementationCallback::get_algo_sizes(
        static_cast<int>(nfft), useRadix2, offset);
    e = 6.28318548F / static_cast<float>(offset);
    b_remainder = offset / 2 / 2;
    costab1q.set_size(1, b_remainder + 1);
    costab1q[0] = 1.0F;
    offset = b_remainder / 2 - 1;
    for (int k{0}; k <= offset; k++) {
      costab1q[k + 1] = std::cos(e * static_cast<float>(k + 1));
    }
    i = offset + 2;
    i1 = b_remainder - 1;
    for (int k{i}; k <= i1; k++) {
      costab1q[k] = std::sin(e * static_cast<float>(b_remainder - k));
    }
    costab1q[b_remainder] = 0.0F;
    if (!useRadix2) {
      b_remainder = costab1q.size(1) - 1;
      offset = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, offset + 1);
      sintab.set_size(1, offset + 1);
      costab[0] = 1.0F;
      sintab[0] = 0.0F;
      sintabinv.set_size(1, offset + 1);
      for (int k{0}; k < b_remainder; k++) {
        sintabinv[k + 1] = costab1q[(b_remainder - k) - 1];
      }
      i = costab1q.size(1);
      for (int k{i}; k <= offset; k++) {
        sintabinv[k] = costab1q[k - b_remainder];
      }
      for (int k{0}; k < b_remainder; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = -costab1q[(b_remainder - k) - 1];
      }
      i = costab1q.size(1);
      for (int k{i}; k <= offset; k++) {
        costab[k] = -costab1q[offset - k];
        sintab[k] = -costab1q[k - b_remainder];
      }
    } else {
      b_remainder = costab1q.size(1) - 1;
      offset = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, offset + 1);
      sintab.set_size(1, offset + 1);
      costab[0] = 1.0F;
      sintab[0] = 0.0F;
      for (int k{0}; k < b_remainder; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = -costab1q[(b_remainder - k) - 1];
      }
      i = costab1q.size(1);
      for (int k{i}; k <= offset; k++) {
        costab[k] = -costab1q[offset - k];
        sintab[k] = -costab1q[k - b_remainder];
      }
      sintabinv.set_size(1, 0);
    }
    if (useRadix2) {
      internal::fft::FFTImplementationCallback::r2br_r2dit_trig(
          xw, static_cast<int>(nfft), costab, sintab, Xx);
    } else {
      internal::fft::FFTImplementationCallback::dobluesteinfft(
          xw, N2blue, static_cast<int>(nfft), costab, sintab, sintabinv, Xx);
    }
  }
  psdfreqvec(nfft, varargin_1, f);
}

} // namespace coder

//
// File trailer for computeDFT.cpp
//
// [EOF]
//
