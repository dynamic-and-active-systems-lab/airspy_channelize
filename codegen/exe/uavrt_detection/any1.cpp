//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: any1.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "any1.h"
#include "anonymous_function.h"
#include "eml_int_forloop_overflow_check.h"
#include "introsort.h"
#include "rt_nonfinite.h"
#include "sparse1.h"
#include "uavrt_detection_internal_types.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const d_sparse &x
//                e_sparse &y
// Return Type  : void
//
namespace coder {
void any(const d_sparse &x, e_sparse &y)
{
  c_anonymous_function b_this;
  array<int, 2U> b_y;
  array<int, 1U> xrowidx;
  array<int, 1U> xrowidxPerm;
  if (x.n == 0) {
    y.colidx.set_size(2);
    y.colidx[0] = 1;
    y.colidx[1] = 1;
    y.d.set_size(1);
    y.d[0] = false;
    y.rowidx.set_size(1);
    y.rowidx[0] = 1;
  } else if (x.n != 0) {
    int n;
    int xnnz_tmp;
    int yk;
    xnnz_tmp = x.colidx[x.colidx.size(0) - 1];
    n = 0;
    if (xnnz_tmp - 1 > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int k{0}; k <= xnnz_tmp - 2; k++) {
      if (n == 0) {
        n = 1;
      }
    }
    yk = 0;
    if (n > 0) {
      yk = 1;
    } else {
      n = 1;
    }
    y.d.set_size(1);
    y.d[0] = true;
    y.rowidx.set_size(1);
    y.rowidx[0] = n;
    y.colidx.set_size(2);
    y.colidx[0] = 1;
    y.colidx[1] = yk + 1;
  } else {
    int k;
    int loop_ub;
    int n;
    int xnnz_tmp;
    int yk;
    xnnz_tmp = x.colidx[x.colidx.size(0) - 1] - 1;
    if (xnnz_tmp < 1) {
      loop_ub = 0;
    } else {
      loop_ub = xnnz_tmp;
    }
    if (loop_ub < 1) {
      n = 0;
    } else {
      n = loop_ub;
    }
    b_y.set_size(1, n);
    if (n > 0) {
      b_y[0] = 1;
      yk = 1;
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (k = 2; k <= n; k++) {
        yk++;
        b_y[k - 1] = yk;
      }
    }
    b_this.workspace.x.set_size(loop_ub);
    for (yk = 0; yk < loop_ub; yk++) {
      b_this.workspace.x[yk] = x.rowidx[yk];
    }
    xrowidxPerm.set_size(b_y.size(1));
    n = b_y.size(1);
    for (yk = 0; yk < n; yk++) {
      xrowidxPerm[yk] = b_y[yk];
    }
    internal::introsort(xrowidxPerm, loop_ub, b_this);
    xrowidx.set_size(xrowidxPerm.size(0));
    loop_ub = xrowidxPerm.size(0);
    for (yk = 0; yk < loop_ub; yk++) {
      xrowidx[yk] = x.rowidx[xrowidxPerm[yk] - 1];
    }
    yk = 0;
    k = 0;
    while (k + 1 <= xnnz_tmp) {
      n = xrowidx[k];
      yk++;
      xrowidx[yk - 1] = xrowidx[k];
      while ((k + 1 <= xnnz_tmp) && (xrowidx[k] == n)) {
        k++;
      }
    }
    n = yk;
    if (yk < 1) {
      n = 1;
    }
    y.rowidx.set_size(n);
    y.colidx.set_size(2);
    y.colidx[0] = 1;
    y.colidx[1] = yk + 1;
    if (yk > 2147483646) {
      check_forloop_overflow_error();
    }
    for (k = 0; k < yk; k++) {
      y.rowidx[k] = xrowidx[k];
    }
    y.d.set_size(n);
    for (yk = 0; yk < n; yk++) {
      y.d[yk] = true;
    }
  }
}

} // namespace coder

//
// File trailer for any1.cpp
//
// [EOF]
//
