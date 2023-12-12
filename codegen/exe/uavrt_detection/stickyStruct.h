//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: stickyStruct.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

#ifndef STICKYSTRUCT_H
#define STICKYSTRUCT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace internal {
class stickyStruct {
public:
  double value;
};

class b_stickyStruct {
public:
  stickyStruct next;
};

class c_stickyStruct {
public:
  b_stickyStruct next;
};

class d_stickyStruct {
public:
  c_stickyStruct next;
};

class e_stickyStruct {
public:
  d_stickyStruct next;
};

class f_stickyStruct {
public:
  e_stickyStruct next;
};

class g_stickyStruct {
public:
  f_stickyStruct next;
};

class h_stickyStruct {
public:
  double value;
  g_stickyStruct next;
};

class i_stickyStruct {
public:
  h_stickyStruct next;
};

class j_stickyStruct {
public:
  array<float, 1U> value;
  i_stickyStruct next;
};

} // namespace internal
} // namespace coder

#endif
//
// File trailer for stickyStruct.h
//
// [EOF]
//
