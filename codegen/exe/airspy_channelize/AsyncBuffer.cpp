//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBuffer.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Apr-2023 16:45:43
//

// Include Files
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "airspy_channelize_data.h"
#include "airspy_channelize_internal_types.h"
#include "airspy_channelize_rtwutil.h"
#include "airspy_channelize_types.h"
#include "colon.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "omp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo c_emlrtRTEI{
    101,                                     // lineNo
    "AsyncBuffercgHelper/validateInputsImpl" // fName
};

static rtRunTimeErrorInfo d_emlrtRTEI{
    324,                       // lineNo
    "AsyncBuffercgHelper/read" // fName
};

// Function Declarations
static void c_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

static void d_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void e_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace coder {
namespace dsp {
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
static void c_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "Expected ") << r) << " to be nonnegative.";
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
static void d_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void e_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "Buffer not initialized. You must call write before read or peek.";
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
// Return Type  : AsyncBuffer
//
namespace coder {
namespace dsp {
AsyncBuffer::AsyncBuffer()
{
  matlabCodegenIsDeleted = true;
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
void AsyncBuffer::read()
{
  static rtRunTimeErrorInfo p_emlrtRTEI{
      103,                 // lineNo
      "AsyncBuffercg/read" // fName
  };
  static rtRunTimeErrorInfo q_emlrtRTEI{
      14,                   // lineNo
      "validatenonnegative" // fName
  };
  array<creal32_T, 1U> b_out;
  array<creal32_T, 1U> out;
  int c;
  int numRows;
  int q0_tmp;
  int qY;
  int underrun;
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
  if (numRows < -2147278847) {
    numRows = MAX_int32_T;
  } else {
    numRows = 204800 - numRows;
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
    numRows = 204800;
  }
  if (numRows < 0) {
    c_rtErrorWithMessageID("number of rows", q_emlrtRTEI.fName,
                           q_emlrtRTEI.lineNo);
  }
  if (numRows > 204800) {
    d_rtErrorWithMessageID(p_emlrtRTEI.fName, p_emlrtRTEI.lineNo);
  }
  if (!pBuffer.AsyncBuffercgHelper_isInitialized) {
    e_rtErrorWithMessageID(d_emlrtRTEI.fName, d_emlrtRTEI.lineNo);
  }
  internal::AsyncBuffercgHelper::ReadSamplesFromBuffer(&pBuffer, numRows, out,
                                                       &underrun, &c);
  b_out.set_size(out.size(0));
  numRows = out.size(0);
  for (q0_tmp = 0; q0_tmp < numRows; q0_tmp++) {
    b_out[q0_tmp] = out[q0_tmp];
  }
  numRows = pBuffer.WritePointer;
  if (numRows < -2147483647) {
    qY = MIN_int32_T;
  } else {
    qY = numRows - 1;
  }
  numRows = pBuffer.CumulativeUnderrun;
  if ((numRows < 0) && (underrun < MIN_int32_T - numRows)) {
    numRows = MIN_int32_T;
  } else if ((numRows > 0) && (underrun > MAX_int32_T - numRows)) {
    numRows = MAX_int32_T;
  } else {
    numRows += underrun;
  }
  pBuffer.CumulativeUnderrun = numRows;
  if (underrun != 0) {
    pBuffer.ReadPointer = qY;
  } else {
    pBuffer.ReadPointer = c;
  }
}

//
// Arguments    : ::coder::array<creal32_T, 1U> &out
// Return Type  : void
//
void AsyncBuffer::read(::coder::array<creal32_T, 1U> &out)
{
  internal::AsyncBuffercgHelper *obj;
  array<creal32_T, 1U> b_out;
  array<int, 2U> readIdx;
  array<int, 2U> y;
  int c;
  int k;
  int n;
  int rPtr;
  int underrun;
  int wPtr;
  int yk;
  if (!pBuffer.AsyncBuffercgHelper_isInitialized) {
    e_rtErrorWithMessageID(d_emlrtRTEI.fName, d_emlrtRTEI.lineNo);
  }
  obj = &pBuffer;
  wPtr = pBuffer.WritePointer;
  underrun = 0;
  n = pBuffer.ReadPointer;
  if (n > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = n + 1;
  }
  if (rPtr > 204801) {
    rPtr = 1;
  }
  if ((wPtr < 1) || (wPtr > 204801) || (rPtr < 1)) {
    rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  c = rPtr + 102399;
  if (rPtr + 102399 > 204801) {
    c = rPtr - 102402;
    n = 204802 - rPtr;
    readIdx.set_size(1, 204802 - rPtr);
    readIdx[0] = rPtr;
    yk = rPtr;
    for (k = 2; k <= n; k++) {
      yk++;
      readIdx[k - 1] = yk;
    }
    y.set_size(1, rPtr - 102402);
    y[0] = 1;
    yk = 1;
    for (k = 2; k <= c; k++) {
      yk++;
      y[k - 1] = yk;
    }
    k = readIdx.size(1);
    readIdx.set_size(1, readIdx.size(1) + y.size(1));
    n = y.size(1);
    for (yk = 0; yk < n; yk++) {
      readIdx[yk + k] = y[yk];
    }
    if (rPtr <= wPtr) {
      underrun = (rPtr - wPtr) + 102400;
    } else if (wPtr <= rPtr - 102402) {
      underrun = (rPtr - wPtr) - 102401;
    }
  } else {
    eml_integer_colon_dispatcher(rPtr, rPtr + 102399, readIdx);
    if ((rPtr <= wPtr) && (wPtr <= rPtr + 102399)) {
      underrun = (rPtr - wPtr) + 102400;
    }
  }
  b_out.set_size(readIdx.size(1));
  n = readIdx.size(1);
  for (k = 0; k < n; k++) {
    if ((readIdx[k] < 1) || (readIdx[k] > 204801)) {
      rtDynamicBoundsError(readIdx[k], 1, 204801, &d_emlrtBCI);
    }
    b_out[k].re = obj->Cache[readIdx[k] - 1].re;
    if ((readIdx[k] < 1) || (readIdx[k] > 204801)) {
      rtDynamicBoundsError(readIdx[k], 1, 204801, &d_emlrtBCI);
    }
    b_out[k].im = obj->Cache[readIdx[k] - 1].im;
  }
  if (underrun != 0) {
    if (102401 - underrun > 102400) {
      k = -1;
      yk = -1;
    } else {
      if ((102401 - underrun < 1) || (102401 - underrun > readIdx.size(1))) {
        rtDynamicBoundsError(102401 - underrun, 1, readIdx.size(1),
                             &c_emlrtBCI);
      }
      k = 102399 - underrun;
      if (readIdx.size(1) < 102400) {
        rtDynamicBoundsError(102400, 1, readIdx.size(1), &b_emlrtBCI);
      }
      yk = 102399;
    }
    if (underrun < 0) {
      rtNonNegativeError(static_cast<double>(underrun), &emlrtDCI);
    }
    n = yk - k;
    rtSubAssignSizeCheck(&n, &underrun, &emlrtECI);
    for (yk = 0; yk < underrun; yk++) {
      n = (k + yk) + 1;
      b_out[n].re = 0.0F;
      b_out[n].im = 0.0F;
    }
  }
  if (b_out.size(0) != 102400) {
    c_rtErrorWithMessageID(e_emlrtRTEI.fName, e_emlrtRTEI.lineNo);
  }
  out.set_size(b_out.size(0));
  n = b_out.size(0);
  for (k = 0; k < n; k++) {
    out[k] = b_out[k];
  }
  n = pBuffer.WritePointer;
  if (n < -2147483647) {
    yk = MIN_int32_T;
  } else {
    yk = n - 1;
  }
  n = pBuffer.CumulativeUnderrun;
  if ((n < 0) && (underrun < MIN_int32_T - n)) {
    n = MIN_int32_T;
  } else if ((n > 0) && (underrun > MAX_int32_T - n)) {
    n = MAX_int32_T;
  } else {
    n += underrun;
  }
  pBuffer.CumulativeUnderrun = n;
  if (underrun != 0) {
    pBuffer.ReadPointer = yk;
  } else {
    pBuffer.ReadPointer = c;
  }
}

//
// Arguments    : void
// Return Type  : void
//
void AsyncBuffer::write()
{
  internal::AsyncBuffercgHelper *obj;
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
    rtErrorWithMessageID("step", emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized != 1) {
    cell_wrap_3 varSizes;
    pBuffer.isSetupComplete = false;
    if (pBuffer.isInitialized != 0) {
      b_rtErrorWithMessageID("setup", emlrtRTEI.fName, emlrtRTEI.lineNo);
    }
    pBuffer.isInitialized = 1;
    for (int b_i{0}; b_i < 8; b_i++) {
      varSizes.f1[b_i] = 1U;
    }
    pBuffer.inputVarSize[0] = varSizes;
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      b_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
    }
    pBuffer.NumChannels = 1;
    pBuffer.AsyncBuffercgHelper_isInitialized = true;
    for (i = 0; i < 204801; i++) {
      pBuffer.Cache[i].re = 0.0F;
      pBuffer.Cache[i].im = 0.0F;
    }
    pBuffer.isSetupComplete = true;
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    for (i = 0; i < 204801; i++) {
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
    b_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
  }
  obj = &pBuffer;
  wPtr = pBuffer.WritePointer;
  rPtr = pBuffer.ReadPointer;
  overrun = 0;
  if ((wPtr < 1) || (wPtr > 204801)) {
    rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  eml_integer_colon_dispatcher(wPtr, wPtr, bc);
  if ((wPtr <= rPtr) && (rPtr <= wPtr)) {
    overrun = (wPtr - rPtr) + 1;
  }
  r.set_size(bc.size(1));
  i = bc.size(1);
  for (int b_i{0}; b_i < i; b_i++) {
    if ((bc[b_i] < 1) || (bc[b_i] > 204801)) {
      rtDynamicBoundsError(bc[b_i], 1, 204801, &emlrtBCI);
    }
    r[b_i] = bc[b_i];
  }
  i = r.size(0);
  for (int b_i{0}; b_i < i; b_i++) {
    obj->Cache[r[b_i] - 1].re = 1.0F;
    obj->Cache[r[b_i] - 1].im = 1.0F;
  }
  if (wPtr + 1 > 204801) {
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
// Arguments    : const ::coder::array<creal32_T, 1U> &in
// Return Type  : void
//
void AsyncBuffer::write(const ::coder::array<creal32_T, 1U> &in)
{
  static const unsigned short inSize[8]{32768U, 1U, 1U, 1U, 1U, 1U, 1U, 1U};
  static const unsigned short uv[8]{32768U, 1U, 1U, 1U, 1U, 1U, 1U, 1U};
  internal::AsyncBuffercgHelper *obj;
  int i;
  boolean_T anyInputSizeChanged;
  boolean_T exitg1;
  obj = &pBuffer;
  if (pBuffer.isInitialized == 2) {
    rtErrorWithMessageID("step", m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized != 1) {
    cell_wrap_3 varSizes;
    pBuffer.isSetupComplete = false;
    if (pBuffer.isInitialized != 0) {
      b_rtErrorWithMessageID("setup", n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
    }
    pBuffer.isInitialized = 1;
    for (i = 0; i < 8; i++) {
      varSizes.f1[i] = inSize[i];
    }
    pBuffer.inputVarSize[0] = varSizes;
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      b_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
    }
    pBuffer.NumChannels = 1;
    pBuffer.AsyncBuffercgHelper_isInitialized = true;
    for (i = 0; i < 204801; i++) {
      pBuffer.Cache[i].re = 0.0F;
      pBuffer.Cache[i].im = 0.0F;
    }
    pBuffer.isSetupComplete = true;
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    for (i = 0; i < 204801; i++) {
      pBuffer.Cache[i].re = 0.0F;
      pBuffer.Cache[i].im = 0.0F;
    }
  }
  anyInputSizeChanged = false;
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 8)) {
    if (obj->inputVarSize[0].f1[i] != uv[i]) {
      anyInputSizeChanged = true;
      for (i = 0; i < 8; i++) {
        obj->inputVarSize[0].f1[i] = inSize[i];
      }
      exitg1 = true;
    } else {
      i++;
    }
  }
  if (anyInputSizeChanged && (pBuffer.NumChannels != -1) &&
      (pBuffer.NumChannels != 1)) {
    b_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
  }
  pBuffer.stepImpl(in);
}

} // namespace dsp
} // namespace coder

//
// File trailer for AsyncBuffer.cpp
//
// [EOF]
//
