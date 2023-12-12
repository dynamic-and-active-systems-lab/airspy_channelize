//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: buildtimecorrelatormatrix.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "buildtimecorrelatormatrix.h"
#include "assembleWq.h"
#include "assertValidSizeArg.h"
#include "colon.h"
#include "eml_int_forloop_overflow_check.h"
#include "minOrMax.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "sparse.h"
#include "sparse1.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "unique.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
static void mb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void mb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Domain error. To compute complex results, make at least one "
               "input complex, e.g. \'power(complex(a),b)\'.";
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
// BUILDTIMECORRELATIONMATRIX Assembles the time correlation matrix that is
// used in the incoherent summation step.
// INPUTS:
//    pri         Pulse repetition interval in stft time windows (N)
//    priUncert   Pulse repetition interval uncertainty in stft time windows
//                (M)
//    priJtr      Pulse repetition interval jitter in stft time windows (J)
//    reps        Pulse repetitions to consider (K)
//
// Arguments    : double pri
//                double priUncert
//                double priJtr
//                double reps
//                coder::sparse &Wq
// Return Type  : void
//
void buildtimecorrelatormatrix(double pri, double priUncert, double priJtr,
                               double reps, coder::sparse &Wq)
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      -1,                              // iFirst
      -1,                              // iLast
      48,                              // lineNo
      42,                              // colNo
      "PRI_mean_value",                // aName
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      0         // checkKind
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      -1,                              // iFirst
      -1,                              // iLast
      48,                              // lineNo
      69,                              // colNo
      "PRI_jitter_value",              // aName
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      0         // checkKind
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      -1,                              // iFirst
      -1,                              // iLast
      47,                              // lineNo
      35,                              // colNo
      "pulse_position_value",          // aName
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      0         // checkKind
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      -1,                              // iFirst
      -1,                              // iLast
      47,                              // lineNo
      38,                              // colNo
      "pulse_position_value",          // aName
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      0         // checkKind
  };
  static rtBoundsCheckInfo eb_emlrtBCI{
      -1,                              // iFirst
      -1,                              // iLast
      47,                              // lineNo
      48,                              // colNo
      "pulse_position_value",          // aName
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      0         // checkKind
  };
  static rtBoundsCheckInfo fb_emlrtBCI{
      -1,                              // iFirst
      -1,                              // iLast
      79,                              // lineNo
      75,                              // colNo
      "pulse_position_value",          // aName
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      0         // checkKind
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      -1,                    // iFirst
      -1,                    // iLast
      46,                    // lineNo
      32,                    // colNo
      "C",                   // aName
      "cartesian_prod_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/cartesian_prod_func.m", // pName
      0                                                        // checkKind
  };
  static rtBoundsCheckInfo hb_emlrtBCI{
      -1,                    // iFirst
      -1,                    // iLast
      46,                    // lineNo
      9,                     // colNo
      "A",                   // aName
      "cartesian_prod_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/cartesian_prod_func.m", // pName
      0                                                        // checkKind
  };
  static rtBoundsCheckInfo ib_emlrtBCI{
      -1,                    // iFirst
      -1,                    // iLast
      46,                    // lineNo
      12,                    // colNo
      "C",                   // aName
      "cartesian_prod_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/cartesian_prod_func.m", // pName
      0                                                        // checkKind
  };
  static rtBoundsCheckInfo jb_emlrtBCI{
      -1,                    // iFirst
      -1,                    // iLast
      46,                    // lineNo
      17,                    // colNo
      "C",                   // aName
      "cartesian_prod_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/cartesian_prod_func.m", // pName
      0                                                        // checkKind
  };
  static rtBoundsCheckInfo kb_emlrtBCI{
      -1,                              // iFirst
      -1,                              // iLast
      80,                              // lineNo
      30,                              // colNo
      "pulse_position_matrix",         // aName
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      0         // checkKind
  };
  static rtBoundsCheckInfo lb_emlrtBCI{
      -1,                              // iFirst
      -1,                              // iLast
      80,                              // lineNo
      55,                              // colNo
      "pulse_position_matrix",         // aName
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      0         // checkKind
  };
  static rtDoubleCheckInfo ab_emlrtDCI{
      39,                              // lineNo
      1,                               // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      1         // checkKind
  };
  static rtDoubleCheckInfo bb_emlrtDCI{
      66,                              // lineNo
      32,                              // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      4         // checkKind
  };
  static rtDoubleCheckInfo cb_emlrtDCI{
      66,                              // lineNo
      32,                              // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      1         // checkKind
  };
  static rtDoubleCheckInfo db_emlrtDCI{
      20,           // lineNo
      1,            // colNo
      "assembleWq", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/assembleWq.m", // pName
      1                                               // checkKind
  };
  static rtDoubleCheckInfo eb_emlrtDCI{
      18,                    // lineNo
      12,                    // colNo
      "cartesian_prod_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/cartesian_prod_func.m", // pName
      1                                                        // checkKind
  };
  static rtDoubleCheckInfo fb_emlrtDCI{
      79,                              // lineNo
      5,                               // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      1         // checkKind
  };
  static rtDoubleCheckInfo gb_emlrtDCI{
      46,                    // lineNo
      12,                    // colNo
      "cartesian_prod_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/cartesian_prod_func.m", // pName
      1                                                        // checkKind
  };
  static rtDoubleCheckInfo hb_emlrtDCI{
      46,                    // lineNo
      17,                    // colNo
      "cartesian_prod_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/cartesian_prod_func.m", // pName
      1                                                        // checkKind
  };
  static rtDoubleCheckInfo ib_emlrtDCI{
      80,                              // lineNo
      30,                              // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      1         // checkKind
  };
  static rtDoubleCheckInfo jb_emlrtDCI{
      80,                              // lineNo
      55,                              // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      1         // checkKind
  };
  static rtDoubleCheckInfo kb_emlrtDCI{
      84,                              // lineNo
      20,                              // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      1         // checkKind
  };
  static rtDoubleCheckInfo s_emlrtDCI{
      30,                          // lineNo
      25,                          // colNo
      "buildtimecorrelatormatrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/buildtimecorrelatormatrix"
      ".m", // pName
      1     // checkKind
  };
  static rtDoubleCheckInfo t_emlrtDCI{
      32,                          // lineNo
      25,                          // colNo
      "buildtimecorrelatormatrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/buildtimecorrelatormatrix"
      ".m", // pName
      1     // checkKind
  };
  static rtDoubleCheckInfo u_emlrtDCI{
      34,                              // lineNo
      32,                              // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      4         // checkKind
  };
  static rtDoubleCheckInfo v_emlrtDCI{
      34,                              // lineNo
      32,                              // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      1         // checkKind
  };
  static rtDoubleCheckInfo w_emlrtDCI{
      34,                              // lineNo
      50,                              // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      1         // checkKind
  };
  static rtDoubleCheckInfo x_emlrtDCI{
      36,                              // lineNo
      39,                              // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      1         // checkKind
  };
  static rtDoubleCheckInfo y_emlrtDCI{
      39,                              // lineNo
      31,                              // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      1         // checkKind
  };
  static rtEqualityCheckInfo g_emlrtECI{
      1,            // nDims
      70,           // lineNo
      15,           // colNo
      "assembleWq", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/assembleWq.m" // pName
  };
  static rtEqualityCheckInfo h_emlrtECI{
      -1,                          // nDims
      40,                          // lineNo
      1,                           // colNo
      "buildtimecorrelatormatrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/buildtimecorrelatormatrix"
      ".m" // pName
  };
  static rtEqualityCheckInfo i_emlrtECI{
      -1,                          // nDims
      42,                          // lineNo
      1,                           // colNo
      "buildtimecorrelatormatrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/buildtimecorrelatormatrix"
      ".m" // pName
  };
  static rtEqualityCheckInfo j_emlrtECI{
      -1,                              // nDims
      36,                              // lineNo
      1,                               // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m" // pName
  };
  static rtEqualityCheckInfo k_emlrtECI{
      -1,                              // nDims
      80,                              // lineNo
      5,                               // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m" // pName
  };
  static rtEqualityCheckInfo l_emlrtECI{
      2,            // nDims
      70,           // lineNo
      15,           // colNo
      "assembleWq", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/assembleWq.m" // pName
  };
  static rtRunTimeErrorInfo bd_emlrtRTEI{
      82,         // lineNo
      5,          // colNo
      "fltpower", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/ops/power.m" // pName
  };
  coder::array<double, 3U> pulse_position_value;
  coder::array<double, 2U> WqRowInds;
  coder::array<double, 2U> pattern_matrix;
  coder::array<double, 2U> priJtrList;
  coder::array<double, 2U> priMeansList;
  coder::array<double, 2U> pulsePositionMatrix;
  coder::array<double, 2U> shiftermat;
  coder::array<double, 1U> b_WqRowInds;
  coder::array<double, 1U> b_priMeansList;
  coder::array<double, 1U> r;
  double d;
  double n_rows;
  double num_PRI_patterns;
  double num_position_patterns;
  double stride;
  int sizes[2];
  int i;
  int i1;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  int ibtile;
  int loop_ub;
  int ncols;
  int ntilecols;
  int num_members_per_set;
  signed char input_sizes_idx_1;
  boolean_T empty_non_axis_sizes;
  if (!(pri >= 0.0)) {
    n_rtErrorWithMessageID("0", e_emlrtRTEI.fName, e_emlrtRTEI.lineNo);
  }
  if (!(priUncert >= 0.0)) {
    n_rtErrorWithMessageID("0", e_emlrtRTEI.fName, e_emlrtRTEI.lineNo);
  }
  if (!(priJtr >= 0.0)) {
    n_rtErrorWithMessageID("0", e_emlrtRTEI.fName, e_emlrtRTEI.lineNo);
  }
  if (!(reps >= 1.0)) {
    n_rtErrorWithMessageID("1", e_emlrtRTEI.fName, e_emlrtRTEI.lineNo);
  }
  // First check to make sure all inputs contain the same number of
  // elements
  d = 2.0 * priUncert + 1.0;
  if (d != static_cast<int>(std::floor(d))) {
    rtIntegerError(d, s_emlrtDCI);
  }
  num_PRI_patterns = 2.0 * priJtr + 1.0;
  if (num_PRI_patterns != static_cast<int>(std::floor(num_PRI_patterns))) {
    rtIntegerError(num_PRI_patterns, t_emlrtDCI);
  }
  // Change names to align with other code.
  if ((std::isinf(-priUncert) || std::isinf(priUncert)) &&
      (-priUncert == priUncert)) {
    priJtrList.set_size(1, 1);
    priJtrList[0] = rtNaN;
  } else if (std::floor(-priUncert) == -priUncert) {
    loop_ub = static_cast<int>(priUncert - (-priUncert));
    priJtrList.set_size(1, loop_ub + 1);
    for (i = 0; i <= loop_ub; i++) {
      priJtrList[i] = -priUncert + static_cast<double>(i);
    }
  } else {
    coder::eml_float_colon(-priUncert, priUncert, priJtrList);
  }
  if (static_cast<int>(d) != priJtrList.size(1)) {
    rtSizeEq1DError(static_cast<int>(d), priJtrList.size(1), h_emlrtECI);
  }
  priMeansList.set_size(1, priJtrList.size(1));
  loop_ub = priJtrList.size(1);
  for (i = 0; i < loop_ub; i++) {
    priMeansList[i] = pri + priJtrList[i];
  }
  if ((std::isinf(-priJtr) || std::isinf(priJtr)) && (-priJtr == priJtr)) {
    priJtrList.set_size(1, 1);
    priJtrList[0] = rtNaN;
  } else if (std::floor(-priJtr) == -priJtr) {
    loop_ub = static_cast<int>(priJtr - (-priJtr));
    priJtrList.set_size(1, loop_ub + 1);
    for (i = 0; i <= loop_ub; i++) {
      priJtrList[i] = -priJtr + static_cast<double>(i);
    }
  } else {
    coder::eml_float_colon(-priJtr, priJtr, priJtrList);
  }
  if (static_cast<int>(num_PRI_patterns) != priJtrList.size(1)) {
    rtSizeEq1DError(static_cast<int>(num_PRI_patterns), priJtrList.size(1),
                    i_emlrtECI);
  }
  //  ASSEMBLEWQ Build the Wq matrix that is used in the incoherent summation
  //  based on a set of mean PRI values, jitter values, and the number of
  //  pulses to sum (K).
  // INPUTS:
  //    PRI_means   a vector of mean PRI values in units of STFT windows.
  //    PRI_jitters a vector of the jitter values in units of STFT windows.
  //    K           The number of pulses that will be summed
  // OUTPUTS:
  //    Wq          a sparse matrix to be used for the incoherent summation
  //
  // Example. Consider an interpulse nominal time of 10 stft windows and an
  // uncertainty of 2. The PRI_mean values would be the vector 10 + (-2:2) =
  //  [8     9    10    11    12]. Jitters input would be something like -1:1.
  //
  // --------------------------------------------------------------------------
  // PPM Contains the column positions (time windows) in the S matrix to search
  // for the K pulses assuming the first pulse arrives at window 1.
  //  GENERATE_PULSE_POSITIONS_FUNC generates the pulse position matrix from
  //  the number of pulses, mean pri values, and jitter values.
  //  PPM Contains the column positions (time windows) in the S matrix to
  //  search for the K pulses assuming the first pulse arrives at window 1.
  //
  //  INPUTS:
  //    PRI_mean_value          row vector of PRI means (scale/index is STFT
  //    step
  //                            size)
  //
  //    PRI_jitter_value        row vector of jitter values (scale/index is STFT
  //    step
  //                            size)
  //
  //    K                       number of pulses forming the pattern
  //
  //  OUTPUTS:
  //    pulse_position_matrix   row is a pattern; each pattern has K pulse
  //                            position values
  //
  //  CALLS:
  //                            cartesion_prod_func()
  //
  //  Author: Paul G. Flikkema
  //  Date:   1 Oct 2021
  // --------------------------------------------------------------------------
  ntilecols = priJtrList.size(1);
  if ((ntilecols < 0) && (std::floor(reps - 1.0) != reps - 1.0)) {
    mb_rtErrorWithMessageID(bd_emlrtRTEI.fName, bd_emlrtRTEI.lineNo);
  }
  num_PRI_patterns = static_cast<double>(priMeansList.size(1)) *
                     rt_powd_snf(static_cast<double>(ntilecols), reps - 1.0);
  if (!(num_PRI_patterns >= 0.0)) {
    rtNonNegativeError(num_PRI_patterns, u_emlrtDCI);
  }
  i = static_cast<int>(std::floor(num_PRI_patterns));
  if (num_PRI_patterns != i) {
    rtIntegerError(num_PRI_patterns, v_emlrtDCI);
  }
  i1 = static_cast<int>(std::floor(reps));
  if (reps != i1) {
    rtIntegerError(reps, w_emlrtDCI);
  }
  ncols = static_cast<int>(num_PRI_patterns);
  if (ncols != i) {
    rtIntegerError(num_PRI_patterns, v_emlrtDCI);
  }
  i2 = static_cast<int>(reps);
  if (i2 != i1) {
    rtIntegerError(reps, w_emlrtDCI);
  }
  //  place first pulse at pulse position q = 1
  if (ncols != i) {
    rtIntegerError(num_PRI_patterns, x_emlrtDCI);
  }
  rtSubAssignSizeCheck(&ncols, 1, &ncols, 1, j_emlrtECI);
  //  based on the model, generate all the pulse position values in a 3D matrix
  if (i2 != i1) {
    rtIntegerError(reps, y_emlrtDCI);
  }
  pulse_position_value.set_size(i2, priJtrList.size(1), priMeansList.size(1));
  if (i2 != i1) {
    rtIntegerError(reps, ab_emlrtDCI);
  }
  loop_ub = i2 * priJtrList.size(1) * priMeansList.size(1);
  for (i = 0; i < loop_ub; i++) {
    pulse_position_value[i] = 0.0;
  }
  loop_ub = priMeansList.size(1);
  for (i = 0; i < loop_ub; i++) {
    ncols = priJtrList.size(1);
    for (i1 = 0; i1 < ncols; i1++) {
      pulse_position_value[pulse_position_value.size(0) * i1 +
                           pulse_position_value.size(0) *
                               pulse_position_value.size(1) * i] = 1.0;
    }
  }
  //  first pulse is always in position 1
  //  loop through the mean PRI values
  i = priMeansList.size(1);
  for (ncols = 0; ncols < i; ncols++) {
    i1 = i2 - 1;
    for (ntilecols = 0; ntilecols < i1; ntilecols++) {
      i3 = priJtrList.size(1);
      for (ibtile = 0; ibtile < i3; ibtile++) {
        if (ncols + 1 > priMeansList.size(1)) {
          rtDynamicBoundsError(ncols + 1, 1, priMeansList.size(1), ab_emlrtBCI);
        }
        if (ibtile + 1 > priJtrList.size(1)) {
          rtDynamicBoundsError(ibtile + 1, 1, priJtrList.size(1), bb_emlrtBCI);
        }
        if (static_cast<int>(static_cast<unsigned int>(ntilecols) + 2U) >
            pulse_position_value.size(0)) {
          rtDynamicBoundsError(
              static_cast<int>(static_cast<unsigned int>(ntilecols) + 2U), 1,
              pulse_position_value.size(0), cb_emlrtBCI);
        }
        if (ibtile + 1 > pulse_position_value.size(1)) {
          rtDynamicBoundsError(ibtile + 1, 1, pulse_position_value.size(1),
                               db_emlrtBCI);
        }
        if (ncols + 1 > pulse_position_value.size(2)) {
          rtDynamicBoundsError(ncols + 1, 1, pulse_position_value.size(2),
                               eb_emlrtBCI);
        }
        pulse_position_value[((ntilecols +
                               pulse_position_value.size(0) * ibtile) +
                              pulse_position_value.size(0) *
                                  pulse_position_value.size(1) * ncols) +
                             1] =
            (((static_cast<double>(ntilecols) + 2.0) - 1.0) *
                 priMeansList[ncols] +
             1.0) +
            priJtrList[ibtile];
      }
    }
  }
  //  generate the pulse_position_matrix by considering
  //  all possible combinations of the values;
  //  each row is for one pattern, there are K columns;
  //  pulse_position_matrix( i_pattern, k)
  //
  //  The number of columns is the number of possible positions
  //
  //  we generate a num_PRI_jitters^(K-1) x K matrix
  //  using the function cartesian_prod_func
  //
  //  we stack matrices vertically into the pulse_position_matrix
  ntilecols = priJtrList.size(1);
  ncols = static_cast<int>(reps) - 1;
  num_position_patterns =
      static_cast<double>(priMeansList.size(1)) *
      rt_powd_snf(static_cast<double>(ntilecols), static_cast<double>(ncols));
  if (!(num_position_patterns >= 0.0)) {
    rtNonNegativeError(num_position_patterns, bb_emlrtDCI);
  }
  if (num_position_patterns != static_cast<int>(num_position_patterns)) {
    rtIntegerError(num_position_patterns, cb_emlrtDCI);
  }
  pulsePositionMatrix.set_size(static_cast<int>(num_position_patterns),
                               pulsePositionMatrix.size(1));
  pulsePositionMatrix.set_size(pulsePositionMatrix.size(0), ncols);
  if (static_cast<int>(num_position_patterns) !=
      static_cast<int>(num_position_patterns)) {
    rtIntegerError(num_position_patterns, db_emlrtDCI);
  }
  loop_ub = static_cast<int>(num_position_patterns) * ncols;
  for (i = 0; i < loop_ub; i++) {
    pulsePositionMatrix[i] = 0.0;
  }
  ntilecols = priJtrList.size(1);
  n_rows =
      rt_powd_snf(static_cast<double>(ntilecols), static_cast<double>(ncols));
  //  number of rows per PRI mean
  i = priMeansList.size(1);
  if (priMeansList.size(1) - 1 >= 0) {
    if (pulse_position_value.size(0) < 2) {
      i4 = 1;
      i5 = 0;
    } else {
      i4 = 2;
      i5 = pulse_position_value.size(0);
    }
    num_members_per_set = pulse_position_value.size(1);
    i6 = i5 - i4;
  }
  for (int i_set{0}; i_set < i; i_set++) {
    //      % DEBUG
    //      a = [ 1 1 1 ]; b = [ 309 310 311 ]; c = [ 618 619 620 ];
    //      A = [ a; b; c ];
    //  since pattern is "fundamental" pattern starting with a pulse in the
    //  first STFT window, we only need to look at combinations
    //  rows 2:end, and then add the column of ones
    if (i_set + 1 > pulse_position_value.size(2)) {
      rtDynamicBoundsError(i_set + 1, 1, pulse_position_value.size(2),
                           fb_emlrtBCI);
    }
    // CARTESIAN_PROD_FUNC returns the Cartesian product C of the values in the
    //  rows of the input matrix A. Each row of A is taken as a set to draw from
    //  Assumes all sets have the same number of members
    // INPUTS:
    //    A   nxm matrix
    // OUTPUTS:
    //    C   a matrix of all the combinations of the sets in the columns of A
    ncols = i5 - i4;
    ntilecols = pulse_position_value.size(1);
    if ((ntilecols < 0) && (static_cast<double>(ncols) + 1.0 !=
                            static_cast<double>(ncols) + 1.0)) {
      mb_rtErrorWithMessageID(bd_emlrtRTEI.fName, bd_emlrtRTEI.lineNo);
    }
    num_PRI_patterns = rt_powd_snf(static_cast<double>(ntilecols),
                                   static_cast<double>(ncols) + 1.0);
    i1 = static_cast<int>(std::floor(num_PRI_patterns));
    if (num_PRI_patterns != i1) {
      rtIntegerError(num_PRI_patterns, eb_emlrtDCI);
    }
    i2 = static_cast<int>(num_PRI_patterns);
    pattern_matrix.set_size(i2, ncols + 1);
    if (i2 != i1) {
      rtIntegerError(num_PRI_patterns, fb_emlrtDCI);
    }
    loop_ub = i2 * (ncols + 1);
    for (i1 = 0; i1 < loop_ub; i1++) {
      pattern_matrix[i1] = 0.0;
    }
    //  loop through columns of C
    for (ntilecols = 0; ntilecols <= i6; ntilecols++) {
      unsigned int i_col_A;
      //  fill the column (aka fill the elements in the column)
      //  stride is number of elements to repeat in a column
      //  num_strides is number of strides per column
      stride = rt_powd_snf(static_cast<double>(num_members_per_set),
                           static_cast<double>(ncols - ntilecols));
      i_col_A = 0U;
      //  the column in A that we use
      i1 = static_cast<int>(num_PRI_patterns / stride);
      for (ibtile = 0; ibtile < i1; ibtile++) {
        double star;
        i_col_A++;
        if (i_col_A > static_cast<unsigned int>(num_members_per_set)) {
          i_col_A = 1U;
        }
        star = ((static_cast<double>(ibtile) + 1.0) - 1.0) * stride + 1.0;
        //  column of C gets elements from row of A
        d = (star + stride) - 1.0;
        if (star > d) {
          i2 = 0;
          i3 = 0;
        } else {
          if (star != static_cast<int>(std::floor(star))) {
            rtIntegerError(star, gb_emlrtDCI);
          }
          if ((static_cast<int>(star) < 1) ||
              (static_cast<int>(star) > pattern_matrix.size(0))) {
            rtDynamicBoundsError(static_cast<int>(star), 1,
                                 pattern_matrix.size(0), ib_emlrtBCI);
          }
          i2 = static_cast<int>(star) - 1;
          if (d != static_cast<int>(std::floor(d))) {
            rtIntegerError(d, hb_emlrtDCI);
          }
          if ((static_cast<int>(d) < 1) ||
              (static_cast<int>(d) > pattern_matrix.size(0))) {
            rtDynamicBoundsError(static_cast<int>(d), 1, pattern_matrix.size(0),
                                 jb_emlrtBCI);
          }
          i3 = static_cast<int>(d);
        }
        if (ntilecols + 1 > pattern_matrix.size(1)) {
          rtDynamicBoundsError(ntilecols + 1, 1, pattern_matrix.size(1),
                               gb_emlrtBCI);
        }
        loop_ub = i3 - i2;
        for (i3 = 0; i3 < loop_ub; i3++) {
          if (ntilecols + 1 > ncols + 1) {
            rtDynamicBoundsError(ntilecols + 1, 1, ncols + 1, hb_emlrtBCI);
          }
          if ((static_cast<int>(i_col_A) < 1) ||
              (static_cast<int>(i_col_A) > pulse_position_value.size(1))) {
            rtDynamicBoundsError(static_cast<int>(i_col_A), 1,
                                 pulse_position_value.size(1), hb_emlrtBCI);
          }
          pattern_matrix[(i2 + i3) + pattern_matrix.size(0) * ntilecols] =
              pulse_position_value[(((i4 + ntilecols) +
                                     pulse_position_value.size(0) *
                                         (static_cast<int>(i_col_A) - 1)) +
                                    pulse_position_value.size(0) *
                                        pulse_position_value.size(1) * i_set) -
                                   1];
        }
      }
    }
    d = ((static_cast<double>(i_set) + 1.0) - 1.0) * n_rows + 1.0;
    num_PRI_patterns = (static_cast<double>(i_set) + 1.0) * n_rows;
    if (d > num_PRI_patterns) {
      i1 = 0;
      i2 = 0;
    } else {
      if (d != static_cast<int>(d)) {
        rtIntegerError(d, ib_emlrtDCI);
      }
      if ((static_cast<int>(d) < 1) ||
          (static_cast<int>(d) > pulsePositionMatrix.size(0))) {
        rtDynamicBoundsError(static_cast<int>(d), 1,
                             pulsePositionMatrix.size(0), kb_emlrtBCI);
      }
      i1 = static_cast<int>(d) - 1;
      if (num_PRI_patterns != static_cast<int>(num_PRI_patterns)) {
        rtIntegerError(num_PRI_patterns, jb_emlrtDCI);
      }
      if ((static_cast<int>(num_PRI_patterns) < 1) ||
          (static_cast<int>(num_PRI_patterns) > pulsePositionMatrix.size(0))) {
        rtDynamicBoundsError(static_cast<int>(num_PRI_patterns), 1,
                             pulsePositionMatrix.size(0), lb_emlrtBCI);
      }
      i2 = static_cast<int>(num_PRI_patterns);
    }
    sizes[0] = i2 - i1;
    sizes[1] = pulsePositionMatrix.size(1);
    rtSubAssignSizeCheck(&sizes[0], 2, pattern_matrix.size(), 2, k_emlrtECI);
    loop_ub = pattern_matrix.size(1);
    for (i2 = 0; i2 < loop_ub; i2++) {
      ncols = pattern_matrix.size(0);
      for (i3 = 0; i3 < ncols; i3++) {
        pulsePositionMatrix[(i1 + i3) + pulsePositionMatrix.size(0) * i2] =
            pattern_matrix[i3 + pattern_matrix.size(0) * i2];
      }
    }
  }
  if (static_cast<int>(num_position_patterns) !=
      static_cast<int>(num_position_patterns)) {
    rtIntegerError(num_position_patterns, kb_emlrtDCI);
  }
  if (num_position_patterns != 0.0) {
    ncols = static_cast<int>(num_position_patterns);
  } else if ((pulsePositionMatrix.size(0) != 0) &&
             (pulsePositionMatrix.size(1) != 0)) {
    ncols = pulsePositionMatrix.size(0);
  } else {
    ncols = static_cast<int>(num_position_patterns);
    if (pulsePositionMatrix.size(0) > ncols) {
      ncols = pulsePositionMatrix.size(0);
    }
  }
  if ((static_cast<int>(num_position_patterns) != ncols) &&
      (!(num_position_patterns == 0.0))) {
    gb_rtErrorWithMessageID(ub_emlrtRTEI.fName, ub_emlrtRTEI.lineNo);
  }
  if ((pulsePositionMatrix.size(0) != ncols) &&
      ((pulsePositionMatrix.size(0) != 0) &&
       (pulsePositionMatrix.size(1) != 0))) {
    gb_rtErrorWithMessageID(ub_emlrtRTEI.fName, ub_emlrtRTEI.lineNo);
  }
  empty_non_axis_sizes = (ncols == 0);
  if (empty_non_axis_sizes || (num_position_patterns != 0.0)) {
    input_sizes_idx_1 = 1;
  } else {
    input_sizes_idx_1 = 0;
  }
  if (empty_non_axis_sizes || ((pulsePositionMatrix.size(0) != 0) &&
                               (pulsePositionMatrix.size(1) != 0))) {
    sizes[1] = pulsePositionMatrix.size(1);
  } else {
    sizes[1] = 0;
  }
  //  remove duplicate patterns
  pattern_matrix.set_size(ncols, input_sizes_idx_1 + sizes[1]);
  loop_ub = input_sizes_idx_1;
  for (i = 0; i < loop_ub; i++) {
    for (i1 = 0; i1 < ncols; i1++) {
      pattern_matrix[i1] = 1.0;
    }
  }
  loop_ub = sizes[1];
  for (i = 0; i < loop_ub; i++) {
    for (i1 = 0; i1 < ncols; i1++) {
      pattern_matrix[i1 + pattern_matrix.size(0) * (i + input_sizes_idx_1)] =
          pulsePositionMatrix[i1 + ncols * i];
    }
  }
  coder::unique_rows(pattern_matrix, pulsePositionMatrix);
  //  if K>1
  //      %n_shifts = min(pulsePositionMatrix(:,2))-1;   %The number of shifts
  //      necessary.
  //
  //  else
  //      n_shifts = max(PRI_means_q)+max(PRI_jitters_q);
  //  end
  // The max element of the ppm for K>1 is (K-1)*(N+M)+J+1 which is the latest
  // possible index of the Kth pulse if the first arrived at n = 1.
  //
  // The max element of the ppm for K=1 is 1 which is the first possible index
  // of the 1st pulse.
  //
  // The size of the STFT matrix is the latest possible location of the Kth
  // pulse which is equal to K*(N+M)+J+1
  //
  // We want to take the PPM matrix that contains the the time locations for
  // the search if the first pulse is at n=1 and shift them to do the search if
  // the first pulse arrives and n = 2,..., N+M+J+1 which is the latest
  // possible location of the pulse pulse. The difference is N+M+J+1-1 = N+M+J
  // This is the max number we need to add the the PPM matrix.
  //
  // For the K = 1 case, the PPM is simply 1 and we add N+M+J which generates a
  // Wq matrix with a dimension of 1+N+M+J. This is equivalent to the STFT
  // size definition for K = 1, which is K(N+M)+J+1 = N+M+J+1, so the sizes
  // will be compatible.
  //
  // For the K > 1 case however the maximum element of the PPM is
  // (K-1)(N+M)+J+1. Adding N+M+J to this will result in a Wq with a dimension
  // of (K-1)(N+M)+J+1+N+M+J = K(N+M)+2J+1. This will be J elements larger than
  // the STFT definitions of K(N+M)+J+1. This extra J comes from the fact that
  // the max element of the PPM include the jitter of the final pulse and we
  // also include the jitter in the shifting. Because jitter is stochastic and
  // zero mean, we don't sum jitter over multiple pulses. We need to remove the
  // extra jitter when shifting for K>1.
  //
  if (reps > 1.0) {
    ntilecols = priMeansList.size(1);
    b_priMeansList = priMeansList.reshape(ntilecols);
    num_PRI_patterns = coder::internal::maximum(b_priMeansList);
    // Equivalent to N+M+J-J
  } else {
    ntilecols = priMeansList.size(1);
    b_priMeansList = priMeansList.reshape(ntilecols);
    num_PRI_patterns = coder::internal::maximum(b_priMeansList);
    ncols = priJtrList.size(1);
    b_priMeansList = priJtrList.reshape(ncols);
    stride = coder::internal::maximum(b_priMeansList);
    num_PRI_patterns += stride;
    // Equivalent to N+M+J
  }
  // Number of rows in pulse_position_matrix
  // Number of cols in pulse_position_matrix --- should always be K
  coder::repmat(pulsePositionMatrix, num_PRI_patterns + 1.0, pattern_matrix);
  // Create multiple copies of the PPM matrix. Each copy will eventually be
  // shifted. The second copy will get a 1 added to it, the third a 2 added, and
  // so on up to n_shifts. Use n_shifts+1 to account for the first one that
  // receives no shifting. Get the number of rows in the big PPM matrix
  if (std::isnan(num_PRI_patterns)) {
    priJtrList.set_size(1, 1);
    priJtrList[0] = rtNaN;
  } else if (num_PRI_patterns < 0.0) {
    priJtrList.set_size(1, 0);
  } else {
    priJtrList.set_size(1, static_cast<int>(num_PRI_patterns) + 1);
    loop_ub = static_cast<int>(num_PRI_patterns);
    for (i = 0; i <= loop_ub; i++) {
      priJtrList[i] = i;
    }
  }
  coder::b_repmat(priJtrList, static_cast<double>(pulsePositionMatrix.size(0)),
                  shiftermat);
  // Create a matrix of the shifts needed for each copy of the PPM matrix
  ncols = shiftermat.size(0) * shiftermat.size(1);
  b_priMeansList = shiftermat.reshape(ncols);
  coder::repmat(b_priMeansList,
                static_cast<double>(pulsePositionMatrix.size(1)), WqRowInds);
  if ((WqRowInds.size(0) != pattern_matrix.size(0)) &&
      ((WqRowInds.size(0) != 1) && (pattern_matrix.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(WqRowInds.size(0), pattern_matrix.size(0),
                                g_emlrtECI);
  }
  if ((WqRowInds.size(1) != pattern_matrix.size(1)) &&
      ((WqRowInds.size(1) != 1) && (pattern_matrix.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(WqRowInds.size(1), pattern_matrix.size(1),
                                l_emlrtECI);
  }
  if ((WqRowInds.size(0) == pattern_matrix.size(0)) &&
      (WqRowInds.size(1) == pattern_matrix.size(1))) {
    loop_ub = WqRowInds.size(0) * WqRowInds.size(1);
    for (i = 0; i < loop_ub; i++) {
      WqRowInds[i] = WqRowInds[i] + pattern_matrix[i];
    }
  } else {
    plus(WqRowInds, pattern_matrix);
  }
  if (pattern_matrix.size(0) < 1) {
    priJtrList.set_size(1, 0);
  } else {
    priJtrList.set_size(1, pattern_matrix.size(0));
    loop_ub = pattern_matrix.size(0) - 1;
    for (i = 0; i <= loop_ub; i++) {
      priJtrList[i] = static_cast<double>(i) + 1.0;
    }
  }
  coder::internal::assertValidSizeArg(
      static_cast<double>(pulsePositionMatrix.size(1)));
  priMeansList.set_size(1, priJtrList.size(1) * pulsePositionMatrix.size(1));
  ncols = priJtrList.size(1);
  ntilecols = pulsePositionMatrix.size(1);
  if (pulsePositionMatrix.size(1) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  for (loop_ub = 0; loop_ub < ntilecols; loop_ub++) {
    ibtile = loop_ub * ncols;
    if (ncols > 2147483646) {
      coder::check_forloop_overflow_error();
    }
    for (int i_set{0}; i_set < ncols; i_set++) {
      priMeansList[ibtile + i_set] = priJtrList[i_set];
    }
  }
  ibtile = WqRowInds.size(0) * WqRowInds.size(1);
  ntilecols = priMeansList.size(1);
  ncols = WqRowInds.size(0) * WqRowInds.size(1);
  r.set_size(ncols);
  for (i = 0; i < ncols; i++) {
    r[i] = 1.0;
  }
  b_WqRowInds = WqRowInds.reshape(ibtile);
  b_priMeansList = priMeansList.reshape(ntilecols);
  coder::i_sparse(b_WqRowInds, b_priMeansList, r, Wq);
}

//
// File trailer for buildtimecorrelatormatrix.cpp
//
// [EOF]
//
