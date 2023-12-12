//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: stft.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

#ifndef STFT_H
#define STFT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void stft(const array<creal32_T, 2U> &x, double varargin_1,
          const array<double, 1U> &varargin_3, double varargin_5,
          double varargin_7, array<creal32_T, 2U> &varargout_1,
          array<float, 1U> &varargout_2, array<float, 1U> &varargout_3);

void stft(const array<creal_T, 2U> &x, double varargin_1,
          const array<double, 1U> &varargin_3, double varargin_5,
          double varargin_7, array<creal_T, 3U> &varargout_1,
          array<double, 1U> &varargout_2, array<double, 1U> &varargout_3);

} // namespace coder

#endif
//
// File trailer for stft.h
//
// [EOF]
//
