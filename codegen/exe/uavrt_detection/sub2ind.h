//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sub2ind.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

#ifndef SUB2IND_H
#define SUB2IND_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void b_sub2ind(const int siz[2], const array<double, 2U> &varargin_1,
               const array<double, 2U> &varargin_2, array<int, 2U> &idx);

void sub2ind(const int siz[2], const array<double, 2U> &varargin_1,
             const array<double, 2U> &varargin_2, array<int, 2U> &idx);

void sub2ind(const int siz[2], const array<double, 1U> &varargin_1,
             const array<double, 1U> &varargin_2, array<int, 1U> &idx);

int sub2ind(const int siz[2], double varargin_2);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for sub2ind.h
//
// [EOF]
//
