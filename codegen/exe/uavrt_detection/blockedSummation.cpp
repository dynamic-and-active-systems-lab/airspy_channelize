//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: blockedSummation.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "blockedSummation.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const array<double, 1U> &x
//                int vlen
// Return Type  : double
//
namespace coder {
double blockedSummation(const array<double, 1U> &x, int vlen)
{
  double y;
  if ((x.size(0) == 0) || (vlen == 0)) {
    y = 0.0;
  } else {
    int firstBlockLength;
    int lastBlockLength;
    int nblocks;
    if (vlen <= 1024) {
      firstBlockLength = vlen;
      lastBlockLength = 0;
      nblocks = 1;
    } else {
      firstBlockLength = 1024;
      nblocks = vlen / 1024;
      lastBlockLength = vlen - (nblocks << 10);
      if (lastBlockLength > 0) {
        nblocks++;
      } else {
        lastBlockLength = 1024;
      }
    }
    y = x[0];
    for (int k{2}; k <= firstBlockLength; k++) {
      y += x[k - 1];
    }
    for (int ib{2}; ib <= nblocks; ib++) {
      double bsum;
      int hi;
      firstBlockLength = (ib - 1) << 10;
      bsum = x[firstBlockLength];
      if (ib == nblocks) {
        hi = lastBlockLength;
      } else {
        hi = 1024;
      }
      for (int k{2}; k <= hi; k++) {
        bsum += x[(firstBlockLength + k) - 1];
      }
      y += bsum;
    }
  }
  return y;
}

//
// Arguments    : const array<double, 1U> &x
//                int vlen
//                int &counts
// Return Type  : double
//
double colMajorFlatIter(const array<double, 1U> &x, int vlen, int &counts)
{
  double bsum;
  double y;
  int firstBlockLength;
  int lastBlockLength;
  int nblocks;
  if (vlen <= 1024) {
    firstBlockLength = vlen;
    lastBlockLength = 0;
    nblocks = 1;
  } else {
    firstBlockLength = 1024;
    nblocks = vlen / 1024;
    lastBlockLength = vlen - (nblocks << 10);
    if (lastBlockLength > 0) {
      nblocks++;
    } else {
      lastBlockLength = 1024;
    }
  }
  if (std::isnan(x[0])) {
    y = 0.0;
    counts = 0;
  } else {
    y = x[0];
    counts = 1;
  }
  for (int k{2}; k <= firstBlockLength; k++) {
    bsum = x[k - 1];
    if (!std::isnan(bsum)) {
      y += bsum;
      counts++;
    }
  }
  for (int ib{2}; ib <= nblocks; ib++) {
    int hi;
    firstBlockLength = (ib - 1) << 10;
    if (std::isnan(x[firstBlockLength])) {
      bsum = 0.0;
    } else {
      bsum = x[firstBlockLength];
      counts++;
    }
    if (ib == nblocks) {
      hi = lastBlockLength;
    } else {
      hi = 1024;
    }
    for (int k{2}; k <= hi; k++) {
      int xoffset;
      xoffset = (firstBlockLength + k) - 1;
      if (!std::isnan(x[xoffset])) {
        bsum += x[xoffset];
        counts++;
      }
    }
    y += bsum;
  }
  return y;
}

} // namespace coder

//
// File trailer for blockedSummation.cpp
//
// [EOF]
//
