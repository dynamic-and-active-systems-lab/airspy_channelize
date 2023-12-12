//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ComplexSingleSamplesUDPReceiver.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
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
  void init(double ipPort);
  int udpReceiver;
  double samplesPerFrame;
};

#endif
//
// File trailer for ComplexSingleSamplesUDPReceiver.h
//
// [EOF]
//
