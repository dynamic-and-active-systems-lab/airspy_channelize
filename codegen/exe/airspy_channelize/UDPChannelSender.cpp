//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: UDPChannelSender.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Apr-2023 15:58:05
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
#include "omp.h"
#include "udp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <string>

// Function Declarations
static void rtIntegerError(const double aInteger,
                           const rtDoubleCheckInfo *aInfo);

// Function Definitions
//
// Arguments    : const double aInteger
//                const rtDoubleCheckInfo *aInfo
// Return Type  : void
//
static void rtIntegerError(const double aInteger,
                           const rtDoubleCheckInfo *aInfo)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "Expected a value representable in the C type \'int\'. Found ")
   << aInteger)
      << " instead.";
  outStream << "\n";
  ((((outStream << "Error in ") << aInfo->fName) << " (line ") << aInfo->lineNo)
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
      -1,                                                 // iFirst
      -1,                                                 // iLast
      30,                                                 // lineNo
      45,                                                 // colNo
      "channelsUsed",                                     // aName
      "UDPChannelSender/UDPChannelSender",                // fName
      "H:\\repos\\airspy_channelize\\UDPChannelSender.m", // pName
      0                                                   // checkKind
  };
  static rtBoundsCheckInfo f_emlrtBCI{
      -1,                                                 // iFirst
      -1,                                                 // iLast
      46,                                                 // lineNo
      32,                                                 // colNo
      "channelSenders",                                   // aName
      "UDPChannelSender/UDPChannelSender",                // fName
      "H:\\repos\\airspy_channelize\\UDPChannelSender.m", // pName
      0                                                   // checkKind
  };
  static rtBoundsCheckInfo g_emlrtBCI{
      -1,                                                 // iFirst
      -1,                                                 // iLast
      51,                                                 // lineNo
      45,                                                 // colNo
      "channelsUsed",                                     // aName
      "UDPChannelSender/UDPChannelSender",                // fName
      "H:\\repos\\airspy_channelize\\UDPChannelSender.m", // pName
      0                                                   // checkKind
  };
  static rtBoundsCheckInfo h_emlrtBCI{
      -1,                                                 // iFirst
      -1,                                                 // iLast
      62,                                                 // lineNo
      37,                                                 // colNo
      "self.channelIndices(nextChannelSlot)",             // aName
      "UDPChannelSender/UDPChannelSender",                // fName
      "H:\\repos\\airspy_channelize\\UDPChannelSender.m", // pName
      0                                                   // checkKind
  };
  static rtBoundsCheckInfo i_emlrtBCI{
      -1,                                                 // iFirst
      -1,                                                 // iLast
      63,                                                 // lineNo
      32,                                                 // colNo
      "channelSenders",                                   // aName
      "UDPChannelSender/UDPChannelSender",                // fName
      "H:\\repos\\airspy_channelize\\UDPChannelSender.m", // pName
      0                                                   // checkKind
  };
  static rtBoundsCheckInfo j_emlrtBCI{
      -1,                                                 // iFirst
      -1,                                                 // iLast
      71,                                                 // lineNo
      41,                                                 // colNo
      "self.channelIndices(nextChannelSlot)",             // aName
      "UDPChannelSender/UDPChannelSender",                // fName
      "H:\\repos\\airspy_channelize\\UDPChannelSender.m", // pName
      0                                                   // checkKind
  };
  static rtBoundsCheckInfo k_emlrtBCI{
      -1,                                                 // iFirst
      -1,                                                 // iLast
      72,                                                 // lineNo
      36,                                                 // colNo
      "channelSenders",                                   // aName
      "UDPChannelSender/UDPChannelSender",                // fName
      "H:\\repos\\airspy_channelize\\UDPChannelSender.m", // pName
      0                                                   // checkKind
  };
  static rtDoubleCheckInfo b_emlrtDCI{
      39,                                                 // lineNo
      44,                                                 // colNo
      "UDPChannelSender/UDPChannelSender",                // fName
      "H:\\repos\\airspy_channelize\\UDPChannelSender.m", // pName
      1                                                   // checkKind
  };
  static rtDoubleCheckInfo c_emlrtDCI{
      40,                                                 // lineNo
      43,                                                 // colNo
      "UDPChannelSender/UDPChannelSender",                // fName
      "H:\\repos\\airspy_channelize\\UDPChannelSender.m", // pName
      1                                                   // checkKind
  };
  static rtRunTimeErrorInfo p_emlrtRTEI{
      124,                   // lineNo
      "validator_check_size" // fName
  };
  static rtRunTimeErrorInfo q_emlrtRTEI{
      52,                                 // lineNo
      "UDPChannelSender/UDPChannelSender" // fName
  };
  static rtRunTimeErrorInfo r_emlrtRTEI{
      53,                                 // lineNo
      "UDPChannelSender/UDPChannelSender" // fName
  };
  ComplexSingleSamplesUDPSender udpSender;
  UDPChannelSender *self;
  coder::array<ComplexSingleSamplesUDPSender, 2U> b_channelSenders;
  coder::array<ComplexSingleSamplesUDPSender, 2U> c__in;
  coder::array<int, 2U> _in;
  coder::array<int, 2U> b__in;
  int absChannelIndex;
  unsigned int cChannelSlots;
  int i;
  int ibtile;
  int jcol;
  int outsize_idx_1;
  int sizes_idx_1;
  char b_tmp_data[10];
  char tmp_data[10];
  boolean_T b;
  boolean_T b1;
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
      rtDynamicBoundsError(b_i + 1, 1, channelsUsed.size(1), &e_emlrtBCI);
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
    rtIntegerError(static_cast<double>(cChannelSlots), &b_emlrtDCI);
  }
  _in.set_size(1, static_cast<int>(cChannelSlots));
  outsize_idx_1 = static_cast<int>(cChannelSlots);
  for (i = 0; i < outsize_idx_1; i++) {
    _in[i] = 0;
  }
  coder::internal::validator_check_size(_in, b__in);
  self->channelIndices.set_size(1, b__in.size(1));
  outsize_idx_1 = b__in.size(1);
  for (i = 0; i < outsize_idx_1; i++) {
    self->channelIndices[i] = b__in[i];
  }
  b_channelSenders.set_size(1, b_channelSenders.size(1));
  if (static_cast<double>(cChannelSlots) != static_cast<int>(cChannelSlots)) {
    rtIntegerError(static_cast<double>(cChannelSlots), &c_emlrtDCI);
  }
  b_channelSenders.set_size(b_channelSenders.size(0),
                            static_cast<int>(cChannelSlots));
  //  We stuff in the first channel first into all slots to keep code happy.
  //  Coder wants all cells to have a value and the code in this function is too
  //  complicated for it to understand that is the case.
  udpSender.samplesPerFrame = 1025.0;
  i = channelsUsed[0];
  if (i <= MIN_int32_T) {
    outsize_idx_1 = MAX_int32_T;
  } else {
    outsize_idx_1 = -i;
  }
  if (channelsUsed[0] >= 0) {
    outsize_idx_1 = channelsUsed[0];
  }
  if (outsize_idx_1 < -2147483647) {
    outsize_idx_1 = MIN_int32_T;
  } else {
    outsize_idx_1--;
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
  if (cChannelSlots > 4294967294U) {
    coder::check_forloop_overflow_error();
  }
  i = static_cast<int>(cChannelSlots);
  for (int b_i{0}; b_i < i; b_i++) {
    if (b_i > b_channelSenders.size(1) - 1) {
      rtDynamicBoundsError(b_i, 0, b_channelSenders.size(1) - 1, &f_emlrtBCI);
    }
    b_channelSenders[b_i] = udpSender;
  }
  cChannelSlots = 1U;
  i = channelsUsed.size(1);
  for (int b_i{0}; b_i < i; b_i++) {
    if (b_i + 1 > channelsUsed.size(1)) {
      rtDynamicBoundsError(b_i + 1, 1, channelsUsed.size(1), &g_emlrtBCI);
    }
    if (channelsUsed[b_i] == 0) {
      c_rtErrorWithMessageID(q_emlrtRTEI.fName, q_emlrtRTEI.lineNo);
    }
    if ((channelsUsed[b_i] < -100) || (channelsUsed[b_i] > 100)) {
      c_rtErrorWithMessageID(r_emlrtRTEI.fName, r_emlrtRTEI.lineNo);
    }
    jcol = channelsUsed[b_i];
    if (jcol <= MIN_int32_T) {
      outsize_idx_1 = MAX_int32_T;
    } else {
      outsize_idx_1 = -jcol;
    }
    if (channelsUsed[b_i] < 0) {
      absChannelIndex = outsize_idx_1;
    } else {
      absChannelIndex = channelsUsed[b_i];
    }
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
    jcol = absChannelIndex;
    if (absChannelIndex < 0) {
      jcol = 0;
    }
    ibtile = outsize_idx_1;
    if (outsize_idx_1 < 0) {
      ibtile = 0;
    }
    printf("Setting up main channel %u port %u\n",
           static_cast<unsigned int>(jcol), static_cast<unsigned int>(ibtile));
    fflush(stdout);
    udpSender.samplesPerFrame = 1025.0;
    udpSender.udpSender = udpSenderSetup(outsize_idx_1);
    if (udpSender.udpSender <= 0) {
      rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
    }
    b__in.set_size(1, self->channelIndices.size(1));
    outsize_idx_1 = self->channelIndices.size(1);
    for (jcol = 0; jcol < outsize_idx_1; jcol++) {
      b__in[jcol] = self->channelIndices[jcol];
    }
    if ((static_cast<int>(cChannelSlots) < 1) ||
        (static_cast<int>(cChannelSlots) > b__in.size(1))) {
      rtDynamicBoundsError(static_cast<int>(cChannelSlots), 1, b__in.size(1),
                           &h_emlrtBCI);
    }
    b__in[static_cast<int>(cChannelSlots) - 1] = absChannelIndex;
    _in.set_size(1, b__in.size(1));
    outsize_idx_1 = b__in.size(0) * b__in.size(1) - 1;
    for (jcol = 0; jcol <= outsize_idx_1; jcol++) {
      _in[jcol] = b__in[jcol];
    }
    coder::internal::validator_check_size(_in, b__in);
    self->channelIndices.set_size(1, b__in.size(1));
    outsize_idx_1 = b__in.size(1);
    for (jcol = 0; jcol < outsize_idx_1; jcol++) {
      self->channelIndices[jcol] = b__in[jcol];
    }
    if ((static_cast<int>(cChannelSlots) - 1 < 0) ||
        (static_cast<int>(cChannelSlots) - 1 > b_channelSenders.size(1) - 1)) {
      rtDynamicBoundsError(static_cast<int>(cChannelSlots) - 1, 0,
                           b_channelSenders.size(1) - 1, &i_emlrtBCI);
    }
    b_channelSenders[static_cast<int>(cChannelSlots) - 1] = udpSender;
    cChannelSlots++;
    if (channelsUsed[b_i] < 0) {
      //  Set up secondary channel output
      jcol = absChannelIndex;
      if (absChannelIndex < 0) {
        jcol = 0;
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
             static_cast<unsigned int>(jcol),
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
      b__in.set_size(1, self->channelIndices.size(1));
      outsize_idx_1 = self->channelIndices.size(1);
      for (jcol = 0; jcol < outsize_idx_1; jcol++) {
        b__in[jcol] = self->channelIndices[jcol];
      }
      if ((static_cast<int>(cChannelSlots) < 1) ||
          (static_cast<int>(cChannelSlots) > b__in.size(1))) {
        rtDynamicBoundsError(static_cast<int>(cChannelSlots), 1, b__in.size(1),
                             &j_emlrtBCI);
      }
      b__in[static_cast<int>(cChannelSlots) - 1] = absChannelIndex;
      _in.set_size(1, b__in.size(1));
      outsize_idx_1 = b__in.size(0) * b__in.size(1) - 1;
      for (jcol = 0; jcol <= outsize_idx_1; jcol++) {
        _in[jcol] = b__in[jcol];
      }
      coder::internal::validator_check_size(_in, b__in);
      self->channelIndices.set_size(1, b__in.size(1));
      outsize_idx_1 = b__in.size(1);
      for (jcol = 0; jcol < outsize_idx_1; jcol++) {
        self->channelIndices[jcol] = b__in[jcol];
      }
      if ((static_cast<int>(cChannelSlots) - 1 < 0) ||
          (static_cast<int>(cChannelSlots) - 1 >
           b_channelSenders.size(1) - 1)) {
        rtDynamicBoundsError(static_cast<int>(cChannelSlots) - 1, 0,
                             b_channelSenders.size(1) - 1, &k_emlrtBCI);
      }
      b_channelSenders[static_cast<int>(cChannelSlots) - 1] = udpSender;
      cChannelSlots++;
    }
  }
  b = (b_channelSenders.size(1) == 1);
  b1 = (b_channelSenders.size(1) == 0);
  if (b) {
    sizes_idx_1 = 1;
  } else {
    sizes_idx_1 = b_channelSenders.size(1);
  }
  if ((!b1) && (!b) && (b_channelSenders.size(1) != sizes_idx_1)) {
    int b_tmp_size[2];
    int tmp_size[2];
    coder::int2str(static_cast<double>(b_channelSenders.size(1)), tmp_data,
                   tmp_size);
    coder::int2str(sizes_idx_1, b_tmp_data, b_tmp_size);
    rtErrorWithMessageID(std::string(&tmp_data[0], tmp_size[1]),
                         std::string(&b_tmp_data[0], b_tmp_size[1]), "2",
                         h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
  }
  if (b) {
    outsize_idx_1 = b_channelSenders.size(1) * sizes_idx_1;
    c__in.set_size(1, outsize_idx_1);
    if ((b_channelSenders.size(1) != 0) && (outsize_idx_1 != 0)) {
      outsize_idx_1 = b_channelSenders.size(1);
      if (sizes_idx_1 > 2147483646) {
        coder::b_check_forloop_overflow_error();
      }
      for (absChannelIndex = 0; absChannelIndex < sizes_idx_1;
           absChannelIndex++) {
        ibtile = absChannelIndex * outsize_idx_1;
        if (outsize_idx_1 > 2147483646) {
          coder::b_check_forloop_overflow_error();
        }
        for (jcol = 0; jcol < outsize_idx_1; jcol++) {
          c__in[ibtile + jcol] = b_channelSenders[jcol];
        }
      }
    }
  } else if (b1) {
    c__in.set_size(1, sizes_idx_1);
    if (sizes_idx_1 != b_channelSenders.size(1)) {
      h_rtErrorWithMessageID(p_emlrtRTEI.fName, p_emlrtRTEI.lineNo);
    }
    if (sizes_idx_1 > 2147483646) {
      coder::b_check_forloop_overflow_error();
    }
    for (int b_i{0}; b_i < sizes_idx_1; b_i++) {
      c__in[b_i] = b_channelSenders[b_i];
    }
  } else {
    outsize_idx_1 = 1;
    if (b_channelSenders.size(1) > 1) {
      outsize_idx_1 = b_channelSenders.size(1);
    }
    ibtile = b_channelSenders.size(1);
    if (ibtile >= outsize_idx_1) {
      outsize_idx_1 = ibtile;
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
      83,                                                 // lineNo
      72,                                                 // colNo
      "channelData",                                      // aName
      "UDPChannelSender/sendChannelData",                 // fName
      "H:\\repos\\airspy_channelize\\UDPChannelSender.m", // pName
      0                                                   // checkKind
  };
  static rtBoundsCheckInfo f_emlrtBCI{
      -1,                                                 // iFirst
      -1,                                                 // iLast
      82,                                                 // lineNo
      55,                                                 // colNo
      "self.channelSenders",                              // aName
      "UDPChannelSender/sendChannelData",                 // fName
      "H:\\repos\\airspy_channelize\\UDPChannelSender.m", // pName
      0                                                   // checkKind
  };
  static rtBoundsCheckInfo g_emlrtBCI{
      -1,                                                 // iFirst
      -1,                                                 // iLast
      81,                                                 // lineNo
      55,                                                 // colNo
      "self.channelIndices",                              // aName
      "UDPChannelSender/sendChannelData",                 // fName
      "H:\\repos\\airspy_channelize\\UDPChannelSender.m", // pName
      0                                                   // checkKind
  };
  static rtRunTimeErrorInfo p_emlrtRTEI{
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
      c_rtErrorWithMessageID(p_emlrtRTEI.fName, p_emlrtRTEI.lineNo);
    }
    udpSenderSendComplex(channelSenders[b_i].udpSender, &data_data[0], 1025.0);
  }
}

//
// File trailer for UDPChannelSender.cpp
//
// [EOF]
//
