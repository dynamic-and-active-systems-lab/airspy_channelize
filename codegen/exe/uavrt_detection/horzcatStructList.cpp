//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: horzcatStructList.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "horzcatStructList.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_internal_types.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const array<c_struct_T, 1U> &structure
//                array<double, 2U> &result
// Return Type  : void
//
namespace coder {
namespace internal {
void b_horzcatStructList(const array<c_struct_T, 1U> &structure,
                         array<double, 2U> &result)
{
  int n;
  int resultSize_idx_1;
  n = structure.size(0);
  if (structure.size(0) == 0) {
    resultSize_idx_1 = 0;
  } else {
    resultSize_idx_1 = structure.size(0);
    if (structure.size(0) > 2147483646) {
      check_forloop_overflow_error();
    }
  }
  result.set_size(1, resultSize_idx_1);
  for (resultSize_idx_1 = 0; resultSize_idx_1 < n; resultSize_idx_1++) {
    result[resultSize_idx_1] = structure[resultSize_idx_1].t_0;
  }
}

//
// Arguments    : const array<c_struct_T, 2U> &structure
//                array<double, 2U> &result
// Return Type  : void
//
void b_horzcatStructList(const array<c_struct_T, 2U> &structure,
                         array<double, 2U> &result)
{
  int n;
  int resultSize_idx_1;
  n = structure.size(1);
  if (structure.size(1) == 0) {
    resultSize_idx_1 = 0;
  } else {
    resultSize_idx_1 = structure.size(1);
    if (structure.size(1) > 2147483646) {
      check_forloop_overflow_error();
    }
  }
  result.set_size(1, resultSize_idx_1);
  for (resultSize_idx_1 = 0; resultSize_idx_1 < n; resultSize_idx_1++) {
    result[resultSize_idx_1] = structure[resultSize_idx_1].t_0;
  }
}

//
// Arguments    : const array<c_struct_T, 1U> &structure
//                array<double, 2U> &result
// Return Type  : void
//
void c_horzcatStructList(const array<c_struct_T, 1U> &structure,
                         array<double, 2U> &result)
{
  int n;
  int resultSize_idx_1;
  n = structure.size(0);
  if (structure.size(0) == 0) {
    resultSize_idx_1 = 0;
  } else {
    resultSize_idx_1 = structure.size(0);
    if (structure.size(0) > 2147483646) {
      check_forloop_overflow_error();
    }
  }
  result.set_size(1, resultSize_idx_1);
  for (resultSize_idx_1 = 0; resultSize_idx_1 < n; resultSize_idx_1++) {
    result[resultSize_idx_1] = structure[resultSize_idx_1].SNR;
  }
}

//
// Arguments    : const array<c_struct_T, 2U> &structure
//                array<double, 2U> &result
// Return Type  : void
//
void c_horzcatStructList(const array<c_struct_T, 2U> &structure,
                         array<double, 2U> &result)
{
  int n;
  int resultSize_idx_1;
  n = structure.size(1);
  if (structure.size(1) == 0) {
    resultSize_idx_1 = 0;
  } else {
    resultSize_idx_1 = structure.size(1);
    if (structure.size(1) > 2147483646) {
      check_forloop_overflow_error();
    }
  }
  result.set_size(1, resultSize_idx_1);
  for (resultSize_idx_1 = 0; resultSize_idx_1 < n; resultSize_idx_1++) {
    result[resultSize_idx_1] = structure[resultSize_idx_1].fp;
  }
}

//
// Arguments    : const array<c_struct_T, 2U> &structure
//                array<boolean_T, 2U> &result
// Return Type  : void
//
void d_horzcatStructList(const array<c_struct_T, 2U> &structure,
                         array<boolean_T, 2U> &result)
{
  int n;
  int resultSize_idx_1;
  n = structure.size(1);
  if (structure.size(1) == 0) {
    resultSize_idx_1 = 0;
  } else {
    resultSize_idx_1 = structure.size(1);
    if (structure.size(1) > 2147483646) {
      check_forloop_overflow_error();
    }
  }
  result.set_size(1, resultSize_idx_1);
  for (resultSize_idx_1 = 0; resultSize_idx_1 < n; resultSize_idx_1++) {
    result[resultSize_idx_1] = structure[resultSize_idx_1].con_dec;
  }
}

//
// Arguments    : const array<c_struct_T, 2U> &structure
//                array<boolean_T, 2U> &result
// Return Type  : void
//
void horzcatStructList(const array<c_struct_T, 2U> &structure,
                       array<boolean_T, 2U> &result)
{
  int n_tmp;
  int resultSize_idx_1;
  n_tmp = structure.size(0) * structure.size(1);
  if (n_tmp == 0) {
    resultSize_idx_1 = 0;
  } else {
    resultSize_idx_1 = n_tmp;
    if (n_tmp > 2147483646) {
      check_forloop_overflow_error();
    }
  }
  result.set_size(1, resultSize_idx_1);
  for (resultSize_idx_1 = 0; resultSize_idx_1 < n_tmp; resultSize_idx_1++) {
    result[resultSize_idx_1] = structure[resultSize_idx_1].det_dec;
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for horzcatStructList.cpp
//
// [EOF]
//
