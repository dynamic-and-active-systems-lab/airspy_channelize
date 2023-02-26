//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBuffercgHelper.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 26-Feb-2023 12:01:14
//

// Include Files
#include "AsyncBuffercgHelper.h"
#include "airspy_channelize_data.h"
#include "airspy_channelize_rtwutil.h"
#include "airspy_channelize_types.h"
#include "colon.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace coder {
namespace dsp {
namespace internal {
void AsyncBuffercgHelper::SystemCore_delete()
{
  release();
}

//
// Arguments    : void
// Return Type  : void
//
void AsyncBuffercgHelper::matlabCodegenDestructor()
{
  if (!matlabCodegenIsDeleted) {
    matlabCodegenIsDeleted = true;
    SystemCore_delete();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void AsyncBuffercgHelper::release()
{
  if (isInitialized == 1) {
    isInitialized = 2;
    releaseWrapper();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void AsyncBuffercgHelper::releaseImpl()
{
  ReadPointer = 1;
  WritePointer = 2;
  CumulativeOverrun = 0;
  CumulativeUnderrun = 0;
  AsyncBuffercgHelper_isInitialized = false;
  NumChannels = -1;
}

//
// Arguments    : void
// Return Type  : void
//
void AsyncBuffercgHelper::releaseWrapper()
{
  if (isSetupComplete) {
    releaseImpl();
  }
}

//
// Arguments    : const AsyncBuffercgHelper *obj
//                int numRowsCast
//                ::coder::array<creal32_T, 1U> &out
//                int *underrun
//                int *c
// Return Type  : void
//
void AsyncBuffercgHelper::ReadSamplesFromBuffer(
    const AsyncBuffercgHelper *obj, int numRowsCast,
    ::coder::array<creal32_T, 1U> &out, int *underrun, int *c)
{
  array<int, 2U> readIdx;
  array<int, 2U> y;
  int i;
  int k;
  int n;
  int rPtr;
  int wPtr;
  int yk;
  wPtr = obj->WritePointer;
  *underrun = 0;
  n = obj->ReadPointer;
  if (n > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = n + 1;
  }
  if (rPtr > 204801) {
    rPtr = 1;
  }
  if ((wPtr < 1) || (wPtr > 204801) || (rPtr < 1) || (numRowsCast > 204801)) {
    rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  *c = (rPtr + numRowsCast) - 1;
  if (*c > 204801) {
    *c -= 204801;
    n = 204802 - rPtr;
    readIdx.set_size(1, 204802 - rPtr);
    readIdx[0] = rPtr;
    yk = rPtr;
    for (k = 2; k <= n; k++) {
      yk++;
      readIdx[k - 1] = yk;
    }
    y.set_size(1, *c);
    y[0] = 1;
    yk = 1;
    for (k = 2; k <= *c; k++) {
      yk++;
      y[k - 1] = yk;
    }
    k = readIdx.size(1);
    readIdx.set_size(1, readIdx.size(1) + y.size(1));
    n = y.size(1);
    for (i = 0; i < n; i++) {
      readIdx[i + k] = y[i];
    }
    if (rPtr <= wPtr) {
      *underrun = (*c - wPtr) + 204802;
    } else if (wPtr <= *c) {
      *underrun = (*c - wPtr) + 1;
    }
  } else {
    eml_integer_colon_dispatcher(rPtr, *c, readIdx);
    if ((rPtr <= wPtr) && (wPtr <= *c)) {
      *underrun = (*c - wPtr) + 1;
    }
  }
  out.set_size(readIdx.size(1));
  n = readIdx.size(1);
  for (k = 0; k < n; k++) {
    if ((readIdx[k] < 1) || (readIdx[k] > 204801)) {
      rtDynamicBoundsError(readIdx[k], 1, 204801, &d_emlrtBCI);
    }
    out[k].re = obj->Cache[readIdx[k] - 1].re;
    if ((readIdx[k] < 1) || (readIdx[k] > 204801)) {
      rtDynamicBoundsError(readIdx[k], 1, 204801, &d_emlrtBCI);
    }
    out[k].im = obj->Cache[readIdx[k] - 1].im;
  }
  if (*underrun != 0) {
    if ((numRowsCast >= 0) && (*underrun < numRowsCast - MAX_int32_T)) {
      yk = MAX_int32_T;
    } else if ((numRowsCast < 0) && (*underrun > numRowsCast - MIN_int32_T)) {
      yk = MIN_int32_T;
    } else {
      yk = numRowsCast - *underrun;
    }
    if (yk + 1 > numRowsCast) {
      yk = 0;
      k = 0;
    } else {
      if ((yk + 1 < 1) || (yk + 1 > readIdx.size(1))) {
        rtDynamicBoundsError(yk + 1, 1, readIdx.size(1), &c_emlrtBCI);
      }
      if ((numRowsCast < 1) || (numRowsCast > readIdx.size(1))) {
        rtDynamicBoundsError(numRowsCast, 1, readIdx.size(1), &b_emlrtBCI);
      }
      k = numRowsCast;
    }
    if (*underrun < 0) {
      rtNonNegativeError(static_cast<double>(*underrun), &emlrtDCI);
    }
    n = k - yk;
    rtSubAssignSizeCheck(&n, underrun, &emlrtECI);
    for (k = 0; k < *underrun; k++) {
      i = yk + k;
      out[i].re = 0.0F;
      out[i].im = 0.0F;
    }
  }
  if (out.size(0) != numRowsCast) {
    c_rtErrorWithMessageID(e_emlrtRTEI.fName, e_emlrtRTEI.lineNo);
  }
}

//
// Arguments    : void
// Return Type  : AsyncBuffercgHelper
//
AsyncBuffercgHelper::AsyncBuffercgHelper()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : void
//
AsyncBuffercgHelper::~AsyncBuffercgHelper()
{
  matlabCodegenDestructor();
}

//
// Arguments    : const creal32_T in_data[]
//                int in_size
// Return Type  : int
//
int AsyncBuffercgHelper::stepImpl(const creal32_T in_data[], int in_size)
{
  static rtEqualityCheckInfo
      b_emlrtECI{
          -1,                          // nDims
          227,                         // lineNo
          13,                          // colNo
          "AsyncBuffercgHelper/write", // fName
          "C:\\Program "
          "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
          "internal\\AsyncBuffercgHelper.m" // pName
      };
  array<int, 2U> bc;
  array<int, 2U> y;
  array<int, 1U> r;
  int c;
  int n;
  int overrun;
  int rPtr;
  int wPtr;
  int yk;
  wPtr = WritePointer;
  rPtr = ReadPointer;
  overrun = 0;
  if ((wPtr < 1) || (wPtr > 204801)) {
    rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  c = wPtr + 2038;
  if (wPtr + 2038 > 204801) {
    c = wPtr - 202763;
    n = 204802 - wPtr;
    bc.set_size(1, 204802 - wPtr);
    bc[0] = wPtr;
    yk = wPtr;
    for (int k{2}; k <= n; k++) {
      yk++;
      bc[k - 1] = yk;
    }
    y.set_size(1, wPtr - 202763);
    y[0] = 1;
    yk = 1;
    for (int k{2}; k <= c; k++) {
      yk++;
      y[k - 1] = yk;
    }
    yk = bc.size(1);
    bc.set_size(1, bc.size(1) + y.size(1));
    n = y.size(1);
    for (int k{0}; k < n; k++) {
      bc[k + yk] = y[k];
    }
    if (wPtr <= rPtr) {
      overrun = (wPtr - rPtr) + 2039;
    } else if (rPtr <= wPtr - 202763) {
      if ((wPtr - 202763 >= 0) && (rPtr < wPtr + 2147280886)) {
        n = MAX_int32_T;
      } else if ((wPtr - 202763 < 0) && (rPtr > wPtr + 2147280885)) {
        n = MIN_int32_T;
      } else {
        n = (wPtr - rPtr) - 202763;
      }
      if (n > 2147483646) {
        overrun = MAX_int32_T;
      } else {
        overrun = n + 1;
      }
    }
  } else {
    eml_integer_colon_dispatcher(wPtr, wPtr + 2038, bc);
    if ((wPtr <= rPtr) && (rPtr <= wPtr + 2038)) {
      overrun = (wPtr - rPtr) + 2039;
    }
  }
  r.set_size(bc.size(1));
  n = bc.size(1);
  for (yk = 0; yk < n; yk++) {
    if ((bc[yk] < 1) || (bc[yk] > 204801)) {
      rtDynamicBoundsError(bc[yk], 1, 204801, &emlrtBCI);
    }
    r[yk] = bc[yk] - 1;
  }
  rtSubAssignSizeCheck(r.size(), &in_size, &b_emlrtECI);
  for (yk = 0; yk < 2039; yk++) {
    Cache[r[yk]] = in_data[yk];
  }
  if (c + 1 > 204801) {
    wPtr = 1;
  } else {
    wPtr = c + 1;
  }
  if (overrun != 0) {
    rPtr = wPtr;
  }
  n = CumulativeOverrun;
  if ((n < 0) && (overrun < MIN_int32_T - n)) {
    n = MIN_int32_T;
  } else if ((n > 0) && (overrun > MAX_int32_T - n)) {
    n = MAX_int32_T;
  } else {
    n += overrun;
  }
  CumulativeOverrun = n;
  WritePointer = wPtr;
  ReadPointer = rPtr;
  return overrun;
}

} // namespace internal
} // namespace dsp
} // namespace coder

//
// File trailer for AsyncBuffercgHelper.cpp
//
// [EOF]
//
