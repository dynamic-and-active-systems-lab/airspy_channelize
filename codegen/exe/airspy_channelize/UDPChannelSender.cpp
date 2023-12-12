//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: UDPChannelSender.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:39:26
//

// Include Files
#include "UDPChannelSender.h"
#include "ComplexSingleSamplesUDPSender.h"
#include "airspy_channelize_data.h"
#include "airspy_channelize_rtwutil.h"
#include "airspy_channelize_types.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "omp.h"
#include "udp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
static void rtIntegerError(const double aInteger,
                           const rtDoubleCheckInfo &aInfo);

// Function Definitions
//
// Arguments    : const double aInteger
//                const rtDoubleCheckInfo &aInfo
// Return Type  : void
//
static void rtIntegerError(const double aInteger,
                           const rtDoubleCheckInfo &aInfo)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "Expected a value representable in the C type \'int\'. Found ")
   << aInteger)
      << " instead.";
  outStream << "\n";
  ((((outStream << "Error in ") << aInfo.fName) << " (line ") << aInfo.lineNo)
      << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : coder::array<int, 2U> &channelsUsed
// Return Type  : UDPChannelSender *
//
UDPChannelSender *UDPChannelSender::init(coder::array<int, 2U> &channelsUsed)
{
  static rtBoundsCheckInfo e_emlrtBCI{
      -1,                                  // iFirst
      -1,                                  // iLast
      30,                                  // lineNo
      45,                                  // colNo
      "channelsUsed",                      // aName
      "UDPChannelSender/UDPChannelSender", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/airspy_channelize/UDPChannelSender.m", // pName
      0                                                       // checkKind
  };
  static rtBoundsCheckInfo f_emlrtBCI{
      -1,                                  // iFirst
      -1,                                  // iLast
      46,                                  // lineNo
      32,                                  // colNo
      "channelSenders",                    // aName
      "UDPChannelSender/UDPChannelSender", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/airspy_channelize/UDPChannelSender.m", // pName
      0                                                       // checkKind
  };
  static rtBoundsCheckInfo g_emlrtBCI{
      -1,                                  // iFirst
      -1,                                  // iLast
      51,                                  // lineNo
      45,                                  // colNo
      "channelsUsed",                      // aName
      "UDPChannelSender/UDPChannelSender", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/airspy_channelize/UDPChannelSender.m", // pName
      0                                                       // checkKind
  };
  static rtBoundsCheckInfo h_emlrtBCI{
      -1,                                     // iFirst
      -1,                                     // iLast
      62,                                     // lineNo
      37,                                     // colNo
      "self.channelIndices(nextChannelSlot)", // aName
      "UDPChannelSender/UDPChannelSender",    // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/airspy_channelize/UDPChannelSender.m", // pName
      0                                                       // checkKind
  };
  static rtBoundsCheckInfo i_emlrtBCI{
      -1,                                  // iFirst
      -1,                                  // iLast
      63,                                  // lineNo
      32,                                  // colNo
      "channelSenders",                    // aName
      "UDPChannelSender/UDPChannelSender", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/airspy_channelize/UDPChannelSender.m", // pName
      0                                                       // checkKind
  };
  static rtBoundsCheckInfo j_emlrtBCI{
      -1,                                     // iFirst
      -1,                                     // iLast
      71,                                     // lineNo
      41,                                     // colNo
      "self.channelIndices(nextChannelSlot)", // aName
      "UDPChannelSender/UDPChannelSender",    // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/airspy_channelize/UDPChannelSender.m", // pName
      0                                                       // checkKind
  };
  static rtBoundsCheckInfo k_emlrtBCI{
      -1,                                  // iFirst
      -1,                                  // iLast
      72,                                  // lineNo
      36,                                  // colNo
      "channelSenders",                    // aName
      "UDPChannelSender/UDPChannelSender", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/airspy_channelize/UDPChannelSender.m", // pName
      0                                                       // checkKind
  };
  static rtDoubleCheckInfo b_emlrtDCI{
      39,                                  // lineNo
      44,                                  // colNo
      "UDPChannelSender/UDPChannelSender", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/airspy_channelize/UDPChannelSender.m", // pName
      1                                                       // checkKind
  };
  static rtDoubleCheckInfo c_emlrtDCI{
      40,                                  // lineNo
      43,                                  // colNo
      "UDPChannelSender/UDPChannelSender", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/airspy_channelize/UDPChannelSender.m", // pName
      1                                                       // checkKind
  };
  static rtRunTimeErrorInfo h_emlrtRTEI{
      52,                                 // lineNo
      "UDPChannelSender/UDPChannelSender" // fName
  };
  static rtRunTimeErrorInfo i_emlrtRTEI{
      53,                                 // lineNo
      "UDPChannelSender/UDPChannelSender" // fName
  };
  ComplexSingleSamplesUDPSender udpSender;
  UDPChannelSender *self;
  coder::array<ComplexSingleSamplesUDPSender, 2U> b_channelSenders;
  coder::array<int, 2U> _in;
  int absChannelIndex;
  unsigned int cChannelSlots;
  int c_qY;
  int i;
  int saturatedUnaryMinus;
  self = this;
  //  channelsUsed: An vector of channel indices. Example: [ 1 3 -5 78 ].
  //  Negative numbers indicate that the channel
  //                must be output on two ports.
  //                An empty vector indicates all channels used and no secondary
  //                ports.
  //  firstIPPort:  The first udp port to output on. This will be use for
  //  channel 1.
  //                Subsequent ports for channels are every other port. So for
  //                example if firstIPPort is 20000:
  //                    channel 1 is output on 20000
  //                    channel 2 is output on 20002
  //                    channel 3 is output on 20004
  //                If the channel is negative then the data is output on a
  //                secondary port. Example for secondary ports:
  //                    channel 1 is output on 20001
  //                    channel 2 is output on 20003
  //                    channel 3 is output on 20005
  if (channelsUsed.size(1) == 0) {
    channelsUsed.set_size(1, 100);
    for (i = 0; i < 100; i++) {
      channelsUsed[i] = i + 1;
    }
  }
  //  Determine how many channel slots we need
  cChannelSlots = 0U;
  i = channelsUsed.size(1);
  for (int b_i{0}; b_i < i; b_i++) {
    unsigned int b_qY;
    unsigned int qY;
    if (b_i + 1 > channelsUsed.size(1)) {
      rtDynamicBoundsError(b_i + 1, 1, channelsUsed.size(1), e_emlrtBCI);
    }
    qY = cChannelSlots + 2U;
    if (cChannelSlots + 2U < cChannelSlots) {
      qY = MAX_uint32_T;
    }
    b_qY = cChannelSlots + 1U;
    if (cChannelSlots + 1U < cChannelSlots) {
      b_qY = MAX_uint32_T;
    }
    if (channelsUsed[b_i] < 0) {
      cChannelSlots = qY;
    } else {
      cChannelSlots = b_qY;
    }
  }
  //  Pre-allocate storage for coder
  if (static_cast<double>(cChannelSlots) != static_cast<int>(cChannelSlots)) {
    rtIntegerError(static_cast<double>(cChannelSlots), b_emlrtDCI);
  }
  self->channelIndices.set_size(1, static_cast<int>(cChannelSlots));
  absChannelIndex = static_cast<int>(cChannelSlots);
  for (i = 0; i < absChannelIndex; i++) {
    self->channelIndices[i] = 0;
  }
  b_channelSenders.set_size(1, b_channelSenders.size(1));
  if (static_cast<double>(cChannelSlots) != static_cast<int>(cChannelSlots)) {
    rtIntegerError(static_cast<double>(cChannelSlots), c_emlrtDCI);
  }
  b_channelSenders.set_size(b_channelSenders.size(0),
                            static_cast<int>(cChannelSlots));
  //  We stuff in the first channel first into all slots to keep code happy.
  //  Coder wants all cells to have a value and the code in this function is too
  //  complicated for it to understand that is the case.
  udpSender.samplesPerFrame = 1025.0;
  i = channelsUsed[0];
  if (i <= MIN_int32_T) {
    saturatedUnaryMinus = MAX_int32_T;
  } else {
    saturatedUnaryMinus = -i;
  }
  if (channelsUsed[0] >= 0) {
    saturatedUnaryMinus = channelsUsed[0];
  }
  if (saturatedUnaryMinus < -2147483647) {
    c_qY = MIN_int32_T;
  } else {
    c_qY = saturatedUnaryMinus - 1;
  }
  if (c_qY > 1073741823) {
    saturatedUnaryMinus = MAX_int32_T;
  } else if (c_qY <= -1073741824) {
    saturatedUnaryMinus = MIN_int32_T;
  } else {
    saturatedUnaryMinus = c_qY << 1;
  }
  if (saturatedUnaryMinus > 2147463647) {
    c_qY = MAX_int32_T;
  } else {
    c_qY = saturatedUnaryMinus + 20000;
  }
  if (c_qY > 2147483646) {
    c_qY = MAX_int32_T;
  } else {
    c_qY++;
  }
  udpSender.udpSender = udpSenderSetup(c_qY);
  if (udpSender.udpSender <= 0) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  if (cChannelSlots > 4294967294U) {
    coder::check_forloop_overflow_error();
  }
  for (int b_i{0}; b_i < absChannelIndex; b_i++) {
    if (b_i > b_channelSenders.size(1) - 1) {
      rtDynamicBoundsError(b_i, 0, b_channelSenders.size(1) - 1, f_emlrtBCI);
    }
    b_channelSenders[b_i] = udpSender;
  }
  cChannelSlots = 1U;
  i = channelsUsed.size(1);
  for (int b_i{0}; b_i < i; b_i++) {
    int i1;
    if (b_i + 1 > channelsUsed.size(1)) {
      rtDynamicBoundsError(b_i + 1, 1, channelsUsed.size(1), g_emlrtBCI);
    }
    if (channelsUsed[b_i] == 0) {
      c_rtErrorWithMessageID(h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
    }
    if ((channelsUsed[b_i] < -100) || (channelsUsed[b_i] > 100)) {
      c_rtErrorWithMessageID(i_emlrtRTEI.fName, i_emlrtRTEI.lineNo);
    }
    i1 = channelsUsed[b_i];
    if (i1 <= MIN_int32_T) {
      saturatedUnaryMinus = MAX_int32_T;
    } else {
      saturatedUnaryMinus = -i1;
    }
    if (channelsUsed[b_i] < 0) {
      absChannelIndex = saturatedUnaryMinus;
    } else {
      absChannelIndex = channelsUsed[b_i];
    }
    //  Set up main channel output
    if (absChannelIndex < -2147483647) {
      c_qY = MIN_int32_T;
    } else {
      c_qY = absChannelIndex - 1;
    }
    if (c_qY > 1073741823) {
      saturatedUnaryMinus = MAX_int32_T;
    } else if (c_qY <= -1073741824) {
      saturatedUnaryMinus = MIN_int32_T;
    } else {
      saturatedUnaryMinus = c_qY << 1;
    }
    if (saturatedUnaryMinus > 2147463647) {
      c_qY = MAX_int32_T;
    } else {
      c_qY = saturatedUnaryMinus + 20000;
    }
    i1 = absChannelIndex;
    if (absChannelIndex < 0) {
      i1 = 0;
    }
    saturatedUnaryMinus = c_qY;
    if (c_qY < 0) {
      saturatedUnaryMinus = 0;
    }
    std::printf("Setting up main channel %u port %u\n",
                static_cast<unsigned int>(i1),
                static_cast<unsigned int>(saturatedUnaryMinus));
    std::fflush(stdout);
    udpSender.samplesPerFrame = 1025.0;
    udpSender.udpSender = udpSenderSetup(c_qY);
    if (udpSender.udpSender <= 0) {
      rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
    }
    _in.set_size(1, self->channelIndices.size(1));
    saturatedUnaryMinus = self->channelIndices.size(1);
    for (i1 = 0; i1 < saturatedUnaryMinus; i1++) {
      _in[i1] = self->channelIndices[i1];
    }
    if ((static_cast<int>(cChannelSlots) < 1) ||
        (static_cast<int>(cChannelSlots) > _in.size(1))) {
      rtDynamicBoundsError(static_cast<int>(cChannelSlots), 1, _in.size(1),
                           h_emlrtBCI);
    }
    _in[static_cast<int>(cChannelSlots) - 1] = absChannelIndex;
    self->channelIndices.set_size(1, _in.size(1));
    saturatedUnaryMinus = _in.size(1);
    for (i1 = 0; i1 < saturatedUnaryMinus; i1++) {
      self->channelIndices[i1] = _in[i1];
    }
    if ((static_cast<int>(cChannelSlots) - 1 < 0) ||
        (static_cast<int>(cChannelSlots) - 1 > b_channelSenders.size(1) - 1)) {
      rtDynamicBoundsError(static_cast<int>(cChannelSlots) - 1, 0,
                           b_channelSenders.size(1) - 1, i_emlrtBCI);
    }
    b_channelSenders[static_cast<int>(cChannelSlots) - 1] = udpSender;
    cChannelSlots++;
    if (channelsUsed[b_i] < 0) {
      //  Set up secondary channel output
      i1 = absChannelIndex;
      if (absChannelIndex < 0) {
        i1 = 0;
      }
      if (absChannelIndex < -2147483647) {
        c_qY = MIN_int32_T;
      } else {
        c_qY = absChannelIndex - 1;
      }
      if (c_qY > 1073741823) {
        saturatedUnaryMinus = MAX_int32_T;
      } else if (c_qY <= -1073741824) {
        saturatedUnaryMinus = MIN_int32_T;
      } else {
        saturatedUnaryMinus = c_qY << 1;
      }
      if (saturatedUnaryMinus > 2147463647) {
        c_qY = MAX_int32_T;
      } else {
        c_qY = saturatedUnaryMinus + 20000;
      }
      if (c_qY > 2147483646) {
        c_qY = MAX_int32_T;
      } else {
        c_qY++;
      }
      if (c_qY < 0) {
        c_qY = 0;
      }
      std::printf("Setting up secondary channel %u port %u\n",
                  static_cast<unsigned int>(i1),
                  static_cast<unsigned int>(c_qY));
      std::fflush(stdout);
      udpSender.samplesPerFrame = 1025.0;
      if (absChannelIndex < -2147483647) {
        c_qY = MIN_int32_T;
      } else {
        c_qY = absChannelIndex - 1;
      }
      if (c_qY > 1073741823) {
        saturatedUnaryMinus = MAX_int32_T;
      } else if (c_qY <= -1073741824) {
        saturatedUnaryMinus = MIN_int32_T;
      } else {
        saturatedUnaryMinus = c_qY << 1;
      }
      if (saturatedUnaryMinus > 2147463647) {
        c_qY = MAX_int32_T;
      } else {
        c_qY = saturatedUnaryMinus + 20000;
      }
      if (c_qY > 2147483646) {
        c_qY = MAX_int32_T;
      } else {
        c_qY++;
      }
      udpSender.udpSender = udpSenderSetup(c_qY);
      if (udpSender.udpSender <= 0) {
        rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
      }
      _in.set_size(1, self->channelIndices.size(1));
      saturatedUnaryMinus = self->channelIndices.size(1);
      for (i1 = 0; i1 < saturatedUnaryMinus; i1++) {
        _in[i1] = self->channelIndices[i1];
      }
      if ((static_cast<int>(cChannelSlots) < 1) ||
          (static_cast<int>(cChannelSlots) > _in.size(1))) {
        rtDynamicBoundsError(static_cast<int>(cChannelSlots), 1, _in.size(1),
                             j_emlrtBCI);
      }
      _in[static_cast<int>(cChannelSlots) - 1] = absChannelIndex;
      self->channelIndices.set_size(1, _in.size(1));
      saturatedUnaryMinus = _in.size(1);
      for (i1 = 0; i1 < saturatedUnaryMinus; i1++) {
        self->channelIndices[i1] = _in[i1];
      }
      if ((static_cast<int>(cChannelSlots) - 1 < 0) ||
          (static_cast<int>(cChannelSlots) - 1 >
           b_channelSenders.size(1) - 1)) {
        rtDynamicBoundsError(static_cast<int>(cChannelSlots) - 1, 0,
                             b_channelSenders.size(1) - 1, k_emlrtBCI);
      }
      b_channelSenders[static_cast<int>(cChannelSlots) - 1] = udpSender;
      cChannelSlots++;
    }
  }
  self->channelSenders.set_size(1, b_channelSenders.size(1));
  saturatedUnaryMinus = b_channelSenders.size(1);
  for (i = 0; i < saturatedUnaryMinus; i++) {
    self->channelSenders[i] = b_channelSenders[i];
  }
  return self;
}

//
// Arguments    : const coder::array<creal32_T, 2U> &channelData
//                const creal32_T timeStampForSending
// Return Type  : void
//
void UDPChannelSender::sendChannelData(
    const coder::array<creal32_T, 2U> &channelData,
    const creal32_T timeStampForSending) const
{
  static rtBoundsCheckInfo e_emlrtBCI{
      -1,                                 // iFirst
      -1,                                 // iLast
      81,                                 // lineNo
      55,                                 // colNo
      "self.channelIndices",              // aName
      "UDPChannelSender/sendChannelData", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/airspy_channelize/UDPChannelSender.m", // pName
      0                                                       // checkKind
  };
  static rtBoundsCheckInfo f_emlrtBCI{
      -1,                                 // iFirst
      -1,                                 // iLast
      82,                                 // lineNo
      55,                                 // colNo
      "self.channelSenders",              // aName
      "UDPChannelSender/sendChannelData", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/airspy_channelize/UDPChannelSender.m", // pName
      0                                                       // checkKind
  };
  static rtBoundsCheckInfo g_emlrtBCI{
      1,                                  // iFirst
      100,                                // iLast
      83,                                 // lineNo
      72,                                 // colNo
      "channelData",                      // aName
      "UDPChannelSender/sendChannelData", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/airspy_channelize/UDPChannelSender.m", // pName
      0                                                       // checkKind
  };
  static rtRunTimeErrorInfo h_emlrtRTEI{
      31,                                  // lineNo
      "ComplexSingleSamplesUDPSender/send" // fName
  };
  int i;
  i = channelIndices.size(1);
  for (int b_i{0}; b_i < i; b_i++) {
    creal32_T data_data[1025];
    int i1;
    int saturatedUnaryMinus;
    int x;
    int y;
    i1 = channelIndices.size(1);
    if (b_i + 1 > i1) {
      rtDynamicBoundsError(b_i + 1, 1, i1, e_emlrtBCI);
    }
    x = channelIndices[b_i];
    i1 = channelSenders.size(1) - 1;
    if (b_i > i1) {
      rtDynamicBoundsError(b_i, 0, i1, f_emlrtBCI);
    }
    if (x <= MIN_int32_T) {
      saturatedUnaryMinus = MAX_int32_T;
    } else {
      saturatedUnaryMinus = -x;
    }
    if (x < 0) {
      y = saturatedUnaryMinus;
    } else {
      y = x;
    }
    if (x <= MIN_int32_T) {
      saturatedUnaryMinus = MAX_int32_T;
    } else {
      saturatedUnaryMinus = -x;
    }
    if (x < 0) {
      i1 = saturatedUnaryMinus;
    } else {
      i1 = x;
    }
    if ((i1 < 1) || (i1 > 100)) {
      rtDynamicBoundsError(i1, 1, 100, g_emlrtBCI);
    }
    saturatedUnaryMinus = channelData.size(0);
    x = channelData.size(0) + 1;
    data_data[0] = timeStampForSending;
    for (i1 = 0; i1 < saturatedUnaryMinus; i1++) {
      data_data[i1 + 1] = channelData[i1 + channelData.size(0) * (y - 1)];
    }
    if (!(x == channelSenders[b_i].samplesPerFrame)) {
      c_rtErrorWithMessageID(h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
    }
    udpSenderSendComplex(channelSenders[b_i].udpSender, &data_data[0],
                         channelSenders[b_i].samplesPerFrame);
  }
}

//
// File trailer for UDPChannelSender.cpp
//
// [EOF]
//
