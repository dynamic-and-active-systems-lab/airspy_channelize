//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sum.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

#ifndef SUM_H
#define SUM_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class sparse;

class b_sparse;

class g_sparse;

class c_sparse;

} // namespace coder

// Function Declarations
namespace coder {
void sum(const sparse &x, b_sparse &y);

void sum(const g_sparse &x, c_sparse &y);

void sum(const array<double, 2U> &x, array<double, 1U> &y);

} // namespace coder

#endif
//
// File trailer for sum.h
//
// [EOF]
//
