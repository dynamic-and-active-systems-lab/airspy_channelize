//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: str2matrix.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "str2matrix.h"
#include "find.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "str2double.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"

// Function Definitions
//
// STR2MATRIX Converts a string containing a matrix in Matlab notation to a
// numeric array. Arrays must be no greater than two dimensions. Hard
// brackets should enclose the array, with semicolons separating rows.
// Columns can be separated by white space or commas. All rows must have the
// same number of columns. Note that str2num would produce similar results to
// this function, but is not supported for code generation.
//
// INPUTS:
//    inputStr    A string containing a matrix. Ex: '[2 3; 5, 6 ;7 ,8 ]'
// OUTPUS:
//    outMat      A numeric array of the input matrix.
//
//
// Author:    Michael W. Shafer
// Date:      2022-02-15
// --------------------------------------------------------------------------
//
// Arguments    : coder::array<char, 2U> &inputStr
//                coder::array<creal_T, 2U> &outMat
// Return Type  : void
//
void str2matrix(coder::array<char, 2U> &inputStr,
                coder::array<creal_T, 2U> &outMat)
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      -1,               // iFirst
      -1,               // iLast
      91,               // lineNo
      28,               // colNo
      "rowDividerLocs", // aName
      "str2matrix",     // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      -1,           // iFirst
      -1,           // iLast
      26,           // lineNo
      49,           // colNo
      "inputStr",   // aName
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      -1,           // iFirst
      -1,           // iLast
      26,           // lineNo
      25,           // colNo
      "inputStr",   // aName
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      -1,           // iFirst
      -1,           // iLast
      41,           // lineNo
      17,           // colNo
      "inputStr",   // aName
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo eb_emlrtBCI{
      -1,           // iFirst
      -1,           // iLast
      41,           // lineNo
      45,           // colNo
      "inputStr",   // aName
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo fb_emlrtBCI{
      -1,           // iFirst
      -1,           // iLast
      44,           // lineNo
      46,           // colNo
      "inputStr",   // aName
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      -1,           // iFirst
      -1,           // iLast
      47,           // lineNo
      49,           // colNo
      "inputStr",   // aName
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo hb_emlrtBCI{
      -1,           // iFirst
      -1,           // iLast
      62,           // lineNo
      17,           // colNo
      "inputStr",   // aName
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo ib_emlrtBCI{
      -1,           // iFirst
      -1,           // iLast
      62,           // lineNo
      45,           // colNo
      "inputStr",   // aName
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo jb_emlrtBCI{
      -1,           // iFirst
      -1,           // iLast
      65,           // lineNo
      46,           // colNo
      "inputStr",   // aName
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo kb_emlrtBCI{
      -1,           // iFirst
      -1,           // iLast
      68,           // lineNo
      49,           // colNo
      "inputStr",   // aName
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo lb_emlrtBCI{
      -1,           // iFirst
      -1,           // iLast
      76,           // lineNo
      10,           // colNo
      "inputStr",   // aName
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo mb_emlrtBCI{
      -1,               // iFirst
      -1,               // iLast
      92,               // lineNo
      28,               // colNo
      "rowDividerLocs", // aName
      "str2matrix",     // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo nb_emlrtBCI{
      -1,           // iFirst
      -1,           // iLast
      93,           // lineNo
      28,           // colNo
      "commaLocs",  // aName
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo ob_emlrtBCI{
      -1,               // iFirst
      -1,               // iLast
      100,              // lineNo
      32,               // colNo
      "rowDividerLocs", // aName
      "str2matrix",     // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo pb_emlrtBCI{
      -1,               // iFirst
      -1,               // iLast
      101,              // lineNo
      32,               // colNo
      "rowDividerLocs", // aName
      "str2matrix",     // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo qb_emlrtBCI{
      -1,           // iFirst
      -1,           // iLast
      102,          // lineNo
      32,           // colNo
      "commaLocs",  // aName
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo rb_emlrtBCI{
      -1,               // iFirst
      -1,               // iLast
      114,              // lineNo
      54,               // colNo
      "colDividerLocs", // aName
      "str2matrix",     // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo sb_emlrtBCI{
      -1,               // iFirst
      -1,               // iLast
      114,              // lineNo
      74,               // colNo
      "colDividerLocs", // aName
      "str2matrix",     // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo tb_emlrtBCI{
      -1,           // iFirst
      -1,           // iLast
      115,          // lineNo
      17,           // colNo
      "tempRow",    // aName
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo ub_emlrtBCI{
      -1,           // iFirst
      -1,           // iLast
      114,          // lineNo
      39,           // colNo
      "inputStr",   // aName
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo vb_emlrtBCI{
      -1,           // iFirst
      -1,           // iLast
      114,          // lineNo
      59,           // colNo
      "inputStr",   // aName
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo wb_emlrtBCI{
      -1,           // iFirst
      -1,           // iLast
      117,          // lineNo
      12,           // colNo
      "outMat",     // aName
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      0                                               // checkKind
  };
  static rtDoubleCheckInfo s_emlrtDCI{
      96,           // lineNo
      24,           // colNo
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      4                                               // checkKind
  };
  static rtDoubleCheckInfo t_emlrtDCI{
      96,           // lineNo
      34,           // colNo
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      1                                               // checkKind
  };
  static rtDoubleCheckInfo u_emlrtDCI{
      96,           // lineNo
      1,            // colNo
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      1                                               // checkKind
  };
  static rtDoubleCheckInfo v_emlrtDCI{
      111,          // lineNo
      31,           // colNo
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      1                                               // checkKind
  };
  static rtDoubleCheckInfo w_emlrtDCI{
      111,          // lineNo
      5,            // colNo
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m", // pName
      1                                               // checkKind
  };
  static rtEqualityCheckInfo g_emlrtECI{
      2,            // nDims
      102,          // lineNo
      32,           // colNo
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m" // pName
  };
  static rtEqualityCheckInfo h_emlrtECI{
      -1,           // nDims
      117,          // lineNo
      5,            // colNo
      "str2matrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/str2matrix.m" // pName
  };
  coder::array<creal_T, 2U> tempRow;
  coder::array<double, 2U> rightBracketLoc;
  coder::array<double, 2U> rowDividerLocs;
  coder::array<int, 2U> ii;
  coder::array<int, 2U> leftBracketLoc;
  coder::array<int, 2U> r;
  coder::array<int, 2U> r1;
  coder::array<char, 2U> c_inputStr;
  coder::array<boolean_T, 2U> b_inputStr;
  int iv[2];
  int iv1[2];
  int b_i;
  int b_leftBracketLoc;
  int end;
  unsigned int i;
  int j2;
  int nd2;
  char xtmp;
  boolean_T b;
  boolean_T done;
  boolean_T guard1;
  boolean_T guard2;
  // Strip redundant white space
  done = false;
  i = 1U;
  while (!done) {
    done = (i + 1U == static_cast<unsigned int>(inputStr.size(1)));
    if ((static_cast<int>(i) < 1) || (static_cast<int>(i) > inputStr.size(1))) {
      rtDynamicBoundsError(static_cast<int>(i), 1, inputStr.size(1),
                           cb_emlrtBCI);
    }
    b_i = static_cast<unsigned char>(inputStr[static_cast<int>(i) - 1]);
    if (b_i > 127) {
      tc_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
    }
    if (bv[b_i]) {
      if ((static_cast<int>(static_cast<double>(i) + 1.0) < 1) ||
          (static_cast<int>(static_cast<double>(i) + 1.0) > inputStr.size(1))) {
        rtDynamicBoundsError(static_cast<int>(static_cast<double>(i) + 1.0), 1,
                             inputStr.size(1), bb_emlrtBCI);
      }
      b_i = static_cast<unsigned char>(inputStr[static_cast<int>(i)]);
      if (b_i > 127) {
        tc_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
      }
      if (bv[b_i]) {
        // inputStr(i+1) = '';
        // inputStr = inputStr(1:numel(inputStr) ~= i+1);
        nd2 = static_cast<int>(i) + 1;
        if (static_cast<int>(i) + 1 > inputStr.size(1)) {
          j_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
        }
        j2 = inputStr.size(1) - 1;
        for (int b_j1{nd2}; b_j1 <= j2; b_j1++) {
          inputStr[b_j1 - 1] = inputStr[b_j1];
        }
        if (inputStr.size(1) - 1 < 1) {
          b_i = 0;
        } else {
          b_i = inputStr.size(1) - 1;
        }
        inputStr.set_size(inputStr.size(0), b_i);
        i = static_cast<unsigned int>(static_cast<int>(i) - 1);
      }
    }
    i++;
  }
  // Strip out white space after [ ; and , characters
  done = false;
  i = 1U;
  while (!done) {
    done = (i + 1U == static_cast<unsigned int>(inputStr.size(1)));
    b = ((static_cast<int>(i) < 1) || (static_cast<int>(i) > inputStr.size(1)));
    if (b) {
      rtDynamicBoundsError(static_cast<int>(i), 1, inputStr.size(1),
                           db_emlrtBCI);
    }
    xtmp = inputStr[static_cast<int>(i) - 1];
    guard1 = false;
    guard2 = false;
    if (xtmp == '[') {
      if ((static_cast<int>(static_cast<double>(i) + 1.0) < 1) ||
          (static_cast<int>(static_cast<double>(i) + 1.0) > inputStr.size(1))) {
        rtDynamicBoundsError(static_cast<int>(static_cast<double>(i) + 1.0), 1,
                             inputStr.size(1), eb_emlrtBCI);
      }
      b_i = static_cast<unsigned char>(inputStr[static_cast<int>(i)]);
      if (b_i > 127) {
        tc_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
      }
      if (bv[b_i]) {
        nd2 = static_cast<int>(i) + 1;
        if (static_cast<int>(i) + 1 > inputStr.size(1)) {
          j_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
        }
        j2 = inputStr.size(1) - 1;
        for (int b_j1{nd2}; b_j1 <= j2; b_j1++) {
          inputStr[b_j1 - 1] = inputStr[b_j1];
        }
        if (inputStr.size(1) - 1 < 1) {
          b_i = 0;
        } else {
          b_i = inputStr.size(1) - 1;
        }
        inputStr.set_size(inputStr.size(0), b_i);
        i = static_cast<unsigned int>(static_cast<int>(i) - 1);
      } else {
        guard2 = true;
      }
    } else {
      guard2 = true;
    }
    if (guard2) {
      if (xtmp == ',') {
        if ((static_cast<int>(static_cast<double>(i) + 1.0) < 1) ||
            (static_cast<int>(static_cast<double>(i) + 1.0) >
             inputStr.size(1))) {
          rtDynamicBoundsError(static_cast<int>(static_cast<double>(i) + 1.0),
                               1, inputStr.size(1), fb_emlrtBCI);
        }
        b_i = static_cast<unsigned char>(inputStr[static_cast<int>(i)]);
        if (b_i > 127) {
          tc_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
        }
        if (bv[b_i]) {
          nd2 = static_cast<int>(i) + 1;
          if (static_cast<int>(i) + 1 > inputStr.size(1)) {
            j_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
          }
          j2 = inputStr.size(1) - 1;
          for (int b_j1{nd2}; b_j1 <= j2; b_j1++) {
            inputStr[b_j1 - 1] = inputStr[b_j1];
          }
          if (inputStr.size(1) - 1 < 1) {
            b_i = 0;
          } else {
            b_i = inputStr.size(1) - 1;
          }
          inputStr.set_size(inputStr.size(0), b_i);
          i = static_cast<unsigned int>(static_cast<int>(i) - 1);
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
    }
    if (guard1 && (xtmp == ';')) {
      if ((static_cast<int>(static_cast<double>(i) + 1.0) < 1) ||
          (static_cast<int>(static_cast<double>(i) + 1.0) > inputStr.size(1))) {
        rtDynamicBoundsError(static_cast<int>(static_cast<double>(i) + 1.0), 1,
                             inputStr.size(1), gb_emlrtBCI);
      }
      b_i = static_cast<unsigned char>(inputStr[static_cast<int>(i)]);
      if (b_i > 127) {
        tc_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
      }
      if (bv[b_i]) {
        nd2 = static_cast<int>(i) + 1;
        if (static_cast<int>(i) + 1 > inputStr.size(1)) {
          j_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
        }
        j2 = inputStr.size(1) - 1;
        for (int b_j1{nd2}; b_j1 <= j2; b_j1++) {
          inputStr[b_j1 - 1] = inputStr[b_j1];
        }
        if (inputStr.size(1) - 1 < 1) {
          b_i = 0;
        } else {
          b_i = inputStr.size(1) - 1;
        }
        inputStr.set_size(inputStr.size(0), b_i);
        i = static_cast<unsigned int>(static_cast<int>(i) - 1);
      }
    }
    i++;
  }
  // Strip out white space before [ ; and , characters
  nd2 = inputStr.size(1) >> 1;
  for (int b_j1{0}; b_j1 < nd2; b_j1++) {
    j2 = (inputStr.size(1) - b_j1) - 1;
    xtmp = inputStr[b_j1];
    inputStr[b_j1] = inputStr[j2];
    inputStr[j2] = xtmp;
  }
  done = false;
  i = 1U;
  while (!done) {
    done = (i + 1U == static_cast<unsigned int>(inputStr.size(1)));
    b = ((static_cast<int>(i) < 1) || (static_cast<int>(i) > inputStr.size(1)));
    if (b) {
      rtDynamicBoundsError(static_cast<int>(i), 1, inputStr.size(1),
                           hb_emlrtBCI);
    }
    xtmp = inputStr[static_cast<int>(i) - 1];
    guard1 = false;
    guard2 = false;
    if (xtmp == '[') {
      if ((static_cast<int>(static_cast<double>(i) + 1.0) < 1) ||
          (static_cast<int>(static_cast<double>(i) + 1.0) > inputStr.size(1))) {
        rtDynamicBoundsError(static_cast<int>(static_cast<double>(i) + 1.0), 1,
                             inputStr.size(1), ib_emlrtBCI);
      }
      b_i = static_cast<unsigned char>(inputStr[static_cast<int>(i)]);
      if (b_i > 127) {
        tc_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
      }
      if (bv[b_i]) {
        nd2 = static_cast<int>(i) + 1;
        if (static_cast<int>(i) + 1 > inputStr.size(1)) {
          j_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
        }
        j2 = inputStr.size(1) - 1;
        for (int b_j1{nd2}; b_j1 <= j2; b_j1++) {
          inputStr[b_j1 - 1] = inputStr[b_j1];
        }
        if (inputStr.size(1) - 1 < 1) {
          b_i = 0;
        } else {
          b_i = inputStr.size(1) - 1;
        }
        inputStr.set_size(inputStr.size(0), b_i);
        i = static_cast<unsigned int>(static_cast<int>(i) - 1);
      } else {
        guard2 = true;
      }
    } else {
      guard2 = true;
    }
    if (guard2) {
      if (xtmp == ',') {
        if ((static_cast<int>(static_cast<double>(i) + 1.0) < 1) ||
            (static_cast<int>(static_cast<double>(i) + 1.0) >
             inputStr.size(1))) {
          rtDynamicBoundsError(static_cast<int>(static_cast<double>(i) + 1.0),
                               1, inputStr.size(1), jb_emlrtBCI);
        }
        b_i = static_cast<unsigned char>(inputStr[static_cast<int>(i)]);
        if (b_i > 127) {
          tc_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
        }
        if (bv[b_i]) {
          nd2 = static_cast<int>(i) + 1;
          if (static_cast<int>(i) + 1 > inputStr.size(1)) {
            j_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
          }
          j2 = inputStr.size(1) - 1;
          for (int b_j1{nd2}; b_j1 <= j2; b_j1++) {
            inputStr[b_j1 - 1] = inputStr[b_j1];
          }
          if (inputStr.size(1) - 1 < 1) {
            b_i = 0;
          } else {
            b_i = inputStr.size(1) - 1;
          }
          inputStr.set_size(inputStr.size(0), b_i);
          i = static_cast<unsigned int>(static_cast<int>(i) - 1);
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
    }
    if (guard1 && (xtmp == ';')) {
      if ((static_cast<int>(static_cast<double>(i) + 1.0) < 1) ||
          (static_cast<int>(static_cast<double>(i) + 1.0) > inputStr.size(1))) {
        rtDynamicBoundsError(static_cast<int>(static_cast<double>(i) + 1.0), 1,
                             inputStr.size(1), kb_emlrtBCI);
      }
      b_i = static_cast<unsigned char>(inputStr[static_cast<int>(i)]);
      if (b_i > 127) {
        tc_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
      }
      if (bv[b_i]) {
        nd2 = static_cast<int>(i) + 1;
        if (static_cast<int>(i) + 1 > inputStr.size(1)) {
          j_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
        }
        j2 = inputStr.size(1) - 1;
        for (int b_j1{nd2}; b_j1 <= j2; b_j1++) {
          inputStr[b_j1 - 1] = inputStr[b_j1];
        }
        if (inputStr.size(1) - 1 < 1) {
          b_i = 0;
        } else {
          b_i = inputStr.size(1) - 1;
        }
        inputStr.set_size(inputStr.size(0), b_i);
        i = static_cast<unsigned int>(static_cast<int>(i) - 1);
      }
    }
    i++;
  }
  nd2 = inputStr.size(1) >> 1;
  for (int b_j1{0}; b_j1 < nd2; b_j1++) {
    j2 = (inputStr.size(1) - b_j1) - 1;
    xtmp = inputStr[b_j1];
    inputStr[b_j1] = inputStr[j2];
    inputStr[j2] = xtmp;
  }
  // Replace space with commas for marking columns
  nd2 = inputStr.size(1) - 1;
  for (int c_i{0}; c_i <= nd2; c_i++) {
    if (inputStr[c_i] == ' ') {
      if (c_i > nd2) {
        rtDynamicBoundsError(c_i, 0, nd2, lb_emlrtBCI);
      }
      inputStr[c_i] = ',';
    }
  }
  b_inputStr.set_size(1, inputStr.size(1));
  j2 = inputStr.size(1);
  for (b_i = 0; b_i < j2; b_i++) {
    b_inputStr[b_i] = (inputStr[b_i] == '[');
  }
  coder::b_eml_find(b_inputStr, ii);
  leftBracketLoc.set_size(1, ii.size(1));
  j2 = ii.size(1);
  for (b_i = 0; b_i < j2; b_i++) {
    leftBracketLoc[b_i] = ii[b_i];
  }
  b_inputStr.set_size(1, inputStr.size(1));
  j2 = inputStr.size(1);
  for (b_i = 0; b_i < j2; b_i++) {
    b_inputStr[b_i] = (inputStr[b_i] == ']');
  }
  coder::b_eml_find(b_inputStr, ii);
  rightBracketLoc.set_size(1, ii.size(1));
  j2 = ii.size(1);
  for (b_i = 0; b_i < j2; b_i++) {
    rightBracketLoc[b_i] = ii[b_i];
  }
  if ((leftBracketLoc.size(1) != 1) || (rightBracketLoc.size(1) != 1)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  b_inputStr.set_size(1, inputStr.size(1));
  j2 = inputStr.size(1);
  for (b_i = 0; b_i < j2; b_i++) {
    b_inputStr[b_i] = (inputStr[b_i] == ';');
  }
  coder::b_eml_find(b_inputStr, ii);
  rowDividerLocs.set_size(1, ii.size(1) + 2);
  rowDividerLocs[0] = leftBracketLoc[0];
  j2 = ii.size(1);
  for (b_i = 0; b_i < j2; b_i++) {
    rowDividerLocs[b_i + 1] = ii[b_i];
  }
  rowDividerLocs[ii.size(1) + 1] = rightBracketLoc[0];
  coder::internal::sort(rowDividerLocs);
  b_inputStr.set_size(1, inputStr.size(1));
  j2 = inputStr.size(1);
  for (b_i = 0; b_i < j2; b_i++) {
    b_inputStr[b_i] = (inputStr[b_i] == ',');
  }
  coder::b_eml_find(b_inputStr, ii);
  leftBracketLoc.set_size(1, ii.size(1));
  j2 = ii.size(1);
  for (b_i = 0; b_i < j2; b_i++) {
    leftBracketLoc[b_i] = ii[b_i];
  }
  // Check for the number of columns in the first row to preallocate outMat
  if (rowDividerLocs.size(1) < 1) {
    rtDynamicBoundsError(1, 1, rowDividerLocs.size(1), ab_emlrtBCI);
  }
  if (rowDividerLocs.size(1) < 2) {
    rtDynamicBoundsError(2, 1, rowDividerLocs.size(1), mb_emlrtBCI);
  }
  iv1[0] = 1;
  iv1[1] = leftBracketLoc.size(1);
  nd2 = leftBracketLoc.size(1) - 1;
  j2 = 0;
  for (int c_i{0}; c_i <= nd2; c_i++) {
    b_i = leftBracketLoc[c_i];
    if ((b_i > rowDividerLocs[0]) && (b_i < rowDividerLocs[1])) {
      j2++;
    }
  }
  r.set_size(1, j2);
  j2 = 0;
  for (int c_i{0}; c_i <= nd2; c_i++) {
    b_i = leftBracketLoc[c_i];
    if ((b_i > rowDividerLocs[0]) && (b_i < rowDividerLocs[1])) {
      r[j2] = c_i;
      j2++;
    }
  }
  j2 = r.size(1);
  for (b_i = 0; b_i < j2; b_i++) {
    if (r[b_i] > nd2) {
      rtDynamicBoundsError(r[b_i], 0, nd2, nb_emlrtBCI);
    }
  }
  b = (rowDividerLocs.size(1) - 1 < 0);
  if (b) {
    rtNonNegativeError(-1.0, s_emlrtDCI);
  }
  outMat.set_size(rowDividerLocs.size(1) - 1, outMat.size(1));
  if (static_cast<double>(r.size(1)) + 1.0 != r.size(1) + 1) {
    rtIntegerError(static_cast<double>(r.size(1)) + 1.0, t_emlrtDCI);
  }
  outMat.set_size(outMat.size(0), r.size(1) + 1);
  if (static_cast<double>(r.size(1)) + 1.0 != r.size(1) + 1) {
    rtIntegerError(static_cast<double>(r.size(1)) + 1.0, u_emlrtDCI);
  }
  j2 = (rowDividerLocs.size(1) - 1) * (r.size(1) + 1);
  for (b_i = 0; b_i < j2; b_i++) {
    outMat[b_i].re = 0.0;
    outMat[b_i].im = 0.0;
  }
  nd2 = 0;
  b_i = rowDividerLocs.size(1);
  if (rowDividerLocs.size(1) - 2 >= 0) {
    iv1[0] = 1;
    iv1[1] = leftBracketLoc.size(1);
    end = leftBracketLoc.size(1) - 1;
    b_leftBracketLoc = leftBracketLoc.size(1);
  }
  for (int c_i{0}; c_i <= b_i - 2; c_i++) {
    int i1;
    if (c_i + 1 > rowDividerLocs.size(1)) {
      rtDynamicBoundsError(c_i + 1, 1, rowDividerLocs.size(1), ob_emlrtBCI);
    }
    if (c_i + 2 > rowDividerLocs.size(1)) {
      rtDynamicBoundsError(c_i + 2, 1, rowDividerLocs.size(1), pb_emlrtBCI);
    }
    iv[0] = 1;
    iv[1] = leftBracketLoc.size(1);
    if (leftBracketLoc.size(1) != iv1[1]) {
      rtSizeEqNDCheck(&iv[0], &iv1[0], g_emlrtECI);
    }
    j2 = 0;
    for (int b_j1{0}; b_j1 <= end; b_j1++) {
      i1 = leftBracketLoc[b_j1];
      if ((i1 > rowDividerLocs[c_i]) && (i1 < rowDividerLocs[c_i + 1])) {
        j2++;
      }
    }
    r1.set_size(1, j2);
    j2 = 0;
    for (int b_j1{0}; b_j1 <= end; b_j1++) {
      i1 = leftBracketLoc[b_j1];
      if ((i1 > rowDividerLocs[c_i]) && (i1 < rowDividerLocs[c_i + 1])) {
        r1[j2] = b_j1;
        j2++;
      }
    }
    j2 = r1.size(1);
    for (i1 = 0; i1 < j2; i1++) {
      if ((r1[i1] < 0) || (r1[i1] > b_leftBracketLoc - 1)) {
        rtDynamicBoundsError(r1[i1], 0, b_leftBracketLoc - 1, qb_emlrtBCI);
      }
    }
    if ((c_i + 1 > 1) && (r1.size(1) != nd2)) {
      rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
    }
    j2 = r1.size(1);
    rightBracketLoc.set_size(1, r1.size(1) + 2);
    rightBracketLoc[0] = rowDividerLocs[c_i];
    for (i1 = 0; i1 < j2; i1++) {
      rightBracketLoc[i1 + 1] = leftBracketLoc[r1[i1]];
    }
    rightBracketLoc[r1.size(1) + 1] = rowDividerLocs[c_i + 1];
    tempRow.set_size(1, tempRow.size(1));
    if (static_cast<double>(r1.size(1)) + 1.0 != r1.size(1) + 1) {
      rtIntegerError(static_cast<double>(r1.size(1)) + 1.0, v_emlrtDCI);
    }
    j2 = r1.size(1) + 1;
    tempRow.set_size(tempRow.size(0), r1.size(1) + 1);
    if (static_cast<double>(r1.size(1)) + 1.0 != r1.size(1) + 1) {
      rtIntegerError(static_cast<double>(r1.size(1)) + 1.0, w_emlrtDCI);
    }
    for (i1 = 0; i1 < j2; i1++) {
      tempRow[i1].re = 0.0;
      tempRow[i1].im = 0.0;
    }
    i1 = rightBracketLoc.size(1);
    for (int b_j1{0}; b_j1 <= i1 - 2; b_j1++) {
      double d;
      int i2;
      if (b_j1 + 1 > rightBracketLoc.size(1)) {
        rtDynamicBoundsError(b_j1 + 1, 1, rightBracketLoc.size(1), rb_emlrtBCI);
      }
      if (b_j1 + 2 > rightBracketLoc.size(1)) {
        rtDynamicBoundsError(b_j1 + 2, 1, rightBracketLoc.size(1), sb_emlrtBCI);
      }
      d = rightBracketLoc[b_j1 + 1] - 1.0;
      if (rightBracketLoc[b_j1] + 1.0 > d) {
        nd2 = 0;
        i2 = 0;
      } else {
        nd2 = static_cast<int>(rightBracketLoc[b_j1] + 1.0);
        if ((nd2 < 1) || (nd2 > inputStr.size(1))) {
          rtDynamicBoundsError(nd2, 1, inputStr.size(1), ub_emlrtBCI);
        }
        nd2--;
        if ((static_cast<int>(d) < 1) ||
            (static_cast<int>(d) > inputStr.size(1))) {
          rtDynamicBoundsError(static_cast<int>(d), 1, inputStr.size(1),
                               vb_emlrtBCI);
        }
        i2 = static_cast<int>(d);
      }
      j2 = i2 - nd2;
      c_inputStr.set_size(1, j2);
      for (i2 = 0; i2 < j2; i2++) {
        c_inputStr[i2] = inputStr[nd2 + i2];
      }
      if (b_j1 + 1 > tempRow.size(1)) {
        rtDynamicBoundsError(b_j1 + 1, 1, tempRow.size(1), tb_emlrtBCI);
      }
      tempRow[b_j1] = coder::internal::str2double(c_inputStr);
    }
    if (c_i + 1 > outMat.size(0)) {
      rtDynamicBoundsError(c_i + 1, 1, outMat.size(0), wb_emlrtBCI);
    }
    iv[0] = 1;
    iv[1] = outMat.size(1);
    rtSubAssignSizeCheck(&iv[0], 2, tempRow.size(), 2, h_emlrtECI);
    j2 = tempRow.size(1);
    for (i1 = 0; i1 < j2; i1++) {
      outMat[c_i + outMat.size(0) * i1] = tempRow[i1];
    }
    nd2 = r1.size(1);
  }
}

//
// File trailer for str2matrix.cpp
//
// [EOF]
//
