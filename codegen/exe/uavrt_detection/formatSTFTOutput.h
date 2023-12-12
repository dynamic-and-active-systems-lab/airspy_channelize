//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: formatSTFTOutput.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

#ifndef FORMATSTFTOUTPUT_H
#define FORMATSTFTOUTPUT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace b_signal {
namespace internal {
namespace stft {
void formatSTFTOutput(array<creal32_T, 2U> &S, const array<double, 1U> &F,
                      array<double, 1U> &Fout);

void formatSTFTOutput(array<creal_T, 3U> &S, const array<double, 1U> &F,
                      array<double, 1U> &Fout);

} // namespace stft
} // namespace internal
} // namespace b_signal
} // namespace coder

#endif
//
// File trailer for formatSTFTOutput.h
//
// [EOF]
//
