//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: makepulsestruc.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

#ifndef MAKEPULSESTRUC_H
#define MAKEPULSESTRUC_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct c_struct_T;

// Function Declarations
void b_makepulsestruc(double A, double yw, double SNR, double t_0, double t_f,
                      const double t_next[2], double fp, double fstart,
                      double fend, c_struct_T *thepulse);

double makepulsestruc(double thepulse_t_next[2],
                      coder::array<char, 2U> &thepulse_mode, double &thepulse_P,
                      double &thepulse_SNR, double &thepulse_yw,
                      double &thepulse_t_0, double &thepulse_t_f,
                      double &thepulse_fp, double &thepulse_fstart,
                      double &thepulse_fend, boolean_T &thepulse_det_dec,
                      boolean_T &thepulse_con_dec);

#endif
//
// File trailer for makepulsestruc.h
//
// [EOF]
//
