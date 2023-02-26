//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ComplexSingleSamplesUDPReceiver.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 26-Feb-2023 09:39:03
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
  void receive(creal32_T complexData_data[], int *complexData_size) const;
  int udpReceiver;
  double samplesPerFrame;
};

#endif
//
// File trailer for ComplexSingleSamplesUDPReceiver.h
//
// [EOF]
//
