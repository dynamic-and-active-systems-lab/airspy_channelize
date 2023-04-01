//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ComplexSingleSamplesUDPReceiver.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Apr-2023 16:45:43
//

// Include Files
#include "ComplexSingleSamplesUDPReceiver.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "udp.h"

// Function Definitions
//
// Arguments    : coder::array<creal32_T, 1U> &complexData
// Return Type  : void
//
void ComplexSingleSamplesUDPReceiver::receive(
    coder::array<creal32_T, 1U> &complexData) const
{
  coder::array<creal32_T, 2U> complexBuffer;
  complexBuffer.set_size(1, 32768);
  for (int i{0}; i < 32768; i++) {
    complexBuffer[i].re = 0.0F;
    complexBuffer[i].im = 0.0F;
  }
  udpReceiverReadComplex(udpReceiver, &complexBuffer[0], 32768.0);
  complexData.set_size(32768);
  for (int i{0}; i < 32768; i++) {
    complexData[i] = complexBuffer[i];
  }
}

//
// File trailer for ComplexSingleSamplesUDPReceiver.cpp
//
// [EOF]
//
