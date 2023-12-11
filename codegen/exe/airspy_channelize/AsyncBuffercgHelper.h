//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBuffercgHelper.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 11-Dec-2023 13:33:03
//

#ifndef ASYNCBUFFERCGHELPER_H
#define ASYNCBUFFERCGHELPER_H

// Include Files
#include "airspy_channelize_internal_types.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace dsp {
namespace internal {
class AsyncBuffercgHelper {
public:
  static int ReadSamplesFromBuffer(const AsyncBuffercgHelper &obj,
                                   int numRowsCast, array<creal32_T, 1U> &out,
                                   int &c);
  int stepImpl(const creal32_T in_data[]);
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
  cell_wrap_3 inputVarSize[1];
  int NumChannels;
  creal32_T Cache[204801];
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
