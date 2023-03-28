//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: airspy_channelize_types.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 28-Mar-2023 15:24:09
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
