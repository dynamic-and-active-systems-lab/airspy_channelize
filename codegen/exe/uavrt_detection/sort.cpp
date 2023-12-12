//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sort.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "sort.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "sortIdx.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : array<double, 2U> &x
// Return Type  : void
//
namespace coder {
namespace internal {
void sort(array<double, 2U> &x)
{
  array<double, 1U> xwork;
  array<int, 2U> idx;
  array<int, 1U> iwork;
  int i;
  int ib;
  idx.set_size(1, x.size(1));
  ib = x.size(1);
  for (i = 0; i < ib; i++) {
    idx[i] = 0;
  }
  if (x.size(1) != 0) {
    double x4[4];
    int idx4[4];
    int bLen;
    int bLen2;
    int i1;
    int i2;
    int i3;
    int i4;
    int idx_tmp;
    int n;
    int wOffset_tmp;
    n = x.size(1);
    x4[0] = 0.0;
    idx4[0] = 0;
    x4[1] = 0.0;
    idx4[1] = 0;
    x4[2] = 0.0;
    idx4[2] = 0;
    x4[3] = 0.0;
    idx4[3] = 0;
    iwork.set_size(x.size(1));
    ib = x.size(1);
    xwork.set_size(x.size(1));
    for (i = 0; i < ib; i++) {
      iwork[i] = 0;
      xwork[i] = 0.0;
    }
    bLen2 = 0;
    ib = 0;
    if (x.size(1) > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int k{0}; k < n; k++) {
      if (std::isnan(x[k])) {
        idx_tmp = (n - bLen2) - 1;
        idx[idx_tmp] = k + 1;
        xwork[idx_tmp] = x[k];
        bLen2++;
      } else {
        ib++;
        idx4[ib - 1] = k + 1;
        x4[ib - 1] = x[k];
        if (ib == 4) {
          double d;
          double d1;
          ib = k - bLen2;
          if (x4[0] <= x4[1]) {
            i1 = 1;
            i2 = 2;
          } else {
            i1 = 2;
            i2 = 1;
          }
          if (x4[2] <= x4[3]) {
            i3 = 3;
            i4 = 4;
          } else {
            i3 = 4;
            i4 = 3;
          }
          d = x4[i3 - 1];
          d1 = x4[i1 - 1];
          if (d1 <= d) {
            d1 = x4[i2 - 1];
            if (d1 <= d) {
              i = i1;
              bLen = i2;
              i1 = i3;
              i2 = i4;
            } else if (d1 <= x4[i4 - 1]) {
              i = i1;
              bLen = i3;
              i1 = i2;
              i2 = i4;
            } else {
              i = i1;
              bLen = i3;
              i1 = i4;
            }
          } else {
            d = x4[i4 - 1];
            if (d1 <= d) {
              if (x4[i2 - 1] <= d) {
                i = i3;
                bLen = i1;
                i1 = i2;
                i2 = i4;
              } else {
                i = i3;
                bLen = i1;
                i1 = i4;
              }
            } else {
              i = i3;
              bLen = i4;
            }
          }
          idx[ib - 3] = idx4[i - 1];
          idx[ib - 2] = idx4[bLen - 1];
          idx[ib - 1] = idx4[i1 - 1];
          idx[ib] = idx4[i2 - 1];
          x[ib - 3] = x4[i - 1];
          x[ib - 2] = x4[bLen - 1];
          x[ib - 1] = x4[i1 - 1];
          x[ib] = x4[i2 - 1];
          ib = 0;
        }
      }
    }
    wOffset_tmp = x.size(1) - bLen2;
    if (ib > 0) {
      signed char perm[4];
      perm[1] = 0;
      perm[2] = 0;
      perm[3] = 0;
      if (ib == 1) {
        perm[0] = 1;
      } else if (ib == 2) {
        if (x4[0] <= x4[1]) {
          perm[0] = 1;
          perm[1] = 2;
        } else {
          perm[0] = 2;
          perm[1] = 1;
        }
      } else if (x4[0] <= x4[1]) {
        if (x4[1] <= x4[2]) {
          perm[0] = 1;
          perm[1] = 2;
          perm[2] = 3;
        } else if (x4[0] <= x4[2]) {
          perm[0] = 1;
          perm[1] = 3;
          perm[2] = 2;
        } else {
          perm[0] = 3;
          perm[1] = 1;
          perm[2] = 2;
        }
      } else if (x4[0] <= x4[2]) {
        perm[0] = 2;
        perm[1] = 1;
        perm[2] = 3;
      } else if (x4[1] <= x4[2]) {
        perm[0] = 2;
        perm[1] = 3;
        perm[2] = 1;
      } else {
        perm[0] = 3;
        perm[1] = 2;
        perm[2] = 1;
      }
      if (ib > 2147483646) {
        check_forloop_overflow_error();
      }
      i = static_cast<unsigned char>(ib);
      for (int k{0}; k < i; k++) {
        idx_tmp = (wOffset_tmp - ib) + k;
        bLen = perm[k];
        idx[idx_tmp] = idx4[bLen - 1];
        x[idx_tmp] = x4[bLen - 1];
      }
    }
    i1 = bLen2 >> 1;
    for (int k{0}; k < i1; k++) {
      ib = wOffset_tmp + k;
      i2 = idx[ib];
      idx_tmp = (n - k) - 1;
      idx[ib] = idx[idx_tmp];
      idx[idx_tmp] = i2;
      x[ib] = xwork[idx_tmp];
      x[idx_tmp] = xwork[ib];
    }
    if ((bLen2 & 1) != 0) {
      i = wOffset_tmp + i1;
      x[i] = xwork[i];
    }
    ib = 2;
    if (wOffset_tmp > 1) {
      if (x.size(1) >= 256) {
        n = wOffset_tmp >> 8;
        if (n > 0) {
          for (int b{0}; b < n; b++) {
            double b_xwork[256];
            int b_iwork[256];
            i4 = (b << 8) - 1;
            for (int b_b{0}; b_b < 6; b_b++) {
              bLen = 1 << (b_b + 2);
              bLen2 = bLen << 1;
              i = 256 >> (b_b + 3);
              for (int k{0}; k < i; k++) {
                i2 = (i4 + k * bLen2) + 1;
                for (i1 = 0; i1 < bLen2; i1++) {
                  ib = i2 + i1;
                  b_iwork[i1] = idx[ib];
                  b_xwork[i1] = x[ib];
                }
                i3 = 0;
                i1 = bLen;
                ib = i2 - 1;
                int exitg1;
                do {
                  exitg1 = 0;
                  ib++;
                  if (b_xwork[i3] <= b_xwork[i1]) {
                    idx[ib] = b_iwork[i3];
                    x[ib] = b_xwork[i3];
                    if (i3 + 1 < bLen) {
                      i3++;
                    } else {
                      exitg1 = 1;
                    }
                  } else {
                    idx[ib] = b_iwork[i1];
                    x[ib] = b_xwork[i1];
                    if (i1 + 1 < bLen2) {
                      i1++;
                    } else {
                      ib -= i3;
                      for (i1 = i3 + 1; i1 <= bLen; i1++) {
                        idx_tmp = ib + i1;
                        idx[idx_tmp] = b_iwork[i1 - 1];
                        x[idx_tmp] = b_xwork[i1 - 1];
                      }
                      exitg1 = 1;
                    }
                  }
                } while (exitg1 == 0);
              }
            }
          }
          ib = n << 8;
          i1 = wOffset_tmp - ib;
          if (i1 > 0) {
            merge_block(idx, x, ib, i1, 2, iwork, xwork);
          }
          ib = 8;
        }
      }
      merge_block(idx, x, 0, wOffset_tmp, ib, iwork, xwork);
    }
  }
}

//
// Arguments    : array<double, 1U> &x
//                array<int, 1U> &idx
// Return Type  : void
//
void sort(array<double, 1U> &x, array<int, 1U> &idx)
{
  array<double, 1U> vwork;
  array<double, 1U> xwork;
  array<int, 1U> iidx;
  array<int, 1U> iwork;
  int dim;
  int i;
  int vlen;
  int vstride;
  boolean_T overflow;
  dim = 0;
  if (x.size(0) != 1) {
    dim = -1;
  }
  if (dim + 2 <= 1) {
    i = x.size(0);
  } else {
    i = 1;
  }
  vlen = i - 1;
  vwork.set_size(i);
  idx.set_size(x.size(0));
  vstride = 1;
  for (int k{0}; k <= dim; k++) {
    vstride *= x.size(0);
  }
  overflow = (vstride > 2147483646);
  for (int b_i{0}; b_i < 1; b_i++) {
    if (overflow) {
      check_forloop_overflow_error();
    }
    for (int j{0}; j < vstride; j++) {
      int i1;
      if (i > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int k{0}; k <= vlen; k++) {
        vwork[k] = x[j + k * vstride];
      }
      iidx.set_size(vwork.size(0));
      dim = vwork.size(0);
      for (i1 = 0; i1 < dim; i1++) {
        iidx[i1] = 0;
      }
      if (vwork.size(0) != 0) {
        double x4[4];
        int idx4[4];
        int bLen;
        int bLen2;
        int b_i1;
        int i2;
        int i3;
        int i4;
        int iidx_tmp;
        int n;
        int wOffset_tmp;
        n = vwork.size(0);
        x4[0] = 0.0;
        idx4[0] = 0;
        x4[1] = 0.0;
        idx4[1] = 0;
        x4[2] = 0.0;
        idx4[2] = 0;
        x4[3] = 0.0;
        idx4[3] = 0;
        iwork.set_size(vwork.size(0));
        dim = vwork.size(0);
        xwork.set_size(vwork.size(0));
        for (i1 = 0; i1 < dim; i1++) {
          iwork[i1] = 0;
          xwork[i1] = 0.0;
        }
        bLen2 = 0;
        dim = 0;
        if (vwork.size(0) > 2147483646) {
          check_forloop_overflow_error();
        }
        for (int k{0}; k < n; k++) {
          if (std::isnan(vwork[k])) {
            iidx_tmp = (n - bLen2) - 1;
            iidx[iidx_tmp] = k + 1;
            xwork[iidx_tmp] = vwork[k];
            bLen2++;
          } else {
            dim++;
            idx4[dim - 1] = k + 1;
            x4[dim - 1] = vwork[k];
            if (dim == 4) {
              double d;
              double d1;
              dim = k - bLen2;
              if (x4[0] <= x4[1]) {
                b_i1 = 1;
                i2 = 2;
              } else {
                b_i1 = 2;
                i2 = 1;
              }
              if (x4[2] <= x4[3]) {
                i3 = 3;
                i4 = 4;
              } else {
                i3 = 4;
                i4 = 3;
              }
              d = x4[i3 - 1];
              d1 = x4[b_i1 - 1];
              if (d1 <= d) {
                d1 = x4[i2 - 1];
                if (d1 <= d) {
                  i1 = b_i1;
                  bLen = i2;
                  b_i1 = i3;
                  i2 = i4;
                } else if (d1 <= x4[i4 - 1]) {
                  i1 = b_i1;
                  bLen = i3;
                  b_i1 = i2;
                  i2 = i4;
                } else {
                  i1 = b_i1;
                  bLen = i3;
                  b_i1 = i4;
                }
              } else {
                d = x4[i4 - 1];
                if (d1 <= d) {
                  if (x4[i2 - 1] <= d) {
                    i1 = i3;
                    bLen = b_i1;
                    b_i1 = i2;
                    i2 = i4;
                  } else {
                    i1 = i3;
                    bLen = b_i1;
                    b_i1 = i4;
                  }
                } else {
                  i1 = i3;
                  bLen = i4;
                }
              }
              iidx[dim - 3] = idx4[i1 - 1];
              iidx[dim - 2] = idx4[bLen - 1];
              iidx[dim - 1] = idx4[b_i1 - 1];
              iidx[dim] = idx4[i2 - 1];
              vwork[dim - 3] = x4[i1 - 1];
              vwork[dim - 2] = x4[bLen - 1];
              vwork[dim - 1] = x4[b_i1 - 1];
              vwork[dim] = x4[i2 - 1];
              dim = 0;
            }
          }
        }
        wOffset_tmp = vwork.size(0) - bLen2;
        if (dim > 0) {
          signed char perm[4];
          perm[1] = 0;
          perm[2] = 0;
          perm[3] = 0;
          if (dim == 1) {
            perm[0] = 1;
          } else if (dim == 2) {
            if (x4[0] <= x4[1]) {
              perm[0] = 1;
              perm[1] = 2;
            } else {
              perm[0] = 2;
              perm[1] = 1;
            }
          } else if (x4[0] <= x4[1]) {
            if (x4[1] <= x4[2]) {
              perm[0] = 1;
              perm[1] = 2;
              perm[2] = 3;
            } else if (x4[0] <= x4[2]) {
              perm[0] = 1;
              perm[1] = 3;
              perm[2] = 2;
            } else {
              perm[0] = 3;
              perm[1] = 1;
              perm[2] = 2;
            }
          } else if (x4[0] <= x4[2]) {
            perm[0] = 2;
            perm[1] = 1;
            perm[2] = 3;
          } else if (x4[1] <= x4[2]) {
            perm[0] = 2;
            perm[1] = 3;
            perm[2] = 1;
          } else {
            perm[0] = 3;
            perm[1] = 2;
            perm[2] = 1;
          }
          if (dim > 2147483646) {
            check_forloop_overflow_error();
          }
          i1 = static_cast<unsigned char>(dim);
          for (int k{0}; k < i1; k++) {
            iidx_tmp = (wOffset_tmp - dim) + k;
            bLen = perm[k];
            iidx[iidx_tmp] = idx4[bLen - 1];
            vwork[iidx_tmp] = x4[bLen - 1];
          }
        }
        dim = bLen2 >> 1;
        for (int k{0}; k < dim; k++) {
          b_i1 = wOffset_tmp + k;
          i2 = iidx[b_i1];
          iidx_tmp = (n - k) - 1;
          iidx[b_i1] = iidx[iidx_tmp];
          iidx[iidx_tmp] = i2;
          vwork[b_i1] = xwork[iidx_tmp];
          vwork[iidx_tmp] = xwork[b_i1];
        }
        if ((bLen2 & 1) != 0) {
          dim += wOffset_tmp;
          vwork[dim] = xwork[dim];
        }
        dim = 2;
        if (wOffset_tmp > 1) {
          if (vwork.size(0) >= 256) {
            n = wOffset_tmp >> 8;
            if (n > 0) {
              for (int b{0}; b < n; b++) {
                double b_xwork[256];
                int b_iwork[256];
                i4 = (b << 8) - 1;
                for (int b_b{0}; b_b < 6; b_b++) {
                  bLen = 1 << (b_b + 2);
                  bLen2 = bLen << 1;
                  i1 = 256 >> (b_b + 3);
                  for (int k{0}; k < i1; k++) {
                    i2 = (i4 + k * bLen2) + 1;
                    for (b_i1 = 0; b_i1 < bLen2; b_i1++) {
                      dim = i2 + b_i1;
                      b_iwork[b_i1] = iidx[dim];
                      b_xwork[b_i1] = vwork[dim];
                    }
                    i3 = 0;
                    b_i1 = bLen;
                    dim = i2 - 1;
                    int exitg1;
                    do {
                      exitg1 = 0;
                      dim++;
                      if (b_xwork[i3] <= b_xwork[b_i1]) {
                        iidx[dim] = b_iwork[i3];
                        vwork[dim] = b_xwork[i3];
                        if (i3 + 1 < bLen) {
                          i3++;
                        } else {
                          exitg1 = 1;
                        }
                      } else {
                        iidx[dim] = b_iwork[b_i1];
                        vwork[dim] = b_xwork[b_i1];
                        if (b_i1 + 1 < bLen2) {
                          b_i1++;
                        } else {
                          dim -= i3;
                          for (b_i1 = i3 + 1; b_i1 <= bLen; b_i1++) {
                            iidx_tmp = dim + b_i1;
                            iidx[iidx_tmp] = b_iwork[b_i1 - 1];
                            vwork[iidx_tmp] = b_xwork[b_i1 - 1];
                          }
                          exitg1 = 1;
                        }
                      }
                    } while (exitg1 == 0);
                  }
                }
              }
              dim = n << 8;
              b_i1 = wOffset_tmp - dim;
              if (b_i1 > 0) {
                merge_block(iidx, vwork, dim, b_i1, 2, iwork, xwork);
              }
              dim = 8;
            }
          }
          merge_block(iidx, vwork, 0, wOffset_tmp, dim, iwork, xwork);
        }
      }
      for (int k{0}; k <= vlen; k++) {
        i1 = j + k * vstride;
        x[i1] = vwork[k];
        idx[i1] = iidx[k];
      }
    }
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for sort.cpp
//
// [EOF]
//
