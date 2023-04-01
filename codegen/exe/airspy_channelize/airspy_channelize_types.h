//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: airspy_channelize_types.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Apr-2023 15:58:05
//

#ifndef AIRSPY_CHANNELIZE_TYPES_H
#define AIRSPY_CHANNELIZE_TYPES_H

// Include Files
#include "rtwtypes.h"
#define MAX_THREADS omp_get_max_threads()

// Type Definitions
struct rtBoundsCheckInfo {
  int iFirst;
  int iLast;
  int lineNo;
  int colNo;
  const char *aName;
  const char *fName;
  const char *pName;
  int checkKind;
};

struct rtEqualityCheckInfo {
  int nDims;
  int lineNo;
  int colNo;
  const char *fName;
  const char *pName;
};

struct rtDoubleCheckInfo {
  int lineNo;
  int colNo;
  const char *fName;
  const char *pName;
  int checkKind;
};

struct rtRunTimeErrorInfo {
  int lineNo;
  const char *fName;
};

#endif
//
// File trailer for airspy_channelize_types.h
//
// [EOF]
//
