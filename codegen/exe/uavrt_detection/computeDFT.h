//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeDFT.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

#ifndef COMPUTEDFT_H
#define COMPUTEDFT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void computeDFT(const array<creal32_T, 2U> &xin, double nfft, double varargin_1,
                array<creal32_T, 2U> &Xx, array<double, 1U> &f);

}

#endif
//
// File trailer for computeDFT.h
//
// [EOF]
//
