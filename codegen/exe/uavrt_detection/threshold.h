//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: threshold.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

#ifndef THRESHOLD_H
#define THRESHOLD_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
class waveform;

// Type Definitions
class threshold {
public:
  void init(double b_pf);
  void makenewthreshold(const waveform &Wfm);
  void setthreshprops(double thresh, const waveform &Wfm);
  double pf;
  double evMuParam;
  double evSigmaParam;
  double thresh1W;
  coder::array<double, 1U> threshVecFine;
  unsigned int trials;
};

#endif
//
// File trailer for threshold.h
//
// [EOF]
//
