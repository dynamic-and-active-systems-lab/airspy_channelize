//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Channelizer.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:39:26
//

#ifndef CHANNELIZER_H
#define CHANNELIZER_H

// Include Files
#include "airspy_channelize_internal_types.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace dsp {
class Channelizer {
public:
  void step(const array<creal32_T, 1U> &varargin_1,
            array<creal32_T, 2U> &varargout_1);
  void matlabCodegenDestructor();
  void release();
  void releaseWrapper();
  ~Channelizer();
  Channelizer();

protected:
  void releaseImpl();

private:
  void SystemCore_delete();

public:
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  short numChannels;

protected:
  creal32_T States[1200];
  float PolyphaseMatrix[1200];
  float actpmatrix[1200];
  int ModuloIdx;
  int StartIdx[100];
  int StopIdx[100];

private:
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  cell_wrap_3 inputVarSize[1];
  creal32_T vextra[100];
  float numStates;
  int phaseIdx;
  int currentState;
};

} // namespace dsp
} // namespace coder

#endif
//
// File trailer for Channelizer.h
//
// [EOF]
//
