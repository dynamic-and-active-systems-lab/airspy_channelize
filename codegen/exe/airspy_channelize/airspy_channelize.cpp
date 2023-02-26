//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: airspy_channelize.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 26-Feb-2023 12:01:14
//

// Include Files
#include "airspy_channelize.h"
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "Channelizer.h"
#include "ComplexSingleSamplesUDPReceiver.h"
#include "UDPChannelSender.h"
#include "airspy_channelize_data.h"
#include "airspy_channelize_initialize.h"
#include "airspy_channelize_rtwutil.h"
#include "airspy_channelize_types.h"
#include "datetime.h"
#include "rt_nonfinite.h"
#include "tic.h"
#include "toc.h"
#include "coder_array.h"
#include "time.h"
#include "udp.h"
#include <cmath>
#include <cstddef>
#include <cstring>
#include <stdio.h>

// Function Definitions
//
// AIRSPYFHCHANNELIZE100 receives complex (IQ) data over a UDP connection from
// an SDR (single precision), channelizes it, and servers it
// up over 100 diferent UDP ports.
//    This function is designed specifically to receive incoming data that
//    has been passed to it via an interanl UDP connection. The program expects
//    128 sample frames of 8-byte complex samples (4 real, 4 imaginary) to be
//    sent over UDP. The program receives that data and fills a buffer until
//    enough samples have been received that 1024 samples will be generated
//    on the output channels at the decimated sample rate.
//
//    Once the buffer fills, the data is channelized and
//    served via UDP to corresponding ports. The function opens a command
//    channel so that integers can be passed to enable basic control
//    authority over the program operation, enabling starting of data
//    processing, pausing, and termination of the program.
//
//    Normal channelization allows for decimation rates and the number of
//    channels to be different. This function holds them equal. Therefore,
//    the decimated rate for each channel is equal to the raw airspy sample
//    rate divided by the number of channels. Additionally, the center
//    frequencies of each channel is therefore
//
//    Data sent over the UDP output channels are single valued complex
//    frames. Each output frame contains 1024 complex values, or 2048
//    individual single precision values. Each frame also contains a
//    timestamp encoded into a complex number in the first element of the
//    frame. The received data frame therefore contains 1025 complex values.
//    The timestamp on each frame is associate with the time of arrival of
//    the first sample in the frame.
//
//    The timestamp is a precision posixtime value in milliseconds. The
//    timestamp is transmitted as a single precision complex value. The
//    imaginary part of this timestamp contains the first 7 digits of the
//    time in milliseconds. The real part contains the upper digits (>=8) of
//    the timestamp. See the help for int2singlecomplex and singlecomplex2int
//    for more information on this transmission standard.
//
//    INPUTS:
//        channelsUsed    Look at UDPChannelSender.m for an explanation of how
//                        this works and how ports are allocated.
//
// Notes:
//        ABOUT CHANNEL CENTER FREQUENCIES:
//        Matlab provides the centerFrequencies function that accepts a
//        channelizer object and a sample rate, and then specifies the
//        center frequencies of the associated channel. This list however is
//        centered at zero and provides negative frequencies. For example a
//        channelizer with Fs = 48000 and a decimation factor of 3 would
//        report center frequencies [-24000 -12000 0 12000]. If the fvtool is
//        used on this channelizer (with the legend turned on) the center
//        frequencies would be [0 12000 -24000 -12000] for filteres 1-4. The
//        shifting here reflects a inconsistency in Matlab's channel
//        reporting. The channelizer outputs follow the latter order, and as
//        such, so to do the UDP port outputs in this function.
//        Because the  number of chanels and the decimation are the same,
//        the frequency of these channels are -Fs/nc*floor(nc/2)<fc<Fs/2,
//        (where nc is the number of channels), if nc is odd. For even nc
//        -Fs/2 < fc < Fs/2-Fs/nc. In both cases the frequency steps are
//        Fs/nc. This was determined by using the centerFrequencies.m
//        function on example channelizer objects. If using the
//        centerFrequencies output the circshift command can be used to get
//        the correct order of channel frequency. For example:
//        circshift(centerFrequencies(channizerObject,48000),ceil(numChannels/2))
//
//        ABOUT INCOMING DATA:
//        An Airspy connected to the machine via USB is received using
//        the airspyhf_rx or airspy_rx executable. Using the program with the
//        '-r stdout' option allows the data to be piped to another program
//        with the | character. Netcat can then be use to provide the data to
//        this function via UDP. An example commandline input would be
//
//        /usr/local/bin/airspyhf_rx -f 91.7 -m on -a 912000 -n 9120000 -r
//        stdout -g on -l high -t 0 | netcat -u localhost 10000
//
//        Note that this system call must executed after this function is
//        already running or a 'Connection refused' error will occur in
//        terminal.
// -------------------------------------------------------------------------
// Author:    Michael Shafer
// Date:      2022-01-18
// -------------------------------------------------------------------------
//
// Arguments    : const coder::array<int, 2U> &channelsUsed
// Return Type  : void
//
void airspy_channelize(const coder::array<int, 2U> &channelsUsed)
{
  static coder::dsp::AsyncBuffer dataBufferFIFO;
  ComplexSingleSamplesUDPReceiver udpReceiver;
  UDPChannelSender udpChannelSender;
  coder::datetime b_this;
  coder::dsp::Channelizer channelizer;
  coder::array<creal32_T, 2U> channelData;
  coder::array<creal32_T, 1U> varargin_1;
  coder::array<int, 2U> b_channelsUsed;
  creal32_T dataReceived_data[2039];
  double startTimeStamp;
  double tocElapsedSubtract;
  unsigned long long totalSampsReceived;
  int loop_ub;
  int qY;
  unsigned int sampsTransmitted;
  if (!isInitialized_airspy_channelize) {
    airspy_channelize_initialize();
  }
  //  Decimation is currently set to equal nChannels. Must be a factor of
  //  rawFrameLength Must be a multiple of 128
  totalSampsReceived = 0ULL;
  sampsTransmitted = 0U;
  startTimeStamp = 0.0;
  tocElapsedSubtract = 0.0;
  dataBufferFIFO.pBuffer.NumChannels = -1;
  dataBufferFIFO.pBuffer.isInitialized = 0;
  dataBufferFIFO.pBuffer.matlabCodegenIsDeleted = false;
  dataBufferFIFO.matlabCodegenIsDeleted = false;
  dataBufferFIFO.write();
  //  Write a single value so the number of channels is specified for coder.
  //  Specify complex single for airspy data
  dataBufferFIFO.read();
  //  Read out that single sample to empty the buffer.
  channelizer.numChannels = -1;
  channelizer.isInitialized = 0;
  channelizer.matlabCodegenIsDeleted = false;
  //  The value for sampleFrameSize (2039) must exactly what csdr is sending per
  //  frame
  udpReceiver.samplesPerFrame = 2039.0;
  udpReceiver.udpReceiver = udpReceiverSetup(10000.0);
  if (udpReceiver.udpReceiver <= 0) {
    rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  b_channelsUsed.set_size(1, channelsUsed.size(1));
  loop_ub = channelsUsed.size(0) * channelsUsed.size(1) - 1;
  for (qY = 0; qY <= loop_ub; qY++) {
    b_channelsUsed[qY] = channelsUsed[qY];
  }
  udpChannelSender.init(b_channelsUsed);
  //  + 1 for timestamp
  //  Start by clearing any stale data
  udpReceiverClear(udpReceiver.udpReceiver);
  printf("Waiting for new udp data\n");
  fflush(stdout);
  coder::tic();
  while (1) {
    double tocBasedElapseTime;
    unsigned long long b_qY;
    udpReceiver.receive(dataReceived_data, &loop_ub);
    if (totalSampsReceived == 0ULL) {
      b_this.init();
      startTimeStamp = b_this.data.re / 1000.0 - 0.0054373333333333339;
      //  At this point the difference between tic and toc for the first packet
      //  is arbitrary. Since we may have been sitting waiting for the first
      //  packet to come in. Because of this we need to be able to subtract out
      //  this waiting time from our elapsed time calcuations. We use the
      //  tocElapsedAdjust for this purpose.
      tocElapsedSubtract = coder::toc() - 0.0054373333333333339;
    }
    b_qY = totalSampsReceived + 2039ULL;
    if (totalSampsReceived + 2039ULL < totalSampsReceived) {
      b_qY = MAX_uint64_T;
    }
    totalSampsReceived = b_qY;
    tocBasedElapseTime = coder::toc() - tocElapsedSubtract;
    //  Reset if a big time offset developes
    tocBasedElapseTime -= static_cast<double>(b_qY) * 2.6666666666666668E-6;
    if (std::abs(tocBasedElapseTime) > 0.1) {
      printf("Resetting buffers to due to drift: Current diff b/t toc and samp "
             "time: %f s \n",
             tocBasedElapseTime);
      fflush(stdout);
      if (dataBufferFIFO.pBuffer.isInitialized == 2) {
        rtErrorWithMessageID("reset", emlrtRTEI.fName, emlrtRTEI.lineNo);
      }
      if (dataBufferFIFO.pBuffer.isInitialized == 1) {
        dataBufferFIFO.pBuffer.ReadPointer = 1;
        dataBufferFIFO.pBuffer.WritePointer = 2;
        dataBufferFIFO.pBuffer.CumulativeOverrun = 0;
        dataBufferFIFO.pBuffer.CumulativeUnderrun = 0;
        std::memset(&dataBufferFIFO.pBuffer.Cache[0], 0,
                    204801U * sizeof(creal32_T));
      }
      udpReceiverClear(udpReceiver.udpReceiver);
      totalSampsReceived = 0ULL;
      sampsTransmitted = 0U;
    }
    //  Collect samples in FIFO until we have enough to channelize
    dataBufferFIFO.write(dataReceived_data, loop_ub);
    if ((dataBufferFIFO.pBuffer.WritePointer >= 0) &&
        (dataBufferFIFO.pBuffer.ReadPointer <
         dataBufferFIFO.pBuffer.WritePointer - MAX_int32_T)) {
      loop_ub = MAX_int32_T;
    } else if ((dataBufferFIFO.pBuffer.WritePointer < 0) &&
               (dataBufferFIFO.pBuffer.ReadPointer >
                dataBufferFIFO.pBuffer.WritePointer - MIN_int32_T)) {
      loop_ub = MIN_int32_T;
    } else {
      loop_ub = dataBufferFIFO.pBuffer.WritePointer -
                dataBufferFIFO.pBuffer.ReadPointer;
    }
    if (loop_ub < -2147483647) {
      loop_ub = MIN_int32_T;
    } else {
      loop_ub--;
    }
    if (dataBufferFIFO.pBuffer.ReadPointer < -2147278847) {
      qY = MAX_int32_T;
    } else {
      qY = 204800 - dataBufferFIFO.pBuffer.ReadPointer;
    }
    if ((qY < 0) && (dataBufferFIFO.pBuffer.WritePointer < MIN_int32_T - qY)) {
      qY = MIN_int32_T;
    } else if ((qY > 0) &&
               (dataBufferFIFO.pBuffer.WritePointer > MAX_int32_T - qY)) {
      qY = MAX_int32_T;
    } else {
      qY += dataBufferFIFO.pBuffer.WritePointer;
    }
    if (dataBufferFIFO.pBuffer.ReadPointer <
        dataBufferFIFO.pBuffer.WritePointer) {
      qY = loop_ub;
    } else if (dataBufferFIFO.pBuffer.ReadPointer ==
               dataBufferFIFO.pBuffer.WritePointer) {
      qY = 204800;
    }
    if (qY >= 102400) {
      creal32_T c_y;
      double bufferTimeStamp;
      float b_y;
      float y;
      unsigned int b_x;
      unsigned int x;
      //  We have enough samples to channelize
      dataBufferFIFO.read(varargin_1);
      channelizer.step(varargin_1, channelData);
      bufferTimeStamp = startTimeStamp + static_cast<double>(sampsTransmitted) *
                                             0.00026666666666666668;
      tocBasedElapseTime = std::floor(bufferTimeStamp);
      if (tocBasedElapseTime < 4.294967296E+9) {
        if (tocBasedElapseTime >= 0.0) {
          x = static_cast<unsigned int>(tocBasedElapseTime);
        } else {
          x = 0U;
        }
      } else if (tocBasedElapseTime >= 4.294967296E+9) {
        x = MAX_uint32_T;
      } else {
        x = 0U;
      }
      if (std::isnan(bufferTimeStamp) || std::isinf(bufferTimeStamp)) {
        tocBasedElapseTime = rtNaN;
      } else if (bufferTimeStamp == 0.0) {
        tocBasedElapseTime = 0.0;
      } else {
        tocBasedElapseTime = std::fmod(bufferTimeStamp, 1.0);
        if (tocBasedElapseTime == 0.0) {
          tocBasedElapseTime = 0.0;
        } else if (bufferTimeStamp < 0.0) {
          tocBasedElapseTime++;
        }
      }
      tocBasedElapseTime = std::round(tocBasedElapseTime * 1.0E+9);
      if (tocBasedElapseTime < 4.294967296E+9) {
        if (tocBasedElapseTime >= 0.0) {
          b_x = static_cast<unsigned int>(tocBasedElapseTime);
        } else {
          b_x = 0U;
        }
      } else {
        b_x = 0U;
      }
      std::memcpy((void *)&y, (void *)&x,
                  (unsigned int)((size_t)1 * sizeof(float)));
      std::memcpy((void *)&b_y, (void *)&b_x,
                  (unsigned int)((size_t)1 * sizeof(float)));
      c_y.re = y;
      c_y.im = b_y;
      udpChannelSender.sendChannelData(channelData, c_y);
      x = sampsTransmitted + 1024U;
      if (sampsTransmitted + 1024U < sampsTransmitted) {
        x = MAX_uint32_T;
      }
      sampsTransmitted = x;
      printf("Channelized samples: transmitted %u\n", x);
      fflush(stdout);
    }
  }
}

//
// File trailer for airspy_channelize.cpp
//
// [EOF]
//
