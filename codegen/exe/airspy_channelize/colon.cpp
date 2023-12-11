//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: colon.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 11-Dec-2023 13:33:03
//

// Include Files
#include "colon.h"
#include "airspy_channelize_rtwutil.h"
#include "airspy_channelize_types.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : int a
//                int b
//                array<int, 2U> &y
// Return Type  : void
//
namespace coder {
void eml_integer_colon_dispatcher(int a, int b, array<int, 2U> &y)
{
  static rtRunTimeErrorInfo h_emlrtRTEI{
      291,                           // lineNo
      "integer_colon_length_nonnegd" // fName
  };
  int bma;
  if (b < a) {
    bma = 0;
  } else {
    bma = b - a;
    if (bma < 0) {
      c_rtErrorWithMessageID(h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
    }
    bma++;
  }
  y.set_size(1, bma);
  if (bma > 0) {
    int yk;
    y[0] = a;
    yk = a;
    for (int k{2}; k <= bma; k++) {
      yk++;
      y[k - 1] = yk;
    }
  }
}

} // namespace coder

//
// File trailer for colon.cpp
//
// [EOF]
//
