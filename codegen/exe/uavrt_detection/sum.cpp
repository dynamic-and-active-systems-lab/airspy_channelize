//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sum.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "sum.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "sparse1.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const sparse &x
//                b_sparse &y
// Return Type  : void
//
namespace coder {
void sum(const sparse &x, b_sparse &y)
{
  static rtDoubleCheckInfo
      s_emlrtDCI{
          20,    // lineNo
          1,     // colNo
          "sum", // fName
          "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/datafun/"
          "sum.m", // pName
          4        // checkKind
      };
  if ((x.m == 0) || (x.n == 0) || (x.m == 0)) {
    int outidx;
    y.n = x.n;
    if (x.n + 1 < 0) {
      rtNonNegativeError(static_cast<double>(x.n + 1), s_emlrtDCI);
    }
    outidx = x.n + 1;
    y.colidx.set_size(x.n + 1);
    for (int u1{0}; u1 < outidx; u1++) {
      y.colidx[u1] = 1;
    }
    y.d.set_size(1);
    y.d[0] = 0.0;
    y.rowidx.set_size(1);
    y.rowidx[0] = 1;
  } else {
    int outidx;
    int u1;
    outidx = x.n;
    u1 = x.colidx[x.colidx.size(0) - 1] - 1;
    if (outidx <= u1) {
      u1 = outidx;
    }
    y.n = x.n;
    if (u1 < 1) {
      u1 = 1;
    }
    y.d.set_size(u1);
    y.rowidx.set_size(u1);
    if (x.n + 1 < 0) {
      rtNonNegativeError(static_cast<double>(x.n + 1), o_emlrtDCI);
    }
    y.colidx.set_size(x.n + 1);
    y.colidx[0] = 1;
    outidx = 1;
    u1 = x.n;
    if (x.n > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int col{0}; col < u1; col++) {
      double r;
      int xend;
      int xstart_tmp;
      xstart_tmp = x.colidx[col];
      xend = x.colidx[col + 1] - 1;
      r = 0.0;
      if ((xstart_tmp <= x.colidx[col + 1] - 1) &&
          (x.colidx[col + 1] - 1 > 2147483646)) {
        check_forloop_overflow_error();
      }
      for (int xp{xstart_tmp}; xp <= xend; xp++) {
        r += x.d[xp - 1];
      }
      if (r != 0.0) {
        y.d[outidx - 1] = r;
        outidx++;
      }
      y.colidx[col + 1] = outidx;
    }
    outidx = y.colidx[y.colidx.size(0) - 1];
    if (outidx - 1 > 2147483646) {
      check_forloop_overflow_error();
    }
    for (u1 = 0; u1 <= outidx - 2; u1++) {
      y.rowidx[u1] = 1;
    }
  }
}

//
// Arguments    : const g_sparse &x
//                c_sparse &y
// Return Type  : void
//
void sum(const g_sparse &x, c_sparse &y)
{
  if (x.m == 0) {
    y.colidx.set_size(2);
    y.colidx[0] = 1;
    y.colidx[1] = 1;
    y.d.set_size(1);
    y.d[0] = 0.0;
    y.rowidx.set_size(1);
    y.rowidx[0] = 1;
  } else {
    double r;
    int xend;
    int xstart;
    y.d.set_size(1);
    y.rowidx.set_size(1);
    y.colidx.set_size(2);
    y.colidx[0] = 1;
    y.colidx[1] = 1;
    xstart = x.colidx[0];
    xend = x.colidx[1] - 1;
    r = 0.0;
    if ((x.colidx[0] <= x.colidx[1] - 1) && (x.colidx[1] - 1 > 2147483646)) {
      check_forloop_overflow_error();
    }
    for (int xp{xstart}; xp <= xend; xp++) {
      r += x.d[xp - 1];
    }
    if (r != 0.0) {
      y.d[0] = r;
      y.colidx[1] = 2;
    }
    if (y.colidx[1] - 2 >= 0) {
      y.rowidx[0] = 1;
    }
  }
}

//
// Arguments    : const array<double, 2U> &x
//                array<double, 1U> &y
// Return Type  : void
//
void sum(const array<double, 2U> &x, array<double, 1U> &y)
{
  array<double, 1U> bsum;
  if ((x.size(0) == 0) || (x.size(1) == 0)) {
    int firstBlockLength;
    y.set_size(x.size(0));
    firstBlockLength = x.size(0);
    for (int xblockoffset{0}; xblockoffset < firstBlockLength; xblockoffset++) {
      y[xblockoffset] = 0.0;
    }
  } else {
    int bvstride;
    int firstBlockLength;
    int lastBlockLength;
    int nblocks;
    int vstride;
    int xoffset;
    vstride = x.size(0);
    bvstride = x.size(0) << 10;
    y.set_size(x.size(0));
    bsum.set_size(x.size(0));
    if (x.size(1) <= 1024) {
      firstBlockLength = x.size(1);
      lastBlockLength = 0;
      nblocks = 1;
    } else {
      firstBlockLength = 1024;
      nblocks = static_cast<int>(static_cast<unsigned int>(x.size(1)) >> 10);
      lastBlockLength = x.size(1) - (nblocks << 10);
      if (lastBlockLength > 0) {
        nblocks++;
      } else {
        lastBlockLength = 1024;
      }
    }
    if (x.size(0) > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int xj{0}; xj < vstride; xj++) {
      y[xj] = x[xj];
      bsum[xj] = 0.0;
    }
    for (int k{2}; k <= firstBlockLength; k++) {
      xoffset = (k - 1) * vstride;
      if (vstride > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int xj{0}; xj < vstride; xj++) {
        y[xj] = y[xj] + x[xoffset + xj];
      }
    }
    for (int ib{2}; ib <= nblocks; ib++) {
      int xblockoffset;
      xblockoffset = (ib - 1) * bvstride;
      if (vstride > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int xj{0}; xj < vstride; xj++) {
        bsum[xj] = x[xblockoffset + xj];
      }
      if (ib == nblocks) {
        firstBlockLength = lastBlockLength;
      } else {
        firstBlockLength = 1024;
      }
      for (int k{2}; k <= firstBlockLength; k++) {
        xoffset = xblockoffset + (k - 1) * vstride;
        for (int xj{0}; xj < vstride; xj++) {
          bsum[xj] = bsum[xj] + x[xoffset + xj];
        }
      }
      for (int xj{0}; xj < vstride; xj++) {
        y[xj] = y[xj] + bsum[xj];
      }
    }
  }
}

} // namespace coder

//
// File trailer for sum.cpp
//
// [EOF]
//
