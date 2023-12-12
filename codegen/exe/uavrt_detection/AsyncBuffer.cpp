//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBuffer.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "colon.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo q_emlrtRTEI{
    1,                    // lineNo
    1,                    // colNo
    "SystemCore/release", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/shared/system/coder/+matlab/"
    "+system/+coder/SystemCore.p" // pName
};

static rtRunTimeErrorInfo r_emlrtRTEI{
    101,                                      // lineNo
    13,                                       // colNo
    "AsyncBuffercgHelper/validateInputsImpl", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/dsp/dsp/+dsp/+internal/"
    "AsyncBuffercgHelper.m" // pName
};

static rtRunTimeErrorInfo s_emlrtRTEI{
    103,                  // lineNo
    17,                   // colNo
    "AsyncBuffercg/read", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/dsp/dsp/+dsp/+internal/"
    "AsyncBuffercg.m" // pName
};

static rtRunTimeErrorInfo qb_emlrtRTEI{
    1,                  // lineNo
    1,                  // colNo
    "SystemCore/reset", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/shared/system/coder/+matlab/"
    "+system/+coder/SystemCore.p" // pName
};

static rtRunTimeErrorInfo rb_emlrtRTEI{
    1,                 // lineNo
    1,                 // colNo
    "SystemCore/step", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/shared/system/coder/+matlab/"
    "+system/+coder/SystemCore.p" // pName
};

static rtRunTimeErrorInfo sb_emlrtRTEI{
    93,                                       // lineNo
    13,                                       // colNo
    "AsyncBuffercgHelper/validateInputsImpl", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/dsp/dsp/+dsp/+internal/"
    "AsyncBuffercgHelper.m" // pName
};

static rtRunTimeErrorInfo tb_emlrtRTEI{
    1,                  // lineNo
    1,                  // colNo
    "SystemCore/setup", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/shared/system/coder/+matlab/"
    "+system/+coder/SystemCore.p" // pName
};

static rtBoundsCheckInfo s_emlrtBCI{
    1,                           // iFirst
    5800321,                     // iLast
    227,                         // lineNo
    23,                          // colNo
    "",                          // aName
    "AsyncBuffercgHelper/write", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/dsp/dsp/+dsp/+internal/"
    "AsyncBuffercgHelper.m", // pName
    3                        // checkKind
};

static rtRunTimeErrorInfo vb_emlrtRTEI{
    109,                  // lineNo
    17,                   // colNo
    "AsyncBuffercg/read", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/dsp/dsp/+dsp/+internal/"
    "AsyncBuffercg.m" // pName
};

// Function Declarations
static void d_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

static void e_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

static void fb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void ib_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void p_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void q_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace coder {
namespace dsp {
void c_AsyncBuffer::matlabCodegenDestructor()
{
  if (!matlabCodegenIsDeleted) {
    matlabCodegenIsDeleted = true;
  }
}

//
// Arguments    : void
// Return Type  : void
//
void b_AsyncBuffer::matlabCodegenDestructor()
{
  if (!matlabCodegenIsDeleted) {
    matlabCodegenIsDeleted = true;
  }
}

//
// Arguments    : void
// Return Type  : void
//
void AsyncBuffer::matlabCodegenDestructor()
{
  if (!matlabCodegenIsDeleted) {
    matlabCodegenIsDeleted = true;
  }
}

//
// Arguments    : const char *r
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
} // namespace dsp
} // namespace coder
static void d_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "The ") << r)
      << " method cannot be called after calling the release method.";
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
// Arguments    : const char *r
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void e_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "The ") << r)
      << " method cannot be called on an initialized System object or after "
         "calling the release method.";
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
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void fb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Invalid number of input rows. Specify an input with number of "
               "rows less than or equal to the buffer capacity.";
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
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void ib_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Invalid overlap requested. Specify overlap as less than or "
               "equal to the requested number of rows.";
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
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void p_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Changing the number of channels (number of columns) of the "
               "input signal is not supported.";
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
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void q_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Invalid number of rows requested. Specify the number of rows "
               "to read as less than or equal to the buffer capacity.";
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
// Arguments    : void
// Return Type  : c_AsyncBuffer
//
namespace coder {
namespace dsp {
c_AsyncBuffer::c_AsyncBuffer()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : b_AsyncBuffer
//
b_AsyncBuffer::b_AsyncBuffer()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : AsyncBuffer
//
AsyncBuffer::AsyncBuffer()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : void
//
c_AsyncBuffer::~c_AsyncBuffer()
{
  matlabCodegenDestructor();
}

//
// Arguments    : void
// Return Type  : void
//
b_AsyncBuffer::~b_AsyncBuffer()
{
  matlabCodegenDestructor();
}

//
// Arguments    : void
// Return Type  : void
//
AsyncBuffer::~AsyncBuffer()
{
  matlabCodegenDestructor();
}

//
// Arguments    : void
// Return Type  : void
//
void c_AsyncBuffer::read()
{
  array<creal32_T, 1U> out;
  int numRows;
  int q0_tmp;
  int qY;
  q0_tmp = pBuffer.WritePointer;
  numRows = pBuffer.ReadPointer;
  if ((q0_tmp >= 0) && (numRows < q0_tmp - MAX_int32_T)) {
    qY = MAX_int32_T;
  } else if ((q0_tmp < 0) && (numRows > q0_tmp - MIN_int32_T)) {
    qY = MIN_int32_T;
  } else {
    qY = q0_tmp - numRows;
  }
  if (qY < -2147483647) {
    qY = MIN_int32_T;
  } else {
    qY--;
  }
  if (numRows < -2146882997) {
    numRows = MAX_int32_T;
  } else {
    numRows = 600650 - numRows;
  }
  if ((numRows < 0) && (q0_tmp < MIN_int32_T - numRows)) {
    numRows = MIN_int32_T;
  } else if ((numRows > 0) && (q0_tmp > MAX_int32_T - numRows)) {
    numRows = MAX_int32_T;
  } else {
    numRows += q0_tmp;
  }
  if (pBuffer.ReadPointer < pBuffer.WritePointer) {
    numRows = qY;
  } else if (pBuffer.ReadPointer == pBuffer.WritePointer) {
    numRows = 600650;
  }
  if (numRows < 0) {
    f_rtErrorWithMessageID("number of rows", t_emlrtRTEI.fName,
                           t_emlrtRTEI.lineNo);
  }
  if (numRows > 600650) {
    q_rtErrorWithMessageID(s_emlrtRTEI.fName, s_emlrtRTEI.lineNo);
  }
  pBuffer.read(numRows, out);
}

//
// Arguments    : array<creal32_T, 1U> &out
// Return Type  : void
//
void c_AsyncBuffer::read(array<creal32_T, 1U> &out)
{
  int numRows;
  int q0_tmp;
  int qY;
  q0_tmp = pBuffer.WritePointer;
  numRows = pBuffer.ReadPointer;
  if ((q0_tmp >= 0) && (numRows < q0_tmp - MAX_int32_T)) {
    qY = MAX_int32_T;
  } else if ((q0_tmp < 0) && (numRows > q0_tmp - MIN_int32_T)) {
    qY = MIN_int32_T;
  } else {
    qY = q0_tmp - numRows;
  }
  if (qY < -2147483647) {
    qY = MIN_int32_T;
  } else {
    qY--;
  }
  if (numRows < -2146882997) {
    numRows = MAX_int32_T;
  } else {
    numRows = 600650 - numRows;
  }
  if ((numRows < 0) && (q0_tmp < MIN_int32_T - numRows)) {
    numRows = MIN_int32_T;
  } else if ((numRows > 0) && (q0_tmp > MAX_int32_T - numRows)) {
    numRows = MAX_int32_T;
  } else {
    numRows += q0_tmp;
  }
  if (pBuffer.ReadPointer < pBuffer.WritePointer) {
    numRows = qY;
  } else if (pBuffer.ReadPointer == pBuffer.WritePointer) {
    numRows = 600650;
  }
  if (numRows < 0) {
    f_rtErrorWithMessageID("number of rows", t_emlrtRTEI.fName,
                           t_emlrtRTEI.lineNo);
  }
  if (numRows > 600650) {
    q_rtErrorWithMessageID(s_emlrtRTEI.fName, s_emlrtRTEI.lineNo);
  }
  pBuffer.read(numRows, out);
}

//
// Arguments    : double numRows
//                array<creal32_T, 1U> &out
// Return Type  : void
//
void AsyncBuffer::read(double numRows, array<creal32_T, 1U> &out)
{
  if (numRows < 0.0) {
    f_rtErrorWithMessageID("number of rows", t_emlrtRTEI.fName,
                           t_emlrtRTEI.lineNo);
  }
  if (std::isinf(numRows) || std::isnan(numRows)) {
    j_rtErrorWithMessageID("number of rows", bb_emlrtRTEI.fName,
                           bb_emlrtRTEI.lineNo);
  }
  if (!(std::floor(numRows) == numRows)) {
    k_rtErrorWithMessageID("number of rows", fb_emlrtRTEI.fName,
                           fb_emlrtRTEI.lineNo);
  }
  if (numRows > 5.80032E+6) {
    q_rtErrorWithMessageID(s_emlrtRTEI.fName, s_emlrtRTEI.lineNo);
  }
  pBuffer.read(static_cast<int>(numRows), out);
}

//
// Arguments    : double numRows
//                array<double, 1U> &out
// Return Type  : void
//
void b_AsyncBuffer::read(double numRows, array<double, 1U> &out)
{
  if (numRows < 0.0) {
    f_rtErrorWithMessageID("number of rows", t_emlrtRTEI.fName,
                           t_emlrtRTEI.lineNo);
  }
  if (std::isinf(numRows) || std::isnan(numRows)) {
    j_rtErrorWithMessageID("number of rows", bb_emlrtRTEI.fName,
                           bb_emlrtRTEI.lineNo);
  }
  if (!(std::floor(numRows) == numRows)) {
    k_rtErrorWithMessageID("number of rows", fb_emlrtRTEI.fName,
                           fb_emlrtRTEI.lineNo);
  }
  if (numRows > 5.80032E+6) {
    q_rtErrorWithMessageID(s_emlrtRTEI.fName, s_emlrtRTEI.lineNo);
  }
  pBuffer.read(static_cast<int>(numRows), out);
}

//
// Arguments    : double numRows
//                double overlap
//                array<creal32_T, 1U> &out
// Return Type  : void
//
void AsyncBuffer::read(double numRows, double overlap,
                       array<creal32_T, 1U> &out)
{
  array<creal32_T, 1U> b_out;
  int c;
  int overlapUnderrun;
  int underrun;
  if (numRows < 0.0) {
    f_rtErrorWithMessageID("number of rows", t_emlrtRTEI.fName,
                           t_emlrtRTEI.lineNo);
  }
  if (std::isinf(numRows) || std::isnan(numRows)) {
    j_rtErrorWithMessageID("number of rows", bb_emlrtRTEI.fName,
                           bb_emlrtRTEI.lineNo);
  }
  if (!(std::floor(numRows) == numRows)) {
    k_rtErrorWithMessageID("number of rows", fb_emlrtRTEI.fName,
                           fb_emlrtRTEI.lineNo);
  }
  if (numRows > 5.80032E+6) {
    q_rtErrorWithMessageID(s_emlrtRTEI.fName, s_emlrtRTEI.lineNo);
  }
  if (overlap < 0.0) {
    f_rtErrorWithMessageID("overlap", t_emlrtRTEI.fName, t_emlrtRTEI.lineNo);
  }
  if (std::isinf(overlap) || std::isnan(overlap)) {
    j_rtErrorWithMessageID("overlap", bb_emlrtRTEI.fName, bb_emlrtRTEI.lineNo);
  }
  if (!(std::floor(overlap) == overlap)) {
    k_rtErrorWithMessageID("overlap", fb_emlrtRTEI.fName, fb_emlrtRTEI.lineNo);
  }
  if (overlap > numRows) {
    ib_rtErrorWithMessageID(vb_emlrtRTEI.fName, vb_emlrtRTEI.lineNo);
  }
  if (!pBuffer.AsyncBuffercgHelper_isInitialized) {
    r_rtErrorWithMessageID(u_emlrtRTEI.fName, u_emlrtRTEI.lineNo);
  }
  underrun = internal::AsyncBuffercgHelper::ReadSamplesFromBuffer(
      pBuffer, static_cast<int>(numRows), static_cast<int>(overlap), b_out,
      overlapUnderrun, c);
  out.set_size(b_out.size(0));
  overlapUnderrun = b_out.size(0);
  for (int i{0}; i < overlapUnderrun; i++) {
    out[i] = b_out[i];
  }
  overlapUnderrun = pBuffer.CumulativeUnderrun;
  if ((overlapUnderrun < 0) && (underrun < MIN_int32_T - overlapUnderrun)) {
    overlapUnderrun = MIN_int32_T;
  } else if ((overlapUnderrun > 0) &&
             (underrun > MAX_int32_T - overlapUnderrun)) {
    overlapUnderrun = MAX_int32_T;
  } else {
    overlapUnderrun += underrun;
  }
  pBuffer.CumulativeUnderrun = overlapUnderrun;
  overlapUnderrun = pBuffer.WritePointer;
  if (overlapUnderrun < -2147483647) {
    overlapUnderrun = MIN_int32_T;
  } else {
    overlapUnderrun--;
  }
  if (underrun != 0) {
    pBuffer.ReadPointer = overlapUnderrun;
  } else {
    pBuffer.ReadPointer = c;
  }
}

//
// Arguments    : double numRows
//                double overlap
//                array<double, 1U> &out
// Return Type  : void
//
void b_AsyncBuffer::read(double numRows, double overlap, array<double, 1U> &out)
{
  array<double, 1U> b_out;
  int c;
  int overlapUnderrun;
  int underrun;
  if (numRows < 0.0) {
    f_rtErrorWithMessageID("number of rows", t_emlrtRTEI.fName,
                           t_emlrtRTEI.lineNo);
  }
  if (std::isinf(numRows) || std::isnan(numRows)) {
    j_rtErrorWithMessageID("number of rows", bb_emlrtRTEI.fName,
                           bb_emlrtRTEI.lineNo);
  }
  if (!(std::floor(numRows) == numRows)) {
    k_rtErrorWithMessageID("number of rows", fb_emlrtRTEI.fName,
                           fb_emlrtRTEI.lineNo);
  }
  if (numRows > 5.80032E+6) {
    q_rtErrorWithMessageID(s_emlrtRTEI.fName, s_emlrtRTEI.lineNo);
  }
  if (overlap < 0.0) {
    f_rtErrorWithMessageID("overlap", t_emlrtRTEI.fName, t_emlrtRTEI.lineNo);
  }
  if (std::isinf(overlap) || std::isnan(overlap)) {
    j_rtErrorWithMessageID("overlap", bb_emlrtRTEI.fName, bb_emlrtRTEI.lineNo);
  }
  if (!(std::floor(overlap) == overlap)) {
    k_rtErrorWithMessageID("overlap", fb_emlrtRTEI.fName, fb_emlrtRTEI.lineNo);
  }
  if (overlap > numRows) {
    ib_rtErrorWithMessageID(vb_emlrtRTEI.fName, vb_emlrtRTEI.lineNo);
  }
  if (!pBuffer.AsyncBuffercgHelper_isInitialized) {
    r_rtErrorWithMessageID(u_emlrtRTEI.fName, u_emlrtRTEI.lineNo);
  }
  underrun = internal::b_AsyncBuffercgHelper::ReadSamplesFromBuffer(
      pBuffer, static_cast<int>(numRows), static_cast<int>(overlap), b_out,
      overlapUnderrun, c);
  out.set_size(b_out.size(0));
  overlapUnderrun = b_out.size(0);
  for (int i{0}; i < overlapUnderrun; i++) {
    out[i] = b_out[i];
  }
  overlapUnderrun = pBuffer.CumulativeUnderrun;
  if ((overlapUnderrun < 0) && (underrun < MIN_int32_T - overlapUnderrun)) {
    overlapUnderrun = MIN_int32_T;
  } else if ((overlapUnderrun > 0) &&
             (underrun > MAX_int32_T - overlapUnderrun)) {
    overlapUnderrun = MAX_int32_T;
  } else {
    overlapUnderrun += underrun;
  }
  pBuffer.CumulativeUnderrun = overlapUnderrun;
  overlapUnderrun = pBuffer.WritePointer;
  if (overlapUnderrun < -2147483647) {
    overlapUnderrun = MIN_int32_T;
  } else {
    overlapUnderrun--;
  }
  if (underrun != 0) {
    pBuffer.ReadPointer = overlapUnderrun;
  } else {
    pBuffer.ReadPointer = c;
  }
}

//
// Arguments    : void
// Return Type  : void
//
void AsyncBuffer::reset()
{
  if (pBuffer.isInitialized == 2) {
    d_rtErrorWithMessageID("reset", q_emlrtRTEI.fName, q_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized == 1) {
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    std::memset(&pBuffer.Cache[0], 0, 5800321U * sizeof(creal32_T));
  }
}

//
// Arguments    : void
// Return Type  : void
//
void b_AsyncBuffer::reset()
{
  if (pBuffer.isInitialized == 2) {
    d_rtErrorWithMessageID("reset", qb_emlrtRTEI.fName, qb_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized == 1) {
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    std::memset(&pBuffer.Cache[0], 0, 5800321U * sizeof(double));
  }
}

//
// Arguments    : void
// Return Type  : void
//
void c_AsyncBuffer::reset()
{
  if (pBuffer.isInitialized == 2) {
    d_rtErrorWithMessageID("reset", qb_emlrtRTEI.fName, qb_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized == 1) {
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    std::memset(&pBuffer.Cache[0], 0, 600651U * sizeof(creal32_T));
  }
}

//
// Arguments    : void
// Return Type  : void
//
void c_AsyncBuffer::write()
{
  internal::c_AsyncBuffercgHelper *obj;
  array<int, 2U> bc;
  array<int, 1U> r;
  int i;
  int overrun;
  int rPtr;
  int wPtr;
  boolean_T anyInputSizeChanged;
  boolean_T exitg1;
  obj = &pBuffer;
  if (pBuffer.isInitialized == 2) {
    d_rtErrorWithMessageID("step", q_emlrtRTEI.fName, q_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized != 1) {
    cell_wrap_2 varSizes;
    pBuffer.isSetupComplete = false;
    if (pBuffer.isInitialized != 0) {
      e_rtErrorWithMessageID("setup", q_emlrtRTEI.fName, q_emlrtRTEI.lineNo);
    }
    pBuffer.isInitialized = 1;
    for (int b_i{0}; b_i < 8; b_i++) {
      varSizes.f1[b_i] = 1U;
    }
    pBuffer.inputVarSize[0] = varSizes;
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      p_rtErrorWithMessageID(r_emlrtRTEI.fName, r_emlrtRTEI.lineNo);
    }
    pBuffer.NumChannels = 1;
    pBuffer.AsyncBuffercgHelper_isInitialized = true;
    pBuffer.isSetupComplete = true;
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    for (i = 0; i < 600651; i++) {
      pBuffer.Cache[i].re = 0.0F;
      pBuffer.Cache[i].im = 0.0F;
      pBuffer.Cache[i].re = 0.0F;
      pBuffer.Cache[i].im = 0.0F;
    }
  }
  anyInputSizeChanged = false;
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 8)) {
    if (obj->inputVarSize[0].f1[i] != 1U) {
      anyInputSizeChanged = true;
      for (int b_i{0}; b_i < 8; b_i++) {
        obj->inputVarSize[0].f1[b_i] = 1U;
      }
      exitg1 = true;
    } else {
      i++;
    }
  }
  if (anyInputSizeChanged && (pBuffer.NumChannels != -1) &&
      (pBuffer.NumChannels != 1)) {
    p_rtErrorWithMessageID(r_emlrtRTEI.fName, r_emlrtRTEI.lineNo);
  }
  obj = &pBuffer;
  wPtr = pBuffer.WritePointer;
  rPtr = pBuffer.ReadPointer;
  overrun = 0;
  if ((wPtr < 1) || (wPtr > 600651)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  eml_integer_colon_dispatcher(wPtr, wPtr, bc);
  if ((wPtr <= rPtr) && (rPtr <= wPtr)) {
    overrun = (wPtr - rPtr) + 1;
  }
  r.set_size(bc.size(1));
  i = bc.size(1);
  for (int b_i{0}; b_i < i; b_i++) {
    if ((bc[b_i] < 1) || (bc[b_i] > 600651)) {
      rtDynamicBoundsError(bc[b_i], 1, 600651, emlrtBCI);
    }
    r[b_i] = bc[b_i];
  }
  i = r.size(0);
  for (int b_i{0}; b_i < i; b_i++) {
    obj->Cache[r[b_i] - 1].re = 1.0F;
    obj->Cache[r[b_i] - 1].im = 1.0F;
  }
  if (wPtr + 1 > 600651) {
    wPtr = 1;
  } else {
    wPtr++;
  }
  if (overrun != 0) {
    rPtr = wPtr;
  }
  i = pBuffer.CumulativeOverrun;
  if ((i < 0) && (overrun < MIN_int32_T - i)) {
    i = MIN_int32_T;
  } else if ((i > 0) && (overrun > MAX_int32_T - i)) {
    i = MAX_int32_T;
  } else {
    i += overrun;
  }
  pBuffer.CumulativeOverrun = i;
  pBuffer.WritePointer = wPtr;
  pBuffer.ReadPointer = rPtr;
}

//
// Arguments    : const array<creal32_T, 1U> &in
// Return Type  : void
//
void AsyncBuffer::write(const array<creal32_T, 1U> &in)
{
  internal::AsyncBuffercgHelper *obj;
  array<int, 2U> b_y;
  array<int, 2U> bc;
  array<int, 2U> y;
  array<int, 1U> r;
  unsigned int inSize[8];
  int b_qY;
  int c;
  int i;
  int k;
  int qY;
  int rPtr;
  int wPtr;
  int yk;
  boolean_T anyInputSizeChanged;
  boolean_T exitg1;
  obj = &pBuffer;
  if (pBuffer.isInitialized == 2) {
    d_rtErrorWithMessageID("step", rb_emlrtRTEI.fName, rb_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized != 1) {
    cell_wrap_2 varSizes;
    pBuffer.isSetupComplete = false;
    if (pBuffer.isInitialized != 0) {
      e_rtErrorWithMessageID("setup", tb_emlrtRTEI.fName, tb_emlrtRTEI.lineNo);
    }
    pBuffer.isInitialized = 1;
    varSizes.f1[0] = static_cast<unsigned int>(in.size(0));
    varSizes.f1[1] = 1U;
    for (yk = 0; yk < 6; yk++) {
      varSizes.f1[yk + 2] = 1U;
    }
    pBuffer.inputVarSize[0] = varSizes;
    if (in.size(0) > 5800320) {
      fb_rtErrorWithMessageID(sb_emlrtRTEI.fName, sb_emlrtRTEI.lineNo);
    }
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      p_rtErrorWithMessageID(r_emlrtRTEI.fName, r_emlrtRTEI.lineNo);
    }
    pBuffer.NumChannels = 1;
    pBuffer.AsyncBuffercgHelper_isInitialized = true;
    pBuffer.isSetupComplete = true;
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    for (i = 0; i < 5800321; i++) {
      pBuffer.Cache[i].re = 0.0F;
      pBuffer.Cache[i].im = 0.0F;
      pBuffer.Cache[i].re = 0.0F;
      pBuffer.Cache[i].im = 0.0F;
    }
  }
  anyInputSizeChanged = false;
  inSize[0] = static_cast<unsigned int>(in.size(0));
  inSize[1] = 1U;
  for (yk = 0; yk < 6; yk++) {
    inSize[yk + 2] = 1U;
  }
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 8)) {
    if (obj->inputVarSize[0].f1[k] != inSize[k]) {
      anyInputSizeChanged = true;
      for (yk = 0; yk < 8; yk++) {
        obj->inputVarSize[0].f1[yk] = inSize[yk];
      }
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (anyInputSizeChanged) {
    if (in.size(0) > 5800320) {
      fb_rtErrorWithMessageID(sb_emlrtRTEI.fName, sb_emlrtRTEI.lineNo);
    }
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      p_rtErrorWithMessageID(r_emlrtRTEI.fName, r_emlrtRTEI.lineNo);
    }
  }
  wPtr = pBuffer.WritePointer;
  rPtr = pBuffer.ReadPointer;
  qY = 0;
  if ((wPtr < 1) || (wPtr > 5800321)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  if (in.size(0) > MAX_int32_T - wPtr) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = wPtr + in.size(0);
  }
  c = b_qY - 1;
  if (b_qY - 1 > 5800321) {
    c = b_qY - 5800322;
    i = 5800322 - wPtr;
    y.set_size(1, i);
    y[0] = wPtr;
    yk = wPtr;
    for (k = 2; k <= i; k++) {
      yk++;
      y[k - 1] = yk;
    }
    if (b_qY - 5800322 < 1) {
      i = 0;
    } else {
      i = b_qY - 5800322;
    }
    b_y.set_size(1, i);
    if (i > 0) {
      b_y[0] = 1;
      yk = 1;
      if (i > 2147483646) {
        check_forloop_overflow_error();
      }
      for (k = 2; k <= i; k++) {
        yk++;
        b_y[k - 1] = yk;
      }
    }
    bc.set_size(1, y.size(1) + b_y.size(1));
    i = y.size(1);
    for (yk = 0; yk < i; yk++) {
      bc[yk] = y[yk];
    }
    i = b_y.size(1);
    for (yk = 0; yk < i; yk++) {
      bc[yk + y.size(1)] = b_y[yk];
    }
    if (wPtr <= rPtr) {
      qY = b_qY - rPtr;
    } else if (rPtr <= b_qY - 5800322) {
      if (rPtr < b_qY + 2141683327) {
        b_qY = MAX_int32_T;
      } else {
        b_qY = (b_qY - rPtr) - 5800322;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  } else {
    eml_integer_colon_dispatcher(wPtr, b_qY - 1, bc);
    if ((wPtr <= rPtr) && (rPtr <= b_qY - 1)) {
      qY = b_qY - rPtr;
    }
  }
  r.set_size(bc.size(1));
  i = bc.size(1);
  for (yk = 0; yk < i; yk++) {
    if ((bc[yk] < 1) || (bc[yk] > 5800321)) {
      rtDynamicBoundsError(bc[yk], 1, 5800321, s_emlrtBCI);
    }
    r[yk] = bc[yk] - 1;
  }
  rtSubAssignSizeCheck(r.size(), 1, ((array<creal32_T, 1U> *)&in)->size(), 1,
                       e_emlrtECI);
  i = in.size(0);
  for (yk = 0; yk < i; yk++) {
    pBuffer.Cache[r[yk]] = in[yk];
  }
  if (c + 1 > 5800321) {
    wPtr = 1;
  } else {
    wPtr = c + 1;
  }
  if (qY != 0) {
    rPtr = wPtr;
  }
  i = pBuffer.CumulativeOverrun;
  if ((i < 0) && (qY < MIN_int32_T - i)) {
    b_qY = MIN_int32_T;
  } else if ((i > 0) && (qY > MAX_int32_T - i)) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = i + qY;
  }
  pBuffer.CumulativeOverrun = b_qY;
  pBuffer.WritePointer = wPtr;
  pBuffer.ReadPointer = rPtr;
}

//
// Arguments    : const array<double, 1U> &in
// Return Type  : void
//
void b_AsyncBuffer::write(const array<double, 1U> &in)
{
  internal::b_AsyncBuffercgHelper *obj;
  array<int, 2U> b_y;
  array<int, 2U> bc;
  array<int, 2U> y;
  array<int, 1U> r;
  unsigned int inSize[8];
  int b_qY;
  int c;
  int i;
  int k;
  int qY;
  int rPtr;
  int wPtr;
  int yk;
  boolean_T anyInputSizeChanged;
  boolean_T exitg1;
  obj = &pBuffer;
  if (pBuffer.isInitialized == 2) {
    d_rtErrorWithMessageID("step", rb_emlrtRTEI.fName, rb_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized != 1) {
    cell_wrap_2 varSizes;
    pBuffer.isSetupComplete = false;
    if (pBuffer.isInitialized != 0) {
      e_rtErrorWithMessageID("setup", tb_emlrtRTEI.fName, tb_emlrtRTEI.lineNo);
    }
    pBuffer.isInitialized = 1;
    varSizes.f1[0] = static_cast<unsigned int>(in.size(0));
    varSizes.f1[1] = 1U;
    for (yk = 0; yk < 6; yk++) {
      varSizes.f1[yk + 2] = 1U;
    }
    pBuffer.inputVarSize[0] = varSizes;
    if (in.size(0) > 5800320) {
      fb_rtErrorWithMessageID(sb_emlrtRTEI.fName, sb_emlrtRTEI.lineNo);
    }
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      p_rtErrorWithMessageID(r_emlrtRTEI.fName, r_emlrtRTEI.lineNo);
    }
    pBuffer.NumChannels = 1;
    pBuffer.AsyncBuffercgHelper_isInitialized = true;
    pBuffer.isSetupComplete = true;
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    for (i = 0; i < 5800321; i++) {
      pBuffer.Cache[i] = 0.0;
      pBuffer.Cache[i] = 0.0;
    }
  }
  anyInputSizeChanged = false;
  inSize[0] = static_cast<unsigned int>(in.size(0));
  inSize[1] = 1U;
  for (yk = 0; yk < 6; yk++) {
    inSize[yk + 2] = 1U;
  }
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 8)) {
    if (obj->inputVarSize[0].f1[k] != inSize[k]) {
      anyInputSizeChanged = true;
      for (yk = 0; yk < 8; yk++) {
        obj->inputVarSize[0].f1[yk] = inSize[yk];
      }
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (anyInputSizeChanged) {
    if (in.size(0) > 5800320) {
      fb_rtErrorWithMessageID(sb_emlrtRTEI.fName, sb_emlrtRTEI.lineNo);
    }
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      p_rtErrorWithMessageID(r_emlrtRTEI.fName, r_emlrtRTEI.lineNo);
    }
  }
  wPtr = pBuffer.WritePointer;
  rPtr = pBuffer.ReadPointer;
  qY = 0;
  if ((wPtr < 1) || (wPtr > 5800321)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  if (in.size(0) > MAX_int32_T - wPtr) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = wPtr + in.size(0);
  }
  c = b_qY - 1;
  if (b_qY - 1 > 5800321) {
    c = b_qY - 5800322;
    i = 5800322 - wPtr;
    y.set_size(1, i);
    y[0] = wPtr;
    yk = wPtr;
    for (k = 2; k <= i; k++) {
      yk++;
      y[k - 1] = yk;
    }
    if (b_qY - 5800322 < 1) {
      i = 0;
    } else {
      i = b_qY - 5800322;
    }
    b_y.set_size(1, i);
    if (i > 0) {
      b_y[0] = 1;
      yk = 1;
      if (i > 2147483646) {
        check_forloop_overflow_error();
      }
      for (k = 2; k <= i; k++) {
        yk++;
        b_y[k - 1] = yk;
      }
    }
    bc.set_size(1, y.size(1) + b_y.size(1));
    i = y.size(1);
    for (yk = 0; yk < i; yk++) {
      bc[yk] = y[yk];
    }
    i = b_y.size(1);
    for (yk = 0; yk < i; yk++) {
      bc[yk + y.size(1)] = b_y[yk];
    }
    if (wPtr <= rPtr) {
      qY = b_qY - rPtr;
    } else if (rPtr <= b_qY - 5800322) {
      if (rPtr < b_qY + 2141683327) {
        b_qY = MAX_int32_T;
      } else {
        b_qY = (b_qY - rPtr) - 5800322;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  } else {
    eml_integer_colon_dispatcher(wPtr, b_qY - 1, bc);
    if ((wPtr <= rPtr) && (rPtr <= b_qY - 1)) {
      qY = b_qY - rPtr;
    }
  }
  r.set_size(bc.size(1));
  i = bc.size(1);
  for (yk = 0; yk < i; yk++) {
    if ((bc[yk] < 1) || (bc[yk] > 5800321)) {
      rtDynamicBoundsError(bc[yk], 1, 5800321, s_emlrtBCI);
    }
    r[yk] = bc[yk] - 1;
  }
  rtSubAssignSizeCheck(r.size(), 1, ((array<double, 1U> *)&in)->size(), 1,
                       e_emlrtECI);
  i = in.size(0);
  for (yk = 0; yk < i; yk++) {
    pBuffer.Cache[r[yk]] = in[yk];
  }
  if (c + 1 > 5800321) {
    wPtr = 1;
  } else {
    wPtr = c + 1;
  }
  if (qY != 0) {
    rPtr = wPtr;
  }
  i = pBuffer.CumulativeOverrun;
  if ((i < 0) && (qY < MIN_int32_T - i)) {
    b_qY = MIN_int32_T;
  } else if ((i > 0) && (qY > MAX_int32_T - i)) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = i + qY;
  }
  pBuffer.CumulativeOverrun = b_qY;
  pBuffer.WritePointer = wPtr;
  pBuffer.ReadPointer = rPtr;
}

//
// Arguments    : const creal32_T in_data[]
// Return Type  : void
//
void c_AsyncBuffer::write(const creal32_T in_data[])
{
  static const short inSize[8]{1023, 1, 1, 1, 1, 1, 1, 1};
  static const short iv[8]{1023, 1, 1, 1, 1, 1, 1, 1};
  static const short iv1[8]{1023, 1, 1, 1, 1, 1, 1, 1};
  internal::c_AsyncBuffercgHelper *obj;
  int i;
  boolean_T anyInputSizeChanged;
  boolean_T exitg1;
  obj = &pBuffer;
  if (pBuffer.isInitialized == 2) {
    d_rtErrorWithMessageID("step", rb_emlrtRTEI.fName, rb_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized != 1) {
    cell_wrap_2 varSizes;
    pBuffer.isSetupComplete = false;
    if (pBuffer.isInitialized != 0) {
      e_rtErrorWithMessageID("setup", tb_emlrtRTEI.fName, tb_emlrtRTEI.lineNo);
    }
    pBuffer.isInitialized = 1;
    for (i = 0; i < 8; i++) {
      varSizes.f1[i] = static_cast<unsigned int>(iv1[i]);
    }
    pBuffer.inputVarSize[0] = varSizes;
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      p_rtErrorWithMessageID(r_emlrtRTEI.fName, r_emlrtRTEI.lineNo);
    }
    pBuffer.NumChannels = 1;
    pBuffer.AsyncBuffercgHelper_isInitialized = true;
    pBuffer.isSetupComplete = true;
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    for (i = 0; i < 600651; i++) {
      pBuffer.Cache[i].re = 0.0F;
      pBuffer.Cache[i].im = 0.0F;
      pBuffer.Cache[i].re = 0.0F;
      pBuffer.Cache[i].im = 0.0F;
    }
  }
  anyInputSizeChanged = false;
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 8)) {
    if (obj->inputVarSize[0].f1[i] != static_cast<unsigned int>(iv[i])) {
      anyInputSizeChanged = true;
      for (i = 0; i < 8; i++) {
        obj->inputVarSize[0].f1[i] = static_cast<unsigned int>(inSize[i]);
      }
      exitg1 = true;
    } else {
      i++;
    }
  }
  if (anyInputSizeChanged && (pBuffer.NumChannels != -1) &&
      (pBuffer.NumChannels != 1)) {
    p_rtErrorWithMessageID(r_emlrtRTEI.fName, r_emlrtRTEI.lineNo);
  }
  pBuffer.stepImpl(in_data);
}

} // namespace dsp
} // namespace coder

//
// File trailer for AsyncBuffer.cpp
//
// [EOF]
//
