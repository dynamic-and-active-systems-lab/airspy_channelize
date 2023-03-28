//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: AsyncBuffer.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 28-Mar-2023 15:24:09
//

#ifndef ASYNCBUFFER_H
#define ASYNCBUFFER_H

// Include Files
#include "AsyncBuffercgHelper.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace dsp {
class AsyncBuffer {
public:
  void write();
  void read();
  void write(const creal32_T in_data[], int in_size);
  void read(::coder::array<creal32_T, 1U> &out);
  void matlabCodegenDestructor();
  ~AsyncBuffer();
  AsyncBuffer();
  boolean_T matlabCodegenIsDeleted;
  internal::AsyncBuffercgHelper pBuffer;
};

} // namespace dsp
} // namespace coder

#endif
//
// File trailer for AsyncBuffer.h
//
// [EOF]
//
