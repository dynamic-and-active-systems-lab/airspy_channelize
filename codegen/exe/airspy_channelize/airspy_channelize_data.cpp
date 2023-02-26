//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: airspy_channelize_data.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 26-Feb-2023 12:32:19
//

// Include Files
#include "airspy_channelize_data.h"
#include "airspy_channelize_types.h"
#include "rt_nonfinite.h"

// Variable Definitions
double freq;

boolean_T freq_not_empty;

omp_nest_lock_t airspy_channelize_nestLockGlobal;

rtRunTimeErrorInfo emlrtRTEI{
    1,                   // lineNo
    "SystemCore/release" // fName
};

rtRunTimeErrorInfo b_emlrtRTEI{
    24,     // lineNo
    "error" // fName
};

rtBoundsCheckInfo
    emlrtBCI{
        1,                           // iFirst
        204801,                      // iLast
        227,                         // lineNo
        23,                          // colNo
        "",                          // aName
        "AsyncBuffercgHelper/write", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m", // pName
        3                                  // checkKind
    };

rtRunTimeErrorInfo e_emlrtRTEI{
    473,                                        // lineNo
    "AsyncBuffercgHelper/ReadSamplesFromBuffer" // fName
};

rtEqualityCheckInfo
    emlrtECI{
        -1,                                          // nDims
        462,                                         // lineNo
        17,                                          // colNo
        "AsyncBuffercgHelper/ReadSamplesFromBuffer", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m" // pName
    };

rtBoundsCheckInfo
    b_emlrtBCI{
        -1,                                          // iFirst
        -1,                                          // iLast
        462,                                         // lineNo
        50,                                          // colNo
        "",                                          // aName
        "AsyncBuffercgHelper/ReadSamplesFromBuffer", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m", // pName
        0                                  // checkKind
    };

rtBoundsCheckInfo
    c_emlrtBCI{
        -1,                                          // iFirst
        -1,                                          // iLast
        462,                                         // lineNo
        21,                                          // colNo
        "",                                          // aName
        "AsyncBuffercgHelper/ReadSamplesFromBuffer", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m", // pName
        0                                  // checkKind
    };

rtDoubleCheckInfo
    emlrtDCI{
        463,                                         // lineNo
        27,                                          // colNo
        "AsyncBuffercgHelper/ReadSamplesFromBuffer", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m", // pName
        4                                  // checkKind
    };

rtBoundsCheckInfo
    d_emlrtBCI{
        1,                                           // iFirst
        204801,                                      // iLast
        457,                                         // lineNo
        29,                                          // colNo
        "",                                          // aName
        "AsyncBuffercgHelper/ReadSamplesFromBuffer", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m", // pName
        0                                  // checkKind
    };

rtRunTimeErrorInfo f_emlrtRTEI{
    52,                 // lineNo
    "reshapeSizeChecks" // fName
};

rtRunTimeErrorInfo g_emlrtRTEI{
    59,                 // lineNo
    "reshapeSizeChecks" // fName
};

rtRunTimeErrorInfo h_emlrtRTEI{
    93,                    // lineNo
    "validator_check_size" // fName
};

rtRunTimeErrorInfo l_emlrtRTEI{
    159,                   // lineNo
    "coderTimeCheckStatus" // fName
};

rtRunTimeErrorInfo m_emlrtRTEI{
    1,                // lineNo
    "SystemCore/step" // fName
};

rtRunTimeErrorInfo n_emlrtRTEI{
    1,                 // lineNo
    "SystemCore/setup" // fName
};

const char cv[22]{'c', 'o', 'd', 'e', 'r', 'I', 'n', 'i', 't', 'T', 'i',
                  'm', 'e', 'F', 'u', 'n', 'c', 't', 'i', 'o', 'n', 's'};

const char cv1[30]{'c', 'o', 'd', 'e', 'r', 'T', 'i', 'm', 'e', 'C',
                   'l', 'o', 'c', 'k', 'G', 'e', 't', 't', 'i', 'm',
                   'e', 'M', 'o', 'n', 'o', 't', 'o', 'n', 'i', 'c'};

boolean_T isInitialized_airspy_channelize{false};

//
// File trailer for airspy_channelize_data.cpp
//
// [EOF]
//
