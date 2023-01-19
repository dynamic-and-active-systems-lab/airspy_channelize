function [retUDPCell] = udpsendercellforcoder(remoteIPAddressIn,remoteIPPortIn,sendBufferSizeIn)
%UDPSENDERCELLFORCODER Generates a cell array of dsp.UDPSend objects in a 
% way that is compatible with Matlab Coder. 
%   This function receives a remote IP address and a column vector of
%   remote IP ports. The function generates a cell arrray with UDPSender
%   objects from the Matlab DSP Toolbox in a way that is compatible with
%   the cell array restrictions present in Matlab Coder. The function
%   generates 256 sender objects and then truncates the cell array to
%   output the same size cell array as the size of the remoteIPPortIn
%   argument. No more that 256 ports can be requested. 
%
%INPUTS:
%   remoteIPAddressIn  String containg the remote IP address to send data
%                      to. i.e. '127.0.0.1' or 'localhost'
%   remoteIPPortIn     [1xn] vector of port numbers. Must have no more than
%                      256 elements
%   sendBufferSizeIn   Size of the buffer for each of the UDP Senders. 
%
%
%OUTPUTS:
%   retUDPCell         [1xn] cell array containing the UDP sender objects. 
%
%
%
%Author: Michael W. Shafer
%Date:   2021-11-24
%-------------------------------------------------------------------------
maxNumofPorts = 256;
numOfPorts = numel(remoteIPPortIn);
if ~isstr(remoteIPAddressIn)
    error('UAV-RT: Remote IP address must be entered as a string')
end

if numel(sendBufferSizeIn)>1
    error('UAV-RT: This function only currently supports a single sendBufferSizeIn argurment. This will be applied to all senders.')
end

if numOfPorts>maxNumofPorts
    error('UAV-RT: This function only supports creation of up to 256 ports. If more are needed, consider running multiple instances of this functions and concatinating the outputs.')
end

sizeRemoteIPPortIn = size(remoteIPPortIn);
if min(sizeRemoteIPPortIn) ~= 1
    error('UAV-RT: remoteIPAddressIn must be a row vector.')
end

if size(sizeRemoteIPPortIn,1)~=1
    remoteIPPortInRow = transpose(remoteIPPortIn);
else
    remoteIPPortInRow = remoteIPPortIn;
end

dummyRemotePort    = 10000;
remoteIPPortFiller = dummyRemotePort*ones(1,maxNumofPorts-numOfPorts);
remoteIPPort       = [remoteIPPortInRow,remoteIPPortFiller];

udps1   = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(1)  , 'SendBufferSize', sendBufferSizeIn  );
udps2   = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(2)  , 'SendBufferSize', sendBufferSizeIn  );
udps3   = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(3)  , 'SendBufferSize', sendBufferSizeIn  );
udps4   = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(4)  , 'SendBufferSize', sendBufferSizeIn  );
udps5   = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(5)  , 'SendBufferSize', sendBufferSizeIn  );
udps6   = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(6)  , 'SendBufferSize', sendBufferSizeIn  );
udps7   = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(7)  , 'SendBufferSize', sendBufferSizeIn  );
udps8   = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(8)  , 'SendBufferSize', sendBufferSizeIn  );
udps9   = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(9)  , 'SendBufferSize', sendBufferSizeIn  );
udps10  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(10) , 'SendBufferSize', sendBufferSizeIn  );

udps11  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(11) , 'SendBufferSize', sendBufferSizeIn  );
udps12  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(12) , 'SendBufferSize', sendBufferSizeIn  );
udps13  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(13) , 'SendBufferSize', sendBufferSizeIn  );
udps14  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(14) , 'SendBufferSize', sendBufferSizeIn  );
udps15  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(15) , 'SendBufferSize', sendBufferSizeIn  );
udps16  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(16) , 'SendBufferSize', sendBufferSizeIn  );
udps17  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(17) , 'SendBufferSize', sendBufferSizeIn  );
udps18  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(18) , 'SendBufferSize', sendBufferSizeIn  );
udps19  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(19) , 'SendBufferSize', sendBufferSizeIn  );
udps20  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(20) , 'SendBufferSize', sendBufferSizeIn  );

udps21  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(21) , 'SendBufferSize', sendBufferSizeIn  );
udps22  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(22) , 'SendBufferSize', sendBufferSizeIn  );
udps23  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(23) , 'SendBufferSize', sendBufferSizeIn  );
udps24  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(24) , 'SendBufferSize', sendBufferSizeIn  );
udps25  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(25) , 'SendBufferSize', sendBufferSizeIn  );
udps26  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(26) , 'SendBufferSize', sendBufferSizeIn  );
udps27  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(27) , 'SendBufferSize', sendBufferSizeIn  );
udps28  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(28) , 'SendBufferSize', sendBufferSizeIn  );
udps29  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(29) , 'SendBufferSize', sendBufferSizeIn  );
udps30  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(30) , 'SendBufferSize', sendBufferSizeIn  );

udps31  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(31) , 'SendBufferSize', sendBufferSizeIn  );
udps32  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(32) , 'SendBufferSize', sendBufferSizeIn  );
udps33  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(33) , 'SendBufferSize', sendBufferSizeIn  );
udps34  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(34) , 'SendBufferSize', sendBufferSizeIn  );
udps35  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(35) , 'SendBufferSize', sendBufferSizeIn  );
udps36  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(36) , 'SendBufferSize', sendBufferSizeIn  );
udps37  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(37) , 'SendBufferSize', sendBufferSizeIn  );
udps38  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(38) , 'SendBufferSize', sendBufferSizeIn  );
udps39  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(39) , 'SendBufferSize', sendBufferSizeIn  );
udps40  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(40) , 'SendBufferSize', sendBufferSizeIn  );

udps41  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(41) , 'SendBufferSize', sendBufferSizeIn  );
udps42  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(42) , 'SendBufferSize', sendBufferSizeIn  );
udps43  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(43) , 'SendBufferSize', sendBufferSizeIn  );
udps44  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(44) , 'SendBufferSize', sendBufferSizeIn  );
udps45  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(45) , 'SendBufferSize', sendBufferSizeIn  );
udps46  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(46) , 'SendBufferSize', sendBufferSizeIn  );
udps47  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(47) , 'SendBufferSize', sendBufferSizeIn  );
udps48  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(48) , 'SendBufferSize', sendBufferSizeIn  );
udps49  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(49) , 'SendBufferSize', sendBufferSizeIn  );
udps50  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(50) , 'SendBufferSize', sendBufferSizeIn  );

udps51  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(51) , 'SendBufferSize', sendBufferSizeIn  );
udps52  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(52) , 'SendBufferSize', sendBufferSizeIn  );
udps53  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(53) , 'SendBufferSize', sendBufferSizeIn  );
udps54  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(54) , 'SendBufferSize', sendBufferSizeIn  );
udps55  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(55) , 'SendBufferSize', sendBufferSizeIn  );
udps56  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(56) , 'SendBufferSize', sendBufferSizeIn  );
udps57  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(57) , 'SendBufferSize', sendBufferSizeIn  );
udps58  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(58) , 'SendBufferSize', sendBufferSizeIn  );
udps59  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(59) , 'SendBufferSize', sendBufferSizeIn  );
udps60  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(60) , 'SendBufferSize', sendBufferSizeIn  );

udps61  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(61) , 'SendBufferSize', sendBufferSizeIn  );
udps62  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(62) , 'SendBufferSize', sendBufferSizeIn  );
udps63  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(63) , 'SendBufferSize', sendBufferSizeIn  );
udps64  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(64) , 'SendBufferSize', sendBufferSizeIn  );
udps65  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(65) , 'SendBufferSize', sendBufferSizeIn  );
udps66  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(66) , 'SendBufferSize', sendBufferSizeIn  );
udps67  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(67) , 'SendBufferSize', sendBufferSizeIn  );
udps68  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(68) , 'SendBufferSize', sendBufferSizeIn  );
udps69  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(69) , 'SendBufferSize', sendBufferSizeIn  );
udps70  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(70) , 'SendBufferSize', sendBufferSizeIn  );

udps71  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(71) , 'SendBufferSize', sendBufferSizeIn  );
udps72  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(72) , 'SendBufferSize', sendBufferSizeIn  );
udps73  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(73) , 'SendBufferSize', sendBufferSizeIn  );
udps74  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(74) , 'SendBufferSize', sendBufferSizeIn  );
udps75  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(75) , 'SendBufferSize', sendBufferSizeIn  );
udps76  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(76) , 'SendBufferSize', sendBufferSizeIn  );
udps77  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(77) , 'SendBufferSize', sendBufferSizeIn  );
udps78  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(78) , 'SendBufferSize', sendBufferSizeIn  );
udps79  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(79) , 'SendBufferSize', sendBufferSizeIn  );
udps80  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(80) , 'SendBufferSize', sendBufferSizeIn  );

udps81  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(81) , 'SendBufferSize', sendBufferSizeIn  );
udps82  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(82) , 'SendBufferSize', sendBufferSizeIn  );
udps83  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(83) , 'SendBufferSize', sendBufferSizeIn  );
udps84  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(84) , 'SendBufferSize', sendBufferSizeIn  );
udps85  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(85) , 'SendBufferSize', sendBufferSizeIn  );
udps86  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(86) , 'SendBufferSize', sendBufferSizeIn  );
udps87  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(87) , 'SendBufferSize', sendBufferSizeIn  );
udps88  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(88) , 'SendBufferSize', sendBufferSizeIn  );
udps89  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(89) , 'SendBufferSize', sendBufferSizeIn  );
udps90  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(90) , 'SendBufferSize', sendBufferSizeIn  );

udps91  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(91) , 'SendBufferSize', sendBufferSizeIn  );
udps92  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(92) , 'SendBufferSize', sendBufferSizeIn  );
udps93  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(93) , 'SendBufferSize', sendBufferSizeIn  );
udps94  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(94) , 'SendBufferSize', sendBufferSizeIn  );
udps95  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(95) , 'SendBufferSize', sendBufferSizeIn  );
udps96  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(96) , 'SendBufferSize', sendBufferSizeIn  );
udps97  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(97) , 'SendBufferSize', sendBufferSizeIn  );
udps98  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(98) , 'SendBufferSize', sendBufferSizeIn  );
udps99  = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(99) , 'SendBufferSize', sendBufferSizeIn  );
udps100 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(100), 'SendBufferSize', sendBufferSizeIn  );

udps101 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(101), 'SendBufferSize', sendBufferSizeIn  );
udps102 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(102), 'SendBufferSize', sendBufferSizeIn  );
udps103 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(103), 'SendBufferSize', sendBufferSizeIn  );
udps104 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(104), 'SendBufferSize', sendBufferSizeIn  );
udps105 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(105), 'SendBufferSize', sendBufferSizeIn  );
udps106 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(106), 'SendBufferSize', sendBufferSizeIn  );
udps107 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(107), 'SendBufferSize', sendBufferSizeIn  );
udps108 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(108), 'SendBufferSize', sendBufferSizeIn  );
udps109 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(109), 'SendBufferSize', sendBufferSizeIn  );
udps110 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(110), 'SendBufferSize', sendBufferSizeIn  );

udps111 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(111), 'SendBufferSize', sendBufferSizeIn  );
udps112 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(112), 'SendBufferSize', sendBufferSizeIn  );
udps113 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(113), 'SendBufferSize', sendBufferSizeIn  );
udps114 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(114), 'SendBufferSize', sendBufferSizeIn  );
udps115 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(115), 'SendBufferSize', sendBufferSizeIn  );
udps116 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(116), 'SendBufferSize', sendBufferSizeIn  );
udps117 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(117), 'SendBufferSize', sendBufferSizeIn  );
udps118 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(118), 'SendBufferSize', sendBufferSizeIn  );
udps119 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(119), 'SendBufferSize', sendBufferSizeIn  );
udps120 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(120), 'SendBufferSize', sendBufferSizeIn  );

udps121 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(121), 'SendBufferSize', sendBufferSizeIn  );
udps122 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(122), 'SendBufferSize', sendBufferSizeIn  );
udps123 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(123), 'SendBufferSize', sendBufferSizeIn  );
udps124 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(124), 'SendBufferSize', sendBufferSizeIn  );
udps125 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(125), 'SendBufferSize', sendBufferSizeIn  );
udps126 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(126), 'SendBufferSize', sendBufferSizeIn  );
udps127 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(127), 'SendBufferSize', sendBufferSizeIn  );
udps128 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(128), 'SendBufferSize', sendBufferSizeIn  );
udps129 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(129), 'SendBufferSize', sendBufferSizeIn  );
udps130 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(130), 'SendBufferSize', sendBufferSizeIn  );

udps131 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(131), 'SendBufferSize', sendBufferSizeIn  );
udps132 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(132), 'SendBufferSize', sendBufferSizeIn  );
udps133 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(133), 'SendBufferSize', sendBufferSizeIn  );
udps134 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(134), 'SendBufferSize', sendBufferSizeIn  );
udps135 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(135), 'SendBufferSize', sendBufferSizeIn  );
udps136 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(136), 'SendBufferSize', sendBufferSizeIn  );
udps137 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(137), 'SendBufferSize', sendBufferSizeIn  );
udps138 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(138), 'SendBufferSize', sendBufferSizeIn  );
udps139 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(139), 'SendBufferSize', sendBufferSizeIn  );
udps140 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(140), 'SendBufferSize', sendBufferSizeIn  );

udps141 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(141), 'SendBufferSize', sendBufferSizeIn  );
udps142 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(142), 'SendBufferSize', sendBufferSizeIn  );
udps143 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(143), 'SendBufferSize', sendBufferSizeIn  );
udps144 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(144), 'SendBufferSize', sendBufferSizeIn  );
udps145 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(145), 'SendBufferSize', sendBufferSizeIn  );
udps146 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(146), 'SendBufferSize', sendBufferSizeIn  );
udps147 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(147), 'SendBufferSize', sendBufferSizeIn  );
udps148 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(148), 'SendBufferSize', sendBufferSizeIn  );
udps149 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(149), 'SendBufferSize', sendBufferSizeIn  );
udps150 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(150), 'SendBufferSize', sendBufferSizeIn  );

udps151 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(151), 'SendBufferSize', sendBufferSizeIn  );
udps152 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(152), 'SendBufferSize', sendBufferSizeIn  );
udps153 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(153), 'SendBufferSize', sendBufferSizeIn  );
udps154 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(154), 'SendBufferSize', sendBufferSizeIn  );
udps155 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(155), 'SendBufferSize', sendBufferSizeIn  );
udps156 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(156), 'SendBufferSize', sendBufferSizeIn  );
udps157 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(157), 'SendBufferSize', sendBufferSizeIn  );
udps158 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(158), 'SendBufferSize', sendBufferSizeIn  );
udps159 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(159), 'SendBufferSize', sendBufferSizeIn  );
udps160 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(160), 'SendBufferSize', sendBufferSizeIn  );

udps161 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(161), 'SendBufferSize', sendBufferSizeIn  );
udps162 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(162), 'SendBufferSize', sendBufferSizeIn  );
udps163 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(163), 'SendBufferSize', sendBufferSizeIn  );
udps164 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(164), 'SendBufferSize', sendBufferSizeIn  );
udps165 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(165), 'SendBufferSize', sendBufferSizeIn  );
udps166 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(166), 'SendBufferSize', sendBufferSizeIn  );
udps167 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(167), 'SendBufferSize', sendBufferSizeIn  );
udps168 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(168), 'SendBufferSize', sendBufferSizeIn  );
udps169 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(169), 'SendBufferSize', sendBufferSizeIn  );
udps170 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(170), 'SendBufferSize', sendBufferSizeIn  );

udps171 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(171), 'SendBufferSize', sendBufferSizeIn  );
udps172 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(172), 'SendBufferSize', sendBufferSizeIn  );
udps173 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(173), 'SendBufferSize', sendBufferSizeIn  );
udps174 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(174), 'SendBufferSize', sendBufferSizeIn  );
udps175 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(175), 'SendBufferSize', sendBufferSizeIn  );
udps176 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(176), 'SendBufferSize', sendBufferSizeIn  );
udps177 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(177), 'SendBufferSize', sendBufferSizeIn  );
udps178 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(178), 'SendBufferSize', sendBufferSizeIn  );
udps179 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(179), 'SendBufferSize', sendBufferSizeIn  );
udps180 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(180), 'SendBufferSize', sendBufferSizeIn  );

udps181 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(181), 'SendBufferSize', sendBufferSizeIn  );
udps182 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(182), 'SendBufferSize', sendBufferSizeIn  );
udps183 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(183), 'SendBufferSize', sendBufferSizeIn  );
udps184 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(184), 'SendBufferSize', sendBufferSizeIn  );
udps185 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(185), 'SendBufferSize', sendBufferSizeIn  );
udps186 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(186), 'SendBufferSize', sendBufferSizeIn  );
udps187 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(187), 'SendBufferSize', sendBufferSizeIn  );
udps188 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(188), 'SendBufferSize', sendBufferSizeIn  );
udps189 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(189), 'SendBufferSize', sendBufferSizeIn  );
udps190 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(190), 'SendBufferSize', sendBufferSizeIn  );

udps191 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(191), 'SendBufferSize', sendBufferSizeIn  );
udps192 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(192), 'SendBufferSize', sendBufferSizeIn  );
udps193 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(193), 'SendBufferSize', sendBufferSizeIn  );
udps194 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(194), 'SendBufferSize', sendBufferSizeIn  );
udps195 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(195), 'SendBufferSize', sendBufferSizeIn  );
udps196 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(196), 'SendBufferSize', sendBufferSizeIn  );
udps197 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(197), 'SendBufferSize', sendBufferSizeIn  );
udps198 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(198), 'SendBufferSize', sendBufferSizeIn  );
udps199 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(199), 'SendBufferSize', sendBufferSizeIn  );
udps200 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(200), 'SendBufferSize', sendBufferSizeIn  );

udps201 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(201), 'SendBufferSize', sendBufferSizeIn  );
udps202 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(202), 'SendBufferSize', sendBufferSizeIn  );
udps203 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(203), 'SendBufferSize', sendBufferSizeIn  );
udps204 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(204), 'SendBufferSize', sendBufferSizeIn  );
udps205 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(205), 'SendBufferSize', sendBufferSizeIn  );
udps206 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(206), 'SendBufferSize', sendBufferSizeIn  );
udps207 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(207), 'SendBufferSize', sendBufferSizeIn  );
udps208 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(208), 'SendBufferSize', sendBufferSizeIn  );
udps209 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(209), 'SendBufferSize', sendBufferSizeIn  );
udps210 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(210), 'SendBufferSize', sendBufferSizeIn  );

udps211 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(211), 'SendBufferSize', sendBufferSizeIn  );
udps212 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(212), 'SendBufferSize', sendBufferSizeIn  );
udps213 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(213), 'SendBufferSize', sendBufferSizeIn  );
udps214 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(214), 'SendBufferSize', sendBufferSizeIn  );
udps215 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(215), 'SendBufferSize', sendBufferSizeIn  );
udps216 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(216), 'SendBufferSize', sendBufferSizeIn  );
udps217 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(217), 'SendBufferSize', sendBufferSizeIn  );
udps218 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(218), 'SendBufferSize', sendBufferSizeIn  );
udps219 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(219), 'SendBufferSize', sendBufferSizeIn  );
udps220 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(220), 'SendBufferSize', sendBufferSizeIn  );

udps221 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(221), 'SendBufferSize', sendBufferSizeIn  );
udps222 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(222), 'SendBufferSize', sendBufferSizeIn  );
udps223 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(223), 'SendBufferSize', sendBufferSizeIn  );
udps224 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(224), 'SendBufferSize', sendBufferSizeIn  );
udps225 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(225), 'SendBufferSize', sendBufferSizeIn  );
udps226 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(226), 'SendBufferSize', sendBufferSizeIn  );
udps227 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(227), 'SendBufferSize', sendBufferSizeIn  );
udps228 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(228), 'SendBufferSize', sendBufferSizeIn  );
udps229 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(229), 'SendBufferSize', sendBufferSizeIn  );
udps230 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(230), 'SendBufferSize', sendBufferSizeIn  );

udps231 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(231), 'SendBufferSize', sendBufferSizeIn  );
udps232 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(232), 'SendBufferSize', sendBufferSizeIn  );
udps233 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(233), 'SendBufferSize', sendBufferSizeIn  );
udps234 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(234), 'SendBufferSize', sendBufferSizeIn  );
udps235 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(235), 'SendBufferSize', sendBufferSizeIn  );
udps236 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(236), 'SendBufferSize', sendBufferSizeIn  );
udps237 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(237), 'SendBufferSize', sendBufferSizeIn  );
udps238 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(238), 'SendBufferSize', sendBufferSizeIn  );
udps239 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(239), 'SendBufferSize', sendBufferSizeIn  );
udps240 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(240), 'SendBufferSize', sendBufferSizeIn  );

udps241 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(241), 'SendBufferSize', sendBufferSizeIn  );
udps242 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(242), 'SendBufferSize', sendBufferSizeIn  );
udps243 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(243), 'SendBufferSize', sendBufferSizeIn  );
udps244 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(244), 'SendBufferSize', sendBufferSizeIn  );
udps245 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(245), 'SendBufferSize', sendBufferSizeIn  );
udps246 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(246), 'SendBufferSize', sendBufferSizeIn  );
udps247 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(247), 'SendBufferSize', sendBufferSizeIn  );
udps248 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(248), 'SendBufferSize', sendBufferSizeIn  );
udps249 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(249), 'SendBufferSize', sendBufferSizeIn  );
udps250 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(250), 'SendBufferSize', sendBufferSizeIn  );

udps251 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(251), 'SendBufferSize', sendBufferSizeIn  );
udps252 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(252), 'SendBufferSize', sendBufferSizeIn  );
udps253 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(253), 'SendBufferSize', sendBufferSizeIn  );
udps254 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(254), 'SendBufferSize', sendBufferSizeIn  );
udps255 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(255), 'SendBufferSize', sendBufferSizeIn  );
udps256 = dsp.UDPSender('RemoteIPAddress', remoteIPAddressIn  , 'RemoteIPPort', remoteIPPort(256), 'SendBufferSize', sendBufferSizeIn  );


%   
udpsCellAll = { udps1   ; udps2   ; udps3   ; udps4   ; udps5   ; udps6   ; udps7   ; udps8   ; udps9   ; udps10  ;...
                udps11  ; udps12  ; udps13  ; udps14  ; udps15  ; udps16  ; udps17  ; udps18  ; udps19  ; udps20  ;...
                udps21  ; udps22  ; udps23  ; udps24  ; udps25  ; udps26  ; udps27  ; udps28  ; udps29  ; udps30  ;...
                udps31  ; udps32  ; udps33  ; udps34  ; udps35  ; udps36  ; udps37  ; udps38  ; udps39  ; udps40  ;...
                udps41  ; udps42  ; udps43  ; udps44  ; udps45  ; udps46  ; udps47  ; udps48  ; udps49  ; udps50  ;...
                udps51  ; udps52  ; udps53  ; udps54  ; udps55  ; udps56  ; udps57  ; udps58  ; udps59  ; udps60  ;...
                udps61  ; udps62  ; udps63  ; udps64  ; udps65  ; udps66  ; udps67  ; udps68  ; udps69  ; udps70  ;...
                udps71  ; udps72  ; udps73  ; udps74  ; udps75  ; udps76  ; udps77  ; udps78  ; udps79  ; udps80  ;...
                udps81  ; udps82  ; udps83  ; udps84  ; udps85  ; udps86  ; udps87  ; udps88  ; udps89  ; udps90  ;...
                udps91  ; udps92  ; udps93  ; udps94  ; udps95  ; udps96  ; udps97  ; udps98  ; udps99  ; udps100 ;...
                udps101 ; udps102 ; udps103 ; udps104 ; udps105 ; udps106 ; udps107 ; udps108 ; udps109 ; udps110 ;...
                udps111 ; udps112 ; udps113 ; udps114 ; udps115 ; udps116 ; udps117 ; udps118 ; udps119 ; udps120 ;...
                udps121 ; udps122 ; udps123 ; udps124 ; udps125 ; udps126 ; udps127 ; udps128 ; udps129 ; udps130 ;...
                udps131 ; udps132 ; udps133 ; udps134 ; udps135 ; udps136 ; udps137 ; udps138 ; udps139 ; udps140 ;...
                udps141 ; udps142 ; udps143 ; udps144 ; udps145 ; udps146 ; udps147 ; udps148 ; udps149 ; udps150 ;...
                udps151 ; udps152 ; udps153 ; udps154 ; udps155 ; udps156 ; udps157 ; udps158 ; udps159 ; udps160 ;...
                udps161 ; udps162 ; udps163 ; udps164 ; udps165 ; udps166 ; udps167 ; udps168 ; udps169 ; udps170 ;...
                udps171 ; udps172 ; udps173 ; udps174 ; udps175 ; udps176 ; udps177 ; udps178 ; udps179 ; udps180 ;...
                udps181 ; udps182 ; udps183 ; udps184 ; udps185 ; udps186 ; udps187 ; udps188 ; udps189 ; udps190 ;...
                udps191 ; udps192 ; udps193 ; udps194 ; udps195 ; udps196 ; udps197 ; udps198 ; udps199 ; udps200 ;...
                udps201 ; udps202 ; udps203 ; udps204 ; udps205 ; udps206 ; udps207 ; udps208 ; udps209 ; udps210 ;...
                udps211 ; udps212 ; udps213 ; udps214 ; udps215 ; udps216 ; udps217 ; udps218 ; udps219 ; udps220 ;...
                udps221 ; udps222 ; udps223 ; udps224 ; udps225 ; udps226 ; udps227 ; udps228 ; udps229 ; udps230 ;...
                udps231 ; udps232 ; udps233 ; udps234 ; udps235 ; udps236 ; udps237 ; udps238 ; udps239 ; udps240 ;...
                udps241 ; udps242 ; udps243 ; udps244 ; udps245 ; udps246 ; udps247 ; udps248 ; udps249 ; udps250 ;...
                udps251 ; udps252 ; udps253 ; udps254 ; udps255 ; udps256 };
            
%udpsCellAll = { udps1   ; udps2   ; udps3   ;udps4   };

%Coder doesn't support curly braces or this would be coded as
%udpsCellAll(1:numOfPorts)
retUDPCell = {udpsCellAll{1:numOfPorts}};

end

