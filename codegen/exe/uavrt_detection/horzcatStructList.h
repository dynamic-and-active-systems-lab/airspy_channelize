//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: horzcatStructList.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

#ifndef HORZCATSTRUCTLIST_H
#define HORZCATSTRUCTLIST_H

// Include Files
#include "rtwtypes.h"
#include "uavrt_detection_internal_types.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void b_horzcatStructList(const array<c_struct_T, 1U> &structure,
                         array<double, 2U> &result);

void b_horzcatStructList(const array<c_struct_T, 2U> &structure,
                         array<double, 2U> &result);

void c_horzcatStructList(const array<c_struct_T, 1U> &structure,
                         array<double, 2U> &result);

void c_horzcatStructList(const array<c_struct_T, 2U> &structure,
                         array<double, 2U> &result);

void d_horzcatStructList(const array<c_struct_T, 2U> &structure,
                         array<boolean_T, 2U> &result);

void horzcatStructList(const array<c_struct_T, 2U> &structure,
                       array<boolean_T, 2U> &result);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for horzcatStructList.h
//
// [EOF]
//