//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: makepulsestruc.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "makepulsestruc.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_internal_types.h"
#include "coder_array.h"

// Function Definitions
//
// PULSE is an thepulseect containing the details of an individual pulse
//
// INPUTS
//    A           Amplitude
//    SNR         Signal to noise ratio in dB - This is often estimated as
//    signal+noise to noise. yw          STFT value at location (time and freq)
//    of pulse. w here mean omega. This is equation 14 in the paper draft. t_0
//    Start time of pulse t_f         End time of pulse t_next      Time range
//    [tstart tend] of expected location of next pulse fp          Peak
//    frequency of pulse (Center frequency if symmetric in frequency domain
//    fstart      Start of the frequency bandwidth
//    fend        End of frequency bandwidth
//
// Arguments    : double A
//                double yw
//                double SNR
//                double t_0
//                double t_f
//                const double t_next[2]
//                double fp
//                double fstart
//                double fend
//                c_struct_T *thepulse
// Return Type  : void
//
void b_makepulsestruc(double A, double yw, double SNR, double t_0, double t_f,
                      const double t_next[2], double fp, double fstart,
                      double fend, c_struct_T *thepulse)
{
  // OUTPUTS
  //    thePulse    a pulse struture with the properties:
  //          A           Amplitude
  //          P           Power
  //          SNR         Signal to noise ratio in dB - This is often estimated
  //          as signal+noise to noise. yw          STFT value at location (time
  //          and freq) of pulse. w here mean omega. This is equation 14 in the
  //          paper draft. t_0         Start time of pulse t_f         End time
  //          of pulse t_next      Time range [tstart tend] of expected location
  //          of next pulse fp          Peak frequency of pulse (Center
  //          frequency if symmetric in frequency domain fstart      Start of
  //          the frequency bandwidth fend        End of frequency bandwidth
  //          mode        State machine mode under which pulse was discovered
  //          det_dec     Detection decision (true/false)
  //          con_dec     Was the pulse confirmed (true/false). In tracking, no
  //          confirmation step is executed so we record false.
  //
  // Author:    Michael Shafer
  // Date:      Summer 2022
  // --------------------------------------------------------------------------
  //
  // Needed to let coder know the mode string will be of variable length
  // https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  // dims 0 if fixed, 1 if variable
  // Allows for array construction
  // https://www.mathworks.com/help/matlab/matlab_oop/initialize-thepulseect-arrays.html
  thepulse->A = A;
  thepulse->P = A * A;
  thepulse->SNR = SNR;
  thepulse->yw = yw;
  thepulse->t_0 = t_0;
  thepulse->t_f = t_f;
  thepulse->t_next[0] = t_next[0];
  thepulse->t_next[1] = t_next[1];
  thepulse->fp = fp;
  thepulse->fstart = fstart;
  thepulse->fend = fend;
  thepulse->mode.set_size(1, 3);
  thepulse->mode[0] = 'T';
  thepulse->mode[1] = 'B';
  thepulse->mode[2] = 'D';
  thepulse->det_dec = false;
  thepulse->con_dec = false;
}

//
// PULSE is an thepulseect containing the details of an individual pulse
//
// INPUTS
//    A           Amplitude
//    SNR         Signal to noise ratio in dB - This is often estimated as
//    signal+noise to noise. yw          STFT value at location (time and freq)
//    of pulse. w here mean omega. This is equation 14 in the paper draft. t_0
//    Start time of pulse t_f         End time of pulse t_next      Time range
//    [tstart tend] of expected location of next pulse fp          Peak
//    frequency of pulse (Center frequency if symmetric in frequency domain
//    fstart      Start of the frequency bandwidth
//    fend        End of frequency bandwidth
//
// Arguments    : double thepulse_t_next[2]
//                coder::array<char, 2U> &thepulse_mode
//                double &thepulse_P
//                double &thepulse_SNR
//                double &thepulse_yw
//                double &thepulse_t_0
//                double &thepulse_t_f
//                double &thepulse_fp
//                double &thepulse_fstart
//                double &thepulse_fend
//                boolean_T &thepulse_det_dec
//                boolean_T &thepulse_con_dec
// Return Type  : double
//
double makepulsestruc(double thepulse_t_next[2],
                      coder::array<char, 2U> &thepulse_mode, double &thepulse_P,
                      double &thepulse_SNR, double &thepulse_yw,
                      double &thepulse_t_0, double &thepulse_t_f,
                      double &thepulse_fp, double &thepulse_fstart,
                      double &thepulse_fend, boolean_T &thepulse_det_dec,
                      boolean_T &thepulse_con_dec)
{
  double thepulse_A;
  // OUTPUTS
  //    thePulse    a pulse struture with the properties:
  //          A           Amplitude
  //          P           Power
  //          SNR         Signal to noise ratio in dB - This is often estimated
  //          as signal+noise to noise. yw          STFT value at location (time
  //          and freq) of pulse. w here mean omega. This is equation 14 in the
  //          paper draft. t_0         Start time of pulse t_f         End time
  //          of pulse t_next      Time range [tstart tend] of expected location
  //          of next pulse fp          Peak frequency of pulse (Center
  //          frequency if symmetric in frequency domain fstart      Start of
  //          the frequency bandwidth fend        End of frequency bandwidth
  //          mode        State machine mode under which pulse was discovered
  //          det_dec     Detection decision (true/false)
  //          con_dec     Was the pulse confirmed (true/false). In tracking, no
  //          confirmation step is executed so we record false.
  //
  // Author:    Michael Shafer
  // Date:      Summer 2022
  // --------------------------------------------------------------------------
  //
  // Needed to let coder know the mode string will be of variable length
  // https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  // dims 0 if fixed, 1 if variable
  thepulse_t_next[0] = rtNaN;
  thepulse_t_next[1] = rtNaN;
  thepulse_mode.set_size(1, 3);
  thepulse_mode[0] = 'T';
  thepulse_mode[1] = 'B';
  thepulse_mode[2] = 'D';
  thepulse_A = rtNaN;
  thepulse_P = rtNaN;
  thepulse_SNR = rtNaN;
  thepulse_yw = rtNaN;
  thepulse_t_0 = rtNaN;
  thepulse_t_f = rtNaN;
  thepulse_fp = rtNaN;
  thepulse_fstart = rtNaN;
  thepulse_fend = rtNaN;
  thepulse_det_dec = false;
  thepulse_con_dec = false;
  return thepulse_A;
}

//
// File trailer for makepulsestruc.cpp
//
// [EOF]
//
