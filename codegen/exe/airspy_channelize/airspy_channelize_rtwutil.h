//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: airspy_channelize_rtwutil.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Apr-2023 16:45:43
//

#ifndef AIRSPY_CHANNELIZE_RTWUTIL_H
#define AIRSPY_CHANNELIZE_RTWUTIL_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>
#include <string>

// Type Declarations
struct rtBoundsCheckInfo;

struct rtDoubleCheckInfo;

struct rtEqualityCheckInfo;

// Function Declarations
extern void b_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

extern void b_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void c_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void f_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void g_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void h_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void rtDynamicBoundsError(int aIndexValue, int aLoBound, int aHiBound,
                                 const rtBoundsCheckInfo *aInfo);

extern void rtErrorWithMessageID(const std::string r, const std::string r1,
                                 const char *r2, const char *aFcnName,
                                 int aLineNum);

extern void rtErrorWithMessageID(const std::string r, const int i,
                                 const char *aFcnName, int aLineNum);

extern void rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void rtErrorWithMessageID(const char *r, const char *aFcnName,
                                 int aLineNum);

extern std::string rtGenSizeString(const int *aDims);

extern boolean_T rtIsNullOrEmptyString(const char *aString);

extern void rtNonNegativeError(const double aPositive,
                               const rtDoubleCheckInfo *aInfo);

extern void rtSubAssignSizeCheck(const int *aDims1, const int *aDims2,
                                 const rtEqualityCheckInfo *aInfo);

#endif
//
// File trailer for airspy_channelize_rtwutil.h
//
// [EOF]
//
