###########################################################################
## Makefile generated for component 'airspy_channelize'. 
## 
## Makefile     : airspy_channelize_rtw.mk
## Generated on : Sun Feb 26 11:46:46 2023
## Final product: $(START_DIR)\airspy_channelize.exe
## Product type : executable
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPILER_COMMAND_FILE   Compiler command listing model reference header paths
# CMD_FILE                Command file

PRODUCT_NAME              = airspy_channelize
MAKEFILE                  = airspy_channelize_rtw.mk
MATLAB_ROOT               = C:\PROGRA~1\MATLAB
MATLAB_BIN                = C:\PROGRA~1\MATLAB\bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)\win64
START_DIR                 = H:\repos\airspy_channelize
TGT_FCN_LIB               = ISO_C++11
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = ..\..\..
COMPILER_COMMAND_FILE     = airspy_channelize_rtw_comp.rsp
CMD_FILE                  = airspy_channelize_rtw.rsp
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 
NODEBUG                   = 1

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          Microsoft Visual C++ 2022 v17.0 | nmake (64-bit Windows)
# Supported Version(s):    17.0
# ToolchainInfo Version:   2022a
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# NODEBUG
# cvarsdll
# cvarsmt
# conlibsmt
# ldebug
# conflags
# cflags

#-----------
# MACROS
#-----------

MW_EXTERNLIB_DIR    = $(MATLAB_ROOT)\extern\lib\win64\microsoft
MW_LIB_DIR          = $(MATLAB_ROOT)\lib\win64
CPU                 = AMD64
APPVER              = 5.02
CVARSFLAG           = $(cvarsmt)
CFLAGS_ADDITIONAL   = -D_CRT_SECURE_NO_WARNINGS
CPPFLAGS_ADDITIONAL = -EHs -D_CRT_SECURE_NO_WARNINGS /wd4251 /Zc:__cplusplus
LIBS_TOOLCHAIN      = $(conlibs)

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: Microsoft Visual C Compiler
CC = cl

# Linker: Microsoft Visual C Linker
LD = link

# C++ Compiler: Microsoft Visual C++ Compiler
CPP = cl

# C++ Linker: Microsoft Visual C++ Linker
CPP_LD = link

# Archiver: Microsoft Visual C/C++ Archiver
AR = lib

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)\mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: NMAKE Utility
MAKE = nmake


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -Zi
C_OUTPUT_FLAG       = -Fo
LDDEBUG             = /DEBUG
OUTPUT_FLAG         = -out:
CPPDEBUG            = -Zi
CPP_OUTPUT_FLAG     = -Fo
CPPLDDEBUG          = /DEBUG
OUTPUT_FLAG         = -out:
ARDEBUG             =
STATICLIB_OUTPUT_FLAG = -out:
MEX_DEBUG           = -g
RM                  = @del
ECHO                = @echo
MV                  = @ren
RUN                 = @cmd /C

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = /nologo
CFLAGS               = $(cflags) $(CVARSFLAG) $(CFLAGS_ADDITIONAL) \
                       /O2 /Oy-
CPPFLAGS             = /TP $(cflags) $(CVARSFLAG) $(CPPFLAGS_ADDITIONAL) \
                       /O2 /Oy-
CPP_LDFLAGS          = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN)
CPP_SHAREDLIB_LDFLAGS  = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN) \
                         -dll -def:$(DEF_FILE)
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN)
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN) \
                       -dll -def:$(DEF_FILE)



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(START_DIR)\airspy_channelize.exe
PRODUCT_TYPE = "executable"
BUILD_TYPE = "Executable"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = 

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

SRCS = udp.cpp $(START_DIR)\codegen\exe\airspy_channelize\coder_posix_time.c $(START_DIR)\codegen\exe\airspy_channelize\airspy_channelize_data.cpp $(START_DIR)\codegen\exe\airspy_channelize\rt_nonfinite.cpp $(START_DIR)\codegen\exe\airspy_channelize\rtGetNaN.cpp $(START_DIR)\codegen\exe\airspy_channelize\rtGetInf.cpp $(START_DIR)\codegen\exe\airspy_channelize\airspy_channelize_initialize.cpp $(START_DIR)\codegen\exe\airspy_channelize\airspy_channelize_terminate.cpp $(START_DIR)\codegen\exe\airspy_channelize\airspy_channelize.cpp $(START_DIR)\codegen\exe\airspy_channelize\colon.cpp $(START_DIR)\codegen\exe\airspy_channelize\validator_check_size.cpp $(START_DIR)\codegen\exe\airspy_channelize\int2str.cpp $(START_DIR)\codegen\exe\airspy_channelize\tic.cpp $(START_DIR)\codegen\exe\airspy_channelize\timeKeeper.cpp $(START_DIR)\codegen\exe\airspy_channelize\getLocalTime.cpp $(START_DIR)\codegen\exe\airspy_channelize\plus.cpp $(START_DIR)\codegen\exe\airspy_channelize\toc.cpp $(START_DIR)\codegen\exe\airspy_channelize\CoderTimeAPI.cpp $(START_DIR)\codegen\exe\airspy_channelize\eml_int_forloop_overflow_check.cpp $(START_DIR)\codegen\exe\airspy_channelize\AsyncBuffercgHelper.cpp $(START_DIR)\codegen\exe\airspy_channelize\AsyncBuffer.cpp $(START_DIR)\codegen\exe\airspy_channelize\Channelizer.cpp $(START_DIR)\codegen\exe\airspy_channelize\ComplexSingleSamplesUDPReceiver.cpp $(START_DIR)\codegen\exe\airspy_channelize\UDPChannelSender.cpp $(START_DIR)\codegen\exe\airspy_channelize\datetime.cpp $(START_DIR)\codegen\exe\airspy_channelize\FFTImplementationCallback.cpp $(START_DIR)\codegen\exe\airspy_channelize\airspy_channelize_rtwutil.cpp

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = udp.obj coder_posix_time.obj airspy_channelize_data.obj rt_nonfinite.obj rtGetNaN.obj rtGetInf.obj airspy_channelize_initialize.obj airspy_channelize_terminate.obj airspy_channelize.obj colon.obj validator_check_size.obj int2str.obj tic.obj timeKeeper.obj getLocalTime.obj plus.obj toc.obj CoderTimeAPI.obj eml_int_forloop_overflow_check.obj AsyncBuffercgHelper.obj AsyncBuffer.obj Channelizer.obj ComplexSingleSamplesUDPReceiver.obj UDPChannelSender.obj datetime.obj FFTImplementationCallback.obj airspy_channelize_rtwutil.obj

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

SYSTEM_LIBS =  /LIBPATH:"$(MATLAB_ROOT)\bin\win64" "$(MATLAB_ROOT)\bin\win64\libiomp5md.lib"

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_ = /source-charset:utf-8
CFLAGS_OPTS = /openmp /wd4101
CFLAGS_BASIC = $(DEFINES) @$(COMPILER_COMMAND_FILE)

CFLAGS = $(CFLAGS) $(CFLAGS_) $(CFLAGS_OPTS) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_ = /source-charset:utf-8
CPPFLAGS_OPTS = /openmp /wd4101
CPPFLAGS_BASIC = $(DEFINES) @$(COMPILER_COMMAND_FILE)

CPPFLAGS = $(CPPFLAGS) $(CPPFLAGS_) $(CPPFLAGS_OPTS) $(CPPFLAGS_BASIC)

#---------------
# C++ Linker
#---------------

CPP_LDFLAGS_ = /nodefaultlib:vcomp  

CPP_LDFLAGS = $(CPP_LDFLAGS) $(CPP_LDFLAGS_)

#------------------------------
# C++ Shared Library Linker
#------------------------------

CPP_SHAREDLIB_LDFLAGS_ = /nodefaultlib:vcomp  

CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS) $(CPP_SHAREDLIB_LDFLAGS_)

#-----------
# Linker
#-----------

LDFLAGS_ = /nodefaultlib:vcomp  

LDFLAGS = $(LDFLAGS) $(LDFLAGS_)

#--------------------------
# Shared Library Linker
#--------------------------

SHAREDLIB_LDFLAGS_ = /nodefaultlib:vcomp  

SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS) $(SHAREDLIB_LDFLAGS_)

###########################################################################
## INLINED COMMANDS
###########################################################################


!include $(MATLAB_ROOT)\rtw\c\tools\vcdefs.mak


###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build buildobj clean info prebuild download execute set_environment_variables


all : build
	@cmd /C "@echo ### Successfully generated all binary outputs."


build : set_environment_variables prebuild $(PRODUCT)


buildobj : set_environment_variables prebuild $(OBJS) $(PREBUILT_OBJS)
	@cmd /C "@echo ### Successfully generated all binary outputs."


prebuild : 


download : $(PRODUCT)


execute : download
	@cmd /C "@echo ### Invoking postbuild tool "Execute" ..."
	$(EXECUTE) $(EXECUTE_FLAGS)
	@cmd /C "@echo ### Done invoking postbuild tool."


set_environment_variables : 
	@set INCLUDE=$(INCLUDES);$(INCLUDE)
	@set LIB=$(LIB)


###########################################################################
## FINAL TARGET
###########################################################################

#-------------------------------------------
# Create a standalone executable            
#-------------------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@cmd /C "@echo ### Creating standalone executable "$(PRODUCT)" ..."
	$(CPP_LD) $(CPP_LDFLAGS) -out:$(PRODUCT) @$(CMD_FILE) $(SYSTEM_LIBS) $(TOOLCHAIN_LIBS)
	@cmd /C "@echo ### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(RELATIVE_PATH_TO_ANCHOR)}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(RELATIVE_PATH_TO_ANCHOR)}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(START_DIR)\codegen\exe\airspy_channelize}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(START_DIR)\codegen\exe\airspy_channelize}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(START_DIR)}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(START_DIR)}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


coder_posix_time.obj : "$(START_DIR)\codegen\exe\airspy_channelize\coder_posix_time.c"
	$(CC) $(CFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\coder_posix_time.c"


airspy_channelize_data.obj : "$(START_DIR)\codegen\exe\airspy_channelize\airspy_channelize_data.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\airspy_channelize_data.cpp"


rt_nonfinite.obj : "$(START_DIR)\codegen\exe\airspy_channelize\rt_nonfinite.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\rt_nonfinite.cpp"


rtGetNaN.obj : "$(START_DIR)\codegen\exe\airspy_channelize\rtGetNaN.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\rtGetNaN.cpp"


rtGetInf.obj : "$(START_DIR)\codegen\exe\airspy_channelize\rtGetInf.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\rtGetInf.cpp"


airspy_channelize_initialize.obj : "$(START_DIR)\codegen\exe\airspy_channelize\airspy_channelize_initialize.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\airspy_channelize_initialize.cpp"


airspy_channelize_terminate.obj : "$(START_DIR)\codegen\exe\airspy_channelize\airspy_channelize_terminate.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\airspy_channelize_terminate.cpp"


airspy_channelize.obj : "$(START_DIR)\codegen\exe\airspy_channelize\airspy_channelize.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\airspy_channelize.cpp"


colon.obj : "$(START_DIR)\codegen\exe\airspy_channelize\colon.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\colon.cpp"


validator_check_size.obj : "$(START_DIR)\codegen\exe\airspy_channelize\validator_check_size.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\validator_check_size.cpp"


int2str.obj : "$(START_DIR)\codegen\exe\airspy_channelize\int2str.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\int2str.cpp"


tic.obj : "$(START_DIR)\codegen\exe\airspy_channelize\tic.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\tic.cpp"


timeKeeper.obj : "$(START_DIR)\codegen\exe\airspy_channelize\timeKeeper.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\timeKeeper.cpp"


getLocalTime.obj : "$(START_DIR)\codegen\exe\airspy_channelize\getLocalTime.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\getLocalTime.cpp"


plus.obj : "$(START_DIR)\codegen\exe\airspy_channelize\plus.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\plus.cpp"


toc.obj : "$(START_DIR)\codegen\exe\airspy_channelize\toc.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\toc.cpp"


CoderTimeAPI.obj : "$(START_DIR)\codegen\exe\airspy_channelize\CoderTimeAPI.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\CoderTimeAPI.cpp"


eml_int_forloop_overflow_check.obj : "$(START_DIR)\codegen\exe\airspy_channelize\eml_int_forloop_overflow_check.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\eml_int_forloop_overflow_check.cpp"


AsyncBuffercgHelper.obj : "$(START_DIR)\codegen\exe\airspy_channelize\AsyncBuffercgHelper.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\AsyncBuffercgHelper.cpp"


AsyncBuffer.obj : "$(START_DIR)\codegen\exe\airspy_channelize\AsyncBuffer.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\AsyncBuffer.cpp"


Channelizer.obj : "$(START_DIR)\codegen\exe\airspy_channelize\Channelizer.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\Channelizer.cpp"


ComplexSingleSamplesUDPReceiver.obj : "$(START_DIR)\codegen\exe\airspy_channelize\ComplexSingleSamplesUDPReceiver.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\ComplexSingleSamplesUDPReceiver.cpp"


UDPChannelSender.obj : "$(START_DIR)\codegen\exe\airspy_channelize\UDPChannelSender.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\UDPChannelSender.cpp"


datetime.obj : "$(START_DIR)\codegen\exe\airspy_channelize\datetime.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\datetime.cpp"


FFTImplementationCallback.obj : "$(START_DIR)\codegen\exe\airspy_channelize\FFTImplementationCallback.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\FFTImplementationCallback.cpp"


airspy_channelize_rtwutil.obj : "$(START_DIR)\codegen\exe\airspy_channelize\airspy_channelize_rtwutil.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\exe\airspy_channelize\airspy_channelize_rtwutil.cpp"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(COMPILER_COMMAND_FILE) $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@cmd /C "@echo ### PRODUCT = $(PRODUCT)"
	@cmd /C "@echo ### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@cmd /C "@echo ### BUILD_TYPE = $(BUILD_TYPE)"
	@cmd /C "@echo ### INCLUDES = $(INCLUDES)"
	@cmd /C "@echo ### DEFINES = $(DEFINES)"
	@cmd /C "@echo ### ALL_SRCS = $(ALL_SRCS)"
	@cmd /C "@echo ### ALL_OBJS = $(ALL_OBJS)"
	@cmd /C "@echo ### LIBS = $(LIBS)"
	@cmd /C "@echo ### MODELREF_LIBS = $(MODELREF_LIBS)"
	@cmd /C "@echo ### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@cmd /C "@echo ### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@cmd /C "@echo ### CFLAGS = $(CFLAGS)"
	@cmd /C "@echo ### LDFLAGS = $(LDFLAGS)"
	@cmd /C "@echo ### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@cmd /C "@echo ### CPPFLAGS = $(CPPFLAGS)"
	@cmd /C "@echo ### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@cmd /C "@echo ### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@cmd /C "@echo ### ARFLAGS = $(ARFLAGS)"
	@cmd /C "@echo ### MEX_CFLAGS = $(MEX_CFLAGS)"
	@cmd /C "@echo ### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@cmd /C "@echo ### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@cmd /C "@echo ### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@cmd /C "@echo ### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@cmd /C "@echo ### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@cmd /C "@echo ### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	@if exist $(PRODUCT) $(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(ECHO) "### Deleted all derived files."


