//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBuffercgHelper.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

#ifndef ASYNCBUFFERCGHELPER_H
#define ASYNCBUFFERCGHELPER_H

// Include Files
#include "rtwtypes.h"
#include "uavrt_detection_internal_types.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace dsp {
namespace internal {
class AsyncBuffercgHelper {
public:
  int read(int numRows, array<creal32_T, 1U> &out);
  static int ReadSamplesFromBuffer(const AsyncBuffercgHelper *obj,
                                   int numRowsCast, array<creal32_T, 1U> &out,
                                   int &c);
  static int ReadSamplesFromBuffer(const AsyncBuffercgHelper &obj,
                                   int numRowsCast, int overlapCast,
                                   array<creal32_T, 1U> &out,
                                   int &overlapUnderrun, int &c);
  void matlabCodegenDestructor();
  void release();
  void releaseWrapper();
  ~AsyncBuffercgHelper();
  AsyncBuffercgHelper();

protected:
  void releaseImpl();

private:
  void SystemCore_delete();

public:
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  cell_wrap_2 inputVarSize[1];
  int NumChannels;
  creal32_T Cache[5800321];
  int CumulativeOverrun;
  int CumulativeUnderrun;
  int ReadPointer;
  int WritePointer;
  boolean_T AsyncBuffercgHelper_isInitialized;
};

class b_AsyncBuffercgHelper {
public:
  int read(int numRows, array<double, 1U> &out);
  static int ReadSamplesFromBuffer(const b_AsyncBuffercgHelper *obj,
                                   int numRowsCast, array<double, 1U> &out,
                                   int &c);
  static int ReadSamplesFromBuffer(const b_AsyncBuffercgHelper &obj,
                                   int numRowsCast, int overlapCast,
                                   array<double, 1U> &out, int &overlapUnderrun,
                                   int &c);
  void matlabCodegenDestructor();
  void release();
  void releaseWrapper();
  ~b_AsyncBuffercgHelper();
  b_AsyncBuffercgHelper();

protected:
  void releaseImpl();

private:
  void SystemCore_delete();

public:
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  cell_wrap_2 inputVarSize[1];
  int NumChannels;
  double Cache[5800321];
  int CumulativeOverrun;
  int CumulativeUnderrun;
  int ReadPointer;
  int WritePointer;
  boolean_T AsyncBuffercgHelper_isInitialized;
};

class c_AsyncBuffercgHelper {
public:
  int read(int numRows, array<creal32_T, 1U> &out);
  static int ReadSamplesFromBuffer(const c_AsyncBuffercgHelper *obj,
                                   int numRowsCast, array<creal32_T, 1U> &out,
                                   int &c);
  void matlabCodegenDestructor();
  void release();
  void releaseWrapper();
  int stepImpl(const creal32_T in_data[]);
  ~c_AsyncBuffercgHelper();
  c_AsyncBuffercgHelper();

protected:
  void releaseImpl();

private:
  void SystemCore_delete();

public:
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  cell_wrap_2 inputVarSize[1];
  int NumChannels;
  creal32_T Cache[600651];
  int CumulativeOverrun;
  int CumulativeUnderrun;
  int ReadPointer;
  int WritePointer;
  boolean_T AsyncBuffercgHelper_isInitialized;
};

} // namespace internal
} // namespace dsp
} // namespace coder

#endif
//
// File trailer for AsyncBuffercgHelper.h
//
// [EOF]
//
