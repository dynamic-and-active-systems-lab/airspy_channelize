//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection_internal_types.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

#ifndef UAVRT_DETECTION_INTERNAL_TYPES_H
#define UAVRT_DETECTION_INTERNAL_TYPES_H

// Include Files
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"

// Type Definitions
struct struct_T {
  int xstart;
  int xend;
  int depth;
};

struct b_struct_T {
  double mu;
  double sigma;
  double pf;
};

struct cell_wrap_2 {
  unsigned int f1[8];
};

struct c_struct_T {
  double A;
  double P;
  double SNR;
  double yw;
  double t_0;
  double t_f;
  double t_next[2];
  double fp;
  double fstart;
  double fend;
  coder::array<char, 2U> mode;
  boolean_T det_dec;
  boolean_T con_dec;
};

struct d_struct_T {
  coder::array<int, 1U> a;
  coder::array<int, 1U> b;
};

struct e_struct_T {
  coder::array<int, 1U> x;
};

struct f_struct_T {
  double sb;
};

#endif
//
// File trailer for uavrt_detection_internal_types.h
//
// [EOF]
//
