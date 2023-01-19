function []= airspy_channelize(rawSampleRate,decimationFactor) %#codegen
%AIRSPYFHCHANNELIZER executes the correct channelizer function depending
%on the specified decimation factor
%   This function is designed specifically to channelize incoming UDP data
%   from an Airspy software defined radio, but could work for any
%   complex single precision UDP data sent in 128 sample frames. It calls
%   the appropriate channelizer function depending on the decimation factor
%   requested by the caller. Separate decimation functions have to be
%   created because of limitation in the channelizer objects in Matlab for
%   code generation. Specifically, the number of channels must be a
%   constant at compile time. A series of individual channelizer functions
%   was therefore developed. This function simply calls the appropriate
%   function depending on the decimation factor.
%
%   Data sent over the UDP output channels are single valued complex
%   frames. Each output frame contains 1024 complex values, or 2048
%   individual single precision values. Each frame also contains a
%   timestamp encoded into a complex number in the first element of the
%   frame. The received data frame therefore contains 1025 complex values.
%   The timestamp on each frame is associate with the time of arrival of
%   the first sample in the frame. 
%
%   The timestamp is a double precision posixtime value. The first (MSB)
%   8 bits of this number is cast to a uint32 value and set as the real
%   part of the encoded time. The second (LSB) 8 bits of this double
%   presition posixtime value are also cast to a uint32 value and set as
%   the complex part of the encoded time. To encode and decode these times,
%   use the double2singlecomplex.m and the singlecomplex2double.m
%   functions, respectively. 
%
%   The incoming and outgoing data and function controls in the individual
%   channelizer functions are standardized:
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
%INPUTS:
%	rawSampleRate   A single integer sample rate. Valid entries
%                       correspond to those available for the Airspy HF+
%                       radio: [912 768 456 384 256 192] kS/s
%	decimationFactor	A single integer that is one of the following:
%                       [2; 4; 10; 12; 16; 24; 32; 48; 64; 80; 96; 100; 
%                        120; 128; 192; 256]
%
%
%OUTPUTS:
%	none
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
%       An Airspy HF+ connected to the machine via USB is received using
%       the airspyhf_rx executable. Using the program with the '-r stdout'
%       option allows the data to be piped to another program with the |
%       character. Netcat can then be use to provide the data to this
%       function via UDP. An example commandline input would be
%
%       /usr/local/bin/airspyhf_rx -f 91.7 -m on -a 912000 -n 9120000 -r
%       stdout -g on -l high -t 0 | netcat -u localhost 10000
%
%       Note that this system call must executed after this function is
%       already running or a 'Connection refused' error will occur in
%       terminal.
%
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

supportedSampleRates = 375000;
%The divisors function does not support code generation. This function was
%run in the command line to develop the valid decimation factors
%allDivisors         = unique([divisors(192000),divisors(256000),divisors(384000),divisors(456000),divisors(768000),divisors(912000)]);
%allDivisors256Max   = allDivisors( allDivisors~=1 & allDivisors<=256 );
%These values were then down-selected to a more common set of factors
%allDivisors256Max = [2; 3; 4; 5; 6; 8; 10; 12; 15; 16; 19; 20; 24; 25; 30; 32; 38; 40; 48; 50; 57; 60; 64; 75; 76; 80; 95; 96; 100; 114; 120; 125; 128; 150; 152; 160; 190; 192; 200; 228; 240; 250; 256];
allDivisors256Max  =  [2; 4; 10; 12; 16; 24; 32; 48; 64; 80; 96; 100; 120; 128; 192; 256];

if ~any(rawSampleRate == supportedSampleRates)
    error(['UAV-RT: Unsupported sample rate requested. Available rates are [',num2str(supportedSampleRates/1000),'] kS/s.'])
end

if ~mod(decimationFactor,1) == 0 %Integer check
   error('UAV-RT: Decimation factor (Raw rate/decimated rate) must be an integer.') 
end

if ~ismember(decimationFactor,allDivisors256Max)
    error(['UAV-RT: Decimation factor not supported. Valid values are: ', num2str(allDivisors256Max.')] ) 
end


% if decimationFactor == 2
%     airspychannelize2(rawSampleRate);
% elseif decimationFactor == 4
%     airspychannelize4(rawSampleRate);
% elseif decimationFactor == 10
%     airspychannelize10(rawSampleRate);
% elseif decimationFactor == 12
%      airspychannelize12(rawSampleRate);
% elseif decimationFactor == 16
%     airspychannelize16(rawSampleRate);
% elseif decimationFactor == 24
%      airspychannelize24(rawSampleRate);
% elseif decimationFactor == 32
%      airspychannelize32(rawSampleRate);    
if decimationFactor == 48
    %airspychannelize48_tunable_sender(rawSampleRate);
    airspychannelize48(rawSampleRate);
else
    fprintf('Only decimation factors of 48 are currently supported. Exiting.')
end

% if decimationFactor == 2
%     airspychannelize2(rawSampleRate);
% elseif decimationFactor == 4
%     airspychannelize4(rawSampleRate);
% elseif decimationFactor == 10
%     airspychannelize10(rawSampleRate);
% elseif decimationFactor == 12
%     airspychannelize12(rawSampleRate);
% elseif decimationFactor == 16
%     airspychannelize16(rawSampleRate);
% elseif decimationFactor == 24
%     airspychannelize24(rawSampleRate);
% elseif decimationFactor == 32
%     airspychannelize32(rawSampleRate);
% elseif decimationFactor == 48
%     airspychannelize48(rawSampleRate);
% elseif decimationFactor == 64
%     airspychannelize64(rawSampleRate);
% elseif decimationFactor == 80
%     airspychannelize80(rawSampleRate);
% elseif decimationFactor == 96
%     airspychannelize96(rawSampleRate);
% elseif decimationFactor == 100
%     airspychannelize100(rawSampleRate);
% elseif decimationFactor == 120
%     airspychannelize120(rawSampleRate);
% elseif decimationFactor == 128
%     airspychannelize128(rawSampleRate);
% elseif decimationFactor == 192
%     airspychannelize192(rawSampleRate);
% elseif decimationFactor == 256
%     airspychannelize256(rawSampleRate);
% end


end
