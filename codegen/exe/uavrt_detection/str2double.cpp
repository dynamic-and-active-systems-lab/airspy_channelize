//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: str2double.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "str2double.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cstdio>

// Function Declarations
namespace coder {
namespace internal {
static boolean_T b_copysign(array<char, 2U> &s1, int &idx,
                            const array<char, 2U> &s, int &k, int n,
                            boolean_T &success);

static boolean_T b_readfloat(array<char, 2U> &s1, int &idx,
                             const array<char, 2U> &s, int &k, int n,
                             boolean_T &b_finite, double &nfv,
                             boolean_T &foundsign, boolean_T &success);

static boolean_T copydigits(array<char, 2U> &s1, int &idx,
                            const array<char, 2U> &s, int &k, int n,
                            boolean_T allowpoint);

static boolean_T copyexponent(array<char, 2U> &s1, int &idx,
                              const array<char, 2U> &s, int &k, int n);

static boolean_T isUnitImag(const array<char, 2U> &s, int k, int n);

static boolean_T readNonFinite(const array<char, 2U> &s, int &k, int n,
                               double &fv);

static int readfloat(array<char, 2U> &s1, const array<char, 2U> &s, int &k,
                     int n, boolean_T &isimag, boolean_T &b_finite, double &nfv,
                     boolean_T &foundsign, boolean_T &success);

} // namespace internal
} // namespace coder

// Function Definitions
//
// Arguments    : array<char, 2U> &s1
//                int &idx
//                const array<char, 2U> &s
//                int &k
//                int n
//                boolean_T &success
// Return Type  : boolean_T
//
namespace coder {
namespace internal {
static boolean_T b_copysign(array<char, 2U> &s1, int &idx,
                            const array<char, 2U> &s, int &k, int n,
                            boolean_T &success)
{
  boolean_T exitg1;
  boolean_T foundsign;
  boolean_T isneg;
  isneg = false;
  foundsign = false;
  exitg1 = false;
  while ((!exitg1) && (k <= n)) {
    char c;
    c = s[k - 1];
    if (c == '-') {
      isneg = !isneg;
      foundsign = true;
      k++;
    } else if (c == ',') {
      k++;
    } else if (c == '+') {
      foundsign = true;
      k++;
    } else {
      if (static_cast<unsigned char>(c) > 127) {
        tc_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
      }
      if (!bv[static_cast<unsigned char>(c) & 127]) {
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  success = (k <= n);
  if (success && isneg) {
    if ((idx >= 2) && (s1[idx - 2] == '-')) {
      s1[idx - 2] = ' ';
    } else {
      s1[idx - 1] = '-';
      idx++;
    }
  }
  return foundsign;
}

//
// Arguments    : array<char, 2U> &s1
//                int &idx
//                const array<char, 2U> &s
//                int &k
//                int n
//                boolean_T &b_finite
//                double &nfv
//                boolean_T &foundsign
//                boolean_T &success
// Return Type  : boolean_T
//
static boolean_T b_readfloat(array<char, 2U> &s1, int &idx,
                             const array<char, 2U> &s, int &k, int n,
                             boolean_T &b_finite, double &nfv,
                             boolean_T &foundsign, boolean_T &success)
{
  int b_idx;
  boolean_T isimag;
  isimag = false;
  b_finite = true;
  nfv = 0.0;
  b_idx = idx;
  foundsign = b_copysign(s1, b_idx, s, k, n, success);
  idx = b_idx;
  if (success) {
    char c;
    boolean_T exitg1;
    if (isUnitImag(s, k, n)) {
      success = false;
    } else {
      b_finite = readNonFinite(s, k, n, nfv);
      if (b_finite) {
        success = copydigits(s1, idx, s, k, n, true);
        if (success) {
          success = copyexponent(s1, idx, s, k, n);
        }
      } else if ((b_idx >= 2) && (s1[b_idx - 2] == '-')) {
        idx = b_idx - 1;
        s1[b_idx - 2] = ' ';
        nfv = -nfv;
      }
      exitg1 = false;
      while ((!exitg1) && (k <= n)) {
        c = s[k - 1];
        if (static_cast<unsigned char>(c) > 127) {
          tc_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
        }
        if (bv[static_cast<unsigned char>(c) & 127] || (c == '\x00') ||
            (c == ',')) {
          k++;
        } else {
          exitg1 = true;
        }
      }
      if ((k <= n) && (s[k - 1] == '*')) {
        k++;
        exitg1 = false;
        while ((!exitg1) && (k <= n)) {
          c = s[k - 1];
          if (static_cast<unsigned char>(c) > 127) {
            tc_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
          }
          if (bv[static_cast<unsigned char>(c) & 127] || (c == '\x00') ||
              (c == ',')) {
            k++;
          } else {
            exitg1 = true;
          }
        }
      }
      if (k <= n) {
        c = s[k - 1];
        if ((c == 'i') || (c == 'j')) {
          k++;
          isimag = true;
        }
      }
    }
    exitg1 = false;
    while ((!exitg1) && (k <= n)) {
      c = s[k - 1];
      if (static_cast<unsigned char>(c) > 127) {
        tc_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
      }
      if (bv[static_cast<unsigned char>(c) & 127] || (c == '\x00') ||
          (c == ',')) {
        k++;
      } else {
        exitg1 = true;
      }
    }
  }
  return isimag;
}

//
// Arguments    : array<char, 2U> &s1
//                int &idx
//                const array<char, 2U> &s
//                int &k
//                int n
//                boolean_T allowpoint
// Return Type  : boolean_T
//
static boolean_T copydigits(array<char, 2U> &s1, int &idx,
                            const array<char, 2U> &s, int &k, int n,
                            boolean_T allowpoint)
{
  boolean_T exitg1;
  boolean_T haspoint;
  boolean_T success;
  success = (k <= n);
  haspoint = false;
  exitg1 = false;
  while ((!exitg1) && (success && (k <= n))) {
    char c;
    c = s[k - 1];
    if ((c >= '0') && (c <= '9')) {
      s1[idx - 1] = c;
      idx++;
      k++;
    } else if (c == '.') {
      if (allowpoint && (!haspoint)) {
        success = true;
      } else {
        success = false;
      }
      if (success) {
        s1[idx - 1] = '.';
        idx++;
        haspoint = true;
      }
      k++;
    } else if (c == ',') {
      k++;
    } else {
      exitg1 = true;
    }
  }
  return success;
}

//
// Arguments    : array<char, 2U> &s1
//                int &idx
//                const array<char, 2U> &s
//                int &k
//                int n
// Return Type  : boolean_T
//
static boolean_T copyexponent(array<char, 2U> &s1, int &idx,
                              const array<char, 2U> &s, int &k, int n)
{
  boolean_T success;
  success = true;
  if (k <= n) {
    char c;
    c = s[k - 1];
    if ((c == 'E') || (c == 'e')) {
      int kexp;
      boolean_T b_success;
      s1[idx - 1] = 'e';
      idx++;
      k++;
      while ((k <= n) && (s[k - 1] == ',')) {
        k++;
      }
      if (k <= n) {
        c = s[k - 1];
        if (c == '-') {
          s1[idx - 1] = '-';
          idx++;
          k++;
        } else if (c == '+') {
          k++;
        }
      }
      kexp = k;
      b_success = copydigits(s1, idx, s, k, n, false);
      if ((!b_success) || (k <= kexp)) {
        success = false;
      }
    }
  }
  return success;
}

//
// Arguments    : const array<char, 2U> &s
//                int k
//                int n
// Return Type  : boolean_T
//
static boolean_T isUnitImag(const array<char, 2U> &s, int k, int n)
{
  boolean_T p;
  p = false;
  if (k <= n) {
    char c;
    c = s[k - 1];
    if (c == 'j') {
      p = true;
    } else if (c == 'i') {
      if (k >= n - 1) {
        p = true;
      } else {
        int b_k;
        char b_c[3];
        b_k = k;
        for (int j{0}; j < 3; j++) {
          b_c[j] = '\x00';
          while ((b_k <= n) && (s[b_k - 1] == ',')) {
            b_k++;
          }
          if (b_k <= n) {
            b_c[j] = s[b_k - 1];
          }
          b_k++;
        }
        if ((((b_c[0] != 'I') && (b_c[0] != 'i')) ||
             ((b_c[1] != 'N') && (b_c[1] != 'n')) ||
             ((b_c[2] != 'F') && (b_c[2] != 'f'))) &&
            (((b_c[0] != 'N') && (b_c[0] != 'n')) ||
             ((b_c[1] != 'A') && (b_c[1] != 'a')) ||
             ((b_c[2] != 'N') && (b_c[2] != 'n')))) {
          p = true;
        }
      }
    }
  }
  return p;
}

//
// Arguments    : const array<char, 2U> &s
//                int &k
//                int n
//                double &fv
// Return Type  : boolean_T
//
static boolean_T readNonFinite(const array<char, 2U> &s, int &k, int n,
                               double &fv)
{
  int ksaved;
  char c[3];
  boolean_T b_finite;
  ksaved = k;
  for (int j{0}; j < 3; j++) {
    c[j] = '\x00';
    while ((k <= n) && (s[k - 1] == ',')) {
      k++;
    }
    if (k <= n) {
      c[j] = s[k - 1];
    }
    k++;
  }
  if (((c[0] == 'I') || (c[0] == 'i')) && ((c[1] == 'N') || (c[1] == 'n')) &&
      ((c[2] == 'F') || (c[2] == 'f'))) {
    b_finite = false;
    fv = rtInf;
  } else if (((c[0] == 'N') || (c[0] == 'n')) &&
             ((c[1] == 'A') || (c[1] == 'a')) &&
             ((c[2] == 'N') || (c[2] == 'n'))) {
    b_finite = false;
    fv = rtNaN;
  } else {
    b_finite = true;
    fv = 0.0;
    k = ksaved;
  }
  return b_finite;
}

//
// Arguments    : array<char, 2U> &s1
//                const array<char, 2U> &s
//                int &k
//                int n
//                boolean_T &isimag
//                boolean_T &b_finite
//                double &nfv
//                boolean_T &foundsign
//                boolean_T &success
// Return Type  : int
//
static int readfloat(array<char, 2U> &s1, const array<char, 2U> &s, int &k,
                     int n, boolean_T &isimag, boolean_T &b_finite, double &nfv,
                     boolean_T &foundsign, boolean_T &success)
{
  int idx;
  char c;
  boolean_T exitg1;
  boolean_T isneg;
  isimag = false;
  b_finite = true;
  nfv = 0.0;
  idx = 1;
  isneg = false;
  foundsign = false;
  exitg1 = false;
  while ((!exitg1) && (k <= n)) {
    c = s[k - 1];
    if (c == '-') {
      isneg = !isneg;
      foundsign = true;
      k++;
    } else if (c == ',') {
      k++;
    } else if (c == '+') {
      foundsign = true;
      k++;
    } else {
      if (static_cast<unsigned char>(c) > 127) {
        tc_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
      }
      if (!bv[static_cast<unsigned char>(c) & 127]) {
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  success = (k <= n);
  if (success && isneg) {
    s1[0] = '-';
    idx = 2;
  }
  if (success) {
    if (isUnitImag(s, k, n)) {
      isimag = true;
      k++;
      exitg1 = false;
      while ((!exitg1) && (k <= n)) {
        c = s[k - 1];
        if (static_cast<unsigned char>(c) > 127) {
          tc_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
        }
        if (bv[static_cast<unsigned char>(c) & 127] || (c == '\x00') ||
            (c == ',')) {
          k++;
        } else {
          exitg1 = true;
        }
      }
      if ((k <= n) && (s[k - 1] == '*')) {
        k++;
        b_readfloat(s1, idx, s, k, n, b_finite, nfv, isneg, success);
      } else {
        s1[idx - 1] = '1';
        idx++;
      }
    } else {
      b_finite = readNonFinite(s, k, n, nfv);
      if (b_finite) {
        success = copydigits(s1, idx, s, k, n, true);
        if (success) {
          success = copyexponent(s1, idx, s, k, n);
        }
      } else if ((idx >= 2) && (s1[0] == '-')) {
        idx = 1;
        s1[0] = ' ';
        nfv = -nfv;
      }
      exitg1 = false;
      while ((!exitg1) && (k <= n)) {
        c = s[k - 1];
        if (static_cast<unsigned char>(c) > 127) {
          tc_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
        }
        if (bv[static_cast<unsigned char>(c) & 127] || (c == '\x00') ||
            (c == ',')) {
          k++;
        } else {
          exitg1 = true;
        }
      }
      if ((k <= n) && (s[k - 1] == '*')) {
        k++;
        exitg1 = false;
        while ((!exitg1) && (k <= n)) {
          c = s[k - 1];
          if (static_cast<unsigned char>(c) > 127) {
            tc_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
          }
          if (bv[static_cast<unsigned char>(c) & 127] || (c == '\x00') ||
              (c == ',')) {
            k++;
          } else {
            exitg1 = true;
          }
        }
      }
      if (k <= n) {
        c = s[k - 1];
        if ((c == 'i') || (c == 'j')) {
          k++;
          isimag = true;
        }
      }
    }
    exitg1 = false;
    while ((!exitg1) && (k <= n)) {
      c = s[k - 1];
      if (static_cast<unsigned char>(c) > 127) {
        tc_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
      }
      if (bv[static_cast<unsigned char>(c) & 127] || (c == '\x00') ||
          (c == ',')) {
        k++;
      } else {
        exitg1 = true;
      }
    }
  }
  return idx;
}

//
// Arguments    : const array<char, 2U> &s
// Return Type  : creal_T
//
creal_T str2double(const array<char, 2U> &s)
{
  array<char, 2U> s1;
  creal_T x;
  double scanned1;
  int n;
  boolean_T a__1;
  boolean_T a__3;
  boolean_T isfinite1;
  boolean_T isimag1;
  boolean_T success;
  x.re = rtNaN;
  x.im = 0.0;
  n = s.size(1);
  if (s.size(1) >= 1) {
    double scanned2;
    int b_idx;
    int idx;
    int k;
    int ntoread;
    boolean_T exitg1;
    if (s.size(1) + 2 > 2147483646) {
      check_forloop_overflow_error();
    }
    ntoread = 0;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k + 1 <= n)) {
      idx = static_cast<unsigned char>(s[k]);
      if (idx > 127) {
        tc_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
      }
      if (bv[idx] || (s[k] == '\x00')) {
        k++;
      } else {
        exitg1 = true;
      }
    }
    s1.set_size(1, s.size(1) + 2);
    b_idx = s.size(1) + 2;
    for (idx = 0; idx < b_idx; idx++) {
      s1[idx] = '\x00';
    }
    k++;
    b_idx = readfloat(s1, s, k, s.size(1), isimag1, isfinite1, scanned1, a__1,
                      success);
    if (isfinite1) {
      ntoread = 1;
    }
    if (success && (k <= s.size(1))) {
      boolean_T b_finite;
      boolean_T foundsign;
      s1[b_idx - 1] = ' ';
      a__1 = false;
      b_finite = true;
      scanned2 = 0.0;
      idx = b_idx + 1;
      foundsign = b_copysign(s1, idx, s, k, s.size(1), success);
      b_idx = idx;
      if (success) {
        char c;
        if (isUnitImag(s, k, s.size(1))) {
          a__1 = true;
          k++;
          exitg1 = false;
          while ((!exitg1) && (k <= n)) {
            c = s[k - 1];
            if (static_cast<unsigned char>(c) > 127) {
              tc_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
            }
            if (bv[static_cast<unsigned char>(c) & 127] || (c == '\x00') ||
                (c == ',')) {
              k++;
            } else {
              exitg1 = true;
            }
          }
          if ((k <= s.size(1)) && (s[k - 1] == '*')) {
            k++;
            b_readfloat(s1, b_idx, s, k, s.size(1), b_finite, scanned2, a__3,
                        success);
          } else {
            s1[idx - 1] = '1';
            b_idx = idx + 1;
          }
        } else {
          b_finite = readNonFinite(s, k, s.size(1), scanned2);
          if (b_finite) {
            success = copydigits(s1, b_idx, s, k, s.size(1), true);
            if (success) {
              success = copyexponent(s1, b_idx, s, k, s.size(1));
            }
          } else if ((idx >= 2) && (s1[idx - 2] == '-')) {
            b_idx = idx - 1;
            s1[idx - 2] = ' ';
            scanned2 = -scanned2;
          }
          exitg1 = false;
          while ((!exitg1) && (k <= n)) {
            c = s[k - 1];
            if (static_cast<unsigned char>(c) > 127) {
              tc_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
            }
            if (bv[static_cast<unsigned char>(c) & 127] || (c == '\x00') ||
                (c == ',')) {
              k++;
            } else {
              exitg1 = true;
            }
          }
          if ((k <= s.size(1)) && (s[k - 1] == '*')) {
            k++;
            exitg1 = false;
            while ((!exitg1) && (k <= n)) {
              c = s[k - 1];
              if (static_cast<unsigned char>(c) > 127) {
                tc_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
              }
              if (bv[static_cast<unsigned char>(c) & 127] || (c == '\x00') ||
                  (c == ',')) {
                k++;
              } else {
                exitg1 = true;
              }
            }
          }
          if (k <= s.size(1)) {
            c = s[k - 1];
            if ((c == 'i') || (c == 'j')) {
              k++;
              a__1 = true;
            }
          }
        }
        exitg1 = false;
        while ((!exitg1) && (k <= n)) {
          c = s[k - 1];
          if (static_cast<unsigned char>(c) > 127) {
            tc_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
          }
          if (bv[static_cast<unsigned char>(c) & 127] || (c == '\x00') ||
              (c == ',')) {
            k++;
          } else {
            exitg1 = true;
          }
        }
      }
      if (b_finite) {
        ntoread++;
      }
      if (success && (k > s.size(1)) && (isimag1 ^ a__1) && foundsign) {
        success = true;
      } else {
        success = false;
      }
    } else {
      scanned2 = 0.0;
    }
    if (success) {
      s1[b_idx - 1] = '\x00';
      if (ntoread == 2) {
        b_idx = std::sscanf(&s1[0], "%lf %lf", &scanned1, &scanned2);
        if (b_idx != 2) {
          scanned1 = rtNaN;
          scanned2 = rtNaN;
        }
      } else if (ntoread == 1) {
        double b_scanned1;
        b_idx = std::sscanf(&s1[0], "%lf", &b_scanned1);
        if (b_idx != 1) {
          b_scanned1 = rtNaN;
        }
        if (isfinite1) {
          scanned1 = b_scanned1;
        } else {
          scanned2 = b_scanned1;
        }
      }
      if (isimag1) {
        x.re = scanned2;
        x.im = scanned1;
      } else {
        x.re = scanned1;
        x.im = scanned2;
      }
    }
  }
  return x;
}

} // namespace internal
} // namespace coder

//
// File trailer for str2double.cpp
//
// [EOF]
//
