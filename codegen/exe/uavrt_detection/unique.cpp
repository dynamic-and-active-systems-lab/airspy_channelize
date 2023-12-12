//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: unique.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "unique.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "sortLE.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const array<double, 2U> &a
//                array<double, 2U> &b
// Return Type  : void
//
namespace coder {
void unique_rows(const array<double, 2U> &a, array<double, 2U> &b)
{
  static rtRunTimeErrorInfo bd_emlrtRTEI{
      331,           // lineNo
      1,             // colNo
      "unique_rows", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/ops/unique.m" // pName
  };
  array<double, 1U> ycol;
  array<int, 2U> col;
  array<int, 1U> idx;
  array<int, 1U> iwork;
  int qEnd;
  if (a.size(0) == 0) {
    b.set_size(0, a.size(1));
  } else {
    int b_i;
    int i;
    int i1;
    int i2;
    int j;
    int k;
    int n;
    int p;
    int pEnd;
    int q;
    b.set_size(a.size(0), a.size(1));
    i2 = a.size(0) * a.size(1);
    for (i = 0; i < i2; i++) {
      b[i] = a[i];
    }
    n = a.size(1);
    col.set_size(1, a.size(1));
    if (a.size(1) > 2147483646) {
      check_forloop_overflow_error();
    }
    for (k = 0; k < n; k++) {
      col[k] = k + 1;
    }
    n = a.size(0) + 1;
    idx.set_size(a.size(0));
    i2 = a.size(0);
    for (i = 0; i < i2; i++) {
      idx[i] = 0;
    }
    if (a.size(1) == 0) {
      if (a.size(0) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (k = 0; k <= n - 2; k++) {
        idx[k] = k + 1;
      }
    } else {
      iwork.set_size(a.size(0));
      q = a.size(0) - 1;
      if (a.size(0) - 1 > 2147483645) {
        check_forloop_overflow_error();
      }
      for (k = 1; k <= q; k += 2) {
        if (internal::sortLE(a, col, k, k + 1)) {
          idx[k - 1] = k;
          idx[k] = k + 1;
        } else {
          idx[k - 1] = k + 1;
          idx[k] = k;
        }
      }
      if ((a.size(0) & 1) != 0) {
        idx[a.size(0) - 1] = a.size(0);
      }
      b_i = 2;
      while (b_i < n - 1) {
        i2 = b_i << 1;
        j = 1;
        for (pEnd = b_i + 1; pEnd < n; pEnd = qEnd + b_i) {
          int kEnd;
          p = j;
          q = pEnd;
          qEnd = j + i2;
          if (qEnd > n) {
            qEnd = n;
          }
          k = 0;
          kEnd = qEnd - j;
          while (k + 1 <= kEnd) {
            i = idx[p - 1];
            i1 = idx[q - 1];
            if (internal::sortLE(a, col, i, i1)) {
              iwork[k] = i;
              p++;
              if (p == pEnd) {
                while (q < qEnd) {
                  k++;
                  iwork[k] = idx[q - 1];
                  q++;
                }
              }
            } else {
              iwork[k] = i1;
              q++;
              if (q == qEnd) {
                while (p < pEnd) {
                  k++;
                  iwork[k] = idx[p - 1];
                  p++;
                }
              }
            }
            k++;
          }
          for (k = 0; k < kEnd; k++) {
            idx[(j + k) - 1] = iwork[k];
          }
          j = qEnd;
        }
        b_i = i2;
      }
    }
    i2 = a.size(0);
    n = a.size(1);
    ycol.set_size(a.size(0));
    for (j = 0; j < n; j++) {
      if (i2 > 2147483646) {
        check_forloop_overflow_error();
      }
      for (b_i = 0; b_i < i2; b_i++) {
        ycol[b_i] = b[(idx[b_i] + b.size(0) * j) - 1];
      }
      for (b_i = 0; b_i < i2; b_i++) {
        b[b_i + b.size(0) * j] = ycol[b_i];
      }
    }
    p = 0;
    i2 = a.size(0);
    k = 0;
    while (k + 1 <= i2) {
      pEnd = k;
      int exitg1;
      do {
        exitg1 = 0;
        k++;
        if (k + 1 > i2) {
          exitg1 = 1;
        } else {
          boolean_T b_p;
          boolean_T exitg2;
          b_p = false;
          j = 0;
          exitg2 = false;
          while ((!exitg2) && (j <= b.size(1) - 1)) {
            if (b[pEnd + b.size(0) * j] != b[k + b.size(0) * j]) {
              b_p = true;
              exitg2 = true;
            } else {
              j++;
            }
          }
          if (b_p) {
            exitg1 = 1;
          }
        }
      } while (exitg1 == 0);
      p++;
      q = b.size(1);
      if (b.size(1) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (j = 0; j < q; j++) {
        b[(p + b.size(0) * j) - 1] = b[pEnd + b.size(0) * j];
      }
      if ((pEnd + 1 <= k) && (k > 2147483646)) {
        check_forloop_overflow_error();
      }
    }
    if (p > a.size(0)) {
      i_rtErrorWithMessageID(bd_emlrtRTEI.fName, bd_emlrtRTEI.lineNo);
    }
    if (p < 1) {
      i2 = 0;
    } else {
      i2 = p;
    }
    q = b.size(1);
    for (i = 0; i < q; i++) {
      for (i1 = 0; i1 < i2; i1++) {
        b[i1 + i2 * i] = b[i1 + b.size(0) * i];
      }
    }
    b.set_size(i2, b.size(1));
    if (p > 2147483646) {
      check_forloop_overflow_error();
    }
  }
}

} // namespace coder

//
// File trailer for unique.cpp
//
// [EOF]
//
