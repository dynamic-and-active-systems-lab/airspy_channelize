//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: airspy_channelize_rtwutil.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Apr-2023 15:58:05
//

// Include Files
#include "airspy_channelize_rtwutil.h"
#include "airspy_channelize_types.h"
#include "rt_nonfinite.h"
#include "omp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Definitions
//
// Arguments    : const char *r
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
void b_rtErrorWithMessageID(const char *r, const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "The ") << r)
      << " method cannot be called on an initialized System object or after "
         "calling the release method.";
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
void b_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "The number of channels (number of columns) of the input signal "
               "cannot change.";
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
void c_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Assertion failed.";
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
void f_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "To RESHAPE the number of elements must not change, and if the input "
         "is empty, the maximum dimension length cannot be increased u"
         "nless the output size is fixed.";
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
void g_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "To RESHAPE the number of elements must not change.";
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
void h_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "Number of elements must not change. Use [] as one of the size inputs "
         "to automatically calculate the appropriate size for that di"
         "mension.";
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
// Arguments    : int aIndexValue
//                int aLoBound
//                int aHiBound
//                const rtBoundsCheckInfo *aInfo
// Return Type  : void
//
void rtDynamicBoundsError(int aIndexValue, int aLoBound, int aHiBound,
                          const rtBoundsCheckInfo *aInfo)
{
  std::string b_errMsg;
  std::string errMsg;
  std::stringstream b_outStream;
  std::stringstream outStream;
  if (aLoBound == 0) {
    aIndexValue++;
    aLoBound = 1;
    aHiBound++;
  }
  if (rtIsNullOrEmptyString(aInfo->aName)) {
    ((((((b_outStream << "Index exceeds array dimensions. Index value ")
         << aIndexValue)
        << " exceeds valid range [")
       << aLoBound)
      << "-")
     << aHiBound)
        << "].";
    b_outStream << "\n";
    ((((b_outStream << "Error in ") << aInfo->fName) << " (line ")
     << aInfo->lineNo)
        << ")";
    if (omp_in_parallel()) {
      b_errMsg = b_outStream.str();
      std::fprintf(stderr, "%s", b_errMsg.c_str());
      std::abort();
    } else {
      throw std::runtime_error(b_outStream.str());
    }
  } else {
    ((((((((outStream << "Index exceeds array dimensions. Index value ")
           << aIndexValue)
          << " exceeds valid range [")
         << aLoBound)
        << "-")
       << aHiBound)
      << "] for array \'")
     << aInfo->aName)
        << "\'.";
    outStream << "\n";
    ((((outStream << "Error in ") << aInfo->fName) << " (line ")
     << aInfo->lineNo)
        << ")";
    if (omp_in_parallel()) {
      errMsg = outStream.str();
      std::fprintf(stderr, "%s", errMsg.c_str());
      std::abort();
    } else {
      throw std::runtime_error(outStream.str());
    }
  }
}

//
// Arguments    : const std::string r
//                const std::string r1
//                const char *r2
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
void rtErrorWithMessageID(const std::string r, const std::string r1,
                          const char *r2, const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((((((outStream << "Validation size mismatch: input size ") << r)
      << " ~= allowed size ")
     << r1)
    << " for dimension ")
   << r2)
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
// Arguments    : const std::string r
//                const int i
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
void rtErrorWithMessageID(const std::string r, const int i,
                          const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((((outStream << "Call to \'") << r) << "\' failed with return value ") << i)
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
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
void rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "Detected a run-time error from a call to the function ASSERT or "
         "ERROR, but unable to report the details in standalone code. To s"
         "ee the error message, generate and execute a MEX function.";
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
// Arguments    : const char *r
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
void rtErrorWithMessageID(const char *r, const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "The ") << r)
      << " method cannot be called after calling the release method.";
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
// Arguments    : const int *aDims
// Return Type  : std::string
//
std::string rtGenSizeString(const int *aDims)
{
  std::stringstream outStream;
  outStream << "[";
  outStream << aDims[0];
  outStream << "]";
  return outStream.str();
}

//
// Arguments    : const char *aString
// Return Type  : boolean_T
//
boolean_T rtIsNullOrEmptyString(const char *aString)
{
  return (aString == nullptr) || (*aString == '\x00');
}

//
// Arguments    : const double aPositive
//                const rtDoubleCheckInfo *aInfo
// Return Type  : void
//
void rtNonNegativeError(const double aPositive, const rtDoubleCheckInfo *aInfo)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "Value ") << aPositive)
      << " is not greater than or equal to zero.\nExiting to prevent memory "
         "corruption.";
  outStream << "\n";
  ((((outStream << "Error in ") << aInfo->fName) << " (line ") << aInfo->lineNo)
      << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const int *aDims1
//                const int *aDims2
//                const rtEqualityCheckInfo *aInfo
// Return Type  : void
//
void rtSubAssignSizeCheck(const int *aDims1, const int *aDims2,
                          const rtEqualityCheckInfo *aInfo)
{
  std::string errMsg;
  std::stringstream outStream;
  int i;
  int j;
  i = 0;
  j = 0;
  while ((i < 1) && (j < 1)) {
    while ((i < 1) && (aDims1[i] == 1)) {
      i = 1;
    }
    while ((j < 1) && (aDims2[j] == 1)) {
      j = 1;
    }
    if (((i < 1) || (j < 1)) &&
        ((i == 1) ||
         ((j == 1) || ((aDims1[i] != -1) &&
                       ((aDims2[j] != -1) && (aDims1[i] != aDims2[j])))))) {
      std::string dims1Str;
      std::string dims2Str;
      dims1Str = rtGenSizeString(aDims1);
      dims2Str = rtGenSizeString(aDims2);
      ((((outStream << "Subscripted assignment dimension mismatch: ")
         << dims1Str)
        << " ~= ")
       << dims2Str)
          << ".";
      outStream << "\n";
      ((((outStream << "Error in ") << aInfo->fName) << " (line ")
       << aInfo->lineNo)
          << ")";
      if (omp_in_parallel()) {
        errMsg = outStream.str();
        std::fprintf(stderr, "%s", errMsg.c_str());
        std::abort();
      } else {
        throw std::runtime_error(outStream.str());
      }
    }
    i++;
    j++;
  }
}

//
// File trailer for airspy_channelize_rtwutil.cpp
//
// [EOF]
//
