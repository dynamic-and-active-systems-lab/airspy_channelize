//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: AsyncBuffercgHelper.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 28-Mar-2023 15:24:09
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
// Arguments    : const AsyncBuffercgHelper &obj
//                int numRowsCast
//                ::coder::array<creal32_T, 1U> &out
//                int &c
// Return Type  : int
//
int AsyncBuffercgHelper::ReadSamplesFromBuffer(
    const AsyncBuffercgHelper &obj, int numRowsCast,
    ::coder::array<creal32_T, 1U> &out, int &c)
{
  array<int, 2U> readIdx;
  array<int, 2U> y;
  int k;
  int n;
  int rPtr;
  int underrun;
  int wPtr;
  int yk;
  wPtr = obj.WritePointer;
  underrun = 0;
  n = obj.ReadPointer;
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
  c = (rPtr + numRowsCast) - 1;
  if (c > 204801) {
    c -= 204801;
    n = 204802 - rPtr;
    readIdx.set_size(1, 204802 - rPtr);
    readIdx[0] = rPtr;
    yk = rPtr;
    for (k = 2; k <= n; k++) {
      yk++;
      readIdx[k - 1] = yk;
    }
    y.set_size(1, c);
    y[0] = 1;
    yk = 1;
    for (k = 2; k <= c; k++) {
      yk++;
      y[k - 1] = yk;
    }
    yk = readIdx.size(1);
    readIdx.set_size(1, readIdx.size(1) + y.size(1));
    n = y.size(1);
    for (k = 0; k < n; k++) {
      readIdx[k + yk] = y[k];
    }
    if (rPtr <= wPtr) {
      underrun = (c - wPtr) + 204802;
    } else if (wPtr <= c) {
      underrun = (c - wPtr) + 1;
    }
  } else {
    eml_integer_colon_dispatcher(rPtr, c, readIdx);
    if ((rPtr <= wPtr) && (wPtr <= c)) {
      underrun = (c - wPtr) + 1;
    }
  }
  out.set_size(readIdx.size(1));
  n = readIdx.size(1);
  for (yk = 0; yk < n; yk++) {
    boolean_T b;
    b = ((readIdx[yk] < 1) || (readIdx[yk] > 204801));
    if (b) {
      rtDynamicBoundsError(readIdx[yk], 1, 204801, d_emlrtBCI);
    }
    out[yk].re = obj.Cache[readIdx[yk] - 1].re;
    out[yk].im = obj.Cache[readIdx[yk] - 1].im;
  }
  if (underrun != 0) {
    if ((numRowsCast >= 0) && (underrun < numRowsCast - MAX_int32_T)) {
      n = MAX_int32_T;
    } else if ((numRowsCast < 0) && (underrun > numRowsCast - MIN_int32_T)) {
      n = MIN_int32_T;
    } else {
      n = numRowsCast - underrun;
    }
    if (n + 1 > numRowsCast) {
      n = 0;
      yk = 0;
    } else {
      if ((n + 1 < 1) || (n + 1 > readIdx.size(1))) {
        rtDynamicBoundsError(n + 1, 1, readIdx.size(1), c_emlrtBCI);
      }
      if ((numRowsCast < 1) || (numRowsCast > readIdx.size(1))) {
        rtDynamicBoundsError(numRowsCast, 1, readIdx.size(1), b_emlrtBCI);
      }
      yk = numRowsCast;
    }
    if (underrun < 0) {
      rtNonNegativeError(static_cast<double>(underrun), emlrtDCI);
    }
    yk -= n;
    rtSubAssignSizeCheck(&yk, underrun, emlrtECI);
    for (yk = 0; yk < underrun; yk++) {
      k = n + yk;
      out[k].re = 0.0F;
      out[k].im = 0.0F;
    }
  }
  if (out.size(0) != numRowsCast) {
    c_rtErrorWithMessageID(e_emlrtRTEI.fName, e_emlrtRTEI.lineNo);
  }
  return underrun;
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
  static rtEqualityCheckInfo b_emlrtECI{
      -1,                          // nDims
      227,                         // lineNo
      13,                          // colNo
      "AsyncBuffercgHelper/write", // fName
      "/Applications/MATLAB_R2023a.app/toolbox/dsp/dsp/+dsp/+internal/"
      "AsyncBuffercgHelper.m" // pName
  };
  array<int, 2U> bc;
  array<int, 1U> r;
  array<short, 2U> y;
  int c;
  int c_tmp_tmp;
  int n;
  int overrun;
  int rPtr;
  int wPtr;
  wPtr = WritePointer;
  rPtr = ReadPointer;
  overrun = 0;
  if ((wPtr < 1) || (wPtr > 204801)) {
    rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  c = wPtr + 2038;
  if (wPtr + 2038 > 204801) {
    int yk;
    c_tmp_tmp = wPtr - 202763;
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
    for (int k{2}; k <= c_tmp_tmp; k++) {
      yk++;
      y[k - 1] = static_cast<short>(yk);
    }
    n = bc.size(1);
    bc.set_size(1, bc.size(1) + y.size(1));
    c_tmp_tmp = y.size(1);
    for (yk = 0; yk < c_tmp_tmp; yk++) {
      bc[yk + n] = y[yk];
    }
    if (wPtr <= rPtr) {
      overrun = (wPtr - rPtr) + 2039;
    } else if (rPtr <= wPtr - 202763) {
      if ((wPtr - 202763 >= 0) && (rPtr < wPtr + 2147280886)) {
        c_tmp_tmp = MAX_int32_T;
      } else if ((wPtr - 202763 < 0) && (rPtr > wPtr + 2147280885)) {
        c_tmp_tmp = MIN_int32_T;
      } else {
        c_tmp_tmp = (wPtr - rPtr) - 202763;
      }
      if (c_tmp_tmp > 2147483646) {
        overrun = MAX_int32_T;
      } else {
        overrun = c_tmp_tmp + 1;
      }
    }
  } else {
    eml_integer_colon_dispatcher(wPtr, wPtr + 2038, bc);
    if ((wPtr <= rPtr) && (rPtr <= wPtr + 2038)) {
      overrun = (wPtr - rPtr) + 2039;
    }
  }
  r.set_size(bc.size(1));
  c_tmp_tmp = bc.size(1);
  for (n = 0; n < c_tmp_tmp; n++) {
    if ((bc[n] < 1) || (bc[n] > 204801)) {
      rtDynamicBoundsError(bc[n], 1, 204801, emlrtBCI);
    }
    r[n] = bc[n] - 1;
  }
  rtSubAssignSizeCheck(r.size(), in_size, b_emlrtECI);
  for (n = 0; n < 2039; n++) {
    Cache[r[n]] = in_data[n];
  }
  if (c + 1 > 204801) {
    wPtr = 1;
  } else {
    wPtr = c + 1;
  }
  if (overrun != 0) {
    rPtr = wPtr;
  }
  c_tmp_tmp = CumulativeOverrun;
  if ((c_tmp_tmp < 0) && (overrun < MIN_int32_T - c_tmp_tmp)) {
    c_tmp_tmp = MIN_int32_T;
  } else if ((c_tmp_tmp > 0) && (overrun > MAX_int32_T - c_tmp_tmp)) {
    c_tmp_tmp = MAX_int32_T;
  } else {
    c_tmp_tmp += overrun;
  }
  CumulativeOverrun = c_tmp_tmp;
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
