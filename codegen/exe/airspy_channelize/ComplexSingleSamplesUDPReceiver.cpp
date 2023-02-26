//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ComplexSingleSamplesUDPReceiver.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 26-Feb-2023 12:32:19
//

// Include Files
#include "ComplexSingleSamplesUDPReceiver.h"
#include "rt_nonfinite.h"
#include "udp.h"
#include <algorithm>
#include <cstring>

// Function Definitions
//
// Arguments    : creal32_T complexData_data[]
//                int *complexData_size
// Return Type  : void
//
void ComplexSingleSamplesUDPReceiver::receive(creal32_T complexData_data[],
                                              int *complexData_size) const
{
  creal32_T complexBuffer_data[2039];
  std::memset(&complexBuffer_data[0], 0, 2039U * sizeof(creal32_T));
  udpReceiverReadComplex(udpReceiver, &complexBuffer_data[0], 2039.0);
  *complexData_size = 2039;
  std::copy(&complexBuffer_data[0], &complexBuffer_data[2039],
            &complexData_data[0]);
}

//
// File trailer for ComplexSingleSamplesUDPReceiver.cpp
//
// [EOF]
//
