//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sparse.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

#ifndef SPARSE_H
#define SPARSE_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class sparse;

class d_sparse;

class g_sparse;

} // namespace coder

// Function Declarations
namespace coder {
void i_sparse(const array<double, 1U> &varargin_1,
              const array<double, 1U> &varargin_2,
              const array<double, 1U> &varargin_3, sparse &y);

void i_sparse(const array<double, 1U> &varargin_1, g_sparse &y);

void j_sparse(const array<boolean_T, 2U> &varargin_1, d_sparse &y);

} // namespace coder

#endif
//
// File trailer for sparse.h
//
// [EOF]
//
