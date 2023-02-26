classdef UDPChannelSender < handle
    properties
        channelsUsed    (1,:) int32;
        channelIndices  (1,:) int32;
        channelSenders  (1,:)
    end

    methods
        % channelsUsed: An vector of channel indices. Example: [ 1 3 -5 78 ]. Negative numbers indicate that the channel 
        %               must be output on two ports.
        %               An empty vector indicates all channels used and no secondary ports.
        % firstIPPort:  The first udp port to output on. This will be use for channel 1.
        %               Subsequent ports for channels are every other port. So for example if firstIPPort is 20000:
        %                   channel 1 is output on 20000
        %                   channel 2 is output on 20002
        %                   channel 3 is output on 20004
        %               If the channel is negative then the data is output on a secondary port. Example for secondary ports:
        %                   channel 1 is output on 20001
        %                   channel 2 is output on 20003
        %                   channel 3 is output on 20005
        function self = UDPChannelSender(ipAddress, firstIPPort, channelsUsed, samplesPerFrame)
            if isempty(channelsUsed)
                channelsUsed = int32([ 1:100 ]);
            end

            % Determine how many channel slots we need
            cChannelsUsed = numel(channelsUsed);
            cChannelSlots = uint32(0);
            for i = 1 : cChannelsUsed
                channelIndex = channelsUsed(i);
                if channelIndex < 0
                    cChannelSlots = cChannelSlots + 2;
                else 
                    cChannelSlots = cChannelSlots + 1;
                end
            end

            % Pre-allocate storage for coder
            self.channelIndices = zeros(1, cChannelSlots);
            channelSenders      = cell(1, cChannelSlots);

            % We stuff in the first channel first into all slots to keep code happy.
            % Coder wants all cells to have a value and the code in this function is too complicated for it to understand that is the case.
            udpSender = ComplexSingleSamplesUDPSender(ipAddress, firstIPPort +  ((abs(channelsUsed(1)) - 1) * 2) + 1, samplesPerFrame); 
            for i = 1 : cChannelSlots
                channelSenders{i} = udpSender;
            end

            nextChannelSlot = uint32(1);
            for i = 1 : cChannelsUsed
                channelIndex = channelsUsed(i);
                assert(channelIndex ~= 0);
                assert(channelIndex >= -100 && channelIndex <= 100);

                absChannelIndex = abs(channelIndex);

                % Set up main channel output
                ipPort = firstIPPort + ((absChannelIndex - 1) * 2);
                fprintf("Setting up main channel %u port %u\n", uint32(absChannelIndex), uint32(ipPort));
                udpSender = ComplexSingleSamplesUDPSender(ipAddress, ipPort, samplesPerFrame);

                self.channelIndices(nextChannelSlot)    = absChannelIndex;
                channelSenders{nextChannelSlot}         = udpSender;
                nextChannelSlot                         = nextChannelSlot + 1;

                if channelIndex < 0
                    % Set up secondary channel output
                    ipPort = firstIPPort + ((absChannelIndex - 1) * 2) + 1;
                    fprintf("Setting up secondary channel %u port %u\n", uint32(absChannelIndex), uint32(ipPort));
                    udpSender = ComplexSingleSamplesUDPSender(ipAddress, firstIPPort +  ((absChannelIndex - 1) * 2) + 1, samplesPerFrame); 
                    self.channelIndices(nextChannelSlot)    = absChannelIndex;
                    channelSenders{nextChannelSlot}         = udpSender;
                    nextChannelSlot                         = nextChannelSlot + 1;
                end
            end
            self.channelSenders = channelSenders;
        end

        function sendChannelData(self, channelData, timeStampForSending)
            for i = 1 : numel(self.channelIndices)
                channelIndex    = self.channelIndices(i);
                udpSender       = self.channelSenders{i};
                data            = [ timeStampForSending; channelData(:,abs(channelIndex)) ];
                udpSender.send(data);
            end
        end
    end
end