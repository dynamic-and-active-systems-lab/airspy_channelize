//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Channelizer.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Apr-2023 15:58:05
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
  void step(const ::coder::array<creal32_T, 1U> &varargin_1,
            ::coder::array<creal32_T, 2U> &varargout_1);
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
  unsigned int IPPflag;

private:
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  cell_wrap_3 inputVarSize[1];
  creal32_T vextra[100];
  float NTPB;
  float numStates;
};

} // namespace dsp
} // namespace coder

#endif
//
// File trailer for Channelizer.h
//
// [EOF]
//
