//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: confirmpulses.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "confirmpulses.h"
#include "eml_int_forloop_overflow_check.h"
#include "horzcatStructList.h"
#include "pulsestats.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "waveform.h"
#include "coder_array.h"
#include <cmath>

// Function Declarations
static void b_ge(coder::array<boolean_T, 2U> &in1,
                 const coder::array<double, 2U> &in2,
                 const coder::array<double, 2U> &in3);

static void b_le(coder::array<boolean_T, 2U> &in1,
                 const coder::array<double, 2U> &in2,
                 const coder::array<double, 2U> &in3);

static void binary_expand_op_25(coder::array<boolean_T, 2U> &in1,
                                const coder::array<boolean_T, 2U> &in2,
                                int in3);

static void binary_expand_op_26(coder::array<boolean_T, 2U> &in1,
                                const coder::array<double, 2U> &in2,
                                const coder::array<double, 2U> &in3);

static void binary_expand_op_27(coder::array<boolean_T, 2U> &in1,
                                const coder::array<double, 2U> &in2,
                                const coder::array<double, 2U> &in3);

static void binary_expand_op_28(coder::array<double, 2U> &in1, double in2,
                                const coder::array<double, 2U> &in3);

static void binary_expand_op_29(coder::array<double, 2U> &in1, double in2,
                                const coder::array<double, 2U> &in3);

static void d_and(coder::array<boolean_T, 2U> &in1,
                  const coder::array<boolean_T, 2U> &in2);

// Function Definitions
//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void b_ge(coder::array<boolean_T, 2U> &in1,
                 const coder::array<double, 2U> &in2,
                 const coder::array<double, 2U> &in3)
{
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  in1.set_size(1, in1.size(1));
  if (in3.size(1) == 1) {
    loop_ub = in2.size(1);
  } else {
    loop_ub = in3.size(1);
  }
  in1.set_size(in1.size(0), loop_ub);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_1 = (in3.size(1) != 1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = (in2[i * stride_0_1] >= in3[i * stride_1_1]);
  }
}

//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void b_le(coder::array<boolean_T, 2U> &in1,
                 const coder::array<double, 2U> &in2,
                 const coder::array<double, 2U> &in3)
{
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  in1.set_size(1, in1.size(1));
  if (in3.size(1) == 1) {
    loop_ub = in2.size(1);
  } else {
    loop_ub = in3.size(1);
  }
  in1.set_size(in1.size(0), loop_ub);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_1 = (in3.size(1) != 1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = (in2[i * stride_0_1] <= in3[i * stride_1_1]);
  }
}

//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<boolean_T, 2U> &in2
//                int in3
// Return Type  : void
//
static void binary_expand_op_25(coder::array<boolean_T, 2U> &in1,
                                const coder::array<boolean_T, 2U> &in2, int in3)
{
  coder::array<boolean_T, 2U> b_in2;
  int loop_ub;
  int stride_1_0;
  if (in1.size(0) == 1) {
    loop_ub = in3;
  } else {
    loop_ub = in1.size(0);
  }
  b_in2.set_size(loop_ub, 1);
  stride_1_0 = (in1.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    b_in2[i] = (in2[0] && in1[i * stride_1_0]);
  }
  in1.set_size(b_in2.size(0), 1);
  loop_ub = b_in2.size(0);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = b_in2[i];
  }
}

//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void binary_expand_op_26(coder::array<boolean_T, 2U> &in1,
                                const coder::array<double, 2U> &in2,
                                const coder::array<double, 2U> &in3)
{
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  in1.set_size(1, in1.size(1));
  if (in3.size(1) == 1) {
    loop_ub = in2.size(1);
  } else {
    loop_ub = in3.size(1);
  }
  in1.set_size(in1.size(0), loop_ub);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_1 = (in3.size(1) != 1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = (in2[i * stride_0_1] <= in3[i * stride_1_1] + 100.0);
  }
}

//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void binary_expand_op_27(coder::array<boolean_T, 2U> &in1,
                                const coder::array<double, 2U> &in2,
                                const coder::array<double, 2U> &in3)
{
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  in1.set_size(1, in1.size(1));
  if (in3.size(1) == 1) {
    loop_ub = in2.size(1);
  } else {
    loop_ub = in3.size(1);
  }
  in1.set_size(in1.size(0), loop_ub);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_1 = (in3.size(1) != 1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = (in2[i * stride_0_1] >= in3[i * stride_1_1] - 100.0);
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                double in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void binary_expand_op_28(coder::array<double, 2U> &in1, double in2,
                                const coder::array<double, 2U> &in3)
{
  coder::array<double, 2U> b_in2;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  if (in3.size(1) == 1) {
    loop_ub = in1.size(1);
  } else {
    loop_ub = in3.size(1);
  }
  b_in2.set_size(1, loop_ub);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_1 = (in3.size(1) != 1);
  for (int i{0}; i < loop_ub; i++) {
    b_in2[i] = (in2 + in1[i * stride_0_1]) + in3[i * stride_1_1];
  }
  in1.set_size(1, b_in2.size(1));
  loop_ub = b_in2.size(1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = b_in2[i];
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                double in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void binary_expand_op_29(coder::array<double, 2U> &in1, double in2,
                                const coder::array<double, 2U> &in3)
{
  coder::array<double, 2U> b_in2;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  if (in3.size(1) == 1) {
    loop_ub = in1.size(1);
  } else {
    loop_ub = in3.size(1);
  }
  b_in2.set_size(1, loop_ub);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_1 = (in3.size(1) != 1);
  for (int i{0}; i < loop_ub; i++) {
    b_in2[i] = (in2 + in1[i * stride_0_1]) - in3[i * stride_1_1];
  }
  in1.set_size(1, b_in2.size(1));
  loop_ub = b_in2.size(1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = b_in2[i];
  }
}

//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<boolean_T, 2U> &in2
// Return Type  : void
//
static void d_and(coder::array<boolean_T, 2U> &in1,
                  const coder::array<boolean_T, 2U> &in2)
{
  coder::array<boolean_T, 2U> b_in1;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  if (in2.size(1) == 1) {
    loop_ub = in1.size(1);
  } else {
    loop_ub = in2.size(1);
  }
  b_in1.set_size(1, loop_ub);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_1 = (in2.size(1) != 1);
  for (int i{0}; i < loop_ub; i++) {
    b_in1[i] = (in1[i * stride_0_1] && in2[i * stride_1_1]);
  }
  in1.set_size(1, b_in1.size(1));
  loop_ub = b_in1.size(1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = b_in1[i];
  }
}

//
// CONFIRMPULSES Returns a boolean vector that say if the pulses in the
// X.ps_pos pulse stats are where they should be in frequency and time based on
// the last pulse of the X.ps_pre and its pulse timing parameter.
//
// INPUTS:
//    X       1x1     waveform
// OUTPUTS
//    conflog n x 1   boolean vector of confirmation of the pulses in
//                    X.ps_pos
//
// --------------------------------------------------------------------------
//
//
// Arguments    : const waveform *X
//                coder::array<boolean_T, 2U> &confLog
// Return Type  : void
//
void confirmpulses(const waveform *X, coder::array<boolean_T, 2U> &confLog)
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      -1,              // iFirst
      -1,              // iLast
      18,              // lineNo
      20,              // colNo
      "X.ps_pre.pl",   // aName
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      0                                                  // checkKind
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      -1,              // iFirst
      -1,              // iLast
      24,              // lineNo
      24,              // colNo
      "X.ps_pos.pl",   // aName
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      0                                                  // checkKind
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      -1,              // iFirst
      -1,              // iLast
      69,              // lineNo
      27,              // colNo
      "indivConfLog",  // aName
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      0                                                  // checkKind
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      -1,              // iFirst
      -1,              // iLast
      94,              // lineNo
      26,              // colNo
      "X.ps_pre.pl",   // aName
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      0                                                  // checkKind
  };
  static rtBoundsCheckInfo eb_emlrtBCI{
      -1,              // iFirst
      -1,              // iLast
      99,              // lineNo
      36,              // colNo
      "X.ps_pos.pl",   // aName
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      0                                                  // checkKind
  };
  static rtDoubleCheckInfo ab_emlrtDCI{
      38,              // lineNo
      74,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      1                                                  // checkKind
  };
  static rtDoubleCheckInfo bb_emlrtDCI{
      39,              // lineNo
      74,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      1                                                  // checkKind
  };
  static rtDoubleCheckInfo s_emlrtDCI{
      27,              // lineNo
      80,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      4                                                  // checkKind
  };
  static rtDoubleCheckInfo t_emlrtDCI{
      27,              // lineNo
      80,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      1                                                  // checkKind
  };
  static rtDoubleCheckInfo u_emlrtDCI{
      28,              // lineNo
      80,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      1                                                  // checkKind
  };
  static rtDoubleCheckInfo v_emlrtDCI{
      34,              // lineNo
      78,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      4                                                  // checkKind
  };
  static rtDoubleCheckInfo w_emlrtDCI{
      34,              // lineNo
      78,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      1                                                  // checkKind
  };
  static rtDoubleCheckInfo x_emlrtDCI{
      35,              // lineNo
      78,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      1                                                  // checkKind
  };
  static rtDoubleCheckInfo y_emlrtDCI{
      38,              // lineNo
      74,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      4                                                  // checkKind
  };
  static rtEqualityCheckInfo g_emlrtECI{
      2,               // nDims
      27,              // lineNo
      38,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo h_emlrtECI{
      2,               // nDims
      28,              // lineNo
      38,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo i_emlrtECI{
      2,               // nDims
      48,              // lineNo
      15,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo j_emlrtECI{
      2,               // nDims
      50,              // lineNo
      15,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo k_emlrtECI{
      2,               // nDims
      54,              // lineNo
      14,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo l_emlrtECI{
      2,               // nDims
      55,              // lineNo
      14,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo m_emlrtECI{
      2,               // nDims
      67,              // lineNo
      16,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo n_emlrtECI{
      1,               // nDims
      103,             // lineNo
      11,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo o_emlrtECI{
      2,               // nDims
      34,              // lineNo
      38,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo p_emlrtECI{
      2,               // nDims
      35,              // lineNo
      38,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo q_emlrtECI{
      2,               // nDims
      38,              // lineNo
      34,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo r_emlrtECI{
      2,               // nDims
      39,              // lineNo
      34,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  coder::array<c_struct_T, 1U> b_X;
  coder::array<double, 2U> SNRall;
  coder::array<double, 2U> pulseendtimes_withuncert;
  coder::array<double, 2U> pulsestarttimes_withuncert;
  coder::array<double, 2U> r;
  coder::array<double, 2U> r1;
  coder::array<boolean_T, 2U> SNRnotNegInfLog;
  coder::array<boolean_T, 2U> freqInBand;
  coder::array<boolean_T, 2U> maxstartlog;
  coder::array<boolean_T, 2U> minstartlog;
  coder::array<boolean_T, 2U> r2;
  double b_tmp;
  double tip;
  double tipj;
  double tipu;
  double tref;
  int i;
  int loop_ub;
  int loop_ub_tmp;
  int numPulses;
  boolean_T SNRnotNegInfAll;
  i = X->ps_pre->pl.size(1);
  numPulses = X->ps_pre->pl.size(1);
  if ((numPulses < 1) || (numPulses > i)) {
    rtDynamicBoundsError(numPulses, 1, i, ab_emlrtBCI);
  }
  tref = X->ps_pre->pl[numPulses - 1].t_0;
  tip = X->ps_pre->t_ip;
  tipu = X->ps_pre->t_ipu;
  tipj = X->ps_pre->t_ipj;
  if (tref > X->t_0) {
    // First pulse in this segment exists in last segment as well because of
    // overlap
    i = X->ps_pos->pl.size(1);
    if (i < 1) {
      rtDynamicBoundsError(1, 1, i, bb_emlrtBCI);
    }
    b_tmp = X->ps_pos->pl[0].t_0 - tref;
    if (std::abs(b_tmp) < tipu + tipj) {
      double a;
      // X.ps_pos.pl(1).t_0 <= tref + (tip + tipu + tipj)
      // new first pulse is the same one as the last one in the last
      // segment
      b_tmp = X->K - 1.0;
      SNRnotNegInfAll = std::isnan(b_tmp);
      if (SNRnotNegInfAll) {
        pulsestarttimes_withuncert.set_size(1, 1);
        pulsestarttimes_withuncert[0] = rtNaN;
      } else if (b_tmp < 0.0) {
        pulsestarttimes_withuncert.set_size(pulsestarttimes_withuncert.size(0),
                                            0);
      } else {
        pulsestarttimes_withuncert.set_size(1, static_cast<int>(b_tmp) + 1);
        loop_ub = static_cast<int>(b_tmp);
        for (i = 0; i <= loop_ub; i++) {
          pulsestarttimes_withuncert[i] = i;
        }
      }
      a = tip - tipu;
      pulsestarttimes_withuncert.set_size(1,
                                          pulsestarttimes_withuncert.size(1));
      loop_ub_tmp = pulsestarttimes_withuncert.size(1) - 1;
      for (i = 0; i <= loop_ub_tmp; i++) {
        pulsestarttimes_withuncert[i] = a * pulsestarttimes_withuncert[i];
      }
      if (!(X->K >= 0.0)) {
        rtNonNegativeError(X->K, s_emlrtDCI);
      }
      i = static_cast<int>(std::floor(X->K));
      if (X->K != i) {
        rtIntegerError(X->K, t_emlrtDCI);
      }
      loop_ub = static_cast<int>(X->K);
      r.set_size(1, loop_ub);
      for (numPulses = 0; numPulses < loop_ub; numPulses++) {
        r[numPulses] = tipj;
      }
      if ((pulsestarttimes_withuncert.size(1) != r.size(1)) &&
          ((pulsestarttimes_withuncert.size(1) != 1) && (r.size(1) != 1))) {
        emlrtDimSizeImpxCheckR2021b(pulsestarttimes_withuncert.size(1),
                                    r.size(1), g_emlrtECI);
      }
      if (pulsestarttimes_withuncert.size(1) == r.size(1)) {
        pulsestarttimes_withuncert.set_size(1,
                                            pulsestarttimes_withuncert.size(1));
        for (numPulses = 0; numPulses <= loop_ub_tmp; numPulses++) {
          pulsestarttimes_withuncert[numPulses] =
              (tref + pulsestarttimes_withuncert[numPulses]) - r[numPulses];
        }
      } else {
        binary_expand_op_29(pulsestarttimes_withuncert, tref, r);
      }
      if (SNRnotNegInfAll) {
        pulseendtimes_withuncert.set_size(1, 1);
        pulseendtimes_withuncert[0] = rtNaN;
      } else if (b_tmp < 0.0) {
        pulseendtimes_withuncert.set_size(pulseendtimes_withuncert.size(0), 0);
      } else {
        pulseendtimes_withuncert.set_size(1, static_cast<int>(b_tmp) + 1);
        loop_ub_tmp = static_cast<int>(b_tmp);
        for (numPulses = 0; numPulses <= loop_ub_tmp; numPulses++) {
          pulseendtimes_withuncert[numPulses] = numPulses;
        }
      }
      a = tip + tipu;
      pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
      loop_ub_tmp = pulseendtimes_withuncert.size(1) - 1;
      for (numPulses = 0; numPulses <= loop_ub_tmp; numPulses++) {
        pulseendtimes_withuncert[numPulses] =
            a * pulseendtimes_withuncert[numPulses];
      }
      if (X->K != i) {
        rtIntegerError(X->K, u_emlrtDCI);
      }
      r.set_size(1, loop_ub);
      for (i = 0; i < loop_ub; i++) {
        r[i] = tipj;
      }
      if ((pulseendtimes_withuncert.size(1) != r.size(1)) &&
          ((pulseendtimes_withuncert.size(1) != 1) && (r.size(1) != 1))) {
        emlrtDimSizeImpxCheckR2021b(pulseendtimes_withuncert.size(1), r.size(1),
                                    h_emlrtECI);
      }
      if (pulseendtimes_withuncert.size(1) == r.size(1)) {
        pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
        for (i = 0; i <= loop_ub_tmp; i++) {
          pulseendtimes_withuncert[i] =
              (tref + pulseendtimes_withuncert[i]) + r[i];
        }
      } else {
        binary_expand_op_28(pulseendtimes_withuncert, tref, r);
      }
    } else {
      double a;
      // new first pulse isn't the same one as the last one in the last
      // segment because the detector detected the last K pulses in the
      // segment and not the first three. Remember that the segment can
      // contain K+1 pulses
      b_tmp = X->K;
      SNRnotNegInfAll = std::isnan(b_tmp);
      if (SNRnotNegInfAll) {
        pulsestarttimes_withuncert.set_size(1, 1);
        pulsestarttimes_withuncert[0] = rtNaN;
      } else if (b_tmp < 1.0) {
        pulsestarttimes_withuncert.set_size(pulsestarttimes_withuncert.size(0),
                                            0);
      } else {
        pulsestarttimes_withuncert.set_size(1,
                                            static_cast<int>(b_tmp - 1.0) + 1);
        loop_ub = static_cast<int>(b_tmp - 1.0);
        for (i = 0; i <= loop_ub; i++) {
          pulsestarttimes_withuncert[i] = static_cast<double>(i) + 1.0;
        }
      }
      a = tip - tipu;
      pulsestarttimes_withuncert.set_size(1,
                                          pulsestarttimes_withuncert.size(1));
      loop_ub_tmp = pulsestarttimes_withuncert.size(1) - 1;
      for (i = 0; i <= loop_ub_tmp; i++) {
        pulsestarttimes_withuncert[i] = a * pulsestarttimes_withuncert[i];
      }
      if (!(X->K >= 0.0)) {
        rtNonNegativeError(X->K, v_emlrtDCI);
      }
      i = static_cast<int>(std::floor(X->K));
      if (X->K != i) {
        rtIntegerError(X->K, w_emlrtDCI);
      }
      loop_ub = static_cast<int>(X->K);
      r.set_size(1, loop_ub);
      for (numPulses = 0; numPulses < loop_ub; numPulses++) {
        r[numPulses] = tipj;
      }
      if ((pulsestarttimes_withuncert.size(1) != r.size(1)) &&
          ((pulsestarttimes_withuncert.size(1) != 1) && (r.size(1) != 1))) {
        emlrtDimSizeImpxCheckR2021b(pulsestarttimes_withuncert.size(1),
                                    r.size(1), o_emlrtECI);
      }
      if (pulsestarttimes_withuncert.size(1) == r.size(1)) {
        pulsestarttimes_withuncert.set_size(1,
                                            pulsestarttimes_withuncert.size(1));
        for (numPulses = 0; numPulses <= loop_ub_tmp; numPulses++) {
          pulsestarttimes_withuncert[numPulses] =
              (tref + pulsestarttimes_withuncert[numPulses]) - r[numPulses];
        }
      } else {
        binary_expand_op_29(pulsestarttimes_withuncert, tref, r);
      }
      if (SNRnotNegInfAll) {
        pulseendtimes_withuncert.set_size(1, 1);
        pulseendtimes_withuncert[0] = rtNaN;
      } else if (b_tmp < 1.0) {
        pulseendtimes_withuncert.set_size(pulseendtimes_withuncert.size(0), 0);
      } else {
        pulseendtimes_withuncert.set_size(1, static_cast<int>(b_tmp - 1.0) + 1);
        loop_ub_tmp = static_cast<int>(b_tmp - 1.0);
        for (numPulses = 0; numPulses <= loop_ub_tmp; numPulses++) {
          pulseendtimes_withuncert[numPulses] =
              static_cast<double>(numPulses) + 1.0;
        }
      }
      a = tip + tipu;
      pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
      loop_ub_tmp = pulseendtimes_withuncert.size(1) - 1;
      for (numPulses = 0; numPulses <= loop_ub_tmp; numPulses++) {
        pulseendtimes_withuncert[numPulses] =
            a * pulseendtimes_withuncert[numPulses];
      }
      if (X->K != i) {
        rtIntegerError(X->K, x_emlrtDCI);
      }
      r.set_size(1, loop_ub);
      for (i = 0; i < loop_ub; i++) {
        r[i] = tipj;
      }
      if ((pulseendtimes_withuncert.size(1) != r.size(1)) &&
          ((pulseendtimes_withuncert.size(1) != 1) && (r.size(1) != 1))) {
        emlrtDimSizeImpxCheckR2021b(pulseendtimes_withuncert.size(1), r.size(1),
                                    p_emlrtECI);
      }
      if (pulseendtimes_withuncert.size(1) == r.size(1)) {
        pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
        for (i = 0; i <= loop_ub_tmp; i++) {
          pulseendtimes_withuncert[i] =
              (tref + pulseendtimes_withuncert[i]) + r[i];
        }
      } else {
        binary_expand_op_28(pulseendtimes_withuncert, tref, r);
      }
    }
  } else {
    double a;
    // First pulse in this segment does not exists in last segment as well
    // because of overlap
    b_tmp = X->K;
    SNRnotNegInfAll = std::isnan(b_tmp);
    if (SNRnotNegInfAll) {
      pulsestarttimes_withuncert.set_size(1, 1);
      pulsestarttimes_withuncert[0] = rtNaN;
    } else if (b_tmp < 1.0) {
      pulsestarttimes_withuncert.set_size(pulsestarttimes_withuncert.size(0),
                                          0);
    } else {
      pulsestarttimes_withuncert.set_size(1, static_cast<int>(b_tmp - 1.0) + 1);
      loop_ub = static_cast<int>(b_tmp - 1.0);
      for (i = 0; i <= loop_ub; i++) {
        pulsestarttimes_withuncert[i] = static_cast<double>(i) + 1.0;
      }
    }
    a = tip - tipu;
    pulsestarttimes_withuncert.set_size(1, pulsestarttimes_withuncert.size(1));
    loop_ub_tmp = pulsestarttimes_withuncert.size(1) - 1;
    for (i = 0; i <= loop_ub_tmp; i++) {
      pulsestarttimes_withuncert[i] = a * pulsestarttimes_withuncert[i];
    }
    if (!(X->K >= 0.0)) {
      rtNonNegativeError(X->K, y_emlrtDCI);
    }
    i = static_cast<int>(std::floor(X->K));
    if (X->K != i) {
      rtIntegerError(X->K, ab_emlrtDCI);
    }
    loop_ub = static_cast<int>(X->K);
    r.set_size(1, loop_ub);
    for (numPulses = 0; numPulses < loop_ub; numPulses++) {
      r[numPulses] = tipj;
    }
    if ((pulsestarttimes_withuncert.size(1) != r.size(1)) &&
        ((pulsestarttimes_withuncert.size(1) != 1) && (r.size(1) != 1))) {
      emlrtDimSizeImpxCheckR2021b(pulsestarttimes_withuncert.size(1), r.size(1),
                                  q_emlrtECI);
    }
    if (pulsestarttimes_withuncert.size(1) == r.size(1)) {
      pulsestarttimes_withuncert.set_size(1,
                                          pulsestarttimes_withuncert.size(1));
      for (numPulses = 0; numPulses <= loop_ub_tmp; numPulses++) {
        pulsestarttimes_withuncert[numPulses] =
            (tref + pulsestarttimes_withuncert[numPulses]) - r[numPulses];
      }
    } else {
      binary_expand_op_29(pulsestarttimes_withuncert, tref, r);
    }
    if (SNRnotNegInfAll) {
      pulseendtimes_withuncert.set_size(1, 1);
      pulseendtimes_withuncert[0] = rtNaN;
    } else if (b_tmp < 1.0) {
      pulseendtimes_withuncert.set_size(pulseendtimes_withuncert.size(0), 0);
    } else {
      pulseendtimes_withuncert.set_size(1, static_cast<int>(b_tmp - 1.0) + 1);
      loop_ub_tmp = static_cast<int>(b_tmp - 1.0);
      for (numPulses = 0; numPulses <= loop_ub_tmp; numPulses++) {
        pulseendtimes_withuncert[numPulses] =
            static_cast<double>(numPulses) + 1.0;
      }
    }
    a = tip + tipu;
    pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
    loop_ub_tmp = pulseendtimes_withuncert.size(1) - 1;
    for (numPulses = 0; numPulses <= loop_ub_tmp; numPulses++) {
      pulseendtimes_withuncert[numPulses] =
          a * pulseendtimes_withuncert[numPulses];
    }
    if (X->K != i) {
      rtIntegerError(X->K, bb_emlrtDCI);
    }
    r.set_size(1, loop_ub);
    for (i = 0; i < loop_ub; i++) {
      r[i] = tipj;
    }
    if ((pulseendtimes_withuncert.size(1) != r.size(1)) &&
        ((pulseendtimes_withuncert.size(1) != 1) && (r.size(1) != 1))) {
      emlrtDimSizeImpxCheckR2021b(pulseendtimes_withuncert.size(1), r.size(1),
                                  r_emlrtECI);
    }
    if (pulseendtimes_withuncert.size(1) == r.size(1)) {
      pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
      for (i = 0; i <= loop_ub_tmp; i++) {
        pulseendtimes_withuncert[i] =
            (tref + pulseendtimes_withuncert[i]) + r[i];
      }
    } else {
      binary_expand_op_28(pulseendtimes_withuncert, tref, r);
    }
  }
  // Debugging plots
  //  figure;xline(pulsestarttimes_withuncert,'--')
  //  hold on;xline(pulseendtimes_withuncert,'--')
  //  plot([X.ps_pos.pl(:).t_0],zeros(size([X.ps_pos.pl(:).t_0])),'ob')
  // Check if pulses started after expected minimum start times
  loop_ub_tmp = X->ps_pos->pl.size(1);
  b_X = X->ps_pos->pl.reshape(loop_ub_tmp);
  coder::internal::b_horzcatStructList(b_X, r);
  if ((r.size(1) != pulsestarttimes_withuncert.size(1)) &&
      ((r.size(1) != 1) && (pulsestarttimes_withuncert.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(r.size(1), pulsestarttimes_withuncert.size(1),
                                i_emlrtECI);
  }
  if (r.size(1) == pulsestarttimes_withuncert.size(1)) {
    minstartlog.set_size(1, r.size(1));
    loop_ub = r.size(1);
    for (i = 0; i < loop_ub; i++) {
      minstartlog[i] = (r[i] >= pulsestarttimes_withuncert[i]);
    }
  } else {
    b_ge(minstartlog, r, pulsestarttimes_withuncert);
  }
  // Check if pulses started before expected maximum start times
  loop_ub_tmp = X->ps_pos->pl.size(1);
  b_X = X->ps_pos->pl.reshape(loop_ub_tmp);
  coder::internal::b_horzcatStructList(b_X, r);
  if ((r.size(1) != pulseendtimes_withuncert.size(1)) &&
      ((r.size(1) != 1) && (pulseendtimes_withuncert.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(r.size(1), pulseendtimes_withuncert.size(1),
                                j_emlrtECI);
  }
  if (r.size(1) == pulseendtimes_withuncert.size(1)) {
    maxstartlog.set_size(1, r.size(1));
    loop_ub = r.size(1);
    for (i = 0; i < loop_ub; i++) {
      maxstartlog[i] = (r[i] <= pulseendtimes_withuncert[i]);
    }
  } else {
    b_le(maxstartlog, r, pulseendtimes_withuncert);
  }
  // Frequency check. Within +/- 100 Hz of previously
  // detected pulses?
  coder::internal::c_horzcatStructList(X->ps_pos->pl, r);
  coder::internal::c_horzcatStructList(X->ps_pre->pl,
                                       pulsestarttimes_withuncert);
  if ((r.size(1) != pulsestarttimes_withuncert.size(1)) &&
      ((r.size(1) != 1) && (pulsestarttimes_withuncert.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(r.size(1), pulsestarttimes_withuncert.size(1),
                                k_emlrtECI);
  }
  coder::internal::c_horzcatStructList(X->ps_pos->pl, pulseendtimes_withuncert);
  coder::internal::c_horzcatStructList(X->ps_pre->pl, r1);
  if ((pulseendtimes_withuncert.size(1) != r1.size(1)) &&
      ((pulseendtimes_withuncert.size(1) != 1) && (r1.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(pulseendtimes_withuncert.size(1), r1.size(1),
                                l_emlrtECI);
  }
  if (r.size(1) == pulsestarttimes_withuncert.size(1)) {
    freqInBand.set_size(1, r.size(1));
    loop_ub = r.size(1);
    for (i = 0; i < loop_ub; i++) {
      freqInBand[i] = (r[i] >= pulsestarttimes_withuncert[i] - 100.0);
    }
  } else {
    binary_expand_op_27(freqInBand, r, pulsestarttimes_withuncert);
  }
  if (pulseendtimes_withuncert.size(1) == r1.size(1)) {
    r2.set_size(1, pulseendtimes_withuncert.size(1));
    loop_ub = pulseendtimes_withuncert.size(1);
    for (i = 0; i < loop_ub; i++) {
      r2[i] = (pulseendtimes_withuncert[i] <= r1[i] + 100.0);
    }
  } else {
    binary_expand_op_26(r2, pulseendtimes_withuncert, r1);
  }
  if ((freqInBand.size(1) != r2.size(1)) &&
      ((freqInBand.size(1) != 1) && (r2.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(freqInBand.size(1), r2.size(1), k_emlrtECI);
  }
  if (freqInBand.size(1) == r2.size(1)) {
    loop_ub = freqInBand.size(1) - 1;
    freqInBand.set_size(1, freqInBand.size(1));
    for (i = 0; i <= loop_ub; i++) {
      freqInBand[i] = (freqInBand[i] && r2[i]);
    }
  } else {
    d_and(freqInBand, r2);
  }
  // confLog = maxstartlog & minstartlog & freqInBand;
  // 2023-09-14
  // The method above has increasing uncertainty bounds for the Kth pulse that
  // allows for the entire group to be shifted in time and only the last K
  // pulse gets confirmed. We really need to only check that the first pulse in
  // the group is in the correct position. If it is, then the others are
  // confirmed by default.
  numPulses = X->ps_pos->pl.size(1);
  if ((maxstartlog.size(1) != minstartlog.size(1)) &&
      ((maxstartlog.size(1) != 1) && (minstartlog.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(maxstartlog.size(1), minstartlog.size(1),
                                m_emlrtECI);
  }
  if (maxstartlog.size(1) == minstartlog.size(1)) {
    loop_ub = maxstartlog.size(1) - 1;
    maxstartlog.set_size(1, maxstartlog.size(1));
    for (i = 0; i <= loop_ub; i++) {
      maxstartlog[i] = (maxstartlog[i] && minstartlog[i]);
    }
  } else {
    d_and(maxstartlog, minstartlog);
  }
  if ((maxstartlog.size(1) != freqInBand.size(1)) &&
      ((maxstartlog.size(1) != 1) && (freqInBand.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(maxstartlog.size(1), freqInBand.size(1),
                                m_emlrtECI);
  }
  if (maxstartlog.size(1) == freqInBand.size(1)) {
    loop_ub = maxstartlog.size(1) - 1;
    maxstartlog.set_size(1, maxstartlog.size(1));
    for (i = 0; i <= loop_ub; i++) {
      maxstartlog[i] = (maxstartlog[i] && freqInBand[i]);
    }
  } else {
    d_and(maxstartlog, freqInBand);
  }
  if (maxstartlog.size(1) < 1) {
    rtDynamicBoundsError(1, 1, maxstartlog.size(1), cb_emlrtBCI);
  }
  // 2023-09-21
  // If an individual pulse of noise energy is sufficient to be above exceed
  // the threshold, even if all the other K-1 pulses in its groups are just
  // noise, and the noise pulses are repeated in a way that a confirmation in
  // time might occur, the SNR of the adjacent pulses in the group will be
  // very low. Here we check to make sure all the pulses have SNRs within 7dB
  // of the max SNR in the pulse group. If they don't we reject the pulses. If
  // we are dealing with a K = 1 case, we check against the previous pulse.
  confLog.set_size(numPulses, 1);
  for (i = 0; i < numPulses; i++) {
    confLog[i] = false;
  }
  if (numPulses > 1) {
    boolean_T exitg1;
    loop_ub_tmp = X->ps_pos->pl.size(1);
    b_X = X->ps_pos->pl.reshape(loop_ub_tmp);
    coder::internal::c_horzcatStructList(b_X, r);
    loop_ub = r.size(1);
    loop_ub_tmp = X->ps_pos->pl.size(1);
    b_X = X->ps_pos->pl.reshape(loop_ub_tmp);
    coder::internal::c_horzcatStructList(b_X, pulsestarttimes_withuncert);
    SNRall.set_size(r.size(1), 1);
    for (i = 0; i < loop_ub; i++) {
      SNRall[i] = pulsestarttimes_withuncert[i];
    }
    // SNRmax     = max(SNRall,[],'all');
    // SNRsimilar = SNRall >= SNRmax - abs(SNRmax/2);%use -abs() because SNRmax
    // could be negative. Can't just mult by 0.5 SNRsimilar = SNRall >= SNRmax -
    // 7;%use a fixed distance of 7 dB (5x)
    SNRnotNegInfLog.set_size(SNRall.size(0), 1);
    loop_ub = SNRall.size(0);
    for (i = 0; i < loop_ub; i++) {
      SNRnotNegInfLog[i] = (SNRall[i] != rtMinusInf);
    }
    SNRnotNegInfAll = true;
    if (SNRnotNegInfLog.size(0) > 2147483646) {
      coder::check_forloop_overflow_error();
    }
    loop_ub_tmp = 1;
    exitg1 = false;
    while ((!exitg1) && (loop_ub_tmp <= SNRnotNegInfLog.size(0))) {
      if (!SNRnotNegInfLog[loop_ub_tmp - 1]) {
        SNRnotNegInfAll = false;
        exitg1 = true;
      } else {
        loop_ub_tmp++;
      }
    }
    loop_ub_tmp = SNRall.size(0);
    confLog.set_size(SNRall.size(0), 1);
    for (i = 0; i < loop_ub_tmp; i++) {
      confLog[i] = SNRnotNegInfAll;
    }
  } else if (numPulses == 1) {
    // If K = 1 and we are confirming pulses, we should always have a pulse
    // in the previous pulse list. Just in case, we check here that there is
    // pulse in the previous segment.
    i = X->ps_pre->pl.size(1);
    if (i < 1) {
      rtDynamicBoundsError(1, 1, i, db_emlrtBCI);
    }
    b_tmp = X->ps_pre->pl[0].fp;
    if (std::isnan(b_tmp)) {
      confLog.set_size(1, 1);
      confLog[0] = false;
    } else {
      //  SNRprevious = X.ps_pre.pl(1).SNR;
      //  SNRsimilar  = X.ps_pos.pl(1).SNR >= SNRprevious - 7;
      i = X->ps_pos->pl.size(1);
      if (i < 1) {
        rtDynamicBoundsError(1, 1, i, eb_emlrtBCI);
      }
      confLog.set_size(1, 1);
      confLog[0] = (X->ps_pos->pl[0].SNR != rtMinusInf);
    }
  }
  if ((numPulses != confLog.size(0)) &&
      ((numPulses != 1) && (confLog.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(numPulses, confLog.size(0), n_emlrtECI);
  }
  if (numPulses == confLog.size(0)) {
    loop_ub = numPulses - 1;
    confLog.set_size(numPulses, 1);
    for (i = 0; i <= loop_ub; i++) {
      confLog[i] = (maxstartlog[0] && confLog[i]);
    }
  } else {
    binary_expand_op_25(confLog, maxstartlog, numPulses);
  }
}

//
// File trailer for confirmpulses.cpp
//
// [EOF]
//
