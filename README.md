# airspy_channelize
This code allows incoming SDR data to be channelized and provided to other processes via UDP. 

The initial goal of this development was to enable complex IQ data streaming from an Airspy SDR to be brought into Matlab for processing. The resulting code should work though for any process that needs to receive channelized data streams. This software sits between the incoming high sample rate data and processes running on a machine that might want access to one or more channels at a lower sample rate. This code was developed in Matlab and can be converted to an executable using Matlab Coder. Instructions to do so are contained within this REAME. Some of the Matlab functions developed here has some interesting methods necessitated by the restrictions on system objects in Matlab when using Matlab Coder. 

**NOTE: This software only currently supports incoming sample rates of 375000 samples per second and channelizing to 100 or 200 channels. It is based on the [airspyhf_channelize](https://github.com/dynamic-and-active-systems-lab/airspyhf_channelize) software, but has been simplified to be specifically designed for the UAV-RT project. Used in conjunction with airspy_decimate and incoming Airspy Mini IQ data at 3 MSPS, airspy_channelize will output 100 channels via UDP, each at 3750 complex samples per second. ** 

The development of this code was funded via [National Science Foundation grant no. 2104570](https://nsf.gov/awardsearch/showAward?AWD_ID=2104570&HistoricalAwards=false).

## Pre-reqs
- [Airspy Mini](https://airspy.com/airspy-mini/): Details on the install can be seen at this link or at the bottom of this readme. 
- [airspy_decimate](https://github.com/dynamic-and-active-systems-lab/airspy_decimate): Program to decimate the 3 MSPS Airspy Mini data down to 375 KSPS. 
- Netcat must be installed on your machine to move data from airspyhf_rx to the channelizer via UDP.
- Running either of the the `airspy_channelize_codegen_script_***` scripts requires that [Matlab Coder](https://www.mathworks.com/products/matlab-coder.html) be installed with your Matlab install. This requires an installed compiler on your machine. More information on Coder requirements can be found [here](https://www.mathworks.com/help/coder/gs/installing-prerequisite-products.html). For macOS, XCode should be installed (don't forget to [accept the license agreement](https://stackoverflow.com/questions/31384994/how-to-accept-xcode-license) or you might get errors). For Linux systems, you need to have the `build-essentials` package installed. Additionally, the Matlab DSP toolbox must be installed, as the channelizer uses DSP objects. Note that if you generate an executable using Coder or gcc, the resulting executable does not depend on the Matlab install. Matlab is only needed at the time of code generation. 

## Setup
### Setup for running in Matlab
After cloning this repo, the airspy_channelize.m function can be run directly in Matlab. No additional setup should be needed.
### Setup for building a compiled executable 
The `airspy_channelize` function can be converted to an executable using Matlab Coder. In this way the channelizer will not require Matlab to run. Steps to build:

* Run 'airspy_channelize_codegen_script.m' in Matlab. This will create the codegen directory of source code.
* Run 'make -f matlab-coder-utils/Makefile PRODUCT_NAME=airspy_channelize' from the root airspy_channelize directory at the command prompt. This will create an 'airspy_channelize' executable.

## Basic Operation
### Starting the program
When compiled to an executable you can specified the channels you want output to udp on the command line. 

The relationship of specified channels to udo port is as follows:

If the channel specified is a positive value:
* channel 1 is output on 20000
* channel 2 is output on 20002
* channel 3 is output on 20004

If the channel specified is negative then the data is output on a secondary port as well as the main port. Example for secondary ports:
* channel 1 is also output on 20001
* channel 2 is also output on 20003
* channel 3 is also output on 20005

If no channel list is specified on the command line then all 100 channels are output on the main ports.

Example command line usage:

`airspy_channelize 1 -3`

Results in the following ports being output:
* channel 1 is output on 20000
* channel 3 is output on 20004 and 2005

### Starting the incoming SDR data
The data coming into the channelizer program should be served on local port 10000. For example, after starting the channelizer program the folling terminal commands should would be issued in separate terminal windows. 

`airspy_rx -f 148.523 -r - -p 0 -a 3000000 -t 0  -d | netcat -u localhost 40000`

`decimate_8`

This requires the installation of [airspy_rx](https://github.com/airspy/airspyone_host) and [airspy_decimate](https://github.com/dynamic-and-active-systems-lab/airspy_decimate). Installation instructions for this can be found [below](https://github.com/dynamic-and-active-systems-lab/airspy_channelize#installing-airspy_rx). This pipes data from airspy_rx to netcat, which then sends the data to the decimator, which decimates the incoming data and sends the data via UDP to port 10000. The `airspy_channelize` function requires single precision complex data with frame lengths of 128 complex samples.

### Controlling operation
After running these two commands the program will start up but will initially be in an idle stat. There are three states of operation: 1) Idle/Pause 2) Running 3) Dead/Killed. The program starts in the 'Run' state. The program accepts commands to transition between states from local port 10001. Transmitting a 1 will start the channelization and output. Transmitting a 0 will pause the operation and put the program into a idle state. Transmitting a -1 will terminate the program. In a separate terminal window, transmit the start, pause, or kill commands with commands: 

Start: `echo -e -n '\x01'| netcat -u -c localhost 10001`

Pause: `echo -e -n '\x00'| netcat -u -c localhost 10001`

Kill:  `echo -e -n '\xFF'| netcat -u -c localhost 10001`

### Receiving channelized data

Because the channelized data is served via UDP ports, the outputs can be used by any program capable of UDP data. 

Note about channel frequencies: Matlab provides the centerFrequencies function that accepts a channelizer object and a sample rate, and then specifies the center frequencies of the associated channel. This list however is centered at zero and provides negative frequencies. For example a channelizer with Fs = 48000 and a decimation factor of 3 would report center frequencies [-24000 -12000 0 12000]. If the fvtool is used on this channelizer (with the legend turned on) the center frequencies would be [0 12000 -24000 -12000] for filteres 1-4. The shifting here reflects a inconsistency in Matlab's channel reporting. The channelizer outputs follow the latter order, and as such, so to do the UDP port outputs in this function. Because the  number of chanels and the decimation are the same, the frequency of these channels are `-Fs/nc*floor(nc/2)<fc<Fs/2`, (where nc is the number of channels), if nc is odd. For even nc, `-Fs/2 < fc < Fs/2-Fs/nc`. In both cases the frequency steps are `Fs/nc`. This was determined by using the centerFrequencies.m function on example channelizer objects. If using the centerFrequencies output the circshift command can be used to get the correct order of channel frequency. For example: `circshift(centerFrequencies(channizerObject,48000),ceil(numChannels/2)).`


## Installing airspy_rx
[airspy_rx](https://github.com/airspy/airspyone_host/blob/master/airspy-tools/src/airspy_rx.c) is useful for manual control of the [Airspy Mini](https://airspy.com/airspy-mini/) software defined radio. 

#### Linux installation 
https://github.com/airspy/airspyone_host#how-to-build-the-host-software-on-linux

The instrunctions for installing airspyhf on Linux can be found in the airspyhf repo under "[How to build the host software on Linux](https://github.com/airspy/airspyone_host#how-to-build-the-host-software-on-linux)". This will include the dependencies necessary for the installation and use of airspyhf. 

#### macOS installation 

To install this on macOS, you'll need to do a few things first:

1. [Ensure homebrew is installed](https://brew.sh/) and run brew doctor to see if any errors come up 
2. Ensure homebrew is updated by running the following command in a terminal window brew update 
3. Need wget: run the following command in a terminal window brew install wget 
4. Need cmake: run the following command in a terminal window brew install cmake 
5. Need libusb: run the following command in a terminal window brew install libusb

To install airspy, open a terminal directory where you want airspyone_host-master directory downloaded to. You don't need to keep this directory after installing. Now, run the commands below for building and installing. 
```
wget https://github.com/airspy/airspyone_host/archive/master.zip
unzip master.zip
cd airspyone_host-master
mkdir build
cd build
export CMAKE_PREFIX_PATH=/usr/local/Cellar/libusb/1.0.24/include/libusb-1.0
cmake ../ -DINSTALL_UDEV_RULES=ON
make
sudo make install
```
That's it. It should be installed. 

All of the instructions here are the same as those found in the repo under "[How to build the host software on Linux](https://github.com/airspy/airspyone_host#how-to-build-the-host-software-on-linux)" except for the export command. CMake doesn't know how to find libusb, so we run the export command to tell it where it is. It's a temp fix in that if you run CMake for this build process again, you'll have to do the same thing. But you would only need to run CMake once theoretically, since we are building/installing and then leaving it be. 
