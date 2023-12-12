//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: function_handle.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "function_handle.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "threshold.h"
#include "waveform.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const coder::array<boolean_T, 1U> &in1
//                const coder::array<boolean_T, 1U> &in2
// Return Type  : boolean_T
//
boolean_T binary_expand_op_19(const coder::array<boolean_T, 1U> &in1,
                              const coder::array<boolean_T, 1U> &in2)
{
  coder::array<boolean_T, 1U> b_in1;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  boolean_T exitg1;
  boolean_T out1;
  if (in2.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2.size(0);
  }
  b_in1.set_size(loop_ub);
  stride_0_0 = (in1.size(0) != 1);
  stride_1_0 = (in2.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    b_in1[i] = (in1[i * stride_0_0] && in2[i * stride_1_0]);
  }
  out1 = false;
  if (b_in1.size(0) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  loop_ub = 1;
  exitg1 = false;
  while ((!exitg1) && (loop_ub <= b_in1.size(0))) {
    if (b_in1[loop_ub - 1]) {
      out1 = true;
      exitg1 = true;
    } else {
      loop_ub++;
    }
  }
  return out1;
}

//
// Arguments    : const coder::array<double, 1U> &in1
//                const waveform *in2
// Return Type  : boolean_T
//
boolean_T binary_expand_op_8(const coder::array<double, 1U> &in1,
                             const waveform *in2)
{
  coder::array<boolean_T, 1U> b_in1;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  boolean_T exitg1;
  boolean_T out1;
  if (in2->thresh.threshVecFine.size(0) == 1) {
    i = in1.size(0);
  } else {
    i = in2->thresh.threshVecFine.size(0);
  }
  b_in1.set_size(i);
  stride_0_0 = (in1.size(0) != 1);
  stride_1_0 = (in2->thresh.threshVecFine.size(0) != 1);
  if (in2->thresh.threshVecFine.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2->thresh.threshVecFine.size(0);
  }
  for (i = 0; i < loop_ub; i++) {
    b_in1[i] =
        (in1[i * stride_0_0] >= in2->thresh.threshVecFine[i * stride_1_0]);
  }
  out1 = false;
  if (b_in1.size(0) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  stride_0_0 = 1;
  exitg1 = false;
  while ((!exitg1) && (stride_0_0 <= b_in1.size(0))) {
    if (b_in1[stride_0_0 - 1]) {
      out1 = true;
      exitg1 = true;
    } else {
      stride_0_0++;
    }
  }
  return out1;
}

//
// File trailer for function_handle.cpp
//
// [EOF]
//
