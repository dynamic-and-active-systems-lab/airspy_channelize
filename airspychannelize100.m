function []= airspychannelize100(rawSampleRate) %#codegen
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
%   Note that all UDP ports have been hardcoded for this function because
%   they are used within the dsp.udpsender and dsp.udpreceiver system
%   objects. When deploying this code to C via Matlab coder, these system
%   object arguments must be constants, which limits the ability of this
%   function to receive ports as arguments and set them at run time. They
%   must be a constant at compile time.
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
%   PORT LISTING
%       10000       Receive port for airspy data
%                      Complex single precision data
%                      Maximum message size 1024 bytes
%       10001       Receive port for fucntion control commands
%                      Real int8 data
%                      Maximum message size 1024 bytes
%                      Valid inputs are
%                           1   Start data reception/transmission
%                           0   Stop (pause) data reception/transmission
%                               and flush the buffer
%                           -1  Terminate the function
%       20000:20*** Send ports for serving channelized UDP data. The
%                   center frequency of the channel for port 20000 is the
%                   center frequency of the incoming data. Subsequent port
%                   correspond to the increasing channel numbers and
%                   frequency, eventually wrapping to negative frequencies
%                   above Fs/2. See notes about channel center frequencies
%                   below.The max port number is equal to 
%                   20000+numberofchannels-1
%
%
%   INPUTS:
%       rawSampleRate   A single integer sample rate. Valid entries
%                       correspond to those available for the Airspy HF+
%                       radio: 375 kS/s
%
%   OUTPUTS:
%       none
%
%
%
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
%       Command signals send via UDP can be entered in the command line as
%       follows:
%           Start (send a 1): 
%               echo -e -n '\x01'| netcat -u localhost 10001
%           Pause (send a 0): 
%               echo -e -n '\x00'| netcat -u localhost 10001
%           Kill (send a -1): 
%               echo -e -n '\xFF'| netcat -u localhost 10001
%
%-------------------------------------------------------------------------
%Author:    Michael Shafer
%Date:      2022-01-18
%-------------------------------------------------------------------------

decimationFactor = 100;
fprintf('Channelizer: Starting up...\n')
coder.varsize('state')

%Channelization Settings
maxNumChannels      = 256;
nChannels           = decimationFactor; %Decimation is currently set to equal nChannels. Must be a factor of rawFrameLength
pauseWhenIdleTime   = 0.25;

%UDP Settings
udpReceivePort      = 10000;
udpCommandPort      = 10001;
udpServePorts       = 20000:20000+maxNumChannels-1;%10000:10039;

%Incoming Data Variables
rawFrameLength  = 128;

rawFrameTime        = rawFrameLength/rawSampleRate;
bytesPerSample      = 8;
supportedSampleRates = 375000;%[912 768 456 384 256 192]*1000;

if ~any(rawSampleRate == supportedSampleRates)
    error(['UAV-RT: Unsupported sample rate requested. Available rates are [',num2str(supportedSampleRates/1000),'] kS/s.'])
end

fprintf('Channelizer: Setting up UDP command and data ports...\n')
%% SETUP UDP COMMAND INPUT OBJECT
udpCommand = dsp.UDPReceiver('RemoteIPAddress','127.0.0.1',...%127.0.0.1',...  %Accept all
    'LocalIPPort',udpCommandPort,...
    'ReceiveBufferSize',2^6,...%2^16 = 65536, 2^18
    'MaximumMessageLength',1024,...
    'MessageDataType','int8',...
    'IsMessageComplex',false);

setup(udpCommand);

%% SETUP UDP DATA INPUT OBJECT
udpReceive = dsp.UDPReceiver('RemoteIPAddress','127.0.0.1',...%127.0.0.1',... %Accept all
    'LocalIPPort',udpReceivePort,...
    'ReceiveBufferSize', 2^19,...%Based nextpow2(2*bytesPerBufferAtFlush)  %2^18,...%2^16 = 65536, 2^18
    'MaximumMessageLength',4096,...%1024,...%128 on a Mac and 2048 on Linux
    'MessageDataType','single',...
    'IsMessageComplex',true);

setup(udpReceive);

%% SETUP UDP OUTPUT OBJECTS
fprintf('Channelizer: Setting up output channel UDP ports...\n')
samplesPerChannelMessage = 256; %1024 Must be a multiple of 128
samplesAtFlush           = samplesPerChannelMessage * decimationFactor;
bytesPerChannelMessage   = bytesPerSample * samplesPerChannelMessage;
bytesPerBufferAtFlush    = bytesPerSample * samplesAtFlush;
sendBufferSize           = 2^nextpow2(bytesPerChannelMessage);
dataBufferFIFO           = dsp.AsyncBuffer(2*samplesAtFlush);
expectedTimeBetweenFlushes = samplesAtFlush/rawSampleRate;
write(dataBufferFIFO,single(1+1i));%Write a single value so the number of channels is specified for coder. Specify complex single for airspy data
read(dataBufferFIFO);     %Read out that single sample to empty the buffer.

udps                     = udpsendercellforcoder('127.0.0.1',udpServePorts,sendBufferSize);

channelizer              = dsp.Channelizer('NumFrequencyBands', nChannels);

totalSampsReceived = 0;
frameIndex = 1;

%Make initial call to udps. First call is very slow and can cause missed
%samples if left within the while loop
for i = 1:numel(nChannels)
    singleZeros = complex(single(zeros(samplesPerChannelMessage,1)));
    udps{i}(singleZeros);%Add one for blank time stamp
end

expectedFrameSize = rawFrameLength;
state = 'run';
fprintf('Channelizer: Setup complete. Awaiting commands...\n')
tic;
writeTime = 0
while 1 
    switch state
        case 'run'
            state = 'run';
            dataReceived = udpReceive();
            if (~isempty(dataReceived))
                sampsReceived = numel(dataReceived);
                totalSampsReceived = totalSampsReceived + sampsReceived;
                %Used to keep a running estimated of the expected frame
                %size to help identifiy subsize frames received. 
                if sampsReceived<expectedFrameSize
                    disp('Subpacket received')
                end
                if sampsReceived~=expectedFrameSize
                    expectedFrameSize = round(mean([sampsReceived, expectedFrameSize]));
                end
                writeTimeHold = toc;
                write(dataBufferFIFO,dataReceived(:));%Call with (:) to help coder realize it is a single channel
                writeTime = writeTime + toc - writeTimeHold;
                frameIndex = frameIndex+1;

                if dataBufferFIFO.NumUnreadSamples>=samplesAtFlush
                    writeTimeHold = writeTime;
                    writeTime = 0;
                    fprintf('Channelizer: Running - Buffer filled with %u samples. Flushing to channels. Currently receiving: %i samples per packet.\n',uint32(samplesAtFlush),int32(expectedFrameSize))
                    %fprintf('Actual time between buffer flushes: %6.6f.  Expected: %6.6f. \n', toc, expectedTimeBetweenFlushes)
                    processTimeHold = toc;
                    frameIndex = 1;
                    y = channelizer(read(dataBufferFIFO,samplesAtFlush));
                    channelizeTime = toc - processTimeHold;
                    %time2Channelize = toc;
                    for i = 1:nChannels
                        udps{i}(y(:,i))
                    end
                    sendTime = toc - channelizeTime - processTimeHold;
                    %time2Send = toc - time2Channelize;
                    %fprintf('Time required to read buffer and channelize: %6.6f \n', time2Channelize)
                    %fprintf('Time required to send: %6.6f \n', time2Send)
                    
                    totalLoopTime         = toc;
                    writeReadAndProcessingTime = writeTime + channelizeTime + sendTime;
                    fprintf('Actual time between buffer flushes: %6.6f.  Expected: %6.6f. \n', totalLoopTime, expectedTimeBetweenFlushes)
                    fprintf('Writing to Buffer Time: %6.6f. \n', writeTimeHold)
                    fprintf('Buffer Read and Channelize Time: %6.6f. \n', channelizeTime)
                    fprintf('Sending via UDP Time: %6.6f. \n', sendTime)
                    fprintf('Total Processing Time: %6.6f. \n', writeReadAndProcessingTime)
                    %Buffer just filled, so give it time to refill minus
                    %the processing time we currently need
                    tic
                    %pause(expectedTimeBetweenFlushes - 4 * readAndProcessingTime);
                    %pausedTime = toc;
                end
            else
                %tic
                pause(rawFrameTime)
                %pause(expectedTimeBetweenFlushes)
                %fprintf('***********Notice: I just paused for %6.6f \n',toc)
                %fprintf('***********Notice: I just paused for \n',toc)
            end
            
            cmdReceived  = udpCommand();
            state = checkcommand(cmdReceived,state);
            
        case 'idle'
            state = 'idle';
            reset(dataBufferFIFO);
            fprintf('Channelizer: Idle. Waiting for command...\n')
            pause(pauseWhenIdleTime);%Wait a bit so to throttle idle execution
            cmdReceived  = udpCommand();
            state = checkcommand(cmdReceived,state);
            if strcmp(state,'run')
                reset(udpReceive);%Reset to clear buffer so data is fresh - in case state had been idle
            end
        case 'kill'
            fprintf('Channelizer: Entering Kill state. Shutting down.\n')
            state = 'dead';
            release(dataBufferFIFO);
            release(udpReceive)
            release(udpCommand)
            break
        otherwise
            %Should never get to this case, but jump to idle if we get
            %here.
            state = 'idle';
    end

end


function state = checkcommand(cmdReceived,currentState)
%This function is designed to check the incoming command and decide what to
%do based on the received command and the current state
if ~isempty(cmdReceived)
    if cmdReceived == -1
        fprintf('Channelizer: Kill command received.\n')
        state = 'kill';
    elseif cmdReceived == 0
        fprintf('Channelizer: Idle command received.\n')
        state = 'idle';
    elseif cmdReceived == 1
        fprintf('Channelizer: Run command received.\n')
        state = 'run';
    else
        %Invalid command. Continue with current state.
        state = currentState;
    end
else
    %Nothing received. Continue with current state.
    state = currentState;
end
end

end
