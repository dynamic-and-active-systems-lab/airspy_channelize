###########################################################################
## Makefile generated for component 'airspy_channelize'. 
## 
## Makefile     : airspy_channelize_rtw.mk
## Generated on : Mon Sep 25 09:03:31 2023
## Final product: $(START_DIR)/airspy_channelize
## Product type : executable
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile

PRODUCT_NAME              = airspy_channelize
MAKEFILE                  = airspy_channelize_rtw.mk
MATLAB_ROOT               = /Applications/MATLAB_R2023a.app
MATLAB_BIN                = /Applications/MATLAB_R2023a.app/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/maci64
START_DIR                 = /Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/airspy_channelize
TGT_FCN_LIB               = ISO_C
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = ../../..
C_STANDARD_OPTS           = -fno-common -fexceptions
CPP_STANDARD_OPTS         = -std=c++14 -fno-common -fexceptions

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          Xcode with Clang | gmake (64-bit Mac)
# Supported Version(s):    
# ToolchainInfo Version:   2023a
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# C_STANDARD_OPTS
# CPP_STANDARD_OPTS

#-----------
# MACROS
#-----------

ARCHS             = x86_64
XCODE_SDK_VER     = $(shell perl $(MATLAB_ROOT)/rtw/c/tools/macsdkver.pl)
XCODE_SDK         = MacOSX$(XCODE_SDK_VER).sdk
XCODE_DEVEL_DIR   = $(shell xcode-select -print-path)
XCODE_SDK_ROOT    = $(XCODE_DEVEL_DIR)/Platforms/MacOSX.platform/Developer/SDKs/$(XCODE_SDK)

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: Clang C Compiler
CC = xcrun clang

# Linker: Clang Linker
LD = xcrun clang++

# C++ Compiler: Clang C++ Compiler
CPP = xcrun clang++

# C++ Linker: Clang C++ Linker
CPP_LD = xcrun clang++

# Archiver: Clang Archiver
AR = xcrun ar

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%/bin/maci64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g
C_OUTPUT_FLAG       = -o
LDDEBUG             = -g
OUTPUT_FLAG         = -o
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = -o
CPPLDDEBUG          = -g
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  = @rm -f
ECHO                = @echo
MV                  = @mv
RUN                 =

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = ruvs
CFLAGS               = -c -isysroot $(XCODE_SDK_ROOT) -arch $(ARCHS) $(C_STANDARD_OPTS) -mmacosx-version-min=10.15 \
                       -O3
CPPFLAGS             = -c -isysroot $(XCODE_SDK_ROOT) -arch $(ARCHS) $(CPP_STANDARD_OPTS) -mmacosx-version-min=10.15 \
                       -O3
CPP_LDFLAGS          = -arch $(ARCHS) -isysroot $(XCODE_SDK_ROOT) -Wl,-rpath,@executable_path -Wl,-rpath,@executable_path/$(RELATIVE_PATH_TO_ANCHOR)
CPP_SHAREDLIB_LDFLAGS  = -arch $(ARCHS)  \
                         -dynamiclib -install_name @rpath/$(notdir $(PRODUCT)) -isysroot $(XCODE_SDK_ROOT) \
                         -Wl,$(LD_NAMESPACE) $(LD_UNDEFS)
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = -arch $(ARCHS) -isysroot $(XCODE_SDK_ROOT) -Wl,-rpath,@executable_path -Wl,-rpath,@executable_path/$(RELATIVE_PATH_TO_ANCHOR)
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -arch $(ARCHS)  \
                       -dynamiclib -install_name @rpath/$(notdir $(PRODUCT)) -isysroot $(XCODE_SDK_ROOT) \
                       -Wl,$(LD_NAMESPACE) $(LD_UNDEFS)



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(START_DIR)/airspy_channelize
PRODUCT_TYPE = "executable"
BUILD_TYPE = "Executable"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR)/codegen/exe/airspy_channelize -I$(START_DIR) -I$(MATLAB_ROOT)/extern/include

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_CUSTOM = 
DEFINES_STANDARD = -DMODEL=airspy_channelize

DEFINES = $(DEFINES_CUSTOM) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = udp.cpp $(START_DIR)/codegen/exe/airspy_channelize/coder_posix_time.c $(START_DIR)/main.c $(START_DIR)/codegen/exe/airspy_channelize/airspy_channelize_data.c $(START_DIR)/codegen/exe/airspy_channelize/rt_nonfinite.c $(START_DIR)/codegen/exe/airspy_channelize/rtGetNaN.c $(START_DIR)/codegen/exe/airspy_channelize/rtGetInf.c $(START_DIR)/codegen/exe/airspy_channelize/airspy_channelize_initialize.c $(START_DIR)/codegen/exe/airspy_channelize/airspy_channelize_terminate.c $(START_DIR)/codegen/exe/airspy_channelize/airspy_channelize.c $(START_DIR)/codegen/exe/airspy_channelize/AsyncBuffer.c $(START_DIR)/codegen/exe/airspy_channelize/AsyncBuffercgHelper.c $(START_DIR)/codegen/exe/airspy_channelize/UDPChannelSender.c $(START_DIR)/codegen/exe/airspy_channelize/tic.c $(START_DIR)/codegen/exe/airspy_channelize/timeKeeper.c $(START_DIR)/codegen/exe/airspy_channelize/ComplexSingleSamplesUDPReceiver.c $(START_DIR)/codegen/exe/airspy_channelize/datetime.c $(START_DIR)/codegen/exe/airspy_channelize/getLocalTime.c $(START_DIR)/codegen/exe/airspy_channelize/plus.c $(START_DIR)/codegen/exe/airspy_channelize/toc.c $(START_DIR)/codegen/exe/airspy_channelize/SystemCore.c $(START_DIR)/codegen/exe/airspy_channelize/FFTImplementationCallback.c $(START_DIR)/codegen/exe/airspy_channelize/CoderTimeAPI.c $(START_DIR)/codegen/exe/airspy_channelize/airspy_channelize_emxutil.c $(START_DIR)/codegen/exe/airspy_channelize/airspy_channelize_rtwutil.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = udp.o coder_posix_time.o main.o airspy_channelize_data.o rt_nonfinite.o rtGetNaN.o rtGetInf.o airspy_channelize_initialize.o airspy_channelize_terminate.o airspy_channelize.o AsyncBuffer.o AsyncBuffercgHelper.o UDPChannelSender.o tic.o timeKeeper.o ComplexSingleSamplesUDPReceiver.o datetime.o getLocalTime.o plus.o toc.o SystemCore.o FFTImplementationCallback.o CoderTimeAPI.o airspy_channelize_emxutil.o airspy_channelize_rtwutil.o

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS =  -L"$(MATLAB_ROOT)/sys/os/maci64" -lm -liomp5

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_OPTS = -Xpreprocessor -fopenmp -I/Applications/MATLAB_R2023a.app/toolbox/eml/externalDependency/omp/maci64/include -DOpenMP_omp_LIBRARY=/Applications/MATLAB_R2023a.app/sys/os/maci64/libiomp5.dylib
CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_OPTS) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_OPTS = -Xpreprocessor -fopenmp -I/Applications/MATLAB_R2023a.app/toolbox/eml/externalDependency/omp/maci64/include -DOpenMP_omp_LIBRARY=/Applications/MATLAB_R2023a.app/sys/os/maci64/libiomp5.dylib
CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += $(CPPFLAGS_OPTS) $(CPPFLAGS_BASIC)

#---------------
# C++ Linker
#---------------

CPP_LDFLAGS_ = -Wl,-rpath,$(MATLAB_ROOT)/sys/os/maci64

CPP_LDFLAGS += $(CPP_LDFLAGS_)

#------------------------------
# C++ Shared Library Linker
#------------------------------

CPP_SHAREDLIB_LDFLAGS_ = -Wl,-rpath,$(MATLAB_ROOT)/sys/os/maci64

CPP_SHAREDLIB_LDFLAGS += $(CPP_SHAREDLIB_LDFLAGS_)

#-----------
# Linker
#-----------

LDFLAGS_ = -Wl,-rpath,$(MATLAB_ROOT)/sys/os/maci64

LDFLAGS += $(LDFLAGS_)

#--------------------------
# Shared Library Linker
#--------------------------

SHAREDLIB_LDFLAGS_ = -Wl,-rpath,$(MATLAB_ROOT)/sys/os/maci64

SHAREDLIB_LDFLAGS += $(SHAREDLIB_LDFLAGS_)

###########################################################################
## INLINED COMMANDS
###########################################################################

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build buildobj clean info prebuild download execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


buildobj : prebuild $(OBJS) $(PREBUILT_OBJS)
	@echo "### Successfully generated all binary outputs."


prebuild : 


download : $(PRODUCT)


execute : download
	@echo "### Invoking postbuild tool "Execute" ..."
	$(EXECUTE) $(EXECUTE_FLAGS)
	@echo "### Done invoking postbuild tool."


###########################################################################
## FINAL TARGET
###########################################################################

#-------------------------------------------
# Create a standalone executable            
#-------------------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@echo "### Creating standalone executable "$(PRODUCT)" ..."
	$(CPP_LD) $(CPP_LDFLAGS) -o $(PRODUCT) $(OBJS) $(SYSTEM_LIBS) $(TOOLCHAIN_LIBS)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.o : %.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : %.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/exe/airspy_channelize/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/exe/airspy_channelize/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


coder_posix_time.o : $(START_DIR)/codegen/exe/airspy_channelize/coder_posix_time.c
	$(CC) $(CFLAGS) -o "$@" "$<"


main.o : $(START_DIR)/main.c
	$(CC) $(CFLAGS) -o "$@" "$<"


airspy_channelize_data.o : $(START_DIR)/codegen/exe/airspy_channelize/airspy_channelize_data.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rt_nonfinite.o : $(START_DIR)/codegen/exe/airspy_channelize/rt_nonfinite.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetNaN.o : $(START_DIR)/codegen/exe/airspy_channelize/rtGetNaN.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetInf.o : $(START_DIR)/codegen/exe/airspy_channelize/rtGetInf.c
	$(CC) $(CFLAGS) -o "$@" "$<"


airspy_channelize_initialize.o : $(START_DIR)/codegen/exe/airspy_channelize/airspy_channelize_initialize.c
	$(CC) $(CFLAGS) -o "$@" "$<"


airspy_channelize_terminate.o : $(START_DIR)/codegen/exe/airspy_channelize/airspy_channelize_terminate.c
	$(CC) $(CFLAGS) -o "$@" "$<"


airspy_channelize.o : $(START_DIR)/codegen/exe/airspy_channelize/airspy_channelize.c
	$(CC) $(CFLAGS) -o "$@" "$<"


AsyncBuffer.o : $(START_DIR)/codegen/exe/airspy_channelize/AsyncBuffer.c
	$(CC) $(CFLAGS) -o "$@" "$<"


AsyncBuffercgHelper.o : $(START_DIR)/codegen/exe/airspy_channelize/AsyncBuffercgHelper.c
	$(CC) $(CFLAGS) -o "$@" "$<"


UDPChannelSender.o : $(START_DIR)/codegen/exe/airspy_channelize/UDPChannelSender.c
	$(CC) $(CFLAGS) -o "$@" "$<"


tic.o : $(START_DIR)/codegen/exe/airspy_channelize/tic.c
	$(CC) $(CFLAGS) -o "$@" "$<"


timeKeeper.o : $(START_DIR)/codegen/exe/airspy_channelize/timeKeeper.c
	$(CC) $(CFLAGS) -o "$@" "$<"


ComplexSingleSamplesUDPReceiver.o : $(START_DIR)/codegen/exe/airspy_channelize/ComplexSingleSamplesUDPReceiver.c
	$(CC) $(CFLAGS) -o "$@" "$<"


datetime.o : $(START_DIR)/codegen/exe/airspy_channelize/datetime.c
	$(CC) $(CFLAGS) -o "$@" "$<"


getLocalTime.o : $(START_DIR)/codegen/exe/airspy_channelize/getLocalTime.c
	$(CC) $(CFLAGS) -o "$@" "$<"


plus.o : $(START_DIR)/codegen/exe/airspy_channelize/plus.c
	$(CC) $(CFLAGS) -o "$@" "$<"


toc.o : $(START_DIR)/codegen/exe/airspy_channelize/toc.c
	$(CC) $(CFLAGS) -o "$@" "$<"


SystemCore.o : $(START_DIR)/codegen/exe/airspy_channelize/SystemCore.c
	$(CC) $(CFLAGS) -o "$@" "$<"


FFTImplementationCallback.o : $(START_DIR)/codegen/exe/airspy_channelize/FFTImplementationCallback.c
	$(CC) $(CFLAGS) -o "$@" "$<"


CoderTimeAPI.o : $(START_DIR)/codegen/exe/airspy_channelize/CoderTimeAPI.c
	$(CC) $(CFLAGS) -o "$@" "$<"


airspy_channelize_emxutil.o : $(START_DIR)/codegen/exe/airspy_channelize/airspy_channelize_emxutil.c
	$(CC) $(CFLAGS) -o "$@" "$<"


airspy_channelize_rtwutil.o : $(START_DIR)/codegen/exe/airspy_channelize/airspy_channelize_rtwutil.c
	$(CC) $(CFLAGS) -o "$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### CPPFLAGS = $(CPPFLAGS)"
	@echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files ..."
	$(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(ECHO) "### Deleted all derived files."


