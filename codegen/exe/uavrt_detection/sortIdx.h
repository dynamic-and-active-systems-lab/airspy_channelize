//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sortIdx.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

#ifndef SORTIDX_H
#define SORTIDX_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void merge_block(array<int, 2U> &idx, array<double, 2U> &x, int offset, int n,
                 int preSortLevel, array<int, 1U> &iwork,
                 array<double, 1U> &xwork);

void merge_block(array<int, 1U> &idx, array<double, 1U> &x, int offset, int n,
                 int preSortLevel, array<int, 1U> &iwork,
                 array<double, 1U> &xwork);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for sortIdx.h
//
// [EOF]
//
