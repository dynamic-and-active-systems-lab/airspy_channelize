//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: AsyncBuffercgHelper.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 28-Mar-2023 15:24:09
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
                                   int numRowsCast,
                                   ::coder::array<creal32_T, 1U> &out, int &c);
  int stepImpl(const creal32_T in_data[], int in_size);
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
