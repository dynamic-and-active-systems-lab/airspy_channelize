//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: repmat.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

#ifndef REPMAT_H
#define REPMAT_H

// Include Files
#include "rtwtypes.h"
#include "uavrt_detection_internal_types.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void b_repmat(const array<double, 2U> &a, double varargin_1,
              array<double, 2U> &b);

void repmat(const array<double, 2U> &a, double varargin_1,
            array<double, 2U> &b);

void repmat(const c_struct_T &a, double varargin_1, double varargin_2,
            array<c_struct_T, 2U> &b);

void repmat(const array<double, 1U> &a, double varargin_2,
            array<double, 2U> &b);

} // namespace coder

#endif
//
// File trailer for repmat.h
//
// [EOF]
//
