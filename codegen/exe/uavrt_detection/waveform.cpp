//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: waveform.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "waveform.h"
#include "FFTImplementationCallback.h"
#include "abs.h"
#include "all.h"
#include "allOrAny.h"
#include "assembleWq.h"
#include "assertCompatibleDims.h"
#include "assertValidSizeArg.h"
#include "blockedSummation.h"
#include "buildtimecorrelatormatrix.h"
#include "circshift.h"
#include "combineVectorElements.h"
#include "confirmpulses.h"
#include "eml_int_forloop_overflow_check.h"
#include "fftshift.h"
#include "find.h"
#include "function_handle.h"
#include "horzcatStructList.h"
#include "ifWhileCond.h"
#include "imresize.h"
#include "incohsumtoeplitz.h"
#include "indexShapeCheck.h"
#include "interp1.h"
#include "linspace.h"
#include "log10.h"
#include "makepulsestruc.h"
#include "mean.h"
#include "minOrMax.h"
#include "norm.h"
#include "pulsestats.h"
#include "repetitionrejector.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "sparse1.h"
#include "sqrt.h"
#include "stft.h"
#include "strcmp.h"
#include "sub2ind.h"
#include "sum.h"
#include "threshold.h"
#include "toc.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "unaryMinOrMax.h"
#include "vecfind.h"
#include "weightingmatrix.h"
#include "wfmstft.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo w_emlrtRTEI{ 18,// lineNo
  5,                                   // colNo
  "check_order",                       // fName
  "/Applications/MATLAB_R2023b.app/toolbox/signal/eml/private/check_order.m"// pName
};

static rtRunTimeErrorInfo x_emlrtRTEI{ 22,// lineNo
  23,                                  // colNo
  "check_order",                       // fName
  "/Applications/MATLAB_R2023b.app/toolbox/signal/eml/private/check_order.m"// pName
};

// Function Declarations
static void b_and(coder::array<boolean_T, 1U> &in1, const coder::array<boolean_T,
                  1U> &in2);
static void b_or(coder::array<boolean_T, 1U> &in1, const coder::array<boolean_T,
                 1U> &in2);
static void binary_expand_op_1(waveform *in1, const coder::array<double, 2U>
  &in2, const coder::array<double, 2U> &in3);
static void binary_expand_op_13(coder::array<boolean_T, 1U> &in1, const coder::
  array<boolean_T, 1U> &in2, const coder::array<boolean_T, 1U> &in3);
static void binary_expand_op_14(coder::array<boolean_T, 1U> &in1, const coder::
  array<boolean_T, 1U> &in2, const coder::array<boolean_T, 1U> &in3);
static void binary_expand_op_15(coder::array<boolean_T, 1U> &in1, const coder::
  array<double, 1U> &in2, int in3, const coder::array<double, 1U> &in4);
static void binary_expand_op_17(coder::array<double, 2U> &in1, const waveform
  *in2);
static void binary_expand_op_18(coder::array<double, 2U> &in1, const coder::
  array<double, 2U> &in2, const coder::array<double, 2U> &in3, int in4, int in5);
static void binary_expand_op_20(coder::array<boolean_T, 1U> &in1, const coder::
  array<boolean_T, 2U> &in2, const coder::array<boolean_T, 2U> &in3);
static void binary_expand_op_22(coder::array<double, 1U> &in1, const coder::
  array<boolean_T, 1U> &in2, const coder::array<boolean_T, 1U> &in3);
static void binary_expand_op_24(coder::array<boolean_T, 2U> &in1, const coder::
  array<double, 2U> &in2, const coder::array<double, 1U> &in3, const waveform
  *in4, const coder::array<double, 2U> &in5);
static void binary_expand_op_4(coder::array<double, 1U> &in1, const coder::array<
  boolean_T, 1U> &in2);
static void binary_expand_op_5(coder::array<boolean_T, 1U> &in1, const coder::
  array<double, 1U> &in2, const waveform *in3);
static void binary_expand_op_7(coder::array<double, 1U> &in1, const coder::array<
  double, 1U> &in2, const coder::array<boolean_T, 1U> &in3);
static void c_and(coder::array<boolean_T, 1U> &in1, const coder::array<boolean_T,
                  1U> &in2, const coder::array<boolean_T, 1U> &in3);
static void c_plus(coder::array<double, 2U> &in1, const coder::array<double, 2U>
                   &in2);
static void g_rtErrorWithMessageID(const char *r, const char *aFcnName, int
  aLineNum);
static void minus(coder::array<double, 2U> &in1, const coder::array<double, 2U>
                  &in2);
static void rdivide(coder::array<double, 2U> &in1, const coder::array<double, 2U>
                    &in2);
static void s_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// FINDPULSE Looks for pulses in the waveform based on its pulse
// statistics object
//
// This method implemets the incoherent summation algorithm for
// the waveform. The number of pulses summed (blocks considere)
// is defined based on the length of obj.x and its priori
// pulsestats object. When the waveform object is created, the
// length of data (x property) included should be defined to be
// long enough so that it is assure to contain no fewer than K
// pulses. This method doesn't know K, but will create as many
// blocks as it can based on the priori information.
//
// Note: The algorithm used for pulse peak energy detection
// requires that the center frequency of the pulse not be at the
// edges of the frequency bins in Wf. There needs to be rolloff
// in signal power above and below the pulse center frequency.
// Pulses at or just above/below the upper/lower limits of Wf may
// exceeed the threshold for detection, but not get recorded in
// the pl_out because the peeling algorithm can't catch them. If
// this happens, the frequencies used in the priori to describe
// the bounds of the pulse frequencies should be adjusted or
// widened to ensure the pulse's spectral power has rolloff above
// and below the center frequency and that this rolloff is within
// the bounds of the Wf input.
//
//
// INPUTS:
//     obj            Waveform object
//     W              spectral weighting matrix
//     Wf             frequencies list from baseband of
//                    corresponding to each row of W
//     time_searchtype     'naive' or 'informed'
//     freq_searchtype     'naive' or 'informed'
//     excluded_freq_bands_in   nx2    matrix of bands of
//                                  frequencies to exclude in
//                                  the search. This is useful if
//                                  there has already been a tag
//                                  found and you want to exclude
//                                  that band when looking for
//                                  other frequencies. The lower
//                                  frequecies of the band should
//                                  be in the first column and
//                                  the upper should be in the
//                                  second. Leave empty [] if no
//                                  exclusion zones are
//                                  necessary. These frequencies
//                                  are used regardless of the
//                                  freq_searchtype setting.
// OUPUTS:
//  pl_out      A matrix of all potential pulses. This will
//                have as many rows as Wf elements and as many
//                rows as blocks that were possible given the
//                length of the data in obj. The number of pulses
//                to be searched for would be defined at the
//                time of the creation of obj and used to define
//                the length of its data.
//
//    indiv_msk   A logical matrix who's columns identify the
//                peaks and sideband locations in the spectrum of
//                each peak. The ith column of indiv_msk
//                identifies the spectral location of the ith
//                most powerful pulse group identified.
//    peak_ind    A vector of the frequency indicies (of Wf)
//                where the power of the pulses were found.
//                These are the row indicies of pl_out where the
//                peaks exist.
//                These are the center frequency of the pulse
//                where the most energy was detected. The
//                sidebands of the ith peak listed in peak_ind is
//                identified in the ith column of indiv_msk
//
//             %%
//
// Arguments    : const char time_searchtype_data[]
//                const int time_searchtype_size[2]
//                const char freq_searchtype_data[]
//                const int freq_searchtype_size[2]
//                const coder::array<double, 2U> &excluded_freq_bands_in
//                coder::array<c_struct_T, 2U> &pl_out
//                coder::array<boolean_T, 2U> &indiv_msk
//                coder::array<double, 1U> &peak_ind
// Return Type  : void
//
void waveform::findpulse(const char time_searchtype_data[], const int
  time_searchtype_size[2], const char freq_searchtype_data[], const int
  freq_searchtype_size[2], const coder::array<double, 2U>
  &excluded_freq_bands_in, coder::array<c_struct_T, 2U> &pl_out, coder::array<
  boolean_T, 2U> &indiv_msk, coder::array<double, 1U> &peak_ind) const
{
  static rtBoundsCheckInfo ab_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    660,                               // lineNo
    29,                                // colNo
    "timeSearchRange",                 // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ac_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1134,                              // lineNo
    40,                                // colNo
    "msk",                             // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ad_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1160,                              // lineNo
    40,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ae_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1209,                              // lineNo
    28,                                // colNo
    "cur_pl",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo af_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    885,                               // lineNo
    57,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo bb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    662,                               // lineNo
    56,                                // colNo
    "timeSearchRange",                 // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo bc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1135,                              // lineNo
    40,                                // colNo
    "msk",                             // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo bd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1180,                              // lineNo
    29,                                // colNo
    "obj.Wf",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo be_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1209,                              // lineNo
    30,                                // colNo
    "cur_pl",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo bf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    885,                               // lineNo
    59,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo cb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    662,                               // lineNo
    33,                                // colNo
    "timeSearchRange",                 // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo cc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1054,                              // lineNo
    42,                                // colNo
    "sideband_msk",                    // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo cd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1198,                              // lineNo
    41,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ce_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1219,                              // lineNo
    28,                                // colNo
    "cur_pl",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo cf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    732,                               // lineNo
    27,                                // colNo
    "freq_mask",                       // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo db_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    668,                               // lineNo
    29,                                // colNo
    "timeSearchRange",                 // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo dc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1054,                              // lineNo
    44,                                // colNo
    "sideband_msk",                    // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo dd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1200,                              // lineNo
    50,                                // colNo
    "t_found_inds",                    // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo de_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1219,                              // lineNo
    30,                                // colNo
    "cur_pl",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo df_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    732,                               // lineNo
    43,                                // colNo
    "freq_mask",                       // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo eb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    669,                               // lineNo
    29,                                // colNo
    "timeSearchRange",                 // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ec_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1056,                              // lineNo
    42,                                // colNo
    "sideband_msk",                    // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ed_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1201,                              // lineNo
    20,                                // colNo
    "t_found",                         // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ee_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1220,                              // lineNo
    31,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ef_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    737,                               // lineNo
    32,                                // colNo
    "obj.Wf",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo fb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    672,                               // lineNo
    48,                                // colNo
    "timeSearchRange",                 // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo fc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1056,                              // lineNo
    54,                                // colNo
    "sideband_msk",                    // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo fd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1201,                              // lineNo
    57,                                // colNo
    "obj.stft.t",                      // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo fe_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1220,                              // lineNo
    42,                                // colNo
    "thresh",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ff_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    737,                               // lineNo
    43,                                // colNo
    "obj.Wf",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo gb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    672,                               // lineNo
    32,                                // colNo
    "timeBlinderVec",                  // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo gc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1058,                              // lineNo
    42,                                // colNo
    "sideband_msk",                    // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo gd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1201,                              // lineNo
    89,                                // colNo
    "obj.stft.t",                      // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ge_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1221,                              // lineNo
    32,                                // colNo
    "cur_pl",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo gf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    558,                               // lineNo
    80,                                // colNo
    "obj.ps_pre.pl",                   // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo hb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    672,                               // lineNo
    53,                                // colNo
    "timeBlinderVec",                  // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo hc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1079,                              // lineNo
    47,                                // colNo
    "bandwidth_of_peak",               // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo hd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1203,                              // lineNo
    41,                                // colNo
    "obj.Wf",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo he_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1221,                              // lineNo
    34,                                // colNo
    "cur_pl",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo hf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    582,                               // lineNo
    45,                                // colNo
    "obj.ps_pre.pl",                   // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ib_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    728,                               // lineNo
    32,                                // colNo
    "obj.Wf",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ic_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1121,                              // lineNo
    83,                                // colNo
    "bandwidth_of_peak",               // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo id_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1203,                              // lineNo
    51,                                // colNo
    "obj.Wf",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ie_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1229,                              // lineNo
    40,                                // colNo
    "obj.Wf",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo if_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    587,                               // lineNo
    42,                                // colNo
    "obj.stft.t",                      // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo jb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    728,                               // lineNo
    55,                                // colNo
    "obj.Wf",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo jc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1123,                              // lineNo
    38,                                // colNo
    "sideband_msk",                    // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo jd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1204,                              // lineNo
    41,                                // colNo
    "obj.Wf",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo je_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1234,                              // lineNo
    38,                                // colNo
    "thresh",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo jf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    587,                               // lineNo
    57,                                // colNo
    "obj.stft.t",                      // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo kb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    821,                               // lineNo
    50,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo kc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1124,                              // lineNo
    38,                                // colNo
    "sideband_msk",                    // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo kd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1204,                              // lineNo
    51,                                // colNo
    "obj.Wf",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ke_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1239,                              // lineNo
    38,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo kf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    592,                               // lineNo
    44,                                // colNo
    "obj.stft.t",                      // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo lb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    823,                               // lineNo
    29,                                // colNo
    "S_cols_for_mask",                 // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo lc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1091,                              // lineNo
    49,                                // colNo
    "bandwidth_of_peak",               // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ld_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1214,                              // lineNo
    26,                                // colNo
    "t_found",                         // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo le_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1156,                              // lineNo
    37,                                // colNo
    "indiv_msk",                       // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo lf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    619,                               // lineNo
    49,                                // colNo
    "obj.stft.t",                      // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo mb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    830,                               // lineNo
    49,                                // colNo
    "S_cols_for_mask",                 // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo mc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1116,                              // lineNo
    47,                                // colNo
    "bandwidth_of_peak",               // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo md_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1215,                              // lineNo
    25,                                // colNo
    "t_found",                         // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo me_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1156,                              // lineNo
    39,                                // colNo
    "indiv_msk",                       // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo nb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    831,                               // lineNo
    66,                                // colNo
    "weightedSRowSubsMat",             // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo nc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1021,                              // lineNo
    59,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo nd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1209,                              // lineNo
    61,                                // colNo
    "signalAmps",                      // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ne_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1031,                              // lineNo
    62,                                // colNo
    "slope_val",                       // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ob_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    833,                               // lineNo
    42,                                // colNo
    "indsOfBins",                      // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo oc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1021,                              // lineNo
    73,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo od_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1209,                              // lineNo
    63,                                // colNo
    "signalAmps",                      // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo oe_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1031,                              // lineNo
    76,                                // colNo
    "slope_val",                       // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo pb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    837,                               // lineNo
    27,                                // colNo
    "binMaskMatrix",                   // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo pc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1020,                              // lineNo
    59,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo pd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1210,                              // lineNo
    41,                                // colNo
    "yw_max_all_freq",                 // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo pe_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1030,                              // lineNo
    62,                                // colNo
    "slope_val",                       // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo qb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    854,                               // lineNo
    29,                                // colNo
    "noisePSDAtZetas",                 // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo qc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1020,                              // lineNo
    76,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo qd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1210,                              // lineNo
    43,                                // colNo
    "yw_max_all_freq",                 // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo qe_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1030,                              // lineNo
    79,                                // colNo
    "slope_val",                       // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo rb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    855,                               // lineNo
    41,                                // colNo
    "obj.stft.f",                      // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo rc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    993,                               // lineNo
    82,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo rd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1211,                              // lineNo
    31,                                // colNo
    "SNRdB",                           // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo re_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1021,                              // lineNo
    87,                                // colNo
    "thresh",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo sb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    855,                               // lineNo
    55,                                // colNo
    "obj.stft.f",                      // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo sc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1143,                              // lineNo
    40,                                // colNo
    "msk",                             // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo sd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1211,                              // lineNo
    33,                                // colNo
    "SNRdB",                           // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo se_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1021,                              // lineNo
    101,                               // colNo
    "thresh",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo tb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    865,                               // lineNo
    23,                                // colNo
    "signalPSD",                       // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo tc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1143,                              // lineNo
    51,                                // colNo
    "msk",                             // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo td_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1212,                              // lineNo
    33,                                // colNo
    "t_found",                         // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo te_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1020,                              // lineNo
    88,                                // colNo
    "thresh",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ub_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    869,                               // lineNo
    19,                                // colNo
    "SNRdB",                           // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo uc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1146,                              // lineNo
    46,                                // colNo
    "msk",                             // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ud_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1212,                              // lineNo
    35,                                // colNo
    "t_found",                         // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ue_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1020,                              // lineNo
    105,                               // colNo
    "thresh",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo vb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    959,                               // lineNo
    23,                                // colNo
    "peak",                            // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo vc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1155,                              // lineNo
    31,                                // colNo
    "msk",                             // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo vd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1213,                              // lineNo
    33,                                // colNo
    "t_found",                         // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ve_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    893,                               // lineNo
    48,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo wb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    974,                               // lineNo
    52,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo wc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1155,                              // lineNo
    33,                                // colNo
    "msk",                             // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo wd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1213,                              // lineNo
    35,                                // colNo
    "t_found",                         // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo we_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    893,                               // lineNo
    50,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo xb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    974,                               // lineNo
    64,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo xc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1158,                              // lineNo
    32,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo xd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1216,                              // lineNo
    36,                                // colNo
    "freq_found",                      // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo xe_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    892,                               // lineNo
    74,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo yb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    991,                               // lineNo
    82,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo yc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1160,                              // lineNo
    38,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo yd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1217,                              // lineNo
    33,                                // colNo
    "f_bands",                         // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ye_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    892,                               // lineNo
    76,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtDoubleCheckInfo ab_emlrtDCI{ 836,// lineNo
    35,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo bb_emlrtDCI{ 974,// lineNo
    52,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo cb_emlrtDCI{ 991,// lineNo
    58,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo db_emlrtDCI{ 1003,// lineNo
    68,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo eb_emlrtDCI{ 1004,// lineNo
    70,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo fb_emlrtDCI{ 1006,// lineNo
    68,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo gb_emlrtDCI{ 1007,// lineNo
    70,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo hb_emlrtDCI{ 1054,// lineNo
    44,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo ib_emlrtDCI{ 1056,// lineNo
    42,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo jb_emlrtDCI{ 1058,// lineNo
    42,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo kb_emlrtDCI{ 1123,// lineNo
    38,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo lb_emlrtDCI{ 1124,// lineNo
    38,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo mb_emlrtDCI{ 1021,// lineNo
    59,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo nb_emlrtDCI{ 1020,// lineNo
    59,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo ob_emlrtDCI{ 993,// lineNo
    58,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo pb_emlrtDCI{ 1201,// lineNo
    57,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo qb_emlrtDCI{ 1031,// lineNo
    62,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo rb_emlrtDCI{ 1030,// lineNo
    62,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo s_emlrtDCI{ 659,// lineNo
    37,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    4                                  // checkKind
  };

  static rtDoubleCheckInfo sb_emlrtDCI{ 1021,// lineNo
    87,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo t_emlrtDCI{ 659,// lineNo
    37,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo tb_emlrtDCI{ 1020,// lineNo
    88,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo u_emlrtDCI{ 659,// lineNo
    13,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    4                                  // checkKind
  };

  static rtDoubleCheckInfo v_emlrtDCI{ 659,// lineNo
    13,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo w_emlrtDCI{ 672,// lineNo
    32,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo x_emlrtDCI{ 672,// lineNo
    53,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo y_emlrtDCI{ 836,// lineNo
    35,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    4                                  // checkKind
  };

  static rtEqualityCheckInfo ab_emlrtECI{ 1,// nDims
    887,                               // lineNo
    27,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo ac_emlrtECI{ 1,// nDims
    1147,                              // lineNo
    43,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo bb_emlrtECI{ 1,// nDims
    888,                               // lineNo
    28,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo bc_emlrtECI{ 1,// nDims
    1148,                              // lineNo
    69,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo cb_emlrtECI{ 1,// nDims
    889,                               // lineNo
    27,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo cc_emlrtECI{ 1,// nDims
    1148,                              // lineNo
    43,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo db_emlrtECI{ 1,// nDims
    890,                               // lineNo
    28,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo dc_emlrtECI{ -1,// nDims
    1201,                              // lineNo
    12,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo eb_emlrtECI{ 1,// nDims
    892,                               // lineNo
    39,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo fb_emlrtECI{ 1,// nDims
    893,                               // lineNo
    34,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo g_emlrtECI{ -1,// nDims
    660,                               // lineNo
    13,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo gb_emlrtECI{ 1,// nDims
    902,                               // lineNo
    27,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo h_emlrtECI{ 1,// nDims
    53,                                // lineNo
    14,                                // colNo
    "vecfind",                         // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/vecfind.m"// pName
  };

  static rtEqualityCheckInfo hb_emlrtECI{ 1,// nDims
    901,                               // lineNo
    26,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo i_emlrtECI{ 2,// nDims
    53,                                // lineNo
    14,                                // colNo
    "vecfind",                         // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/vecfind.m"// pName
  };

  static rtEqualityCheckInfo ib_emlrtECI{ 1,// nDims
    902,                               // lineNo
    56,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo j_emlrtECI{ 1,// nDims
    57,                                // lineNo
    14,                                // colNo
    "vecfind",                         // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/vecfind.m"// pName
  };

  static rtEqualityCheckInfo jb_emlrtECI{ 1,// nDims
    927,                               // lineNo
    39,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo k_emlrtECI{ 2,// nDims
    57,                                // lineNo
    14,                                // colNo
    "vecfind",                         // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/vecfind.m"// pName
  };

  static rtEqualityCheckInfo kb_emlrtECI{ 1,// nDims
    942,                               // lineNo
    65,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo l_emlrtECI{ 1,// nDims
    681,                               // lineNo
    32,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo lb_emlrtECI{ 1,// nDims
    942,                               // lineNo
    39,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo m_emlrtECI{ 2,// nDims
    681,                               // lineNo
    32,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo mb_emlrtECI{ 1,// nDims
    946,                               // lineNo
    21,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo n_emlrtECI{ 1,// nDims
    743,                               // lineNo
    57,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo nb_emlrtECI{ 1,// nDims
    955,                               // lineNo
    23,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo o_emlrtECI{ 1,// nDims
    752,                               // lineNo
    26,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo ob_emlrtECI{ -1,// nDims
    1003,                              // lineNo
    48,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo p_emlrtECI{ 1,// nDims
    839,                               // lineNo
    40,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo pb_emlrtECI{ -1,// nDims
    1006,                              // lineNo
    48,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo q_emlrtECI{ 2,// nDims
    839,                               // lineNo
    40,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo qb_emlrtECI{ 1,// nDims
    1008,                              // lineNo
    39,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo r_emlrtECI{ 1,// nDims
    844,                               // lineNo
    44,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo rb_emlrtECI{ 1,// nDims
    1020,                              // lineNo
    52,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo s_emlrtECI{ 2,// nDims
    844,                               // lineNo
    44,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo sb_emlrtECI{ 1,// nDims
    1021,                              // lineNo
    52,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo t_emlrtECI{ 1,// nDims
    852,                               // lineNo
    40,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo tb_emlrtECI{ 1,// nDims
    1137,                              // lineNo
    34,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo u_emlrtECI{ 2,// nDims
    852,                               // lineNo
    40,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo ub_emlrtECI{ 1,// nDims
    1136,                              // lineNo
    34,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo v_emlrtECI{ 1,// nDims
    864,                               // lineNo
    37,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo vb_emlrtECI{ 1,// nDims
    1134,                              // lineNo
    34,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo w_emlrtECI{ 2,// nDims
    864,                               // lineNo
    37,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo wb_emlrtECI{ -1,// nDims
    1134,                              // lineNo
    21,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo x_emlrtECI{ 1,// nDims
    884,                               // lineNo
    33,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo xb_emlrtECI{ -1,// nDims
    1143,                              // lineNo
    17,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo y_emlrtECI{ 1,// nDims
    885,                               // lineNo
    33,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo yb_emlrtECI{ 1,// nDims
    1146,                              // lineNo
    31,                                // colNo
    "waveform/findpulse",              // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  coder::sparse Wq;
  coder::sparse serialRejectionMatrix;
  coder::array<creal_T, 2U> obj;
  coder::array<double, 2U> S_cols;
  coder::array<double, 2U> S_cols_for_mask;
  coder::array<double, 2U> b_excluded_freq_bands;
  coder::array<double, 2U> c_S_cols;
  coder::array<double, 2U> excluded_freq_bands;
  coder::array<double, 2U> r3;
  coder::array<double, 2U> refmat;
  coder::array<double, 2U> result;
  coder::array<double, 2U> searchmat;
  coder::array<double, 2U> signalPlusNoisePSD;
  coder::array<double, 2U> timeSearchRange;
  coder::array<double, 2U> yw_max_all_freq;
  coder::array<double, 1U> b_S_cols;
  coder::array<double, 1U> b_varargin_1_data;
  coder::array<double, 1U> bandwidth_of_peak;
  coder::array<double, 1U> n_diff_check_back;
  coder::array<double, 1U> n_diff_check_for;
  coder::array<double, 1U> peak;
  coder::array<double, 1U> scores;
  coder::array<double, 1U> timeBlinderVec;
  coder::array<int, 2U> r6;
  coder::array<int, 2U> r7;
  coder::array<int, 1U> r2;
  coder::array<int, 1U> r5;
  coder::array<boolean_T, 2U> msk;
  coder::array<boolean_T, 2U> r;
  coder::array<boolean_T, 2U> r1;
  coder::array<boolean_T, 1U> b_freq_mask;
  coder::array<boolean_T, 1U> excld_msk_vec;
  coder::array<boolean_T, 1U> freq_mask;
  coder::array<boolean_T, 1U> greater_than_next;
  coder::array<boolean_T, 1U> r4;
  coder::array<boolean_T, 1U> score_right_bndry;
  coder::array<boolean_T, 1U> slope_neg;
  coder::array<boolean_T, 1U> slope_pos;
  coder::array<boolean_T, 1U> slope_val;
  c_struct_T expl_temp;
  double t_srch_rng[2];
  double varargin_1_data[2];
  double a;
  double b_J;
  double b_M;
  double b_N;
  double naive_wind_end;
  double naive_wind_end_tmp;
  double next_pulse_start;
  double previousToc;
  double stft_dt;
  double t_lastknown;
  double timetol;
  double tip_temp;
  double tp_temp;
  double wind_start_data;
  int iv[2];
  int sizes[2];
  int b_loop_ub;
  int b_p;
  int b_result;
  int c_loop_ub;
  int d_loop_ub;
  int e_loop_ub;
  int f_loop_ub;
  int g_loop_ub;
  int h_loop_ub;
  int i;
  int i1;
  int i10;
  int i11;
  int i12;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  int i7;
  int i8;
  int i9;
  int i_loop_ub;
  int ii_data;
  int inds_bkwd_2_next_valley_data;
  int loop_ub;
  int loop_ub_tmp;
  int nRowsOfS;
  int n_freqs;
  int nx;
  unsigned int p;
  int wind_end_size;
  int wind_start_size;
  boolean_T freqModWarningFlag;
  boolean_T t8_con_dec;
  std::printf("FINDING PULSES...\n");
  std::fflush(stdout);
  previousToc = coder::toc();
  std::printf("\t Setting up parameter for finding pulses  ...\n");
  std::fflush(stdout);
  if (excluded_freq_bands_in.size(0) == 0) {
    excluded_freq_bands.set_size(1, 2);
    excluded_freq_bands[0] = rtInf;
    excluded_freq_bands[1] = rtMinusInf;
  } else {
    excluded_freq_bands.set_size(excluded_freq_bands_in.size(0), 2);
    loop_ub = excluded_freq_bands_in.size(0) << 1;
    for (i = 0; i < loop_ub; i++) {
      excluded_freq_bands[i] = excluded_freq_bands_in[i];
    }
  }

  // Get relavent variables and rename for readable code.
  b_N = N;
  b_M = M;
  b_J = J;

  // Define naive search window for pulse 1
  naive_wind_end_tmp = b_N + b_M;
  naive_wind_end = naive_wind_end_tmp + b_J;

  // The caller of this method should have already set the
  // threshold in the posteriori pulse stats. We just rename it
  // here to simplify code.
  // thresh = obj.ps_pos.thresh;
  // The caller of this method should have already set the
  // threshold. We just rename it
  // here to simplify code.
  // NAIVE SEARCH
  if (coder::internal::e_strcmp(time_searchtype_data, time_searchtype_size)) {
    wind_start_size = 1;
    wind_start_data = 1.0;
    wind_end_size = 1;
    next_pulse_start = naive_wind_end;

    // INFORMED SEARCH BUT NOT PRIORI FOR START TIME
  } else {
    if (coder::internal::f_strcmp(time_searchtype_data, time_searchtype_size)) {
      i = ps_pre->pl.size(1);
      if (i < 1) {
        rtDynamicBoundsError(1, 1, i, gf_emlrtBCI);
      }
    }

    // Due to segment lengths and overlapping, there can
    // sometimes be more than the desired number of pulses in a
    // segment. One more. If for example we were looking for 3
    // pulses, but the previous segment contained 4, the
    // algorithm may have localized the latter 3 rather than the
    // first 3. Here we set up the time window search range.
    // If the last known pulse is in the first part of the time
    // range of this segement currently getting processed, we
    // search around that very narrow region. If it
    // isn't (doesn't existing in this segement, only the
    // previous) we project the last known pulse forward one
    // interpulse time, and develop search region in accordance
    // with the uncertainty of the subsequent pulse.
    // Project out search range for first pulse in this segment
    // based on previous pulses.
    i = ps_pre->pl.size(1);
    i1 = ps_pre->pl.size(1);
    if ((i1 < 1) || (i1 > i)) {
      rtDynamicBoundsError(i1, 1, i, hf_emlrtBCI);
    }

    t_lastknown = ps_pre->pl[i1 - 1].t_0;
    tp_temp = ps_pre->t_p;

    // If the last pulse identified occured in this segement, use
    // it to downselect the first pulse search range.
    // Time steps in the STFT windows:
    i = stft->t.size(0);
    if (i < 2) {
      rtDynamicBoundsError(2, 1, i, if_emlrtBCI);
    }

    i = stft->t.size(0);
    if (i < 1) {
      rtDynamicBoundsError(1, 1, i, jf_emlrtBCI);
    }

    stft_dt = stft->t[1] - stft->t[0];

    // IF LAST SEGMENT'S LAST PULSE ALSO LIVES IN THIS SEGMENT
    // BECAUSE OF OVERLAP:
    timetol = n_ws / Fs;
    i = stft->t.size(0);
    if (i < 1) {
      rtDynamicBoundsError(1, 1, i, kf_emlrtBCI);
    }

    if (t_lastknown >= stft->t[0] - stft_dt / 2.0) {
      // The stft_dt/2 is because the stft time stamps are for
      //  the middle of each time windpw
      // wind_start = find(obj.stft.t-stft_dt/2 >=t_lastknown,1,'first');
      // wind_end   = find(obj.stft.t-stft_dt/2 <=t_lastknown+tp_temp,1,'last');
      // The logic below executes the same logic as the two
      // lines above (left commented for reference) but avoids
      // issues associated when comparing floating point
      // numbers. There can be small errors that make two
      // numbers not equal each other and this addresses that
      // problem. See the Matlab help file on eq.m under the
      // section 'Compare Floating-Point Numbers'.
      next_pulse_start = stft_dt / 2.0;
      peak.set_size(stft->t.size(0));
      loop_ub = stft->t.size(0);
      for (i = 0; i < loop_ub; i++) {
        peak[i] = (stft->t[i] - next_pulse_start) - t_lastknown;
      }

      nx = peak.size(0);
      timeBlinderVec.set_size(peak.size(0));
      if (peak.size(0) > 2147483646) {
        coder::check_forloop_overflow_error();
      }

      for (int k{0}; k < nx; k++) {
        timeBlinderVec[k] = std::abs(peak[k]);
      }

      score_right_bndry.set_size(timeBlinderVec.size(0));
      loop_ub = timeBlinderVec.size(0);
      for (i = 0; i < loop_ub; i++) {
        score_right_bndry[i] = (timeBlinderVec[i] <= timetol);
      }

      nx = coder::c_eml_find(score_right_bndry, (int *)&ii_data);
      wind_start_size = nx;
      for (i = 0; i < nx; i++) {
        wind_start_data = ii_data;
      }

      t_lastknown += tp_temp;
      peak.set_size(stft->t.size(0));
      loop_ub = stft->t.size(0);
      for (i = 0; i < loop_ub; i++) {
        peak[i] = (stft->t[i] - next_pulse_start) - t_lastknown;
      }

      nx = peak.size(0);
      timeBlinderVec.set_size(peak.size(0));
      if (peak.size(0) > 2147483646) {
        coder::check_forloop_overflow_error();
      }

      for (int k{0}; k < nx; k++) {
        timeBlinderVec[k] = std::abs(peak[k]);
      }

      score_right_bndry.set_size(timeBlinderVec.size(0));
      loop_ub = timeBlinderVec.size(0);
      for (i = 0; i < loop_ub; i++) {
        score_right_bndry[i] = (timeBlinderVec[i] <= timetol);
      }

      nx = coder::d_eml_find(score_right_bndry, (int *)&ii_data);
      wind_end_size = nx;
      for (i = 0; i < nx; i++) {
        next_pulse_start = ii_data;
      }

      // IF LAST SEGMENT'S LAST PULSE DOESN'T LIVE IN THIS SEGMENT:
    } else {
      // Project forward one pulse in time with
      // +/-2M uncertainty in search range.
      tip_temp = ps_pre->t_ip;
      a = ps_pre->t_ipu;
      next_pulse_start = t_lastknown + tip_temp;

      // +tp_temp/2;
      // These are the times of the START OF THE PULSE...not
      // the center. This is why we have stft_dt/2 terms in
      // subsequent equations.
      t_srch_rng[0] = -a + next_pulse_start;
      t_srch_rng[1] = a + next_pulse_start;
      i = stft->t.size(0);
      if (i < 1) {
        rtDynamicBoundsError(1, 1, i, lf_emlrtBCI);
      }

      if (t_srch_rng[0] < stft->t[0] - stft_dt / 2.0) {
        // If for some reason the last known pulse is more
        // that one pulse repetition interval away from the
        // current waveform start time, use the naive search
        // range.
        std::printf("UAV-RT: Requested informed search, but the last know pulse is more that one interpulse time away from the current segment start "
                    "time. This means the algorithm would have to project forward by more than one pulse repetition interval. This is not supported. "
                    "The naive search method will be used.");
        std::fflush(stdout);
        wind_start_size = 1;
        wind_start_data = 1.0;
        wind_end_size = 1;
        next_pulse_start = naive_wind_end;
      } else {
        // wind_start = find(obj.stft.t-stft_dt/2>=t_srch_rng(1),1,'first');
        // wind_end   = find(obj.stft.t-stft_dt/2<=t_srch_rng(2),1,'last');
        // The logic below executes the same logic as the two
        // lines above (left commented for reference) but
        // avoids issues associated when comparing floating
        // point numbers. There can be small errors that
        // make two numbers not equal each other and this
        // addresses that problem. See the Matlab help file
        // on eq.m under the section 'Compare Floating-Point
        // Numbers'.
        next_pulse_start = stft_dt / 2.0;
        peak.set_size(stft->t.size(0));
        loop_ub = stft->t.size(0);
        for (i = 0; i < loop_ub; i++) {
          peak[i] = (stft->t[i] - next_pulse_start) - t_srch_rng[0];
        }

        nx = peak.size(0);
        timeBlinderVec.set_size(peak.size(0));
        if (peak.size(0) > 2147483646) {
          coder::check_forloop_overflow_error();
        }

        for (int k{0}; k < nx; k++) {
          timeBlinderVec[k] = std::abs(peak[k]);
        }

        score_right_bndry.set_size(timeBlinderVec.size(0));
        loop_ub = timeBlinderVec.size(0);
        for (i = 0; i < loop_ub; i++) {
          score_right_bndry[i] = (timeBlinderVec[i] <= timetol);
        }

        nx = coder::c_eml_find(score_right_bndry, (int *)&ii_data);
        wind_start_size = nx;
        for (i = 0; i < nx; i++) {
          wind_start_data = ii_data;
        }

        peak.set_size(stft->t.size(0));
        loop_ub = stft->t.size(0);
        for (i = 0; i < loop_ub; i++) {
          peak[i] = (stft->t[i] - next_pulse_start) - t_srch_rng[1];
        }

        nx = peak.size(0);
        timeBlinderVec.set_size(peak.size(0));
        if (peak.size(0) > 2147483646) {
          coder::check_forloop_overflow_error();
        }

        for (int k{0}; k < nx; k++) {
          timeBlinderVec[k] = std::abs(peak[k]);
        }

        score_right_bndry.set_size(timeBlinderVec.size(0));
        loop_ub = timeBlinderVec.size(0);
        for (i = 0; i < loop_ub; i++) {
          score_right_bndry[i] = (timeBlinderVec[i] <= timetol);
        }

        nx = coder::d_eml_find(score_right_bndry, (int *)&ii_data);
        wind_end_size = nx;
        for (i = 0; i < nx; i++) {
          next_pulse_start = ii_data;
        }
      }
    }
  }

  if (wind_start_size == 0) {
    std::printf("UAV-RT: An error occured when trying to determine a time window search range based on prior information. Defaulting to naive sea"
                "rch.\n");
    std::fflush(stdout);
    wind_start_data = 1.0;
    wind_end_size = 1;
    next_pulse_start = naive_wind_end;
  }

  // Build a time search range matrix with one row for each pulse
  // The first column is the first window where that pulse might
  // live in the S matrix, and the second column is the last window
  // where that pulse might live in the S matrix.
  if (!(K >= 0.0)) {
    rtNonNegativeError(K, s_emlrtDCI);
  }

  a = K;
  if (a != static_cast<int>(std::floor(a))) {
    rtIntegerError(a, t_emlrtDCI);
  }

  timeSearchRange.set_size(static_cast<int>(a), 2);
  if (!(K >= 0.0)) {
    rtNonNegativeError(K, u_emlrtDCI);
  }

  a = K;
  if (a != static_cast<int>(std::floor(a))) {
    rtIntegerError(a, v_emlrtDCI);
  }

  loop_ub = static_cast<int>(a) << 1;
  for (i = 0; i < loop_ub; i++) {
    timeSearchRange[i] = 0.0;
  }

  if (static_cast<int>(K) < 1) {
    rtDynamicBoundsError(1, 1, static_cast<int>(K), ab_emlrtBCI);
  }

  if (wind_end_size != 1) {
    gb_rtErrorWithMessageID(ub_emlrtRTEI.fName, ub_emlrtRTEI.lineNo);
  }

  result.set_size(1, 2);
  result[0] = wind_start_data;
  result[result.size(0)] = next_pulse_start;
  sizes[0] = 1;
  sizes[1] = 2;
  rtSubAssignSizeCheck(&sizes[0], 2, result.size(), 2, g_emlrtECI);
  timeSearchRange[0] = result[0];
  timeSearchRange[timeSearchRange.size(0)] = result[1];
  i = static_cast<int>(K - 1.0);
  for (int k{0}; k < i; k++) {
    if (timeSearchRange.size(0) < 1) {
      rtDynamicBoundsError(1, 1, timeSearchRange.size(0), bb_emlrtBCI);
    }

    if ((static_cast<int>(static_cast<unsigned int>(k) + 2U) < 1) || (
         static_cast<int>(static_cast<unsigned int>(k) + 2U) >
         timeSearchRange.size(0))) {
      rtDynamicBoundsError(static_cast<int>(static_cast<unsigned int>(k) + 2U),
                           1, timeSearchRange.size(0), cb_emlrtBCI);
    }

    t_srch_rng[1] = timeSearchRange[timeSearchRange.size(0)] + (((static_cast<
      double>(k) + 2.0) - 1.0) * naive_wind_end_tmp + b_J);
    timeSearchRange[k + 1] = timeSearchRange[0] + (((static_cast<double>(k) +
      2.0) - 1.0) * (b_N - b_M) - b_J);
    timeSearchRange[(k + timeSearchRange.size(0)) + 1] = t_srch_rng[1];
  }

  nx = stft->S.size(1);

  // Limit the search to ranges of time that will be in the sftf
  // matrix
  inds_bkwd_2_next_valley_data = (timeSearchRange.size(0) << 1) - 1;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (timeSearchRange[k] > nx) {
      if (k > inds_bkwd_2_next_valley_data) {
        rtDynamicBoundsError(k, 0, inds_bkwd_2_next_valley_data, db_emlrtBCI);
      }

      timeSearchRange[k] = nx;
    }
  }

  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (timeSearchRange[k] < 1.0) {
      if (k > inds_bkwd_2_next_valley_data) {
        rtDynamicBoundsError(k, 0, inds_bkwd_2_next_valley_data, eb_emlrtBCI);
      }

      timeSearchRange[k] = 1.0;
    }
  }

  timeBlinderVec.set_size(nx);
  for (i = 0; i < nx; i++) {
    timeBlinderVec[i] = 0.0;
  }

  i = static_cast<int>(K);
  for (int k{0}; k < i; k++) {
    t8_con_dec = ((static_cast<int>(static_cast<unsigned int>(k) + 1U) < 1) || (
      static_cast<int>(static_cast<unsigned int>(k) + 1U) > timeSearchRange.size
      (0)));
    if (t8_con_dec) {
      rtDynamicBoundsError(static_cast<int>(static_cast<unsigned int>(k) + 1U),
                           1, timeSearchRange.size(0), fb_emlrtBCI);
    }

    a = timeSearchRange[k];
    next_pulse_start = timeSearchRange[k + timeSearchRange.size(0)];
    if (a > next_pulse_start) {
      i1 = 0;
      i2 = 0;
    } else {
      if (a != static_cast<int>(std::floor(a))) {
        rtIntegerError(a, w_emlrtDCI);
      }

      if ((static_cast<int>(a) < 1) || (static_cast<int>(a) >
           timeBlinderVec.size(0))) {
        rtDynamicBoundsError(static_cast<int>(a), 1, timeBlinderVec.size(0),
                             gb_emlrtBCI);
      }

      i1 = static_cast<int>(a) - 1;
      if (next_pulse_start != static_cast<int>(std::floor(next_pulse_start))) {
        rtIntegerError(next_pulse_start, x_emlrtDCI);
      }

      if ((static_cast<int>(next_pulse_start) < 1) || (static_cast<int>
           (next_pulse_start) > timeBlinderVec.size(0))) {
        rtDynamicBoundsError(static_cast<int>(next_pulse_start), 1,
                             timeBlinderVec.size(0), hb_emlrtBCI);
      }

      i2 = static_cast<int>(next_pulse_start);
    }

    loop_ub = i2 - i1;
    for (i2 = 0; i2 < loop_ub; i2++) {
      timeBlinderVec[i1 + i2] = 1.0;
    }
  }

  // Build the excluded frequency mask
  // False where we want to exclude
  // VECFIND creates a logical matrix based on the input operator comparing a
  // reference vector and a vector to be compared.
  //    This function can be used to do comparison operations of vectors of
  //    difference sizes. Comparing a single to a vector work natively
  //    in Matlab and create a resulting logic vector, i.e. [1 3 5]>4 outputs
  //    [0 0 1]. Many cases though require comparison of a vector to all the
  //    elements of another. i.e. [1 3 5]>[2 4] would ask which elements of
  //    [1 3 5] are greater than 2 and which are greater than 4? This function
  //    produces an output matrix whose columns are the logicial comparion of
  //    the reference vector to each element of the search vector. Logicals for
  //    comparison are input to this function as strings.
  //
  //    Example:
  //              outmat = vecfind([1 3 5],'>',[2 4])
  //
  //              outmat =
  //
  //              3×2 logical array
  //
  //              0   0
  //              1   0
  //              1   1
  //
  // INPUTS:
  //    refvec              n-element vector of numerics to be compared.
  //    comparison_op_string   A string of the comparison operator to be used
  //                        Valid options are '<' '<=' '>' '>=' '==' '~='
  //    searchvec           m-element vector of numerics used for comparison
  // OUTPUTS:
  //    outmat              nxm logical matrix comparing the ref and search
  //                        vectors
  //
  // Author: Michael Shafer
  // Date:   2021-05-25
  //
  // 2022-01-24 - Updated to use limited comparison operators and removed use
  //              of the eval.m function.
  //
  // Ensure column vector
  coder::repmat(Wf, static_cast<double>(excluded_freq_bands.size(0)), refmat);
  b_excluded_freq_bands.set_size(1, excluded_freq_bands.size(0));
  loop_ub = excluded_freq_bands.size(0);
  for (i = 0; i < loop_ub; i++) {
    b_excluded_freq_bands[i] = excluded_freq_bands[i];
  }

  coder::b_repmat(b_excluded_freq_bands, static_cast<double>(Wf.size(0)),
                  searchmat);

  // outmat = eval(['refmat',logical_op_string,'searchmat']);
  if ((refmat.size(0) != searchmat.size(0)) && ((refmat.size(0) != 1) &&
       (searchmat.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(refmat.size(0), searchmat.size(0), h_emlrtECI);
  }

  if ((refmat.size(1) != searchmat.size(1)) && ((refmat.size(1) != 1) &&
       (searchmat.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(refmat.size(1), searchmat.size(1), i_emlrtECI);
  }

  if ((refmat.size(0) == searchmat.size(0)) && (refmat.size(1) == searchmat.size
       (1))) {
    r.set_size(refmat.size(0), refmat.size(1));
    loop_ub = refmat.size(0) * refmat.size(1);
    for (i = 0; i < loop_ub; i++) {
      r[i] = (refmat[i] >= searchmat[i]);
    }
  } else {
    ge(r, refmat, searchmat);
  }

  // VECFIND creates a logical matrix based on the input operator comparing a
  // reference vector and a vector to be compared.
  //    This function can be used to do comparison operations of vectors of
  //    difference sizes. Comparing a single to a vector work natively
  //    in Matlab and create a resulting logic vector, i.e. [1 3 5]>4 outputs
  //    [0 0 1]. Many cases though require comparison of a vector to all the
  //    elements of another. i.e. [1 3 5]>[2 4] would ask which elements of
  //    [1 3 5] are greater than 2 and which are greater than 4? This function
  //    produces an output matrix whose columns are the logicial comparion of
  //    the reference vector to each element of the search vector. Logicals for
  //    comparison are input to this function as strings.
  //
  //    Example:
  //              outmat = vecfind([1 3 5],'>',[2 4])
  //
  //              outmat =
  //
  //              3×2 logical array
  //
  //              0   0
  //              1   0
  //              1   1
  //
  // INPUTS:
  //    refvec              n-element vector of numerics to be compared.
  //    comparison_op_string   A string of the comparison operator to be used
  //                        Valid options are '<' '<=' '>' '>=' '==' '~='
  //    searchvec           m-element vector of numerics used for comparison
  // OUTPUTS:
  //    outmat              nxm logical matrix comparing the ref and search
  //                        vectors
  //
  // Author: Michael Shafer
  // Date:   2021-05-25
  //
  // 2022-01-24 - Updated to use limited comparison operators and removed use
  //              of the eval.m function.
  //
  // Ensure column vector
  coder::repmat(Wf, static_cast<double>(excluded_freq_bands.size(0)), refmat);
  b_excluded_freq_bands.set_size(1, excluded_freq_bands.size(0));
  loop_ub = excluded_freq_bands.size(0);
  for (i = 0; i < loop_ub; i++) {
    b_excluded_freq_bands[i] = excluded_freq_bands[i + excluded_freq_bands.size
      (0)];
  }

  coder::b_repmat(b_excluded_freq_bands, static_cast<double>(Wf.size(0)),
                  searchmat);

  // outmat = eval(['refmat',logical_op_string,'searchmat']);
  if ((refmat.size(0) != searchmat.size(0)) && ((refmat.size(0) != 1) &&
       (searchmat.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(refmat.size(0), searchmat.size(0), j_emlrtECI);
  }

  if ((refmat.size(1) != searchmat.size(1)) && ((refmat.size(1) != 1) &&
       (searchmat.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(refmat.size(1), searchmat.size(1), k_emlrtECI);
  }

  if ((refmat.size(0) == searchmat.size(0)) && (refmat.size(1) == searchmat.size
       (1))) {
    msk.set_size(refmat.size(0), refmat.size(1));
    loop_ub = refmat.size(0) * refmat.size(1);
    for (i = 0; i < loop_ub; i++) {
      msk[i] = (refmat[i] <= searchmat[i]);
    }
  } else {
    le(msk, refmat, searchmat);
  }

  if ((r.size(0) != msk.size(0)) && ((r.size(0) != 1) && (msk.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(r.size(0), msk.size(0), l_emlrtECI);
  }

  if ((r.size(1) != msk.size(1)) && ((r.size(1) != 1) && (msk.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(r.size(1), msk.size(1), m_emlrtECI);
  }

  if ((r.size(0) == msk.size(0)) && (r.size(1) == msk.size(1))) {
    r1.set_size(r.size(0), r.size(1));
    loop_ub = r.size(0) * r.size(1);
    for (i = 0; i < loop_ub; i++) {
      r1[i] = ((!r[i]) || (!msk[i]));
    }

    coder::all(r1, excld_msk_vec);
  } else {
    binary_expand_op_20(excld_msk_vec, r, msk);
  }

  // Build the priori frequency mask
  // Naive or informed frequency search
  t8_con_dec = coder::internal::f_strcmp(freq_searchtype_data,
    freq_searchtype_size);
  if (t8_con_dec) {
    freqModWarningFlag = false;
    score_right_bndry.set_size(Wf.size(0));
    loop_ub = Wf.size(0);
    for (i = 0; i < loop_ub; i++) {
      score_right_bndry[i] = (Wf[i] >= ps_pre->fstart);
    }

    nx = coder::c_eml_find(score_right_bndry, (int *)&ii_data);
    for (i = 0; i < nx; i++) {
      wind_start_data = ii_data;
    }

    if (nx == 0) {
      wind_start_data = 1.0;
      freqModWarningFlag = true;
    }

    score_right_bndry.set_size(Wf.size(0));
    loop_ub = Wf.size(0);
    for (i = 0; i < loop_ub; i++) {
      score_right_bndry[i] = (Wf[i] <= ps_pre->fend);
    }

    nx = coder::d_eml_find(score_right_bndry, (int *)&ii_data);
    for (i = 0; i < nx; i++) {
      next_pulse_start = ii_data;
    }

    if (nx == 0) {
      next_pulse_start = Wf.size(0);
      freqModWarningFlag = true;
    }

    if (freqModWarningFlag) {
      std::printf("UAVRT: Requested informed search, but previous segment does not contain a start and/or stop frequency, or those values produces "
                  "a search range outside the range of frequencies available. The frequency search range has been modified.");
      std::fflush(stdout);
    }

    i = Wf.size(0);
    i1 = static_cast<int>(wind_start_data);
    if ((wind_start_data < 1.0) || (i1 > i)) {
      rtDynamicBoundsError(static_cast<int>(wind_start_data), 1, i, ib_emlrtBCI);
    }

    i = Wf.size(0);
    i2 = static_cast<int>(next_pulse_start);
    if ((next_pulse_start < 1.0) || (i2 > i)) {
      rtDynamicBoundsError(static_cast<int>(next_pulse_start), 1, i, jb_emlrtBCI);
    }

    std::printf("\t Frequency Search Range will be \t %f \t to \t %f.\n", Wf[
                static_cast<int>(wind_start_data) - 1], Wf[static_cast<int>
                (next_pulse_start) - 1]);
    std::fflush(stdout);

    // (1) is for coder so it knows it is a scalar
    result.set_size(1, 2);
    result[0] = wind_start_data;
    result[result.size(0)] = next_pulse_start;
    t_srch_rng[0] = Wf.size(0);
    freq_mask.set_size(Wf.size(0));
    loop_ub = Wf.size(0);
    for (i = 0; i < loop_ub; i++) {
      freq_mask[i] = false;
    }

    if (result[0] > result[1]) {
      i1 = 0;
      i2 = 0;
    } else {
      i = static_cast<int>(t_srch_rng[0]);
      if ((i1 < 1) || (i1 > i)) {
        rtDynamicBoundsError(i1, 1, static_cast<int>(t_srch_rng[0]), cf_emlrtBCI);
      }

      i1--;
      if ((i2 < 1) || (i2 > i)) {
        rtDynamicBoundsError(i2, 1, static_cast<int>(t_srch_rng[0]), df_emlrtBCI);
      }
    }

    loop_ub = i2 - i1;
    for (i = 0; i < loop_ub; i++) {
      freq_mask[i1 + i] = true;
    }
  } else {
    // Naive frequency search
    freq_mask.set_size(Wf.size(0));
    loop_ub = Wf.size(0);
    for (i = 0; i < loop_ub; i++) {
      freq_mask[i] = true;
    }

    i = Wf.size(0);
    if (i < 1) {
      rtDynamicBoundsError(1, 1, i, ef_emlrtBCI);
    }

    i = Wf.size(0);
    i1 = Wf.size(0);
    if ((i1 < 1) || (i1 > i)) {
      rtDynamicBoundsError(i1, 1, i, ff_emlrtBCI);
    }

    std::printf("\t Frequency Search Range will be \t %f \t to \t %f.\n", Wf[0],
                Wf[i1 - 1]);
    std::fflush(stdout);
  }

  // If using informed search and excluded frequencies overlap with
  // priori frequencies, warn the user.
  if (t8_con_dec) {
    b_freq_mask.set_size(excld_msk_vec.size(0));
    loop_ub = excld_msk_vec.size(0);
    for (i = 0; i < loop_ub; i++) {
      b_freq_mask[i] = !excld_msk_vec[i];
    }

    if ((freq_mask.size(0) != b_freq_mask.size(0)) && ((freq_mask.size(0) != 1) &&
         (b_freq_mask.size(0) != 1))) {
      emlrtDimSizeImpxCheckR2021b(freq_mask.size(0), b_freq_mask.size(0),
        n_emlrtECI);
    }

    if (freq_mask.size(0) == b_freq_mask.size(0)) {
      b_freq_mask.set_size(freq_mask.size(0));
      loop_ub = freq_mask.size(0);
      for (i = 0; i < loop_ub; i++) {
        b_freq_mask[i] = (freq_mask[i] && b_freq_mask[i]);
      }

      freqModWarningFlag = coder::internal::allOrAny_anonFcn1(b_freq_mask);
    } else {
      freqModWarningFlag = binary_expand_op_19(freq_mask, b_freq_mask);
    }

    if (freqModWarningFlag) {
      std::printf("UAV-RT: Using informed frequency search method and excluded frequencies. Some or all of the priori frequency band used for the i"
                  "nformed search overlaps with frequencies specified for exclusion from the search and thus will not be included.");
      std::fflush(stdout);
    }
  }

  // Combine the masks
  if ((freq_mask.size(0) != excld_msk_vec.size(0)) && ((freq_mask.size(0) != 1) &&
       (excld_msk_vec.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(freq_mask.size(0), excld_msk_vec.size(0),
      o_emlrtECI);
  }

  if (freq_mask.size(0) == excld_msk_vec.size(0)) {
    loop_ub = freq_mask.size(0);
    for (i = 0; i < loop_ub; i++) {
      freq_mask[i] = (freq_mask[i] && excld_msk_vec[i]);
    }
  } else {
    b_and(freq_mask, excld_msk_vec);
  }

  // Check that we actually have something to search
  freqModWarningFlag = coder::internal::allOrAny_anonFcn1(freq_mask);
  if (!freqModWarningFlag) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }

  // Determine the number of blocks to cut the data into. Should
  // always be the number of pulses currently looking for.
  stft_dt = (static_cast<double>(stft->S.size(1)) - 1.0) / naive_wind_end_tmp;
  stft_dt = std::floor(stft_dt);
  if (stft_dt == 0.0) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }

  next_pulse_start = coder::toc() - previousToc;
  std::printf("complete. Elapsed time: %f seconds \n", next_pulse_start);
  std::fflush(stdout);
  previousToc = coder::toc();
  std::printf("\t Building Time Correlation Matrix  ...");
  std::fflush(stdout);
  buildtimecorrelatormatrix(b_N, b_M, b_J, K, Wq);
  next_pulse_start = coder::toc() - previousToc;
  std::printf("complete. Elapsed time: %f seconds \n", next_pulse_start);
  std::fflush(stdout);
  previousToc = coder::toc();
  std::printf("\t Conducting incoherent summation step  ...");
  std::fflush(stdout);
  repetitionrejector(stft->t, serialRejectionMatrix);

  // [serialRejectionMatrix] = repetitionrejector(obj.stft.t, 0);%Outputs Identity for testing purposes
  obj.set_size(W.size(1), W.size(0));
  loop_ub = W.size(0);
  for (i = 0; i < loop_ub; i++) {
    nx = W.size(1);
    for (i1 = 0; i1 < nx; i1++) {
      obj[i1 + obj.size(0) * i].re = W[i + W.size(0) * i1].re;
      obj[i1 + obj.size(0) * i].im = -W[i + W.size(0) * i1].im;
    }
  }

  incohsumtoeplitz(freq_mask, obj, stft->S, serialRejectionMatrix,
                   timeBlinderVec, Wq, yw_max_all_freq, S_cols);

  // obj.TimeCorr.Wq(obj.K));
  next_pulse_start = coder::toc() - previousToc;
  std::printf("complete. Elapsed time: %f seconds \n", next_pulse_start);
  std::fflush(stdout);
  previousToc = coder::toc();
  std::printf("\t Running Peeling Algorithm...\n");
  std::fflush(stdout);

  //             %% PEELING ALGORITHM
  //  The following algorithm is used to help tease out the central
  //  peaks of the outputs of filter and sort out those entries
  //  that are sideband. It looks through all of the scores
  //  (yw_max_all_freqs), beginning with the highest score. It
  //  looks for other scores that are correlated in time and nearby
  //  frequency and identifies them as sidebands. Once the highest
  //  peak's sidebands are identified and excluded from further
  //  consideration as a separate pulse, the algorithm moves to the
  //  next highest score, repeating the sideband identification.
  //  This continues until no more scores that exceed the decision
  //  threshold remain.
  // Number of pulses identified for each frequency. This should be
  // equal to the K pulses of the search or n_blks.
  n_freqs = yw_max_all_freq.size(0);

  // Calculate the sum of the yw values - the score/test statistic
  coder::sum(yw_max_all_freq, scores);
  wind_start_size = stft->S.size(1);
  nRowsOfS = stft->S.size(0);

  // The few lines below finds the noisePSD, but excludes regions
  // in time and frequency around possible detection. We do
  // detections as the zeta steps, but use the S matrix for PSD
  // estimates so there is a size mismatch that necessitates the
  // code below.
  // In cases when there are K+1 pulses in a waveform, the
  // detection method will pull the first K, but an extra pulse
  // will be in the S matrix and needs to be excluded from the
  // noise power consideration. Here we add another column to the
  // S_cols matrix that projects the next Kth pulse out by 1
  // interpulse duration (N) so that that K+1th pulse will be
  // masked as well.
  if (S_cols.size(1) < 1) {
    rtDynamicBoundsError(S_cols.size(1), 1, S_cols.size(1), kb_emlrtBCI);
  }

  timeBlinderVec.set_size(S_cols.size(0));
  loop_ub = S_cols.size(0);
  for (i = 0; i < loop_ub; i++) {
    timeBlinderVec[i] = S_cols[i + S_cols.size(0) * (S_cols.size(1) - 1)] + N;
  }

  t8_con_dec = ((S_cols.size(0) != 0) && (S_cols.size(1) != 0));
  if (t8_con_dec) {
    b_result = S_cols.size(0);
  } else if (timeBlinderVec.size(0) != 0) {
    b_result = timeBlinderVec.size(0);
  } else {
    b_result = S_cols.size(0);
  }

  if ((S_cols.size(0) != b_result) && ((S_cols.size(0) != 0) && (S_cols.size(1)
        != 0))) {
    gb_rtErrorWithMessageID(ub_emlrtRTEI.fName, ub_emlrtRTEI.lineNo);
  }

  if ((timeBlinderVec.size(0) != b_result) && (timeBlinderVec.size(0) != 0)) {
    gb_rtErrorWithMessageID(ub_emlrtRTEI.fName, ub_emlrtRTEI.lineNo);
  }

  freqModWarningFlag = (b_result == 0);
  if (freqModWarningFlag || t8_con_dec) {
    nx = S_cols.size(1);
  } else {
    nx = 0;
  }

  if (freqModWarningFlag || (timeBlinderVec.size(0) != 0)) {
    sizes[1] = 1;
  } else {
    sizes[1] = 0;
  }

  i = nx + sizes[1];
  refmat.set_size(b_result, i);
  for (i1 = 0; i1 < nx; i1++) {
    for (i2 = 0; i2 < b_result; i2++) {
      refmat[i2 + refmat.size(0) * i1] = S_cols[i2 + b_result * i1];
    }
  }

  loop_ub = sizes[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    for (i2 = 0; i2 < b_result; i2++) {
      refmat[i2 + refmat.size(0) * nx] = timeBlinderVec[i2];
    }
  }

  S_cols_for_mask.set_size(b_result, i);
  for (i = 0; i < nx; i++) {
    for (i1 = 0; i1 < b_result; i1++) {
      S_cols_for_mask[i1 + S_cols_for_mask.size(0) * i] = S_cols[i1 + b_result *
        i];
    }
  }

  loop_ub = sizes[1];
  for (i = 0; i < loop_ub; i++) {
    for (i1 = 0; i1 < b_result; i1++) {
      S_cols_for_mask[i1 + S_cols_for_mask.size(0) * nx] = timeBlinderVec[i1];
    }
  }

  nx = stft->S.size(1);
  wind_end_size = refmat.size(0) * refmat.size(1);
  inds_bkwd_2_next_valley_data = wind_end_size - 1;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (refmat[k] > nx) {
      if (k > wind_end_size - 1) {
        rtDynamicBoundsError(k, 0, wind_end_size - 1, lb_emlrtBCI);
      }

      S_cols_for_mask[k] = nx;
    }
  }

  b_result = Wf.size(0);
  if (b_result < 1) {
    b_excluded_freq_bands.set_size(1, 0);
  } else {
    b_excluded_freq_bands.set_size(1, b_result);
    loop_ub = b_result - 1;
    for (i = 0; i <= loop_ub; i++) {
      b_excluded_freq_bands[i] = static_cast<double>(i) + 1.0;
    }
  }

  peak.set_size(b_excluded_freq_bands.size(1));
  loop_ub = b_excluded_freq_bands.size(1);
  for (i = 0; i < loop_ub; i++) {
    peak[i] = b_excluded_freq_bands[i];
  }

  coder::repmat(peak, static_cast<double>(S_cols_for_mask.size(1)), refmat);

  // sub2ind doesn't support NaN values, so we focus here on those
  // that don't have NaN
  sizes[0] = S_cols_for_mask.size(0);
  sizes[1] = S_cols_for_mask.size(1);
  iv[0] = (*(int (*)[2])S_cols_for_mask.size())[0];
  iv[1] = (*(int (*)[2])S_cols_for_mask.size())[1];
  coder::internal::b_indexShapeCheck(iv, sizes);
  b_result = 0;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (!std::isnan(S_cols_for_mask[k])) {
      b_result++;
    }
  }

  r2.set_size(b_result);
  b_result = 0;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (!std::isnan(S_cols_for_mask[k])) {
      r2[b_result] = k;
      b_result++;
    }
  }

  loop_ub = r2.size(0);
  for (i = 0; i < loop_ub; i++) {
    if (r2[i] > wind_end_size - 1) {
      rtDynamicBoundsError(r2[i], 0, wind_end_size - 1, mb_emlrtBCI);
    }
  }

  sizes[0] = S_cols_for_mask.size(0);
  sizes[1] = S_cols_for_mask.size(1);
  iv[0] = (*(int (*)[2])refmat.size())[0];
  iv[1] = (*(int (*)[2])refmat.size())[1];
  coder::internal::b_indexShapeCheck(iv, sizes);
  nx = refmat.size(0) * refmat.size(1);
  loop_ub = r2.size(0);
  for (i = 0; i < loop_ub; i++) {
    if (r2[i] > nx - 1) {
      rtDynamicBoundsError(r2[i], 0, nx - 1, nb_emlrtBCI);
    }
  }

  next_pulse_start = static_cast<double>(Wf.size(0)) / static_cast<double>
    (nRowsOfS) * static_cast<double>(nRowsOfS);
  nx = static_cast<int>(next_pulse_start);
  sizes[0] = static_cast<int>(next_pulse_start);
  sizes[1] = wind_start_size;
  peak.set_size(r2.size(0));
  loop_ub = r2.size(0);
  bandwidth_of_peak.set_size(r2.size(0));
  for (i = 0; i < loop_ub; i++) {
    peak[i] = refmat[r2[i]];
    bandwidth_of_peak[i] = S_cols_for_mask[r2[i]];
  }

  coder::internal::sub2ind(sizes, peak, bandwidth_of_peak, r2);
  timeBlinderVec.set_size(r2.size(0));
  loop_ub = r2.size(0);
  for (i = 0; i < loop_ub; i++) {
    timeBlinderVec[i] = r2[i];
  }

  inds_bkwd_2_next_valley_data = timeBlinderVec.size(0) - 1;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (k > inds_bkwd_2_next_valley_data) {
      rtDynamicBoundsError(k, 0, inds_bkwd_2_next_valley_data, ob_emlrtBCI);
    }
  }

  // binMaskMatrix will be a matrix of NaN at potential pulse
  // locations
  if (!(next_pulse_start >= 0.0)) {
    rtNonNegativeError(rtNaN, y_emlrtDCI);
  }

  if (next_pulse_start != static_cast<int>(std::floor(next_pulse_start))) {
    rtIntegerError(next_pulse_start, ab_emlrtDCI);
  }

  refmat.set_size(nx, wind_start_size);
  loop_ub_tmp = static_cast<int>(next_pulse_start) * wind_start_size;
  for (i = 0; i < loop_ub_tmp; i++) {
    refmat[i] = 0.0;
  }

  b_result = 0;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    b_result++;
  }

  r2.set_size(b_result);
  b_result = 0;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    i = static_cast<int>(timeBlinderVec[k]);
    if ((i < 1) || (i > loop_ub_tmp)) {
      rtDynamicBoundsError(i, 1, loop_ub_tmp, pb_emlrtBCI);
    }

    r2[b_result] = i;
    b_result++;
  }

  loop_ub = r2.size(0);
  for (i = 0; i < loop_ub; i++) {
    refmat[r2[i] - 1] = rtNaN;
  }

  // 0;
  // Now add some buffer around the potential pulse locations
  searchmat.set_size(refmat.size(0), refmat.size(1));
  for (i = 0; i < loop_ub_tmp; i++) {
    searchmat[i] = refmat[i];
  }

  coder::circshift(searchmat);
  if ((refmat.size(0) != searchmat.size(0)) && ((refmat.size(0) != 1) &&
       (searchmat.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(refmat.size(0), searchmat.size(0), p_emlrtECI);
  }

  if ((refmat.size(1) != searchmat.size(1)) && ((refmat.size(1) != 1) &&
       (searchmat.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(refmat.size(1), searchmat.size(1), q_emlrtECI);
  }

  if ((refmat.size(0) == searchmat.size(0)) && (refmat.size(1) == searchmat.size
       (1))) {
    searchmat.set_size(refmat.size(0), refmat.size(1));
    for (i = 0; i < loop_ub_tmp; i++) {
      searchmat[i] = refmat[i] + searchmat[i];
    }
  } else {
    c_plus(searchmat, refmat);
  }

  r3.set_size(refmat.size(0), refmat.size(1));
  loop_ub_tmp = refmat.size(0) * refmat.size(1);
  for (i = 0; i < loop_ub_tmp; i++) {
    r3[i] = refmat[i];
  }

  coder::b_circshift(r3);
  if ((searchmat.size(0) != r3.size(0)) && ((searchmat.size(0) != 1) && (r3.size
        (0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(0), r3.size(0), p_emlrtECI);
  }

  if ((searchmat.size(1) != r3.size(1)) && ((searchmat.size(1) != 1) && (r3.size
        (1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(1), r3.size(1), q_emlrtECI);
  }

  if ((searchmat.size(0) == r3.size(0)) && (searchmat.size(1) == r3.size(1))) {
    loop_ub = searchmat.size(0) * searchmat.size(1);
    for (i = 0; i < loop_ub; i++) {
      searchmat[i] = searchmat[i] + r3[i];
    }
  } else {
    plus(searchmat, r3);
  }

  r3.set_size(refmat.size(0), refmat.size(1));
  for (i = 0; i < loop_ub_tmp; i++) {
    r3[i] = refmat[i];
  }

  coder::c_circshift(r3);
  if ((searchmat.size(0) != r3.size(0)) && ((searchmat.size(0) != 1) && (r3.size
        (0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(0), r3.size(0), p_emlrtECI);
  }

  if ((searchmat.size(1) != r3.size(1)) && ((searchmat.size(1) != 1) && (r3.size
        (1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(1), r3.size(1), q_emlrtECI);
  }

  if ((searchmat.size(0) == r3.size(0)) && (searchmat.size(1) == r3.size(1))) {
    loop_ub = searchmat.size(0) * searchmat.size(1);
    for (i = 0; i < loop_ub; i++) {
      searchmat[i] = searchmat[i] + r3[i];
    }
  } else {
    plus(searchmat, r3);
  }

  coder::d_circshift(refmat);
  if ((searchmat.size(0) != refmat.size(0)) && ((searchmat.size(0) != 1) &&
       (refmat.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(0), refmat.size(0), p_emlrtECI);
  }

  if ((searchmat.size(1) != refmat.size(1)) && ((searchmat.size(1) != 1) &&
       (refmat.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(1), refmat.size(1), q_emlrtECI);
  }

  if ((searchmat.size(0) == refmat.size(0)) && (searchmat.size(1) == refmat.size
       (1))) {
    loop_ub = searchmat.size(0) * searchmat.size(1);
    for (i = 0; i < loop_ub; i++) {
      searchmat[i] = searchmat[i] + refmat[i];
    }
  } else {
    plus(searchmat, refmat);
  }

  r3.set_size(searchmat.size(0), searchmat.size(1));
  loop_ub_tmp = searchmat.size(0) * searchmat.size(1);
  for (i = 0; i < loop_ub_tmp; i++) {
    r3[i] = searchmat[i];
  }

  coder::e_circshift(r3);
  if ((searchmat.size(0) != r3.size(0)) && ((searchmat.size(0) != 1) && (r3.size
        (0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(0), r3.size(0), r_emlrtECI);
  }

  if ((searchmat.size(1) != r3.size(1)) && ((searchmat.size(1) != 1) && (r3.size
        (1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(1), r3.size(1), s_emlrtECI);
  }

  if ((searchmat.size(0) == r3.size(0)) && (searchmat.size(1) == r3.size(1))) {
    r3.set_size(searchmat.size(0), searchmat.size(1));
    for (i = 0; i < loop_ub_tmp; i++) {
      r3[i] = searchmat[i] + r3[i];
    }
  } else {
    c_plus(r3, searchmat);
  }

  coder::f_circshift(searchmat);
  if ((r3.size(0) != searchmat.size(0)) && ((r3.size(0) != 1) && (searchmat.size
        (0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(r3.size(0), searchmat.size(0), r_emlrtECI);
  }

  if ((r3.size(1) != searchmat.size(1)) && ((r3.size(1) != 1) && (searchmat.size
        (1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(r3.size(1), searchmat.size(1), s_emlrtECI);
  }

  if ((r3.size(0) == searchmat.size(0)) && (r3.size(1) == searchmat.size(1))) {
    signalPlusNoisePSD.set_size(r3.size(0), r3.size(1));
    loop_ub = r3.size(0) * r3.size(1);
    for (i = 0; i < loop_ub; i++) {
      signalPlusNoisePSD[i] = r3[i] + searchmat[i];
    }

    t_srch_rng[0] = nRowsOfS;
    t_srch_rng[1] = wind_start_size;
    coder::imresize(signalPlusNoisePSD, t_srch_rng, refmat);
  } else {
    binary_expand_op_18(refmat, r3, searchmat, nRowsOfS, wind_start_size);
  }

  next_pulse_start = 1.0 / Fs;
  i = stft->S.size(0);
  if ((i != refmat.size(0)) && ((i != 1) && (refmat.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(i, refmat.size(0), t_emlrtECI);
  }

  i = stft->S.size(1);
  if ((i != refmat.size(1)) && ((i != 1) && (refmat.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(i, refmat.size(1), u_emlrtECI);
  }

  tip_temp = next_pulse_start * next_pulse_start / (n_w / Fs);
  if ((stft->S.size(0) == refmat.size(0)) && (stft->S.size(1) == refmat.size(1)))
  {
    obj.set_size(stft->S.size(0), stft->S.size(1));
    loop_ub = stft->S.size(0) * stft->S.size(1);
    for (i = 0; i < loop_ub; i++) {
      obj[i].re = stft->S[i].re + refmat[i];
      obj[i].im = stft->S[i].im;
    }

    nx = obj.size(0) * obj.size(1);
    refmat.set_size(obj.size(0), obj.size(1));
    if (nx > 2147483646) {
      coder::check_forloop_overflow_error();
    }

    for (int k{0}; k < nx; k++) {
      refmat[k] = rt_hypotd_snf(obj[k].re, obj[k].im);
    }
  } else {
    binary_expand_op_17(refmat, this);
  }

  r3.set_size(refmat.size(0), refmat.size(1));
  loop_ub = refmat.size(0) * refmat.size(1);
  for (i = 0; i < loop_ub; i++) {
    next_pulse_start = refmat[i];
    r3[i] = next_pulse_start * next_pulse_start;
  }

  coder::mean(r3, timeBlinderVec);

  // Add since it is 0 where we expect noise and NaN where there might be a pulse
  peak.set_size(timeBlinderVec.size(0));
  loop_ub = timeBlinderVec.size(0);
  for (i = 0; i < loop_ub; i++) {
    peak[i] = tip_temp * timeBlinderVec[i];
  }

  coder::interp1(stft->f, peak, Wf, timeBlinderVec);
  inds_bkwd_2_next_valley_data = timeBlinderVec.size(0) - 1;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (timeBlinderVec[k] < 0.0) {
      if (k > inds_bkwd_2_next_valley_data) {
        rtDynamicBoundsError(k, 0, inds_bkwd_2_next_valley_data, qb_emlrtBCI);
      }

      timeBlinderVec[k] = 0.0;
    }
  }

  i = stft->f.size(0);
  if (i < 2) {
    rtDynamicBoundsError(2, 1, i, rb_emlrtBCI);
  }

  i = stft->f.size(0);
  if (i < 1) {
    rtDynamicBoundsError(1, 1, i, sb_emlrtBCI);
  }

  next_pulse_start = stft->f[1] - stft->f[0];

  // Not the delta f of the Wf vector, because the frequency bins are the same width, just with half bin steps %
  // Calculate the power at each of the S locations that were
  // selected by the incohsum function. Scores are the mag squared
  // S values. Mult by dt^2/T to get psd, then mult by the width of
  // the frequency bin to get power. We have to do this because the
  // psd in the stft object uses dt^2/T factor for the psd calc.
  signalPlusNoisePSD.set_size(yw_max_all_freq.size(0), yw_max_all_freq.size(1));
  loop_ub_tmp = yw_max_all_freq.size(0) * yw_max_all_freq.size(1);
  for (i = 0; i < loop_ub_tmp; i++) {
    signalPlusNoisePSD[i] = tip_temp * yw_max_all_freq[i];
  }

  // scores;
  coder::repmat(timeBlinderVec, static_cast<double>(yw_max_all_freq.size(1)), r3);
  if ((signalPlusNoisePSD.size(0) != r3.size(0)) && ((signalPlusNoisePSD.size(0)
        != 1) && (r3.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(signalPlusNoisePSD.size(0), r3.size(0),
      v_emlrtECI);
  }

  if ((signalPlusNoisePSD.size(1) != r3.size(1)) && ((signalPlusNoisePSD.size(1)
        != 1) && (r3.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(signalPlusNoisePSD.size(1), r3.size(1),
      w_emlrtECI);
  }

  if ((signalPlusNoisePSD.size(0) == r3.size(0)) && (signalPlusNoisePSD.size(1) ==
       r3.size(1))) {
    for (i = 0; i < loop_ub_tmp; i++) {
      signalPlusNoisePSD[i] = signalPlusNoisePSD[i] - r3[i];
    }
  } else {
    minus(signalPlusNoisePSD, r3);
  }

  wind_end_size = signalPlusNoisePSD.size(0) * signalPlusNoisePSD.size(1);
  inds_bkwd_2_next_valley_data = wind_end_size - 1;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (signalPlusNoisePSD[k] < 0.0) {
      if (k > wind_end_size - 1) {
        rtDynamicBoundsError(k, 0, wind_end_size - 1, tb_emlrtBCI);
      }

      signalPlusNoisePSD[k] = 0.0;
    }
  }

  // Can't have negative values
  searchmat.set_size(signalPlusNoisePSD.size(0), signalPlusNoisePSD.size(1));
  for (i = 0; i < wind_end_size; i++) {
    searchmat[i] = signalPlusNoisePSD[i] * next_pulse_start;
  }

  coder::b_sqrt(searchmat);
  coder::repmat(timeBlinderVec, static_cast<double>(yw_max_all_freq.size(1)),
                refmat);
  coder::internal::assertCompatibleDims(signalPlusNoisePSD, refmat);
  if ((signalPlusNoisePSD.size(0) == refmat.size(0)) && (signalPlusNoisePSD.size
       (1) == refmat.size(1))) {
    for (i = 0; i < wind_end_size; i++) {
      signalPlusNoisePSD[i] = signalPlusNoisePSD[i] / refmat[i];
    }
  } else {
    rdivide(signalPlusNoisePSD, refmat);
  }

  coder::b_log10(signalPlusNoisePSD);
  nRowsOfS = signalPlusNoisePSD.size(0) * signalPlusNoisePSD.size(1);
  for (i = 0; i < nRowsOfS; i++) {
    signalPlusNoisePSD[i] = 10.0 * signalPlusNoisePSD[i];
  }

  inds_bkwd_2_next_valley_data = nRowsOfS - 1;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (signalPlusNoisePSD[k] == rtInf) {
      if (k > nRowsOfS - 1) {
        rtDynamicBoundsError(k, 0, nRowsOfS - 1, ub_emlrtBCI);
      }

      signalPlusNoisePSD[k] = rtNaN;
    }
  }

  // Calculate the first and second frequency derivatives of the
  // scores. We'll use these for slope and curvature assessments.
  // These aren't truely the frequency derivatives because we don't
  // divide by deltaf. The are really dsdfrequency bin. We don't
  // really care about the magnitude though, just the sign. Each
  // dsdf value is the average of the slope ahead and behind the
  // point.
  // dsdf     = [0; mean([diff(scores(1:end-1)),diff(scores(2:end))],2);0];%See notebook entry 2021-02-10
  // d2sdf2   = [0; mean([diff(dsdf(1:end-1)),diff(dsdf(2:end))],2);0];%See notebook entry 2021-02-10
  // This block of code determines where there are peaks (negative
  // slopes to the left and right) and where there are valleys
  // (positive slopes to left and right)
  if (scores.size(0) < 1) {
    loop_ub = 0;
  } else {
    loop_ub = scores.size(0);
  }

  sizes[0] = 1;
  sizes[1] = loop_ub;
  coder::internal::indexShapeCheck(scores.size(0), sizes);
  if (scores.size(0) < 2) {
    i = 0;
    i1 = 0;
  } else {
    i = 1;
    i1 = scores.size(0);
  }

  sizes[0] = 1;
  nx = i1 - i;
  sizes[1] = nx;
  coder::internal::indexShapeCheck(scores.size(0), sizes);
  timeBlinderVec.set_size(nx + 1);
  for (i1 = 0; i1 < nx; i1++) {
    timeBlinderVec[i1] = scores[i + i1];
  }

  timeBlinderVec[nx] = 0.0;
  if ((loop_ub != timeBlinderVec.size(0)) && ((loop_ub != 1) &&
       (timeBlinderVec.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(loop_ub, timeBlinderVec.size(0), x_emlrtECI);
  }

  if (loop_ub == timeBlinderVec.size(0)) {
    greater_than_next.set_size(loop_ub);
    for (i = 0; i < loop_ub; i++) {
      greater_than_next[i] = (scores[i] > timeBlinderVec[i]);
    }
  } else {
    binary_expand_op_15(greater_than_next, scores, loop_ub, timeBlinderVec);
  }

  if (scores.size(0) < 1) {
    loop_ub = 0;
  } else {
    loop_ub = scores.size(0);
  }

  sizes[0] = 1;
  sizes[1] = loop_ub;
  coder::internal::indexShapeCheck(scores.size(0), sizes);
  if (scores.size(0) - 1 < 1) {
    nx = 0;
  } else {
    if (scores.size(0) < 1) {
      rtDynamicBoundsError(1, 1, scores.size(0), af_emlrtBCI);
    }

    if ((scores.size(0) - 1 < 1) || (scores.size(0) - 1 > scores.size(0))) {
      rtDynamicBoundsError(scores.size(0) - 1, 1, scores.size(0), bf_emlrtBCI);
    }

    nx = scores.size(0) - 1;
  }

  sizes[0] = 1;
  sizes[1] = nx;
  coder::internal::indexShapeCheck(scores.size(0), sizes);
  timeBlinderVec.set_size(nx + 1);
  timeBlinderVec[0] = 0.0;
  for (i = 0; i < nx; i++) {
    timeBlinderVec[i + 1] = scores[i];
  }

  if ((loop_ub != timeBlinderVec.size(0)) && ((loop_ub != 1) &&
       (timeBlinderVec.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(loop_ub, timeBlinderVec.size(0), y_emlrtECI);
  }

  if (loop_ub == timeBlinderVec.size(0)) {
    excld_msk_vec.set_size(loop_ub);
    for (i = 0; i < loop_ub; i++) {
      excld_msk_vec[i] = (scores[i] > timeBlinderVec[i]);
    }
  } else {
    binary_expand_op_15(excld_msk_vec, scores, loop_ub, timeBlinderVec);
  }

  slope_val.set_size(greater_than_next.size(0));
  loop_ub = greater_than_next.size(0);
  for (i = 0; i < loop_ub; i++) {
    slope_val[i] = !greater_than_next[i];
  }

  if ((slope_val.size(0) != excld_msk_vec.size(0)) && ((slope_val.size(0) != 1) &&
       (excld_msk_vec.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(slope_val.size(0), excld_msk_vec.size(0),
      ab_emlrtECI);
  }

  if (slope_val.size(0) == excld_msk_vec.size(0)) {
    slope_pos.set_size(slope_val.size(0));
    loop_ub = slope_val.size(0);
    for (i = 0; i < loop_ub; i++) {
      slope_pos[i] = (slope_val[i] && excld_msk_vec[i]);
    }
  } else {
    c_and(slope_pos, slope_val, excld_msk_vec);
  }

  b_freq_mask.set_size(excld_msk_vec.size(0));
  loop_ub = excld_msk_vec.size(0);
  for (i = 0; i < loop_ub; i++) {
    b_freq_mask[i] = !excld_msk_vec[i];
  }

  if ((greater_than_next.size(0) != b_freq_mask.size(0)) &&
      ((greater_than_next.size(0) != 1) && (b_freq_mask.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(greater_than_next.size(0), b_freq_mask.size(0),
      bb_emlrtECI);
  }

  if (greater_than_next.size(0) == b_freq_mask.size(0)) {
    slope_neg.set_size(greater_than_next.size(0));
    loop_ub = greater_than_next.size(0);
    for (i = 0; i < loop_ub; i++) {
      slope_neg[i] = (greater_than_next[i] && b_freq_mask[i]);
    }
  } else {
    c_and(slope_neg, greater_than_next, b_freq_mask);
  }

  if ((slope_val.size(0) != b_freq_mask.size(0)) && ((slope_val.size(0) != 1) &&
       (b_freq_mask.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(slope_val.size(0), b_freq_mask.size(0),
      cb_emlrtECI);
  }

  if (slope_val.size(0) == b_freq_mask.size(0)) {
    loop_ub = slope_val.size(0);
    for (i = 0; i < loop_ub; i++) {
      slope_val[i] = (slope_val[i] && b_freq_mask[i]);
    }
  } else {
    b_and(slope_val, b_freq_mask);
  }

  if ((greater_than_next.size(0) != excld_msk_vec.size(0)) &&
      ((greater_than_next.size(0) != 1) && (excld_msk_vec.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(greater_than_next.size(0), excld_msk_vec.size(0),
      db_emlrtECI);
  }

  if (greater_than_next.size(0) == excld_msk_vec.size(0)) {
    loop_ub = greater_than_next.size(0);
    for (i = 0; i < loop_ub; i++) {
      greater_than_next[i] = (greater_than_next[i] && excld_msk_vec[i]);
    }
  } else {
    b_and(greater_than_next, excld_msk_vec);
  }

  if (scores.size(0) < 2) {
    i = 0;
    i1 = 0;
  } else {
    i = 1;
    i1 = scores.size(0);
  }

  sizes[0] = 1;
  nx = i1 - i;
  sizes[1] = nx;
  coder::internal::indexShapeCheck(scores.size(0), sizes);
  if (scores.size(0) - 1 < 1) {
    loop_ub = 0;
  } else {
    if (scores.size(0) < 1) {
      rtDynamicBoundsError(1, 1, scores.size(0), xe_emlrtBCI);
    }

    if ((scores.size(0) - 1 < 1) || (scores.size(0) - 1 > scores.size(0))) {
      rtDynamicBoundsError(scores.size(0) - 1, 1, scores.size(0), ye_emlrtBCI);
    }

    loop_ub = scores.size(0) - 1;
  }

  sizes[0] = 1;
  sizes[1] = loop_ub;
  coder::internal::indexShapeCheck(scores.size(0), sizes);
  b_freq_mask.set_size(nx);
  for (i1 = 0; i1 < nx; i1++) {
    b_freq_mask[i1] = !std::isnan(scores[i + i1]);
  }

  r4.set_size(loop_ub);
  for (i = 0; i < loop_ub; i++) {
    r4[i] = std::isnan(scores[i]);
  }

  if ((b_freq_mask.size(0) != r4.size(0)) && ((b_freq_mask.size(0) != 1) &&
       (r4.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(b_freq_mask.size(0), r4.size(0), eb_emlrtECI);
  }

  if (b_freq_mask.size(0) == r4.size(0)) {
    excld_msk_vec.set_size(b_freq_mask.size(0) + 1);
    excld_msk_vec[0] = true;
    loop_ub = b_freq_mask.size(0);
    for (i = 0; i < loop_ub; i++) {
      excld_msk_vec[i + 1] = (b_freq_mask[i] && r4[i]);
    }
  } else {
    binary_expand_op_14(excld_msk_vec, b_freq_mask, r4);
  }

  if (scores.size(0) - 1 < 1) {
    loop_ub = 0;
  } else {
    if (scores.size(0) < 1) {
      rtDynamicBoundsError(1, 1, scores.size(0), ve_emlrtBCI);
    }

    if ((scores.size(0) - 1 < 1) || (scores.size(0) - 1 > scores.size(0))) {
      rtDynamicBoundsError(scores.size(0) - 1, 1, scores.size(0), we_emlrtBCI);
    }

    loop_ub = scores.size(0) - 1;
  }

  sizes[0] = 1;
  sizes[1] = loop_ub;
  coder::internal::indexShapeCheck(scores.size(0), sizes);
  if (scores.size(0) < 2) {
    i = 0;
    i1 = 0;
  } else {
    i = 1;
    i1 = scores.size(0);
  }

  sizes[0] = 1;
  nx = i1 - i;
  sizes[1] = nx;
  coder::internal::indexShapeCheck(scores.size(0), sizes);
  b_freq_mask.set_size(loop_ub);
  for (i1 = 0; i1 < loop_ub; i1++) {
    b_freq_mask[i1] = !std::isnan(scores[i1]);
  }

  r4.set_size(nx);
  for (i1 = 0; i1 < nx; i1++) {
    r4[i1] = std::isnan(scores[i + i1]);
  }

  if ((b_freq_mask.size(0) != r4.size(0)) && ((b_freq_mask.size(0) != 1) &&
       (r4.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(b_freq_mask.size(0), r4.size(0), fb_emlrtECI);
  }

  if (b_freq_mask.size(0) == r4.size(0)) {
    score_right_bndry.set_size(b_freq_mask.size(0) + 1);
    loop_ub = b_freq_mask.size(0);
    for (i = 0; i < loop_ub; i++) {
      score_right_bndry[i] = (b_freq_mask[i] && r4[i]);
    }

    score_right_bndry[b_freq_mask.size(0)] = true;
  } else {
    binary_expand_op_13(score_right_bndry, b_freq_mask, r4);
  }

  // This deals with the frequency masking and some scores will be
  // NaN because they were excluded from consideration in the
  // incohsum processing. If the score is a left boundary
  // (frequencies lower were excluded) and the slope is negative,
  // this would be considered a peak. Visa-versa for right
  // boundaries.
  if ((excld_msk_vec.size(0) != slope_neg.size(0)) && ((excld_msk_vec.size(0) !=
        1) && (slope_neg.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(excld_msk_vec.size(0), slope_neg.size(0),
      gb_emlrtECI);
  }

  if (excld_msk_vec.size(0) == slope_neg.size(0)) {
    loop_ub = excld_msk_vec.size(0);
    for (i = 0; i < loop_ub; i++) {
      excld_msk_vec[i] = (excld_msk_vec[i] && slope_neg[i]);
    }
  } else {
    b_and(excld_msk_vec, slope_neg);
  }

  if ((greater_than_next.size(0) != excld_msk_vec.size(0)) &&
      ((greater_than_next.size(0) != 1) && (excld_msk_vec.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(greater_than_next.size(0), excld_msk_vec.size(0),
      hb_emlrtECI);
  }

  if ((score_right_bndry.size(0) != slope_pos.size(0)) &&
      ((score_right_bndry.size(0) != 1) && (slope_pos.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(score_right_bndry.size(0), slope_pos.size(0),
      ib_emlrtECI);
  }

  if (greater_than_next.size(0) == excld_msk_vec.size(0)) {
    loop_ub = greater_than_next.size(0);
    for (i = 0; i < loop_ub; i++) {
      greater_than_next[i] = (greater_than_next[i] || excld_msk_vec[i]);
    }
  } else {
    b_or(greater_than_next, excld_msk_vec);
  }

  if (score_right_bndry.size(0) == slope_pos.size(0)) {
    loop_ub = score_right_bndry.size(0);
    for (i = 0; i < loop_ub; i++) {
      score_right_bndry[i] = (score_right_bndry[i] && slope_pos[i]);
    }
  } else {
    b_and(score_right_bndry, slope_pos);
  }

  if ((greater_than_next.size(0) != score_right_bndry.size(0)) &&
      ((greater_than_next.size(0) != 1) && (score_right_bndry.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(greater_than_next.size(0),
      score_right_bndry.size(0), hb_emlrtECI);
  }

  if (greater_than_next.size(0) == score_right_bndry.size(0)) {
    loop_ub = greater_than_next.size(0);
    for (i = 0; i < loop_ub; i++) {
      greater_than_next[i] = (greater_than_next[i] || score_right_bndry[i]);
    }
  } else {
    b_or(greater_than_next, score_right_bndry);
  }

  // How many time windows difference do we considered the found
  // pulse to be the same as one found at a different frequency?
  // We'll say that if they are within two pulse time width of
  // each other they are the same pulse.
  naive_wind_end = 2.0 * n_p / n_ws;
  p = 1U;

  // Initilize a peak counter variable
  // Initially these are the same.
  // The peak and peak_ind variables are a vector of scores and the
  // frequency index of the identified peaks of the pulses. There
  // could only ever be n_freqs peaks, so we preallocate the
  // vectors to be that long, although there will typically be far
  // fever of them - ideally the number of tags in the signal.
  peak.set_size(yw_max_all_freq.size(0));
  loop_ub = yw_max_all_freq.size(0);
  peak_ind.set_size(yw_max_all_freq.size(0));
  bandwidth_of_peak.set_size(yw_max_all_freq.size(0));
  for (i = 0; i < loop_ub; i++) {
    peak[i] = 0.0;
    peak_ind[i] = 0.0;
    bandwidth_of_peak[i] = 0.0;
  }

  msk.set_size(yw_max_all_freq.size(0), yw_max_all_freq.size(0));
  nRowsOfS = yw_max_all_freq.size(0) * yw_max_all_freq.size(0);
  indiv_msk.set_size(yw_max_all_freq.size(0), yw_max_all_freq.size(0));
  for (i = 0; i < nRowsOfS; i++) {
    msk[i] = false;
    indiv_msk[i] = false;
  }

  // peak_masked_curr_scores is a vector of scores where only the
  // peaks have scores. All others (valleys, +slope, -slope) are
  // set to zero. As we identify peaks, they will also be set to
  // zero so that we can work our way through these peaks.
  if ((scores.size(0) != greater_than_next.size(0)) && ((scores.size(0) != 1) &&
       (greater_than_next.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(scores.size(0), greater_than_next.size(0),
      jb_emlrtECI);
  }

  if (scores.size(0) == greater_than_next.size(0)) {
    timeBlinderVec.set_size(scores.size(0));
    loop_ub = scores.size(0);
    for (i = 0; i < loop_ub; i++) {
      timeBlinderVec[i] = scores[i] * static_cast<double>(greater_than_next[i]);
    }
  } else {
    binary_expand_op_7(timeBlinderVec, scores, greater_than_next);
  }

  // This checks to make sure that at least one frequency has a
  // threshold exceeding score. If there isn't one (all the scroes
  // are below the threshold), we set the output variables as NaN
  // so that the caller knows nothing was detected.
  // 2021-10-11
  // Update to to set all peak_masked_curr_scores less than the
  // threshold to zero. This wasn't needed when there was one
  // threshold, but with local frequency specific thresholds, we
  // only want threshold positive peaks listed in this vector so
  // the while loop below doesn't try to sort out sub-threshold
  // peaks. This can happen when there is a sub threhold peak that
  // has a higher score than a score at a different frequency that
  // was lower, but exceeded it's local threshold.
  i = thresh.threshVecFine.size(0);
  if ((timeBlinderVec.size(0) != i) && ((timeBlinderVec.size(0) != 1) && (i != 1)))
  {
    emlrtDimSizeImpxCheckR2021b(timeBlinderVec.size(0), i, kb_emlrtECI);
  }

  if (timeBlinderVec.size(0) == thresh.threshVecFine.size(0)) {
    b_freq_mask.set_size(timeBlinderVec.size(0));
    loop_ub = timeBlinderVec.size(0);
    for (i = 0; i < loop_ub; i++) {
      b_freq_mask[i] = (timeBlinderVec[i] >= thresh.threshVecFine[i]);
    }
  } else {
    binary_expand_op_5(b_freq_mask, timeBlinderVec, this);
  }

  if ((timeBlinderVec.size(0) != b_freq_mask.size(0)) && ((timeBlinderVec.size(0)
        != 1) && (b_freq_mask.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(timeBlinderVec.size(0), b_freq_mask.size(0),
      lb_emlrtECI);
  }

  if (timeBlinderVec.size(0) == b_freq_mask.size(0)) {
    loop_ub = timeBlinderVec.size(0);
    for (i = 0; i < loop_ub; i++) {
      timeBlinderVec[i] = timeBlinderVec[i] * static_cast<double>(b_freq_mask[i]);
    }
  } else {
    binary_expand_op_4(timeBlinderVec, b_freq_mask);
  }

  // ------------------------------------------------
  // thresh_hold = thresh;thresh = interp1(obj.stft.f,thresh,Wf);
  i = thresh.threshVecFine.size(0);
  if ((timeBlinderVec.size(0) != i) && ((timeBlinderVec.size(0) != 1) && (i != 1)))
  {
    emlrtDimSizeImpxCheckR2021b(timeBlinderVec.size(0), i, mb_emlrtECI);
  }

  if (timeBlinderVec.size(0) == thresh.threshVecFine.size(0)) {
    score_right_bndry.set_size(timeBlinderVec.size(0));
    loop_ub = timeBlinderVec.size(0);
    for (i = 0; i < loop_ub; i++) {
      score_right_bndry[i] = (timeBlinderVec[i] >= thresh.threshVecFine[i]);
    }

    freqModWarningFlag = coder::internal::allOrAny_anonFcn1(score_right_bndry);
  } else {
    freqModWarningFlag = binary_expand_op_8(timeBlinderVec, this);
  }

  if (!freqModWarningFlag) {
    // all(peak_masked_curr_scores < thresh, 'all')%
    // peak_ind = [];
    peak_ind.set_size(1);
    peak_ind[0] = rtNaN;
    peak.set_size(1);

    // [];
  }

  // Keep doing this loop below while there are scores that exceed
  // the threshold which aren't masked as a valley, +slope, -slope,
  // or previously identified peak/sideband.
  i = thresh.threshVecFine.size(0);
  int exitg1;
  do {
    exitg1 = 0;
    if ((timeBlinderVec.size(0) != i) && ((timeBlinderVec.size(0) != 1) && (i !=
          1))) {
      emlrtDimSizeImpxCheckR2021b(timeBlinderVec.size(0), i, nb_emlrtECI);
    }

    if (timeBlinderVec.size(0) == thresh.threshVecFine.size(0)) {
      score_right_bndry.set_size(timeBlinderVec.size(0));
      loop_ub = timeBlinderVec.size(0);
      for (i1 = 0; i1 < loop_ub; i1++) {
        score_right_bndry[i1] = (timeBlinderVec[i1] >= thresh.threshVecFine[i1]);
      }

      freqModWarningFlag = coder::internal::allOrAny_anonFcn1(score_right_bndry);
    } else {
      freqModWarningFlag = binary_expand_op_8(timeBlinderVec, this);
    }

    if (freqModWarningFlag) {
      // Identify the highest scoring peak of the currently
      // identifed scores.
      t8_con_dec = ((static_cast<int>(p) < 1) || (static_cast<int>(p) >
        peak.size(0)));
      if (t8_con_dec) {
        rtDynamicBoundsError(static_cast<int>(p), 1, peak.size(0), vb_emlrtBCI);
      }

      peak[static_cast<int>(p) - 1] = coder::internal::maximum(timeBlinderVec,
        b_result);
      peak_ind[static_cast<int>(p) - 1] = b_result;

      // Build a mask that highlights all the elements whose time
      // windows share (or are close) to any of the time windows
      // of the pulses associated with the current peak.
      i1 = static_cast<int>(stft_dt);
      if (static_cast<int>(stft_dt) - 1 >= 0) {
        b_loop_ub = S_cols.size(0);
        c_loop_ub = n_freqs;
        d_loop_ub = S_cols.size(0);
        e_loop_ub = S_cols.size(0);
        f_loop_ub = S_cols.size(0);
        g_loop_ub = S_cols.size(0);
        a = peak_ind[static_cast<int>(p) - 1];
        if (a - 1.0 < 1.0) {
          i3 = 0;
          i4 = 1;
          i5 = -1;
        } else {
          if (a - 1.0 != static_cast<int>(a - 1.0)) {
            rtIntegerError(a - 1.0, tb_emlrtDCI);
          }

          i2 = thresh.threshVecFine.size(0);
          if ((static_cast<int>(a - 1.0) < 1) || (static_cast<int>(a - 1.0) > i2))
          {
            rtDynamicBoundsError(static_cast<int>(a - 1.0), 1, i2, te_emlrtBCI);
          }

          i3 = static_cast<int>(a - 1.0) - 1;
          i4 = -1;
          i2 = thresh.threshVecFine.size(0);
          if (i2 < 1) {
            rtDynamicBoundsError(1, 1, i2, ue_emlrtBCI);
          }

          i5 = 0;
        }

        if (a + 1.0 > thresh.threshVecFine.size(0)) {
          i6 = 0;
          i7 = 0;
        } else {
          if (a + 1.0 != static_cast<int>(a + 1.0)) {
            rtIntegerError(a + 1.0, sb_emlrtDCI);
          }

          i2 = thresh.threshVecFine.size(0);
          if ((static_cast<int>(a + 1.0) < 1) || (static_cast<int>(a + 1.0) > i2))
          {
            rtDynamicBoundsError(static_cast<int>(a + 1.0), 1, i2, re_emlrtBCI);
          }

          i6 = static_cast<int>(a + 1.0) - 1;
          i2 = thresh.threshVecFine.size(0);
          i7 = thresh.threshVecFine.size(0);
          if ((i7 < 1) || (i7 > i2)) {
            rtDynamicBoundsError(i7, 1, i2, se_emlrtBCI);
          }
        }

        if (a - 1.0 < 1.0) {
          i8 = 0;
          i9 = 1;
          i10 = -1;
        } else {
          if (a - 1.0 != static_cast<int>(a - 1.0)) {
            rtIntegerError(a - 1.0, rb_emlrtDCI);
          }

          if ((static_cast<int>(a - 1.0) < 1) || (static_cast<int>(a - 1.0) >
               slope_val.size(0))) {
            rtDynamicBoundsError(static_cast<int>(a - 1.0), 1, slope_val.size(0),
                                 pe_emlrtBCI);
          }

          i8 = static_cast<int>(a - 1.0) - 1;
          i9 = -1;
          if (slope_val.size(0) < 1) {
            rtDynamicBoundsError(1, 1, slope_val.size(0), qe_emlrtBCI);
          }

          i10 = 0;
        }

        h_loop_ub = div_s32(i10 - i8, i9);
        if (a + 1.0 > slope_val.size(0)) {
          i11 = 0;
          i12 = 0;
        } else {
          if (a + 1.0 != static_cast<int>(a + 1.0)) {
            rtIntegerError(a + 1.0, qb_emlrtDCI);
          }

          if ((static_cast<int>(a + 1.0) < 1) || (static_cast<int>(a + 1.0) >
               slope_val.size(0))) {
            rtDynamicBoundsError(static_cast<int>(a + 1.0), 1, slope_val.size(0),
                                 ne_emlrtBCI);
          }

          i11 = static_cast<int>(a + 1.0) - 1;
          if (slope_val.size(0) < 1) {
            rtDynamicBoundsError(slope_val.size(0), 1, slope_val.size(0),
                                 oe_emlrtBCI);
          }

          i12 = slope_val.size(0);
        }

        i_loop_ub = i12 - i11;
        b_p = static_cast<int>(p);
      }

      for (int k{0}; k < i1; k++) {
        // This block of code is used to find the number of time
        // windows between the current peak and the others in
        // the same block. It checks the blocks in front and
        // behind
        // n_diff_to_curr_pk is a vector of time window
        // differences between the currently identified peaks and
        // all the other identified time windows in the current
        // block
        a = peak_ind[static_cast<int>(p) - 1];
        if (a != static_cast<int>(a)) {
          rtIntegerError(a, bb_emlrtDCI);
        }

        t8_con_dec = ((static_cast<int>(a) < 1) || (static_cast<int>(a) >
          S_cols.size(0)));
        if (t8_con_dec) {
          rtDynamicBoundsError(static_cast<int>(a), 1, S_cols.size(0),
                               wb_emlrtBCI);
        }

        t8_con_dec = ((static_cast<int>(static_cast<unsigned int>(k) + 1U) < 1) ||
                      (static_cast<int>(static_cast<unsigned int>(k) + 1U) >
                       S_cols.size(1)));
        if (t8_con_dec) {
          rtDynamicBoundsError(static_cast<int>(static_cast<unsigned int>(k) +
            1U), 1, S_cols.size(1), xb_emlrtBCI);
        }

        next_pulse_start = S_cols[(static_cast<int>(a) + S_cols.size(0) * k) - 1];
        b_S_cols.set_size(S_cols.size(0));
        for (i2 = 0; i2 < b_loop_ub; i2++) {
          b_S_cols[i2] = next_pulse_start - S_cols[i2 + S_cols.size(0) * k];
        }

        nx = b_S_cols.size(0);
        timeBlinderVec.set_size(b_S_cols.size(0));
        if (b_S_cols.size(0) > 2147483646) {
          coder::check_forloop_overflow_error();
        }

        for (b_result = 0; b_result < nx; b_result++) {
          timeBlinderVec[b_result] = std::abs(b_S_cols[b_result]);
        }

        n_diff_check_back.set_size(n_freqs);
        n_diff_check_for.set_size(n_freqs);
        for (i2 = 0; i2 < c_loop_ub; i2++) {
          n_diff_check_back[i2] = rtNaN;
          n_diff_check_for[i2] = rtNaN;
        }

        // Remember that the segments are long enough to
        // guarentee K pulses, but can get K+1. If we identified
        // the first or last K peaks, but there is an extra, its
        // side bands might be in this list in nearby frequencies.
        // We need to exclude these like we do the sidebands that
        // are nearby in time. In this case, we want to see if
        // any of the identified peaks are +/-tp+/-tip from the
        // current peak. Here we look a block forward and/or
        // backward at the reported columns of the S matrix that
        // were identified as exceeding the decision threshold
        // and see if those columns are the same as the current
        // blocks identified column. We'll check later in the
        // code to see if these are less than a threshold.
        if (static_cast<double>(k) + 1.0 <= stft_dt - 1.0) {
          // Don't compute forward check when k=n_blks
          if (a != static_cast<int>(a)) {
            rtIntegerError(a, cb_emlrtDCI);
          }

          if ((static_cast<int>(static_cast<unsigned int>(k) + 2U) < 1) || (
               static_cast<int>(static_cast<unsigned int>(k) + 2U) > S_cols.size
               (1))) {
            rtDynamicBoundsError(static_cast<int>(static_cast<unsigned int>(k) +
              2U), 1, S_cols.size(1), yb_emlrtBCI);
          }

          b_S_cols.set_size(S_cols.size(0));
          loop_ub = S_cols.size(0);
          for (i2 = 0; i2 < loop_ub; i2++) {
            b_S_cols[i2] = next_pulse_start - S_cols[i2 + S_cols.size(0) * (k +
              1)];
          }

          nx = b_S_cols.size(0);
          n_diff_check_for.set_size(b_S_cols.size(0));
          if (b_S_cols.size(0) > 2147483646) {
            coder::check_forloop_overflow_error();
          }

          for (b_result = 0; b_result < nx; b_result++) {
            n_diff_check_for[b_result] = std::abs(b_S_cols[b_result]);
          }
        } else if (static_cast<unsigned int>(k) + 1U >= 2U) {
          // Don't compute backward check when k=1
          if (a != static_cast<int>(a)) {
            rtIntegerError(a, ob_emlrtDCI);
          }

          if ((k < 1) || (k > S_cols.size(1))) {
            rtDynamicBoundsError(k, 1, S_cols.size(1), rc_emlrtBCI);
          }

          b_S_cols.set_size(S_cols.size(0));
          loop_ub = S_cols.size(0);
          for (i2 = 0; i2 < loop_ub; i2++) {
            b_S_cols[i2] = next_pulse_start - S_cols[i2 + S_cols.size(0) * (k -
              1)];
          }

          nx = b_S_cols.size(0);
          n_diff_check_back.set_size(b_S_cols.size(0));
          if (b_S_cols.size(0) > 2147483646) {
            coder::check_forloop_overflow_error();
          }

          for (b_result = 0; b_result < nx; b_result++) {
            n_diff_check_back[b_result] = std::abs(b_S_cols[b_result]);
          }
        }

        // There could be instances when a single block contains
        // two pulses, as mentioned above, but if the search is
        // only for one pulse (K = 1) then the if statments above
        // won't run. We need here to check if there are
        // identified scores within the current block that are
        // also one time repetition interval (tip+/tipu) away
        // from the current peak
        if (a != static_cast<int>(a)) {
          rtIntegerError(a, db_emlrtDCI);
        }

        tip_temp = next_pulse_start + b_N;
        tp_temp = tip_temp + b_M;
        slope_pos.set_size(S_cols.size(0));
        for (i2 = 0; i2 < d_loop_ub; i2++) {
          slope_pos[i2] = (S_cols[i2 + S_cols.size(0) * k] < tp_temp);
        }

        if (a != static_cast<int>(a)) {
          rtIntegerError(a, eb_emlrtDCI);
        }

        tp_temp = tip_temp - b_M;
        b_freq_mask.set_size(S_cols.size(0));
        for (i2 = 0; i2 < e_loop_ub; i2++) {
          b_freq_mask[i2] = (S_cols[i2 + S_cols.size(0) * k] > tp_temp);
        }

        if (slope_pos.size(0) != b_freq_mask.size(0)) {
          rtSizeEq1DError(slope_pos.size(0), b_freq_mask.size(0), ob_emlrtECI);
        }

        loop_ub = slope_pos.size(0);
        for (i2 = 0; i2 < loop_ub; i2++) {
          slope_pos[i2] = (slope_pos[i2] && b_freq_mask[i2]);
        }

        if (a != static_cast<int>(a)) {
          rtIntegerError(a, fb_emlrtDCI);
        }

        next_pulse_start -= b_N;
        tp_temp = next_pulse_start - b_M;
        score_right_bndry.set_size(S_cols.size(0));
        for (i2 = 0; i2 < f_loop_ub; i2++) {
          score_right_bndry[i2] = (S_cols[i2 + S_cols.size(0) * k] > tp_temp);
        }

        if (a != static_cast<int>(a)) {
          rtIntegerError(a, gb_emlrtDCI);
        }

        tp_temp = next_pulse_start + b_M;
        b_freq_mask.set_size(S_cols.size(0));
        for (i2 = 0; i2 < g_loop_ub; i2++) {
          b_freq_mask[i2] = (S_cols[i2 + S_cols.size(0) * k] < tp_temp);
        }

        if (score_right_bndry.size(0) != b_freq_mask.size(0)) {
          rtSizeEq1DError(score_right_bndry.size(0), b_freq_mask.size(0),
                          pb_emlrtECI);
        }

        loop_ub = score_right_bndry.size(0);
        for (i2 = 0; i2 < loop_ub; i2++) {
          score_right_bndry[i2] = (score_right_bndry[i2] && b_freq_mask[i2]);
        }

        if ((slope_pos.size(0) != score_right_bndry.size(0)) && ((slope_pos.size
              (0) != 1) && (score_right_bndry.size(0) != 1))) {
          emlrtDimSizeImpxCheckR2021b(slope_pos.size(0), score_right_bndry.size
            (0), qb_emlrtECI);
        }

        if (slope_pos.size(0) == score_right_bndry.size(0)) {
          loop_ub = slope_pos.size(0);
          for (i2 = 0; i2 < loop_ub; i2++) {
            slope_pos[i2] = (slope_pos[i2] || score_right_bndry[i2]);
          }
        } else {
          b_or(slope_pos, score_right_bndry);
        }

        // This code below builds a mask that highlights the
        // sidebands of the peak. It looks for the frequency bin
        // (higher and lower) where the score no longer meets
        // the threshold. If no threshold crossings are found,
        // it assumes the entire frequeny list is a sideband.
        // This happens often in an informed search method when
        // the frequency search has been narrowed to a small
        // band on either side of a known peak.
        // These are the number of frequency bins foward or
        // backward from the peak to the last score>threshold
        if (a - 1.0 < 1.0) {
          i2 = 0;
          b_result = 1;
          wind_end_size = -1;
        } else {
          if (a - 1.0 != static_cast<int>(a - 1.0)) {
            rtIntegerError(a - 1.0, nb_emlrtDCI);
          }

          if ((static_cast<int>(a - 1.0) < 1) || (static_cast<int>(a - 1.0) >
               scores.size(0))) {
            rtDynamicBoundsError(static_cast<int>(a - 1.0), 1, scores.size(0),
                                 pc_emlrtBCI);
          }

          i2 = static_cast<int>(a - 1.0) - 1;
          b_result = -1;
          if (scores.size(0) < 1) {
            rtDynamicBoundsError(1, 1, scores.size(0), qc_emlrtBCI);
          }

          wind_end_size = 0;
        }

        loop_ub = div_s32(wind_end_size - i2, b_result);
        nx = div_s32(i5 - i3, i4) + 1;
        if ((loop_ub + 1 != nx) && ((loop_ub + 1 != 1) && (nx != 1))) {
          emlrtDimSizeImpxCheckR2021b(loop_ub + 1, nx, rb_emlrtECI);
        }

        if (loop_ub + 1 == nx) {
          score_right_bndry.set_size(loop_ub + 1);
          for (wind_end_size = 0; wind_end_size <= loop_ub; wind_end_size++) {
            score_right_bndry[wind_end_size] = (scores[i2 + b_result *
              wind_end_size] < thresh.threshVecFine[i3 + i4 * wind_end_size]);
          }

          nx = coder::c_eml_find(score_right_bndry, (int *)&ii_data);
        } else {
          nx = binary_expand_op_3((int *)&ii_data, scores, i2 + 1, b_result,
            wind_end_size, this, i3 + 1, i4, i5);
        }

        wind_start_size = nx;
        for (i2 = 0; i2 < nx; i2++) {
          wind_start_data = static_cast<double>(ii_data) - 1.0;
        }

        if (a + 1.0 > scores.size(0)) {
          i2 = 0;
          b_result = 0;
        } else {
          if (a + 1.0 != static_cast<int>(a + 1.0)) {
            rtIntegerError(a + 1.0, mb_emlrtDCI);
          }

          if ((static_cast<int>(a + 1.0) < 1) || (static_cast<int>(a + 1.0) >
               scores.size(0))) {
            rtDynamicBoundsError(static_cast<int>(a + 1.0), 1, scores.size(0),
                                 nc_emlrtBCI);
          }

          i2 = static_cast<int>(a + 1.0) - 1;
          if (scores.size(0) < 1) {
            rtDynamicBoundsError(scores.size(0), 1, scores.size(0), oc_emlrtBCI);
          }

          b_result = scores.size(0);
        }

        loop_ub = b_result - i2;
        wind_end_size = i7 - i6;
        if ((loop_ub != wind_end_size) && ((loop_ub != 1) && (wind_end_size != 1)))
        {
          emlrtDimSizeImpxCheckR2021b(loop_ub, wind_end_size, sb_emlrtECI);
        }

        if (loop_ub == wind_end_size) {
          score_right_bndry.set_size(loop_ub);
          for (b_result = 0; b_result < loop_ub; b_result++) {
            score_right_bndry[b_result] = (scores[i2 + b_result] <
              thresh.threshVecFine[i6 + b_result]);
          }

          nx = coder::c_eml_find(score_right_bndry, (int *)&ii_data);
        } else {
          nx = binary_expand_op_2((int *)&ii_data, scores, i2, b_result, this,
            i6, i7);
        }

        wind_end_size = nx;
        for (i2 = 0; i2 < nx; i2++) {
          next_pulse_start = static_cast<double>(ii_data) - 1.0;
        }

        // Here we look for the location where the slope changes.
        // We don't use the -1 like above because we want to be
        // sure to capture the entire saddle between peaks, so
        // we include the point after the transition of the slope
        // sign. If we didn't do this, then the lowest point
        // between the peaks that was still above the threshold
        // wouldn't be included in a sideband mask and might get
        // picked up later as an additional peak.
        score_right_bndry.set_size(div_s32(i10 - i8, i9) + 1);
        for (i2 = 0; i2 <= h_loop_ub; i2++) {
          score_right_bndry[i2] = slope_val[i8 + i9 * i2];
        }

        nx = coder::c_eml_find(score_right_bndry, (int *)&ii_data);
        b_result = nx;
        for (i2 = 0; i2 < nx; i2++) {
          inds_bkwd_2_next_valley_data = ii_data;
        }

        score_right_bndry.set_size(i12 - i11);
        for (i2 = 0; i2 < i_loop_ub; i2++) {
          score_right_bndry[i2] = slope_val[i11 + i2];
        }

        nx = coder::c_eml_find(score_right_bndry, (int *)&ii_data);
        if ((wind_end_size == 0) && (wind_start_size == 0)) {
          // If it can't find a place backwards or forwards
          // that is less than the threshold, the whole thing
          // could be sideband. Often the case for informed
          // search.
          // Alternatively, the interactions of
          // adjacent sidebands might be so large, that there
          // are no adjacent scores that are below the
          // threshold. We need to deal with both of these
          // cases. In the latter, we need to find the
          // frequency bin ahead of and behind the peak where
          // the slope changes and define that as the
          // sidebands. If the slope doesn't change, then we
          // are likely the former case wherein the entire set
          // of scores are side band and we make the mask all
          // true.
          excld_msk_vec.set_size(n_freqs);
          for (i2 = 0; i2 < n_freqs; i2++) {
            excld_msk_vec[i2] = false;
          }

          if ((b_result == 0) && (nx == 0)) {
            excld_msk_vec.set_size(n_freqs);
            for (i2 = 0; i2 < n_freqs; i2++) {
              excld_msk_vec[i2] = true;
            }
          } else if ((b_result == 0) && (nx != 0)) {
            if (a < 1.0) {
              loop_ub = 0;
            } else {
              if (n_freqs < 1) {
                rtDynamicBoundsError(1, 1, n_freqs, cc_emlrtBCI);
              }

              if (a != static_cast<int>(a)) {
                rtIntegerError(a, hb_emlrtDCI);
              }

              if ((static_cast<int>(a) < 1) || (static_cast<int>(a) > n_freqs))
              {
                rtDynamicBoundsError(static_cast<int>(a), 1, n_freqs,
                                     dc_emlrtBCI);
              }

              loop_ub = static_cast<int>(a);
            }

            for (i2 = 0; i2 < loop_ub; i2++) {
              excld_msk_vec[i2] = true;
            }
          } else if ((b_result != 0) && (nx == 0)) {
            if (a > n_freqs) {
              i2 = 0;
              b_result = 0;
            } else {
              if (a != static_cast<int>(a)) {
                rtIntegerError(a, ib_emlrtDCI);
              }

              if ((static_cast<int>(a) < 1) || (static_cast<int>(a) > n_freqs))
              {
                rtDynamicBoundsError(static_cast<int>(a), 1, n_freqs,
                                     ec_emlrtBCI);
              }

              i2 = static_cast<int>(a) - 1;
              if (n_freqs < 1) {
                rtDynamicBoundsError(n_freqs, 1, n_freqs, fc_emlrtBCI);
              }

              b_result = n_freqs;
            }

            loop_ub = b_result - i2;
            for (b_result = 0; b_result < loop_ub; b_result++) {
              excld_msk_vec[i2 + b_result] = true;
            }
          } else if ((b_result != 0) && (nx != 0)) {
            if (ii_data < -static_cast<double>(inds_bkwd_2_next_valley_data)) {
              b_excluded_freq_bands.set_size(1, 0);
            } else {
              loop_ub = ii_data + inds_bkwd_2_next_valley_data;
              b_excluded_freq_bands.set_size(1, loop_ub + 1);
              for (i2 = 0; i2 <= loop_ub; i2++) {
                b_excluded_freq_bands[i2] = -static_cast<double>
                  (inds_bkwd_2_next_valley_data) + static_cast<double>(i2);
              }
            }

            r7.set_size(1, b_excluded_freq_bands.size(1));
            loop_ub = b_excluded_freq_bands.size(1);
            for (i2 = 0; i2 < loop_ub; i2++) {
              next_pulse_start = a + b_excluded_freq_bands[i2];
              if (next_pulse_start != static_cast<int>(next_pulse_start)) {
                rtIntegerError(next_pulse_start, jb_emlrtDCI);
              }

              if ((static_cast<int>(next_pulse_start) < 1) || (static_cast<int>
                   (next_pulse_start) > n_freqs)) {
                rtDynamicBoundsError(static_cast<int>(next_pulse_start), 1,
                                     n_freqs, gc_emlrtBCI);
              }

              r7[i2] = static_cast<int>(next_pulse_start);
            }

            loop_ub = r7.size(1);
            for (i2 = 0; i2 < loop_ub; i2++) {
              excld_msk_vec[r7[i2] - 1] = true;
            }
          }

          // If there was a threhold crossing before and/or after
          // the peak, sort out the sidebands here
        } else {
          excld_msk_vec.set_size(n_freqs);
          for (i2 = 0; i2 < n_freqs; i2++) {
            excld_msk_vec[i2] = false;
          }

          if ((wind_end_size == 0) && (wind_start_size != 0)) {
            // Threshold crossing back was found but not
            // forwards.
            // What is smaller, the distance from the peak to
            // the first entry backwards, or the distance
            // from the peak to the threshold crossing in
            // front of the peak? Use that distance as the
            // 1/2 width of the sideband.
            if (b_result != 1) {
              gb_rtErrorWithMessageID(ub_emlrtRTEI.fName, ub_emlrtRTEI.lineNo);
            }

            t_srch_rng[0] = inds_bkwd_2_next_valley_data;
            t_srch_rng[1] = wind_start_data;
            if ((static_cast<int>(p) < 1) || (static_cast<int>(p) >
                 bandwidth_of_peak.size(0))) {
              rtDynamicBoundsError(static_cast<int>(p), 1,
                                   bandwidth_of_peak.size(0), hc_emlrtBCI);
            }

            bandwidth_of_peak[static_cast<int>(p) - 1] = coder::internal::
              minimum(t_srch_rng);

            // Had to code this way so coder/simulink would know the size of the min operation
          } else if ((wind_end_size != 0) && (wind_start_size == 0)) {
            // Threshold crossing forward was found but not
            // backwards.
            // What is smaller, the distance from the peak to
            // the last entry forwards, or the distance
            // from the peak to the threshold crossing in
            // back of the peak? Use that distance as the
            // 1/2 width of the sideband.
            if (nx != 1) {
              gb_rtErrorWithMessageID(ub_emlrtRTEI.fName, ub_emlrtRTEI.lineNo);
            }

            t_srch_rng[0] = ii_data;
            t_srch_rng[1] = next_pulse_start;
            if ((static_cast<int>(p) < 1) || (static_cast<int>(p) >
                 bandwidth_of_peak.size(0))) {
              rtDynamicBoundsError(static_cast<int>(p), 1,
                                   bandwidth_of_peak.size(0), lc_emlrtBCI);
            }

            bandwidth_of_peak[static_cast<int>(p) - 1] = coder::internal::
              minimum(t_srch_rng);

            // Had to code this way so coder/simulink
            // would know the size of the min operation
          } else {
            // Threshold crossing forward and backward was
            // found.
            // What is smaller, the distance
            // from the peak to the threshold crossing in
            // or the distance from the peak to the nearby
            // valley? Use that distance as the 1/2 width of
            // the sideband. Do this both forwards and
            // backwards.
            if (b_result != 0) {
              if (wind_start_size != 1) {
                gb_rtErrorWithMessageID(ub_emlrtRTEI.fName, ub_emlrtRTEI.lineNo);
              }

              t_srch_rng[0] = wind_start_data;
              t_srch_rng[1] = inds_bkwd_2_next_valley_data;
              wind_start_data = coder::internal::minimum(t_srch_rng);
            }

            if (nx != 0) {
              if (wind_end_size != 1) {
                gb_rtErrorWithMessageID(ub_emlrtRTEI.fName, ub_emlrtRTEI.lineNo);
              }

              t_srch_rng[0] = ii_data;
              t_srch_rng[1] = next_pulse_start;
              next_pulse_start = coder::internal::minimum(t_srch_rng);
            }

            if (wind_end_size != wind_start_size) {
              gb_rtErrorWithMessageID(ub_emlrtRTEI.fName, ub_emlrtRTEI.lineNo);
            }

            for (i2 = 0; i2 < wind_start_size; i2++) {
              varargin_1_data[0] = wind_start_data;
            }

            for (i2 = 0; i2 < wind_end_size; i2++) {
              varargin_1_data[wind_start_size] = next_pulse_start;
            }

            b_result = wind_start_size << 1;
            if ((static_cast<int>(p) < 1) || (static_cast<int>(p) >
                 bandwidth_of_peak.size(0))) {
              rtDynamicBoundsError(static_cast<int>(p), 1,
                                   bandwidth_of_peak.size(0), mc_emlrtBCI);
            }

            b_varargin_1_data.set(&varargin_1_data[0], b_result);
            bandwidth_of_peak[static_cast<int>(p) - 1] = coder::internal::
              unaryMinOrMax_anonFcn1(b_varargin_1_data);
          }

          // Make sure we aren't requesting masking of elements
          // that are outside the bounds of what we have
          // available in the vector
          t8_con_dec = ((static_cast<int>(p) < 1) || (static_cast<int>(p) >
            bandwidth_of_peak.size(0)));
          if (t8_con_dec) {
            rtDynamicBoundsError(static_cast<int>(p), 1, bandwidth_of_peak.size
                                 (0), ic_emlrtBCI);
          }

          t_srch_rng[0] = 1.0;
          next_pulse_start = bandwidth_of_peak[static_cast<int>(p) - 1];
          t_srch_rng[1] = a - next_pulse_start;
          tip_temp = coder::internal::maximum(t_srch_rng);
          t_srch_rng[0] = n_freqs;
          t_srch_rng[1] = a + next_pulse_start;
          next_pulse_start = coder::internal::b_minimum(t_srch_rng);
          if (tip_temp > next_pulse_start) {
            i2 = 0;
            b_result = 0;
          } else {
            if (tip_temp != static_cast<int>(std::floor(tip_temp))) {
              rtIntegerError(tip_temp, kb_emlrtDCI);
            }

            if ((static_cast<int>(tip_temp) < 1) || (static_cast<int>(tip_temp) >
                 n_freqs)) {
              rtDynamicBoundsError(static_cast<int>(tip_temp), 1, n_freqs,
                                   jc_emlrtBCI);
            }

            i2 = static_cast<int>(tip_temp) - 1;
            if (next_pulse_start != static_cast<int>(std::floor(next_pulse_start)))
            {
              rtIntegerError(next_pulse_start, lb_emlrtDCI);
            }

            if ((static_cast<int>(next_pulse_start) < 1) || (static_cast<int>
                 (next_pulse_start) > n_freqs)) {
              rtDynamicBoundsError(static_cast<int>(next_pulse_start), 1,
                                   n_freqs, kc_emlrtBCI);
            }

            b_result = static_cast<int>(next_pulse_start);
          }

          loop_ub = b_result - i2;
          for (b_result = 0; b_result < loop_ub; b_result++) {
            excld_msk_vec[i2 + b_result] = true;
          }
        }

        // Here we build up a mask that incorporates all the
        // peaks and their sidebands that we have identified
        // so far. The msk(:,p+1) entry is here because we are
        // looping through n_blks and are updating the p+1 column
        // each time.
        if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > msk.size(1))) {
          rtDynamicBoundsError(static_cast<int>(p), 1, msk.size(1), ac_emlrtBCI);
        }

        t8_con_dec = ((static_cast<int>(static_cast<double>(p) + 1.0) < 1) || (
          static_cast<int>(static_cast<double>(p) + 1.0) > msk.size(1)));
        if (t8_con_dec) {
          rtDynamicBoundsError(static_cast<int>(static_cast<double>(p) + 1.0), 1,
                               msk.size(1), bc_emlrtBCI);
        }

        b_freq_mask.set_size(timeBlinderVec.size(0));
        loop_ub = timeBlinderVec.size(0);
        for (i2 = 0; i2 < loop_ub; i2++) {
          b_freq_mask[i2] = (timeBlinderVec[i2] <= naive_wind_end);
        }

        r4.set_size(n_diff_check_back.size(0));
        loop_ub = n_diff_check_back.size(0);
        for (i2 = 0; i2 < loop_ub; i2++) {
          r4[i2] = (n_diff_check_back[i2] <= naive_wind_end);
        }

        if ((b_freq_mask.size(0) != r4.size(0)) && ((b_freq_mask.size(0) != 1) &&
             (r4.size(0) != 1))) {
          emlrtDimSizeImpxCheckR2021b(b_freq_mask.size(0), r4.size(0),
            tb_emlrtECI);
        }

        if (b_freq_mask.size(0) == r4.size(0)) {
          loop_ub = b_freq_mask.size(0);
          for (i2 = 0; i2 < loop_ub; i2++) {
            b_freq_mask[i2] = (b_freq_mask[i2] || r4[i2]);
          }
        } else {
          b_or(b_freq_mask, r4);
        }

        r4.set_size(n_diff_check_for.size(0));
        loop_ub = n_diff_check_for.size(0);
        for (i2 = 0; i2 < loop_ub; i2++) {
          r4[i2] = (n_diff_check_for[i2] <= naive_wind_end);
        }

        if ((b_freq_mask.size(0) != r4.size(0)) && ((b_freq_mask.size(0) != 1) &&
             (r4.size(0) != 1))) {
          emlrtDimSizeImpxCheckR2021b(b_freq_mask.size(0), r4.size(0),
            tb_emlrtECI);
        }

        if (b_freq_mask.size(0) == r4.size(0)) {
          loop_ub = b_freq_mask.size(0);
          for (i2 = 0; i2 < loop_ub; i2++) {
            b_freq_mask[i2] = (b_freq_mask[i2] || r4[i2]);
          }
        } else {
          b_or(b_freq_mask, r4);
        }

        if ((excld_msk_vec.size(0) != b_freq_mask.size(0)) &&
            ((excld_msk_vec.size(0) != 1) && (b_freq_mask.size(0) != 1))) {
          emlrtDimSizeImpxCheckR2021b(excld_msk_vec.size(0), b_freq_mask.size(0),
            ub_emlrtECI);
        }

        if (excld_msk_vec.size(0) == b_freq_mask.size(0)) {
          loop_ub = excld_msk_vec.size(0);
          for (i2 = 0; i2 < loop_ub; i2++) {
            excld_msk_vec[i2] = (excld_msk_vec[i2] || b_freq_mask[i2]);
          }
        } else {
          b_or(excld_msk_vec, b_freq_mask);
        }

        if ((excld_msk_vec.size(0) != slope_pos.size(0)) && ((excld_msk_vec.size
              (0) != 1) && (slope_pos.size(0) != 1))) {
          emlrtDimSizeImpxCheckR2021b(excld_msk_vec.size(0), slope_pos.size(0),
            ub_emlrtECI);
        }

        loop_ub = msk.size(0);
        b_freq_mask.set_size(msk.size(0));
        for (i2 = 0; i2 < loop_ub; i2++) {
          b_freq_mask[i2] = (msk[i2 + msk.size(0) * (b_p - 1)] || msk[i2 +
                             msk.size(0) * static_cast<int>(p)]);
        }

        if (excld_msk_vec.size(0) == slope_pos.size(0)) {
          loop_ub = excld_msk_vec.size(0);
          for (i2 = 0; i2 < loop_ub; i2++) {
            excld_msk_vec[i2] = (excld_msk_vec[i2] || slope_pos[i2]);
          }
        } else {
          b_or(excld_msk_vec, slope_pos);
        }

        if ((b_freq_mask.size(0) != excld_msk_vec.size(0)) && ((b_freq_mask.size
              (0) != 1) && (excld_msk_vec.size(0) != 1))) {
          emlrtDimSizeImpxCheckR2021b(b_freq_mask.size(0), excld_msk_vec.size(0),
            vb_emlrtECI);
        }

        if (b_freq_mask.size(0) == excld_msk_vec.size(0)) {
          loop_ub = b_freq_mask.size(0);
          for (i2 = 0; i2 < loop_ub; i2++) {
            b_freq_mask[i2] = (b_freq_mask[i2] || excld_msk_vec[i2]);
          }
        } else {
          b_or(b_freq_mask, excld_msk_vec);
        }

        rtSubAssignSizeCheck(msk.size(), 1, b_freq_mask.size(), 1, wb_emlrtECI);
        loop_ub = b_freq_mask.size(0);
        for (i2 = 0; i2 < loop_ub; i2++) {
          msk[i2 + msk.size(0) * static_cast<int>(p)] = b_freq_mask[i2];
        }
      }

      // Extract the mask for this peak and no others
      if ((static_cast<int>(static_cast<double>(p) + 1.0) < 1) || (static_cast<
           int>(static_cast<double>(p) + 1.0) > msk.size(1))) {
        rtDynamicBoundsError(static_cast<int>(static_cast<double>(p) + 1.0), 1,
                             msk.size(1), sc_emlrtBCI);
      }

      t8_con_dec = ((static_cast<int>(p) < 1) || (static_cast<int>(p) > msk.size
        (1)));
      if (t8_con_dec) {
        rtDynamicBoundsError(static_cast<int>(p), 1, msk.size(1), tc_emlrtBCI);
      }

      b_freq_mask.set_size(msk.size(0));
      loop_ub = msk.size(0);
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_freq_mask[i1] = (msk[i1 + msk.size(0) * static_cast<int>(p)] - msk[i1
                           + msk.size(0) * (static_cast<int>(p) - 1)] != 0);
      }

      rtSubAssignSizeCheck(indiv_msk.size(), 1, b_freq_mask.size(), 1,
                           xb_emlrtECI);
      loop_ub = b_freq_mask.size(0);
      for (i1 = 0; i1 < loop_ub; i1++) {
        indiv_msk[i1 + indiv_msk.size(0) * (static_cast<int>(p) - 1)] =
          b_freq_mask[i1];
      }

      // Update the current scores to exclude peaks and sidebands
      // we have identified so far.
      if ((static_cast<int>(p + 1U) < 1) || (static_cast<int>(p + 1U) > msk.size
           (1))) {
        rtDynamicBoundsError(static_cast<int>(p + 1U), 1, msk.size(1),
                             uc_emlrtBCI);
      }

      b_freq_mask.set_size(msk.size(0));
      loop_ub = msk.size(0);
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_freq_mask[i1] = !msk[i1 + msk.size(0) * static_cast<int>(p)];
      }

      if ((scores.size(0) != b_freq_mask.size(0)) && ((scores.size(0) != 1) &&
           (b_freq_mask.size(0) != 1))) {
        emlrtDimSizeImpxCheckR2021b(scores.size(0), b_freq_mask.size(0),
          yb_emlrtECI);
      }

      if (scores.size(0) == b_freq_mask.size(0)) {
        timeBlinderVec.set_size(scores.size(0));
        loop_ub = scores.size(0);
        for (i1 = 0; i1 < loop_ub; i1++) {
          timeBlinderVec[i1] = scores[i1] * static_cast<double>(b_freq_mask[i1]);
        }
      } else {
        binary_expand_op_7(timeBlinderVec, scores, b_freq_mask);
      }

      // Mask the recently found sidebands
      if ((timeBlinderVec.size(0) != greater_than_next.size(0)) &&
          ((timeBlinderVec.size(0) != 1) && (greater_than_next.size(0) != 1))) {
        emlrtDimSizeImpxCheckR2021b(timeBlinderVec.size(0),
          greater_than_next.size(0), ac_emlrtECI);
      }

      if (timeBlinderVec.size(0) == greater_than_next.size(0)) {
        loop_ub = timeBlinderVec.size(0);
        for (i1 = 0; i1 < loop_ub; i1++) {
          timeBlinderVec[i1] = timeBlinderVec[i1] * static_cast<double>
            (greater_than_next[i1]);
        }
      } else {
        binary_expand_op_4(timeBlinderVec, greater_than_next);
      }

      // Mask to only look at peaks
      i1 = thresh.threshVecFine.size(0);
      if ((timeBlinderVec.size(0) != i1) && ((timeBlinderVec.size(0) != 1) &&
           (i1 != 1))) {
        emlrtDimSizeImpxCheckR2021b(timeBlinderVec.size(0), i1, bc_emlrtECI);
      }

      if (timeBlinderVec.size(0) == thresh.threshVecFine.size(0)) {
        b_freq_mask.set_size(timeBlinderVec.size(0));
        loop_ub = timeBlinderVec.size(0);
        for (i1 = 0; i1 < loop_ub; i1++) {
          b_freq_mask[i1] = (timeBlinderVec[i1] >= thresh.threshVecFine[i1]);
        }
      } else {
        binary_expand_op_5(b_freq_mask, timeBlinderVec, this);
      }

      if ((timeBlinderVec.size(0) != b_freq_mask.size(0)) &&
          ((timeBlinderVec.size(0) != 1) && (b_freq_mask.size(0) != 1))) {
        emlrtDimSizeImpxCheckR2021b(timeBlinderVec.size(0), b_freq_mask.size(0),
          cc_emlrtECI);
      }

      if (timeBlinderVec.size(0) == b_freq_mask.size(0)) {
        loop_ub = timeBlinderVec.size(0);
        for (i1 = 0; i1 < loop_ub; i1++) {
          timeBlinderVec[i1] = timeBlinderVec[i1] * static_cast<double>
            (b_freq_mask[i1]);
        }
      } else {
        binary_expand_op_4(timeBlinderVec, b_freq_mask);
      }

      // Eliminate non-threshold exceeding scores from consideration
      p++;
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  // Clean up the msk and indiv_mask so their columns align with
  // n_pulsegroup_found.
  r.set_size(msk.size(0), msk.size(1));
  for (i = 0; i < nRowsOfS; i++) {
    r[i] = msk[i];
  }

  coder::g_circshift(r);
  if (static_cast<int>(p - 1U) >= 1) {
    if (r.size(1) < 1) {
      rtDynamicBoundsError(1, 1, r.size(1), vc_emlrtBCI);
    }

    if ((static_cast<int>(static_cast<double>(p) - 1.0) < 1) || (static_cast<int>
         (static_cast<double>(p) - 1.0) > r.size(1))) {
      rtDynamicBoundsError(static_cast<int>(static_cast<double>(p) - 1.0), 1,
                           r.size(1), wc_emlrtBCI);
    }
  }

  if (static_cast<int>(p - 1U) < 1) {
    loop_ub = 0;
  } else {
    if (indiv_msk.size(1) < 1) {
      rtDynamicBoundsError(1, 1, indiv_msk.size(1), le_emlrtBCI);
    }

    if ((static_cast<int>(p - 1U) < 1) || (static_cast<int>(p - 1U) >
         indiv_msk.size(1))) {
      rtDynamicBoundsError(static_cast<int>(p - 1U), 1, indiv_msk.size(1),
                           me_emlrtBCI);
    }

    loop_ub = static_cast<int>(p - 1U);
  }

  b_result = indiv_msk.size(0);
  for (i = 0; i < loop_ub; i++) {
    for (i1 = 0; i1 < b_result; i1++) {
      indiv_msk[i1 + b_result * i] = indiv_msk[i1 + indiv_msk.size(0) * i];
    }
  }

  indiv_msk.set_size(indiv_msk.size(0), loop_ub);
  if (peak_ind.size(0) < 1) {
    rtDynamicBoundsError(1, 1, peak_ind.size(0), xc_emlrtBCI);
  }

  if ((!std::isnan(peak_ind[0])) && (static_cast<int>(p - 1U) > 0)) {
    // Only update from NaN if there were some found.
    if (peak_ind.size(0) < 1) {
      rtDynamicBoundsError(1, 1, peak_ind.size(0), yc_emlrtBCI);
    }

    if ((static_cast<int>(static_cast<double>(p) - 1.0) < 1) || (static_cast<int>
         (static_cast<double>(p) - 1.0) > peak_ind.size(0))) {
      rtDynamicBoundsError(static_cast<int>(static_cast<double>(p) - 1.0), 1,
                           peak_ind.size(0), ad_emlrtBCI);
    }

    sizes[0] = 1;
    sizes[1] = static_cast<int>(p - 1U);
    coder::internal::indexShapeCheck(peak_ind.size(0), sizes);
    peak_ind.set_size(static_cast<int>(p - 1U));
  }

  // Each row of msk is a mask that isolates the elements of the
  // yw_max_all_freq vector associated with that column's peak and all
  // higher power peaks. For exampl msk(:,2) provides a mask that
  // highlights which elements of yw_max_all_freq are associated in
  // time with the second highest peak and the first highest peak.
  // Plotting scores.*~msk(:,2) will plot all of the scores of
  // yw_max_all_freq that are not associated in time with the first
  // or second highest power peak.
  //             %% CODE FOR REPORTING A CANDIDATE PULSE AT ALL THE FREQUENCY
  // BINS WITHOUTH DOING THE THRESHOLDING.
  // Preallocate cur_pl matrix
  tp_temp = makepulsestruc(expl_temp.t_next, expl_temp.mode, tip_temp,
    next_pulse_start, a, stft_dt, t_lastknown, timetol, wind_start_data,
    naive_wind_end, freqModWarningFlag, t8_con_dec);
  expl_temp.con_dec = t8_con_dec;
  expl_temp.det_dec = freqModWarningFlag;
  expl_temp.fend = naive_wind_end;
  expl_temp.fstart = wind_start_data;
  expl_temp.fp = timetol;
  expl_temp.t_f = t_lastknown;
  expl_temp.t_0 = stft_dt;
  expl_temp.yw = a;
  expl_temp.SNR = next_pulse_start;
  expl_temp.P = tip_temp;
  expl_temp.A = tp_temp;
  coder::repmat(expl_temp, static_cast<double>(yw_max_all_freq.size(0)),
                static_cast<double>(yw_max_all_freq.size(1)), pl_out);

  // Create a frequency array that accounts for the masking that
  // was done to reduce the frequency space.
  nx = freq_mask.size(0) - 1;
  b_result = 0;
  for (int k{0}; k <= nx; k++) {
    if (freq_mask[k]) {
      b_result++;
    }
  }

  r5.set_size(b_result);
  b_result = 0;
  for (int k{0}; k <= nx; k++) {
    if (freq_mask[k]) {
      r5[b_result] = k;
      b_result++;
    }
  }

  nx = Wf.size(0);
  loop_ub = r5.size(0);
  for (i = 0; i < loop_ub; i++) {
    if (r5[i] > nx - 1) {
      rtDynamicBoundsError(r5[i], 0, nx - 1, bd_emlrtBCI);
    }
  }

  // t_found here is the start of the pulse - not the center like
  // in the time stamps in the stft, which are the centers of the
  // windows. The dt_stft/2 term offfset would affect both the first
  // and second terms of the equation below and therefore cancel.
  refmat.set_size(yw_max_all_freq.size(0), yw_max_all_freq.size(1));
  for (i = 0; i < loop_ub_tmp; i++) {
    refmat[i] = rtNaN;
  }

  // The lines below effectively do the following operation:
  //     t_found(freq_mask,:)    = obj.stft.t(S_cols(freq_mask,:))-obj.stft.t(1)+obj.t_0;
  // but in a way that doesn't generate errors in the C++ generated
  // executable for cases when S_cols_freq_mask goes from an nxK
  // matrix to a 1xK matrix. This could sometimes happen when
  // switching between values of tip mid-processing through changes
  // to the interpulse spec. Coder had assumed at compile time that
  // the result of S_cols(freq_mask,:) was a matrix and then would
  // error our it it became a row vector at runtime. This method
  // does everythe as a vector input.
  loop_ub = r5.size(0);
  for (i = 0; i < loop_ub; i++) {
    if (r5[i] > S_cols.size(0) - 1) {
      rtDynamicBoundsError(r5[i], 0, S_cols.size(0) - 1, cd_emlrtBCI);
    }
  }

  if (loop_ub_tmp < 1) {
    b_excluded_freq_bands.set_size(1, 0);
  } else {
    b_excluded_freq_bands.set_size(1, loop_ub_tmp);
    loop_ub = loop_ub_tmp - 1;
    for (i = 0; i <= loop_ub; i++) {
      b_excluded_freq_bands[i] = static_cast<double>(i) + 1.0;
    }
  }

  t_srch_rng[0] = yw_max_all_freq.size(0);
  t_srch_rng[1] = yw_max_all_freq.size(1);
  coder::internal::assertValidSizeArg(t_srch_rng);
  nx = 1;
  if (b_excluded_freq_bands.size(1) > 1) {
    nx = b_excluded_freq_bands.size(1);
  }

  b_result = b_excluded_freq_bands.size(1);
  if (b_result >= nx) {
    nx = b_result;
  }

  if (yw_max_all_freq.size(0) > nx) {
    k_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }

  if (yw_max_all_freq.size(1) > nx) {
    k_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }

  if (yw_max_all_freq.size(0) * yw_max_all_freq.size(1) !=
      b_excluded_freq_bands.size(1)) {
    l_rtErrorWithMessageID(o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
  }

  loop_ub = r5.size(0);
  for (i = 0; i < loop_ub; i++) {
    if (r5[i] > yw_max_all_freq.size(0) - 1) {
      rtDynamicBoundsError(r5[i], 0, yw_max_all_freq.size(0) - 1, dd_emlrtBCI);
    }
  }

  sizes[0] = yw_max_all_freq.size(0);
  r6.set_size(r5.size(0), yw_max_all_freq.size(1));
  loop_ub = yw_max_all_freq.size(1);
  for (i = 0; i < loop_ub; i++) {
    nx = r5.size(0);
    for (i1 = 0; i1 < nx; i1++) {
      i2 = static_cast<int>(b_excluded_freq_bands[r5[i1] + sizes[0] * i]);
      if (i2 > loop_ub_tmp) {
        rtDynamicBoundsError(i2, 1, loop_ub_tmp, ed_emlrtBCI);
      }

      r6[i1 + r6.size(0) * i] = i2;
    }
  }

  c_S_cols.set_size(r5.size(0), S_cols.size(1));
  loop_ub = S_cols.size(1);
  for (i = 0; i < loop_ub; i++) {
    nx = r5.size(0);
    for (i1 = 0; i1 < nx; i1++) {
      c_S_cols[i1 + c_S_cols.size(0) * i] = S_cols[r5[i1] + S_cols.size(0) * i];
    }
  }

  b_result = r5.size(0) * S_cols.size(1);
  nx = stft->t.size(0);
  timeBlinderVec.set_size(b_result);
  for (i = 0; i < b_result; i++) {
    a = c_S_cols[i];
    if (a != static_cast<int>(std::floor(a))) {
      rtIntegerError(a, pb_emlrtDCI);
    }

    if ((static_cast<int>(a) < 1) || (static_cast<int>(a) > nx)) {
      rtDynamicBoundsError(static_cast<int>(a), 1, nx, fd_emlrtBCI);
    }

    timeBlinderVec[i] = stft->t[static_cast<int>(a) - 1];
  }

  loop_ub = r6.size(0) * r6.size(1);
  if (loop_ub != timeBlinderVec.size(0)) {
    rtSizeEq1DError(loop_ub, timeBlinderVec.size(0), dc_emlrtECI);
  }

  i = stft->t.size(0);
  if (i < 1) {
    rtDynamicBoundsError(1, 1, i, gd_emlrtBCI);
  }

  next_pulse_start = stft->t[0];
  for (i = 0; i < loop_ub; i++) {
    refmat[r6[i] - 1] = (timeBlinderVec[i] - next_pulse_start) + t_0;
  }

  i = Wf.size(0);
  if (i < 2) {
    rtDynamicBoundsError(2, 1, i, hd_emlrtBCI);
  }

  i = Wf.size(0);
  if (i < 1) {
    rtDynamicBoundsError(1, 1, i, id_emlrtBCI);
  }

  i = Wf.size(0);
  if (i < 2) {
    rtDynamicBoundsError(2, 1, i, jd_emlrtBCI);
  }

  i = Wf.size(0);
  if (i < 1) {
    rtDynamicBoundsError(1, 1, i, kd_emlrtBCI);
  }

  next_pulse_start = (Wf[1] - Wf[0]) / 2.0;
  n_diff_check_back.set_size(Wf.size(0));
  loop_ub = Wf.size(0);
  timeBlinderVec.set_size(Wf.size(0));
  for (i = 0; i < loop_ub; i++) {
    a = Wf[i];
    n_diff_check_back[i] = a - next_pulse_start;
    timeBlinderVec[i] = a + next_pulse_start;
  }

  if (timeBlinderVec.size(0) != n_diff_check_back.size(0)) {
    gb_rtErrorWithMessageID(ub_emlrtRTEI.fName, ub_emlrtRTEI.lineNo);
  }

  excluded_freq_bands.set_size(n_diff_check_back.size(0), 2);
  loop_ub = n_diff_check_back.size(0);
  for (i = 0; i < loop_ub; i++) {
    excluded_freq_bands[i] = n_diff_check_back[i];
    excluded_freq_bands[i + excluded_freq_bands.size(0)] = timeBlinderVec[i];
  }

  // Build out the pulse object for each one found
  i = yw_max_all_freq.size(1);
  for (int k{0}; k < i; k++) {
    for (nx = 0; nx < n_freqs; nx++) {
      if (nx + 1 > refmat.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, refmat.size(0), ld_emlrtBCI);
      }

      if (k + 1 > refmat.size(1)) {
        rtDynamicBoundsError(k + 1, 1, refmat.size(1), ld_emlrtBCI);
      }

      next_pulse_start = refmat[nx + refmat.size(0) * k];
      t_srch_rng[0] = ((next_pulse_start + ps_pos->t_ip) - ps_pos->t_ipu) -
        ps_pos->t_ipj;
      if (nx + 1 > refmat.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, refmat.size(0), md_emlrtBCI);
      }

      if (k + 1 > refmat.size(1)) {
        rtDynamicBoundsError(k + 1, 1, refmat.size(1), md_emlrtBCI);
      }

      t_srch_rng[1] = ((next_pulse_start + ps_pos->t_ip) + ps_pos->t_ipu) +
        ps_pos->t_ipj;
      if (nx + 1 > searchmat.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, searchmat.size(0), nd_emlrtBCI);
      }

      if (k + 1 > searchmat.size(1)) {
        rtDynamicBoundsError(k + 1, 1, searchmat.size(1), od_emlrtBCI);
      }

      if (nx + 1 > yw_max_all_freq.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, yw_max_all_freq.size(0), pd_emlrtBCI);
      }

      if (k + 1 > yw_max_all_freq.size(1)) {
        rtDynamicBoundsError(k + 1, 1, yw_max_all_freq.size(1), qd_emlrtBCI);
      }

      if (nx + 1 > signalPlusNoisePSD.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, signalPlusNoisePSD.size(0), rd_emlrtBCI);
      }

      if (k + 1 > signalPlusNoisePSD.size(1)) {
        rtDynamicBoundsError(k + 1, 1, signalPlusNoisePSD.size(1), sd_emlrtBCI);
      }

      if (nx + 1 > refmat.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, refmat.size(0), td_emlrtBCI);
      }

      if (k + 1 > refmat.size(1)) {
        rtDynamicBoundsError(k + 1, 1, refmat.size(1), ud_emlrtBCI);
      }

      if (nx + 1 > refmat.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, refmat.size(0), vd_emlrtBCI);
      }

      if (k + 1 > refmat.size(1)) {
        rtDynamicBoundsError(k + 1, 1, refmat.size(1), wd_emlrtBCI);
      }

      i1 = Wf.size(0);
      if (nx + 1 > i1) {
        rtDynamicBoundsError(nx + 1, 1, i1, xd_emlrtBCI);
      }

      if (nx + 1 > excluded_freq_bands.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, excluded_freq_bands.size(0), yd_emlrtBCI);
      }

      if (nx + 1 > pl_out.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, pl_out.size(0), ae_emlrtBCI);
      }

      if (k + 1 > pl_out.size(1)) {
        rtDynamicBoundsError(k + 1, 1, pl_out.size(1), be_emlrtBCI);
      }

      b_makepulsestruc(searchmat[nx + searchmat.size(0) * k], yw_max_all_freq[nx
                       + yw_max_all_freq.size(0) * k], signalPlusNoisePSD[nx +
                       signalPlusNoisePSD.size(0) * k], next_pulse_start,
                       next_pulse_start + ps_pre->t_p, t_srch_rng, Wf[nx],
                       excluded_freq_bands[nx], excluded_freq_bands[nx +
                       excluded_freq_bands.size(0)], &pl_out[nx + pl_out.size(0)
                       * k]);

      // %NaN,...
      if (nx + 1 > pl_out.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, pl_out.size(0), ce_emlrtBCI);
      }

      if (k + 1 > pl_out.size(1)) {
        rtDynamicBoundsError(k + 1, 1, pl_out.size(1), de_emlrtBCI);
      }

      pl_out[nx + pl_out.size(0) * k].con_dec = false;

      // Confirmation status
      if (nx + 1 > scores.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, scores.size(0), ee_emlrtBCI);
      }

      i1 = thresh.threshVecFine.size(0);
      if (nx + 1 > i1) {
        rtDynamicBoundsError(nx + 1, 1, i1, fe_emlrtBCI);
      }

      if (scores[nx] >= thresh.threshVecFine[nx]) {
        // scores(j)>=thresh
        if (nx + 1 > pl_out.size(0)) {
          rtDynamicBoundsError(nx + 1, 1, pl_out.size(0), ge_emlrtBCI);
        }

        if (k + 1 > pl_out.size(1)) {
          rtDynamicBoundsError(k + 1, 1, pl_out.size(1), he_emlrtBCI);
        }

        pl_out[nx + pl_out.size(0) * k].det_dec = true;
      }
    }
  }

  std::printf("Frequencies are:\n");
  std::fflush(stdout);
  i = Wf.size(0);
  for (int k{0}; k < i; k++) {
    i1 = Wf.size(0);
    if (k + 1 > i1) {
      rtDynamicBoundsError(k + 1, 1, i1, ie_emlrtBCI);
    }

    std::printf("%.6f,", Wf[k]);
    std::fflush(stdout);
  }

  std::printf("\n");
  std::fflush(stdout);
  std::printf("Threshold vector is equal to:\n");
  std::fflush(stdout);
  i = thresh.threshVecFine.size(0);
  for (int k{0}; k < i; k++) {
    i1 = thresh.threshVecFine.size(0);
    if (k + 1 > i1) {
      rtDynamicBoundsError(k + 1, 1, i1, je_emlrtBCI);
    }

    std::printf("%f,", thresh.threshVecFine[k]);
    std::fflush(stdout);
  }

  std::printf("\n");
  std::fflush(stdout);
  std::printf("Scores vector is equal to:\n");
  std::fflush(stdout);
  i = scores.size(0);
  for (int k{0}; k < i; k++) {
    if (k + 1 > scores.size(0)) {
      rtDynamicBoundsError(k + 1, 1, scores.size(0), ke_emlrtBCI);
    }

    std::printf("%f,", scores[k]);
    std::fflush(stdout);
  }

  std::printf("\n");
  std::fflush(stdout);
  next_pulse_start = coder::toc() - previousToc;
  std::printf("complete. Elapsed time: %f seconds \n", next_pulse_start);
  std::fflush(stdout);
  coder::toc();
}

//
// Arguments    : const coder::array<c_struct_T, 2U> &candidateList
//                const coder::array<double, 1U> &peakIndexList
// Return Type  : double
//
double waveform::selectpeakindex(const coder::array<c_struct_T, 2U>
  &candidateList, const coder::array<double, 1U> &peakIndexList) const
{
  static rtBoundsCheckInfo ab_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1866,                              // lineNo
    47,                                // colNo
    "selectedIndex",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ac_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1910,                              // lineNo
    82,                                // colNo
    "candidateList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo bb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1832,                              // lineNo
    56,                                // colNo
    "candidateList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo bc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1910,                              // lineNo
    66,                                // colNo
    "peakIndexList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo cb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1832,                              // lineNo
    70,                                // colNo
    "peakIndexList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo cc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1910,                              // lineNo
    52,                                // colNo
    "candidateList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo db_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1832,                              // lineNo
    126,                               // colNo
    "peakIndexList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo dc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1918,                              // lineNo
    82,                                // colNo
    "candidateList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo eb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1832,                              // lineNo
    112,                               // colNo
    "obj.ps_pre.clst",                 // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ec_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1918,                              // lineNo
    66,                                // colNo
    "peakIndexList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo fb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1832,                              // lineNo
    129,                               // colNo
    "obj.ps_pre.clst",                 // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo fc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1918,                              // lineNo
    52,                                // colNo
    "candidateList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo gb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1833,                              // lineNo
    39,                                // colNo
    "interPulseAligned",               // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo gc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1832,                              // lineNo
    73,                                // colNo
    "candidateList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo hb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1837,                              // lineNo
    54,                                // colNo
    "candidateList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo hc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1832,                              // lineNo
    76,                                // colNo
    "candidateList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ib_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1867,                              // lineNo
    78,                                // colNo
    "candidateList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo jb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1867,                              // lineNo
    62,                                // colNo
    "peakIndexList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo kb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1867,                              // lineNo
    48,                                // colNo
    "candidateList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo lb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1874,                              // lineNo
    51,                                // colNo
    "selectedIndex",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo mb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1875,                              // lineNo
    82,                                // colNo
    "candidateList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo nb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1875,                              // lineNo
    66,                                // colNo
    "peakIndexList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ob_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1875,                              // lineNo
    52,                                // colNo
    "candidateList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo pb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1883,                              // lineNo
    82,                                // colNo
    "candidateList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo qb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1883,                              // lineNo
    66,                                // colNo
    "peakIndexList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo rb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1883,                              // lineNo
    52,                                // colNo
    "candidateList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo sb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1891,                              // lineNo
    82,                                // colNo
    "candidateList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo tb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1891,                              // lineNo
    66,                                // colNo
    "peakIndexList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ub_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1891,                              // lineNo
    52,                                // colNo
    "candidateList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo vb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1901,                              // lineNo
    51,                                // colNo
    "selectedIndex",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo wb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1902,                              // lineNo
    82,                                // colNo
    "candidateList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo xb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1902,                              // lineNo
    66,                                // colNo
    "peakIndexList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo yb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1902,                              // lineNo
    52,                                // colNo
    "candidateList",                   // aName
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtDoubleCheckInfo s_emlrtDCI{ 1832,// lineNo
    56,                                // colNo
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo t_emlrtDCI{ 1832,// lineNo
    112,                               // colNo
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo u_emlrtDCI{ 1837,// lineNo
    54,                                // colNo
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo v_emlrtDCI{ 1832,// lineNo
    76,                                // colNo
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtEqualityCheckInfo g_emlrtECI{ 2,// nDims
    1833,                              // lineNo
    48,                                // colNo
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo h_emlrtECI{ 1,// nDims
    1870,                              // lineNo
    24,                                // colNo
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo i_emlrtECI{ 1,// nDims
    1873,                              // lineNo
    42,                                // colNo
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo j_emlrtECI{ 1,// nDims
    1877,                              // lineNo
    29,                                // colNo
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo k_emlrtECI{ 1,// nDims
    1881,                              // lineNo
    45,                                // colNo
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo l_emlrtECI{ 1,// nDims
    1885,                              // lineNo
    29,                                // colNo
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  static rtEqualityCheckInfo m_emlrtECI{ 1,// nDims
    1908,                              // lineNo
    45,                                // colNo
    "waveform/selectpeakindex",        // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m"// pName
  };

  coder::array<c_struct_T, 2U> b_candidateList;
  coder::array<c_struct_T, 2U> structure;
  coder::array<double, 2U> deltaTimeFromPrev;
  coder::array<double, 2U> r;
  coder::array<double, 2U> y;
  coder::array<double, 1U> sumScores;
  coder::array<double, 1U> x_tmp;
  coder::array<boolean_T, 2U> b_x;
  coder::array<boolean_T, 2U> r1;
  coder::array<boolean_T, 2U> r2;
  coder::array<boolean_T, 1U> c_x;
  coder::array<boolean_T, 1U> interPulseAligned;
  coder::array<boolean_T, 1U> likelyCaughSingleBigPeak;
  double d;
  double interpulseTimeRangeMax;
  double interpulseTimeRangeMin;
  double selectedIndex;
  int b_peakIndexList[2];
  int b_i1;
  int i;
  int i1;
  int ii_data;
  int j;
  int maxdimlen;
  int resultSize_idx_1;
  boolean_T exitg1;
  boolean_T overflow;
  interpulseTimeRangeMin = (ps_pre->t_ip - ps_pre->t_ipu) - ps_pre->t_ipj;
  interpulseTimeRangeMax = (ps_pre->t_ip + ps_pre->t_ipu) + ps_pre->t_ipj;
  interPulseAligned.set_size(peakIndexList.size(0));
  i1 = peakIndexList.size(0);
  for (i = 0; i < i1; i++) {
    interPulseAligned[i] = false;
  }

  if (ps_pre->clst.size(0) * ps_pre->clst.size(1) != 1) {
    // There is a previous candidate list
    i = peakIndexList.size(0);
    if (peakIndexList.size(0) - 1 >= 0) {
      d = (static_cast<double>(candidateList.size(1)) - K) + 2.0;
      if (d < 1.0) {
        ii_data = 0;
      } else {
        if (candidateList.size(1) < 1) {
          rtDynamicBoundsError(1, 1, candidateList.size(1), gc_emlrtBCI);
        }

        if (d != static_cast<int>(std::floor(d))) {
          rtIntegerError(d, v_emlrtDCI);
        }

        if ((static_cast<int>(d) < 1) || (static_cast<int>(d) >
             candidateList.size(1))) {
          rtDynamicBoundsError(static_cast<int>(d), 1, candidateList.size(1),
                               hc_emlrtBCI);
        }

        ii_data = static_cast<int>(d);
      }
    }

    for (int b_i{0}; b_i < i; b_i++) {
      if (b_i + 1 > peakIndexList.size(0)) {
        rtDynamicBoundsError(b_i + 1, 1, peakIndexList.size(0), cb_emlrtBCI);
      }

      d = peakIndexList[b_i];
      j = static_cast<int>(std::floor(d));
      if (d != j) {
        rtIntegerError(d, s_emlrtDCI);
      }

      if ((d < 1.0) || (static_cast<int>(d) > candidateList.size(0))) {
        rtDynamicBoundsError(static_cast<int>(d), 1, candidateList.size(0),
                             bb_emlrtBCI);
      }

      b_candidateList.set_size(1, ii_data);
      for (b_i1 = 0; b_i1 < ii_data; b_i1++) {
        b_candidateList[b_i1] = candidateList[(static_cast<int>
          (peakIndexList[b_i]) + candidateList.size(0) * b_i1) - 1];
      }

      coder::internal::b_horzcatStructList(b_candidateList, deltaTimeFromPrev);
      deltaTimeFromPrev.set_size(1, deltaTimeFromPrev.size(1));
      i1 = deltaTimeFromPrev.size(1) - 1;
      for (b_i1 = 0; b_i1 <= i1; b_i1++) {
        resultSize_idx_1 = ps_pre->clst.size(0);
        if (b_i + 1 > peakIndexList.size(0)) {
          rtDynamicBoundsError(b_i + 1, 1, peakIndexList.size(0), db_emlrtBCI);
        }

        if (static_cast<int>(d) != j) {
          rtIntegerError(d, t_emlrtDCI);
        }

        if (static_cast<int>(d) > resultSize_idx_1) {
          rtDynamicBoundsError(static_cast<int>(d), 1, resultSize_idx_1,
                               eb_emlrtBCI);
        }

        resultSize_idx_1 = ps_pre->clst.size(1);
        maxdimlen = ps_pre->clst.size(1);
        if ((maxdimlen < 1) || (maxdimlen > resultSize_idx_1)) {
          rtDynamicBoundsError(maxdimlen, 1, resultSize_idx_1, fb_emlrtBCI);
        }

        deltaTimeFromPrev[b_i1] = deltaTimeFromPrev[b_i1] - ps_pre->clst[(
          static_cast<int>(d) + ps_pre->clst.size(0) * (maxdimlen - 1)) - 1].t_0;
      }

      r1.set_size(1, deltaTimeFromPrev.size(1));
      i1 = deltaTimeFromPrev.size(1);
      r2.set_size(1, deltaTimeFromPrev.size(1));
      for (j = 0; j < i1; j++) {
        d = deltaTimeFromPrev[j];
        r1[j] = (d < interpulseTimeRangeMax);
        r2[j] = (d > interpulseTimeRangeMin);
      }

      if (r1.size(1) != r2.size(1)) {
        rtSizeEqNDCheck(r1.size(), r2.size(), g_emlrtECI);
      }

      b_x.set_size(1, r1.size(1));
      i1 = r1.size(1);
      for (j = 0; j < i1; j++) {
        b_x[j] = (r1[j] && r2[j]);
      }

      resultSize_idx_1 = b_x.size(1);
      if (b_i + 1 > interPulseAligned.size(0)) {
        rtDynamicBoundsError(b_i + 1, 1, interPulseAligned.size(0), gb_emlrtBCI);
      }

      c_x = b_x.reshape(resultSize_idx_1);
      interPulseAligned[b_i] = coder::internal::allOrAny_anonFcn1(c_x);
    }
  }

  structure.set_size(peakIndexList.size(0), candidateList.size(1));
  i1 = candidateList.size(1);
  for (i = 0; i < i1; i++) {
    ii_data = peakIndexList.size(0);
    for (j = 0; j < ii_data; j++) {
      if (peakIndexList[j] != static_cast<int>(std::floor(peakIndexList[j]))) {
        rtIntegerError(peakIndexList[j], u_emlrtDCI);
      }

      b_i1 = static_cast<int>(peakIndexList[j]);
      if ((b_i1 < 1) || (b_i1 > candidateList.size(0))) {
        rtDynamicBoundsError(b_i1, 1, candidateList.size(0), hb_emlrtBCI);
      }

      structure[j + structure.size(0) * i] = candidateList[(b_i1 +
        candidateList.size(0) * i) - 1];
    }
  }

  maxdimlen = peakIndexList.size(0) * candidateList.size(1);
  if (maxdimlen == 0) {
    resultSize_idx_1 = 0;
  } else {
    resultSize_idx_1 = maxdimlen;
    if (maxdimlen > 2147483646) {
      coder::check_forloop_overflow_error();
    }
  }

  r.set_size(1, resultSize_idx_1);
  for (int b_i{0}; b_i < maxdimlen; b_i++) {
    r[b_i] = structure[b_i].yw;
  }

  interpulseTimeRangeMin = K;
  coder::internal::assertValidSizeArg(static_cast<double>(peakIndexList.size(0)));
  coder::internal::assertValidSizeArg(interpulseTimeRangeMin);
  maxdimlen = 1;
  if (r.size(1) > 1) {
    maxdimlen = r.size(1);
  }

  resultSize_idx_1 = r.size(1);
  if (resultSize_idx_1 >= maxdimlen) {
    maxdimlen = resultSize_idx_1;
  }

  if (peakIndexList.size(0) > maxdimlen) {
    k_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }

  if (static_cast<int>(interpulseTimeRangeMin) > maxdimlen) {
    k_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }

  if (static_cast<int>(interpulseTimeRangeMin) < 0) {
    jb_rtErrorWithMessageID(yb_emlrtRTEI.fName, yb_emlrtRTEI.lineNo);
  }

  i1 = peakIndexList.size(0) * static_cast<int>(interpulseTimeRangeMin);
  if (i1 != r.size(1)) {
    l_rtErrorWithMessageID(o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
  }

  b_peakIndexList[0] = peakIndexList.size(0);
  resultSize_idx_1 = static_cast<int>(K);
  deltaTimeFromPrev = r.reshape(b_peakIndexList[0], resultSize_idx_1);
  coder::sum(deltaTimeFromPrev, sumScores);
  if (K > 1.0) {
    coder::repmat(sumScores, K, y);
    b_peakIndexList[0] = peakIndexList.size(0);
    deltaTimeFromPrev = r.reshape(b_peakIndexList[0], resultSize_idx_1);
    coder::internal::assertCompatibleDims(deltaTimeFromPrev, y);
    if ((peakIndexList.size(0) == y.size(0)) && (static_cast<int>(K) == y.size(1)))
    {
      b_x.set_size(peakIndexList.size(0), resultSize_idx_1);
      for (i = 0; i < i1; i++) {
        b_x[i] = (r[i] / y[i] > 0.8);
      }
    } else {
      binary_expand_op_24(b_x, r, peakIndexList, this, y);
    }

    likelyCaughSingleBigPeak.set_size(b_x.size(0));
    i1 = b_x.size(0);
    for (i = 0; i < i1; i++) {
      likelyCaughSingleBigPeak[i] = false;
    }

    resultSize_idx_1 = b_x.size(0);
    maxdimlen = (b_x.size(1) - 1) * b_x.size(0);
    i1 = 0;
    if (b_x.size(0) > 2147483646) {
      coder::check_forloop_overflow_error();
    }

    for (j = 0; j < resultSize_idx_1; j++) {
      i1++;
      maxdimlen++;
      if ((resultSize_idx_1 == 0) || (i1 > maxdimlen)) {
        overflow = false;
      } else {
        overflow = (maxdimlen > MAX_int32_T - resultSize_idx_1);
      }

      if (resultSize_idx_1 == 0) {
        cc_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
      }

      if (overflow) {
        coder::check_forloop_overflow_error();
      }

      ii_data = i1;
      exitg1 = false;
      while ((!exitg1) && (ii_data <= maxdimlen)) {
        if (b_x[ii_data - 1]) {
          likelyCaughSingleBigPeak[j] = true;
          exitg1 = true;
        } else {
          ii_data += resultSize_idx_1;
        }
      }
    }

    i1 = likelyCaughSingleBigPeak.size(0);
    for (i = 0; i < i1; i++) {
      likelyCaughSingleBigPeak[i] = !likelyCaughSingleBigPeak[i];
    }
  } else {
    likelyCaughSingleBigPeak.set_size(sumScores.size(0));
    i1 = sumScores.size(0);
    for (i = 0; i < i1; i++) {
      likelyCaughSingleBigPeak[i] = true;
    }
  }

  // There are three things we need to consider. 1) Are the pulses
  // aligned in time (interPulseAligned). 2) Are the pulses
  // relatively consistent in their score - ie.
  // doesntContainSingleBigPeak. 3) Which peak had the largest
  // score. We'll selected pulses based on this order of
  // preference.
  //
  //  if sum(interPulseAligned) > 1 | sum(interPulseAligned) == 0
  //      selectedIndex = 1;
  //  else
  //      selectedIndex = find(interPulseAligned);
  //  end
  //
  selectedIndex = rtNaN;
  resultSize_idx_1 = coder::combineVectorElements(interPulseAligned);
  if (resultSize_idx_1 == 1) {
    // Only one option that has pulse times aligned with
    // previous segment, so select that even if there are
    // stronger (higher scoring) pulses available
    resultSize_idx_1 = coder::c_eml_find(interPulseAligned, (int *)&ii_data);

    // There will only be 1, but we use n = 1 so coder knows there selectedIndex will be a scalar
    if (resultSize_idx_1 < 1) {
      rtDynamicBoundsError(1, 1, resultSize_idx_1, ab_emlrtBCI);
    }

    selectedIndex = ii_data;
    if (candidateList.size(1) < 1) {
      rtDynamicBoundsError(1, 1, candidateList.size(1), ib_emlrtBCI);
    }

    if ((ii_data < 1) || (ii_data > peakIndexList.size(0))) {
      rtDynamicBoundsError(ii_data, 1, peakIndexList.size(0), jb_emlrtBCI);
    }

    i = static_cast<int>(peakIndexList[ii_data - 1]);
    if ((i < 1) || (i > candidateList.size(0))) {
      rtDynamicBoundsError(i, 1, candidateList.size(0), kb_emlrtBCI);
    }

    std::printf("Selected peak at frequency %f Hz from center because it was the only one that was aligned in time with candidates from the previ"
                "ous segment.", candidateList[static_cast<int>
                (peakIndexList[ii_data - 1]) - 1].fp);
    std::fflush(stdout);
  } else {
    resultSize_idx_1 = coder::combineVectorElements(interPulseAligned);
    if (resultSize_idx_1 > 1) {
      if ((interPulseAligned.size(0) != likelyCaughSingleBigPeak.size(0)) &&
          ((interPulseAligned.size(0) != 1) && (likelyCaughSingleBigPeak.size(0)
            != 1))) {
        emlrtDimSizeImpxCheckR2021b(interPulseAligned.size(0),
          likelyCaughSingleBigPeak.size(0), h_emlrtECI);
      }

      if (interPulseAligned.size(0) == likelyCaughSingleBigPeak.size(0)) {
        x_tmp.set_size(interPulseAligned.size(0));
        i1 = interPulseAligned.size(0);
        for (i = 0; i < i1; i++) {
          x_tmp[i] = static_cast<double>(interPulseAligned[i]) * static_cast<
            double>(likelyCaughSingleBigPeak[i]);
        }
      } else {
        binary_expand_op_22(x_tmp, interPulseAligned, likelyCaughSingleBigPeak);
      }

      d = coder::blockedSummation(x_tmp, x_tmp.size(0));
      if (d == 1.0) {
        // Single option that doesn't contain a single big
        // peak and pulses are aligned in time so pick that one
        if ((interPulseAligned.size(0) != likelyCaughSingleBigPeak.size(0)) &&
            ((interPulseAligned.size(0) != 1) && (likelyCaughSingleBigPeak.size
              (0) != 1))) {
          emlrtDimSizeImpxCheckR2021b(interPulseAligned.size(0),
            likelyCaughSingleBigPeak.size(0), i_emlrtECI);
        }

        resultSize_idx_1 = (x_tmp.size(0) >= 1);
        if (resultSize_idx_1 > x_tmp.size(0)) {
          i_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
        }

        maxdimlen = 0;
        if (x_tmp.size(0) > 2147483646) {
          coder::check_forloop_overflow_error();
        }

        i1 = 0;
        exitg1 = false;
        while ((!exitg1) && (i1 <= x_tmp.size(0) - 1)) {
          if (x_tmp[i1] != 0.0) {
            maxdimlen = 1;
            ii_data = i1 + 1;
            exitg1 = true;
          } else {
            i1++;
          }
        }

        if (maxdimlen > resultSize_idx_1) {
          i_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
        }

        if (resultSize_idx_1 == 1) {
          if (maxdimlen == 0) {
            resultSize_idx_1 = 0;
          }
        } else {
          resultSize_idx_1 = (maxdimlen >= 1);
          b_peakIndexList[0] = 1;
          b_peakIndexList[1] = resultSize_idx_1;
          coder::internal::indexShapeCheck(0, b_peakIndexList);
        }

        // There will only be 1, but we use n = 1 so coder knows there selectedIndex will be a scalar
        if (resultSize_idx_1 < 1) {
          rtDynamicBoundsError(1, 1, 0, lb_emlrtBCI);
        }

        selectedIndex = ii_data;
        if (candidateList.size(1) < 1) {
          rtDynamicBoundsError(1, 1, candidateList.size(1), mb_emlrtBCI);
        }

        if (ii_data > peakIndexList.size(0)) {
          rtDynamicBoundsError(ii_data, 1, peakIndexList.size(0), nb_emlrtBCI);
        }

        i = static_cast<int>(peakIndexList[ii_data - 1]);
        if ((i < 1) || (i > candidateList.size(0))) {
          rtDynamicBoundsError(i, 1, candidateList.size(0), ob_emlrtBCI);
        }

        std::printf("Selected peak at frequency %f Hz from center because of those that were aligned in time with candidates from the previous segmen"
                    "t, it was the only one without a single big peak.",
                    candidateList[static_cast<int>(peakIndexList[ii_data - 1]) -
                    1].fp);
        std::fflush(stdout);
      } else {
        overflow = ((interPulseAligned.size(0) != likelyCaughSingleBigPeak.size
                     (0)) && ((interPulseAligned.size(0) != 1) &&
                              (likelyCaughSingleBigPeak.size(0) != 1)));
        if (overflow) {
          emlrtDimSizeImpxCheckR2021b(interPulseAligned.size(0),
            likelyCaughSingleBigPeak.size(0), j_emlrtECI);
        }

        if (d > 1.0) {
          // Multiple options that don't contain a single big
          // peak and pulses are aligned in time. Pick the one
          // with the biggest score from that subset.
          if (overflow) {
            emlrtDimSizeImpxCheckR2021b(interPulseAligned.size(0),
              likelyCaughSingleBigPeak.size(0), k_emlrtECI);
          }

          if ((x_tmp.size(0) != sumScores.size(0)) && ((x_tmp.size(0) != 1) &&
               (sumScores.size(0) != 1))) {
            emlrtDimSizeImpxCheckR2021b(x_tmp.size(0), sumScores.size(0),
              k_emlrtECI);
          }

          if (x_tmp.size(0) == sumScores.size(0)) {
            i1 = x_tmp.size(0);
            for (i = 0; i < i1; i++) {
              x_tmp[i] = x_tmp[i] * sumScores[i];
            }

            coder::internal::b_maximum(x_tmp, resultSize_idx_1);
          } else {
            binary_expand_op_21(x_tmp, sumScores, resultSize_idx_1);
          }

          selectedIndex = resultSize_idx_1;
          if (candidateList.size(1) < 1) {
            rtDynamicBoundsError(1, 1, candidateList.size(1), pb_emlrtBCI);
          }

          if ((resultSize_idx_1 < 1) || (resultSize_idx_1 > peakIndexList.size(0)))
          {
            rtDynamicBoundsError(resultSize_idx_1, 1, peakIndexList.size(0),
                                 qb_emlrtBCI);
          }

          i = static_cast<int>(peakIndexList[resultSize_idx_1 - 1]);
          if ((i < 1) || (i > candidateList.size(0))) {
            rtDynamicBoundsError(i, 1, candidateList.size(0), rb_emlrtBCI);
          }

          std::printf("Selected peak at frequency %f Hz from center because of those that were aligned in time with candidates from the previous segmen"
                      "t and those without a single big peak, it had the strongst pulses",
                      candidateList[static_cast<int>
                      (peakIndexList[resultSize_idx_1 - 1]) - 1].fp);
          std::fflush(stdout);
        } else {
          if (overflow) {
            emlrtDimSizeImpxCheckR2021b(interPulseAligned.size(0),
              likelyCaughSingleBigPeak.size(0), l_emlrtECI);
          }

          if (d == 0.0) {
            // No options that don't contain a single big
            // peak and pulses are aligned in time. Pick the one
            // with the biggest score.
            coder::internal::b_maximum(sumScores, resultSize_idx_1);
            selectedIndex = resultSize_idx_1;
            if (candidateList.size(1) < 1) {
              rtDynamicBoundsError(1, 1, candidateList.size(1), sb_emlrtBCI);
            }

            if ((resultSize_idx_1 < 1) || (resultSize_idx_1 > peakIndexList.size
                 (0))) {
              rtDynamicBoundsError(resultSize_idx_1, 1, peakIndexList.size(0),
                                   tb_emlrtBCI);
            }

            i = static_cast<int>(peakIndexList[resultSize_idx_1 - 1]);
            if ((i < 1) || (i > candidateList.size(0))) {
              rtDynamicBoundsError(i, 1, candidateList.size(0), ub_emlrtBCI);
            }

            std::printf("Selected peak at frequency %f Hz from center because there were no pulses that aligned in time with the previous segment that al"
                        "so did not have a single bit peak, so the stronget pulse set was selected.",
                        candidateList[static_cast<int>
                        (peakIndexList[resultSize_idx_1 - 1]) - 1].fp);
            std::fflush(stdout);
          }
        }
      }
    } else {
      resultSize_idx_1 = coder::combineVectorElements(interPulseAligned);
      if (resultSize_idx_1 == 0) {
        // No pulses are aligned in time, so only use single big
        // peak and pulse stregth as decision criteria
        resultSize_idx_1 = coder::combineVectorElements(likelyCaughSingleBigPeak);
        if (resultSize_idx_1 == 1) {
          // Single option that doesn't contain a single big
          // peak and pulses are aligned in time so pick that one
          resultSize_idx_1 = coder::c_eml_find(likelyCaughSingleBigPeak, (int *)
            &ii_data);

          // There will only be 1, but we use n = 1 so coder knows there selectedIndex will be a scalar
          if (resultSize_idx_1 < 1) {
            rtDynamicBoundsError(1, 1, resultSize_idx_1, vb_emlrtBCI);
          }

          selectedIndex = ii_data;
          if (candidateList.size(1) < 1) {
            rtDynamicBoundsError(1, 1, candidateList.size(1), wb_emlrtBCI);
          }

          if ((ii_data < 1) || (ii_data > peakIndexList.size(0))) {
            rtDynamicBoundsError(ii_data, 1, peakIndexList.size(0), xb_emlrtBCI);
          }

          i = static_cast<int>(peakIndexList[ii_data - 1]);
          if ((i < 1) || (i > candidateList.size(0))) {
            rtDynamicBoundsError(i, 1, candidateList.size(0), yb_emlrtBCI);
          }

          std::printf("Selected peak at frequency %f Hz from center because no pulses that aligned in time with the previous segment were found and thi"
                      "s was the only one that did not have a single big peak.",
                      candidateList[static_cast<int>(peakIndexList[ii_data - 1])
                      - 1].fp);
          std::fflush(stdout);
        } else {
          resultSize_idx_1 = coder::combineVectorElements
            (likelyCaughSingleBigPeak);
          if (resultSize_idx_1 > 1) {
            // Multiple options that don't contain a single big
            // peak. Pick the one with the biggest score from that
            // subset.
            if ((likelyCaughSingleBigPeak.size(0) != sumScores.size(0)) &&
                ((likelyCaughSingleBigPeak.size(0) != 1) && (sumScores.size(0)
                  != 1))) {
              emlrtDimSizeImpxCheckR2021b(likelyCaughSingleBigPeak.size(0),
                sumScores.size(0), m_emlrtECI);
            }

            if (likelyCaughSingleBigPeak.size(0) == sumScores.size(0)) {
              sumScores.set_size(likelyCaughSingleBigPeak.size(0));
              i1 = likelyCaughSingleBigPeak.size(0);
              for (i = 0; i < i1; i++) {
                sumScores[i] = static_cast<double>(likelyCaughSingleBigPeak[i]) *
                  sumScores[i];
              }

              coder::internal::b_maximum(sumScores, resultSize_idx_1);
            } else {
              binary_expand_op_23(likelyCaughSingleBigPeak, sumScores,
                                  resultSize_idx_1);
            }

            selectedIndex = resultSize_idx_1;
            if (candidateList.size(1) < 1) {
              rtDynamicBoundsError(1, 1, candidateList.size(1), ac_emlrtBCI);
            }

            if ((resultSize_idx_1 < 1) || (resultSize_idx_1 > peakIndexList.size
                 (0))) {
              rtDynamicBoundsError(resultSize_idx_1, 1, peakIndexList.size(0),
                                   bc_emlrtBCI);
            }

            i = static_cast<int>(peakIndexList[resultSize_idx_1 - 1]);
            if ((i < 1) || (i > candidateList.size(0))) {
              rtDynamicBoundsError(i, 1, candidateList.size(0), cc_emlrtBCI);
            }

            std::printf("Selected peak at frequency %f Hz from center because no pulses that aligned in time with the previous segment were found and of "
                        "those that did not have a single big peak, this one had the strongest pulses.",
                        candidateList[static_cast<int>
                        (peakIndexList[resultSize_idx_1 - 1]) - 1].fp);
            std::fflush(stdout);
          } else {
            resultSize_idx_1 = coder::combineVectorElements
              (likelyCaughSingleBigPeak);
            if (resultSize_idx_1 == 0) {
              // No options that don't contain a single big
              // peak and pulses are aligned in time. Pick the one
              // with the biggest score.
              coder::internal::b_maximum(sumScores, resultSize_idx_1);
              selectedIndex = resultSize_idx_1;
              if (candidateList.size(1) < 1) {
                rtDynamicBoundsError(1, 1, candidateList.size(1), dc_emlrtBCI);
              }

              if ((resultSize_idx_1 < 1) || (resultSize_idx_1 >
                   peakIndexList.size(0))) {
                rtDynamicBoundsError(resultSize_idx_1, 1, peakIndexList.size(0),
                                     ec_emlrtBCI);
              }

              i = static_cast<int>(peakIndexList[resultSize_idx_1 - 1]);
              if ((i < 1) || (i > candidateList.size(0))) {
                rtDynamicBoundsError(i, 1, candidateList.size(0), fc_emlrtBCI);
              }

              std::printf("Selected peak at frequency %f Hz from center because no pulses that aligned in time with the previous segment were found and all"
                          " peaks considered had a single big peak. This one had the strongest pulses.",
                          candidateList[static_cast<int>
                          (peakIndexList[resultSize_idx_1 - 1]) - 1].fp);
              std::fflush(stdout);
            }
          }
        }
      }
    }
  }

  return selectedIndex;
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<boolean_T, 1U> &in2
// Return Type  : void
//
static void b_and(coder::array<boolean_T, 1U> &in1, const coder::array<boolean_T,
                  1U> &in2)
{
  coder::array<boolean_T, 1U> b_in1;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in2.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2.size(0);
  }

  b_in1.set_size(loop_ub);
  stride_0_0 = (in1.size(0) != 1);
  stride_1_0 = (in2.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    b_in1[i] = (in1[i * stride_0_0] && in2[i * stride_1_0]);
  }

  in1.set_size(b_in1.size(0));
  loop_ub = b_in1.size(0);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = b_in1[i];
  }
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<boolean_T, 1U> &in2
// Return Type  : void
//
static void b_or(coder::array<boolean_T, 1U> &in1, const coder::array<boolean_T,
                 1U> &in2)
{
  coder::array<boolean_T, 1U> b_in1;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in2.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2.size(0);
  }

  b_in1.set_size(loop_ub);
  stride_0_0 = (in1.size(0) != 1);
  stride_1_0 = (in2.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    b_in1[i] = (in1[i * stride_0_0] || in2[i * stride_1_0]);
  }

  in1.set_size(b_in1.size(0));
  loop_ub = b_in1.size(0);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = b_in1[i];
  }
}

//
// Arguments    : waveform *in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void binary_expand_op_1(waveform *in1, const coder::array<double, 2U>
  &in2, const coder::array<double, 2U> &in3)
{
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in3.size(1) == 1) {
    loop_ub = in2.size(1);
  } else {
    loop_ub = in3.size(1);
  }

  in1->Wf.set_size(loop_ub);
  stride_0_0 = (in2.size(1) != 1);
  stride_1_0 = (in3.size(1) != 1);
  for (int i{0}; i < loop_ub; i++) {
    in1->Wf[i] = in2[i * stride_0_0] + in3[i * stride_1_0];
  }
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<boolean_T, 1U> &in2
//                const coder::array<boolean_T, 1U> &in3
// Return Type  : void
//
static void binary_expand_op_13(coder::array<boolean_T, 1U> &in1, const coder::
  array<boolean_T, 1U> &in2, const coder::array<boolean_T, 1U> &in3)
{
  coder::array<boolean_T, 1U> b_in2;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in3.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3.size(0);
  }

  b_in2.set_size(loop_ub);
  stride_0_0 = (in2.size(0) != 1);
  stride_1_0 = (in3.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    b_in2[i] = (in2[i * stride_0_0] && in3[i * stride_1_0]);
  }

  in1.set_size(b_in2.size(0) + 1);
  loop_ub = b_in2.size(0);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = b_in2[i];
  }

  in1[b_in2.size(0)] = true;
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<boolean_T, 1U> &in2
//                const coder::array<boolean_T, 1U> &in3
// Return Type  : void
//
static void binary_expand_op_14(coder::array<boolean_T, 1U> &in1, const coder::
  array<boolean_T, 1U> &in2, const coder::array<boolean_T, 1U> &in3)
{
  coder::array<boolean_T, 1U> b_in2;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in3.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3.size(0);
  }

  b_in2.set_size(loop_ub);
  stride_0_0 = (in2.size(0) != 1);
  stride_1_0 = (in3.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    b_in2[i] = (in2[i * stride_0_0] && in3[i * stride_1_0]);
  }

  in1.set_size(b_in2.size(0) + 1);
  in1[0] = true;
  loop_ub = b_in2.size(0);
  for (int i{0}; i < loop_ub; i++) {
    in1[i + 1] = b_in2[i];
  }
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<double, 1U> &in2
//                int in3
//                const coder::array<double, 1U> &in4
// Return Type  : void
//
static void binary_expand_op_15(coder::array<boolean_T, 1U> &in1, const coder::
  array<double, 1U> &in2, int in3, const coder::array<double, 1U> &in4)
{
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in4.size(0) == 1) {
    loop_ub = in3;
  } else {
    loop_ub = in4.size(0);
  }

  in1.set_size(loop_ub);
  stride_0_0 = (in3 != 1);
  stride_1_0 = (in4.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = (in2[i * stride_0_0] > in4[i * stride_1_0]);
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                const waveform *in2
// Return Type  : void
//
static void binary_expand_op_17(coder::array<double, 2U> &in1, const waveform
  *in2)
{
  coder::array<creal_T, 2U> b_in2;
  int aux_0_1;
  int aux_1_1;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in1.size(0) == 1) {
    i = in2->stft->S.size(0);
  } else {
    i = in1.size(0);
  }

  if (in1.size(1) == 1) {
    i1 = in2->stft->S.size(1);
  } else {
    i1 = in1.size(1);
  }

  b_in2.set_size(i, i1);
  stride_0_0 = (in2->stft->S.size(0) != 1);
  stride_0_1 = (in2->stft->S.size(1) != 1);
  stride_1_0 = (in1.size(0) != 1);
  stride_1_1 = (in1.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in1.size(1) == 1) {
    loop_ub = in2->stft->S.size(1);
  } else {
    loop_ub = in1.size(1);
  }

  for (i = 0; i < loop_ub; i++) {
    int b_loop_ub;
    if (in1.size(0) == 1) {
      b_loop_ub = in2->stft->S.size(0);
    } else {
      b_loop_ub = in1.size(0);
    }

    for (i1 = 0; i1 < b_loop_ub; i1++) {
      b_in2[i1 + b_in2.size(0) * i].re = in2->stft->S[i1 * stride_0_0 +
        in2->stft->S.size(0) * aux_0_1].re + in1[i1 * stride_1_0 + in1.size(0) *
        aux_1_1];
      b_in2[i1 + b_in2.size(0) * i].im = in2->stft->S[i1 * stride_0_0 +
        in2->stft->S.size(0) * aux_0_1].im;
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  coder::b_abs(b_in2, in1);
}

//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 2U> &in3
//                int in4
//                int in5
// Return Type  : void
//
static void binary_expand_op_18(coder::array<double, 2U> &in1, const coder::
  array<double, 2U> &in2, const coder::array<double, 2U> &in3, int in4, int in5)
{
  coder::array<double, 2U> b_in2;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in3.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3.size(0);
  }

  if (in3.size(1) == 1) {
    b_loop_ub = in2.size(1);
  } else {
    b_loop_ub = in3.size(1);
  }

  b_in2.set_size(loop_ub, b_loop_ub);
  stride_0_0 = (in2.size(0) != 1);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_0 = (in3.size(0) != 1);
  stride_1_1 = (in3.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (int i{0}; i < b_loop_ub; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      b_in2[i1 + b_in2.size(0) * i] = in2[i1 * stride_0_0 + in2.size(0) *
        aux_0_1] + in3[i1 * stride_1_0 + in3.size(0) * aux_1_1];
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  double b_in4[2];
  b_in4[0] = static_cast<unsigned int>(in4);
  b_in4[1] = static_cast<unsigned int>(in5);
  coder::imresize(b_in2, b_in4, in1);
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<boolean_T, 2U> &in2
//                const coder::array<boolean_T, 2U> &in3
// Return Type  : void
//
static void binary_expand_op_20(coder::array<boolean_T, 1U> &in1, const coder::
  array<boolean_T, 2U> &in2, const coder::array<boolean_T, 2U> &in3)
{
  coder::array<boolean_T, 2U> b_in2;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in3.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3.size(0);
  }

  if (in3.size(1) == 1) {
    b_loop_ub = in2.size(1);
  } else {
    b_loop_ub = in3.size(1);
  }

  b_in2.set_size(loop_ub, b_loop_ub);
  stride_0_0 = (in2.size(0) != 1);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_0 = (in3.size(0) != 1);
  stride_1_1 = (in3.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (int i{0}; i < b_loop_ub; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      b_in2[i1 + b_in2.size(0) * i] = ((!in2[i1 * stride_0_0 + in2.size(0) *
        aux_0_1]) || (!in3[i1 * stride_1_0 + in3.size(0) * aux_1_1]));
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  coder::all(b_in2, in1);
}

//
// Arguments    : coder::array<double, 1U> &in1
//                const coder::array<boolean_T, 1U> &in2
//                const coder::array<boolean_T, 1U> &in3
// Return Type  : void
//
static void binary_expand_op_22(coder::array<double, 1U> &in1, const coder::
  array<boolean_T, 1U> &in2, const coder::array<boolean_T, 1U> &in3)
{
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in3.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3.size(0);
  }

  in1.set_size(loop_ub);
  stride_0_0 = (in2.size(0) != 1);
  stride_1_0 = (in3.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = static_cast<double>(in2[i * stride_0_0]) * static_cast<double>
      (in3[i * stride_1_0]);
  }
}

//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 1U> &in3
//                const waveform *in4
//                const coder::array<double, 2U> &in5
// Return Type  : void
//
static void binary_expand_op_24(coder::array<boolean_T, 2U> &in1, const coder::
  array<double, 2U> &in2, const coder::array<double, 1U> &in3, const waveform
  *in4, const coder::array<double, 2U> &in5)
{
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int in3_idx_0;
  int in3_idx_1;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  int stride_1_1;
  in3_idx_0 = in3.size(0);
  in3_idx_1 = static_cast<int>(in4->K);
  if (in5.size(0) == 1) {
    loop_ub = in3_idx_0;
  } else {
    loop_ub = in5.size(0);
  }

  in1.set_size(loop_ub, in1.size(1));
  if (in5.size(1) == 1) {
    b_loop_ub = in3_idx_1;
  } else {
    b_loop_ub = in5.size(1);
  }

  in1.set_size(in1.size(0), b_loop_ub);
  stride_0_0 = (in3_idx_0 != 1);
  in3_idx_1 = (in3_idx_1 != 1);
  stride_1_0 = (in5.size(0) != 1);
  stride_1_1 = (in5.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (int i{0}; i < b_loop_ub; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] = (in2[i1 * stride_0_0 + in3_idx_0 * aux_0_1] /
        in5[i1 * stride_1_0 + in5.size(0) * aux_1_1] > 0.8);
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += in3_idx_1;
  }
}

//
// Arguments    : coder::array<double, 1U> &in1
//                const coder::array<boolean_T, 1U> &in2
// Return Type  : void
//
static void binary_expand_op_4(coder::array<double, 1U> &in1, const coder::array<
  boolean_T, 1U> &in2)
{
  coder::array<double, 1U> b_in1;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in2.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2.size(0);
  }

  b_in1.set_size(loop_ub);
  stride_0_0 = (in1.size(0) != 1);
  stride_1_0 = (in2.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    b_in1[i] = in1[i * stride_0_0] * static_cast<double>(in2[i * stride_1_0]);
  }

  in1.set_size(b_in1.size(0));
  loop_ub = b_in1.size(0);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = b_in1[i];
  }
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<double, 1U> &in2
//                const waveform *in3
// Return Type  : void
//
static void binary_expand_op_5(coder::array<boolean_T, 1U> &in1, const coder::
  array<double, 1U> &in2, const waveform *in3)
{
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in3->thresh.threshVecFine.size(0) == 1) {
    i = in2.size(0);
  } else {
    i = in3->thresh.threshVecFine.size(0);
  }

  in1.set_size(i);
  stride_0_0 = (in2.size(0) != 1);
  stride_1_0 = (in3->thresh.threshVecFine.size(0) != 1);
  if (in3->thresh.threshVecFine.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3->thresh.threshVecFine.size(0);
  }

  for (i = 0; i < loop_ub; i++) {
    in1[i] = (in2[i * stride_0_0] >= in3->thresh.threshVecFine[i * stride_1_0]);
  }
}

//
// Arguments    : coder::array<double, 1U> &in1
//                const coder::array<double, 1U> &in2
//                const coder::array<boolean_T, 1U> &in3
// Return Type  : void
//
static void binary_expand_op_7(coder::array<double, 1U> &in1, const coder::array<
  double, 1U> &in2, const coder::array<boolean_T, 1U> &in3)
{
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in3.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3.size(0);
  }

  in1.set_size(loop_ub);
  stride_0_0 = (in2.size(0) != 1);
  stride_1_0 = (in3.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = in2[i * stride_0_0] * static_cast<double>(in3[i * stride_1_0]);
  }
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<boolean_T, 1U> &in2
//                const coder::array<boolean_T, 1U> &in3
// Return Type  : void
//
static void c_and(coder::array<boolean_T, 1U> &in1, const coder::array<boolean_T,
                  1U> &in2, const coder::array<boolean_T, 1U> &in3)
{
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in3.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3.size(0);
  }

  in1.set_size(loop_ub);
  stride_0_0 = (in2.size(0) != 1);
  stride_1_0 = (in3.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = (in2[i * stride_0_0] && in3[i * stride_1_0]);
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 2U> &in2
// Return Type  : void
//
static void c_plus(coder::array<double, 2U> &in1, const coder::array<double, 2U>
                   &in2)
{
  coder::array<double, 2U> b_in2;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in1.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in1.size(0);
  }

  if (in1.size(1) == 1) {
    b_loop_ub = in2.size(1);
  } else {
    b_loop_ub = in1.size(1);
  }

  b_in2.set_size(loop_ub, b_loop_ub);
  stride_0_0 = (in2.size(0) != 1);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_0 = (in1.size(0) != 1);
  stride_1_1 = (in1.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (int i{0}; i < b_loop_ub; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      b_in2[i1 + b_in2.size(0) * i] = in2[i1 * stride_0_0 + in2.size(0) *
        aux_0_1] + in1[i1 * stride_1_0 + in1.size(0) * aux_1_1];
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  in1.set_size(b_in2.size(0), b_in2.size(1));
  loop_ub = b_in2.size(1);
  for (int i{0}; i < loop_ub; i++) {
    b_loop_ub = b_in2.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] = b_in2[i1 + b_in2.size(0) * i];
    }
  }
}

//
// Arguments    : const char *r
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void g_rtErrorWithMessageID(const char *r, const char *aFcnName, int
  aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "Order, ") << r) << ", must be finite.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 2U> &in2
// Return Type  : void
//
static void minus(coder::array<double, 2U> &in1, const coder::array<double, 2U>
                  &in2)
{
  coder::array<double, 2U> b_in1;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in2.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2.size(0);
  }

  if (in2.size(1) == 1) {
    b_loop_ub = in1.size(1);
  } else {
    b_loop_ub = in2.size(1);
  }

  b_in1.set_size(loop_ub, b_loop_ub);
  stride_0_0 = (in1.size(0) != 1);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_0 = (in2.size(0) != 1);
  stride_1_1 = (in2.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (int i{0}; i < b_loop_ub; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      b_in1[i1 + b_in1.size(0) * i] = in1[i1 * stride_0_0 + in1.size(0) *
        aux_0_1] - in2[i1 * stride_1_0 + in2.size(0) * aux_1_1];
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  in1.set_size(b_in1.size(0), b_in1.size(1));
  loop_ub = b_in1.size(1);
  for (int i{0}; i < loop_ub; i++) {
    b_loop_ub = b_in1.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] = b_in1[i1 + b_in1.size(0) * i];
    }
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 2U> &in2
// Return Type  : void
//
static void rdivide(coder::array<double, 2U> &in1, const coder::array<double, 2U>
                    &in2)
{
  coder::array<double, 2U> b_in1;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in2.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2.size(0);
  }

  if (in2.size(1) == 1) {
    b_loop_ub = in1.size(1);
  } else {
    b_loop_ub = in2.size(1);
  }

  b_in1.set_size(loop_ub, b_loop_ub);
  stride_0_0 = (in1.size(0) != 1);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_0 = (in2.size(0) != 1);
  stride_1_1 = (in2.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (int i{0}; i < b_loop_ub; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      b_in1[i1 + b_in1.size(0) * i] = in1[i1 * stride_0_0 + in1.size(0) *
        aux_0_1] / in2[i1 * stride_1_0 + in2.size(0) * aux_1_1];
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  in1.set_size(b_in1.size(0), b_in1.size(1));
  loop_ub = b_in1.size(1);
  for (int i{0}; i < loop_ub; i++) {
    b_loop_ub = b_in1.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] = b_in1[i1 + b_in1.size(0) * i];
    }
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void s_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Order must be greater than or equal to zero.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// WAVEFORM Constructs an instance of this class
// INPUTS:
//    x       1xn     Vector of samples
//    Fs      1x1     Sample frequency (Hz)
//    t_0     1x1     Time stamp of first element (s)
//  ps_pre  1x1     Pulse stats object from previous data (priori)
//    OLF     1x1     Overlap fraction as decimal (0.5 = 50%
//                    overlap)
// OUTPUTS:
//    obj             The waveform object
//             %%
//
// Arguments    : const creal32_T b_x[1000]
//                double b_Fs
//                pulsestats *b_ps_pre
//                const threshold &b_thresh
// Return Type  : waveform *
//
waveform *waveform::init(const creal32_T b_x[1000], double b_Fs, pulsestats
  *b_ps_pre, const threshold &b_thresh)
{
  pulsestats *obj_out;
  waveform *obj;
  coder::array<c_struct_T, 2U> c_ps_pre;
  coder::array<c_struct_T, 2U> d_ps_pre;
  coder::array<double, 2U> f_ps_pre;
  coder::array<boolean_T, 2U> e_ps_pre;
  int loop_ub;
  obj = this;
  obj->x.set_size(1, 0);
  obj->W.set_size(0, 0);
  obj->Wf.set_size(0);

  // Flatten input to row
  obj->x.set_size(1, 1000);
  for (int i{0}; i < 1000; i++) {
    obj->x[i] = b_x[i];
  }

  // Data vector
  obj->l = 1000.0;

  // Elements in the data
  obj->Fs = b_Fs;

  // Sample rate
  obj->t_0 = 0.0;

  // Time stamp of first element
  obj->t_f = 999.0 / b_Fs;

  // Time stamp of last element
  obj->t_nextsegstart[0] = 0.0;
  obj->t_nextsegstart[1] = 0.0;

  // This is the time when next
  // segment should start to
  // ensure sufficient overlap.
  // Will need to be updated
  // elsewhere.
  obj->ps_pre = b_ps_pre;
  obj->OLF = 0.5;

  // Overlap Fraction for STFT
  obj->K = rtNaN;

  // Unknown number of pulses.
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
  // Instructions on https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  // maxFs*maxpulsewidth
  // Now actually assign them
  obj->_pobj1.S.set_size(0, 0);
  obj->_pobj1.t.set_size(0);
  obj->_pobj1.f.set_size(0);
  obj->_pobj1.psd.set_size(0);
  obj->_pobj1.wind.set_size(0);
  obj->_pobj1.dt = 0.0;
  obj->_pobj1.T = 0.0;
  obj->stft = &obj->_pobj1;

  // Unknown values but set types
  obj->W.set_size(0, 0);
  obj->Wf.set_size(0);

  // Copy over ps_
  // COPY Creates an exact copy of the pulse stats object as a
  // separate object
  c_ps_pre.set_size(1, b_ps_pre->pl.size(1));
  loop_ub = b_ps_pre->pl.size(0) * b_ps_pre->pl.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    c_ps_pre[i] = b_ps_pre->pl[i];
  }

  d_ps_pre.set_size(b_ps_pre->clst.size(0), b_ps_pre->clst.size(1));
  loop_ub = b_ps_pre->clst.size(0) * b_ps_pre->clst.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    d_ps_pre[i] = b_ps_pre->clst[i];
  }

  e_ps_pre.set_size(b_ps_pre->cmsk.size(0), b_ps_pre->cmsk.size(1));
  loop_ub = b_ps_pre->cmsk.size(0) * b_ps_pre->cmsk.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    e_ps_pre[i] = b_ps_pre->cmsk[i];
  }

  f_ps_pre.set_size(b_ps_pre->cpki.size(0), b_ps_pre->cpki.size(1));
  loop_ub = b_ps_pre->cpki.size(0) * b_ps_pre->cpki.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    f_ps_pre[i] = b_ps_pre->cpki[i];
  }

  double g_ps_pre[2];
  g_ps_pre[0] = b_ps_pre->tmplt[0];
  g_ps_pre[1] = b_ps_pre->tmplt[1];
  obj_out = obj->_pobj0.b_init(b_ps_pre->t_p, b_ps_pre->t_ip, b_ps_pre->t_ipu,
    b_ps_pre->t_ipj, b_ps_pre->fp, b_ps_pre->fstart, b_ps_pre->fend, g_ps_pre,
    b_ps_pre->mode, c_ps_pre, d_ps_pre, e_ps_pre, f_ps_pre);

  // ,...
  // obj.thresh);
  obj->ps_pos = obj_out;

  // Current stats are same as previous during construction
  obj->setprioridependentprops(b_ps_pre);
  obj->thresh = b_thresh;
  return obj;
}

//
// WAVEFORM Constructs an instance of this class
// INPUTS:
//    x       1xn     Vector of samples
//    Fs      1x1     Sample frequency (Hz)
//    t_0     1x1     Time stamp of first element (s)
//  ps_pre  1x1     Pulse stats object from previous data (priori)
//    OLF     1x1     Overlap fraction as decimal (0.5 = 50%
//                    overlap)
// OUTPUTS:
//    obj             The waveform object
//             %%
//
// Arguments    : const creal32_T b_x[1000]
//                double b_Fs
//                pulsestats *b_ps_pre
//                pulsestats &iobj_0
//                wfmstft &iobj_1
// Return Type  : b_waveform *
//
b_waveform *b_waveform::init(const creal32_T b_x[1000], double b_Fs, pulsestats *
  b_ps_pre, pulsestats &iobj_0, wfmstft &iobj_1)
{
  b_waveform *obj;
  pulsestats *obj_out;
  coder::array<c_struct_T, 2U> c_ps_pre;
  coder::array<c_struct_T, 2U> d_ps_pre;
  coder::array<double, 2U> f_ps_pre;
  coder::array<boolean_T, 2U> e_ps_pre;
  int loop_ub;
  obj = this;
  obj->x.set_size(1, 0);

  // Flatten input to row
  obj->x.set_size(1, 1000);
  for (int i{0}; i < 1000; i++) {
    obj->x[i] = b_x[i];
  }

  // Data vector
  // Elements in the data
  obj->Fs = b_Fs;

  // Sample rate
  obj->t_0 = 0.0;

  // Time stamp of first element
  // Time stamp of last element
  // This is the time when next
  // segment should start to
  // ensure sufficient overlap.
  // Will need to be updated
  // elsewhere.
  obj->ps_pre = b_ps_pre;
  obj->OLF = 0.5;

  // Overlap Fraction for STFT
  obj->K = rtNaN;

  // Unknown number of pulses.
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
  // Instructions on https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  // maxFs*maxpulsewidth
  // Now actually assign them
  iobj_1.S.set_size(0, 0);
  iobj_1.t.set_size(0);
  iobj_1.f.set_size(0);
  iobj_1.psd.set_size(0);
  iobj_1.wind.set_size(0);
  iobj_1.dt = 0.0;
  iobj_1.T = 0.0;
  obj->stft = &iobj_1;

  // Unknown values but set types
  // Copy over ps_
  // COPY Creates an exact copy of the pulse stats object as a
  // separate object
  c_ps_pre.set_size(1, b_ps_pre->pl.size(1));
  loop_ub = b_ps_pre->pl.size(0) * b_ps_pre->pl.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    c_ps_pre[i] = b_ps_pre->pl[i];
  }

  d_ps_pre.set_size(b_ps_pre->clst.size(0), b_ps_pre->clst.size(1));
  loop_ub = b_ps_pre->clst.size(0) * b_ps_pre->clst.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    d_ps_pre[i] = b_ps_pre->clst[i];
  }

  e_ps_pre.set_size(b_ps_pre->cmsk.size(0), b_ps_pre->cmsk.size(1));
  loop_ub = b_ps_pre->cmsk.size(0) * b_ps_pre->cmsk.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    e_ps_pre[i] = b_ps_pre->cmsk[i];
  }

  f_ps_pre.set_size(b_ps_pre->cpki.size(0), b_ps_pre->cpki.size(1));
  loop_ub = b_ps_pre->cpki.size(0) * b_ps_pre->cpki.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    f_ps_pre[i] = b_ps_pre->cpki[i];
  }

  double g_ps_pre[2];
  double b_n_ol;
  double n_p;
  g_ps_pre[0] = b_ps_pre->tmplt[0];
  g_ps_pre[1] = b_ps_pre->tmplt[1];
  obj_out = iobj_0.b_init(b_ps_pre->t_p, b_ps_pre->t_ip, b_ps_pre->t_ipu,
    b_ps_pre->t_ipj, b_ps_pre->fp, b_ps_pre->fstart, b_ps_pre->fend, g_ps_pre,
    b_ps_pre->mode, c_ps_pre, d_ps_pre, e_ps_pre, f_ps_pre);

  // ,...
  // obj.thresh);
  obj->ps_pos = obj_out;

  // Current stats are same as previous during construction
  // SETPRIORIDEPENDENTVARS updates the properties in the
  // waveform that are dependent on properties in a pulsestats
  // object.
  //
  // INPUTS:
  //    obj     waveform object
  //    ps_obj  a pulse stats object
  // OUTPUTS:
  //    None (This method modifies the waveform object properties)
  //
  //             %%
  // GETPRIORIDEPENDENTVARS returns the properties in the
  // waveform that are dependent on prior pulse data estimates. It
  // depends on the waveform properties list Fs etc, as well as
  // pulse stats like t_ip, etc.
  // INPUTS:  ps_obj  1x1 pulse stats object
  // OUTPUTS:  pulse stats object
  n_p = b_ps_pre->t_p * obj->Fs;
  n_p = std::ceil(n_p);

  // Samples per pulse
  // Number of elements in STFT window
  b_n_ol = obj->OLF * n_p;

  // Number of elements overlap in STFT window
  // Number of elements in each step of STFT
  // Time of each step of STFT
  // Samples per pulse
  obj->n_w = n_p;

  // Number of elements in STFT window
  obj->n_ol = std::floor(b_n_ol);

  // Number of elements overlap in STFT window
  // Number of elements in each step of STFT
  // Time of each step of STFT
  // Samples of interpulse duration
  // Baseline interpulse duration in units of STFT windows
  // Interpulse duration deviation from baselines in units of STFT windows
  // Amount of deviation from the PRI means to search
  // See 2022-07-11 for updates to samples def
  // Don't need the overlap here since the next segment starts at samplesforKpulses+n_ol-n_ol from current sample
  return obj;
}

//
// WAVEFORM Constructs an instance of this class
// INPUTS:
//    x       1xn     Vector of samples
//    Fs      1x1     Sample frequency (Hz)
//    t_0     1x1     Time stamp of first element (s)
//  ps_pre  1x1     Pulse stats object from previous data (priori)
//    OLF     1x1     Overlap fraction as decimal (0.5 = 50%
//                    overlap)
// OUTPUTS:
//    obj             The waveform object
//             %%
//
// Arguments    : const coder::array<creal32_T, 1U> &b_x
//                double b_Fs
//                double b_t_0
//                pulsestats *b_ps_pre
//                const threshold &b_thresh
//                pulsestats &iobj_0
//                wfmstft &iobj_1
// Return Type  : waveform *
//
waveform *waveform::init(const coder::array<creal32_T, 1U> &b_x, double b_Fs,
  double b_t_0, pulsestats *b_ps_pre, const threshold &b_thresh, pulsestats &
  iobj_0, wfmstft &iobj_1)
{
  pulsestats *obj_out;
  waveform *obj;
  coder::array<c_struct_T, 2U> c_ps_pre;
  coder::array<c_struct_T, 2U> d_ps_pre;
  coder::array<double, 2U> f_ps_pre;
  coder::array<boolean_T, 2U> e_ps_pre;
  int n;
  int u0;
  obj = this;
  obj->x.set_size(1, 0);
  obj->W.set_size(0, 0);
  obj->Wf.set_size(0);
  n = b_x.size(0);
  if (b_x.size(0) < 1) {
    n = 1;
  }

  u0 = b_x.size(0);
  if (u0 >= n) {
    n = u0;
  }

  if (b_x.size(0) > n) {
    k_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }

  // Flatten input to row
  obj->x.set_size(1, b_x.size(0));
  n = b_x.size(0);
  for (u0 = 0; u0 < n; u0++) {
    obj->x[u0] = b_x[u0];
  }

  // Data vector
  obj->l = b_x.size(0);

  // Elements in the data
  obj->Fs = b_Fs;

  // Sample rate
  obj->t_0 = b_t_0;

  // Time stamp of first element
  obj->t_f = b_t_0 + (static_cast<double>(b_x.size(0)) - 1.0) / b_Fs;

  // Time stamp of last element
  obj->t_nextsegstart[0] = b_t_0;
  obj->t_nextsegstart[1] = b_t_0;

  // This is the time when next
  // segment should start to
  // ensure sufficient overlap.
  // Will need to be updated
  // elsewhere.
  obj->ps_pre = b_ps_pre;
  obj->OLF = 0.5;

  // Overlap Fraction for STFT
  obj->K = rtNaN;

  // Unknown number of pulses.
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
  // Instructions on https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  // maxFs*maxpulsewidth
  // Now actually assign them
  iobj_1.S.set_size(0, 0);
  iobj_1.t.set_size(0);
  iobj_1.f.set_size(0);
  iobj_1.psd.set_size(0);
  iobj_1.wind.set_size(0);
  iobj_1.dt = 0.0;
  iobj_1.T = 0.0;
  obj->stft = &iobj_1;

  // Unknown values but set types
  obj->W.set_size(0, 0);
  obj->Wf.set_size(0);

  // Copy over ps_
  // COPY Creates an exact copy of the pulse stats object as a
  // separate object
  c_ps_pre.set_size(1, b_ps_pre->pl.size(1));
  n = b_ps_pre->pl.size(0) * b_ps_pre->pl.size(1) - 1;
  for (u0 = 0; u0 <= n; u0++) {
    c_ps_pre[u0] = b_ps_pre->pl[u0];
  }

  d_ps_pre.set_size(b_ps_pre->clst.size(0), b_ps_pre->clst.size(1));
  n = b_ps_pre->clst.size(0) * b_ps_pre->clst.size(1) - 1;
  for (u0 = 0; u0 <= n; u0++) {
    d_ps_pre[u0] = b_ps_pre->clst[u0];
  }

  e_ps_pre.set_size(b_ps_pre->cmsk.size(0), b_ps_pre->cmsk.size(1));
  n = b_ps_pre->cmsk.size(0) * b_ps_pre->cmsk.size(1) - 1;
  for (u0 = 0; u0 <= n; u0++) {
    e_ps_pre[u0] = b_ps_pre->cmsk[u0];
  }

  f_ps_pre.set_size(b_ps_pre->cpki.size(0), b_ps_pre->cpki.size(1));
  n = b_ps_pre->cpki.size(0) * b_ps_pre->cpki.size(1) - 1;
  for (u0 = 0; u0 <= n; u0++) {
    f_ps_pre[u0] = b_ps_pre->cpki[u0];
  }

  double g_ps_pre[2];
  g_ps_pre[0] = b_ps_pre->tmplt[0];
  g_ps_pre[1] = b_ps_pre->tmplt[1];
  obj_out = iobj_0.b_init(b_ps_pre->t_p, b_ps_pre->t_ip, b_ps_pre->t_ipu,
    b_ps_pre->t_ipj, b_ps_pre->fp, b_ps_pre->fstart, b_ps_pre->fend, g_ps_pre,
    b_ps_pre->mode, c_ps_pre, d_ps_pre, e_ps_pre, f_ps_pre);

  // ,...
  // obj.thresh);
  obj->ps_pos = obj_out;

  // Current stats are same as previous during construction
  obj->setprioridependentprops(b_ps_pre);
  obj->thresh = b_thresh;
  return obj;
}

//
// PROCESS is a method that runs the pulse detection algorithm on
// a waveform object.
//
// This method is is intended to be run on a waveform
// segment that is short enought to contain at most K+1 pulses,
// but at least K pulses, where K is the number of pulses to be
// summed. Input paramets allow for the selection of search mode,
// the focus mode, and the selection mode. The search mode
// ('mode') is eithr 'discovery', 'confirmation', or 'tracking'
// and selection of each of these affects how priori information
// is used to reduce the frequency or time scope of the pulse
// search. This also affects how the resulting ps_pos property of
// the waveform is set. The false alarm probabilty is used along
// with the decision table in order to determine the thresholds
// used for the decision making on pulse detection.
//
// Arguments    : char mode
//                const coder::array<double, 2U> &excluded_freq_bands
// Return Type  : void
//
void waveform::process(char mode, const coder::array<double, 2U>
  &excluded_freq_bands)
{
  static rtBoundsCheckInfo ab_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1485,                              // lineNo
    56,                                // colNo
    "obj.ps_pre.pl",                   // aName
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo bb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1490,                              // lineNo
    56,                                // colNo
    "obj.ps_pre.pl",                   // aName
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo cb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1748,                              // lineNo
    58,                                // colNo
    "pk_ind",                          // aName
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo db_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1748,                              // lineNo
    51,                                // colNo
    "candidatelist",                   // aName
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo eb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1773,                              // lineNo
    65,                                // colNo
    "conflog",                         // aName
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo fb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1773,                              // lineNo
    43,                                // colNo
    "obj.ps_pos.pl(ip)",               // aName
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo gb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1807,                              // lineNo
    35,                                // colNo
    "obj.ps_pos.pl(tick)",             // aName
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo hb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1810,                              // lineNo
    37,                                // colNo
    "obj.ps_pos.clst(tick)",           // aName
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ib_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1672,                              // lineNo
    58,                                // colNo
    "pk_ind",                          // aName
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo jb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1672,                              // lineNo
    51,                                // colNo
    "candidatelist",                   // aName
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo kb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1703,                              // lineNo
    61,                                // colNo
    "conflog",                         // aName
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo lb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1703,                              // lineNo
    39,                                // colNo
    "obj.ps_pos.pl(ip)",               // aName
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo mb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1715,                              // lineNo
    35,                                // colNo
    "obj.ps_pos.pl(tick)",             // aName
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo nb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1718,                              // lineNo
    37,                                // colNo
    "obj.ps_pos.clst(tick)",           // aName
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ob_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1574,                              // lineNo
    58,                                // colNo
    "pk_ind",                          // aName
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo pb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1574,                              // lineNo
    51,                                // colNo
    "candidatelist",                   // aName
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo qb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1618,                              // lineNo
    61,                                // colNo
    "conflog",                         // aName
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo rb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1618,                              // lineNo
    39,                                // colNo
    "obj.ps_pos.pl(ip)",               // aName
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo sb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1635,                              // lineNo
    35,                                // colNo
    "obj.ps_pos.pl(tick)",             // aName
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo tb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1638,                              // lineNo
    37,                                // colNo
    "obj.ps_pos.clst(tick)",           // aName
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    0                                  // checkKind
  };

  static rtDoubleCheckInfo s_emlrtDCI{ 1748,// lineNo
    58,                                // colNo
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo t_emlrtDCI{ 1748,// lineNo
    51,                                // colNo
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo u_emlrtDCI{ 1672,// lineNo
    58,                                // colNo
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo v_emlrtDCI{ 1672,// lineNo
    51,                                // colNo
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo w_emlrtDCI{ 1574,// lineNo
    58,                                // colNo
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo x_emlrtDCI{ 1574,// lineNo
    51,                                // colNo
    "waveform/process",                // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/waveform.m",// pName
    1                                  // checkKind
  };

  static const char b_cv[8]{ 'i', 'n', 'f', 'o', 'r', 'm', 'e', 'd' };

  static const char cv3[7]{ 'c', 'o', 'n', 'f', 'i', 'r', 'm' };

  static const char b_cv2[6]{ 's', 'e', 'a', 'r', 'c', 'h' };

  static const char b_cv1[5]{ 'n', 'a', 'i', 'v', 'e' };

  static const char cv4[5]{ 't', 'r', 'a', 'c', 'k' };

  pulsestats *obj;
  coder::array<c_struct_T, 2U> _in;
  coder::array<c_struct_T, 2U> candidatelist;
  coder::array<double, 1U> pk_ind;
  coder::array<char, 2U> varargin_1;
  coder::array<boolean_T, 2U> b_varargin_1;
  coder::array<boolean_T, 2U> conflog;
  coder::array<boolean_T, 2U> msk;
  coder::array<boolean_T, 1U> c_varargin_1;
  coder::array<boolean_T, 1U> r;
  c_struct_T r1;
  double b_x;
  double c_x;
  double d_x;
  double selected_ind;
  double validatedHoleFilling_idx_1;
  int freq_search_type_size[2];
  int runmode_size[2];
  int time_search_type_size[2];
  int b_index;
  int i;
  int i1;
  char freq_search_type_data[8];
  char time_search_type_data[8];
  char runmode_data[7];
  boolean_T have_priori_freq_band;
  boolean_T have_priori_time;

  // Mode description:
  // Processing can be done in either discovery 'D', confirmation
  // 'C', or tracking 'T' modes. The selection of these modes
  // affects how time and frequency focusing is used to improve
  // processing time. In discovery mode is used for intial
  // detection when little is know about where pulses might exist
  // in time or frequeny. Confirmation is similar to discovery, but
  // is used after an initial detection to confirm that the
  // subsequent pulses exists where they should based on
  // forecasting from a previous detection. After pulses are
  // confirmed, the mode can be set to tracking which reduces the
  // frequency and time search space to improve processing speed.
  //
  //    Discovey mode:      'D'
  //        This mode uses no priori information and looks at the
  //        widest possible time bounds for pulses. If there is
  //        no priori frequency information in the ps_pre property
  //        or the focus mode is set to 'open', discovery mode
  //        will search across all frequencies. Otherwise it
  //        will search over all frequencies. If it detects pulses
  //        in the dataset that exceed the decision threshold, the
  //        posterior pulsestats object will be set to a mode of
  //        'C' so that the next segment processed will run in
  //        confirmation mode. If a detection or set of detections
  //        are made, the 'selection_mode' input will dictate how
  //        the posterior pulsestat property is set.
  //
  //    Confirmation mode:  'C'
  //        This mode is similar to discovery mode, but after a
  //        detection is made, it will compare the spectral and
  //        temporal location of the detected pulses to determine
  //        if the pulses align with what could be predicted from
  //        the pulses listed in the priori information of the
  //        waveform getting processed. If these pulses are
  //        confirmed, then the posteriori pulsestats mode property
  //        is set to 'T' so that subsequent segments can move to
  //        tracking mode. If pulses are detected but not where
  //        they should have been based on predictions from the
  //        priori, then the posteriori mode is set back to 'D'.
  //
  //    Tracking mode:      'T'
  //        Tracking mode uses priori pulsestats information in
  //        order to reduce the time and/or frequency space used
  //        for detection. The significantly speed processing
  //        speeds, but can miss detections if pulses move in time
  //        from where they should be based on a previous segment's
  //        detection. If using tracking mode and pulses aren't
  //        detected (scores don't meet the decision threhold), the
  //        posteriori pulsestats mode is set back to 'D'.
  //
  // INPUTS:
  //    mode    The search mode used. Must be string 'D' for
  //            discovery, 'C' for confirmation, or 'T' for
  //            tracking.
  //    focus_mode  How the algorithm decided whether or not to
  //            focus on a particular pulse. This mode can be set
  //            to 'open' wherein no focusing is done and the
  //            processing always proceeds along in discovery mode
  //            without narrowing the frequency or time span of the
  //            search. If this mode is set to 'focus', the method
  //            will allow for down selection of detected pulses
  //            for subsequent processing. The method of this
  //            downselection is determined by the 'selection_mode'
  //            input.
  //    selection_mode  How the algorithm narrows the scope for
  //            subsequent segment processing. This input is
  //            used when in 'discovery' mode. If pulses are
  //            detected, the focus mode will dictate which
  //            pulse is focused on for subsequent data
  //            segments. Focus mode can be set to 'most' to
  //            focus on the most powerful detecte pulse or
  //            'least' to focus on the least powerful detected
  //            pulse. See DETECT.M for more
  //            information on these focus modes.
  //    zetas   A vector of fractions of the DFT frequency bin
  //            width for which to compute and include in the
  //            spectral weighting matrix output. If no interbin
  //            shifting is desired, enter 0. Range of inputs
  //            [0,1). See WEIGHTINGMATRIX.m for more information
  //            on this vector.
  //    PF      A numeric probability of false alarm for decision
  //            threshold determination. Value range of PF must be
  //            within the pf property vector of the decision_table
  //            input.
  //    decision_table  A structure with two properties - 'pf' and
  //            'values'. The pf property is a vector of false alarm
  //            probabilities in decimal form (not percentage). The
  //            values property is vector of the same size as pf
  //            with the decision thresholds for the corresponding
  //            false alarm probability.
  //    excluded_freq_bands   nx2    matrix of bands of
  //                                 frequencies to exclude in
  //                                 the search. This is useful if
  //                                 there has already been a tag
  //                                 found and you want to exclude
  //                                 that band when looking for
  //                                 other frequencies. The lower
  //                                 frequecie of the band should
  //                                 be in the first column and
  //                                 the upper should be in the
  //                                 second. This is only used in
  //                                 the naive frequency search
  //                                 mode. Leave empty [] if no
  //                                 exclusion zones are
  //                                 necessary.
  //
  // OUTPUTS:
  //    None. This method updates the ps_pos property of the
  //    waveform object 'obj'.
  //
  //             %%
  //
  //         %% CHECK MODE ENTRANCE REQUIREMENTS
  // Determine if there is sufficient priori for the operation of each
  // mode. Check to see if they have entries and if they are finite (not Nan or Inf).
  // We just catch that and then set the have_priori flag to false.
  selected_ind = ps_pre->fstart;
  validatedHoleFilling_idx_1 = ps_pre->fend;
  std::printf("ps_pre.fstart and ps_pre.fend at beginning of PROCESS call: \t %f \t to \t %f.\n",
              selected_ind, validatedHoleFilling_idx_1);
  std::fflush(stdout);

  // (1) is for coder so it knows it is a scalar
  selected_ind = ps_pos->fstart;
  validatedHoleFilling_idx_1 = ps_pos->fend;
  std::printf("ps_pos.fstart and ps_pos.fend at beginning of PROCESS call: \t %f \t to \t %f.\n",
              selected_ind, validatedHoleFilling_idx_1);
  std::fflush(stdout);

  // (1) is for coder so it knows it is a scalar
  selected_ind = ps_pre->fstart;
  validatedHoleFilling_idx_1 = ps_pre->fend;
  have_priori_freq_band = ((!std::isinf(selected_ind)) && (!std::isnan
    (selected_ind)) && ((!std::isinf(validatedHoleFilling_idx_1)) && (!std::
    isnan(validatedHoleFilling_idx_1))));
  i = ps_pre->pl.size(1);
  i1 = ps_pre->pl.size(1);
  if ((i1 < 1) || (i1 > i)) {
    rtDynamicBoundsError(i1, 1, i, ab_emlrtBCI);
  }

  i = ps_pre->pl.size(1);
  i1 = ps_pre->pl.size(1);
  if ((i1 < 1) || (i1 > i)) {
    rtDynamicBoundsError(i1, 1, i, bb_emlrtBCI);
  }

  selected_ind = ps_pre->pl[i1 - 1].t_0;
  validatedHoleFilling_idx_1 = ps_pre->t_p;
  b_x = ps_pre->t_ip;
  c_x = ps_pre->t_ipu;
  d_x = ps_pre->t_ipj;
  have_priori_time = ((!std::isinf(selected_ind)) && (!std::isnan(selected_ind))
                      && ((!std::isinf(validatedHoleFilling_idx_1)) && (!std::
    isnan(validatedHoleFilling_idx_1))) && ((!std::isinf(b_x)) && (!std::isnan
    (b_x))) && ((!std::isinf(c_x)) && (!std::isnan(c_x))) && ((!std::isinf(d_x))
    && (!std::isnan(d_x))));

  // Enforce entry requirements on the modes so we don't get errors in
  // the 'C' and 'T' modes, as they required priori freq and time info.
  if ((mode == 'T') && (!have_priori_time) && (!have_priori_freq_band)) {
    // if strcmp(mode,'C'); attemptedmodestring = 'confirmation';end
    mode = 'D';
  }

  if ((mode == 'C') && (!have_priori_time)) {
    mode = 'D';
  }

  if ((mode == 'I') && (!have_priori_freq_band)) {
    mode = 'D';
  }

  if (mode == 'D') {
    b_index = 0;
  } else if (mode == 'I') {
    b_index = 1;
  } else if (mode == 'C') {
    b_index = 2;
  } else if (mode == 'T') {
    b_index = 3;
  } else {
    b_index = -1;
  }

  switch (b_index) {
   case 0:
    {
      freq_search_type_size[0] = 1;
      freq_search_type_size[1] = 5;
      time_search_type_size[0] = 1;
      time_search_type_size[1] = 5;
      for (i = 0; i < 5; i++) {
        char c;
        c = b_cv1[i];
        freq_search_type_data[i] = c;
        time_search_type_data[i] = c;
      }

      runmode_size[0] = 1;
      runmode_size[1] = 6;
      for (i = 0; i < 6; i++) {
        runmode_data[i] = b_cv2[i];
      }
    }
    break;

   case 1:
    freq_search_type_size[0] = 1;
    freq_search_type_size[1] = 8;
    for (i = 0; i < 8; i++) {
      freq_search_type_data[i] = b_cv[i];
    }

    time_search_type_size[0] = 1;
    time_search_type_size[1] = 5;
    for (i = 0; i < 5; i++) {
      time_search_type_data[i] = b_cv1[i];
    }

    runmode_size[0] = 1;
    runmode_size[1] = 6;
    for (i = 0; i < 6; i++) {
      runmode_data[i] = b_cv2[i];
    }
    break;

   case 2:
    {
      freq_search_type_size[0] = 1;
      freq_search_type_size[1] = 5;
      time_search_type_size[0] = 1;
      time_search_type_size[1] = 5;
      for (i = 0; i < 5; i++) {
        char c;
        c = b_cv1[i];
        freq_search_type_data[i] = c;
        time_search_type_data[i] = c;
      }

      runmode_size[0] = 1;
      runmode_size[1] = 7;
      for (i = 0; i < 7; i++) {
        runmode_data[i] = cv3[i];
      }
    }
    break;

   case 3:
    {
      freq_search_type_size[0] = 1;
      freq_search_type_size[1] = 8;
      time_search_type_size[0] = 1;
      time_search_type_size[1] = 8;
      for (i = 0; i < 8; i++) {
        char c;
        c = b_cv[i];
        freq_search_type_data[i] = c;
        time_search_type_data[i] = c;
      }

      runmode_size[0] = 1;
      runmode_size[1] = 5;
      for (i = 0; i < 5; i++) {
        runmode_data[i] = cv4[i];
      }
    }
    break;

   default:
    {
      freq_search_type_size[0] = 1;
      freq_search_type_size[1] = 5;
      time_search_type_size[0] = 1;
      time_search_type_size[1] = 5;
      for (i = 0; i < 5; i++) {
        char c;
        c = b_cv1[i];
        freq_search_type_data[i] = c;
        time_search_type_data[i] = c;
      }

      runmode_size[0] = 1;
      runmode_size[1] = 6;
      for (i = 0; i < 6; i++) {
        runmode_data[i] = b_cv2[i];
      }
    }
    break;
  }

  std::printf("================ RUNNING DETECTION ================\n");
  std::fflush(stdout);
  varargin_1.set_size(1, freq_search_type_size[1] + 1);
  b_index = freq_search_type_size[1];
  for (i = 0; i < b_index; i++) {
    varargin_1[i] = freq_search_type_data[i];
  }

  varargin_1[freq_search_type_size[1]] = '\x00';
  std::printf("FREQ SEARCH MODE: %s \n", &varargin_1[0]);
  std::fflush(stdout);
  varargin_1.set_size(1, time_search_type_size[1] + 1);
  b_index = time_search_type_size[1];
  for (i = 0; i < b_index; i++) {
    varargin_1[i] = time_search_type_data[i];
  }

  varargin_1[time_search_type_size[1]] = '\x00';
  std::printf("TIME SEARCH MODE: %s \n", &varargin_1[0]);
  std::fflush(stdout);
  if (coder::internal::b_strcmp(runmode_data, runmode_size)) {
    b_index = 0;
  } else if (coder::internal::c_strcmp(runmode_data, runmode_size)) {
    b_index = 1;
  } else if (coder::internal::d_strcmp(runmode_data, runmode_size)) {
    b_index = 2;
  } else {
    b_index = -1;
  }

  switch (b_index) {
   case 0:
    //             %% SEARCH RUN MODE
    std::printf("DETECTING IN SEARCH MODE.\n");
    std::fflush(stdout);

    // Find all the potential pulses in the dataset
    findpulse(time_search_type_data, time_search_type_size,
              freq_search_type_data, freq_search_type_size, excluded_freq_bands,
              candidatelist, msk, pk_ind);
    coder::internal::horzcatStructList(candidatelist, b_varargin_1);
    b_index = b_varargin_1.size(1);
    c_varargin_1 = b_varargin_1.reshape(b_index);
    have_priori_freq_band = coder::internal::allOrAny_anonFcn1(c_varargin_1);
    if (have_priori_freq_band) {
      r.set_size(pk_ind.size(0));
      b_index = pk_ind.size(0);
      for (i = 0; i < b_index; i++) {
        r[i] = std::isnan(pk_ind[i]);
      }

      coder::internal::allOrAny_anonFcn1(r);
    } else {
      //  Determine which peak to focus depending on the selection mode
      //  Select a peak if we found had at least one detection
    }

    r.set_size(pk_ind.size(0));
    b_index = pk_ind.size(0);
    for (i = 0; i < b_index; i++) {
      r[i] = !std::isnan(pk_ind[i]);
    }

    if (coder::internal::ifWhileCond(r)) {
      selected_ind = selectpeakindex(candidatelist, pk_ind);

      // Set the pulselist property in the ps_pos based on the
      // downselection of pulses
      obj = ps_pos;
      if (selected_ind != static_cast<int>(std::floor(selected_ind))) {
        rtIntegerError(selected_ind, w_emlrtDCI);
      }

      if ((static_cast<int>(selected_ind) < 1) || (static_cast<int>(selected_ind)
           > pk_ind.size(0))) {
        rtDynamicBoundsError(static_cast<int>(selected_ind), 1, pk_ind.size(0),
                             ob_emlrtBCI);
      }

      selected_ind = pk_ind[static_cast<int>(selected_ind) - 1];
      if (selected_ind != static_cast<int>(std::floor(selected_ind))) {
        rtIntegerError(selected_ind, x_emlrtDCI);
      }

      if ((static_cast<int>(selected_ind) < 1) || (static_cast<int>(selected_ind)
           > candidatelist.size(0))) {
        rtDynamicBoundsError(static_cast<int>(selected_ind), 1,
                             candidatelist.size(0), pb_emlrtBCI);
      }

      obj->pl.set_size(1, candidatelist.size(1));
      b_index = candidatelist.size(1);
      for (i = 0; i < b_index; i++) {
        obj->pl[i] = candidatelist[(static_cast<int>(selected_ind) +
          candidatelist.size(0) * i) - 1];
      }
    } else {
      // If nothing above threshold was found, fill with empty
      // pulse object
      obj = ps_pos;
      r1.A = makepulsestruc(r1.t_next, r1.mode, r1.P, r1.SNR, r1.yw, r1.t_0,
                            r1.t_f, r1.fp, r1.fstart, r1.fend, r1.det_dec,
                            r1.con_dec);
      obj->pl.set_size(1, 1);
      obj->pl[0] = r1;
    }

    // Record all candidates for posterity
    obj = ps_pos;
    obj->clst.set_size(candidatelist.size(0), candidatelist.size(1));
    b_index = candidatelist.size(0) * candidatelist.size(1);
    for (i = 0; i < b_index; i++) {
      obj->clst[i] = candidatelist[i];
    }

    obj = ps_pos;
    obj->cmsk.set_size(msk.size(0), msk.size(1));
    b_index = msk.size(0) * msk.size(1);
    for (i = 0; i < b_index; i++) {
      obj->cmsk[i] = msk[i];
    }

    obj = ps_pos;
    obj->cpki.set_size(pk_ind.size(0), 1);
    b_index = pk_ind.size(0);
    conflog.set_size(1, 1);
    conflog[0] = false;

    // Set to all false. Needed
    //  Detection?
    r.set_size(pk_ind.size(0));
    for (i = 0; i < b_index; i++) {
      obj->cpki[i] = pk_ind[i];
      r[i] = !std::isnan(pk_ind[i]);
    }

    if (coder::internal::ifWhileCond(r)) {
      // If move to confirm pulses that were real but the pulses before them were
      // noise, the real pulses will not be confirmed and the detector will move
      // back to search mode. Then when it gets to this point, it should try to
      // confirm against the previous detections.
      confirmpulses(this, conflog);
      b_index = conflog.size(0);
      c_varargin_1 = conflog.reshape(b_index);
      have_priori_freq_band = coder::internal::allOrAny_anonFcn1(c_varargin_1);

      //  %True ->
      //  %Update confirmation property for each pulse. False
      //  %recorded for confirmation property since we are
      //  %currently in discovery mode and can't confirm anything
      //  %yet.
      //  for ip = 1:length(obj.ps_pos.pl)
      //      obj.ps_pos.pl(ip).con_dec = false;
      //  end
      //
      //  %   Update Mode Recommendation -> Confirmation
      //  obj.ps_pos.mode = 'C';
    } else {
      // Dection was not made
      //  obj.ps_pos.mode = 'S';%'D';
      have_priori_freq_band = false;
    }

    //  Confirmation?
    if (have_priori_freq_band) {
      i = ps_pos->pl.size(1) - 1;
      for (int ip{0}; ip <= i; ip++) {
        _in.set_size(1, ps_pos->pl.size(1));
        b_index = ps_pos->pl.size(1);
        for (i1 = 0; i1 < b_index; i1++) {
          _in[i1] = ps_pos->pl[i1];
        }

        if (ip + 1 > conflog.size(0)) {
          rtDynamicBoundsError(ip + 1, 1, conflog.size(0), qb_emlrtBCI);
        }

        if (ip + 1 > _in.size(1)) {
          rtDynamicBoundsError(ip + 1, 1, _in.size(1), rb_emlrtBCI);
        }

        _in[ip].con_dec = conflog[ip];
        obj = ps_pos;
        obj->pl.set_size(1, _in.size(1));
        b_index = _in.size(1);
        for (i1 = 0; i1 < b_index; i1++) {
          obj->pl[i1] = _in[i1];
        }
      }

      obj = ps_pos;
      obj->mode = 'T';
    } else {
      r.set_size(pk_ind.size(0));
      b_index = pk_ind.size(0);
      for (i = 0; i < b_index; i++) {
        r[i] = !std::isnan(pk_ind[i]);
      }

      if (coder::internal::ifWhileCond(r)) {
        // Detection, no confirmation  -> Confirmation mode
        obj = ps_pos;
        obj->mode = 'C';
      } else {
        // No detection, no confirmation  -> Search mode
        obj = ps_pos;
        obj->mode = 'S';
      }
    }

    // Set the mode in the pulse and candidate listing for
    // records. This records the mode that was used in the
    // detection of the record pulses. This is useful for
    // debugging.
    i = ps_pos->pl.size(1) - 1;
    for (int ip{0}; ip <= i; ip++) {
      _in.set_size(1, ps_pos->pl.size(1));
      b_index = ps_pos->pl.size(1);
      for (i1 = 0; i1 < b_index; i1++) {
        _in[i1] = ps_pos->pl[i1];
      }

      if (ip + 1 > _in.size(1)) {
        rtDynamicBoundsError(ip + 1, 1, _in.size(1), sb_emlrtBCI);
      }

      _in[_in.size(0) * ip].mode.set_size(1, _in[_in.size(0) * ip].mode.size(1));
      if (ip + 1 > _in.size(1)) {
        rtDynamicBoundsError(ip + 1, 1, _in.size(1), sb_emlrtBCI);
      }

      _in[_in.size(0) * ip].mode.set_size(_in[_in.size(0) * ip].mode.size(0), 1);
      if (ip + 1 > _in.size(1)) {
        rtDynamicBoundsError(ip + 1, 1, _in.size(1), sb_emlrtBCI);
      }

      _in[ip].mode[0] = mode;
      obj = ps_pos;
      obj->pl.set_size(1, _in.size(1));
      b_index = _in.size(1);
      for (i1 = 0; i1 < b_index; i1++) {
        obj->pl[i1] = _in[i1];
      }

      // 'D';
    }

    i = ps_pos->clst.size(0) * ps_pos->clst.size(1) - 1;
    for (int ip{0}; ip <= i; ip++) {
      candidatelist.set_size(ps_pos->clst.size(0), ps_pos->clst.size(1));
      b_index = ps_pos->clst.size(0) * ps_pos->clst.size(1);
      for (i1 = 0; i1 < b_index; i1++) {
        candidatelist[i1] = ps_pos->clst[i1];
      }

      b_index = candidatelist.size(0) * candidatelist.size(1);
      if ((static_cast<int>(static_cast<unsigned int>(ip) + 1U) < 1) || (
           static_cast<int>(static_cast<unsigned int>(ip) + 1U) > b_index)) {
        rtDynamicBoundsError(static_cast<int>(static_cast<unsigned int>(ip) + 1U),
                             1, b_index, tb_emlrtBCI);
      }

      candidatelist[ip].mode.set_size(1, candidatelist[ip].mode.size(1));
      candidatelist[ip].mode.set_size(candidatelist[ip].mode.size(0), 1);
      candidatelist[ip].mode[0] = mode;
      obj = ps_pos;
      obj->clst.set_size(candidatelist.size(0), candidatelist.size(1));
      for (i1 = 0; i1 < b_index; i1++) {
        obj->clst[i1] = candidatelist[i1];
      }

      //  'D';
    }

    selected_ind = ps_pre->fstart;
    validatedHoleFilling_idx_1 = ps_pre->fend;
    std::printf("ps_pre.fstart and ps_pre.fend at the end Detection search : \t %f \t to \t %f.\n",
                selected_ind, validatedHoleFilling_idx_1);
    std::fflush(stdout);

    // (1) is for coder so it knows it is a scalar
    selected_ind = ps_pos->fstart;
    validatedHoleFilling_idx_1 = ps_pos->fend;
    std::printf("ps_pos.fstart and ps_pos.fend at the end Detection search : \t %f \t to \t %f.\n",
                selected_ind, validatedHoleFilling_idx_1);
    std::fflush(stdout);

    // (1) is for coder so it knows it is a scalar
    //             %% CONFIRMATION MODE
    break;

   case 1:
    std::printf("DETECTING IN CONFIRMATION MODE.\n");
    std::fflush(stdout);

    // Find all the potential pulses in the dataset
    findpulse(time_search_type_data, time_search_type_size,
              freq_search_type_data, freq_search_type_size, excluded_freq_bands,
              candidatelist, msk, pk_ind);
    coder::internal::horzcatStructList(candidatelist, b_varargin_1);
    b_index = b_varargin_1.size(1);
    c_varargin_1 = b_varargin_1.reshape(b_index);
    have_priori_freq_band = coder::internal::allOrAny_anonFcn1(c_varargin_1);
    if (have_priori_freq_band) {
      r.set_size(pk_ind.size(0));
      b_index = pk_ind.size(0);
      for (i = 0; i < b_index; i++) {
        r[i] = std::isnan(pk_ind[i]);
      }

      coder::internal::allOrAny_anonFcn1(r);
    } else {
      // At least one pulse group met the threshold
    }

    r.set_size(pk_ind.size(0));
    b_index = pk_ind.size(0);
    for (i = 0; i < b_index; i++) {
      r[i] = !std::isnan(pk_ind[i]);
    }

    if (coder::internal::ifWhileCond(r)) {
      selected_ind = selectpeakindex(candidatelist, pk_ind);

      // Record the detection pulses
      // We only use the highest power pulse group for now
      // because if we are in confirmation mode, we only allow
      // for the selection mode to be 'most'
      obj = ps_pos;
      if (selected_ind != static_cast<int>(std::floor(selected_ind))) {
        rtIntegerError(selected_ind, u_emlrtDCI);
      }

      if ((static_cast<int>(selected_ind) < 1) || (static_cast<int>(selected_ind)
           > pk_ind.size(0))) {
        rtDynamicBoundsError(static_cast<int>(selected_ind), 1, pk_ind.size(0),
                             ib_emlrtBCI);
      }

      selected_ind = pk_ind[static_cast<int>(selected_ind) - 1];
      if (selected_ind != static_cast<int>(std::floor(selected_ind))) {
        rtIntegerError(selected_ind, v_emlrtDCI);
      }

      if ((static_cast<int>(selected_ind) < 1) || (static_cast<int>(selected_ind)
           > candidatelist.size(0))) {
        rtDynamicBoundsError(static_cast<int>(selected_ind), 1,
                             candidatelist.size(0), jb_emlrtBCI);
      }

      obj->pl.set_size(1, candidatelist.size(1));
      b_index = candidatelist.size(1);
      for (i = 0; i < b_index; i++) {
        obj->pl[i] = candidatelist[(static_cast<int>(selected_ind) +
          candidatelist.size(0) * i) - 1];
      }
    } else {
      // If nothing above threshold was found, fill with empty
      // pulse object
      obj = ps_pos;
      r1.A = makepulsestruc(r1.t_next, r1.mode, r1.P, r1.SNR, r1.yw, r1.t_0,
                            r1.t_f, r1.fp, r1.fstart, r1.fend, r1.det_dec,
                            r1.con_dec);
      obj->pl.set_size(1, 1);
      obj->pl[0] = r1;
    }

    // Record all candidates for posterity
    obj = ps_pos;
    obj->clst.set_size(candidatelist.size(0), candidatelist.size(1));
    b_index = candidatelist.size(0) * candidatelist.size(1);
    for (i = 0; i < b_index; i++) {
      obj->clst[i] = candidatelist[i];
    }

    obj = ps_pos;
    obj->cmsk.set_size(msk.size(0), msk.size(1));
    b_index = msk.size(0) * msk.size(1);
    for (i = 0; i < b_index; i++) {
      obj->cmsk[i] = msk[i];
    }

    obj = ps_pos;
    obj->cpki.set_size(pk_ind.size(0), 1);
    b_index = pk_ind.size(0);
    conflog.set_size(1, 1);
    conflog[0] = false;

    // Set to all false. Needed
    //  Detection?
    r.set_size(pk_ind.size(0));
    for (i = 0; i < b_index; i++) {
      obj->cpki[i] = pk_ind[i];
      r[i] = !std::isnan(pk_ind[i]);
    }

    if (coder::internal::ifWhileCond(r)) {
      confirmpulses(this, conflog);

      // Confirmation?
      b_index = conflog.size(0);
      c_varargin_1 = conflog.reshape(b_index);
      have_priori_freq_band = coder::internal::allOrAny_anonFcn1(c_varargin_1);
    } else {
      // False ->
      // Set confirmation = False
      have_priori_freq_band = false;
    }

    if (have_priori_freq_band) {
      i = ps_pos->pl.size(1) - 1;
      for (int ip{0}; ip <= i; ip++) {
        _in.set_size(1, ps_pos->pl.size(1));
        b_index = ps_pos->pl.size(1);
        for (i1 = 0; i1 < b_index; i1++) {
          _in[i1] = ps_pos->pl[i1];
        }

        if (ip + 1 > conflog.size(0)) {
          rtDynamicBoundsError(ip + 1, 1, conflog.size(0), kb_emlrtBCI);
        }

        if (ip + 1 > _in.size(1)) {
          rtDynamicBoundsError(ip + 1, 1, _in.size(1), lb_emlrtBCI);
        }

        _in[ip].con_dec = conflog[ip];
        obj = ps_pos;
        obj->pl.set_size(1, _in.size(1));
        b_index = _in.size(1);
        for (i1 = 0; i1 < b_index; i1++) {
          obj->pl[i1] = _in[i1];
        }
      }

      obj = ps_pos;
      obj->mode = 'T';
    } else {
      obj = ps_pos;
      obj->mode = 'S';
    }

    // Set the mode in the pulse and candidate listing for
    // records. This records the mode that was used in the
    // detection of the record pulses. This is useful for
    // debugging.
    i = ps_pos->pl.size(1) - 1;
    for (int ip{0}; ip <= i; ip++) {
      _in.set_size(1, ps_pos->pl.size(1));
      b_index = ps_pos->pl.size(1);
      for (i1 = 0; i1 < b_index; i1++) {
        _in[i1] = ps_pos->pl[i1];
      }

      if (ip + 1 > _in.size(1)) {
        rtDynamicBoundsError(ip + 1, 1, _in.size(1), mb_emlrtBCI);
      }

      _in[_in.size(0) * ip].mode.set_size(1, _in[_in.size(0) * ip].mode.size(1));
      if (ip + 1 > _in.size(1)) {
        rtDynamicBoundsError(ip + 1, 1, _in.size(1), mb_emlrtBCI);
      }

      _in[_in.size(0) * ip].mode.set_size(_in[_in.size(0) * ip].mode.size(0), 1);
      if (ip + 1 > _in.size(1)) {
        rtDynamicBoundsError(ip + 1, 1, _in.size(1), mb_emlrtBCI);
      }

      _in[ip].mode[0] = mode;
      obj = ps_pos;
      obj->pl.set_size(1, _in.size(1));
      b_index = _in.size(1);
      for (i1 = 0; i1 < b_index; i1++) {
        obj->pl[i1] = _in[i1];
      }

      // 'C';
    }

    i = ps_pos->clst.size(0) * ps_pos->clst.size(1) - 1;
    for (int ip{0}; ip <= i; ip++) {
      candidatelist.set_size(ps_pos->clst.size(0), ps_pos->clst.size(1));
      b_index = ps_pos->clst.size(0) * ps_pos->clst.size(1);
      for (i1 = 0; i1 < b_index; i1++) {
        candidatelist[i1] = ps_pos->clst[i1];
      }

      b_index = candidatelist.size(0) * candidatelist.size(1);
      if ((static_cast<int>(static_cast<unsigned int>(ip) + 1U) < 1) || (
           static_cast<int>(static_cast<unsigned int>(ip) + 1U) > b_index)) {
        rtDynamicBoundsError(static_cast<int>(static_cast<unsigned int>(ip) + 1U),
                             1, b_index, nb_emlrtBCI);
      }

      candidatelist[ip].mode.set_size(1, candidatelist[ip].mode.size(1));
      candidatelist[ip].mode.set_size(candidatelist[ip].mode.size(0), 1);
      candidatelist[ip].mode[0] = mode;
      obj = ps_pos;
      obj->clst.set_size(candidatelist.size(0), candidatelist.size(1));
      for (i1 = 0; i1 < b_index; i1++) {
        obj->clst[i1] = candidatelist[i1];
      }

      // 'C';
    }

    selected_ind = ps_pre->fstart;
    validatedHoleFilling_idx_1 = ps_pre->fend;
    std::printf("ps_pre.fstart and ps_pre.fend at the end Confirmation search : \t %f \t to \t %f.\n",
                selected_ind, validatedHoleFilling_idx_1);
    std::fflush(stdout);

    // (1) is for coder so it knows it is a scalar
    selected_ind = ps_pos->fstart;
    validatedHoleFilling_idx_1 = ps_pos->fend;
    std::printf("ps_pos.fstart and ps_pos.fend at the end Confirmation search : \t %f \t to \t %f.\n",
                selected_ind, validatedHoleFilling_idx_1);
    std::fflush(stdout);

    // (1) is for coder so it knows it is a scalar
    break;

   case 2:
    //                 %% TRACKING MODE
    std::printf("DETECTING IN TRACKING MODE.\n");
    std::fflush(stdout);

    // Find all the potential pulses in the dataset
    findpulse(time_search_type_data, time_search_type_size,
              freq_search_type_data, freq_search_type_size, excluded_freq_bands,
              candidatelist, msk, pk_ind);
    coder::internal::horzcatStructList(candidatelist, b_varargin_1);
    b_index = b_varargin_1.size(1);
    c_varargin_1 = b_varargin_1.reshape(b_index);
    have_priori_freq_band = coder::internal::allOrAny_anonFcn1(c_varargin_1);
    if (have_priori_freq_band) {
      r.set_size(pk_ind.size(0));
      b_index = pk_ind.size(0);
      for (i = 0; i < b_index; i++) {
        r[i] = std::isnan(pk_ind[i]);
      }

      coder::internal::allOrAny_anonFcn1(r);
    } else {
      // At least one pulse group met the threshold
    }

    r.set_size(pk_ind.size(0));
    b_index = pk_ind.size(0);
    for (i = 0; i < b_index; i++) {
      r[i] = !std::isnan(pk_ind[i]);
    }

    if (coder::internal::ifWhileCond(r)) {
      selected_ind = selectpeakindex(candidatelist, pk_ind);

      // Record the detection pulses
      // We only use the highest power pulse group for now
      // because if we are in confirmation mode, we only allow
      // for the selection mode to be 'most'
      obj = ps_pos;
      if (selected_ind != static_cast<int>(std::floor(selected_ind))) {
        rtIntegerError(selected_ind, s_emlrtDCI);
      }

      if ((static_cast<int>(selected_ind) < 1) || (static_cast<int>(selected_ind)
           > pk_ind.size(0))) {
        rtDynamicBoundsError(static_cast<int>(selected_ind), 1, pk_ind.size(0),
                             cb_emlrtBCI);
      }

      selected_ind = pk_ind[static_cast<int>(selected_ind) - 1];
      if (selected_ind != static_cast<int>(std::floor(selected_ind))) {
        rtIntegerError(selected_ind, t_emlrtDCI);
      }

      if ((static_cast<int>(selected_ind) < 1) || (static_cast<int>(selected_ind)
           > candidatelist.size(0))) {
        rtDynamicBoundsError(static_cast<int>(selected_ind), 1,
                             candidatelist.size(0), db_emlrtBCI);
      }

      obj->pl.set_size(1, candidatelist.size(1));
      b_index = candidatelist.size(1);
      for (i = 0; i < b_index; i++) {
        obj->pl[i] = candidatelist[(static_cast<int>(selected_ind) +
          candidatelist.size(0) * i) - 1];
      }
    } else {
      // Nothing met the threshold for detection
      obj = ps_pos;
      r1.A = makepulsestruc(r1.t_next, r1.mode, r1.P, r1.SNR, r1.yw, r1.t_0,
                            r1.t_f, r1.fp, r1.fstart, r1.fend, r1.det_dec,
                            r1.con_dec);
      obj->pl.set_size(1, 1);
      obj->pl[0] = r1;
    }

    obj = ps_pos;
    obj->clst.set_size(candidatelist.size(0), candidatelist.size(1));
    b_index = candidatelist.size(0) * candidatelist.size(1);
    for (i = 0; i < b_index; i++) {
      obj->clst[i] = candidatelist[i];
    }

    obj = ps_pos;
    obj->cmsk.set_size(msk.size(0), msk.size(1));
    b_index = msk.size(0) * msk.size(1);
    for (i = 0; i < b_index; i++) {
      obj->cmsk[i] = msk[i];
    }

    obj = ps_pos;
    obj->cpki.set_size(pk_ind.size(0), 1);
    b_index = pk_ind.size(0);

    //  Detection?
    r.set_size(pk_ind.size(0));
    for (i = 0; i < b_index; i++) {
      obj->cpki[i] = pk_ind[i];
      r[i] = !std::isnan(pk_ind[i]);
    }

    if (coder::internal::ifWhileCond(r)) {
      // ~isempty(pulselist)%obj.decide(pulselist,PF,decision_table) %Decision on IDed pulses
      // True ->
      confirmpulses(this, conflog);

      // [minstartlog', maxstartlog', freqInBand', conflog']
      b_index = conflog.size(0);
      c_varargin_1 = conflog.reshape(b_index);
      have_priori_freq_band = coder::internal::allOrAny_anonFcn1(c_varargin_1);
      if (have_priori_freq_band) {
        //  	Confirmed?
        //  		True -> Confirmation = True
        have_priori_freq_band = true;

        // Update confirmation property for each pulse
        i = ps_pos->pl.size(1) - 1;
        for (int ip{0}; ip <= i; ip++) {
          // obj.ps_pos.pl(ip).con_dec = true;
          _in.set_size(1, ps_pos->pl.size(1));
          b_index = ps_pos->pl.size(1);
          for (i1 = 0; i1 < b_index; i1++) {
            _in[i1] = ps_pos->pl[i1];
          }

          if (ip + 1 > conflog.size(0)) {
            rtDynamicBoundsError(ip + 1, 1, conflog.size(0), eb_emlrtBCI);
          }

          if (ip + 1 > _in.size(1)) {
            rtDynamicBoundsError(ip + 1, 1, _in.size(1), fb_emlrtBCI);
          }

          _in[ip].con_dec = conflog[ip];
          obj = ps_pos;
          obj->pl.set_size(1, _in.size(1));
          b_index = _in.size(1);
          for (i1 = 0; i1 < b_index; i1++) {
            obj->pl[i1] = _in[i1];
          }
        }

        // Update mode suggestion for next segment processing
        //    Mode -> Tracking
        obj = ps_pos;
        obj->mode = mode;

        // 'T';
      } else {
        //  		False -> Confirmation = False
        have_priori_freq_band = false;
      }
    } else {
      // False ->
      // Set confirmation = False
      have_priori_freq_band = false;
    }

    //  Handle not confirmed
    if (!have_priori_freq_band) {
      // False ->
      // Update confirmation property for each pulse. Don't need to
      // do this since there are no pulses to record a confirmation
      // decision on.
      // Update mode suggestion for next segment processing
      //    Mode -> Discovery
      obj = ps_pos;
      obj->mode = 'S';

      // 'D';
      // obj.ps_pos.updateposteriori(obj.ps_pre,[]);%No pulses to update the posteriori
    }

    // Set the mode in the pulse and candidate listing for
    // records. This records the mode that was used in the
    // detection of the record pulses. This is useful for
    // debugging.
    i = ps_pos->pl.size(1) - 1;
    for (int ip{0}; ip <= i; ip++) {
      _in.set_size(1, ps_pos->pl.size(1));
      b_index = ps_pos->pl.size(1);
      for (i1 = 0; i1 < b_index; i1++) {
        _in[i1] = ps_pos->pl[i1];
      }

      if (ip + 1 > _in.size(1)) {
        rtDynamicBoundsError(ip + 1, 1, _in.size(1), gb_emlrtBCI);
      }

      _in[_in.size(0) * ip].mode.set_size(1, _in[_in.size(0) * ip].mode.size(1));
      if (ip + 1 > _in.size(1)) {
        rtDynamicBoundsError(ip + 1, 1, _in.size(1), gb_emlrtBCI);
      }

      _in[_in.size(0) * ip].mode.set_size(_in[_in.size(0) * ip].mode.size(0), 1);
      if (ip + 1 > _in.size(1)) {
        rtDynamicBoundsError(ip + 1, 1, _in.size(1), gb_emlrtBCI);
      }

      _in[ip].mode[0] = mode;
      obj = ps_pos;
      obj->pl.set_size(1, _in.size(1));
      b_index = _in.size(1);
      for (i1 = 0; i1 < b_index; i1++) {
        obj->pl[i1] = _in[i1];
      }

      //  'T';
    }

    i = ps_pos->clst.size(0) * ps_pos->clst.size(1) - 1;
    for (int ip{0}; ip <= i; ip++) {
      candidatelist.set_size(ps_pos->clst.size(0), ps_pos->clst.size(1));
      b_index = ps_pos->clst.size(0) * ps_pos->clst.size(1);
      for (i1 = 0; i1 < b_index; i1++) {
        candidatelist[i1] = ps_pos->clst[i1];
      }

      b_index = candidatelist.size(0) * candidatelist.size(1);
      if ((static_cast<int>(static_cast<unsigned int>(ip) + 1U) < 1) || (
           static_cast<int>(static_cast<unsigned int>(ip) + 1U) > b_index)) {
        rtDynamicBoundsError(static_cast<int>(static_cast<unsigned int>(ip) + 1U),
                             1, b_index, hb_emlrtBCI);
      }

      candidatelist[ip].mode.set_size(1, candidatelist[ip].mode.size(1));
      candidatelist[ip].mode.set_size(candidatelist[ip].mode.size(0), 1);
      candidatelist[ip].mode[0] = mode;
      obj = ps_pos;
      obj->clst.set_size(candidatelist.size(0), candidatelist.size(1));
      for (i1 = 0; i1 < b_index; i1++) {
        obj->clst[i1] = candidatelist[i1];
      }

      //  'T';
    }

    selected_ind = ps_pre->fstart;
    validatedHoleFilling_idx_1 = ps_pre->fend;
    std::printf("ps_pre.fstart and ps_pre.fend at the end Tracking search : \t %f \t to \t %f.\n",
                selected_ind, validatedHoleFilling_idx_1);
    std::fflush(stdout);

    // (1) is for coder so it knows it is a scalar
    selected_ind = ps_pos->fstart;
    validatedHoleFilling_idx_1 = ps_pos->fend;
    std::printf("ps_pos.fstart and ps_pre.fend at the end Tracking search : \t %f \t to \t %f.\n",
                selected_ind, validatedHoleFilling_idx_1);
    std::fflush(stdout);

    // (1) is for coder so it knows it is a scalar
    break;

   default:
    //                 %% SOMETHING BROKE
    break;
  }
}

//
// SETPRIORIDEPENDENTVARS updates the properties in the
// waveform that are dependent on properties in a pulsestats
// object.
//
// INPUTS:
//    obj     waveform object
//    ps_obj  a pulse stats object
// OUTPUTS:
//    None (This method modifies the waveform object properties)
//
//             %%
//
// Arguments    : const pulsestats *ps_obj
// Return Type  : void
//
void waveform::setprioridependentprops(const pulsestats *ps_obj)
{
  double b_M;
  double b_N;
  double b_n_ip;
  double b_n_ol;
  double b_n_p;
  double b_n_ws;
  double n_ipj;
  double n_ipu;
  double val;

  // GETPRIORIDEPENDENTVARS returns the properties in the
  // waveform that are dependent on prior pulse data estimates. It
  // depends on the waveform properties list Fs etc, as well as
  // pulse stats like t_ip, etc.
  // INPUTS:  ps_obj  1x1 pulse stats object
  // OUTPUTS:  pulse stats object
  b_n_p = ps_obj->t_p * Fs;
  b_n_p = std::ceil(b_n_p);

  // Samples per pulse
  // Number of elements in STFT window
  b_n_ol = OLF * b_n_p;
  b_n_ol = std::floor(b_n_ol);

  // Number of elements overlap in STFT window
  b_n_ws = b_n_p - b_n_ol;

  // Number of elements in each step of STFT
  val = b_n_ws / Fs;

  // Time of each step of STFT
  b_n_ip = ps_obj->t_ip * Fs;
  b_n_ip = std::ceil(b_n_ip);
  n_ipu = ps_obj->t_ipu * Fs;
  n_ipu = std::ceil(n_ipu);
  n_ipj = ps_obj->t_ipj * Fs;
  n_ipj = std::ceil(n_ipj);
  b_N = std::floor(b_n_ip / b_n_ws);
  b_M = std::ceil(n_ipu / b_n_ws);
  n_ipj = std::ceil(n_ipj / b_n_ws);
  n_p = b_n_p;

  // Samples per pulse
  n_w = b_n_p;

  // Number of elements in STFT window
  n_ol = b_n_ol;

  // Number of elements overlap in STFT window
  n_ws = b_n_ws;

  // Number of elements in each step of STFT
  t_ws = val;

  // Time of each step of STFT
  n_ip = b_n_ip;

  // Samples of interpulse duration
  N = b_N;

  // Baseline interpulse duration in units of STFT windows
  M = b_M;

  // Interpulse duration deviation from baselines in units of STFT windows
  J = n_ipj;

  // Amount of deviation from the PRI means to search
  n_ipu = K;

  // See 2022-07-11 for updates to samples def
  n_ipu = t_0 + ((b_n_ws * ((n_ipu * (b_N + b_M) + n_ipj) + 1.0) + b_n_ol) -
                 b_n_ws * (2.0 * (n_ipu * b_M + n_ipj))) / Fs;
  t_nextsegstart[0] = n_ipu;
  t_nextsegstart[1] = n_ipu;

  // Don't need the overlap here since the next segment starts at samplesforKpulses+n_ol-n_ol from current sample
}

//
// SETWEIGHTINGMATRIX method sets the W and Wf properties of
// the waveform. These are the weighting matrix and the
// frequencys (Wf) at which they are computed.
// INPUTS:
//    none
// OUTPUTS:
//    none other than setting obj.Wf and obj.W
// ----------------------------------------------------------
//
// Here we build the spectral scaling vector. We make it the same
// size as the FFT length in the STFT operation, so it has the
// same frequency resolution.
// How many frequency bins are there?
//
// Arguments    : void
// Return Type  : void
//
void waveform::setweightingmatrix()
{
  static rtBoundsCheckInfo ab_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    159,                               // lineNo
    71,                                // colNo
    "Xs",                              // aName
    "weightingmatrix",                 // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/weightingmatrix.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo bb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    159,                               // lineNo
    38,                                // colNo
    "stackedToeplitzMatrices",         // aName
    "weightingmatrix",                 // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/weightingmatrix.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo cb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    181,                               // lineNo
    33,                                // colNo
    "freqs",                           // aName
    "weightingmatrix",                 // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/weightingmatrix.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo db_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    159,                               // lineNo
    29,                                // colNo
    "stackedToeplitzMatrices",         // aName
    "weightingmatrix",                 // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/weightingmatrix.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo eb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    191,                               // lineNo
    9,                                 // colNo
    "W",                               // aName
    "weightingmatrix",                 // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/weightingmatrix.m",// pName
    0                                  // checkKind
  };

  static rtDoubleCheckInfo s_emlrtDCI{ 53,// lineNo
    28,                                // colNo
    "gettemplate",                     // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/gettemplate.m",// pName
    4                                  // checkKind
  };

  static rtDoubleCheckInfo t_emlrtDCI{ 155,// lineNo
    41,                                // colNo
    "weightingmatrix",                 // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/weightingmatrix.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo u_emlrtDCI{ 155,// lineNo
    1,                                 // colNo
    "weightingmatrix",                 // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/weightingmatrix.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo v_emlrtDCI{ 183,// lineNo
    55,                                // colNo
    "weightingmatrix",                 // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/weightingmatrix.m",// pName
    4                                  // checkKind
  };

  static rtEqualityCheckInfo g_emlrtECI{ -1,// nDims
    180,                               // lineNo
    1,                                 // colNo
    "weightingmatrix",                 // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/weightingmatrix.m"// pName
  };

  static rtEqualityCheckInfo h_emlrtECI{ -1,// nDims
    159,                               // lineNo
    5,                                 // colNo
    "weightingmatrix",                 // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/weightingmatrix.m"// pName
  };

  static rtEqualityCheckInfo i_emlrtECI{ -1,// nDims
    145,                               // lineNo
    5,                                 // colNo
    "weightingmatrix",                 // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/weightingmatrix.m"// pName
  };

  static rtEqualityCheckInfo j_emlrtECI{ 1,// nDims
    146,                               // lineNo
    19,                                // colNo
    "weightingmatrix",                 // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/weightingmatrix.m"// pName
  };

  static rtEqualityCheckInfo k_emlrtECI{ -1,// nDims
    147,                               // lineNo
    5,                                 // colNo
    "weightingmatrix",                 // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/weightingmatrix.m"// pName
  };

  static rtEqualityCheckInfo l_emlrtECI{ 1,// nDims
    184,                               // lineNo
    6,                                 // colNo
    "weightingmatrix",                 // fName
    "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/weightingmatrix.m"// pName
  };

  coder::array<creal_T, 2U> Xs;
  coder::array<creal_T, 2U> _in;
  coder::array<creal_T, 2U> buffer;
  coder::array<creal_T, 2U> c_x;
  coder::array<creal_T, 2U> currDFT;
  coder::array<creal_T, 2U> s;
  coder::array<creal_T, 2U> stackedToeplitzMatrices;
  coder::array<creal_T, 1U> b_x;
  coder::array<creal_T, 1U> r;
  coder::array<double, 2U> output_samps;
  coder::array<double, 2U> sintabinv;
  coder::array<double, 2U> w_time_domain;
  coder::array<double, 2U> wrapper;
  coder::array<double, 2U> x_of_n;
  coder::array<int, 1U> iidx;
  coder::array<boolean_T, 2U> b_output_samps;
  double tmplt_samps[2];
  double b_Fs;
  double xtmp_im;
  double xtmp_re;
  int b_w_time_domain[2];
  int b_loop_ub_tmp;
  int i;
  int i1;
  int k;
  int loop_ub;
  int loop_ub_tmp;
  int md2;
  int nRows;
  int nw;
  int nx;
  unsigned int rowStart;
  boolean_T useRadix2;
  if (stft->f.size(0) == 0) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }

  nx = stft->f.size(0);

  // Build a pulse time domain template with the same number
  // of samples as frequency bins:
  // GETTEMPLATE Generates a time domain template of the the signal template
  //  (tmplt)in the priori pulsestats object in the waveform passed to the
  //  function. The returned vector is the template at the waveform's sample
  //  rate. The caller can request a total number of samples greater than the
  //  samples required to describe the signal. This is useful if the call will
  //  be using a DFT on the result and wants a specific number of samples to
  //  ensure a particular frequency resolution.
  //
  // INPUTS:
  //    X       A waveform object with a populated ps_pre property
  //    samples The number of sample desired in the output. Must be greater
  //            than or equal to ceil(X.ps_pre.t_p*X.Fs)
  //
  // OUTPUTS:
  //    sig_template    A vector of the signal amplitude over the samples
  //                    requested at the sample rate of the input waveform.
  //
  // Author: Michael W. Shafer
  // Date:   2021-05-21
  //
  // --------------------------------------------------------------------------
  // Sort out the samples input, if submitted by the caller
  xtmp_re = ps_pre->t_p * Fs;
  xtmp_re = std::ceil(xtmp_re);
  if (nx < xtmp_re) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }

  // Generates a the template in the time domain at the sample rate of the
  // waveform.
  tmplt_samps[1] = xtmp_re;
  tmplt_samps[0] = 0.0;
  coder::linspace(xtmp_re, xtmp_re, output_samps);
  coder::interp1(tmplt_samps, ps_pre->tmplt, output_samps, w_time_domain);

  // Generate the extra-zeros needed to pad to get to 'samples' samples
  loop_ub = nx - output_samps.size(1);
  if (loop_ub < 0) {
    rtNonNegativeError(static_cast<double>(loop_ub), s_emlrtDCI);
  }

  output_samps.set_size(1, loop_ub);
  for (i = 0; i < loop_ub; i++) {
    output_samps[i] = 0.0;
  }

  i = w_time_domain.size(1);
  loop_ub = output_samps.size(1);
  w_time_domain.set_size(w_time_domain.size(0), w_time_domain.size(1) +
    output_samps.size(1));
  for (i1 = 0; i1 < loop_ub; i1++) {
    w_time_domain[i + i1] = 0.0;
  }

  // Build a rectagular waveform in the time domain with the same number of samples as frequency bins
  // Build weighting matrix
  b_Fs = Fs;

  // WEIGHTINGMATRIX Builds the spectral weighting matrix for the incoherent
  // summationation algorithm. The matrix is based on the DFT coefficients
  // developed from the waveform passed to the function. The function first
  // developeds a weighting vectors based on an unaltered waveform, but then
  // shifts the waveforms spectral content base fractions of the DFT bin width,
  // as defined by the zetas input. These shifted waveforms then have their
  // DFT's computed. The original and shifted DFT coefficients are then aligned
  // in a matrix. In this way, this weighting matrix allows for the dominant
  // frequency in the vector it weights to be between bins. This submatrix is
  // then row shifted and concantinated a number of times so that the DFT
  // coefficients are shifted across all DFT frequency bins. The outputs are
  // the weighting matrix W and a frequency vector Wf that corresponds to the
  // rows of W. The frequencies, and therefore the rows of the W matrix, use a
  // centered frequency definitions defined by the STFT.m algorithm.
  //
  //    Example:   [W,Wf] = weightingmatrix(rand(1,10),1,[0 0.5])
  //
  //    INPUTS:
  //    x_of_n      nx1     Vector of discrete data sampled as Fs. Can be 1xn.
  //    Fs          1x1     Sampling rate in Hz of the dataset
  //    zetas       mx1     A vector of fractions of the DFT frequency bin
  //                        width for which to compute and include in the
  //                        spectral weighting matrix output. If no interbin
  //                        shifting is desired, enter 0. Range of inputs
  //                        [0,1).
  //    frequencyRangeType  String of either 'centered' or 'twosided'. See
  //                        stft.m documentation on details of these frequency
  //                        bounds. If 'centered' is selected, the zero
  //                        frequency point is near the center of the output
  //                        matrix. If 'twosided' is selected, the zero
  //                        frequency points is in the upper left corner of the
  //                        output W matrix.
  //
  //    OUTPUTS:
  //    W           nxnm    A matrix of spectral weighting vectors along each
  //                        column. The hermitian of this matrix is designed to
  //                        be multiplied by a vector of DFT coefficients. The
  //                        weights held in column p can be thought of as the
  //                        matched DFT coefficients if the signal were to have
  //                        been shifted by the template by Wf(p).
  //    Wf          nmx1    A matrix of the frequency shifts corresponding to
  //                        each column of W
  //
  //  The intended use of the W matrix is to multiply it's hermetian by a FFT
  //  vector, or STFT matrix with frequencies in the rows.
  //
  //
  //    [W^h]*S         or          [W^h]*FFT
  //
  //  The outputs of this multiplication will have n*m rows. The rows of the
  //  result there for are the "scores" of at frequency associated with that
  //  row. The row frequencies are dependent on the zetas. Consider an input
  //  series that had frequencies [-100 0 100 200]. If the zeta input was
  //  [0 0.5], weightings for full and half frequencies steps would be
  //  developed.
  //
  //        output freq     input freq
  //                            -100    0   100     200
  //                -150    [                           ]
  //                -100    [                           ]
  //                -50     [                           ]
  //                0       [            W^h            ]
  //                50      [                           ]
  //                100     [                           ]
  //                150     [                           ]
  //                200     [                           ]
  //
  //    The first row of the matrix above would contain the weightings for the
  //    -100 0 100 and 200 Hz frequencie bins if the FFT (or STFT time window)
  //    had a signal at -150 Hz. Similarly, the second row would contain the
  //    weightings for the -100 0 100 and 200 Hz frequencie bins if the FFT
  //    (or STFT time window) had a signal at -100 Hz.
  //
  // Author: Michael Shafer
  // Date:   2020-12-19
  //
  //  Change Log
  //  2022-01-12    Updated to include twosided frequency range for output and
  //                updated the code associated with generating the unsorted W
  //                matrix to increase speed. Added use of makestftFreqVector
  //                function.
  //
  // Check the inputs
  // Reshape to a column vector, as the algorithm expects
  if (w_time_domain.size(1) != 1) {
    x_of_n.set_size(w_time_domain.size(1), 1);
    loop_ub = w_time_domain.size(1);
    for (i = 0; i < loop_ub; i++) {
      x_of_n[i] = w_time_domain[i];
    }
  } else {
    x_of_n.set_size(1, 1);
    x_of_n[0] = w_time_domain[0];
  }

  nw = x_of_n.size(0);

  // F_bin_width = Fs/nw;
  if (x_of_n.size(0) - 1 < 0) {
    output_samps.set_size(1, 0);
  } else {
    output_samps.set_size(1, x_of_n.size(0));
    loop_ub = x_of_n.size(0) - 1;
    for (i = 0; i <= loop_ub; i++) {
      output_samps[i] = i;
    }
  }

  // Use complex so when implementing in simulink later, it knows this is a
  // complex vector.
  s.set_size(x_of_n.size(0), 2);
  loop_ub_tmp = x_of_n.size(0) << 1;
  for (i = 0; i < loop_ub_tmp; i++) {
    s[i].re = 0.0;
    s[i].im = 0.0;
  }

  Xs.set_size(x_of_n.size(0), 2);
  for (i = 0; i < loop_ub_tmp; i++) {
    Xs[i].re = 0.0;
    Xs[i].im = 0.0;
  }

  // Develop a vector of frequencies that would result from the centered method
  // of the STFT function if it were computed on the x input. This is useful
  // for debugging the frequency outputs.
  // These are designed to develop the same freqs as the STFT centered method
  // Check the "'FrequencyRange' — STFT frequency range" in the STFT help file
  // if mod(nw,2)==0
  //     freqs_orig = ((-nw/2+1):nw/2)*Fs/nw;
  // else
  //     freqs_orig = (ceil(-nw/2):floor(nw/2))*Fs/nw;
  // end
  // figure;
  loop_ub = output_samps.size(1);
  for (int b_i{0}; b_i < 2; b_i++) {
    double ai;
    double y;
    xtmp_im = 0.5 * static_cast<double>(b_i) * 6.2831853071795862;
    b_x.set_size(output_samps.size(1));
    for (i = 0; i < loop_ub; i++) {
      ai = xtmp_im * output_samps[i];
      if (ai == 0.0) {
        b_x[i].re = 0.0 / static_cast<double>(nw);
        b_x[i].im = 0.0;
      } else {
        b_x[i].re = 0.0;
        b_x[i].im = ai / static_cast<double>(nw);
      }
    }

    nx = b_x.size(0);
    if (b_x.size(0) > 2147483646) {
      coder::check_forloop_overflow_error();
    }

    for (k = 0; k < nx; k++) {
      if (b_x[k].re == 0.0) {
        xtmp_im = b_x[k].im;
        b_x[k].re = std::cos(xtmp_im);
        b_x[k].im = std::sin(xtmp_im);
      } else if (b_x[k].im == 0.0) {
        b_x[k].re = std::exp(b_x[k].re);
        b_x[k].im = 0.0;
      } else if (std::isinf(b_x[k].im) && std::isinf(b_x[k].re) && (b_x[k].re <
                  0.0)) {
        b_x[k].re = 0.0;
        b_x[k].im = 0.0;
      } else {
        xtmp_re = std::exp(b_x[k].re / 2.0);
        xtmp_im = b_x[k].im;
        b_x[k].re = xtmp_re * (xtmp_re * std::cos(xtmp_im));
        b_x[k].im = xtmp_re * (xtmp_re * std::sin(xtmp_im));
      }
    }

    rtSubAssignSizeCheck(s.size(), 1, b_x.size(), 1, i_emlrtECI);
    nx = b_x.size(0);
    for (i = 0; i < nx; i++) {
      s[i + s.size(0) * b_i] = b_x[i];
    }

    if ((s.size(0) != x_of_n.size(0)) && ((s.size(0) != 1) && (x_of_n.size(0) !=
          1))) {
      emlrtDimSizeImpxCheckR2021b(s.size(0), x_of_n.size(0), j_emlrtECI);
    }

    if (s.size(0) == x_of_n.size(0)) {
      c_x.set_size(s.size(0), 1);
      nx = s.size(0);
      for (i = 0; i < nx; i++) {
        c_x[i].re = x_of_n[i] * s[i + s.size(0) * b_i].re;
        c_x[i].im = x_of_n[i] * s[i + s.size(0) * b_i].im;
      }
    } else {
      binary_expand_op(c_x, s, b_i, x_of_n);
    }

    if (c_x.size(0) == 1) {
      w_rtErrorWithMessageID(hb_emlrtRTEI.fName, hb_emlrtRTEI.lineNo);
    }

    if (c_x.size(0) == 0) {
      currDFT.set_size(0, 1);
    } else {
      useRadix2 = ((c_x.size(0) & (c_x.size(0) - 1)) == 0);
      nx = coder::internal::fft::FFTImplementationCallback::get_algo_sizes
        (c_x.size(0), useRadix2, nRows);
      coder::internal::fft::FFTImplementationCallback::generate_twiddle_tables
        (nRows, useRadix2, w_time_domain, wrapper, sintabinv);
      if (useRadix2) {
        coder::internal::fft::FFTImplementationCallback::r2br_r2dit_trig(c_x,
          c_x.size(0), w_time_domain, wrapper, currDFT);
      } else {
        coder::internal::fft::FFTImplementationCallback::dobluesteinfft(c_x, nx,
          c_x.size(0), w_time_domain, wrapper, sintabinv, currDFT);
      }
    }

    y = coder::b_norm(currDFT);
    currDFT.set_size(currDFT.size(0), 1);
    nx = currDFT.size(0) - 1;
    for (i = 0; i <= nx; i++) {
      xtmp_re = currDFT[i].re;
      ai = currDFT[i].im;
      if (ai == 0.0) {
        xtmp_im = xtmp_re / y;
        xtmp_re = 0.0;
      } else if (xtmp_re == 0.0) {
        xtmp_im = 0.0;
        xtmp_re = ai / y;
      } else {
        xtmp_im = xtmp_re / y;
        xtmp_re = ai / y;
      }

      currDFT[i].re = xtmp_im;
      currDFT[i].im = xtmp_re;
    }

    // FFTSHIFTSTFT Performs a standard fftshift operation but accounts for the
    // different frequency range definition in Matlabs STFT function when
    // outputing a 'centered' frequency range
    //    When calling the STFT function, the default output for frequency is
    //    the 'centered' method where frequencies are reported on the range of
    //    (-n/2+1:n/2)*Fs/n if the vector is of even length and
    //    (ceil(-n/2):floor(n/2))*Fs/n if the vector is of odd length. It seems
    //    that Matlab's fftshift function is develped for frequencies in the
    //    range of (-n/2:n/2+1)*Fs/n if the vector is of even length. The odd
    //    length definition is unaffected. The result is an incorrect shifting of
    //    the frequency vector if fftshift is used on f defined by stft's
    //    centered method. This function uses the fftshift command for vectors
    //    of even length, but shifts the result by 1 to the left to correct for
    //    this problem.
    //
    //    If x is a matrix, it is assumed that the matrix is formatted similar to
    //    the output of a STFT call, wherein the rows represent the different
    //    frequencies and the rows are the time windows. As such, in this case
    //    the rows are operated on (shifted).
    //
    // INPUTS:
    //    x       nxm     A matrix of real or complex data. If passed a matrix,
    //                    the rows should represent frequency bins
    // OUTPUT:
    //    xout    nxm     A matrix of real or complex shifted data
    //
    //  Author: Michael Shafer
    //  Date:   2020-12-19
    //
    //  Change log:
    //  2022-01-10    Updated to deal with row or column vectors or stft matrices
    //
    // --------------------------------------------------------------------------
    // Passed a matrix or a column vector
    if (currDFT.size(0) == 0) {
      i = 0;
    } else {
      i = static_cast<int>(std::fmod(static_cast<double>(currDFT.size(0)), 2.0));
    }

    if (i != 0.0) {
      coder::fftshift(currDFT);
    } else {
      coder::fftshift(currDFT);
      if ((currDFT.size(0) != 0) && (currDFT.size(0) != 1)) {
        nx = currDFT.size(0) / 2;
        buffer.set_size(1, nx);
        for (i = 0; i < nx; i++) {
          buffer[i].re = 0.0;
          buffer[i].im = 0.0;
        }

        i = currDFT.size(0) - 2;
        buffer[0] = currDFT[0];
        for (k = 0; k <= i; k++) {
          currDFT[k] = currDFT[k + 1];
        }

        currDFT[currDFT.size(0) - 1] = buffer[0];
      }
    }

    rtSubAssignSizeCheck(Xs.size(), 1, currDFT.size(), 2, k_emlrtECI);
    nx = Xs.size(0);
    for (i = 0; i < nx; i++) {
      Xs[i + Xs.size(0) * b_i] = currDFT[i];
    }

    //    stem(freqs_orig,abs(Xs(:,i)),'DisplayName',['\zeta =',num2str(zetas(i))]);
    //    hold on
  }

  // ylabel('|Xs|');xlabel('Frequency');legend('Location',"best");
  // title('DFT of primary frequency shifts of the template')
  // New W generation method. ~25% faster on average
  xtmp_im = 2.0 * static_cast<double>(x_of_n.size(0));
  if (xtmp_im != static_cast<int>(xtmp_im)) {
    rtIntegerError(xtmp_im, t_emlrtDCI);
  }

  stackedToeplitzMatrices.set_size(static_cast<int>(xtmp_im), x_of_n.size(0));
  if (xtmp_im != static_cast<int>(xtmp_im)) {
    rtIntegerError(xtmp_im, u_emlrtDCI);
  }

  loop_ub_tmp = static_cast<int>(xtmp_im) * x_of_n.size(0);
  for (i = 0; i < loop_ub_tmp; i++) {
    stackedToeplitzMatrices[i].re = 0.0;
    stackedToeplitzMatrices[i].im = 0.0;
  }

  if (Xs.size(0) < 2) {
    i = 0;
    i1 = 0;
  } else {
    i = 1;
    i1 = Xs.size(0);
  }

  b_loop_ub_tmp = i1 - i;
  md2 = b_loop_ub_tmp >> 1;
  i1 = Xs.size(0) - 1;
  for (int b_i{0}; b_i < 2; b_i++) {
    int i2;
    int i3;
    int i4;
    unsigned int rowEnd;
    rowStart = static_cast<unsigned int>(b_i * nw) + 1U;
    rowEnd = (rowStart + static_cast<unsigned int>(nw)) - 1U;
    if (rowStart > rowEnd) {
      i2 = 0;
      i3 = 0;
    } else {
      if ((static_cast<int>(rowStart) < 1) || (static_cast<int>(rowStart) >
           stackedToeplitzMatrices.size(0))) {
        rtDynamicBoundsError(static_cast<int>(rowStart), 1,
                             stackedToeplitzMatrices.size(0), db_emlrtBCI);
      }

      i2 = static_cast<int>(rowStart) - 1;
      if ((static_cast<int>(rowEnd) < 1) || (static_cast<int>(rowEnd) >
           stackedToeplitzMatrices.size(0))) {
        rtDynamicBoundsError(static_cast<int>(rowEnd), 1,
                             stackedToeplitzMatrices.size(0), bb_emlrtBCI);
      }

      i3 = static_cast<int>(rowEnd);
    }

    if (Xs.size(0) < 1) {
      rtDynamicBoundsError(1, 1, Xs.size(0), ab_emlrtBCI);
    }

    b_x.set_size(b_loop_ub_tmp);
    for (i4 = 0; i4 < b_loop_ub_tmp; i4++) {
      b_x[i4] = Xs[(i + i4) + Xs.size(0) * b_i];
    }

    for (loop_ub = 0; loop_ub < md2; loop_ub++) {
      xtmp_re = b_x[loop_ub].re;
      xtmp_im = b_x[loop_ub].im;
      nx = (b_loop_ub_tmp - loop_ub) - 1;
      b_x[loop_ub] = b_x[nx];
      b_x[nx].re = xtmp_re;
      b_x[nx].im = xtmp_im;
    }

    r.set_size(b_x.size(0) + 1);
    r[0] = Xs[Xs.size(0) * b_i];
    loop_ub = b_x.size(0);
    for (i4 = 0; i4 < loop_ub; i4++) {
      r[i4 + 1] = b_x[i4];
    }

    _in.set_size(Xs.size(0), r.size(0));
    nx = 0;
    i4 = r.size(0) - 1;
    for (nRows = 0; nRows <= i4; nRows++) {
      k = nRows;
      for (loop_ub = 0; loop_ub <= i1; loop_ub++) {
        if (loop_ub < nRows) {
          _in[nx + loop_ub] = r[k];
          k--;
        } else {
          _in[nx + loop_ub] = Xs[k + Xs.size(0) * b_i];
          k++;
        }
      }

      if (i1 >= 0) {
        nx = (nx + i1) + 1;
      }
    }

    b_w_time_domain[0] = i3 - i2;
    b_w_time_domain[1] = stackedToeplitzMatrices.size(1);
    rtSubAssignSizeCheck(&b_w_time_domain[0], 2, _in.size(), 2, h_emlrtECI);
    loop_ub = _in.size(1);
    for (i3 = 0; i3 < loop_ub; i3++) {
      nx = _in.size(0);
      for (i4 = 0; i4 < nx; i4++) {
        stackedToeplitzMatrices[(i2 + i4) + stackedToeplitzMatrices.size(0) * i3]
          = _in[i4 + _in.size(0) * i3];
      }
    }
  }

  // Reshape in this way will interweave rows of each sub matrix of the stack
  rowStart = static_cast<unsigned int>(x_of_n.size(0)) << 1;
  coder::internal::assertValidSizeArg(static_cast<double>(x_of_n.size(0)));
  coder::internal::assertValidSizeArg(static_cast<double>(rowStart));
  nx = stackedToeplitzMatrices.size(0);
  if (stackedToeplitzMatrices.size(1) > stackedToeplitzMatrices.size(0)) {
    nx = stackedToeplitzMatrices.size(1);
  }

  if (loop_ub_tmp >= nx) {
    nx = loop_ub_tmp;
  }

  if (x_of_n.size(0) > nx) {
    k_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }

  if (static_cast<int>(rowStart) > nx) {
    k_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }

  if (static_cast<int>(rowStart) < 0) {
    jb_rtErrorWithMessageID(yb_emlrtRTEI.fName, yb_emlrtRTEI.lineNo);
  }

  if (x_of_n.size(0) * static_cast<int>(rowStart) != loop_ub_tmp) {
    l_rtErrorWithMessageID(o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
  }

  // OLD W generation method. Easier to understand, but slower
  //  W     = 1i*zeros(nw,numZetas*nw);
  //  freqs = zeros(1,numZetas*nw);
  //  for i = 1:nw
  //      W(:,(i-1)*numZetas+(1:numZetas))=...
  //          circshift(Xs,i-1,1);
  //  end
  // Build a vector of the frequencies
  // MAKESTFTFREQVECTOR Generates the frequency vector based on the frequency
  // range specification for Matlab's stft.m 'FrequencyRange' input standard,
  //
  //    This function outputs a frequency vector based on the frequency
  //    range specification for Matlab's stft.m 'FrequencyRange' input
  //    standard. The options for the frequency ranges are 'centered'
  //    (default), 'twosided', and 'onesided'. The sftf.m documentation
  //    standard states:
  //        STFT frequency range, specified as 'centered', 'twosided', or
  //        'onesided'.
  //
  //        'centered' — Compute a two-sided, centered STFT. If 'FFTLength' is
  //        even, then s is computed over the interval (–π, π] rad/sample. If
  //        'FFTLength' is odd, then s is computed over the interval (–π, π)
  //        rad/sample. If you specify time information, then the intervals are
  //         (–fs, fs/2] cycles/unit time and (–fs, fs/2) cycles/unit time,
  //        respectively, where fs is the effective sample rate.
  //
  //        'twosided' — Compute a two-sided STFT over the interval [0, 2π)
  //        rad/sample. If you specify time information, then the interval is
  //        [0, fs) cycles/unit time.
  //
  //        'onesided' — Compute a one-sided STFT. If 'FFTLength' is even,
  //        then s is computed over the interval [0, π] rad/sample. If
  //        'FFTLength' is odd, then s is computed over the interval [0, π)
  //        rad/sample. If you specify time information, then the intervals are
  //         [0, fs/2] cycles/unit time and [0, fs/2) cycles/unit time,
  //        respectively, where fs is the effective sample rate. This option is
  //         valid only for real signals.
  //
  //    If Fs is not specificed, outputs will be in rad/sample with pi as
  //    specified in the stft.m frequency range standard.
  //
  // INPUTS:
  //    nfft                 Length of FFT performed on the STFT.
  //    frequencyRangeType   String containing 'centered', 'twosided', 'onesided'
  //    Fs                   Sample rate of data
  //
  // OUTPUTS:
  //    freqs       Vector of frequencies at which the STFT is calculated
  //
  // Author:    Michael Shafer
  // Date:      2022-01-11
  //
  if (static_cast<double>(rowStart) - 1.0 < 0.0) {
    output_samps.set_size(output_samps.size(0), 0);
  } else {
    output_samps.set_size(1, static_cast<int>(static_cast<double>(rowStart) -
      1.0) + 1);
    loop_ub = static_cast<int>(static_cast<double>(rowStart) - 1.0);
    for (i = 0; i <= loop_ub; i++) {
      output_samps[i] = i;
    }
  }

  output_samps.set_size(1, output_samps.size(1));
  loop_ub = output_samps.size(1) - 1;
  for (i = 0; i <= loop_ub; i++) {
    output_samps[i] = output_samps[i] * b_Fs / static_cast<double>(rowStart);
  }

  // Shift everything so we use a negative frequencies
  // A little non-matlab notation to get this to run in simulink.
  xtmp_re = b_Fs / 2.0;
  b_output_samps.set_size(1, output_samps.size(1));
  loop_ub = output_samps.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_output_samps[i] = (output_samps[i] == xtmp_re);
  }

  coder::eml_find(b_output_samps, (int *)&nx, b_w_time_domain);
  if (b_w_time_domain[1] != 1) {
    rtSizeEq1DError(1, 0, g_emlrtECI);
  }

  useRadix2 = (output_samps.size(1) < 1);
  if (useRadix2) {
    rtDynamicBoundsError(output_samps.size(1), 1, output_samps.size(1),
                         cb_emlrtBCI);
  }

  xtmp_re = output_samps[output_samps.size(1) - 1];
  xtmp_re = -xtmp_re - (b_Fs - xtmp_re);
  w_time_domain.set_size(1, w_time_domain.size(1));
  xtmp_im = static_cast<double>(output_samps.size(1)) - static_cast<double>(nx);
  if (!(xtmp_im >= 0.0)) {
    rtNonNegativeError(xtmp_im, v_emlrtDCI);
  }

  loop_ub_tmp = static_cast<int>(xtmp_im);
  w_time_domain.set_size(w_time_domain.size(0), loop_ub_tmp);
  for (i = 0; i < loop_ub_tmp; i++) {
    w_time_domain[i] = 1.0;
  }

  wrapper.set_size(1, nx + w_time_domain.size(1));
  for (i = 0; i < nx; i++) {
    wrapper[i] = 0.0;
  }

  loop_ub = w_time_domain.size(1);
  for (i = 0; i < loop_ub; i++) {
    wrapper[i + nx] = xtmp_re;
  }

  if ((wrapper.size(1) != output_samps.size(1)) && ((wrapper.size(1) != 1) &&
       (output_samps.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(wrapper.size(1), output_samps.size(1),
      l_emlrtECI);
  }

  // Here we sort the output to set up to have an ascending order of frequency
  // to be similar to the centered frequency list used elsewhere in the
  // codebase for the STFT output.
  if (wrapper.size(1) == output_samps.size(1)) {
    Wf.set_size(wrapper.size(1));
    loop_ub = wrapper.size(1);
    for (i = 0; i < loop_ub; i++) {
      Wf[i] = wrapper[i] + output_samps[i];
    }
  } else {
    binary_expand_op_1(this, wrapper, output_samps);
  }

  coder::internal::sort(Wf, iidx);
  b_w_time_domain[0] = x_of_n.size(0);
  W.set_size(x_of_n.size(0), iidx.size(0));
  loop_ub = iidx.size(0);
  for (i = 0; i < loop_ub; i++) {
    nx = x_of_n.size(0);
    for (i1 = 0; i1 < nx; i1++) {
      useRadix2 = ((iidx[i] < 1) || (iidx[i] > static_cast<int>(rowStart)));
      if (useRadix2) {
        rtDynamicBoundsError(iidx[i], 1, static_cast<int>(rowStart), eb_emlrtBCI);
      }

      W[i1 + W.size(0) * i].re = stackedToeplitzMatrices[i1 + b_w_time_domain[0]
        * (iidx[i] - 1)].re;
      W[i1 + W.size(0) * i].im = stackedToeplitzMatrices[i1 + b_w_time_domain[0]
        * (iidx[i] - 1)].im;
    }
  }
}

//
// SPECTRO Executes an STFT of x and sets up the wfmstst object
// for the waveform
//
// INPUTS:
//    obj     The waveform object
// OUTPUTS:
//    none
//
//
//
// Arguments    : wfmstft &iobj_0
// Return Type  : void
//
void b_waveform::spectro(wfmstft &iobj_0)
{
  coder::array<creal32_T, 2U> S;
  coder::array<creal32_T, 2U> obj;
  coder::array<double, 1U> _in;
  coder::array<float, 1U> local_time;
  coder::array<float, 1U> r;
  double n_est;
  int n;

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
  // Instructions on https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  // maxFs*maxpulsewidth
  // Now actually assign them
  iobj_0.S.set_size(0, 0);
  iobj_0.t.set_size(0);
  iobj_0.f.set_size(0);
  iobj_0.psd.set_size(0);
  iobj_0.wind.set_size(0);
  iobj_0.dt = 0.0;
  iobj_0.T = 0.0;

  // wind = hann(waveform_obj.n_w,'periodic');
  // wind = tukeywin(waveform_obj.n_w,0.3);
  n_est = n_w;
  if (std::isinf(n_est) || std::isnan(n_est)) {
    g_rtErrorWithMessageID("N", w_emlrtRTEI.fName, w_emlrtRTEI.lineNo);
  }

  if (!(n_est >= 0.0)) {
    s_rtErrorWithMessageID(x_emlrtRTEI.fName, x_emlrtRTEI.lineNo);
  }

  if (n_est == std::floor(n_est)) {
    n = static_cast<int>(n_est);
  } else {
    n = static_cast<int>(std::round(n_est));
  }

  _in.set_size(n);
  for (int i{0}; i < n; i++) {
    _in[i] = 1.0;
  }

  iobj_0.wind.set_size(_in.size(0));
  n = _in.size(0);
  for (int i{0}; i < n; i++) {
    iobj_0.wind[i] = _in[i];
  }

  obj.set_size(1, x.size(1));
  n = x.size(0) * x.size(1) - 1;
  for (int i{0}; i <= n; i++) {
    obj[i] = x[i];
  }

  _in.set_size(iobj_0.wind.size(0));
  n = iobj_0.wind.size(0) - 1;
  for (int i{0}; i <= n; i++) {
    _in[i] = iobj_0.wind[i];
  }

  ::coder::stft(obj, Fs, _in, n_ol, n_w, S, r, local_time);
  iobj_0.f.set_size(r.size(0));
  n = r.size(0);
  for (int i{0}; i < n; i++) {
    iobj_0.f[i] = r[i];
  }

  iobj_0.S.set_size(S.size(0), S.size(1));
  n = S.size(0) * S.size(1);
  for (int i{0}; i < n; i++) {
    iobj_0.S[i].re = S[i].re;
    iobj_0.S[i].im = S[i].im;
  }

  //  Incoming x data in waveform is single precision, but sparse matrix multipliation later is only supported for double precision.
  _in.set_size(local_time.size(0));
  n = local_time.size(0);
  for (int i{0}; i < n; i++) {
    _in[i] = local_time[i] + t_0;
  }

  iobj_0.t.set_size(_in.size(0));
  n = _in.size(0);
  for (int i{0}; i < n; i++) {
    iobj_0.t[i] = _in[i];
  }

  // Convert to global time of waveform. Double cast is needed because if x data in stft is single precision then the output t will be single as well.
  n_est = 1.0 / Fs;
  iobj_0.dt = n_est;
  n_est = n_w / Fs;
  iobj_0.T = n_est;
  iobj_0.updatepsd();

  // obj.psd = obj.dt^2/obj.T*mean(abs(obj.S).^2,2);% Sxx = dt^2/T*|xhat(f)|^2
  // Vestigial properties no longer used. Kept in case we want
  // to resurect them.
  // obj.wind_per_pulse = floor(waveform_obj.n_w/waveform_obj.n_p); %How many windows are needed to capture a pulse
  // obj.stft_steps_per_pulse = floor(waveform_obj.t_ws/waveform_obj.ps_pre.t_p);%How many stft steps are needed to capture a pulse
  stft = &iobj_0;
}

//
// SPECTRO Executes an STFT of x and sets up the wfmstst object
// for the waveform
//
// INPUTS:
//    obj     The waveform object
// OUTPUTS:
//    none
//
//
//
// Arguments    : wfmstft &iobj_0
// Return Type  : void
//
void waveform::spectro(wfmstft &iobj_0)
{
  coder::array<creal32_T, 2U> S;
  coder::array<creal32_T, 2U> obj;
  coder::array<double, 1U> _in;
  coder::array<float, 1U> local_time;
  coder::array<float, 1U> r;
  double n_est;
  int n;

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
  // Instructions on https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  // maxFs*maxpulsewidth
  // Now actually assign them
  iobj_0.S.set_size(0, 0);
  iobj_0.t.set_size(0);
  iobj_0.f.set_size(0);
  iobj_0.psd.set_size(0);
  iobj_0.wind.set_size(0);
  iobj_0.dt = 0.0;
  iobj_0.T = 0.0;

  // wind = hann(waveform_obj.n_w,'periodic');
  // wind = tukeywin(waveform_obj.n_w,0.3);
  n_est = n_w;
  if (std::isinf(n_est) || std::isnan(n_est)) {
    g_rtErrorWithMessageID("N", w_emlrtRTEI.fName, w_emlrtRTEI.lineNo);
  }

  if (!(n_est >= 0.0)) {
    s_rtErrorWithMessageID(x_emlrtRTEI.fName, x_emlrtRTEI.lineNo);
  }

  if (n_est == std::floor(n_est)) {
    n = static_cast<int>(n_est);
  } else {
    n = static_cast<int>(std::round(n_est));
  }

  _in.set_size(n);
  for (int i{0}; i < n; i++) {
    _in[i] = 1.0;
  }

  iobj_0.wind.set_size(_in.size(0));
  n = _in.size(0);
  for (int i{0}; i < n; i++) {
    iobj_0.wind[i] = _in[i];
  }

  obj.set_size(1, x.size(1));
  n = x.size(0) * x.size(1) - 1;
  for (int i{0}; i <= n; i++) {
    obj[i] = x[i];
  }

  _in.set_size(iobj_0.wind.size(0));
  n = iobj_0.wind.size(0) - 1;
  for (int i{0}; i <= n; i++) {
    _in[i] = iobj_0.wind[i];
  }

  ::coder::stft(obj, Fs, _in, n_ol, n_w, S, r, local_time);
  iobj_0.f.set_size(r.size(0));
  n = r.size(0);
  for (int i{0}; i < n; i++) {
    iobj_0.f[i] = r[i];
  }

  iobj_0.S.set_size(S.size(0), S.size(1));
  n = S.size(0) * S.size(1);
  for (int i{0}; i < n; i++) {
    iobj_0.S[i].re = S[i].re;
    iobj_0.S[i].im = S[i].im;
  }

  //  Incoming x data in waveform is single precision, but sparse matrix multipliation later is only supported for double precision.
  _in.set_size(local_time.size(0));
  n = local_time.size(0);
  for (int i{0}; i < n; i++) {
    _in[i] = local_time[i] + t_0;
  }

  iobj_0.t.set_size(_in.size(0));
  n = _in.size(0);
  for (int i{0}; i < n; i++) {
    iobj_0.t[i] = _in[i];
  }

  // Convert to global time of waveform. Double cast is needed because if x data in stft is single precision then the output t will be single as well.
  n_est = 1.0 / Fs;
  iobj_0.dt = n_est;
  n_est = n_w / Fs;
  iobj_0.T = n_est;
  iobj_0.updatepsd();

  // obj.psd = obj.dt^2/obj.T*mean(abs(obj.S).^2,2);% Sxx = dt^2/T*|xhat(f)|^2
  // Vestigial properties no longer used. Kept in case we want
  // to resurect them.
  // obj.wind_per_pulse = floor(waveform_obj.n_w/waveform_obj.n_p); %How many windows are needed to capture a pulse
  // obj.stft_steps_per_pulse = floor(waveform_obj.t_ws/waveform_obj.ps_pre.t_p);%How many stft steps are needed to capture a pulse
  stft = &iobj_0;
}

//
// File trailer for waveform.cpp
//
// [EOF]
//
