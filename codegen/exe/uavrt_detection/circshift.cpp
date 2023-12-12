//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: circshift.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "circshift.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : array<double, 2U> &a
// Return Type  : void
//
namespace coder {
void b_circshift(array<double, 2U> &a)
{
  array<double, 2U> buffer;
  if ((a.size(0) != 0) && (a.size(1) != 0) &&
      ((a.size(0) != 1) || (a.size(1) != 1))) {
    int i;
    int npages;
    int ns;
    int nv;
    int pageroot;
    ns = 1;
    if (a.size(0) <= 1) {
      ns = 0;
    }
    pageroot = static_cast<int>(static_cast<unsigned int>(a.size(0)) >> 1);
    buffer.set_size(1, pageroot);
    for (i = 0; i < pageroot; i++) {
      buffer[i] = 0.0;
    }
    nv = a.size(0);
    npages = a.size(1);
    if ((a.size(0) > 1) && (ns > 0)) {
      if (a.size(1) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (ns = 0; ns < npages; ns++) {
        pageroot = ns * nv;
        buffer[0] = a[pageroot];
        for (int k{0}; k <= nv - 2; k++) {
          i = pageroot + k;
          a[i] = a[i + 1];
        }
        a[(pageroot + nv) - 1] = buffer[0];
      }
    }
  }
}

//
// Arguments    : array<double, 2U> &a
// Return Type  : void
//
void c_circshift(array<double, 2U> &a)
{
  array<double, 2U> buffer;
  if ((a.size(0) != 0) && (a.size(1) != 0) &&
      ((a.size(0) != 1) || (a.size(1) != 1))) {
    int i;
    int npages;
    int ns;
    int nv;
    boolean_T shiftright;
    ns = 1;
    shiftright = true;
    if (a.size(0) <= 1) {
      ns = -1;
    } else if ((a.size(0) >> 1) < 2) {
      ns = a.size(0) - 3;
      shiftright = false;
    }
    nv = static_cast<int>(static_cast<unsigned int>(a.size(0)) >> 1);
    buffer.set_size(1, nv);
    for (i = 0; i < nv; i++) {
      buffer[i] = 0.0;
    }
    nv = a.size(0);
    npages = a.size(1);
    if ((a.size(0) > 1) && (ns + 1 > 0)) {
      if (a.size(1) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int b_i{0}; b_i < npages; b_i++) {
        int pageroot;
        pageroot = b_i * nv;
        if (shiftright) {
          for (int k{0}; k <= ns; k++) {
            buffer[k] = a[(((pageroot + k) + nv) - ns) - 1];
          }
          i = ns + 2;
          for (int k{nv}; k >= i; k--) {
            int i1;
            i1 = pageroot + k;
            a[i1 - 1] = a[(i1 - ns) - 2];
          }
          for (int k{0}; k <= ns; k++) {
            a[pageroot + k] = buffer[k];
          }
        } else {
          for (int k{0}; k <= ns; k++) {
            buffer[k] = a[pageroot + k];
          }
          i = nv - ns;
          for (int k{0}; k <= i - 2; k++) {
            int i1;
            i1 = pageroot + k;
            a[i1] = a[(i1 + ns) + 1];
          }
          for (int k{0}; k <= ns; k++) {
            a[(((pageroot + k) + nv) - ns) - 1] = buffer[k];
          }
        }
      }
    }
  }
}

//
// Arguments    : array<double, 2U> &a
// Return Type  : void
//
void circshift(array<double, 2U> &a)
{
  array<double, 2U> buffer;
  if ((a.size(0) != 0) && (a.size(1) != 0) &&
      ((a.size(0) != 1) || (a.size(1) != 1))) {
    int i;
    int npages;
    int ns;
    int nv;
    int pageroot;
    ns = 1;
    if (a.size(0) <= 1) {
      ns = 0;
    }
    pageroot = static_cast<int>(static_cast<unsigned int>(a.size(0)) >> 1);
    buffer.set_size(1, pageroot);
    for (i = 0; i < pageroot; i++) {
      buffer[i] = 0.0;
    }
    nv = a.size(0);
    npages = a.size(1);
    if ((a.size(0) > 1) && (ns > 0)) {
      if (a.size(1) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (ns = 0; ns < npages; ns++) {
        pageroot = ns * nv;
        buffer[0] = a[(pageroot + nv) - 1];
        for (int k{nv}; k >= 2; k--) {
          i = pageroot + k;
          a[i - 1] = a[i - 2];
        }
        a[pageroot] = buffer[0];
      }
    }
  }
}

//
// Arguments    : array<double, 2U> &a
// Return Type  : void
//
void d_circshift(array<double, 2U> &a)
{
  array<double, 2U> buffer;
  if ((a.size(0) != 0) && (a.size(1) != 0) &&
      ((a.size(0) != 1) || (a.size(1) != 1))) {
    int i;
    int npages;
    int ns;
    int nv;
    boolean_T shiftright;
    ns = 1;
    shiftright = false;
    if (a.size(0) <= 1) {
      ns = -1;
    } else if ((a.size(0) >> 1) < 2) {
      ns = a.size(0) - 3;
      shiftright = true;
    }
    nv = static_cast<int>(static_cast<unsigned int>(a.size(0)) >> 1);
    buffer.set_size(1, nv);
    for (i = 0; i < nv; i++) {
      buffer[i] = 0.0;
    }
    nv = a.size(0);
    npages = a.size(1);
    if ((a.size(0) > 1) && (ns + 1 > 0)) {
      if (a.size(1) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int b_i{0}; b_i < npages; b_i++) {
        int pageroot;
        pageroot = b_i * nv;
        if (shiftright) {
          for (int k{0}; k <= ns; k++) {
            buffer[k] = a[(((pageroot + k) + nv) - ns) - 1];
          }
          i = ns + 2;
          for (int k{nv}; k >= i; k--) {
            int i1;
            i1 = pageroot + k;
            a[i1 - 1] = a[(i1 - ns) - 2];
          }
          for (int k{0}; k <= ns; k++) {
            a[pageroot + k] = buffer[k];
          }
        } else {
          for (int k{0}; k <= ns; k++) {
            buffer[k] = a[pageroot + k];
          }
          i = nv - ns;
          for (int k{0}; k <= i - 2; k++) {
            int i1;
            i1 = pageroot + k;
            a[i1] = a[(i1 + ns) + 1];
          }
          for (int k{0}; k <= ns; k++) {
            a[(((pageroot + k) + nv) - ns) - 1] = buffer[k];
          }
        }
      }
    }
  }
}

//
// Arguments    : array<double, 2U> &a
// Return Type  : void
//
void e_circshift(array<double, 2U> &a)
{
  array<double, 2U> buffer;
  if ((a.size(0) != 0) && (a.size(1) != 0) &&
      ((a.size(0) != 1) || (a.size(1) != 1))) {
    int ns;
    int stride;
    int unnamed_idx_1;
    ns = 1;
    if (a.size(1) <= 1) {
      ns = 0;
    }
    unnamed_idx_1 = static_cast<int>(static_cast<unsigned int>(a.size(1)) >> 1);
    buffer.set_size(1, unnamed_idx_1);
    for (stride = 0; stride < unnamed_idx_1; stride++) {
      buffer[stride] = 0.0;
    }
    unnamed_idx_1 = a.size(1);
    stride = a.size(0);
    if ((a.size(1) > 1) && (ns > 0)) {
      if (a.size(0) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (ns = 0; ns < stride; ns++) {
        buffer[0] = a[ns + (unnamed_idx_1 - 1) * stride];
        for (int k{unnamed_idx_1}; k >= 2; k--) {
          a[ns + (k - 1) * stride] = a[ns + (k - 2) * stride];
        }
        a[ns] = buffer[0];
      }
    }
  }
}

//
// Arguments    : array<double, 2U> &a
// Return Type  : void
//
void f_circshift(array<double, 2U> &a)
{
  array<double, 2U> buffer;
  if ((a.size(0) != 0) && (a.size(1) != 0) &&
      ((a.size(0) != 1) || (a.size(1) != 1))) {
    int ns;
    int stride;
    int unnamed_idx_1;
    ns = 1;
    if (a.size(1) <= 1) {
      ns = 0;
    }
    unnamed_idx_1 = static_cast<int>(static_cast<unsigned int>(a.size(1)) >> 1);
    buffer.set_size(1, unnamed_idx_1);
    for (stride = 0; stride < unnamed_idx_1; stride++) {
      buffer[stride] = 0.0;
    }
    unnamed_idx_1 = a.size(1) - 2;
    stride = a.size(0);
    if ((a.size(1) > 1) && (ns > 0)) {
      if (a.size(0) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (ns = 0; ns < stride; ns++) {
        buffer[0] = a[ns];
        for (int k{0}; k <= unnamed_idx_1; k++) {
          a[ns + k * stride] = a[ns + (k + 1) * stride];
        }
        a[ns + (unnamed_idx_1 + 1) * stride] = buffer[0];
      }
    }
  }
}

//
// Arguments    : array<boolean_T, 2U> &a
// Return Type  : void
//
void g_circshift(array<boolean_T, 2U> &a)
{
  array<boolean_T, 2U> buffer;
  if ((a.size(0) != 0) && (a.size(1) != 0) &&
      ((a.size(0) != 1) || (a.size(1) != 1))) {
    int ns;
    int stride;
    int unnamed_idx_1;
    ns = 1;
    if (a.size(1) <= 1) {
      ns = 0;
    }
    unnamed_idx_1 = static_cast<int>(static_cast<unsigned int>(a.size(1)) >> 1);
    buffer.set_size(1, unnamed_idx_1);
    for (stride = 0; stride < unnamed_idx_1; stride++) {
      buffer[stride] = false;
    }
    unnamed_idx_1 = a.size(1) - 2;
    stride = a.size(0);
    if ((a.size(1) > 1) && (ns > 0)) {
      if (a.size(0) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (ns = 0; ns < stride; ns++) {
        buffer[0] = a[ns];
        for (int k{0}; k <= unnamed_idx_1; k++) {
          a[ns + k * stride] = a[ns + (k + 1) * stride];
        }
        a[ns + (unnamed_idx_1 + 1) * stride] = buffer[0];
      }
    }
  }
}

} // namespace coder

//
// File trailer for circshift.cpp
//
// [EOF]
//
