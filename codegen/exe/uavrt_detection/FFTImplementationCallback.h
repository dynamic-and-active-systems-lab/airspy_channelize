//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FFTImplementationCallback.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

#ifndef FFTIMPLEMENTATIONCALLBACK_H
#define FFTIMPLEMENTATIONCALLBACK_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace internal {
namespace fft {
class FFTImplementationCallback {
public:
  static int get_algo_sizes(int nfft, boolean_T useRadix2, int &nRows);
  static void r2br_r2dit_trig(const array<creal32_T, 2U> &x, int n1_unsigned,
                              const array<float, 2U> &costab,
                              const array<float, 2U> &sintab,
                              array<creal32_T, 2U> &y);
  static void dobluesteinfft(const array<creal32_T, 2U> &x, int n2blue,
                             int nfft, const array<float, 2U> &costab,
                             const array<float, 2U> &sintab,
                             const array<float, 2U> &sintabinv,
                             array<creal32_T, 2U> &y);
  static void generate_twiddle_tables(int nRows, boolean_T useRadix2,
                                      array<double, 2U> &costab,
                                      array<double, 2U> &sintab,
                                      array<double, 2U> &sintabinv);
  static void r2br_r2dit_trig(const array<creal_T, 2U> &x, int n1_unsigned,
                              const array<double, 2U> &costab,
                              const array<double, 2U> &sintab,
                              array<creal_T, 2U> &y);
  static void dobluesteinfft(const array<creal_T, 2U> &x, int n2blue, int nfft,
                             const array<double, 2U> &costab,
                             const array<double, 2U> &sintab,
                             const array<double, 2U> &sintabinv,
                             array<creal_T, 2U> &y);
  static void r2br_r2dit_trig(const array<creal_T, 3U> &x, int n1_unsigned,
                              const array<double, 2U> &costab,
                              const array<double, 2U> &sintab,
                              array<creal_T, 3U> &y);
  static void dobluesteinfft(const array<creal_T, 3U> &x, int n2blue, int nfft,
                             const array<double, 2U> &costab,
                             const array<double, 2U> &sintab,
                             const array<double, 2U> &sintabinv,
                             array<creal_T, 3U> &y);

protected:
  static void r2br_r2dit_trig_impl(const array<creal32_T, 1U> &x,
                                   int unsigned_nRows,
                                   const array<float, 2U> &costab,
                                   const array<float, 2U> &sintab,
                                   array<creal32_T, 1U> &y);
  static void r2br_r2dit_trig_impl(const array<creal_T, 1U> &x,
                                   int unsigned_nRows,
                                   const array<double, 2U> &costab,
                                   const array<double, 2U> &sintab,
                                   array<creal_T, 1U> &y);
};

} // namespace fft
} // namespace internal
} // namespace coder

#endif
//
// File trailer for FFTImplementationCallback.h
//
// [EOF]
//
