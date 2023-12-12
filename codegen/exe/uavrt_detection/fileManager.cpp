//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fileManager.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "fileManager.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Variable Definitions
static std::FILE *eml_openfiles[20];

static boolean_T eml_autoflush[20];

static rtRunTimeErrorInfo g_emlrtRTEI{
    147,           // lineNo
    5,             // colNo
    "getfilestar", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
    "fileManager.m" // pName
};

static rtRunTimeErrorInfo h_emlrtRTEI{
    297,                     // lineNo
    1,                       // colNo
    "cast_and_validate_fid", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
    "fileManager.m" // pName
};

static rtRunTimeErrorInfo i_emlrtRTEI{
    293,                     // lineNo
    1,                       // colNo
    "cast_and_validate_fid", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
    "fileManager.m" // pName
};

// Function Declarations
namespace coder {
namespace internal {
static signed char filedata();

}
} // namespace coder
static void h_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void sc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : void
// Return Type  : signed char
//
namespace coder {
namespace internal {
static signed char filedata()
{
  int k;
  signed char f;
  boolean_T exitg1;
  f = 0;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 20)) {
    if (eml_openfiles[k] == nullptr) {
      f = static_cast<signed char>(k + 1);
      exitg1 = true;
    } else {
      k++;
    }
  }
  return f;
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
} // namespace internal
} // namespace coder
static void h_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Invalid file identifier.  Use fopen to generate a valid file "
               "identifier.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void sc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "For code generation, maximum number of open files is ") << 20)
      << ".";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : double fid
// Return Type  : int
//
namespace coder {
namespace internal {
int cfclose(double fid)
{
  static rtRunTimeErrorInfo bd_emlrtRTEI{
      168,                 // lineNo
      5,                   // colNo
      "conditionalAssert", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
      "fileManager.m" // pName
  };
  std::FILE *f;
  std::FILE *f_tmp;
  int cst;
  int st;
  signed char fileid;
  st = -1;
  if (fid < 0.0) {
    c_rtErrorWithMessageID(i_emlrtRTEI.fName, i_emlrtRTEI.lineNo);
  }
  fileid = static_cast<signed char>(fid);
  if (fid != static_cast<signed char>(fid)) {
    c_rtErrorWithMessageID(h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
  }
  if (static_cast<int>(fid) != static_cast<signed char>(fid)) {
    fileid = -1;
  }
  if (fileid < 0) {
    c_rtErrorWithMessageID(i_emlrtRTEI.fName, i_emlrtRTEI.lineNo);
  }
  if (fileid >= 3) {
    f_tmp = eml_openfiles[fileid - 3];
    f = f_tmp;
    if (f_tmp == nullptr) {
      h_rtErrorWithMessageID(g_emlrtRTEI.fName, g_emlrtRTEI.lineNo);
    }
  } else if (fileid == 0) {
    f = stdin;
  } else if (fileid == 1) {
    f = stdout;
  } else {
    f = stderr;
  }
  if ((!(f != nullptr)) || (fileid < 3)) {
    c_rtErrorWithMessageID(bd_emlrtRTEI.fName, bd_emlrtRTEI.lineNo);
  }
  cst = std::fclose(f);
  if (cst == 0) {
    st = 0;
    eml_openfiles[fileid - 3] = nullptr;
    eml_autoflush[fileid - 3] = true;
  }
  return st;
}

//
// Arguments    : const array<char, 2U> &cfilename
//                const char *cpermission
// Return Type  : signed char
//
signed char cfopen(const array<char, 2U> &cfilename, const char *cpermission)
{
  static rtRunTimeErrorInfo bd_emlrtRTEI{
      111,      // lineNo
      5,        // colNo
      "cfopen", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
      "fileManager.m" // pName
  };
  std::FILE *filestar;
  array<char, 2U> ccfilename;
  signed char fileid;
  signed char j;
  fileid = -1;
  j = filedata();
  if (j < 1) {
    sc_rtErrorWithMessageID(bd_emlrtRTEI.fName, bd_emlrtRTEI.lineNo);
  } else {
    int i;
    int loop_ub;
    ccfilename.set_size(1, cfilename.size(1) + 1);
    loop_ub = cfilename.size(1);
    for (i = 0; i < loop_ub; i++) {
      ccfilename[i] = cfilename[i];
    }
    ccfilename[cfilename.size(1)] = '\x00';
    filestar = std::fopen(&ccfilename[0], cpermission);
    if (filestar != nullptr) {
      eml_openfiles[j - 1] = filestar;
      eml_autoflush[j - 1] = true;
      i = j + 2;
      if (j + 2 > 127) {
        i = 127;
      }
      fileid = static_cast<signed char>(i);
    }
  }
  return fileid;
}

//
// Arguments    : double fid
//                boolean_T &autoflush
// Return Type  : std::FILE *
//
std::FILE *getfilestar(double fid, boolean_T &autoflush)
{
  std::FILE *filestar;
  std::FILE *filestar_tmp;
  signed char fileid;
  if (fid < 0.0) {
    c_rtErrorWithMessageID(i_emlrtRTEI.fName, i_emlrtRTEI.lineNo);
  }
  fileid = static_cast<signed char>(fid);
  if (fid != static_cast<signed char>(fid)) {
    c_rtErrorWithMessageID(h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
  }
  if (static_cast<int>(fid) != static_cast<signed char>(fid)) {
    fileid = -1;
  }
  if (fileid >= 3) {
    autoflush = eml_autoflush[fileid - 3];
    filestar_tmp = eml_openfiles[fileid - 3];
    filestar = filestar_tmp;
    if (filestar_tmp == nullptr) {
      h_rtErrorWithMessageID(g_emlrtRTEI.fName, g_emlrtRTEI.lineNo);
    }
  } else if (fileid == 0) {
    filestar = stdin;
    autoflush = true;
  } else if (fileid == 1) {
    filestar = stdout;
    autoflush = true;
  } else if (fileid == 2) {
    filestar = stderr;
    autoflush = true;
  } else {
    filestar = nullptr;
    autoflush = true;
  }
  return filestar;
}

//
// Arguments    : void
// Return Type  : void
//
} // namespace internal
} // namespace coder
void filedata_init()
{
  for (int i{0}; i < 20; i++) {
    eml_autoflush[i] = false;
  }
  for (int i{0}; i < 20; i++) {
    eml_openfiles[i] = nullptr;
  }
}

//
// File trailer for fileManager.cpp
//
// [EOF]
//
