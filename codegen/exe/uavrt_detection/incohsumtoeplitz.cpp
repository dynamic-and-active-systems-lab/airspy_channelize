//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: incohsumtoeplitz.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "incohsumtoeplitz.h"
#include "any1.h"
#include "assertValidSizeArg.h"
#include "eml_int_forloop_overflow_check.h"
#include "find.h"
#include "indexShapeCheck.h"
#include "minOrMax.h"
#include "mtimes.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "sparse.h"
#include "sparse1.h"
#include "sub2ind.h"
#include "sum.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"

// Function Definitions
//
// INCOHSUMTOEPLITZ Performs the incoherent summation of time windows of an
// input matrix S per the elements in the time selection matrix Wq.
//    This function performs the incoherent summation of time elements within
//    the short time Fourier transform matrix S per the selections within the
//    Wq matrix. The rows of the S matrix represent frequency bins, whereas
//    the columns represent the time windows. The Wq matrix is a Toeplitz
//    based matrix with non-zero elements of each column used to select and
//    then sum through matrix multiplication the time windows of S.
//     abs(S).^2    *  Wq
//    [1   2  3  4]  [1 0]
//    [5   6  7  8]  [0 1]
//    [9  10 11 12]  [1 0]
//    [13 14 15 16]  [0 1]
//
//    The other matricies are used to select and weight the frequency and
//    time elements of S through matrix multiplication. The Wfherm matrix
//    applies weightings to the S matrix across frequency in order to capture
//    energy spread across frequency bins. Fb is a matrix or a vector with 1s
//    in elements associated with the frequency bins of Wh that are to be
//    included for consideration. Similarly, the Tb matrix (vector) uses 1s
//    to select time elements for consideration. Both Fb and Tb can use zeros
//    to exclude particular frequencies or times from consideration in
//    processing.
//
//    The code performs the matrix multiplication Fb*Wfherm*abs(S).^2*Tb*Wq.
//    The sizes of these matricies must be set so that this matrix
//    multiplication can be performed. The functions checks for correct
//    dimensions and will generate an error of dimensional mismatch occurs.
//    After performing the matrix multiplication of Fb*Wfherm*S*Tb*Wq, it
//    determines which columns of the resulting matrix are maximum in each
//    row (frequency bin). The function reports the a matrix that has the
//    same number of rows as Fb and K columns that contains the scores for
//    in each S time window that the maximum summed score based on the Wq
//    matrix selections for each frequency bin. It also reports a similarly
//    size matrix that contains the columns in S where these max scores were
//    found
//
//    The number of pulses for summation (K) is extracted from Wq by querying
//    the number of non-zero elements in the first column of the Wq matrix.
//
//
// INPUTS:
//    Fb      Frequency blinder matrix: A matrix (fz x fz) or vector (fz x 1)
//            of elements with 1s for frequencies of the Wfherm matrix that
//            should be considered when looking for maximum incoheren
//            summation. If the rows of the Wfherm matrix represent
//            frequencies of [100 50 0 -50 -100] and the search needs to
//            focus only on the 0 and 50 Hz bins, Fb should be [0 1 1 0 0]
//            or diag([0 1 1 0 0]). Inputs can be full or sparse.
//    Wfherm  Hermitian of the spectral weighting matrix. This matrix should
//            have the same number of columns as the number of rows in S. See
//            weightingmatrix.m for information on this matrix. The function
//            weightingmatrix.m generates Wf, so when passing Wf to this
//            function, Wf' should be used.
//    S       STFT output matrix
//    Tb      Time blinder matrix: A matrix with only diagonal elements or a
//            vector that contains 1s that corresponds to the columns (time
//            windows) of the S matrix that should be considered for
//            summation. If priori information informs the caller as to the
//            potential location of the pulses in the block being processed,
//            the Tb matrix can be used to exclude other times from
//            consideration which can considerably decrease processing time
//            for this function. If no-priori is available, this entry should
//            be the identity matrix or vector of size equal to the number
//            of columns of S.
//    Wq      Time correlation matrix: A matrix containing 1s in entries in
//            each column for S matrix time windows that should be summed.
//            Wq must have the same number of rows as columns of S, but can
//            have as many columns as summation cases that need to be
//            considered.
//    IR      Repetition rejection comb filter matrix. Set to the identity to
//            if no comb filtering is needed.
//
// OUTPUTS:
//    Sscores The results of the incoherent summation of S per the time
//            selections of the inputs after looking for maximums for each
//            frequency bin. This has the same number of rows as that of the
//            input Fb and the same number of columns a the number of pulses
//            used for summation. The matrix has K columns. The scores
//            represent the square magnitudes of the selected elements of the
//            S matrix.
//
//    Scols   A matrix of the columns of S (time windows of STFT)
//            that correspond to the potential pulses identified
//            in Sscors. The size of this matrix is the same as Sscores.
//
//
// Author: Michael W. Shafer
// Date:   2022-03-31
// --------------------------------------------------------------------------
//
// Arguments    : const coder::array<boolean_T, 1U> &Fb
//                const coder::array<creal_T, 2U> &Wfherm
//                const coder::array<creal_T, 2U> &S
//                const coder::sparse &IR
//                const coder::array<double, 1U> &Tb
//                const coder::sparse &Wq
//                coder::array<double, 2U> &Sscores
//                coder::array<double, 2U> &Scols
// Return Type  : void
//
void incohsumtoeplitz(const coder::array<boolean_T, 1U> &Fb,
                      const coder::array<creal_T, 2U> &Wfherm,
                      const coder::array<creal_T, 2U> &S,
                      const coder::sparse &IR,
                      const coder::array<double, 1U> &Tb,
                      const coder::sparse &Wq,
                      coder::array<double, 2U> &Sscores,
                      coder::array<double, 2U> &Scols)
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      -1,                 // iFirst
      -1,                 // iLast
      199,                // lineNo
      1,                  // colNo
      "Scols",            // aName
      "incohsumtoeplitz", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/incohsumtoeplitz.m", // pName
      0                                                     // checkKind
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      -1,                 // iFirst
      -1,                 // iLast
      198,                // lineNo
      1,                  // colNo
      "Sscores",          // aName
      "incohsumtoeplitz", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/incohsumtoeplitz.m", // pName
      0                                                     // checkKind
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      -1,                 // iFirst
      -1,                 // iLast
      193,                // lineNo
      24,                 // colNo
      "allScores",        // aName
      "incohsumtoeplitz", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/incohsumtoeplitz.m", // pName
      0                                                     // checkKind
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      -1,                 // iFirst
      -1,                 // iLast
      178,                // lineNo
      37,                 // colNo
      "Tb",               // aName
      "incohsumtoeplitz", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/incohsumtoeplitz.m", // pName
      0                                                     // checkKind
  };
  static rtBoundsCheckInfo eb_emlrtBCI{
      -1,                 // iFirst
      -1,                 // iLast
      165,                // lineNo
      37,                 // colNo
      "Fb",               // aName
      "incohsumtoeplitz", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/incohsumtoeplitz.m", // pName
      0                                                     // checkKind
  };
  coder::b_sparse pulsesInEachColumn;
  coder::c_sparse firstPulseNum;
  coder::d_sparse r;
  coder::d_sparse sameAsFirst;
  coder::e_sparse b_this;
  coder::f_sparse FbSparseMat;
  coder::f_sparse TbSparseMat;
  coder::g_sparse r2;
  coder::h_sparse Tbdiags;
  coder::sparse b_y;
  coder::array<creal_T, 2U> d_y;
  coder::array<double, 2U> FbmatDiagInds;
  coder::array<double, 2U> Sinds;
  coder::array<double, 2U> Srows;
  coder::array<double, 2U> allScores;
  coder::array<double, 2U> c_y;
  coder::array<double, 1U> ex;
  coder::array<int, 2U> r1;
  coder::array<int, 2U> r3;
  coder::array<int, 1U> b_idx;
  coder::array<int, 1U> jj;
  coder::array<int, 1U> r4;
  coder::array<boolean_T, 2U> Fbdiags;
  coder::array<boolean_T, 2U> b_S;
  double K;
  double varargin_1;
  int b_Fbnumrows_tmp[2];
  int Fbnumrows_tmp;
  int Tbnumrows_tmp;
  int a;
  int b_minval_tmp;
  int cend;
  int loop_ub_tmp;
  int maxdimlen;
  int minval_tmp;
  boolean_T y;
  if (Tb.size(0) > 1) {
    minval_tmp = 1;
  } else {
    minval_tmp = Tb.size(0);
  }
  if (Fb.size(0) > 1) {
    b_minval_tmp = 1;
  } else {
    b_minval_tmp = Fb.size(0);
  }
  if ((minval_tmp != 1) && (Tb.size(0) != 1)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  if ((b_minval_tmp != 1) && (Fb.size(0) != 1)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  if (Tb.size(0) < 1) {
    Tbnumrows_tmp = 1;
  } else {
    Tbnumrows_tmp = Tb.size(0);
  }
  if (Fb.size(0) < 1) {
    Fbnumrows_tmp = 1;
  } else {
    Fbnumrows_tmp = Fb.size(0);
  }
  if (Fbnumrows_tmp != Wfherm.size(0)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  if (S.size(0) != Wfherm.size(1)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  if (S.size(1) != Tbnumrows_tmp) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  if (Tbnumrows_tmp != Wq.m) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  // Make sure the number of pulses considered for all Wq columns is the same
  coder::sum(Wq, pulsesInEachColumn);
  pulsesInEachColumn.parenReference(firstPulseNum);
  b_S.set_size(1, pulsesInEachColumn.n);
  loop_ub_tmp = pulsesInEachColumn.n;
  for (int idx{0}; idx < loop_ub_tmp; idx++) {
    b_S[idx] = true;
  }
  if (pulsesInEachColumn.n > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  for (cend = 0; cend < loop_ub_tmp; cend++) {
    a = pulsesInEachColumn.colidx[cend];
    maxdimlen = pulsesInEachColumn.colidx[cend + 1] - 1;
    if ((pulsesInEachColumn.colidx[cend] <= maxdimlen) &&
        (maxdimlen > 2147483646)) {
      coder::check_forloop_overflow_error();
    }
    for (int idx{a}; idx <= maxdimlen; idx++) {
      b_S[cend] = (pulsesInEachColumn.d[idx - 1] <= 0.0);
    }
  }
  coder::j_sparse(b_S, sameAsFirst);
  coder::any(sameAsFirst, b_this);
  y = false;
  cend = b_this.colidx[1] - 1;
  a = b_this.colidx[0];
  if ((b_this.colidx[0] <= b_this.colidx[1] - 1) &&
      (b_this.colidx[1] - 1 > 2147483646)) {
    coder::check_forloop_overflow_error();
  }
  for (int idx{a}; idx <= cend; idx++) {
    y = b_this.d[idx - 1];
  }
  if (y) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  pulsesInEachColumn.eq(firstPulseNum, sameAsFirst);
  sameAsFirst.b_not(r);
  coder::any(r, b_this);
  y = false;
  cend = b_this.colidx[1] - 1;
  a = b_this.colidx[0];
  if ((b_this.colidx[0] <= b_this.colidx[1] - 1) &&
      (b_this.colidx[1] - 1 > 2147483646)) {
    coder::check_forloop_overflow_error();
  }
  for (int idx{a}; idx <= cend; idx++) {
    y = b_this.d[idx - 1];
  }
  if (y) {
    // numel(unique(full(pulsesInEachColumn)))~=1 %Unique doesn't support sparse
    // for code-generation. %numel(unique(sum(Wq,1)))~=1
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  //  Generate Tb and Fb sparse matrices if entered as vectors
  // Frequency Blinder (Fb) matrix definitions:
  coder::internal::assertValidSizeArg(static_cast<double>(Fbnumrows_tmp));
  coder::internal::assertValidSizeArg(static_cast<double>(Fbnumrows_tmp));
  coder::sparse::eyeLike(Fbnumrows_tmp, Fbnumrows_tmp, Fbnumrows_tmp, b_y);
  b_y.logical(FbSparseMat);
  // Prototype Fb matrix with identity logical matrix
  if (Fbnumrows_tmp < 1) {
    FbmatDiagInds.set_size(1, 0);
    c_y.set_size(1, 0);
  } else {
    FbmatDiagInds.set_size(1, Fbnumrows_tmp);
    loop_ub_tmp = Fbnumrows_tmp - 1;
    c_y.set_size(1, Fbnumrows_tmp);
    for (int idx{0}; idx <= loop_ub_tmp; idx++) {
      FbmatDiagInds[idx] = static_cast<double>(idx) + 1.0;
      c_y[idx] = static_cast<double>(idx) + 1.0;
    }
  }
  b_Fbnumrows_tmp[0] = Fbnumrows_tmp;
  b_Fbnumrows_tmp[1] = Fbnumrows_tmp;
  coder::internal::sub2ind(b_Fbnumrows_tmp, FbmatDiagInds, c_y, r1);
  FbmatDiagInds.set_size(1, r1.size(1));
  maxdimlen = r1.size(1);
  for (int idx{0}; idx < maxdimlen; idx++) {
    FbmatDiagInds[idx] = r1[idx];
  }
  if (b_minval_tmp == 1) {
    // Passed a vector, so make the matrix
    Fbdiags.set_size(Fb.size(0), 1);
    maxdimlen = Fb.size(0);
    for (int idx{0}; idx < maxdimlen; idx++) {
      Fbdiags[idx] = Fb[idx];
    }
    // FbSparseMat = logical(speye(max(Fbsz)));
    FbSparseMat.parenAssign(Fb, FbmatDiagInds);
  } else {
    // Passed a matrix, so make sparse.
    // FbSparseMat = logical(sparse(Fb));
    b_S.set_size(1, FbmatDiagInds.size(1));
    maxdimlen = FbmatDiagInds.size(1);
    for (int idx{0}; idx < maxdimlen; idx++) {
      a = static_cast<int>(FbmatDiagInds[idx]);
      if ((a < 1) || (a > Fb.size(0))) {
        rtDynamicBoundsError(a, 1, Fb.size(0), eb_emlrtBCI);
      }
      b_S[idx] = Fb[a - 1];
    }
    FbSparseMat.b_parenAssign(b_S, FbmatDiagInds);
    // Had do do it this way rather than with logical(sparse(Fb)) to get code to
    // work with Fb being either a vector or matrix.
    FbSparseMat.parenReference(FbmatDiagInds, r);
    r.full(b_S);
    cend = b_S.size(1);
    FbSparseMat.parenReference(FbmatDiagInds, r);
    r.full(b_S);
    Fbdiags.set_size(cend, 1);
    for (int idx{0}; idx < cend; idx++) {
      Fbdiags[idx] = b_S[idx];
    }
    // Get the diag elements. Transpose needed for size considerations for code
    // generation.
  }
  // Time Blinder (Tb) matrix definitions:
  coder::internal::assertValidSizeArg(static_cast<double>(Tbnumrows_tmp));
  coder::internal::assertValidSizeArg(static_cast<double>(Tbnumrows_tmp));
  coder::sparse::eyeLike(Tbnumrows_tmp, Tbnumrows_tmp, Tbnumrows_tmp, b_y);
  b_y.logical(TbSparseMat);
  // Prototype Fb matrix with identity logical matrix
  if (Tbnumrows_tmp < 1) {
    FbmatDiagInds.set_size(1, 0);
    c_y.set_size(1, 0);
  } else {
    FbmatDiagInds.set_size(1, Tbnumrows_tmp);
    loop_ub_tmp = Tbnumrows_tmp - 1;
    c_y.set_size(1, Tbnumrows_tmp);
    for (int idx{0}; idx <= loop_ub_tmp; idx++) {
      FbmatDiagInds[idx] = static_cast<double>(idx) + 1.0;
      c_y[idx] = static_cast<double>(idx) + 1.0;
    }
  }
  b_Fbnumrows_tmp[0] = Tbnumrows_tmp;
  b_Fbnumrows_tmp[1] = Tbnumrows_tmp;
  coder::internal::sub2ind(b_Fbnumrows_tmp, FbmatDiagInds, c_y, r1);
  FbmatDiagInds.set_size(1, r1.size(1));
  maxdimlen = r1.size(1);
  for (int idx{0}; idx < maxdimlen; idx++) {
    FbmatDiagInds[idx] = r1[idx];
  }
  if (minval_tmp == 1) {
    coder::i_sparse(Tb, r2);
    r2.logical(Tbdiags);
    coder::internal::assertValidSizeArg(static_cast<double>(Tbnumrows_tmp));
    coder::sparse::eyeLike(Tbnumrows_tmp, Tbnumrows_tmp, Tbnumrows_tmp, b_y);
    b_y.logical(TbSparseMat);
    TbSparseMat.c_parenAssign(Tbdiags, FbmatDiagInds);
  } else {
    c_y.set_size(1, FbmatDiagInds.size(1));
    maxdimlen = FbmatDiagInds.size(1);
    for (int idx{0}; idx < maxdimlen; idx++) {
      a = static_cast<int>(FbmatDiagInds[idx]);
      if ((a < 1) || (a > Tb.size(0))) {
        rtDynamicBoundsError(a, 1, Tb.size(0), db_emlrtBCI);
      }
      c_y[idx] = Tb[a - 1];
    }
    TbSparseMat.c_parenAssign(c_y, FbmatDiagInds);
    // Had do do it this way rather than with logical(sparse(Tb)) to get code to
    // work with Tb being either a vector or matrix.
  }
  //  Perform the incoherent summation
  Wq.parenReference(r2);
  coder::sum(r2, firstPulseNum);
  K = 0.0;
  cend = firstPulseNum.colidx[1] - 1;
  a = firstPulseNum.colidx[0];
  if ((firstPulseNum.colidx[0] <= firstPulseNum.colidx[1] - 1) &&
      (firstPulseNum.colidx[1] - 1 > 2147483646)) {
    coder::check_forloop_overflow_error();
  }
  for (int idx{a}; idx <= cend; idx++) {
    K = firstPulseNum.d[0];
  }
  if (S.size(0) != Wfherm.size(1)) {
    if (((Wfherm.size(0) == 1) && (Wfherm.size(1) == 1)) ||
        ((S.size(0) == 1) && (S.size(1) == 1))) {
      dc_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
    } else {
      tb_rtErrorWithMessageID(lc_emlrtRTEI.fName, lc_emlrtRTEI.lineNo);
    }
  }
  coder::internal::blas::mtimes(Wfherm, S, d_y);
  cend = d_y.size(0) * d_y.size(1);
  Srows.set_size(d_y.size(0), d_y.size(1));
  if (cend > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  for (maxdimlen = 0; maxdimlen < cend; maxdimlen++) {
    Srows[maxdimlen] = rt_hypotd_snf(d_y[maxdimlen].re, d_y[maxdimlen].im);
  }
  Sinds.set_size(Srows.size(0), Srows.size(1));
  maxdimlen = Srows.size(0) * Srows.size(1);
  for (int idx{0}; idx < maxdimlen; idx++) {
    varargin_1 = Srows[idx];
    Sinds[idx] = varargin_1 * varargin_1;
  }
  IR.mtimes(Sinds, allScores);
  FbSparseMat.mtimes(allScores, Srows);
  TbSparseMat.b_mtimes(Srows, Sinds);
  Wq.mtimes(Sinds, Srows);
  coder::internal::maximum(Srows, ex, b_idx);
  // Check max on each row (frequency). This gives the columns of the resulting
  // matrix output with the max for each frequency bin This and the next line
  // gets the column numbers (time windows) of the S matrix where the highest
  // K-summed entries exist for each row (frequency bin)
  ex.set_size(b_idx.size(0));
  maxdimlen = b_idx.size(0);
  for (int idx{0}; idx < maxdimlen; idx++) {
    ex[idx] = b_idx[idx];
  }
  Wq.parenReference(ex, b_y);
  coder::e_eml_find(b_y, b_idx, jj);
  ex.set_size(b_idx.size(0));
  maxdimlen = b_idx.size(0);
  for (int idx{0}; idx < maxdimlen; idx++) {
    ex[idx] = b_idx[idx];
  }
  // Get the rows that had 1s in them that corresponded to the winning columns
  varargin_1 = static_cast<double>(ex.size(0)) / K;
  coder::internal::assertValidSizeArg(K);
  coder::internal::assertValidSizeArg(varargin_1);
  maxdimlen = ex.size(0);
  if (ex.size(0) < 1) {
    maxdimlen = 1;
  }
  cend = ex.size(0);
  if (cend >= maxdimlen) {
    maxdimlen = cend;
  }
  if (static_cast<int>(K) > maxdimlen) {
    k_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }
  if (static_cast<int>(varargin_1) > maxdimlen) {
    k_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }
  if (static_cast<int>(varargin_1) < 0) {
    jb_rtErrorWithMessageID(yb_emlrtRTEI.fName, yb_emlrtRTEI.lineNo);
  }
  if (static_cast<int>(K) * static_cast<int>(varargin_1) != ex.size(0)) {
    l_rtErrorWithMessageID(o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
  }
  cend = static_cast<int>(K);
  maxdimlen = static_cast<int>(varargin_1);
  Scols.set_size(static_cast<int>(varargin_1), static_cast<int>(K));
  for (int idx{0}; idx < cend; idx++) {
    for (a = 0; a < maxdimlen; a++) {
      Scols[a + Scols.size(0) * idx] = ex[idx + static_cast<int>(K) * a];
    }
  }
  if (Wfherm.size(0) < 1) {
    FbmatDiagInds.set_size(1, 0);
  } else {
    FbmatDiagInds.set_size(1, Wfherm.size(0));
    maxdimlen = Wfherm.size(0) - 1;
    for (int idx{0}; idx <= maxdimlen; idx++) {
      FbmatDiagInds[idx] = static_cast<double>(idx) + 1.0;
    }
  }
  ex.set_size(FbmatDiagInds.size(1));
  maxdimlen = FbmatDiagInds.size(1);
  for (int idx{0}; idx < maxdimlen; idx++) {
    ex[idx] = FbmatDiagInds[idx];
  }
  coder::repmat(ex, K, Srows);
  b_Fbnumrows_tmp[0] = (*(int(*)[2])allScores.size())[0];
  b_Fbnumrows_tmp[1] = (*(int(*)[2])allScores.size())[1];
  coder::internal::b_sub2ind(b_Fbnumrows_tmp, Srows, Scols, r3);
  Sinds.set_size(r3.size(0), r3.size(1));
  loop_ub_tmp = r3.size(0) * r3.size(1);
  for (int idx{0}; idx < loop_ub_tmp; idx++) {
    Sinds[idx] = r3[idx];
  }
  int iv[2];
  b_Fbnumrows_tmp[0] = (*(int(*)[2])allScores.size())[0];
  b_Fbnumrows_tmp[1] = (*(int(*)[2])allScores.size())[1];
  iv[0] = (*(int(*)[2])Sinds.size())[0];
  iv[1] = (*(int(*)[2])Sinds.size())[1];
  coder::internal::indexShapeCheck(b_Fbnumrows_tmp, iv);
  Sscores.set_size(Sinds.size(0), Sinds.size(1));
  cend = allScores.size(0) * allScores.size(1);
  for (int idx{0}; idx < loop_ub_tmp; idx++) {
    a = static_cast<int>(Sinds[idx]);
    if ((a < 1) || (a > cend)) {
      rtDynamicBoundsError(a, 1, cend, cb_emlrtBCI);
    }
    Sscores[idx] = allScores[a - 1];
  }
  // Extract individual pulse scores
  // The max function will just return the first index if all elements are
  // equal. Here we zero out the scores and set the cols to NaN for frequencies
  // were ignored with the frequency blinder matrix.
  maxdimlen = Fbdiags.size(0) - 1;
  cend = 0;
  for (a = 0; a <= maxdimlen; a++) {
    if (!Fbdiags[a]) {
      cend++;
    }
  }
  r4.set_size(cend);
  cend = 0;
  for (a = 0; a <= maxdimlen; a++) {
    if (!Fbdiags[a]) {
      r4[cend] = a;
      cend++;
    }
  }
  maxdimlen = Sinds.size(1);
  for (int idx{0}; idx < maxdimlen; idx++) {
    cend = r4.size(0);
    for (a = 0; a < cend; a++) {
      if (r4[a] > Sinds.size(0) - 1) {
        rtDynamicBoundsError(r4[a], 0, Sinds.size(0) - 1, bb_emlrtBCI);
      }
      Sscores[r4[a] + Sscores.size(0) * idx] = rtNaN;
    }
  }
  maxdimlen = Scols.size(1);
  for (int idx{0}; idx < maxdimlen; idx++) {
    cend = r4.size(0);
    for (a = 0; a < cend; a++) {
      if (r4[a] > Scols.size(0) - 1) {
        rtDynamicBoundsError(r4[a], 0, Scols.size(0) - 1, ab_emlrtBCI);
      }
      Scols[r4[a] + Scols.size(0) * idx] = rtNaN;
    }
  }
}

//
// File trailer for incohsumtoeplitz.cpp
//
// [EOF]
//
