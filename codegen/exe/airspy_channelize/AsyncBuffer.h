//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBuffer.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:39:26
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
  void write(const creal32_T in_data[]);
  void read(array<creal32_T, 1U> &out);
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
