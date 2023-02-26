//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: UDPChannelSender.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 26-Feb-2023 09:39:03
//

// Include Files
#include "UDPChannelSender.h"
#include "ComplexSingleSamplesUDPSender.h"
#include "airspy_channelize_data.h"
#include "airspy_channelize_rtwutil.h"
#include "airspy_channelize_types.h"
#include "eml_int_forloop_overflow_check.h"
#include "int2str.h"
#include "rt_nonfinite.h"
#include "validator_check_size.h"
#include "coder_array.h"
#include "udp.h"
#include <stdio.h>
#include <string>

// Function Definitions
//
// Arguments    : coder::array<int, 2U> &channelsUsed
// Return Type  : UDPChannelSender *
//
UDPChannelSender *UDPChannelSender::init(coder::array<int, 2U> &channelsUsed)
{
  static rtBoundsCheckInfo e_emlrtBCI{
      -1,                                                 // iFirst
      -1,                                                 // iLast
      32,                                                 // lineNo
      45,                                                 // colNo
      "channelsUsed",                                     // aName
      "UDPChannelSender/UDPChannelSender",                // fName
      "H:\\repos\\airspy_channelize\\UDPChannelSender.m", // pName
      0                                                   // checkKind
  };
  static rtBoundsCheckInfo f_emlrtBCI{
      -1,                                                 // iFirst
      -1,                                                 // iLast
      49,                                                 // lineNo
      37,                                                 // colNo
      "self.channelIndices(i)",                           // aName
      "UDPChannelSender/UDPChannelSender",                // fName
      "H:\\repos\\airspy_channelize\\UDPChannelSender.m", // pName
      0                                                   // checkKind
  };
  static rtBoundsCheckInfo g_emlrtBCI{
      -1,                                                 // iFirst
      -1,                                                 // iLast
      50,                                                 // lineNo
      32,                                                 // colNo
      "channelSenders",                                   // aName
      "UDPChannelSender/UDPChannelSender",                // fName
      "H:\\repos\\airspy_channelize\\UDPChannelSender.m", // pName
      0                                                   // checkKind
  };
  static rtRunTimeErrorInfo o_emlrtRTEI{
      33,                                 // lineNo
      "UDPChannelSender/UDPChannelSender" // fName
  };
  static rtRunTimeErrorInfo p_emlrtRTEI{
      34,                                 // lineNo
      "UDPChannelSender/UDPChannelSender" // fName
  };
  UDPChannelSender *self;
  coder::array<ComplexSingleSamplesUDPSender, 2U> b_channelSenders;
  coder::array<ComplexSingleSamplesUDPSender, 2U> c__in;
  coder::array<int, 2U> _in;
  coder::array<int, 2U> b__in;
  int absChannelIndex;
  int i;
  int jtilecol;
  int outsize_idx_1;
  int sizes_idx_1;
  char b_tmp_data[10];
  char tmp_data[10];
  boolean_T overflow;
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
  //  Pre-allocate storage for coder
  _in.set_size(1, channelsUsed.size(1));
  outsize_idx_1 = channelsUsed.size(1);
  for (i = 0; i < outsize_idx_1; i++) {
    _in[i] = 0;
  }
  coder::internal::validator_check_size(_in, b__in);
  self->channelIndices.set_size(1, b__in.size(1));
  outsize_idx_1 = b__in.size(1);
  for (i = 0; i < outsize_idx_1; i++) {
    self->channelIndices[i] = b__in[i];
  }
  b_channelSenders.set_size(1, channelsUsed.size(1));
  //  100 max channels * 2 for secondary ports
  i = channelsUsed.size(1);
  for (int b_i{0}; b_i < i; b_i++) {
    ComplexSingleSamplesUDPSender udpSender;
    if (b_i + 1 > channelsUsed.size(1)) {
      rtDynamicBoundsError(b_i + 1, 1, channelsUsed.size(1), &e_emlrtBCI);
    }
    if (channelsUsed[b_i] == 0) {
      c_rtErrorWithMessageID(o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
    }
    if ((channelsUsed[b_i] < -100) || (channelsUsed[b_i] > 100)) {
      c_rtErrorWithMessageID(p_emlrtRTEI.fName, p_emlrtRTEI.lineNo);
    }
    jtilecol = channelsUsed[b_i];
    if (jtilecol <= MIN_int32_T) {
      outsize_idx_1 = MAX_int32_T;
    } else {
      outsize_idx_1 = -jtilecol;
    }
    if (channelsUsed[b_i] < 0) {
      absChannelIndex = outsize_idx_1;
    } else {
      absChannelIndex = channelsUsed[b_i];
    }
    if (channelsUsed[b_i] > 0) {
      //  Set up main channel output
      if (absChannelIndex < -2147483647) {
        outsize_idx_1 = MIN_int32_T;
      } else {
        outsize_idx_1 = absChannelIndex - 1;
      }
      if (outsize_idx_1 > 1073741823) {
        outsize_idx_1 = MAX_int32_T;
      } else if (outsize_idx_1 <= -1073741824) {
        outsize_idx_1 = MIN_int32_T;
      } else {
        outsize_idx_1 <<= 1;
      }
      if (outsize_idx_1 > 2147463647) {
        outsize_idx_1 = MAX_int32_T;
      } else {
        outsize_idx_1 += 20000;
      }
      if (absChannelIndex < 0) {
        absChannelIndex = 0;
      }
      jtilecol = outsize_idx_1;
      if (outsize_idx_1 < 0) {
        jtilecol = 0;
      }
      printf("Setting up main channel %u port %u\n",
             static_cast<unsigned int>(absChannelIndex),
             static_cast<unsigned int>(jtilecol));
      fflush(stdout);
      udpSender.samplesPerFrame = 1025.0;
      udpSender.udpSender = udpSenderSetup(outsize_idx_1);
      if (udpSender.udpSender <= 0) {
        rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
      }
    } else {
      //  Set up secondary channel output
      jtilecol = absChannelIndex;
      if (absChannelIndex < 0) {
        jtilecol = 0;
      }
      if (absChannelIndex < -2147483647) {
        outsize_idx_1 = MIN_int32_T;
      } else {
        outsize_idx_1 = absChannelIndex - 1;
      }
      if (outsize_idx_1 > 1073741823) {
        outsize_idx_1 = MAX_int32_T;
      } else if (outsize_idx_1 <= -1073741824) {
        outsize_idx_1 = MIN_int32_T;
      } else {
        outsize_idx_1 <<= 1;
      }
      if (outsize_idx_1 > 2147463647) {
        outsize_idx_1 = MAX_int32_T;
      } else {
        outsize_idx_1 += 20000;
      }
      if (outsize_idx_1 > 2147483646) {
        outsize_idx_1 = MAX_int32_T;
      } else {
        outsize_idx_1++;
      }
      if (outsize_idx_1 < 0) {
        outsize_idx_1 = 0;
      }
      printf("Setting up secondary channel %u port %u\n",
             static_cast<unsigned int>(jtilecol),
             static_cast<unsigned int>(outsize_idx_1));
      fflush(stdout);
      udpSender.samplesPerFrame = 1025.0;
      if (absChannelIndex < -2147483647) {
        outsize_idx_1 = MIN_int32_T;
      } else {
        outsize_idx_1 = absChannelIndex - 1;
      }
      if (outsize_idx_1 > 1073741823) {
        outsize_idx_1 = MAX_int32_T;
      } else if (outsize_idx_1 <= -1073741824) {
        outsize_idx_1 = MIN_int32_T;
      } else {
        outsize_idx_1 <<= 1;
      }
      if (outsize_idx_1 > 2147463647) {
        outsize_idx_1 = MAX_int32_T;
      } else {
        outsize_idx_1 += 20000;
      }
      if (outsize_idx_1 > 2147483646) {
        outsize_idx_1 = MAX_int32_T;
      } else {
        outsize_idx_1++;
      }
      udpSender.udpSender = udpSenderSetup(outsize_idx_1);
      if (udpSender.udpSender <= 0) {
        rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
      }
    }
    b__in.set_size(1, self->channelIndices.size(1));
    outsize_idx_1 = self->channelIndices.size(1);
    for (jtilecol = 0; jtilecol < outsize_idx_1; jtilecol++) {
      b__in[jtilecol] = self->channelIndices[jtilecol];
    }
    if (b_i + 1 > b__in.size(1)) {
      rtDynamicBoundsError(b_i + 1, 1, b__in.size(1), &f_emlrtBCI);
    }
    b__in[b_i] = channelsUsed[b_i];
    _in.set_size(1, b__in.size(1));
    outsize_idx_1 = b__in.size(0) * b__in.size(1) - 1;
    for (jtilecol = 0; jtilecol <= outsize_idx_1; jtilecol++) {
      _in[jtilecol] = b__in[jtilecol];
    }
    coder::internal::validator_check_size(_in, b__in);
    self->channelIndices.set_size(1, b__in.size(1));
    outsize_idx_1 = b__in.size(1);
    for (jtilecol = 0; jtilecol < outsize_idx_1; jtilecol++) {
      self->channelIndices[jtilecol] = b__in[jtilecol];
    }
    if (b_i > b_channelSenders.size(1) - 1) {
      rtDynamicBoundsError(b_i, 0, b_channelSenders.size(1) - 1, &g_emlrtBCI);
    }
    b_channelSenders[b_i] = udpSender;
  }
  overflow = (b_channelSenders.size(1) == 1);
  if (overflow) {
    sizes_idx_1 = 1;
  } else {
    sizes_idx_1 = b_channelSenders.size(1);
  }
  if (!overflow) {
    if (b_channelSenders.size(1) != sizes_idx_1) {
      int b_tmp_size[2];
      int tmp_size[2];
      coder::int2str(static_cast<double>(b_channelSenders.size(1)), tmp_data,
                     tmp_size);
      coder::int2str(sizes_idx_1, b_tmp_data, b_tmp_size);
      rtErrorWithMessageID(std::string(&tmp_data[0], tmp_size[1]),
                           std::string(&b_tmp_data[0], b_tmp_size[1]), "2",
                           h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
    }
    outsize_idx_1 = 1;
    if (b_channelSenders.size(1) > 1) {
      outsize_idx_1 = b_channelSenders.size(1);
    }
    absChannelIndex = b_channelSenders.size(1);
    if (absChannelIndex >= outsize_idx_1) {
      outsize_idx_1 = absChannelIndex;
    }
    if (sizes_idx_1 > outsize_idx_1) {
      f_rtErrorWithMessageID(f_emlrtRTEI.fName, f_emlrtRTEI.lineNo);
    }
    if (sizes_idx_1 != b_channelSenders.size(1)) {
      g_rtErrorWithMessageID(g_emlrtRTEI.fName, g_emlrtRTEI.lineNo);
    }
    c__in.set_size(1, sizes_idx_1);
    for (i = 0; i < sizes_idx_1; i++) {
      c__in[i] = b_channelSenders[i];
    }
  } else {
    outsize_idx_1 = b_channelSenders.size(1) * sizes_idx_1;
    c__in.set_size(1, outsize_idx_1);
    if (outsize_idx_1 != 0) {
      outsize_idx_1 = b_channelSenders.size(1);
      if (sizes_idx_1 > 2147483646) {
        coder::check_forloop_overflow_error();
      }
      overflow = (b_channelSenders.size(1) > 2147483646);
      for (jtilecol = 0; jtilecol < sizes_idx_1; jtilecol++) {
        absChannelIndex = jtilecol * outsize_idx_1;
        if (overflow) {
          coder::check_forloop_overflow_error();
        }
        for (int b_i{0}; b_i < outsize_idx_1; b_i++) {
          c__in[absChannelIndex + b_i] = b_channelSenders[b_i];
        }
      }
    }
  }
  self->channelSenders.set_size(1, c__in.size(1));
  outsize_idx_1 = c__in.size(1);
  for (i = 0; i < outsize_idx_1; i++) {
    self->channelSenders[i] = c__in[i];
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
      1,                                                  // iFirst
      100,                                                // iLast
      59,                                                 // lineNo
      72,                                                 // colNo
      "channelData",                                      // aName
      "UDPChannelSender/sendChannelData",                 // fName
      "H:\\repos\\airspy_channelize\\UDPChannelSender.m", // pName
      0                                                   // checkKind
  };
  static rtBoundsCheckInfo f_emlrtBCI{
      -1,                                                 // iFirst
      -1,                                                 // iLast
      58,                                                 // lineNo
      55,                                                 // colNo
      "self.channelSenders",                              // aName
      "UDPChannelSender/sendChannelData",                 // fName
      "H:\\repos\\airspy_channelize\\UDPChannelSender.m", // pName
      0                                                   // checkKind
  };
  static rtBoundsCheckInfo g_emlrtBCI{
      -1,                                                 // iFirst
      -1,                                                 // iLast
      57,                                                 // lineNo
      55,                                                 // colNo
      "self.channelIndices",                              // aName
      "UDPChannelSender/sendChannelData",                 // fName
      "H:\\repos\\airspy_channelize\\UDPChannelSender.m", // pName
      0                                                   // checkKind
  };
  static rtRunTimeErrorInfo o_emlrtRTEI{
      31,                                  // lineNo
      "ComplexSingleSamplesUDPSender/send" // fName
  };
  int i;
  i = channelIndices.size(1);
  for (int b_i{0}; b_i < i; b_i++) {
    creal32_T data_data[1025];
    int saturatedUnaryMinus;
    int x;
    int y;
    saturatedUnaryMinus = channelIndices.size(1);
    if (b_i + 1 > saturatedUnaryMinus) {
      rtDynamicBoundsError(b_i + 1, 1, saturatedUnaryMinus, &g_emlrtBCI);
    }
    x = channelIndices[b_i];
    saturatedUnaryMinus = channelSenders.size(1) - 1;
    if (b_i > saturatedUnaryMinus) {
      rtDynamicBoundsError(b_i, 0, saturatedUnaryMinus, &f_emlrtBCI);
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
    if (x >= 0) {
      saturatedUnaryMinus = x;
    }
    if ((saturatedUnaryMinus < 1) || (saturatedUnaryMinus > 100)) {
      rtDynamicBoundsError(saturatedUnaryMinus, 1, 100, &e_emlrtBCI);
    }
    data_data[0] = timeStampForSending;
    for (saturatedUnaryMinus = 0; saturatedUnaryMinus < 1024;
         saturatedUnaryMinus++) {
      data_data[saturatedUnaryMinus + 1] =
          channelData[saturatedUnaryMinus + 1024 * (y - 1)];
    }
    if (!(channelSenders[b_i].samplesPerFrame == 1025.0)) {
      c_rtErrorWithMessageID(o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
    }
    udpSenderSendComplex(channelSenders[b_i].udpSender, &data_data[0], 1025.0);
  }
}

//
// File trailer for UDPChannelSender.cpp
//
// [EOF]
//
