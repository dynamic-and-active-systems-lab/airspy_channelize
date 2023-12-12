//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: waveformcopy.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "waveformcopy.h"
#include "makepulsestruc.h"
#include "pulsestats.h"
#include "rt_nonfinite.h"
#include "threshold.h"
#include "uavrt_detection_internal_types.h"
#include "validator_check_size.h"
#include "waveform.h"
#include "wfmstft.h"
#include "coder_array.h"
#include "coder_bounded_array.h"

// Function Definitions
//
// WAVEFORMCOPY makes a copy of the input waveform. Waveforms are handle
// objects, as are some of their properties. This function make new instances
// of these objects.
//
// INPUTS:
//    wfmIn   an individual waveform
// OUTPUTS
//    wfmOut  copy of input waveform
//
//
// Arguments    : waveform &wfmIn
//                wfmstft &iobj_0
//                pulsestats &iobj_1
//                waveform &iobj_2
// Return Type  : waveform *
//
waveform *waveformcopy(waveform &wfmIn, wfmstft &iobj_0, pulsestats &iobj_1,
                       waveform &iobj_2)
{
  pulsestats *val;
  threshold _in;
  waveform *wfmOut;
  wfmstft *obj;
  coder::array<c_struct_T, 2U> b__in;
  coder::array<c_struct_T, 2U> b_wfmIn;
  coder::array<c_struct_T, 2U> r2;
  coder::array<c_struct_T, 2U> r3;
  coder::array<creal_T, 2U> c__in;
  coder::array<creal32_T, 2U> e__in;
  coder::array<double, 2U> d_wfmIn;
  coder::array<double, 1U> d__in;
  coder::array<boolean_T, 2U> c_wfmIn;
  coder::bounded_array<c_struct_T, 1U, 2U> r1;
  c_struct_T r;
  double e_wfmIn[2];
  double b_val;
  int loop_ub;
  // WAVEFORM Constructs an instance of this class
  // INPUTS:
  //    x       1xn     Vector of samples
  //    Fs      1x1     Sample frequency (Hz)
  //    t_0     1x1     Time stamp of first element (s)
  // 	ps_pre  1x1     Pulse stats object from previous data (priori)
  //    OLF     1x1     Overlap fraction as decimal (0.5 = 50%
  //                    overlap)
  // OUTPUTS:
  //    obj             The waveform object
  //             %%
  wfmOut = &iobj_2;
  iobj_2.x.set_size(1, 0);
  iobj_2.W.set_size(0, 0);
  iobj_2.Wf.set_size(0);
  // THRESHOLD Constructs an instance of this class
  // INPUTS:
  //    pf  probability of false alarm
  //
  _in.trials = 100U;
  _in.pf = 0.01;
  _in.evMuParam = 0.0;
  _in.evSigmaParam = 0.0;
  _in.thresh1W = 0.0;
  _in.threshVecFine.set_size(1);
  _in.threshVecFine[0] = 0.0;
  iobj_2.thresh = _in;
  // Set custom types for coder.
  // WFMSTFT Constructs and returns an instance of this class
  //
  // An waveform object must be passed to this construction method
  // so that the constructor has access to the data vector, desired
  // overlap fraction, and priori pulse data, which is used to
  // develop the window sizes.
  // INPUTS:
  //    waveform_obj   A single waveform object with prior
  //                   dependent properties set.
  // OUTPUTS:
  //    obj             A wfmstft object
  //             %%
  //
  // The following are variable sized properties. To tell coder
  // that they may vary setup as a local variable size variable
  // first, then set.
  // Instructions on
  // https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  // maxFs*maxpulsewidth
  // Now actually assign them
  iobj_0.S.set_size(0, 0);
  iobj_0.t.set_size(0);
  iobj_0.f.set_size(0);
  iobj_0.psd.set_size(0);
  iobj_0.wind.set_size(0);
  iobj_0.dt = 0.0;
  iobj_0.T = 0.0;
  iobj_2.stft = &iobj_0;
  // PULSESTATS Constructs an instance of this class
  //
  // INPUTS:
  //    tp      1x1     Duration of pulse (second)
  //    tip     1x1     Inter-pulse time (seconds)
  //    tipu    1x1     Inter-pulse time uncertainty (seconds)
  //    tipj    1x1     Inter-pulse time jitter (deviations from means)
  //    (seconds) fp      1x1     Pulses' center frequency (Hz) (if known)
  //    fstart  1x1     Lower frequency bound pulses' center frequency (Hz) (if
  //    known) fend    1x1     Upper frequency bound pulses' center frequency
  //    (Hz) (if known) tmplt   1xn     Pulse template. See properies for
  //                    definition. Usually set to [1 1] for
  //                    square pulse.
  //    pl      px1     Vector of pulse objects in waveform (if
  //                    known). If unknown enter a blank pulse made
  //                    from the contstructor "pulse";
  //  Note: Unknown inputs should be set to NaN.
  //
  // OUTPUTS:
  //    pulsestats object
  //
  //             %%
  // Tell coder these are variable size.
  // Now actually assign them
  r.A = makepulsestruc(r.t_next, r.mode, r.P, r.SNR, r.yw, r.t_0, r.t_f, r.fp,
                       r.fstart, r.fend, r.det_dec, r.con_dec);
  r1.size[0] = 1;
  r1.size[1] = 1;
  r1.data[0] = r;
  r2.set(&r1.data[0], r1.size[0], r1.size[1]);
  coder::internal::validator_check_size(r2, b__in);
  (&(&iobj_1)[0])[0].pl.set_size(1, b__in.size(1));
  loop_ub = b__in.size(1);
  for (int i{0}; i < loop_ub; i++) {
    (&(&iobj_1)[0])[0].pl[i] = b__in[i];
  }
  r.A = makepulsestruc(r.t_next, r.mode, r.P, r.SNR, r.yw, r.t_0, r.t_f, r.fp,
                       r.fstart, r.fend, r.det_dec, r.con_dec);
  (&(&iobj_1)[0])[0].clst.set_size(1, 1);
  (&(&iobj_1)[0])[0].clst[0] = r;
  (&(&iobj_1)[0])[0].cmsk.set_size(0, 0);
  (&(&iobj_1)[0])[0].cpki.set_size(0, 0);
  iobj_2.ps_pre = &(&(&iobj_1)[0])[0];
  // PULSESTATS Constructs an instance of this class
  //
  // INPUTS:
  //    tp      1x1     Duration of pulse (second)
  //    tip     1x1     Inter-pulse time (seconds)
  //    tipu    1x1     Inter-pulse time uncertainty (seconds)
  //    tipj    1x1     Inter-pulse time jitter (deviations from means)
  //    (seconds) fp      1x1     Pulses' center frequency (Hz) (if known)
  //    fstart  1x1     Lower frequency bound pulses' center frequency (Hz) (if
  //    known) fend    1x1     Upper frequency bound pulses' center frequency
  //    (Hz) (if known) tmplt   1xn     Pulse template. See properies for
  //                    definition. Usually set to [1 1] for
  //                    square pulse.
  //    pl      px1     Vector of pulse objects in waveform (if
  //                    known). If unknown enter a blank pulse made
  //                    from the contstructor "pulse";
  //  Note: Unknown inputs should be set to NaN.
  //
  // OUTPUTS:
  //    pulsestats object
  //
  //             %%
  // Tell coder these are variable size.
  // Now actually assign them
  r.A = makepulsestruc(r.t_next, r.mode, r.P, r.SNR, r.yw, r.t_0, r.t_f, r.fp,
                       r.fstart, r.fend, r.det_dec, r.con_dec);
  r1.size[0] = 1;
  r1.size[1] = 1;
  r1.data[0] = r;
  r3.set(&r1.data[0], r1.size[0], r1.size[1]);
  coder::internal::validator_check_size(r3, b__in);
  (&(&iobj_1)[0])[1].pl.set_size(1, b__in.size(1));
  loop_ub = b__in.size(1);
  for (int i{0}; i < loop_ub; i++) {
    (&(&iobj_1)[0])[1].pl[i] = b__in[i];
  }
  r.A = makepulsestruc(r.t_next, r.mode, r.P, r.SNR, r.yw, r.t_0, r.t_f, r.fp,
                       r.fstart, r.fend, r.det_dec, r.con_dec);
  (&(&iobj_1)[0])[1].clst.set_size(1, 1);
  (&(&iobj_1)[0])[1].clst[0] = r;
  (&(&iobj_1)[0])[1].cmsk.set_size(0, 0);
  (&(&iobj_1)[0])[1].cpki.set_size(0, 0);
  iobj_2.ps_pos = &(&(&iobj_1)[0])[1];
  b__in.set_size(1, wfmIn.ps_pre->pl.size(1));
  loop_ub = wfmIn.ps_pre->pl.size(0) * wfmIn.ps_pre->pl.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    b__in[i] = wfmIn.ps_pre->pl[i];
  }
  b_wfmIn.set_size(wfmIn.ps_pre->clst.size(0), wfmIn.ps_pre->clst.size(1));
  loop_ub = wfmIn.ps_pre->clst.size(0) * wfmIn.ps_pre->clst.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    b_wfmIn[i] = wfmIn.ps_pre->clst[i];
  }
  c_wfmIn.set_size(wfmIn.ps_pre->cmsk.size(0), wfmIn.ps_pre->cmsk.size(1));
  loop_ub = wfmIn.ps_pre->cmsk.size(0) * wfmIn.ps_pre->cmsk.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    c_wfmIn[i] = wfmIn.ps_pre->cmsk[i];
  }
  d_wfmIn.set_size(wfmIn.ps_pre->cpki.size(0), wfmIn.ps_pre->cpki.size(1));
  loop_ub = wfmIn.ps_pre->cpki.size(0) * wfmIn.ps_pre->cpki.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    d_wfmIn[i] = wfmIn.ps_pre->cpki[i];
  }
  e_wfmIn[0] = wfmIn.ps_pre->tmplt[0];
  e_wfmIn[1] = wfmIn.ps_pre->tmplt[1];
  val = (&iobj_1)[2].b_init(wfmIn.ps_pre->t_p, wfmIn.ps_pre->t_ip,
                            wfmIn.ps_pre->t_ipu, wfmIn.ps_pre->t_ipj,
                            wfmIn.ps_pre->fp, wfmIn.ps_pre->fstart,
                            wfmIn.ps_pre->fend, e_wfmIn, wfmIn.ps_pre->mode,
                            b__in, b_wfmIn, c_wfmIn, d_wfmIn);
  iobj_2.ps_pre = val;
  b__in.set_size(1, wfmIn.ps_pos->pl.size(1));
  loop_ub = wfmIn.ps_pos->pl.size(0) * wfmIn.ps_pos->pl.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    b__in[i] = wfmIn.ps_pos->pl[i];
  }
  b_wfmIn.set_size(wfmIn.ps_pos->clst.size(0), wfmIn.ps_pos->clst.size(1));
  loop_ub = wfmIn.ps_pos->clst.size(0) * wfmIn.ps_pos->clst.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    b_wfmIn[i] = wfmIn.ps_pos->clst[i];
  }
  c_wfmIn.set_size(wfmIn.ps_pos->cmsk.size(0), wfmIn.ps_pos->cmsk.size(1));
  loop_ub = wfmIn.ps_pos->cmsk.size(0) * wfmIn.ps_pos->cmsk.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    c_wfmIn[i] = wfmIn.ps_pos->cmsk[i];
  }
  d_wfmIn.set_size(wfmIn.ps_pos->cpki.size(0), wfmIn.ps_pos->cpki.size(1));
  loop_ub = wfmIn.ps_pos->cpki.size(0) * wfmIn.ps_pos->cpki.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    d_wfmIn[i] = wfmIn.ps_pos->cpki[i];
  }
  e_wfmIn[0] = wfmIn.ps_pos->tmplt[0];
  e_wfmIn[1] = wfmIn.ps_pos->tmplt[1];
  val = (&iobj_1)[3].b_init(wfmIn.ps_pos->t_p, wfmIn.ps_pos->t_ip,
                            wfmIn.ps_pos->t_ipu, wfmIn.ps_pos->t_ipj,
                            wfmIn.ps_pos->fp, wfmIn.ps_pos->fstart,
                            wfmIn.ps_pos->fend, e_wfmIn, wfmIn.ps_pos->mode,
                            b__in, b_wfmIn, c_wfmIn, d_wfmIn);
  iobj_2.ps_pos = val;
  _in = wfmIn.thresh;
  iobj_2.thresh = _in;
  obj = iobj_2.stft;
  c__in.set_size(wfmIn.stft->S.size(0), wfmIn.stft->S.size(1));
  loop_ub = wfmIn.stft->S.size(0) * wfmIn.stft->S.size(1);
  for (int i{0}; i < loop_ub; i++) {
    c__in[i] = wfmIn.stft->S[i];
  }
  obj->S.set_size(c__in.size(0), c__in.size(1));
  loop_ub = c__in.size(0) * c__in.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->S[i] = c__in[i];
  }
  obj = iobj_2.stft;
  d__in.set_size(wfmIn.stft->f.size(0));
  loop_ub = wfmIn.stft->f.size(0);
  for (int i{0}; i < loop_ub; i++) {
    d__in[i] = wfmIn.stft->f[i];
  }
  obj->f.set_size(d__in.size(0));
  loop_ub = d__in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    obj->f[i] = d__in[i];
  }
  obj = iobj_2.stft;
  d__in.set_size(wfmIn.stft->t.size(0));
  loop_ub = wfmIn.stft->t.size(0);
  for (int i{0}; i < loop_ub; i++) {
    d__in[i] = wfmIn.stft->t[i];
  }
  obj->t.set_size(d__in.size(0));
  loop_ub = d__in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    obj->t[i] = d__in[i];
  }
  obj = iobj_2.stft;
  d__in.set_size(wfmIn.stft->psd.size(0));
  loop_ub = wfmIn.stft->psd.size(0);
  for (int i{0}; i < loop_ub; i++) {
    d__in[i] = wfmIn.stft->psd[i];
  }
  obj->psd.set_size(d__in.size(0));
  loop_ub = d__in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    obj->psd[i] = d__in[i];
  }
  obj = iobj_2.stft;
  b_val = wfmIn.stft->dt;
  obj->dt = b_val;
  obj = iobj_2.stft;
  b_val = wfmIn.stft->T;
  obj->T = b_val;
  obj = iobj_2.stft;
  d__in.set_size(wfmIn.stft->wind.size(0));
  loop_ub = wfmIn.stft->wind.size(0);
  for (int i{0}; i < loop_ub; i++) {
    d__in[i] = wfmIn.stft->wind[i];
  }
  obj->wind.set_size(d__in.size(0));
  loop_ub = d__in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    obj->wind[i] = d__in[i];
  }
  b_val = wfmIn.K;
  iobj_2.K = b_val;
  e__in.set_size(1, wfmIn.x.size(1));
  loop_ub = wfmIn.x.size(1);
  for (int i{0}; i < loop_ub; i++) {
    e__in[i] = wfmIn.x[i];
  }
  iobj_2.x.set_size(1, e__in.size(1));
  loop_ub = e__in.size(1);
  for (int i{0}; i < loop_ub; i++) {
    iobj_2.x[i] = e__in[i];
  }
  double _in_idx_1;
  b_val = wfmIn.Fs;
  iobj_2.Fs = b_val;
  b_val = wfmIn.l;
  iobj_2.l = b_val;
  b_val = wfmIn.t_0;
  iobj_2.t_0 = b_val;
  b_val = wfmIn.t_f;
  iobj_2.t_0 = b_val;
  b_val = wfmIn.t_nextsegstart[0];
  _in_idx_1 = wfmIn.t_nextsegstart[1];
  iobj_2.t_nextsegstart[0] = b_val;
  iobj_2.t_nextsegstart[1] = _in_idx_1;
  b_val = wfmIn.OLF;
  iobj_2.OLF = b_val;
  c__in.set_size(wfmIn.W.size(0), wfmIn.W.size(1));
  loop_ub = wfmIn.W.size(0) * wfmIn.W.size(1);
  for (int i{0}; i < loop_ub; i++) {
    c__in[i] = wfmIn.W[i];
  }
  iobj_2.W.set_size(c__in.size(0), c__in.size(1));
  loop_ub = c__in.size(0) * c__in.size(1);
  for (int i{0}; i < loop_ub; i++) {
    iobj_2.W[i] = c__in[i];
  }
  d__in.set_size(wfmIn.Wf.size(0));
  loop_ub = wfmIn.Wf.size(0);
  for (int i{0}; i < loop_ub; i++) {
    d__in[i] = wfmIn.Wf[i];
  }
  iobj_2.Wf.set_size(d__in.size(0));
  loop_ub = d__in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_2.Wf[i] = d__in[i];
  }
  b_val = wfmIn.n_p;
  iobj_2.n_p = b_val;
  b_val = wfmIn.n_w;
  iobj_2.n_w = b_val;
  b_val = wfmIn.n_ol;
  iobj_2.n_ol = b_val;
  b_val = wfmIn.n_ws;
  iobj_2.n_ws = b_val;
  b_val = wfmIn.t_ws;
  iobj_2.t_ws = b_val;
  b_val = wfmIn.n_ip;
  iobj_2.n_ip = b_val;
  b_val = wfmIn.N;
  iobj_2.N = b_val;
  b_val = wfmIn.M;
  iobj_2.M = b_val;
  b_val = wfmIn.J;
  iobj_2.J = b_val;
  return wfmOut;
}

//
// File trailer for waveformcopy.cpp
//
// [EOF]
//
