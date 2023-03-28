//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: ComplexSingleSamplesUDPReceiver.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 28-Mar-2023 15:24:09
//

#ifndef COMPLEXSINGLESAMPLESUDPRECEIVER_H
#define COMPLEXSINGLESAMPLESUDPRECEIVER_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class ComplexSingleSamplesUDPReceiver {
public:
  int receive(creal32_T complexData_data[]) const;
  int udpReceiver;
  double samplesPerFrame;
};

#endif
//
// File trailer for ComplexSingleSamplesUDPReceiver.h
//
// [EOF]
//
