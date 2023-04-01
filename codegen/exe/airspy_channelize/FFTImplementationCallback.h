//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FFTImplementationCallback.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Apr-2023 16:55:28
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
  static void dobluesteinfft(const ::coder::array<creal32_T, 2U> &x,
                             ::coder::array<creal32_T, 2U> &y);
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
