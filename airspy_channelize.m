function airspy_channelize(channelsUsed) 
%#codegen
%AIRSPYFHCHANNELIZE100 receives complex (IQ) data over a UDP connection from 
%an SDR (single precision), channelizes it, and servers it 
%up over 100 diferent UDP ports.
%   This function is designed specifically to receive incoming data that
%   has been passed to it via an interanl UDP connection. The program expects
%   128 sample frames of 8-byte complex samples (4 real, 4 imaginary) to be
%   sent over UDP. The program receives that data and fills a buffer until
%   enough samples have been received that 1024 samples will be generated
%   on the output channels at the decimated sample rate. 
%
%   Once the buffer fills, the data is channelized and
%   served via UDP to corresponding ports. The function opens a command
%   channel so that integers can be passed to enable basic control
%   authority over the program operation, enabling starting of data
%   processing, pausing, and termination of the program.
%
%   Normal channelization allows for decimation rates and the number of
%   channels to be different. This function holds them equal. Therefore,
%   the decimated rate for each channel is equal to the raw airspy sample
%   rate divided by the number of channels. Additionally, the center
%   frequencies of each channel is therefore
%
%   Data sent over the UDP output channels are single valued complex
%   frames. Each output frame contains 1024 complex values, or 2048
%   individual single precision values. Each frame also contains a
%   timestamp encoded into a complex number in the first element of the
%   frame. The received data frame therefore contains 1025 complex values.
%   The timestamp on each frame is associate with the time of arrival of
%   the first sample in the frame. 
%
%   The timestamp is a precision posixtime value in milliseconds. The 
%   timestamp is transmitted as a single precision complex value. The
%   imaginary part of this timestamp contains the first 7 digits of the
%   time in milliseconds. The real part contains the upper digits (>=8) of
%   the timestamp. See the help for int2singlecomplex and singlecomplex2int
%   for more information on this transmission standard. 
%
%   INPUTS:
%       channelsUsed    Look at UDPChannelSender.m for an explanation of how 
%                       this works and how ports are allocated.
%
%Notes:   
%       ABOUT CHANNEL CENTER FREQUENCIES:
%       Matlab provides the centerFrequencies function that accepts a
%       channelizer object and a sample rate, and then specifies the
%       center frequencies of the associated channel. This list however is
%       centered at zero and provides negative frequencies. For example a
%       channelizer with Fs = 48000 and a decimation factor of 3 would
%       report center frequencies [-24000 -12000 0 12000]. If the fvtool is
%       used on this channelizer (with the legend turned on) the center
%       frequencies would be [0 12000 -24000 -12000] for filteres 1-4. The
%       shifting here reflects a inconsistency in Matlab's channel
%       reporting. The channelizer outputs follow the latter order, and as
%       such, so to do the UDP port outputs in this function. 
%       Because the  number of chanels and the decimation are the same, 
%       the frequency of these channels are -Fs/nc*floor(nc/2)<fc<Fs/2, 
%       (where nc is the number of channels), if nc is odd. For even nc
%       -Fs/2 < fc < Fs/2-Fs/nc. In both cases the frequency steps are 
%       Fs/nc. This was determined by using the centerFrequencies.m 
%       function on example channelizer objects. If using the
%       centerFrequencies output the circshift command can be used to get
%       the correct order of channel frequency. For example:
%       circshift(centerFrequencies(channizerObject,48000),ceil(numChannels/2))
%
%       ABOUT INCOMING DATA:
%       An Airspy connected to the machine via USB is received using
%       the airspyhf_rx or airspy_rx executable. Using the program with the
%       '-r stdout' option allows the data to be piped to another program 
%       with the | character. Netcat can then be use to provide the data to
%       this function via UDP. An example commandline input would be
%
%       /usr/local/bin/airspyhf_rx -f 91.7 -m on -a 912000 -n 9120000 -r
%       stdout -g on -l high -t 0 | netcat -u localhost 10000
%
%       Note that this system call must executed after this function is
%       already running or a 'Connection refused' error will occur in
%       terminal.
%-------------------------------------------------------------------------
%Author:    Michael Shafer
%Date:      2022-01-18
%-------------------------------------------------------------------------

coder.cinclude('time.h');

if nargin == 0
    channelsUsed = [ 1 ];
end

decimationFactor            = 100;
nChannels                   = decimationFactor; % Decimation is currently set to equal nChannels. Must be a factor of rawFrameLength

incomingSampleRate          = 375000;
outgoingSampleRate          = incomingSampleRate / decimationFactor;

sampleCountPerChannelOutput = 1024;             % Must be a multiple of 128
sampleCountToChannelize     = double(sampleCountPerChannelOutput) * decimationFactor;
totalSampsReceived          = uint64(0);
sampsTransmitted            = uint32(0);

udpReceivePort              = 10000;
firstChannelSendIPPort      = 20000;

startTimeStamp              = 0;
bufferTimeStamp4Sending     = complex(single(0));

tocStart                    = 0;
tocBasedElapseTime          = 0;
sampBasedElapsedTime        = 0;

dataBufferFIFO              = dsp.AsyncBuffer(2 * sampleCountToChannelize);

write(dataBufferFIFO, single(1+1i));    % Write a single value so the number of channels is specified for coder. Specify complex single for airspy data
read(dataBufferFIFO);                   % Read out that single sample to empty the buffer.

channelizer = dsp.Channelizer('NumFrequencyBands', nChannels);

udpReceiver         = ComplexSingleSamplesUDPReceiver('127.0.0.1', 10000, 2048);
udpChannelSender    = UDPChannelSender('127.0.0.1', firstChannelSendIPPort, channelsUsed, sampleCountPerChannelOutput + 1); % + 1 for timestamp

% Start by clearing any stale data
udpReceiver.clear();

fprintf("Waiting for new udp data\n");

while true
    dataReceived = udpReceiver.receive();

    if ~isempty(dataReceived)
        sampsReceived = uint64(numel(dataReceived));

        if totalSampsReceived == 0
            setStartTimeStamp   = false;
            timeDurOfPacket     = double(sampsReceived) * (1 / incomingSampleRate);
            startTimeStamp      = posixtime(datetime('now')) - timeDurOfPacket;
            tocStart            = tic - timeDurOfPacket;
        end

        totalSampsReceived   = totalSampsReceived + sampsReceived;
        sampBasedElapsedTime = double(totalSampsReceived) * (1 / incomingSampleRate);
        tocBasedElapseTime   = toc - tocStart;

        % Reset if a big time offset developes
        timeDiff = tocBasedElapseTime - sampBasedElapsedTime;
        if abs(timeDiff) > 0.1
            fprintf('Resetting buffers to due to drift: Current diff b/t toc and samp time: %f s \n', timeDiff);
            dataBufferFIFO.reset();
            clearBufferFlag = true;
        end

        % Collect samples in FIFO until we have enough to channelize
        write(dataBufferFIFO, dataReceived);

        if dataBufferFIFO.NumUnreadSamples >= sampleCountToChannelize
            % We have enough samples to channelize

            channelData = channelizer(read(dataBufferFIFO, sampleCountToChannelize));

            bufferTimeStamp         = startTimeStamp + (double(sampsTransmitted) * (1 / outgoingSampleRate));
            bufferTimeStampSec      = uint32(floor(bufferTimeStamp));
            bufferTimeStampNanoSec  = uint32(mod(bufferTimeStamp,1)*10^9);
            bufferTimeStamp4Sending = complex(typecast(bufferTimeStampSec,    'single'), ...
                                              typecast(bufferTimeStampNanoSec,'single'));

            udpChannelSender.sendChannelData(channelData, bufferTimeStamp4Sending);

            sampsTransmitted = sampsTransmitted + sampleCountPerChannelOutput;
            fprintf("Channelized samples: transmitted %u\n", sampsTransmitted);
        end
    end
end
