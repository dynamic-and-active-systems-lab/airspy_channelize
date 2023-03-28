//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: ComplexSingleSamplesUDPReceiver.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 28-Mar-2023 15:24:09
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
// Return Type  : int
//
int ComplexSingleSamplesUDPReceiver::receive(creal32_T complexData_data[]) const
{
  creal32_T complexBuffer_data[2039];
  int complexData_size;
  std::memset(&complexBuffer_data[0], 0, 2039U * sizeof(creal32_T));
  udpReceiverReadComplex(udpReceiver, &complexBuffer_data[0], 2039.0);
  complexData_size = 2039;
  std::copy(&complexBuffer_data[0], &complexBuffer_data[2039],
            &complexData_data[0]);
  return complexData_size;
}

//
// File trailer for ComplexSingleSamplesUDPReceiver.cpp
//
// [EOF]
//
