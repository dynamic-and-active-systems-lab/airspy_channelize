//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ComplexSingleSamplesUDPReceiver.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "ComplexSingleSamplesUDPReceiver.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "udp.h"
#include <algorithm>
#include <cstring>

// Function Definitions
//
// Arguments    : double ipPort
// Return Type  : void
//
void ComplexSingleSamplesUDPReceiver::init(double ipPort)
{
  samplesPerFrame = 1024.0;
  udpReceiver = udpReceiverSetup(ipPort);
  if (udpReceiver <= 0) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
}

//
// Arguments    : creal32_T complexData_data[]
// Return Type  : int
//
int ComplexSingleSamplesUDPReceiver::receive(creal32_T complexData_data[]) const
{
  creal32_T complexBuffer_data[1024];
  int complexData_size;
  std::memset(&complexBuffer_data[0], 0, 1024U * sizeof(creal32_T));
  udpReceiverReadComplex(udpReceiver, &complexBuffer_data[0], 1024.0);
  complexData_size = 1024;
  std::copy(&complexBuffer_data[0], &complexBuffer_data[1024],
            &complexData_data[0]);
  return complexData_size;
}

//
// File trailer for ComplexSingleSamplesUDPReceiver.cpp
//
// [EOF]
//
