//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection_data.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "uavrt_detection_data.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"

// Variable Definitions
coder::array<char, 2U> globalThresholdCachePath;

unsigned int state[625];

double freq;

boolean_T freq_not_empty;

omp_nest_lock_t uavrt_detection_nestLockGlobal;

rtRunTimeErrorInfo emlrtRTEI{
    24,      // lineNo
    9,       // colNo
    "error", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/lang/error.m" // pName
};

rtRunTimeErrorInfo b_emlrtRTEI{
    14,      // lineNo
    9,       // colNo
    "log10", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/elfun/log10.m" // pName
};

rtRunTimeErrorInfo c_emlrtRTEI{
    24,     // lineNo
    13,     // colNo
    "feof", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/iofun/feof.m" // pName
};

rtRunTimeErrorInfo d_emlrtRTEI{
    12,               // lineNo
    23,               // colNo
    "mustBePositive", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/validators/"
    "mustBePositive.m" // pName
};

rtRunTimeErrorInfo e_emlrtRTEI{
    18,                     // lineNo
    5,                      // colNo
    "binaryRelopValidator", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/validators/private/"
    "binaryRelopValidator.m" // pName
};

rtRunTimeErrorInfo f_emlrtRTEI{
    86,            // lineNo
    5,             // colNo
    "getFileStar", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/iofun/fseek.m" // pName
};

rtRunTimeErrorInfo j_emlrtRTEI{
    81,         // lineNo
    1,          // colNo
    "eml_find", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/elmat/find.m" // pName
};

rtRunTimeErrorInfo k_emlrtRTEI{
    392,                  // lineNo
    1,                    // colNo
    "find_first_indices", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/elmat/find.m" // pName
};

rtRunTimeErrorInfo l_emlrtRTEI{
    15,                      // lineNo
    9,                       // colNo
    "assertSupportedString", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
    "assertSupportedString.m" // pName
};

rtRunTimeErrorInfo m_emlrtRTEI{
    85,                // lineNo
    27,                // colNo
    "validate_inputs", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
    "nullAssignment.m" // pName
};

rtRunTimeErrorInfo n_emlrtRTEI{
    74,                  // lineNo
    13,                  // colNo
    "reshapeSizeChecks", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
    "reshapeSizeChecks.m" // pName
};

rtRunTimeErrorInfo o_emlrtRTEI{
    81,                  // lineNo
    23,                  // colNo
    "reshapeSizeChecks", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
    "reshapeSizeChecks.m" // pName
};

rtRunTimeErrorInfo p_emlrtRTEI{
    64,                   // lineNo
    15,                   // colNo
    "assertValidSizeArg", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
    "assertValidSizeArg.m" // pName
};

rtDoubleCheckInfo
    emlrtDCI{
        12,       // lineNo
        20,       // colNo
        "blanks", // fName
        "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/strfun/"
        "blanks.m", // pName
        4           // checkKind
    };

rtBoundsCheckInfo emlrtBCI{
    1,                           // iFirst
    600651,                      // iLast
    227,                         // lineNo
    23,                          // colNo
    "",                          // aName
    "AsyncBuffercgHelper/write", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/dsp/dsp/+dsp/+internal/"
    "AsyncBuffercgHelper.m", // pName
    3                        // checkKind
};

rtRunTimeErrorInfo t_emlrtRTEI{
    14,                    // lineNo
    37,                    // colNo
    "validatenonnegative", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/+valattr/"
    "validatenonnegative.m" // pName
};

rtRunTimeErrorInfo u_emlrtRTEI{
    324,                        // lineNo
    13,                         // colNo
    "AsyncBuffercgHelper/read", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/dsp/dsp/+dsp/+internal/"
    "AsyncBuffercgHelper.m" // pName
};

rtRunTimeErrorInfo y_emlrtRTEI{
    13,                 // lineNo
    37,                 // colNo
    "validatenonempty", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/+valattr/"
    "validatenonempty.m" // pName
};

rtRunTimeErrorInfo ab_emlrtRTEI{
    14,               // lineNo
    37,               // colNo
    "validatenonnan", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/+valattr/"
    "validatenonnan.m" // pName
};

rtRunTimeErrorInfo bb_emlrtRTEI{
    14,               // lineNo
    37,               // colNo
    "validatefinite", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/+valattr/"
    "validatefinite.m" // pName
};

rtRunTimeErrorInfo cb_emlrtRTEI{
    53,       // lineNo
    15,       // colNo
    "bsxfun", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/elmat/bsxfun.m" // pName
};

rtRunTimeErrorInfo fb_emlrtRTEI{
    13,                // lineNo
    37,                // colNo
    "validateinteger", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/+valattr/"
    "validateinteger.m" // pName
};

rtBoundsCheckInfo k_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    84,                 // lineNo
    38,                 // colNo
    "",                 // aName
    "computeDFTviaFFT", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/private/"
    "computeDFT.m", // pName
    0               // checkKind
};

rtBoundsCheckInfo l_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    85,                 // lineNo
    14,                 // colNo
    "",                 // aName
    "computeDFTviaFFT", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/private/"
    "computeDFT.m", // pName
    0               // checkKind
};

rtEqualityCheckInfo
    d_emlrtECI{
        -1,                 // nDims
        85,                 // lineNo
        9,                  // colNo
        "computeDFTviaFFT", // fName
        "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/private/"
        "computeDFT.m" // pName
    };

rtRunTimeErrorInfo hb_emlrtRTEI{
    37,    // lineNo
    31,    // colNo
    "fft", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/datafun/fft.m" // pName
};

rtRunTimeErrorInfo ib_emlrtRTEI{
    48,    // lineNo
    35,    // colNo
    "fft", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/datafun/fft.m" // pName
};

rtRunTimeErrorInfo jb_emlrtRTEI{
    52,    // lineNo
    35,    // colNo
    "fft", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/datafun/fft.m" // pName
};

rtRunTimeErrorInfo kb_emlrtRTEI{
    12,                                                             // lineNo
    23,                                                             // colNo
    "datawrap",                                                     // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/eml/datawrap.m" // pName
};

rtDoubleCheckInfo h_emlrtDCI{
    82,                 // lineNo
    16,                 // colNo
    "computeDFTviaFFT", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/private/"
    "computeDFT.m", // pName
    1               // checkKind
};

rtDoubleCheckInfo i_emlrtDCI{
    82,                 // lineNo
    16,                 // colNo
    "computeDFTviaFFT", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/private/"
    "computeDFT.m", // pName
    4               // checkKind
};

rtDoubleCheckInfo j_emlrtDCI{
    82,                 // lineNo
    5,                  // colNo
    "computeDFTviaFFT", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/signal/private/"
    "computeDFT.m", // pName
    1               // checkKind
};

rtBoundsCheckInfo m_emlrtBCI{
    -1,                                                              // iFirst
    -1,                                                              // iLast
    35,                                                              // lineNo
    14,                                                              // colNo
    "",                                                              // aName
    "datawrap",                                                      // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/eml/datawrap.m", // pName
    0 // checkKind
};

rtBoundsCheckInfo n_emlrtBCI{
    -1,                                                              // iFirst
    -1,                                                              // iLast
    35,                                                              // lineNo
    7,                                                               // colNo
    "",                                                              // aName
    "datawrap",                                                      // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/eml/datawrap.m", // pName
    0 // checkKind
};

rtBoundsCheckInfo o_emlrtBCI{
    -1,                                                              // iFirst
    -1,                                                              // iLast
    39,                                                              // lineNo
    7,                                                               // colNo
    "",                                                              // aName
    "datawrap",                                                      // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/eml/datawrap.m", // pName
    0 // checkKind
};

rtBoundsCheckInfo p_emlrtBCI{
    -1,                                                              // iFirst
    -1,                                                              // iLast
    45,                                                              // lineNo
    18,                                                              // colNo
    "",                                                              // aName
    "datawrap",                                                      // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/eml/datawrap.m", // pName
    0 // checkKind
};

rtBoundsCheckInfo q_emlrtBCI{
    -1,                                                              // iFirst
    -1,                                                              // iLast
    45,                                                              // lineNo
    25,                                                              // colNo
    "",                                                              // aName
    "datawrap",                                                      // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/eml/datawrap.m", // pName
    0 // checkKind
};

rtBoundsCheckInfo r_emlrtBCI{
    -1,                                                              // iFirst
    -1,                                                              // iLast
    45,                                                              // lineNo
    11,                                                              // colNo
    "",                                                              // aName
    "datawrap",                                                      // fName
    "/Applications/MATLAB_R2023b.app/toolbox/signal/eml/datawrap.m", // pName
    0 // checkKind
};

rtRunTimeErrorInfo lb_emlrtRTEI{
    13,               // lineNo
    13,               // colNo
    "toLogicalCheck", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
    "toLogicalCheck.m" // pName
};

rtRunTimeErrorInfo nb_emlrtRTEI{
    58,                   // lineNo
    23,                   // colNo
    "assertValidSizeArg", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
    "assertValidSizeArg.m" // pName
};

rtRunTimeErrorInfo ob_emlrtRTEI{
    13,                     // lineNo
    27,                     // colNo
    "assertCompatibleDims", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/shared/coder/coder/lib/+coder/"
    "+internal/assertCompatibleDims.m" // pName
};

rtRunTimeErrorInfo pb_emlrtRTEI{
    159,                    // lineNo
    13,                     // colNo
    "coderTimeCheckStatus", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/shared/coder/coder/lib/+coder/"
    "+internal/+time/CoderTimeAPI.m" // pName
};

rtEqualityCheckInfo e_emlrtECI{
    -1,                          // nDims
    227,                         // lineNo
    13,                          // colNo
    "AsyncBuffercgHelper/write", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/dsp/dsp/+dsp/+internal/"
    "AsyncBuffercgHelper.m" // pName
};

rtRunTimeErrorInfo ub_emlrtRTEI{
    288,                   // lineNo
    27,                    // colNo
    "check_non_axis_size", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/cat.m" // pName
};

rtRunTimeErrorInfo yb_emlrtRTEI{
    79,                  // lineNo
    23,                  // colNo
    "reshapeSizeChecks", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
    "reshapeSizeChecks.m" // pName
};

rtRunTimeErrorInfo cc_emlrtRTEI{
    134,             // lineNo
    27,              // colNo
    "unaryMinOrMax", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
    "unaryMinOrMax.m" // pName
};

rtRunTimeErrorInfo ec_emlrtRTEI{
    13,     // lineNo
    9,      // colNo
    "sqrt", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/elfun/sqrt.m" // pName
};

rtRunTimeErrorInfo gc_emlrtRTEI{
    1626,              // lineNo
    31,                // colNo
    "assertValidSize", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/shared/coder/coder/+coder/"
    "+internal/@sparse/sparse.m" // pName
};

rtDoubleCheckInfo o_emlrtDCI{
    1495,                  // lineNo
    44,                    // colNo
    "sparse/nullcopyLike", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/shared/coder/coder/+coder/"
    "+internal/@sparse/sparse.m", // pName
    4                             // checkKind
};

rtRunTimeErrorInfo jc_emlrtRTEI{
    18,                               // lineNo
    27,                               // colNo
    "eml_int_forloop_overflow_check", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/eml/"
    "eml_int_forloop_overflow_check.m" // pName
};

rtRunTimeErrorInfo kc_emlrtRTEI{
    133,                   // lineNo
    23,                    // colNo
    "dynamic_size_checks", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/ops/"
    "eml_mtimes_helper.m" // pName
};

rtRunTimeErrorInfo lc_emlrtRTEI{
    138,                   // lineNo
    23,                    // colNo
    "dynamic_size_checks", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/ops/"
    "eml_mtimes_helper.m" // pName
};

rtRunTimeErrorInfo
    pc_emlrtRTEI{
        28,        // lineNo
        19,        // colNo
        "sub2ind", // fName
        "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
        "sub2ind.m" // pName
    };

rtRunTimeErrorInfo uc_emlrtRTEI{
    48,        // lineNo
    5,         // colNo
    "fprintf", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/iofun/fprintf.m" // pName
};

rtRunTimeErrorInfo vc_emlrtRTEI{
    125,        // lineNo
    17,         // colNo
    "cfprintf", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/iofun/fprintf.m" // pName
};

const boolean_T bv[128]{
    false, false, false, false, false, false, false, false, false, true,  true,
    true,  true,  true,  false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, true,  true,  true,  true,  true,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false};

const char cv1[22]{'c', 'o', 'd', 'e', 'r', 'I', 'n', 'i', 't', 'T', 'i',
                   'm', 'e', 'F', 'u', 'n', 'c', 't', 'i', 'o', 'n', 's'};

const char cv2[30]{'c', 'o', 'd', 'e', 'r', 'T', 'i', 'm', 'e', 'C',
                   'l', 'o', 'c', 'k', 'G', 'e', 't', 't', 'i', 'm',
                   'e', 'M', 'o', 'n', 'o', 't', 'o', 'n', 'i', 'c'};

boolean_T isInitialized_uavrt_detection{false};

//
// File trailer for uavrt_detection_data.cpp
//
// [EOF]
//
