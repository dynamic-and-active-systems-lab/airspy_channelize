//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: FFTImplementationCallback.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 28-Mar-2023 15:24:09
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
