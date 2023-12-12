//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: wfmstft.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

#ifndef WFMSTFT_H
#define WFMSTFT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class wfmstft {
public:
  void updatepsd();
  coder::array<creal_T, 2U> S;
  coder::array<double, 1U> f;
  coder::array<double, 1U> t;
  coder::array<double, 1U> psd;
  double dt;
  double T;
  coder::array<double, 1U> wind;
};

#endif
//
// File trailer for wfmstft.h
//
// [EOF]
//
