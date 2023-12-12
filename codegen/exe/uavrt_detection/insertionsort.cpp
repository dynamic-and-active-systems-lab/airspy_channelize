//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: insertionsort.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "insertionsort.h"
#include "anonymous_function.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_internal_types.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : array<int, 1U> &x
//                int xstart
//                int xend
//                const anonymous_function &cmp
// Return Type  : void
//
namespace coder {
namespace internal {
void insertionsort(array<int, 1U> &x, int xstart, int xend,
                   const anonymous_function &cmp)
{
  int a;
  a = xstart + 1;
  if ((xstart + 1 <= xend) && (xend > 2147483646)) {
    check_forloop_overflow_error();
  }
  for (int k{a}; k <= xend; k++) {
    int idx;
    int xc;
    boolean_T exitg1;
    xc = x[k - 1] - 1;
    idx = k - 2;
    exitg1 = false;
    while ((!exitg1) && (idx + 1 >= xstart)) {
      int i;
      boolean_T varargout_1;
      i = cmp.workspace.a[x[idx] - 1];
      if (cmp.workspace.a[xc] < i) {
        varargout_1 = true;
      } else if (cmp.workspace.a[xc] == i) {
        varargout_1 = (cmp.workspace.b[xc] < cmp.workspace.b[x[idx] - 1]);
      } else {
        varargout_1 = false;
      }
      if (varargout_1) {
        x[idx + 1] = x[idx];
        idx--;
      } else {
        exitg1 = true;
      }
    }
    x[idx + 1] = xc + 1;
  }
}

//
// Arguments    : array<int, 1U> &x
//                int xend
//                const anonymous_function &cmp
// Return Type  : void
//
void insertionsort(array<int, 1U> &x, int xend, const anonymous_function &cmp)
{
  if (xend > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{2}; k <= xend; k++) {
    int idx;
    int xc;
    boolean_T exitg1;
    xc = x[k - 1] - 1;
    idx = k - 2;
    exitg1 = false;
    while ((!exitg1) && (idx + 1 >= 1)) {
      int i;
      boolean_T varargout_1;
      i = cmp.workspace.a[x[idx] - 1];
      if (cmp.workspace.a[xc] < i) {
        varargout_1 = true;
      } else if (cmp.workspace.a[xc] == i) {
        varargout_1 = (cmp.workspace.b[xc] < cmp.workspace.b[x[idx] - 1]);
      } else {
        varargout_1 = false;
      }
      if (varargout_1) {
        x[idx + 1] = x[idx];
        idx--;
      } else {
        exitg1 = true;
      }
    }
    x[idx + 1] = xc + 1;
  }
}

//
// Arguments    : array<int, 1U> &x
//                int xstart
//                int xend
//                const c_anonymous_function &cmp
// Return Type  : void
//
void insertionsort(array<int, 1U> &x, int xstart, int xend,
                   const c_anonymous_function &cmp)
{
  int a;
  a = xstart + 1;
  if ((xstart + 1 <= xend) && (xend > 2147483646)) {
    check_forloop_overflow_error();
  }
  for (int k{a}; k <= xend; k++) {
    int idx;
    int xc;
    boolean_T exitg1;
    xc = x[k - 1];
    idx = k - 1;
    exitg1 = false;
    while ((!exitg1) && (idx >= xstart)) {
      int i;
      i = x[idx - 1];
      if (cmp.workspace.x[xc - 1] < cmp.workspace.x[i - 1]) {
        x[idx] = i;
        idx--;
      } else {
        exitg1 = true;
      }
    }
    x[idx] = xc;
  }
}

//
// Arguments    : array<int, 1U> &x
//                int xend
//                const c_anonymous_function &cmp
// Return Type  : void
//
void insertionsort(array<int, 1U> &x, int xend, const c_anonymous_function &cmp)
{
  if (xend > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{2}; k <= xend; k++) {
    int idx;
    int xc;
    boolean_T exitg1;
    xc = x[k - 1];
    idx = k - 1;
    exitg1 = false;
    while ((!exitg1) && (idx >= 1)) {
      int i;
      i = x[idx - 1];
      if (cmp.workspace.x[xc - 1] < cmp.workspace.x[i - 1]) {
        x[idx] = i;
        idx--;
      } else {
        exitg1 = true;
      }
    }
    x[idx] = xc;
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for insertionsort.cpp
//
// [EOF]
//
