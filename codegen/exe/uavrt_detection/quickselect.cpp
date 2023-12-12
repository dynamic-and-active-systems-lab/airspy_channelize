//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: quickselect.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "quickselect.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Declarations
namespace coder {
namespace internal {
static int thirdOfFive(const array<double, 1U> &v, int ia, int ib);

}
} // namespace coder

// Function Definitions
//
// Arguments    : const array<double, 1U> &v
//                int ia
//                int ib
// Return Type  : int
//
namespace coder {
namespace internal {
static int thirdOfFive(const array<double, 1U> &v, int ia, int ib)
{
  int im;
  if ((ia == ib) || (ia + 1 == ib)) {
    im = ia;
  } else if ((ia + 2 == ib) || (ia + 3 == ib)) {
    double v4;
    v4 = v[ia - 1];
    if (v4 < v[ia]) {
      double v5;
      v5 = v[ia + 1];
      if (v[ia] < v5) {
        im = ia + 1;
      } else if (v4 < v5) {
        im = ia + 2;
      } else {
        im = ia;
      }
    } else {
      double v5;
      v5 = v[ia + 1];
      if (v4 < v5) {
        im = ia;
      } else if (v[ia] < v5) {
        im = ia + 2;
      } else {
        im = ia + 1;
      }
    }
  } else {
    double v4;
    double v5;
    int j2;
    int j3;
    int j4;
    int j5;
    v4 = v[ia - 1];
    if (v4 < v[ia]) {
      v5 = v[ia + 1];
      if (v[ia] < v5) {
        im = ia;
        j2 = ia;
        j3 = ia + 2;
      } else if (v4 < v5) {
        im = ia;
        j2 = ia + 1;
        j3 = ia + 1;
      } else {
        im = ia + 2;
        j2 = ia - 1;
        j3 = ia + 1;
      }
    } else {
      v5 = v[ia + 1];
      if (v4 < v5) {
        im = ia + 1;
        j2 = ia - 1;
        j3 = ia + 2;
      } else if (v[ia] < v5) {
        im = ia + 1;
        j2 = ia + 1;
        j3 = ia;
      } else {
        im = ia + 2;
        j2 = ia;
        j3 = ia;
      }
    }
    j4 = ia;
    j5 = ia + 1;
    v4 = v[ia + 2];
    v5 = v[ia + 3];
    if (v5 < v4) {
      j4 = ia + 1;
      j5 = ia;
      v5 = v4;
      v4 = v[ia + 3];
    }
    if (!(v5 < v[im - 1])) {
      if (v5 < v[j2]) {
        im = j5 + 3;
      } else if (v4 < v[j2]) {
        im = j2 + 1;
      } else if (v4 < v[j3 - 1]) {
        im = j4 + 3;
      } else {
        im = j3;
      }
    }
  }
  return im;
}

//
// Arguments    : array<double, 1U> &v
//                int n
//                int vlen
//                int &nfirst
//                int &nlast
// Return Type  : double
//
double quickselect(array<double, 1U> &v, int n, int vlen, int &nfirst,
                   int &nlast)
{
  double vn;
  if (n > vlen) {
    vn = rtNaN;
    nfirst = 0;
    nlast = 0;
  } else {
    int ia;
    int ib;
    int ilast;
    int ipiv;
    int oldnv;
    boolean_T checkspeed;
    boolean_T exitg1;
    boolean_T isslow;
    ipiv = n;
    ia = 0;
    ib = vlen - 1;
    nfirst = 1;
    ilast = vlen - 1;
    oldnv = vlen;
    checkspeed = false;
    isslow = false;
    exitg1 = false;
    while ((!exitg1) && (ia + 1 < ib + 1)) {
      double vref;
      boolean_T guard1;
      vref = v[ipiv - 1];
      v[ipiv - 1] = v[ib];
      v[ib] = vref;
      ilast = ia;
      ipiv = -1;
      for (int k{ia + 1}; k <= ib; k++) {
        double vk_tmp;
        vk_tmp = v[k - 1];
        if (vk_tmp == vref) {
          v[k - 1] = v[ilast];
          v[ilast] = vk_tmp;
          ipiv++;
          ilast++;
        } else if (vk_tmp < vref) {
          v[k - 1] = v[ilast];
          v[ilast] = vk_tmp;
          ilast++;
        }
      }
      v[ib] = v[ilast];
      v[ilast] = vref;
      guard1 = false;
      if (n <= ilast + 1) {
        nfirst = ilast - ipiv;
        if (n >= nfirst) {
          exitg1 = true;
        } else {
          ib = ilast - 1;
          guard1 = true;
        }
      } else {
        ia = ilast + 1;
        guard1 = true;
      }
      if (guard1) {
        int c;
        c = (ib - ia) + 1;
        if (checkspeed) {
          isslow = (c > oldnv / 2);
          oldnv = c;
        }
        checkspeed = !checkspeed;
        if (isslow) {
          while (c > 1) {
            int ngroupsof5;
            ngroupsof5 = c / 5;
            nlast = c - ngroupsof5 * 5;
            c = ngroupsof5;
            for (int k{0}; k < ngroupsof5; k++) {
              ipiv = (ia + k * 5) + 1;
              ipiv = thirdOfFive(v, ipiv, ipiv + 4) - 1;
              ilast = ia + k;
              vref = v[ilast];
              v[ilast] = v[ipiv];
              v[ipiv] = vref;
            }
            if (nlast > 0) {
              ipiv = (ia + ngroupsof5 * 5) + 1;
              ipiv = thirdOfFive(v, ipiv, (ipiv + nlast) - 1) - 1;
              ilast = ia + ngroupsof5;
              vref = v[ilast];
              v[ilast] = v[ipiv];
              v[ipiv] = vref;
              c = ngroupsof5 + 1;
            }
          }
        } else if (c >= 3) {
          ipiv = ia + static_cast<int>(static_cast<unsigned int>(c - 1) >> 1);
          if (v[ia] < v[ipiv]) {
            if (!(v[ipiv] < v[ib])) {
              if (v[ia] < v[ib]) {
                ipiv = ib;
              } else {
                ipiv = ia;
              }
            }
          } else if (v[ia] < v[ib]) {
            ipiv = ia;
          } else if (v[ipiv] < v[ib]) {
            ipiv = ib;
          }
          if (ipiv + 1 > ia + 1) {
            vref = v[ia];
            v[ia] = v[ipiv];
            v[ipiv] = vref;
          }
        }
        ipiv = ia + 1;
        nfirst = ia + 1;
        ilast = ib;
      }
    }
    vn = v[ilast];
    nlast = ilast + 1;
  }
  return vn;
}

} // namespace internal
} // namespace coder

//
// File trailer for quickselect.cpp
//
// [EOF]
//
