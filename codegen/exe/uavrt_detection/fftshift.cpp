//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fftshift.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "fftshift.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : array<creal_T, 2U> &x
// Return Type  : void
//
namespace coder {
void fftshift(array<creal_T, 2U> &x)
{
  if (x.size(0) > 1) {
    int vlend2;
    vlend2 = static_cast<int>(static_cast<unsigned int>(x.size(0)) >> 1) - 1;
    if ((vlend2 + 1) << 1 == x.size(0)) {
      for (int k{0}; k <= vlend2; k++) {
        double xtmp_im;
        double xtmp_re;
        int i;
        xtmp_re = x[k].re;
        xtmp_im = x[k].im;
        i = (vlend2 + k) + 1;
        x[k] = x[i];
        x[i].re = xtmp_re;
        x[i].im = xtmp_im;
      }
    } else {
      double xtmp_im;
      double xtmp_re;
      xtmp_re = x[vlend2 + 1].re;
      xtmp_im = x[vlend2 + 1].im;
      for (int k{0}; k <= vlend2; k++) {
        int i;
        i = (vlend2 + k) + 1;
        x[i] = x[k];
        x[k] = x[i + 1];
      }
      vlend2 = (vlend2 + vlend2) + 2;
      x[vlend2].re = xtmp_re;
      x[vlend2].im = xtmp_im;
    }
  }
}

} // namespace coder

//
// File trailer for fftshift.cpp
//
// [EOF]
//
