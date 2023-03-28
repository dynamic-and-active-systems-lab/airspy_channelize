//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: colon.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 28-Mar-2023 15:24:09
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
//                ::coder::array<int, 2U> &y
// Return Type  : void
//
namespace coder {
void eml_integer_colon_dispatcher(int a, int b, ::coder::array<int, 2U> &y)
{
  static rtRunTimeErrorInfo i_emlrtRTEI{
      291,                           // lineNo
      "integer_colon_length_nonnegd" // fName
  };
  int bma;
  if (b < a) {
    bma = 0;
  } else {
    bma = b - a;
    if (bma < 0) {
      c_rtErrorWithMessageID(i_emlrtRTEI.fName, i_emlrtRTEI.lineNo);
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
