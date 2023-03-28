//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: UDPChannelSender.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 28-Mar-2023 15:24:09
//

#ifndef UDPCHANNELSENDER_H
#define UDPCHANNELSENDER_H

// Include Files
#include "ComplexSingleSamplesUDPSender.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class UDPChannelSender {
public:
  UDPChannelSender *init(coder::array<int, 2U> &channelsUsed);
  void sendChannelData(const coder::array<creal32_T, 2U> &channelData,
                       const creal32_T timeStampForSending) const;
  coder::array<int, 2U> channelIndices;
  coder::array<ComplexSingleSamplesUDPSender, 2U> channelSenders;
};

#endif
//
// File trailer for UDPChannelSender.h
//
// [EOF]
//
