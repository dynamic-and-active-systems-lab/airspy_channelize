//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FFTImplementationCallback.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "FFTImplementationCallback.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>

// Variable Definitions
static rtDoubleCheckInfo k_emlrtDCI{
    33,                     // lineNo
    28,                     // colNo
    "bluestein_setup_impl", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
    "bluesteinSetup.m", // pName
    4                   // checkKind
};

// Function Definitions
//
// Arguments    : const array<creal32_T, 1U> &x
//                int unsigned_nRows
//                const array<float, 2U> &costab
//                const array<float, 2U> &sintab
//                array<creal32_T, 1U> &y
// Return Type  : void
//
namespace coder {
namespace internal {
namespace fft {
void FFTImplementationCallback::r2br_r2dit_trig_impl(
    const array<creal32_T, 1U> &x, int unsigned_nRows,
    const array<float, 2U> &costab, const array<float, 2U> &sintab,
    array<creal32_T, 1U> &y)
{
  float temp_im;
  float temp_re;
  float temp_re_tmp;
  float twid_re;
  int i;
  int iDelta;
  int iDelta2;
  int iheight;
  int ihi;
  int iy;
  int j;
  int ju;
  int k;
  int nRowsD2;
  y.set_size(unsigned_nRows);
  if (unsigned_nRows > x.size(0)) {
    y.set_size(unsigned_nRows);
    for (iy = 0; iy < unsigned_nRows; iy++) {
      y[iy].re = 0.0F;
      y[iy].im = 0.0F;
    }
  }
  j = x.size(0);
  if (j > unsigned_nRows) {
    j = unsigned_nRows;
  }
  ihi = unsigned_nRows - 2;
  nRowsD2 = unsigned_nRows / 2;
  k = nRowsD2 / 2;
  iy = 0;
  ju = 0;
  if (j - 1 > 2147483646) {
    check_forloop_overflow_error();
  }
  for (i = 0; i <= j - 2; i++) {
    boolean_T tst;
    y[iy] = x[i];
    iy = unsigned_nRows;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }
    iy = ju;
  }
  if (j - 2 < 0) {
    j = 0;
  } else {
    j--;
  }
  y[iy] = x[j];
  if (unsigned_nRows > 1) {
    for (i = 0; i <= ihi; i += 2) {
      temp_re_tmp = y[i + 1].re;
      temp_im = y[i + 1].im;
      temp_re = y[i].re;
      twid_re = y[i].im;
      y[i + 1].re = temp_re - temp_re_tmp;
      y[i + 1].im = twid_re - temp_im;
      y[i].re = temp_re + temp_re_tmp;
      y[i].im = twid_re + temp_im;
    }
  }
  iDelta = 2;
  iDelta2 = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < iheight; i += iDelta2) {
      iy = i + iDelta;
      temp_re = y[iy].re;
      temp_im = y[iy].im;
      y[iy].re = y[i].re - temp_re;
      y[iy].im = y[i].im - temp_im;
      y[i].re = y[i].re + temp_re;
      y[i].im = y[i].im + temp_im;
    }
    iy = 1;
    for (j = k; j < nRowsD2; j += k) {
      float twid_im;
      twid_re = costab[j];
      twid_im = sintab[j];
      i = iy;
      ihi = iy + iheight;
      while (i < ihi) {
        ju = i + iDelta;
        temp_re_tmp = y[ju].im;
        temp_im = y[ju].re;
        temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
        y[ju].re = y[i].re - temp_re;
        y[ju].im = y[i].im - temp_im;
        y[i].re = y[i].re + temp_re;
        y[i].im = y[i].im + temp_im;
        i += iDelta2;
      }
      iy++;
    }
    k /= 2;
    iDelta = iDelta2;
    iDelta2 += iDelta2;
    iheight -= iDelta;
  }
}

//
// Arguments    : const array<creal_T, 1U> &x
//                int unsigned_nRows
//                const array<double, 2U> &costab
//                const array<double, 2U> &sintab
//                array<creal_T, 1U> &y
// Return Type  : void
//
void FFTImplementationCallback::r2br_r2dit_trig_impl(
    const array<creal_T, 1U> &x, int unsigned_nRows,
    const array<double, 2U> &costab, const array<double, 2U> &sintab,
    array<creal_T, 1U> &y)
{
  double temp_im;
  double temp_re;
  double temp_re_tmp;
  double twid_re;
  int i;
  int iDelta;
  int iDelta2;
  int iheight;
  int ihi;
  int iy;
  int j;
  int ju;
  int k;
  int nRowsD2;
  y.set_size(unsigned_nRows);
  if (unsigned_nRows > x.size(0)) {
    y.set_size(unsigned_nRows);
    for (iy = 0; iy < unsigned_nRows; iy++) {
      y[iy].re = 0.0;
      y[iy].im = 0.0;
    }
  }
  j = x.size(0);
  if (j > unsigned_nRows) {
    j = unsigned_nRows;
  }
  ihi = unsigned_nRows - 2;
  nRowsD2 = unsigned_nRows / 2;
  k = nRowsD2 / 2;
  iy = 0;
  ju = 0;
  if (j - 1 > 2147483646) {
    check_forloop_overflow_error();
  }
  for (i = 0; i <= j - 2; i++) {
    boolean_T tst;
    y[iy] = x[i];
    iy = unsigned_nRows;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }
    iy = ju;
  }
  if (j - 2 < 0) {
    j = 0;
  } else {
    j--;
  }
  y[iy] = x[j];
  if (unsigned_nRows > 1) {
    for (i = 0; i <= ihi; i += 2) {
      temp_re_tmp = y[i + 1].re;
      temp_im = y[i + 1].im;
      temp_re = y[i].re;
      twid_re = y[i].im;
      y[i + 1].re = temp_re - temp_re_tmp;
      y[i + 1].im = twid_re - temp_im;
      y[i].re = temp_re + temp_re_tmp;
      y[i].im = twid_re + temp_im;
    }
  }
  iDelta = 2;
  iDelta2 = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < iheight; i += iDelta2) {
      iy = i + iDelta;
      temp_re = y[iy].re;
      temp_im = y[iy].im;
      y[iy].re = y[i].re - temp_re;
      y[iy].im = y[i].im - temp_im;
      y[i].re = y[i].re + temp_re;
      y[i].im = y[i].im + temp_im;
    }
    iy = 1;
    for (j = k; j < nRowsD2; j += k) {
      double twid_im;
      twid_re = costab[j];
      twid_im = sintab[j];
      i = iy;
      ihi = iy + iheight;
      while (i < ihi) {
        ju = i + iDelta;
        temp_re_tmp = y[ju].im;
        temp_im = y[ju].re;
        temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
        y[ju].re = y[i].re - temp_re;
        y[ju].im = y[i].im - temp_im;
        y[i].re = y[i].re + temp_re;
        y[i].im = y[i].im + temp_im;
        i += iDelta2;
      }
      iy++;
    }
    k /= 2;
    iDelta = iDelta2;
    iDelta2 += iDelta2;
    iheight -= iDelta;
  }
}

//
// Arguments    : const array<creal32_T, 2U> &x
//                int n2blue
//                int nfft
//                const array<float, 2U> &costab
//                const array<float, 2U> &sintab
//                const array<float, 2U> &sintabinv
//                array<creal32_T, 2U> &y
// Return Type  : void
//
void FFTImplementationCallback::dobluesteinfft(
    const array<creal32_T, 2U> &x, int n2blue, int nfft,
    const array<float, 2U> &costab, const array<float, 2U> &sintab,
    const array<float, 2U> &sintabinv, array<creal32_T, 2U> &y)
{
  array<creal32_T, 1U> fv;
  array<creal32_T, 1U> fy;
  array<creal32_T, 1U> r;
  array<creal32_T, 1U> wwc;
  float re_tmp;
  float temp_im;
  float temp_re;
  float temp_re_tmp;
  float twid_im;
  float twid_re;
  int b_i;
  int b_k;
  int b_y;
  int i;
  int iDelta;
  int iDelta2;
  int iheight;
  int iy;
  int ju;
  int minNrowsNx;
  int nInt2;
  int nInt2m1;
  int nRowsD2;
  int rt;
  int xoff;
  boolean_T tst;
  nInt2m1 = (nfft + nfft) - 1;
  if (nInt2m1 < 0) {
    rtNonNegativeError(static_cast<double>(nInt2m1), k_emlrtDCI);
  }
  wwc.set_size(nInt2m1);
  rt = 0;
  wwc[nfft - 1].re = 1.0F;
  wwc[nfft - 1].im = 0.0F;
  nInt2 = nfft << 1;
  if (nfft - 1 > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k <= nfft - 2; k++) {
    float nt_im;
    b_y = ((k + 1) << 1) - 1;
    if (nInt2 - rt <= b_y) {
      rt += b_y - nInt2;
    } else {
      rt += b_y;
    }
    nt_im = -3.14159274F * static_cast<float>(rt) / static_cast<float>(nfft);
    i = (nfft - k) - 2;
    wwc[i].re = std::cos(nt_im);
    wwc[i].im = -std::sin(nt_im);
  }
  i = nInt2m1 - 1;
  for (int k{i}; k >= nfft; k--) {
    wwc[k] = wwc[(nInt2m1 - k) - 1];
  }
  nInt2m1 = x.size(0);
  y.set_size(nfft, x.size(1));
  if (nfft > x.size(0)) {
    y.set_size(nfft, x.size(1));
    b_y = nfft * x.size(1);
    for (i = 0; i < b_y; i++) {
      y[i].re = 0.0F;
      y[i].im = 0.0F;
    }
  }
  if (x.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  b_y = x.size(1) - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    fv, fy, r, xoff, ju, minNrowsNx, b_k, iy, temp_re, temp_im, twid_im,       \
    re_tmp, iDelta, nRowsD2, b_i, tst, temp_re_tmp, twid_re, iDelta2, iheight)

  for (int chan = 0; chan <= b_y; chan++) {
    xoff = chan * nInt2m1;
    r.set_size(nfft);
    if (nfft > x.size(0)) {
      r.set_size(nfft);
      for (ju = 0; ju < nfft; ju++) {
        r[ju].re = 0.0F;
        r[ju].im = 0.0F;
      }
    }
    minNrowsNx = x.size(0);
    if (nfft <= minNrowsNx) {
      minNrowsNx = nfft;
    }
    if (minNrowsNx > 2147483646) {
      check_forloop_overflow_error();
    }
    for (b_k = 0; b_k < minNrowsNx; b_k++) {
      iy = (nfft + b_k) - 1;
      temp_re = wwc[iy].re;
      temp_im = wwc[iy].im;
      ju = xoff + b_k;
      twid_im = x[ju].im;
      re_tmp = x[ju].re;
      r[b_k].re = temp_re * re_tmp + temp_im * twid_im;
      r[b_k].im = temp_re * twid_im - temp_im * re_tmp;
    }
    iy = minNrowsNx + 1;
    if ((minNrowsNx + 1 <= nfft) && (nfft > 2147483646)) {
      check_forloop_overflow_error();
    }
    for (b_k = iy; b_k <= nfft; b_k++) {
      r[b_k - 1].re = 0.0F;
      r[b_k - 1].im = 0.0F;
    }
    fy.set_size(n2blue);
    if (n2blue > r.size(0)) {
      fy.set_size(n2blue);
      for (ju = 0; ju < n2blue; ju++) {
        fy[ju].re = 0.0F;
        fy[ju].im = 0.0F;
      }
    }
    iy = r.size(0);
    iDelta = n2blue;
    if (iy <= n2blue) {
      iDelta = iy;
    }
    minNrowsNx = n2blue - 2;
    nRowsD2 = n2blue / 2;
    b_k = nRowsD2 / 2;
    iy = 0;
    ju = 0;
    if (iDelta - 1 > 2147483646) {
      check_forloop_overflow_error();
    }
    for (b_i = 0; b_i <= iDelta - 2; b_i++) {
      fy[iy] = r[b_i];
      xoff = n2blue;
      tst = true;
      while (tst) {
        xoff >>= 1;
        ju ^= xoff;
        tst = ((ju & xoff) == 0);
      }
      iy = ju;
    }
    if (iDelta - 2 < 0) {
      xoff = 0;
    } else {
      xoff = iDelta - 1;
    }
    fy[iy] = r[xoff];
    if (n2blue > 1) {
      for (b_i = 0; b_i <= minNrowsNx; b_i += 2) {
        temp_re_tmp = fy[b_i + 1].re;
        temp_im = fy[b_i + 1].im;
        re_tmp = fy[b_i].re;
        twid_re = fy[b_i].im;
        fy[b_i + 1].re = re_tmp - temp_re_tmp;
        fy[b_i + 1].im = twid_re - temp_im;
        fy[b_i].re = re_tmp + temp_re_tmp;
        fy[b_i].im = twid_re + temp_im;
      }
    }
    iDelta = 2;
    iDelta2 = 4;
    iheight = ((b_k - 1) << 2) + 1;
    while (b_k > 0) {
      for (b_i = 0; b_i < iheight; b_i += iDelta2) {
        iy = b_i + iDelta;
        temp_re = fy[iy].re;
        temp_im = fy[iy].im;
        fy[iy].re = fy[b_i].re - temp_re;
        fy[iy].im = fy[b_i].im - temp_im;
        fy[b_i].re = fy[b_i].re + temp_re;
        fy[b_i].im = fy[b_i].im + temp_im;
      }
      xoff = 1;
      for (minNrowsNx = b_k; minNrowsNx < nRowsD2; minNrowsNx += b_k) {
        twid_re = costab[minNrowsNx];
        twid_im = sintab[minNrowsNx];
        b_i = xoff;
        iy = xoff + iheight;
        while (b_i < iy) {
          ju = b_i + iDelta;
          temp_re_tmp = fy[ju].im;
          temp_im = fy[ju].re;
          temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
          temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
          fy[ju].re = fy[b_i].re - temp_re;
          fy[ju].im = fy[b_i].im - temp_im;
          fy[b_i].re = fy[b_i].re + temp_re;
          fy[b_i].im = fy[b_i].im + temp_im;
          b_i += iDelta2;
        }
        xoff++;
      }
      b_k /= 2;
      iDelta = iDelta2;
      iDelta2 += iDelta2;
      iheight -= iDelta;
    }
    FFTImplementationCallback::r2br_r2dit_trig_impl(wwc, n2blue, costab, sintab,
                                                    fv);
    iy = fy.size(0);
    for (ju = 0; ju < iy; ju++) {
      re_tmp = fy[ju].re;
      temp_im = fv[ju].im;
      twid_re = fy[ju].im;
      twid_im = fv[ju].re;
      fy[ju].re = re_tmp * twid_im - twid_re * temp_im;
      fy[ju].im = re_tmp * temp_im + twid_re * twid_im;
    }
    FFTImplementationCallback::r2br_r2dit_trig_impl(fy, n2blue, costab,
                                                    sintabinv, fv);
    if (fv.size(0) > 1) {
      temp_im = 1.0F / static_cast<float>(fv.size(0));
      iy = fv.size(0);
      for (ju = 0; ju < iy; ju++) {
        fv[ju].re = temp_im * fv[ju].re;
        fv[ju].im = temp_im * fv[ju].im;
      }
    }
    iy = static_cast<int>(static_cast<float>(nfft));
    xoff = wwc.size(0);
    if ((static_cast<int>(static_cast<float>(nfft)) <= wwc.size(0)) &&
        (wwc.size(0) > 2147483646)) {
      check_forloop_overflow_error();
    }
    for (b_k = iy; b_k <= xoff; b_k++) {
      twid_im = wwc[b_k - 1].re;
      re_tmp = fv[b_k - 1].im;
      temp_im = wwc[b_k - 1].im;
      twid_re = fv[b_k - 1].re;
      ju = b_k - static_cast<int>(static_cast<float>(nfft));
      r[ju].re = twid_im * twid_re + temp_im * re_tmp;
      r[ju].im = twid_im * re_tmp - temp_im * twid_re;
    }
    iy = r.size(0);
    for (ju = 0; ju < iy; ju++) {
      y[ju + y.size(0) * chan] = r[ju];
    }
  }
}

//
// Arguments    : const array<creal_T, 2U> &x
//                int n2blue
//                int nfft
//                const array<double, 2U> &costab
//                const array<double, 2U> &sintab
//                const array<double, 2U> &sintabinv
//                array<creal_T, 2U> &y
// Return Type  : void
//
void FFTImplementationCallback::dobluesteinfft(
    const array<creal_T, 2U> &x, int n2blue, int nfft,
    const array<double, 2U> &costab, const array<double, 2U> &sintab,
    const array<double, 2U> &sintabinv, array<creal_T, 2U> &y)
{
  array<creal_T, 1U> fv;
  array<creal_T, 1U> fy;
  array<creal_T, 1U> r;
  array<creal_T, 1U> wwc;
  double b_re_tmp;
  double nt_im;
  double nt_re;
  double re_tmp;
  int b_y;
  int i;
  int nInt2;
  int nInt2m1;
  int rt;
  nInt2m1 = (nfft + nfft) - 1;
  if (nInt2m1 < 0) {
    rtNonNegativeError(static_cast<double>(nInt2m1), k_emlrtDCI);
  }
  wwc.set_size(nInt2m1);
  rt = 0;
  wwc[nfft - 1].re = 1.0;
  wwc[nfft - 1].im = 0.0;
  nInt2 = nfft << 1;
  if (nfft - 1 > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k <= nfft - 2; k++) {
    b_y = ((k + 1) << 1) - 1;
    if (nInt2 - rt <= b_y) {
      rt += b_y - nInt2;
    } else {
      rt += b_y;
    }
    nt_im = -3.1415926535897931 * static_cast<double>(rt) /
            static_cast<double>(nfft);
    i = (nfft - k) - 2;
    wwc[i].re = std::cos(nt_im);
    wwc[i].im = -std::sin(nt_im);
  }
  i = nInt2m1 - 1;
  for (int k{i}; k >= nfft; k--) {
    wwc[k] = wwc[(nInt2m1 - k) - 1];
  }
  y.set_size(nfft, 1);
  if (nfft > x.size(0)) {
    y.set_size(nfft, 1);
    for (i = 0; i < nfft; i++) {
      y[i].re = 0.0;
      y[i].im = 0.0;
    }
  }
  nInt2m1 = x.size(0);
  if (nfft <= nInt2m1) {
    nInt2m1 = nfft;
  }
  rt = nInt2m1 + 1;
  nInt2 = wwc.size(0);
  r.set_size(nfft);
  if (nfft > x.size(0)) {
    r.set_size(nfft);
    for (i = 0; i < nfft; i++) {
      r[i].re = 0.0;
      r[i].im = 0.0;
    }
  }
  if (nInt2m1 > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nInt2m1; k++) {
    b_y = (nfft + k) - 1;
    nt_re = wwc[b_y].re;
    nt_im = wwc[b_y].im;
    re_tmp = x[k].im;
    b_re_tmp = x[k].re;
    r[k].re = nt_re * b_re_tmp + nt_im * re_tmp;
    r[k].im = nt_re * re_tmp - nt_im * b_re_tmp;
  }
  if ((nInt2m1 + 1 <= nfft) && (nfft > 2147483646)) {
    check_forloop_overflow_error();
  }
  for (int k{rt}; k <= nfft; k++) {
    r[k - 1].re = 0.0;
    r[k - 1].im = 0.0;
  }
  FFTImplementationCallback::r2br_r2dit_trig_impl(r, n2blue, costab, sintab,
                                                  fy);
  FFTImplementationCallback::r2br_r2dit_trig_impl(wwc, n2blue, costab, sintab,
                                                  fv);
  b_y = fy.size(0);
  for (i = 0; i < b_y; i++) {
    nt_re = fy[i].re;
    nt_im = fv[i].im;
    re_tmp = fy[i].im;
    b_re_tmp = fv[i].re;
    fy[i].re = nt_re * b_re_tmp - re_tmp * nt_im;
    fy[i].im = nt_re * nt_im + re_tmp * b_re_tmp;
  }
  FFTImplementationCallback::r2br_r2dit_trig_impl(fy, n2blue, costab, sintabinv,
                                                  fv);
  if (fv.size(0) > 1) {
    nt_re = 1.0 / static_cast<double>(fv.size(0));
    b_y = fv.size(0);
    for (i = 0; i < b_y; i++) {
      fv[i].re = nt_re * fv[i].re;
      fv[i].im = nt_re * fv[i].im;
    }
  }
  if ((nfft <= wwc.size(0)) && (wwc.size(0) > 2147483646)) {
    check_forloop_overflow_error();
  }
  for (int k{nfft}; k <= nInt2; k++) {
    re_tmp = wwc[k - 1].re;
    b_re_tmp = fv[k - 1].im;
    nt_re = wwc[k - 1].im;
    nt_im = fv[k - 1].re;
    i = k - nfft;
    r[i].re = re_tmp * nt_im + nt_re * b_re_tmp;
    r[i].im = re_tmp * b_re_tmp - nt_re * nt_im;
  }
  b_y = r.size(0);
  for (i = 0; i < b_y; i++) {
    y[i] = r[i];
  }
}

//
// Arguments    : const array<creal_T, 3U> &x
//                int n2blue
//                int nfft
//                const array<double, 2U> &costab
//                const array<double, 2U> &sintab
//                const array<double, 2U> &sintabinv
//                array<creal_T, 3U> &y
// Return Type  : void
//
void FFTImplementationCallback::dobluesteinfft(
    const array<creal_T, 3U> &x, int n2blue, int nfft,
    const array<double, 2U> &costab, const array<double, 2U> &sintab,
    const array<double, 2U> &sintabinv, array<creal_T, 3U> &y)
{
  array<creal_T, 1U> fv;
  array<creal_T, 1U> fy;
  array<creal_T, 1U> r;
  array<creal_T, 1U> wwc;
  double a_im;
  double a_re;
  double b_re_tmp;
  double re_tmp;
  int b_k;
  int b_y;
  int i;
  int i1;
  int minNrowsNx;
  int nChan;
  int nInt2;
  int nInt2m1;
  int rt;
  int u0;
  int xoff;
  nChan = x.size(1) * x.size(2);
  nInt2m1 = (nfft + nfft) - 1;
  if (nInt2m1 < 0) {
    rtNonNegativeError(static_cast<double>(nInt2m1), k_emlrtDCI);
  }
  wwc.set_size(nInt2m1);
  rt = 0;
  wwc[nfft - 1].re = 1.0;
  wwc[nfft - 1].im = 0.0;
  nInt2 = nfft << 1;
  if (nfft - 1 > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k <= nfft - 2; k++) {
    double nt_im;
    b_y = ((k + 1) << 1) - 1;
    if (nInt2 - rt <= b_y) {
      rt += b_y - nInt2;
    } else {
      rt += b_y;
    }
    nt_im = -3.1415926535897931 * static_cast<double>(rt) /
            static_cast<double>(nfft);
    i = (nfft - k) - 2;
    wwc[i].re = std::cos(nt_im);
    wwc[i].im = -std::sin(nt_im);
  }
  i = nInt2m1 - 1;
  for (int k{i}; k >= nfft; k--) {
    wwc[k] = wwc[(nInt2m1 - k) - 1];
  }
  nInt2m1 = x.size(0);
  y.set_size(nfft, x.size(1), x.size(2));
  if (nfft > x.size(0)) {
    y.set_size(nfft, x.size(1), x.size(2));
    b_y = nfft * x.size(1) * x.size(2);
    for (i = 0; i < b_y; i++) {
      y[i].re = 0.0;
      y[i].im = 0.0;
    }
  }
  if (nChan > 2147483646) {
    check_forloop_overflow_error();
  }
  b_y = nChan - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    fv, fy, r, xoff, i1, minNrowsNx, b_k, u0, a_re, a_im, re_tmp, b_re_tmp)

  for (int chan = 0; chan <= b_y; chan++) {
    xoff = chan * nInt2m1;
    r.set_size(nfft);
    if (nfft > x.size(0)) {
      r.set_size(nfft);
      for (i1 = 0; i1 < nfft; i1++) {
        r[i1].re = 0.0;
        r[i1].im = 0.0;
      }
    }
    minNrowsNx = x.size(0);
    if (nfft <= minNrowsNx) {
      minNrowsNx = nfft;
    }
    if (minNrowsNx > 2147483646) {
      check_forloop_overflow_error();
    }
    for (b_k = 0; b_k < minNrowsNx; b_k++) {
      u0 = (nfft + b_k) - 1;
      a_re = wwc[u0].re;
      a_im = wwc[u0].im;
      i1 = xoff + b_k;
      re_tmp = x[i1].im;
      b_re_tmp = x[i1].re;
      r[b_k].re = a_re * b_re_tmp + a_im * re_tmp;
      r[b_k].im = a_re * re_tmp - a_im * b_re_tmp;
    }
    u0 = minNrowsNx + 1;
    if ((minNrowsNx + 1 <= nfft) && (nfft > 2147483646)) {
      check_forloop_overflow_error();
    }
    for (b_k = u0; b_k <= nfft; b_k++) {
      r[b_k - 1].re = 0.0;
      r[b_k - 1].im = 0.0;
    }
    FFTImplementationCallback::r2br_r2dit_trig_impl(r, n2blue, costab, sintab,
                                                    fy);
    FFTImplementationCallback::r2br_r2dit_trig_impl(wwc, n2blue, costab, sintab,
                                                    fv);
    u0 = fy.size(0);
    for (i1 = 0; i1 < u0; i1++) {
      a_re = fy[i1].re;
      a_im = fv[i1].im;
      re_tmp = fy[i1].im;
      b_re_tmp = fv[i1].re;
      fy[i1].re = a_re * b_re_tmp - re_tmp * a_im;
      fy[i1].im = a_re * a_im + re_tmp * b_re_tmp;
    }
    FFTImplementationCallback::r2br_r2dit_trig_impl(fy, n2blue, costab,
                                                    sintabinv, fv);
    if (fv.size(0) > 1) {
      a_re = 1.0 / static_cast<double>(fv.size(0));
      u0 = fv.size(0);
      for (i1 = 0; i1 < u0; i1++) {
        fv[i1].re = a_re * fv[i1].re;
        fv[i1].im = a_re * fv[i1].im;
      }
    }
    u0 = wwc.size(0);
    if ((nfft <= wwc.size(0)) && (wwc.size(0) > 2147483646)) {
      check_forloop_overflow_error();
    }
    for (b_k = nfft; b_k <= u0; b_k++) {
      re_tmp = wwc[b_k - 1].re;
      b_re_tmp = fv[b_k - 1].im;
      a_re = wwc[b_k - 1].im;
      a_im = fv[b_k - 1].re;
      i1 = b_k - nfft;
      r[i1].re = re_tmp * a_im + a_re * b_re_tmp;
      r[i1].im = re_tmp * b_re_tmp - a_re * a_im;
    }
    xoff = y.size(0);
    u0 = r.size(0);
    for (i1 = 0; i1 < u0; i1++) {
      y[i1 + xoff * chan] = r[i1];
    }
  }
}

//
// Arguments    : int nRows
//                boolean_T useRadix2
//                array<double, 2U> &costab
//                array<double, 2U> &sintab
//                array<double, 2U> &sintabinv
// Return Type  : void
//
void FFTImplementationCallback::generate_twiddle_tables(
    int nRows, boolean_T useRadix2, array<double, 2U> &costab,
    array<double, 2U> &sintab, array<double, 2U> &sintabinv)
{
  array<double, 2U> costab1q;
  double e;
  int i;
  int n;
  int nd2;
  e = 6.2831853071795862 / static_cast<double>(nRows);
  n = nRows / 2 / 2;
  costab1q.set_size(1, n + 1);
  costab1q[0] = 1.0;
  nd2 = n / 2 - 1;
  for (int k{0}; k <= nd2; k++) {
    costab1q[k + 1] = std::cos(e * (static_cast<double>(k) + 1.0));
  }
  i = nd2 + 2;
  nd2 = n - 1;
  for (int k{i}; k <= nd2; k++) {
    costab1q[k] = std::sin(e * static_cast<double>(n - k));
  }
  costab1q[n] = 0.0;
  if (!useRadix2) {
    n = costab1q.size(1) - 1;
    nd2 = (costab1q.size(1) - 1) << 1;
    costab.set_size(1, nd2 + 1);
    sintab.set_size(1, nd2 + 1);
    costab[0] = 1.0;
    sintab[0] = 0.0;
    sintabinv.set_size(1, nd2 + 1);
    for (int k{0}; k < n; k++) {
      sintabinv[k + 1] = costab1q[(n - k) - 1];
    }
    i = costab1q.size(1);
    for (int k{i}; k <= nd2; k++) {
      sintabinv[k] = costab1q[k - n];
    }
    for (int k{0}; k < n; k++) {
      costab[k + 1] = costab1q[k + 1];
      sintab[k + 1] = -costab1q[(n - k) - 1];
    }
    i = costab1q.size(1);
    for (int k{i}; k <= nd2; k++) {
      costab[k] = -costab1q[nd2 - k];
      sintab[k] = -costab1q[k - n];
    }
  } else {
    n = costab1q.size(1) - 1;
    nd2 = (costab1q.size(1) - 1) << 1;
    costab.set_size(1, nd2 + 1);
    sintab.set_size(1, nd2 + 1);
    costab[0] = 1.0;
    sintab[0] = 0.0;
    for (int k{0}; k < n; k++) {
      costab[k + 1] = costab1q[k + 1];
      sintab[k + 1] = -costab1q[(n - k) - 1];
    }
    i = costab1q.size(1);
    for (int k{i}; k <= nd2; k++) {
      costab[k] = -costab1q[nd2 - k];
      sintab[k] = -costab1q[k - n];
    }
    sintabinv.set_size(1, 0);
  }
}

//
// Arguments    : int nfft
//                boolean_T useRadix2
//                int &nRows
// Return Type  : int
//
int FFTImplementationCallback::get_algo_sizes(int nfft, boolean_T useRadix2,
                                              int &nRows)
{
  static rtRunTimeErrorInfo bd_emlrtRTEI{
      417,                                        // lineNo
      17,                                         // colNo
      "FFTImplementationCallback/get_algo_sizes", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/shared/coder/coder/lib/+coder/"
      "+internal/FFTImplementationCallback.m" // pName
  };
  int n2blue;
  n2blue = 1;
  if (useRadix2) {
    nRows = nfft;
  } else {
    int n;
    if (nfft > 0) {
      int pmax;
      n = (nfft + nfft) - 1;
      pmax = 31;
      if (n <= 1) {
        pmax = 0;
      } else {
        int pmin;
        boolean_T exitg1;
        pmin = 0;
        exitg1 = false;
        while ((!exitg1) && (pmax - pmin > 1)) {
          int k;
          int pow2p;
          k = (pmin + pmax) >> 1;
          pow2p = 1 << k;
          if (pow2p == n) {
            pmax = k;
            exitg1 = true;
          } else if (pow2p > n) {
            pmax = k;
          } else {
            pmin = k;
          }
        }
      }
      n2blue = 1 << pmax;
    }
    n = nfft << 2;
    if (n < 1) {
      n = 1;
    }
    if (n2blue > n) {
      i_rtErrorWithMessageID(bd_emlrtRTEI.fName, bd_emlrtRTEI.lineNo);
    }
    nRows = n2blue;
  }
  return n2blue;
}

//
// Arguments    : const array<creal32_T, 2U> &x
//                int n1_unsigned
//                const array<float, 2U> &costab
//                const array<float, 2U> &sintab
//                array<creal32_T, 2U> &y
// Return Type  : void
//
void FFTImplementationCallback::r2br_r2dit_trig(const array<creal32_T, 2U> &x,
                                                int n1_unsigned,
                                                const array<float, 2U> &costab,
                                                const array<float, 2U> &sintab,
                                                array<creal32_T, 2U> &y)
{
  array<creal32_T, 1U> r;
  float temp_im;
  float temp_re;
  float temp_re_tmp;
  float twid_im;
  float twid_re;
  int b_i;
  int iDelta;
  int iheight;
  int ihi;
  int iy;
  int j;
  int ju;
  int k;
  int loop_ub;
  int nRowsD2;
  int nrows;
  int xoff;
  boolean_T tst;
  nrows = x.size(0);
  y.set_size(n1_unsigned, x.size(1));
  if (n1_unsigned > x.size(0)) {
    y.set_size(n1_unsigned, x.size(1));
    loop_ub = n1_unsigned * x.size(1);
    for (int i{0}; i < loop_ub; i++) {
      y[i].re = 0.0F;
      y[i].im = 0.0F;
    }
  }
  if (x.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  loop_ub = x.size(1) - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    r, xoff, j, iy, iDelta, ihi, nRowsD2, k, ju, b_i, tst, temp_re_tmp,        \
    temp_im, temp_re, twid_re, iheight, twid_im)

  for (int chan = 0; chan <= loop_ub; chan++) {
    xoff = chan * nrows;
    r.set_size(n1_unsigned);
    if (n1_unsigned > x.size(0)) {
      r.set_size(n1_unsigned);
      for (j = 0; j < n1_unsigned; j++) {
        r[j].re = 0.0F;
        r[j].im = 0.0F;
      }
    }
    iy = x.size(0);
    iDelta = n1_unsigned;
    if (iy <= n1_unsigned) {
      iDelta = iy;
    }
    ihi = n1_unsigned - 2;
    nRowsD2 = n1_unsigned / 2;
    k = nRowsD2 / 2;
    iy = 0;
    ju = 0;
    if (iDelta - 1 > 2147483646) {
      check_forloop_overflow_error();
    }
    for (b_i = 0; b_i <= iDelta - 2; b_i++) {
      r[iy] = x[xoff + b_i];
      j = n1_unsigned;
      tst = true;
      while (tst) {
        j >>= 1;
        ju ^= j;
        tst = ((ju & j) == 0);
      }
      iy = ju;
    }
    if (iDelta - 2 >= 0) {
      xoff = (xoff + iDelta) - 1;
    }
    r[iy] = x[xoff];
    if (n1_unsigned > 1) {
      for (b_i = 0; b_i <= ihi; b_i += 2) {
        temp_re_tmp = r[b_i + 1].re;
        temp_im = r[b_i + 1].im;
        temp_re = r[b_i].re;
        twid_re = r[b_i].im;
        r[b_i + 1].re = temp_re - temp_re_tmp;
        r[b_i + 1].im = twid_re - temp_im;
        r[b_i].re = temp_re + temp_re_tmp;
        r[b_i].im = twid_re + temp_im;
      }
    }
    iDelta = 2;
    xoff = 4;
    iheight = ((k - 1) << 2) + 1;
    while (k > 0) {
      for (b_i = 0; b_i < iheight; b_i += xoff) {
        iy = b_i + iDelta;
        temp_re = r[iy].re;
        temp_im = r[iy].im;
        r[iy].re = r[b_i].re - temp_re;
        r[iy].im = r[b_i].im - temp_im;
        r[b_i].re = r[b_i].re + temp_re;
        r[b_i].im = r[b_i].im + temp_im;
      }
      iy = 1;
      for (j = k; j < nRowsD2; j += k) {
        twid_re = costab[j];
        twid_im = sintab[j];
        b_i = iy;
        ihi = iy + iheight;
        while (b_i < ihi) {
          ju = b_i + iDelta;
          temp_re_tmp = r[ju].im;
          temp_im = r[ju].re;
          temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
          temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
          r[ju].re = r[b_i].re - temp_re;
          r[ju].im = r[b_i].im - temp_im;
          r[b_i].re = r[b_i].re + temp_re;
          r[b_i].im = r[b_i].im + temp_im;
          b_i += xoff;
        }
        iy++;
      }
      k /= 2;
      iDelta = xoff;
      xoff += xoff;
      iheight -= iDelta;
    }
    iy = r.size(0);
    for (j = 0; j < iy; j++) {
      y[j + y.size(0) * chan] = r[j];
    }
  }
}

//
// Arguments    : const array<creal_T, 2U> &x
//                int n1_unsigned
//                const array<double, 2U> &costab
//                const array<double, 2U> &sintab
//                array<creal_T, 2U> &y
// Return Type  : void
//
void FFTImplementationCallback::r2br_r2dit_trig(const array<creal_T, 2U> &x,
                                                int n1_unsigned,
                                                const array<double, 2U> &costab,
                                                const array<double, 2U> &sintab,
                                                array<creal_T, 2U> &y)
{
  array<creal_T, 1U> r;
  double temp_im;
  double temp_re;
  double temp_re_tmp;
  double twid_re;
  int i;
  int iDelta;
  int iDelta2;
  int iheight;
  int ihi;
  int iy;
  int ju;
  int k;
  int nRowsD2;
  int nRowsM2;
  y.set_size(n1_unsigned, 1);
  if (n1_unsigned > x.size(0)) {
    y.set_size(n1_unsigned, 1);
    for (ju = 0; ju < n1_unsigned; ju++) {
      y[ju].re = 0.0;
      y[ju].im = 0.0;
    }
  }
  ihi = x.size(0);
  if (ihi > n1_unsigned) {
    ihi = n1_unsigned;
  }
  nRowsM2 = n1_unsigned - 2;
  nRowsD2 = n1_unsigned / 2;
  k = nRowsD2 / 2;
  r.set_size(n1_unsigned);
  if (n1_unsigned > x.size(0)) {
    r.set_size(n1_unsigned);
    for (ju = 0; ju < n1_unsigned; ju++) {
      r[ju].re = 0.0;
      r[ju].im = 0.0;
    }
  }
  iy = 0;
  ju = 0;
  if (ihi - 1 > 2147483646) {
    check_forloop_overflow_error();
  }
  for (i = 0; i <= ihi - 2; i++) {
    boolean_T tst;
    r[iy] = x[i];
    iy = n1_unsigned;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }
    iy = ju;
  }
  if (ihi - 2 < 0) {
    ihi = 0;
  } else {
    ihi--;
  }
  r[iy] = x[ihi];
  if (n1_unsigned > 1) {
    for (i = 0; i <= nRowsM2; i += 2) {
      temp_re_tmp = r[i + 1].re;
      temp_im = r[i + 1].im;
      temp_re = r[i].re;
      twid_re = r[i].im;
      r[i + 1].re = temp_re - temp_re_tmp;
      r[i + 1].im = twid_re - temp_im;
      r[i].re = temp_re + temp_re_tmp;
      r[i].im = twid_re + temp_im;
    }
  }
  iDelta = 2;
  iDelta2 = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < iheight; i += iDelta2) {
      iy = i + iDelta;
      temp_re = r[iy].re;
      temp_im = r[iy].im;
      r[iy].re = r[i].re - temp_re;
      r[iy].im = r[i].im - temp_im;
      r[i].re = r[i].re + temp_re;
      r[i].im = r[i].im + temp_im;
    }
    iy = 1;
    for (ju = k; ju < nRowsD2; ju += k) {
      double twid_im;
      twid_re = costab[ju];
      twid_im = sintab[ju];
      i = iy;
      ihi = iy + iheight;
      while (i < ihi) {
        nRowsM2 = i + iDelta;
        temp_re_tmp = r[nRowsM2].im;
        temp_im = r[nRowsM2].re;
        temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
        r[nRowsM2].re = r[i].re - temp_re;
        r[nRowsM2].im = r[i].im - temp_im;
        r[i].re = r[i].re + temp_re;
        r[i].im = r[i].im + temp_im;
        i += iDelta2;
      }
      iy++;
    }
    k /= 2;
    iDelta = iDelta2;
    iDelta2 += iDelta2;
    iheight -= iDelta;
  }
  iy = r.size(0);
  for (ju = 0; ju < iy; ju++) {
    y[ju] = r[ju];
  }
}

//
// Arguments    : const array<creal_T, 3U> &x
//                int n1_unsigned
//                const array<double, 2U> &costab
//                const array<double, 2U> &sintab
//                array<creal_T, 3U> &y
// Return Type  : void
//
void FFTImplementationCallback::r2br_r2dit_trig(const array<creal_T, 3U> &x,
                                                int n1_unsigned,
                                                const array<double, 2U> &costab,
                                                const array<double, 2U> &sintab,
                                                array<creal_T, 3U> &y)
{
  array<creal_T, 1U> r;
  double temp_im;
  double temp_re;
  double temp_re_tmp;
  double twid_im;
  double twid_re;
  int b_i;
  int iDelta;
  int iheight;
  int ihi;
  int iy;
  int j;
  int ju;
  int k;
  int nChan;
  int nRowsD2;
  int nrows;
  int xoff;
  boolean_T tst;
  nChan = x.size(1) * x.size(2);
  nrows = x.size(0);
  y.set_size(n1_unsigned, x.size(1), x.size(2));
  if (n1_unsigned > x.size(0)) {
    int loop_ub;
    y.set_size(n1_unsigned, x.size(1), x.size(2));
    loop_ub = n1_unsigned * x.size(1) * x.size(2);
    for (int i{0}; i < loop_ub; i++) {
      y[i].re = 0.0;
      y[i].im = 0.0;
    }
  }
  if (nChan > 2147483646) {
    check_forloop_overflow_error();
  }
  nChan--;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    r, xoff, ihi, iy, iDelta, nRowsD2, k, ju, b_i, j, tst, temp_re_tmp,        \
    temp_im, temp_re, twid_re, iheight, twid_im)

  for (int chan = 0; chan <= nChan; chan++) {
    xoff = chan * nrows;
    r.set_size(n1_unsigned);
    if (n1_unsigned > x.size(0)) {
      r.set_size(n1_unsigned);
      for (ihi = 0; ihi < n1_unsigned; ihi++) {
        r[ihi].re = 0.0;
        r[ihi].im = 0.0;
      }
    }
    iy = x.size(0);
    iDelta = n1_unsigned;
    if (iy <= n1_unsigned) {
      iDelta = iy;
    }
    ihi = n1_unsigned - 2;
    nRowsD2 = n1_unsigned / 2;
    k = nRowsD2 / 2;
    iy = 0;
    ju = 0;
    if (iDelta - 1 > 2147483646) {
      check_forloop_overflow_error();
    }
    for (b_i = 0; b_i <= iDelta - 2; b_i++) {
      r[iy] = x[xoff + b_i];
      j = n1_unsigned;
      tst = true;
      while (tst) {
        j >>= 1;
        ju ^= j;
        tst = ((ju & j) == 0);
      }
      iy = ju;
    }
    if (iDelta - 2 >= 0) {
      xoff = (xoff + iDelta) - 1;
    }
    r[iy] = x[xoff];
    if (n1_unsigned > 1) {
      for (b_i = 0; b_i <= ihi; b_i += 2) {
        temp_re_tmp = r[b_i + 1].re;
        temp_im = r[b_i + 1].im;
        temp_re = r[b_i].re;
        twid_re = r[b_i].im;
        r[b_i + 1].re = temp_re - temp_re_tmp;
        r[b_i + 1].im = twid_re - temp_im;
        r[b_i].re = temp_re + temp_re_tmp;
        r[b_i].im = twid_re + temp_im;
      }
    }
    iDelta = 2;
    xoff = 4;
    iheight = ((k - 1) << 2) + 1;
    while (k > 0) {
      for (b_i = 0; b_i < iheight; b_i += xoff) {
        iy = b_i + iDelta;
        temp_re = r[iy].re;
        temp_im = r[iy].im;
        r[iy].re = r[b_i].re - temp_re;
        r[iy].im = r[b_i].im - temp_im;
        r[b_i].re = r[b_i].re + temp_re;
        r[b_i].im = r[b_i].im + temp_im;
      }
      iy = 1;
      for (j = k; j < nRowsD2; j += k) {
        twid_re = costab[j];
        twid_im = sintab[j];
        b_i = iy;
        ihi = iy + iheight;
        while (b_i < ihi) {
          ju = b_i + iDelta;
          temp_re_tmp = r[ju].im;
          temp_im = r[ju].re;
          temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
          temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
          r[ju].re = r[b_i].re - temp_re;
          r[ju].im = r[b_i].im - temp_im;
          r[b_i].re = r[b_i].re + temp_re;
          r[b_i].im = r[b_i].im + temp_im;
          b_i += xoff;
        }
        iy++;
      }
      k /= 2;
      iDelta = xoff;
      xoff += xoff;
      iheight -= iDelta;
    }
    iy = y.size(0);
    j = r.size(0);
    for (ihi = 0; ihi < j; ihi++) {
      y[ihi + iy * chan] = r[ihi];
    }
  }
}

} // namespace fft
} // namespace internal
} // namespace coder

//
// File trailer for FFTImplementationCallback.cpp
//
// [EOF]
//
