//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sparse1.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "sparse1.h"
#include "anonymous_function.h"
#include "bigProduct.h"
#include "eml_int_forloop_overflow_check.h"
#include "ind2sub.h"
#include "indexShapeCheck.h"
#include "locBsearch.h"
#include "rt_nonfinite.h"
#include "sparse.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo hc_emlrtRTEI{
    29,              // lineNo
    23,              // colNo
    "sparse/mtimes", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/shared/coder/coder/+coder/"
    "+internal/@sparse/mtimes.m" // pName
};

static rtRunTimeErrorInfo mc_emlrtRTEI{
    12,                                   // lineNo
    27,                                   // colNo
    "sparse/sparse_validateNumericIndex", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/shared/coder/coder/+coder/"
    "+internal/@sparse/private/validateNumericIndex.m" // pName
};

static rtRunTimeErrorInfo oc_emlrtRTEI{
    1623,              // lineNo
    9,                 // colNo
    "assertValidSize", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/shared/coder/coder/+coder/"
    "+internal/@sparse/sparse.m" // pName
};

static rtRunTimeErrorInfo sc_emlrtRTEI{
    11,                                   // lineNo
    27,                                   // colNo
    "sparse/sparse_validateNumericIndex", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/shared/coder/coder/+coder/"
    "+internal/@sparse/private/validateNumericIndex.m" // pName
};

static rtRunTimeErrorInfo tc_emlrtRTEI{
    92,                        // lineNo
    1,                         // colNo
    "parenReference2DColumns", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/shared/coder/coder/+coder/"
    "+internal/@sparse/parenReference2D.m" // pName
};

static rtRunTimeErrorInfo yc_emlrtRTEI{
    11,                     // lineNo
    23,                     // colNo
    "sparse/parenAssign1D", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/shared/coder/coder/+coder/"
    "+internal/@sparse/parenAssign1D.m" // pName
};

// Function Declarations
static void ec_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void fc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void gc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void jc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void pb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void qb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void qc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void rb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void rc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void rtErrorWithMessageID(const int i, const int i1,
                                 const char *aFcnName, int aLineNum);

static void rtErrorWithMessageID(const long i, const int i1,
                                 const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : f_sparse *b_this
//                int numAllocRequested
//                int ub1
//                int lb2
//                int ub2
// Return Type  : void
//
namespace coder {
void sparse::b_realloc(f_sparse *b_this, int numAllocRequested, int ub1,
                       int lb2, int ub2)
{
  static rtRunTimeErrorInfo bd_emlrtRTEI{
      237,            // lineNo
      13,             // colNo
      "sparse/numel", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/shared/coder/coder/+coder/"
      "+internal/@sparse/sparse.m" // pName
  };
  array<int, 1U> rowidxt;
  array<boolean_T, 1U> dt;
  int numAlloc;
  int overflow;
  rowidxt.set_size(b_this->rowidx.size(0));
  numAlloc = b_this->rowidx.size(0);
  for (overflow = 0; overflow < numAlloc; overflow++) {
    rowidxt[overflow] = b_this->rowidx[overflow];
  }
  dt.set_size(b_this->d.size(0));
  numAlloc = b_this->d.size(0);
  for (overflow = 0; overflow < numAlloc; overflow++) {
    dt[overflow] = b_this->d[overflow];
  }
  internal::b_bigProduct(b_this->m, b_this->n, overflow);
  if (overflow == 0) {
    internal::b_bigProduct(b_this->m, b_this->n, overflow);
    if (overflow != 0) {
      rc_rtErrorWithMessageID(bd_emlrtRTEI.fName, bd_emlrtRTEI.lineNo);
    }
    numAlloc = b_this->m * b_this->n;
    if (numAllocRequested <= numAlloc) {
      numAlloc = numAllocRequested;
    }
    if (numAlloc <= 1) {
      numAlloc = 1;
    }
  } else if (numAllocRequested <= 1) {
    numAlloc = 1;
  } else {
    numAlloc = numAllocRequested;
  }
  b_this->rowidx.set_size(numAlloc);
  b_this->d.set_size(numAlloc);
  for (overflow = 0; overflow < numAlloc; overflow++) {
    b_this->rowidx[overflow] = 0;
    b_this->d[overflow] = false;
  }
  b_this->maxnz = numAlloc;
  if (ub1 > 2147483646) {
    check_forloop_overflow_error();
  }
  for (numAlloc = 0; numAlloc < ub1; numAlloc++) {
    b_this->rowidx[numAlloc] = rowidxt[numAlloc];
    b_this->d[numAlloc] = dt[numAlloc];
  }
  if ((lb2 <= ub2) && (ub2 > 2147483646)) {
    check_forloop_overflow_error();
  }
  for (numAlloc = lb2; numAlloc <= ub2; numAlloc++) {
    b_this->rowidx[numAlloc] = rowidxt[numAlloc - 1];
    b_this->d[numAlloc] = dt[numAlloc - 1];
  }
}

//
// Arguments    : boolean_T rhs
//                double r
//                double c
// Return Type  : void
//
void f_sparse::parenAssign2D(boolean_T rhs, double r, double c)
{
  double b_d;
  int vidx;
  boolean_T b;
  boolean_T thisv;
  b_d = std::floor(r);
  if ((!(b_d == r)) || std::isinf(r) || (!(r > 0.0))) {
    jc_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
  }
  if (!(r <= m)) {
    rtErrorWithMessageID(static_cast<long>(b_d), m, mc_emlrtRTEI.fName,
                         mc_emlrtRTEI.lineNo);
  }
  b_d = std::floor(c);
  if ((!(b_d == c)) || std::isinf(c) || (!(c > 0.0))) {
    jc_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
  }
  if (!(c <= n)) {
    rtErrorWithMessageID(static_cast<long>(b_d), n, mc_emlrtRTEI.fName,
                         mc_emlrtRTEI.lineNo);
  }
  vidx = b_sparse_locBsearch(rowidx, static_cast<int>(r),
                             colidx[static_cast<int>(c) - 1],
                             colidx[static_cast<int>(c)], thisv);
  if (thisv) {
    thisv = d[vidx - 1];
  } else {
    thisv = false;
  }
  b = !thisv;
  if ((!b) || rhs) {
    if (thisv && rhs) {
      d[vidx - 1] = true;
    } else if (b) {
      int nelem;
      if (colidx[colidx.size(0) - 1] - 1 == maxnz) {
        sparse::b_realloc(this, colidx[colidx.size(0) - 1] + 9, vidx, vidx + 1,
                          colidx[colidx.size(0) - 1] - 1);
        rowidx[vidx] = static_cast<int>(r);
        d[vidx] = rhs;
      } else {
        nelem = (colidx[colidx.size(0) - 1] - vidx) - 1;
        if (nelem > 0) {
          std::memmove((void *)&rowidx[vidx + 1], (void *)&rowidx[vidx],
                       (unsigned int)((size_t)nelem * sizeof(int)));
          std::memmove((void *)&d[vidx + 1], (void *)&d[vidx],
                       (unsigned int)((size_t)nelem * sizeof(boolean_T)));
        }
        d[vidx] = rhs;
        rowidx[vidx] = static_cast<int>(r);
      }
      nelem = static_cast<int>(c) + 1;
      vidx = n + 1;
      if ((nelem <= n + 1) && (n + 1 > 2147483646)) {
        check_forloop_overflow_error();
      }
      for (int k{nelem}; k <= vidx; k++) {
        colidx[k - 1] = colidx[k - 1] + 1;
      }
    } else {
      int nelem;
      nelem = (colidx[colidx.size(0) - 1] - vidx) - 1;
      if (nelem > 0) {
        std::memmove((void *)&rowidx[vidx - 1], (void *)&rowidx[vidx],
                     (unsigned int)((size_t)nelem * sizeof(int)));
        std::memmove((void *)&d[vidx - 1], (void *)&d[vidx],
                     (unsigned int)((size_t)nelem * sizeof(boolean_T)));
      }
      nelem = static_cast<int>(c) + 1;
      vidx = n + 1;
      if ((nelem <= vidx) && (vidx > 2147483646)) {
        check_forloop_overflow_error();
      }
      for (int k{nelem}; k <= vidx; k++) {
        colidx[k - 1] = colidx[k - 1] - 1;
      }
    }
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
} // namespace coder
static void ec_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "The number of nonzeros must be at least as large as the number "
               "of elements specified by the first 3 arguments to sparse.";
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
static void fc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Sparse matrix sizes must be non-negative integers.";
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
static void gc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Unable to represent result of \'~\' because it contains too "
               "many nonzero elements.";
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
static void jc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "Subscript indices must either be real positive integers or logicals.";
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
static void pb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Index into matrix must be an integer.";
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
static void qb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Index into matrix is too large.";
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
static void qc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "In an assignment  A(:) = B, the number of elements in A and B "
               "must be the same.";
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
static void rb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Index into matrix must be positive.";
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
static void rc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Number of elements exceeds maximum representable value.";
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
// Arguments    : const long i
//                const int i1
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void rtErrorWithMessageID(const long i, const int i1,
                                 const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((((((outStream
        << "Index expression out of bounds. Attempted to access element ")
       << i)
      << ". The valid range is ")
     << 1)
    << "-")
   << i1)
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
// Arguments    : const int i
//                const int i1
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void rtErrorWithMessageID(const int i, const int i1,
                                 const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((((((outStream
        << "Index expression out of bounds. Attempted to access element ")
       << i)
      << ". The valid range is ")
     << 1)
    << "-")
   << i1)
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
// Arguments    : const array<double, 1U> &s
//                array<int, 1U> &sint
// Return Type  : void
//
namespace coder {
void sparse::assertValidIndexArg(const array<double, 1U> &s,
                                 array<int, 1U> &sint)
{
  static rtRunTimeErrorInfo bd_emlrtRTEI{
      1652,                  // lineNo
      31,                    // colNo
      "assertValidIndexArg", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/shared/coder/coder/+coder/"
      "+internal/@sparse/sparse.m" // pName
  };
  static rtRunTimeErrorInfo cd_emlrtRTEI{
      1654,                  // lineNo
      31,                    // colNo
      "assertValidIndexArg", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/shared/coder/coder/+coder/"
      "+internal/@sparse/sparse.m" // pName
  };
  static rtRunTimeErrorInfo dd_emlrtRTEI{
      1656,                  // lineNo
      31,                    // colNo
      "assertValidIndexArg", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/shared/coder/coder/+coder/"
      "+internal/@sparse/sparse.m" // pName
  };
  int ns;
  ns = s.size(0);
  sint.set_size(s.size(0));
  if (s.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < ns; k++) {
    if (!(std::floor(s[k]) == s[k])) {
      pb_rtErrorWithMessageID(bd_emlrtRTEI.fName, bd_emlrtRTEI.lineNo);
    }
    if (!(s[k] < 2.147483647E+9)) {
      qb_rtErrorWithMessageID(cd_emlrtRTEI.fName, cd_emlrtRTEI.lineNo);
    }
    if (!(s[k] > 0.0)) {
      rb_rtErrorWithMessageID(dd_emlrtRTEI.fName, dd_emlrtRTEI.lineNo);
    }
    sint[k] = static_cast<int>(s[k]);
  }
}

//
// Arguments    : const array<double, 2U> &a
//                array<double, 2U> &c
// Return Type  : void
//
void f_sparse::b_mtimes(const array<double, 2U> &a, array<double, 2U> &c) const
{
  int aoff;
  int b_m;
  int b_n;
  int cidx;
  if (a.size(1) != m) {
    tb_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
  }
  b_m = a.size(0);
  b_n = n - 1;
  c.set_size(a.size(0), n);
  aoff = a.size(0) * n;
  for (cidx = 0; cidx < aoff; cidx++) {
    c[cidx] = 0.0;
  }
  if ((a.size(1) != 0) && (a.size(0) != 0) && (n != 0) &&
      (colidx[colidx.size(0) - 1] - 1 != 0)) {
    if (a.size(0) == 1) {
      aoff = n;
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int aidx_tmp{0}; aidx_tmp < aoff; aidx_tmp++) {
        double cd;
        int b_a;
        cd = 0.0;
        cidx = colidx[aidx_tmp + 1] - 1;
        b_a = colidx[aidx_tmp];
        if ((colidx[aidx_tmp] <= cidx) && (cidx > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int mend{b_a}; mend <= cidx; mend++) {
          cd += static_cast<double>(d[mend - 1]) * a[rowidx[mend - 1] - 1];
        }
        c[aidx_tmp] = cd;
      }
    } else if (a.size(0) >= 4) {
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int ccol{0}; ccol <= b_n; ccol++) {
        int b_a;
        int bpend_tmp;
        int coff;
        coff = ccol * c.size(0);
        bpend_tmp = colidx[ccol + 1] - 1;
        b_a = colidx[ccol];
        if ((colidx[ccol] <= bpend_tmp) && (bpend_tmp > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int bp{b_a}; bp <= bpend_tmp; bp++) {
          int aoff_tmp;
          int mend;
          boolean_T bd;
          aoff_tmp = rowidx[bp - 1] - 1;
          aoff = aoff_tmp * a.size(0);
          bd = d[bp - 1];
          mend = (b_m / 4) << 2;
          if (mend > 2147483643) {
            check_forloop_overflow_error();
          }
          for (int crow{1}; crow <= mend; crow += 4) {
            int aidx_tmp;
            cidx = crow + coff;
            aidx_tmp = crow + aoff;
            c[cidx - 1] =
                c[cidx - 1] + a[aidx_tmp - 1] * static_cast<double>(bd);
            c[cidx] = c[cidx] + a[aidx_tmp] * static_cast<double>(bd);
            c[cidx + 1] =
                c[cidx + 1] + a[aidx_tmp + 1] * static_cast<double>(bd);
            c[cidx + 2] =
                c[cidx + 2] + a[aidx_tmp + 2] * static_cast<double>(bd);
          }
          aoff = mend + 1;
          if ((mend + 1 <= b_m) && (b_m > 2147483646)) {
            check_forloop_overflow_error();
          }
          for (int crow{aoff}; crow <= b_m; crow++) {
            cidx = (crow + coff) - 1;
            c[cidx] = c[cidx] + a[(crow + a.size(0) * aoff_tmp) - 1] *
                                    static_cast<double>(bd);
          }
        }
      }
    } else {
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int ccol{0}; ccol <= b_n; ccol++) {
        int b_a;
        int bpend_tmp;
        bpend_tmp = colidx[ccol + 1] - 1;
        b_a = colidx[ccol];
        if ((colidx[ccol] <= bpend_tmp) && (bpend_tmp > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int bp{b_a}; bp <= bpend_tmp; bp++) {
          for (int crow{0}; crow < b_m; crow++) {
            c[crow + c.size(0) * ccol] =
                c[crow + c.size(0) * ccol] +
                a[crow + a.size(0) * (rowidx[bp - 1] - 1)] *
                    static_cast<double>(d[bp - 1]);
          }
        }
      }
    }
  }
}

//
// Arguments    : d_sparse &out
// Return Type  : void
//
void d_sparse::b_not(d_sparse &out) const
{
  static rtRunTimeErrorInfo bd_emlrtRTEI{
      83,       // lineNo
      27,       // colNo
      "notnnz", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/shared/coder/coder/+coder/"
      "+internal/@sparse/not.m" // pName
  };
  int b;
  int curPosition;
  int larger;
  int nzmax;
  if (n < 1) {
    larger = 0;
  } else {
    larger = (n - colidx[colidx.size(0) - 1]) + 1;
    if (larger == 0) {
      larger = 0;
    } else if (div_s32(MAX_int32_T, larger) < 1) {
      gc_rtErrorWithMessageID(bd_emlrtRTEI.fName, bd_emlrtRTEI.lineNo);
    }
  }
  nzmax = larger;
  out.n = n;
  if (larger < 1) {
    nzmax = 1;
  }
  out.d.set_size(nzmax);
  out.rowidx.set_size(nzmax);
  if (n + 1 < 0) {
    rtNonNegativeError(static_cast<double>(n + 1), o_emlrtDCI);
  }
  out.colidx.set_size(n + 1);
  if (larger < 1) {
    larger = 0;
  }
  for (nzmax = 0; nzmax < larger; nzmax++) {
    out.d[nzmax] = true;
  }
  curPosition = 1;
  b = n;
  if (n > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int c{0}; c < b; c++) {
    out.colidx[c] = curPosition;
    nzmax = colidx[c + 1];
    if (colidx[c] == nzmax) {
      out.rowidx[curPosition - 1] = 1;
      curPosition++;
    } else {
      if (rowidx[colidx[c] - 1] - 1 > 2147483646) {
        check_forloop_overflow_error();
      }
      larger = (nzmax - colidx[c]) - 2;
      for (int i{0}; i <= larger; i++) {
        int b_b;
        nzmax = colidx[c] + i;
        b_b = rowidx[nzmax] - 1;
        if ((rowidx[nzmax - 1] + 1 <= b_b) && (b_b > 2147483646)) {
          check_forloop_overflow_error();
        }
      }
      larger = rowidx[colidx[c] + larger] + 1;
      for (nzmax = larger; nzmax < 2; nzmax++) {
        out.rowidx[((curPosition + nzmax) - larger) - 1] = 1;
      }
      if (larger <= 1) {
        curPosition = (curPosition - larger) + 2;
      }
    }
  }
  out.colidx[n] = curPosition;
}

//
// Arguments    : const array<boolean_T, 2U> &rhs
//                const array<double, 2U> &varargin_1
// Return Type  : void
//
void f_sparse::b_parenAssign(const array<boolean_T, 2U> &rhs,
                             const array<double, 2U> &varargin_1)
{
  int nidx;
  int overflow;
  int varargout_4;
  internal::bigProduct(m, n, overflow);
  if (rhs.size(1) != varargin_1.size(1)) {
    qc_rtErrorWithMessageID(yc_emlrtRTEI.fName, yc_emlrtRTEI.lineNo);
  }
  if (overflow == 0) {
    overflow = m * n;
    nidx = varargin_1.size(1);
    for (int k{0}; k < nidx; k++) {
      double b_d;
      double d1;
      b_d = varargin_1[k];
      d1 = std::floor(b_d);
      if ((!(d1 == b_d)) || std::isinf(b_d)) {
        jc_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
      }
      if (!(b_d <= overflow)) {
        rtErrorWithMessageID(static_cast<long>(d1), overflow,
                             mc_emlrtRTEI.fName, mc_emlrtRTEI.lineNo);
      }
    }
  } else {
    nidx = varargin_1.size(1);
    for (int k{0}; k < nidx; k++) {
      double b_d;
      b_d = varargin_1[k];
      if ((!(std::floor(b_d) == b_d)) || std::isinf(b_d)) {
        jc_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
      }
    }
  }
  nidx = varargin_1.size(1);
  if (varargin_1.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nidx; k++) {
    double b_this[2];
    b_this[0] = m;
    b_this[1] = n;
    overflow = internal::ind2sub(b_this, varargin_1[k], varargout_4);
    parenAssign2D(rhs[k], static_cast<double>(overflow),
                  static_cast<double>(varargout_4));
  }
}

//
// Arguments    : const h_sparse &rhs
//                const array<double, 2U> &varargin_1
// Return Type  : void
//
void f_sparse::c_parenAssign(const h_sparse &rhs,
                             const array<double, 2U> &varargin_1)
{
  e_sparse s;
  double varargout_1_tmp[2];
  int cend;
  int highOrderRHS;
  int nidx;
  int varargout_4;
  boolean_T rhsv;
  internal::bigProduct(m, n, nidx);
  varargout_1_tmp[0] = rhs.m;
  varargout_1_tmp[1] = 1.0;
  cend = internal::bigProduct(rhs.m, 1, highOrderRHS);
  if (((varargin_1.size(1) & 65535) + ((varargin_1.size(1) >> 16) << 16) !=
       cend) ||
      (highOrderRHS != 0)) {
    qc_rtErrorWithMessageID(yc_emlrtRTEI.fName, yc_emlrtRTEI.lineNo);
  }
  if (nidx == 0) {
    cend = m * n;
    highOrderRHS = varargin_1.size(1);
    for (int k{0}; k < highOrderRHS; k++) {
      double b_d;
      double d1;
      b_d = varargin_1[k];
      d1 = std::floor(b_d);
      if ((!(d1 == b_d)) || std::isinf(b_d)) {
        jc_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
      }
      if (!(b_d <= cend)) {
        rtErrorWithMessageID(static_cast<long>(d1), cend, mc_emlrtRTEI.fName,
                             mc_emlrtRTEI.lineNo);
      }
    }
  } else {
    highOrderRHS = varargin_1.size(1);
    for (int k{0}; k < highOrderRHS; k++) {
      double b_d;
      b_d = varargin_1[k];
      if ((!(std::floor(b_d) == b_d)) || std::isinf(b_d)) {
        jc_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
      }
    }
  }
  nidx = varargin_1.size(1);
  if (varargin_1.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nidx; k++) {
    double b_this[2];
    int idx;
    int varargout_3;
    b_this[0] = m;
    b_this[1] = n;
    varargout_3 = internal::ind2sub(b_this, varargin_1[k], varargout_4);
    if (((rhs.m & 65535) <= MAX_int32_T - ((rhs.m >> 16) << 16)) &&
        (k + 1 > rhs.m)) {
      rtErrorWithMessageID(k + 1, rhs.m, mc_emlrtRTEI.fName,
                           mc_emlrtRTEI.lineNo);
    }
    s.colidx.set_size(2);
    s.colidx[0] = 1;
    s.colidx[1] = 1;
    cend = internal::ind2sub(varargout_1_tmp, k + 1, highOrderRHS);
    idx = sparse_locBsearch(rhs.rowidx, static_cast<double>(cend),
                            rhs.colidx[highOrderRHS - 1],
                            rhs.colidx[highOrderRHS], rhsv);
    if (rhsv) {
      s.d.set_size(1);
      s.d[0] = rhs.d[idx - 1];
      s.colidx[1] = 2;
    } else {
      s.d.set_size(1);
      s.d[0] = false;
    }
    rhsv = false;
    cend = s.colidx[1] - 1;
    highOrderRHS = s.colidx[0];
    for (idx = highOrderRHS; idx <= cend; idx++) {
      rhsv = s.d[idx - 1];
    }
    parenAssign2D(rhsv, static_cast<double>(varargout_3),
                  static_cast<double>(varargout_4));
  }
}

//
// Arguments    : const array<double, 2U> &rhs
//                const array<double, 2U> &varargin_1
// Return Type  : void
//
void f_sparse::c_parenAssign(const array<double, 2U> &rhs,
                             const array<double, 2U> &varargin_1)
{
  int lowOrderSize;
  int nidx;
  int overflow;
  int varargout_4;
  boolean_T thisv;
  internal::bigProduct(m, n, overflow);
  if (rhs.size(1) != varargin_1.size(1)) {
    qc_rtErrorWithMessageID(yc_emlrtRTEI.fName, yc_emlrtRTEI.lineNo);
  }
  if (overflow == 0) {
    overflow = m * n;
    lowOrderSize = varargin_1.size(1);
    for (int k{0}; k < lowOrderSize; k++) {
      double b_d;
      double d1;
      b_d = varargin_1[k];
      d1 = std::floor(b_d);
      if ((!(d1 == b_d)) || std::isinf(b_d)) {
        jc_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
      }
      if (!(b_d <= overflow)) {
        rtErrorWithMessageID(static_cast<long>(d1), overflow,
                             mc_emlrtRTEI.fName, mc_emlrtRTEI.lineNo);
      }
    }
  } else {
    lowOrderSize = varargin_1.size(1);
    for (int k{0}; k < lowOrderSize; k++) {
      double b_d;
      b_d = varargin_1[k];
      if ((!(std::floor(b_d) == b_d)) || std::isinf(b_d)) {
        jc_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
      }
    }
  }
  nidx = varargin_1.size(1);
  if (varargin_1.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nidx; k++) {
    double b_this[2];
    boolean_T b;
    b_this[0] = m;
    b_this[1] = n;
    lowOrderSize = internal::ind2sub(b_this, varargin_1[k], varargout_4);
    if (lowOrderSize <= 0) {
      jc_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
    }
    if (lowOrderSize > m) {
      rtErrorWithMessageID(static_cast<long>(lowOrderSize), m,
                           mc_emlrtRTEI.fName, mc_emlrtRTEI.lineNo);
    }
    if (varargout_4 <= 0) {
      jc_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
    }
    if (varargout_4 > n) {
      rtErrorWithMessageID(static_cast<long>(varargout_4), n,
                           mc_emlrtRTEI.fName, mc_emlrtRTEI.lineNo);
    }
    overflow =
        b_sparse_locBsearch(rowidx, lowOrderSize, colidx[varargout_4 - 1],
                            colidx[varargout_4], thisv);
    if (thisv) {
      thisv = d[overflow - 1];
    } else {
      thisv = false;
    }
    b = !thisv;
    if ((!b) || (!(rhs[k] == 0.0))) {
      if (thisv && (rhs[k] != 0.0)) {
        d[overflow - 1] = true;
      } else if (b) {
        int nelem;
        if (colidx[colidx.size(0) - 1] - 1 == maxnz) {
          sparse::b_realloc(this, colidx[colidx.size(0) - 1] + 9, overflow,
                            overflow + 1, colidx[colidx.size(0) - 1] - 1);
          rowidx[overflow] = lowOrderSize;
          d[overflow] = (rhs[k] != 0.0);
        } else {
          nelem = (colidx[colidx.size(0) - 1] - overflow) - 1;
          if (nelem > 0) {
            std::memmove((void *)&rowidx[overflow + 1],
                         (void *)&rowidx[overflow],
                         (unsigned int)((size_t)nelem * sizeof(int)));
            std::memmove((void *)&d[overflow + 1], (void *)&d[overflow],
                         (unsigned int)((size_t)nelem * sizeof(boolean_T)));
          }
          d[overflow] = (rhs[k] != 0.0);
          rowidx[overflow] = lowOrderSize;
        }
        overflow = varargout_4 + 1;
        lowOrderSize = n + 1;
        if ((varargout_4 + 1 <= n + 1) && (n + 1 > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (nelem = overflow; nelem <= lowOrderSize; nelem++) {
          colidx[nelem - 1] = colidx[nelem - 1] + 1;
        }
      } else {
        int nelem;
        nelem = (colidx[colidx.size(0) - 1] - overflow) - 1;
        if (nelem > 0) {
          std::memmove((void *)&rowidx[overflow - 1], (void *)&rowidx[overflow],
                       (unsigned int)((size_t)nelem * sizeof(int)));
          std::memmove((void *)&d[overflow - 1], (void *)&d[overflow],
                       (unsigned int)((size_t)nelem * sizeof(boolean_T)));
        }
        overflow = varargout_4 + 1;
        lowOrderSize = n + 1;
        if ((varargout_4 + 1 <= lowOrderSize) && (lowOrderSize > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (nelem = overflow; nelem <= lowOrderSize; nelem++) {
          colidx[nelem - 1] = colidx[nelem - 1] - 1;
        }
      }
    }
  }
}

//
// Arguments    : const c_sparse &b
//                d_sparse &s
// Return Type  : void
//
void b_sparse::eq(const c_sparse &b, d_sparse &s) const
{
  static rtRunTimeErrorInfo bd_emlrtRTEI{
      460,                // lineNo
      34,                 // colNo
      "sparse/spfunImpl", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/shared/coder/coder/+coder/"
      "+internal/@sparse/sparse.m" // pName
  };
  static rtRunTimeErrorInfo cd_emlrtRTEI{
      178,             // lineNo
      39,              // colNo
      "sparse/sparse", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/shared/coder/coder/+coder/"
      "+internal/@sparse/sparse.m" // pName
  };
  d_anonymous_function uniOp;
  array<boolean_T, 2U> S;
  array<boolean_T, 1U> tmpd;
  if (b.colidx[b.colidx.size(0) - 1] - 1 > 0) {
    uniOp.workspace.sb = b.d[0];
  } else {
    uniOp.workspace.sb = 0.0;
  }
  if (!(uniOp.workspace.sb == 0.0)) {
    int col;
    int i;
    int idx;
    int loop_ub_tmp;
    int numalloc;
    int ridx;
    boolean_T val;
    col = colidx[colidx.size(0) - 1];
    if (col - 1 < 1) {
      numalloc = 0;
    } else {
      numalloc = col - 1;
    }
    tmpd.set_size(numalloc);
    for (i = 0; i < numalloc; i++) {
      tmpd[i] = (d[i] == uniOp.workspace.sb);
    }
    if (tmpd.size(0) != col - 1) {
      ob_rtErrorWithMessageID(bd_emlrtRTEI.fName, bd_emlrtRTEI.lineNo);
    }
    if (n < 0) {
      fc_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
    }
    if (n >= MAX_int32_T) {
      uc_rtErrorWithMessageID(gc_emlrtRTEI.fName, gc_emlrtRTEI.lineNo);
    }
    s.n = n;
    if (col - 1 < 0) {
      fc_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
    }
    if (col - 1 >= MAX_int32_T) {
      uc_rtErrorWithMessageID(gc_emlrtRTEI.fName, gc_emlrtRTEI.lineNo);
    }
    if (col - 1 < 0) {
      ec_rtErrorWithMessageID(cd_emlrtRTEI.fName, cd_emlrtRTEI.lineNo);
    }
    if (col - 1 >= 1) {
      numalloc = col - 2;
    } else {
      numalloc = 0;
    }
    s.d.set_size(numalloc + 1);
    for (i = 0; i <= numalloc; i++) {
      s.d[i] = false;
    }
    s.colidx.set_size(n + 1);
    loop_ub_tmp = n;
    for (i = 0; i <= loop_ub_tmp; i++) {
      s.colidx[i] = 0;
    }
    s.colidx[0] = 1;
    s.rowidx.set_size(numalloc + 1);
    for (i = 0; i <= numalloc; i++) {
      s.rowidx[i] = 0;
    }
    for (int c{0}; c < loop_ub_tmp; c++) {
      s.colidx[c + 1] = 1;
    }
    idx = 0;
    i = s.colidx.size(0);
    for (int c{0}; c <= i - 2; c++) {
      ridx = s.colidx[c];
      s.colidx[c] = idx + 1;
      int exitg1;
      do {
        exitg1 = 0;
        numalloc = s.colidx[c + 1];
        if (ridx < numalloc) {
          val = false;
          while (ridx < numalloc) {
            if (val || s.d[ridx - 1]) {
              val = true;
            }
            ridx++;
          }
          if (val) {
            s.d[idx] = true;
            s.rowidx[idx] = 0;
            idx++;
          }
        } else {
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (col - 1 < 1) {
      numalloc = 1;
    } else {
      numalloc = col;
    }
    for (i = 0; i <= numalloc - 2; i++) {
      s.rowidx[i] = rowidx[i];
    }
    s.colidx.set_size(colidx.size(0));
    numalloc = colidx.size(0);
    for (i = 0; i < numalloc; i++) {
      s.colidx[i] = colidx[i];
    }
    if (col - 1 > 2147483646) {
      check_forloop_overflow_error();
    }
    for (numalloc = 0; numalloc <= col - 2; numalloc++) {
      s.d[numalloc] = tmpd[numalloc];
    }
    idx = 1;
    i = colidx.size(0);
    for (int c{0}; c <= i - 2; c++) {
      ridx = s.colidx[c];
      s.colidx[c] = idx;
      while (ridx < s.colidx[c + 1]) {
        numalloc = s.rowidx[ridx - 1];
        val = s.d[ridx - 1];
        ridx++;
        if (val) {
          s.d[idx - 1] = true;
          s.rowidx[idx - 1] = numalloc;
          idx++;
        }
      }
    }
    s.colidx[s.colidx.size(0) - 1] = idx;
  } else {
    int loop_ub_tmp;
    S.set_size(1, n);
    loop_ub_tmp = n;
    for (int i{0}; i < loop_ub_tmp; i++) {
      S[i] = true;
    }
    if (n > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int col{0}; col < loop_ub_tmp; col++) {
      int numalloc;
      int ridx;
      numalloc = colidx[col];
      ridx = colidx[col + 1] - 1;
      if ((colidx[col] <= ridx) && (ridx > 2147483646)) {
        check_forloop_overflow_error();
      }
      for (int idx{numalloc}; idx <= ridx; idx++) {
        S[col] = (d[idx - 1] == uniOp.workspace.sb);
      }
    }
    j_sparse(S, s);
  }
}

//
// Arguments    : int ndiag
//                int b_m
//                int b_n
//                sparse &b_I
// Return Type  : void
//
void sparse::eyeLike(int ndiag, int b_m, int b_n, sparse &b_I)
{
  int b;
  int nzmax;
  b_I.m = b_m;
  nzmax = ndiag;
  b_I.n = b_n;
  if (ndiag < 1) {
    nzmax = 1;
  }
  b_I.maxnz = nzmax;
  b_I.d.set_size(nzmax);
  b_I.rowidx.set_size(nzmax);
  if (b_n + 1 < 0) {
    rtNonNegativeError(static_cast<double>(b_n + 1), o_emlrtDCI);
  }
  b_I.colidx.set_size(b_n + 1);
  if (ndiag > 2147483646) {
    check_forloop_overflow_error();
  }
  for (nzmax = 0; nzmax < ndiag; nzmax++) {
    b_I.d[nzmax] = 1.0;
    b_I.rowidx[nzmax] = nzmax + 1;
  }
  b_I.colidx[0] = 1;
  for (int c{2}; c <= ndiag; c++) {
    b_I.colidx[c - 1] = c;
  }
  nzmax = ndiag + 1;
  b = b_n + 1;
  if ((ndiag + 1 <= b_n + 1) && (b_n + 1 > 2147483646)) {
    check_forloop_overflow_error();
  }
  for (int c{nzmax}; c <= b; c++) {
    b_I.colidx[c - 1] = ndiag + 1;
  }
}

//
// Arguments    : void
// Return Type  : void
//
void sparse::fillIn()
{
  int i;
  int idx;
  idx = 1;
  i = colidx.size(0);
  for (int c{0}; c <= i - 2; c++) {
    int ridx;
    ridx = colidx[c];
    colidx[c] = idx;
    int exitg1;
    int i1;
    do {
      exitg1 = 0;
      i1 = colidx[c + 1];
      if (ridx < i1) {
        double val;
        int currRowIdx;
        val = 0.0;
        currRowIdx = rowidx[ridx - 1];
        while ((ridx < i1) && (rowidx[ridx - 1] == currRowIdx)) {
          val += d[ridx - 1];
          ridx++;
        }
        if (val != 0.0) {
          d[idx - 1] = val;
          rowidx[idx - 1] = currRowIdx;
          idx++;
        }
      } else {
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  colidx[colidx.size(0) - 1] = idx;
}

//
// Arguments    : array<boolean_T, 2U> &y
// Return Type  : void
//
void d_sparse::full(array<boolean_T, 2U> &y) const
{
  int cend_tmp;
  int loop_ub_tmp;
  y.set_size(1, n);
  loop_ub_tmp = n;
  for (cend_tmp = 0; cend_tmp < loop_ub_tmp; cend_tmp++) {
    y[cend_tmp] = false;
  }
  if (n > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int c{0}; c < loop_ub_tmp; c++) {
    int a;
    cend_tmp = colidx[c + 1] - 1;
    a = colidx[c];
    if ((colidx[c] <= cend_tmp) && (cend_tmp > 2147483646)) {
      check_forloop_overflow_error();
    }
    for (int idx{a}; idx <= cend_tmp; idx++) {
      y[c] = d[idx - 1];
    }
  }
}

//
// Arguments    : f_sparse &y
// Return Type  : void
//
void sparse::logical(f_sparse &y) const
{
  int i;
  int numalloc;
  int ridx;
  if (m < 0) {
    fc_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  if (m >= MAX_int32_T) {
    uc_rtErrorWithMessageID(gc_emlrtRTEI.fName, gc_emlrtRTEI.lineNo);
  }
  if (n < 0) {
    fc_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  if (n >= MAX_int32_T) {
    uc_rtErrorWithMessageID(gc_emlrtRTEI.fName, gc_emlrtRTEI.lineNo);
  }
  y.m = m;
  y.n = n;
  if (maxnz < 0) {
    fc_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  if (maxnz >= MAX_int32_T) {
    uc_rtErrorWithMessageID(gc_emlrtRTEI.fName, gc_emlrtRTEI.lineNo);
  }
  numalloc = maxnz;
  if (numalloc < 1) {
    numalloc = 1;
  }
  y.d.set_size(numalloc);
  for (i = 0; i < numalloc; i++) {
    y.d[i] = false;
  }
  y.maxnz = numalloc;
  y.colidx.set_size(n + 1);
  ridx = n;
  for (i = 0; i <= ridx; i++) {
    y.colidx[i] = 0;
  }
  y.colidx[0] = 1;
  y.rowidx.set_size(numalloc);
  for (i = 0; i < numalloc; i++) {
    y.rowidx[i] = 0;
  }
  for (int c{0}; c < ridx; c++) {
    y.colidx[c + 1] = 1;
  }
  numalloc = 0;
  i = y.colidx.size(0);
  for (int c{0}; c <= i - 2; c++) {
    ridx = y.colidx[c];
    y.colidx[c] = numalloc + 1;
    int exitg1;
    int i1;
    do {
      exitg1 = 0;
      i1 = y.colidx[c + 1];
      if (ridx < i1) {
        boolean_T val;
        val = false;
        while (ridx < i1) {
          if (val || y.d[ridx - 1]) {
            val = true;
          }
          ridx++;
        }
        if (val) {
          y.d[numalloc] = true;
          y.rowidx[numalloc] = 0;
          numalloc++;
        }
      } else {
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  y.rowidx.set_size(rowidx.size(0));
  numalloc = rowidx.size(0);
  for (i = 0; i < numalloc; i++) {
    y.rowidx[i] = rowidx[i];
  }
  y.colidx.set_size(colidx.size(0));
  numalloc = colidx.size(0);
  for (i = 0; i < numalloc; i++) {
    y.colidx[i] = colidx[i];
  }
  numalloc = colidx[colidx.size(0) - 1] - 1;
  if (numalloc < 1) {
    numalloc = 1;
  }
  for (ridx = 0; ridx < numalloc; ridx++) {
    if (std::isnan(d[ridx])) {
      ab_rtErrorWithMessageID(lb_emlrtRTEI.fName, lb_emlrtRTEI.lineNo);
    }
  }
  for (i = 0; i < numalloc; i++) {
    y.d[i] = (d[i] != 0.0);
  }
}

//
// Arguments    : h_sparse &y
// Return Type  : void
//
void g_sparse::logical(h_sparse &y) const
{
  int numalloc;
  if (m < 0) {
    fc_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  if (m >= MAX_int32_T) {
    uc_rtErrorWithMessageID(gc_emlrtRTEI.fName, gc_emlrtRTEI.lineNo);
  }
  y.m = m;
  if (maxnz < 0) {
    fc_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  if (maxnz >= MAX_int32_T) {
    uc_rtErrorWithMessageID(gc_emlrtRTEI.fName, gc_emlrtRTEI.lineNo);
  }
  numalloc = maxnz;
  if (numalloc < 1) {
    numalloc = 1;
  }
  y.d.set_size(numalloc);
  y.colidx.set_size(2);
  y.rowidx.set_size(numalloc);
  for (int k{0}; k < numalloc; k++) {
    y.d[k] = false;
    y.rowidx[k] = 0;
  }
  y.colidx[1] = 1;
  y.colidx[0] = 1;
  y.rowidx.set_size(rowidx.size(0));
  numalloc = rowidx.size(0);
  for (int k{0}; k < numalloc; k++) {
    y.rowidx[k] = rowidx[k];
  }
  y.colidx.set_size(colidx.size(0));
  numalloc = colidx.size(0);
  for (int k{0}; k < numalloc; k++) {
    y.colidx[k] = colidx[k];
  }
  numalloc = colidx[colidx.size(0) - 1] - 1;
  if (numalloc < 1) {
    numalloc = 1;
  }
  for (int k{0}; k < numalloc; k++) {
    if (std::isnan(d[k])) {
      ab_rtErrorWithMessageID(lb_emlrtRTEI.fName, lb_emlrtRTEI.lineNo);
    }
  }
  for (int k{0}; k < numalloc; k++) {
    y.d[k] = (d[k] != 0.0);
  }
}

//
// Arguments    : const array<double, 2U> &a
//                array<double, 2U> &c
// Return Type  : void
//
void sparse::mtimes(const array<double, 2U> &a, array<double, 2U> &c) const
{
  int aoff;
  int b_m;
  int b_n;
  int cidx;
  if (a.size(1) != m) {
    tb_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
  }
  b_m = a.size(0);
  b_n = n - 1;
  c.set_size(a.size(0), n);
  aoff = a.size(0) * n;
  for (cidx = 0; cidx < aoff; cidx++) {
    c[cidx] = 0.0;
  }
  if ((a.size(1) != 0) && (a.size(0) != 0) && (n != 0) &&
      (colidx[colidx.size(0) - 1] - 1 != 0)) {
    if (a.size(0) == 1) {
      aoff = n;
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int aidx_tmp{0}; aidx_tmp < aoff; aidx_tmp++) {
        double bd;
        int b_a;
        bd = 0.0;
        cidx = colidx[aidx_tmp + 1] - 1;
        b_a = colidx[aidx_tmp];
        if ((colidx[aidx_tmp] <= cidx) && (cidx > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int mend{b_a}; mend <= cidx; mend++) {
          bd += d[mend - 1] * a[rowidx[mend - 1] - 1];
        }
        c[aidx_tmp] = bd;
      }
    } else if (a.size(0) >= 4) {
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int ccol{0}; ccol <= b_n; ccol++) {
        int b_a;
        int bpend_tmp;
        int coff;
        coff = ccol * c.size(0);
        bpend_tmp = colidx[ccol + 1] - 1;
        b_a = colidx[ccol];
        if ((colidx[ccol] <= bpend_tmp) && (bpend_tmp > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int bp{b_a}; bp <= bpend_tmp; bp++) {
          double bd;
          int aoff_tmp;
          int mend;
          aoff_tmp = rowidx[bp - 1] - 1;
          aoff = aoff_tmp * a.size(0);
          bd = d[bp - 1];
          mend = (b_m / 4) << 2;
          if (mend > 2147483643) {
            check_forloop_overflow_error();
          }
          for (int crow{1}; crow <= mend; crow += 4) {
            int aidx_tmp;
            cidx = crow + coff;
            aidx_tmp = crow + aoff;
            c[cidx - 1] = c[cidx - 1] + a[aidx_tmp - 1] * bd;
            c[cidx] = c[cidx] + a[aidx_tmp] * bd;
            c[cidx + 1] = c[cidx + 1] + a[aidx_tmp + 1] * bd;
            c[cidx + 2] = c[cidx + 2] + a[aidx_tmp + 2] * bd;
          }
          aoff = mend + 1;
          if ((mend + 1 <= b_m) && (b_m > 2147483646)) {
            check_forloop_overflow_error();
          }
          for (int crow{aoff}; crow <= b_m; crow++) {
            cidx = (crow + coff) - 1;
            c[cidx] = c[cidx] + a[(crow + a.size(0) * aoff_tmp) - 1] * bd;
          }
        }
      }
    } else {
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int ccol{0}; ccol <= b_n; ccol++) {
        int b_a;
        int bpend_tmp;
        bpend_tmp = colidx[ccol + 1] - 1;
        b_a = colidx[ccol];
        if ((colidx[ccol] <= bpend_tmp) && (bpend_tmp > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int bp{b_a}; bp <= bpend_tmp; bp++) {
          for (int crow{0}; crow < b_m; crow++) {
            c[crow + c.size(0) * ccol] =
                c[crow + c.size(0) * ccol] +
                a[crow + a.size(0) * (rowidx[bp - 1] - 1)] * d[bp - 1];
          }
        }
      }
    }
  }
}

//
// Arguments    : const array<double, 2U> &b
//                array<double, 2U> &c
// Return Type  : void
//
void f_sparse::mtimes(const array<double, 2U> &b, array<double, 2U> &c) const
{
  int apendm1_tmp;
  int b_n;
  int nap;
  if (n != b.size(0)) {
    tb_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
  }
  b_n = b.size(1);
  c.set_size(m, b.size(1));
  nap = m * b.size(1);
  for (apendm1_tmp = 0; apendm1_tmp < nap; apendm1_tmp++) {
    c[apendm1_tmp] = 0.0;
  }
  if ((n != 0) && (m != 0) && (b.size(1) != 0) &&
      (colidx[colidx.size(0) - 1] - 1 != 0)) {
    if (b.size(1) == 1) {
      int b_b;
      b_b = n;
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int acol{0}; acol < b_b; acol++) {
        double bc;
        int a;
        int nap_tmp;
        bc = b[acol];
        a = colidx[acol];
        nap_tmp = colidx[acol + 1];
        nap = nap_tmp - colidx[acol];
        if (nap >= 4) {
          nap = ((nap_tmp - nap) + ((nap / 4) << 2)) - 1;
          if ((colidx[acol] <= nap) && (nap > 2147483643)) {
            check_forloop_overflow_error();
          }
          for (int ap{a}; ap <= nap; ap += 4) {
            apendm1_tmp = rowidx[ap - 1] - 1;
            c[apendm1_tmp] =
                c[apendm1_tmp] + static_cast<double>(d[ap - 1]) * bc;
            c[rowidx[ap] - 1] =
                c[rowidx[ap] - 1] + static_cast<double>(d[ap]) * bc;
            apendm1_tmp = rowidx[ap + 1] - 1;
            c[apendm1_tmp] =
                c[apendm1_tmp] + static_cast<double>(d[ap + 1]) * bc;
            apendm1_tmp = rowidx[ap + 2] - 1;
            c[apendm1_tmp] =
                c[apendm1_tmp] + static_cast<double>(d[ap + 2]) * bc;
          }
          apendm1_tmp = nap_tmp - 1;
          a = nap + 1;
          if ((nap + 1 <= nap_tmp - 1) && (nap_tmp - 1 > 2147483646)) {
            check_forloop_overflow_error();
          }
          for (int ap{a}; ap <= apendm1_tmp; ap++) {
            nap = rowidx[ap - 1] - 1;
            c[nap] = c[nap] + static_cast<double>(d[ap - 1]) * bc;
          }
        } else {
          nap = nap_tmp - 1;
          if ((colidx[acol] <= nap_tmp - 1) && (nap_tmp - 1 > 2147483646)) {
            check_forloop_overflow_error();
          }
          for (int ap{a}; ap <= nap; ap++) {
            apendm1_tmp = rowidx[ap - 1] - 1;
            c[apendm1_tmp] =
                c[apendm1_tmp] + static_cast<double>(d[ap - 1]) * bc;
          }
        }
      }
    } else {
      int b_b;
      boolean_T overflow;
      if (b.size(1) > 2147483646) {
        check_forloop_overflow_error();
      }
      b_b = n;
      overflow = (n > 2147483646);
      for (int j{0}; j < b_n; j++) {
        int coff;
        coff = j * c.size(0) - 1;
        if (overflow) {
          check_forloop_overflow_error();
        }
        for (int acol{0}; acol < b_b; acol++) {
          double bc;
          int a;
          int nap_tmp;
          bc = b[acol + b.size(0) * j];
          a = colidx[acol];
          nap_tmp = colidx[acol + 1];
          nap = nap_tmp - colidx[acol];
          if (nap >= 4) {
            nap = ((nap_tmp - nap) + ((nap / 4) << 2)) - 1;
            if ((colidx[acol] <= nap) && (nap > 2147483643)) {
              check_forloop_overflow_error();
            }
            for (int ap{a}; ap <= nap; ap += 4) {
              apendm1_tmp = rowidx[ap - 1] + coff;
              c[apendm1_tmp] =
                  c[apendm1_tmp] + static_cast<double>(d[ap - 1]) * bc;
              apendm1_tmp = rowidx[ap] + coff;
              c[apendm1_tmp] = c[apendm1_tmp] + static_cast<double>(d[ap]) * bc;
              apendm1_tmp = rowidx[ap + 1] + coff;
              c[apendm1_tmp] =
                  c[apendm1_tmp] + static_cast<double>(d[ap + 1]) * bc;
              apendm1_tmp = rowidx[ap + 2] + coff;
              c[apendm1_tmp] =
                  c[apendm1_tmp] + static_cast<double>(d[ap + 2]) * bc;
            }
            apendm1_tmp = nap_tmp - 1;
            a = nap + 1;
            if ((nap + 1 <= nap_tmp - 1) && (nap_tmp - 1 > 2147483646)) {
              check_forloop_overflow_error();
            }
            for (int ap{a}; ap <= apendm1_tmp; ap++) {
              nap = rowidx[ap - 1] - 1;
              c[nap + c.size(0) * j] =
                  c[nap + c.size(0) * j] + static_cast<double>(d[ap - 1]) * bc;
            }
          } else {
            nap = nap_tmp - 1;
            if ((colidx[acol] <= nap_tmp - 1) && (nap_tmp - 1 > 2147483646)) {
              check_forloop_overflow_error();
            }
            for (int ap{a}; ap <= nap; ap++) {
              apendm1_tmp = rowidx[ap - 1] + coff;
              c[apendm1_tmp] =
                  c[apendm1_tmp] + static_cast<double>(d[ap - 1]) * bc;
            }
          }
        }
      }
    }
  }
}

//
// Arguments    : const array<boolean_T, 1U> &rhs
//                const array<double, 2U> &varargin_1
// Return Type  : void
//
void f_sparse::parenAssign(const array<boolean_T, 1U> &rhs,
                           const array<double, 2U> &varargin_1)
{
  int nidx;
  int overflow;
  int varargout_4;
  internal::bigProduct(m, n, overflow);
  if (rhs.size(0) != varargin_1.size(1)) {
    qc_rtErrorWithMessageID(yc_emlrtRTEI.fName, yc_emlrtRTEI.lineNo);
  }
  if (overflow == 0) {
    overflow = m * n;
    nidx = varargin_1.size(1);
    for (int k{0}; k < nidx; k++) {
      double b_d;
      double d1;
      b_d = varargin_1[k];
      d1 = std::floor(b_d);
      if ((!(d1 == b_d)) || std::isinf(b_d)) {
        jc_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
      }
      if (!(b_d <= overflow)) {
        rtErrorWithMessageID(static_cast<long>(d1), overflow,
                             mc_emlrtRTEI.fName, mc_emlrtRTEI.lineNo);
      }
    }
  } else {
    nidx = varargin_1.size(1);
    for (int k{0}; k < nidx; k++) {
      double b_d;
      b_d = varargin_1[k];
      if ((!(std::floor(b_d) == b_d)) || std::isinf(b_d)) {
        jc_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
      }
    }
  }
  nidx = varargin_1.size(1);
  if (varargin_1.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nidx; k++) {
    double b_this[2];
    b_this[0] = m;
    b_this[1] = n;
    overflow = internal::ind2sub(b_this, varargin_1[k], varargout_4);
    parenAssign2D(rhs[k], static_cast<double>(overflow),
                  static_cast<double>(varargout_4));
  }
}

//
// Arguments    : const array<double, 1U> &varargin_2
//                sparse &s
// Return Type  : void
//
void sparse::parenReference(const array<double, 1U> &varargin_2,
                            sparse &s) const
{
  int i;
  int nd;
  int nd_tmp;
  int sn;
  int ub;
  ub = n;
  i = varargin_2.size(0);
  for (int k{0}; k < i; k++) {
    double b_d;
    b_d = std::floor(varargin_2[k]);
    if ((!(b_d == varargin_2[k])) || std::isinf(varargin_2[k])) {
      jc_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
    }
    if (!(varargin_2[k] <= ub)) {
      rtErrorWithMessageID(static_cast<long>(b_d), ub, mc_emlrtRTEI.fName,
                           mc_emlrtRTEI.lineNo);
    }
  }
  sn = varargin_2.size(0) - 1;
  ub = m * varargin_2.size(0);
  nd = 0;
  if (varargin_2.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int cidx{0}; cidx <= sn; cidx++) {
    nd_tmp = static_cast<int>(varargin_2[cidx]);
    nd = (nd + colidx[nd_tmp]) - colidx[nd_tmp - 1];
  }
  if ((nd > ub) && (ub != 0)) {
    i_rtErrorWithMessageID(tc_emlrtRTEI.fName, tc_emlrtRTEI.lineNo);
  }
  if (m < 0) {
    fc_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  if (m >= MAX_int32_T) {
    uc_rtErrorWithMessageID(gc_emlrtRTEI.fName, gc_emlrtRTEI.lineNo);
  }
  s.m = m;
  s.n = varargin_2.size(0);
  if (nd < 0) {
    fc_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  if (nd >= MAX_int32_T) {
    uc_rtErrorWithMessageID(gc_emlrtRTEI.fName, gc_emlrtRTEI.lineNo);
  }
  if (nd >= 1) {
    ub = nd;
  } else {
    ub = 1;
  }
  s.d.set_size(ub);
  for (i = 0; i < ub; i++) {
    s.d[i] = 0.0;
  }
  s.maxnz = ub;
  s.colidx.set_size(varargin_2.size(0) + 1);
  nd_tmp = varargin_2.size(0);
  for (i = 0; i <= nd_tmp; i++) {
    s.colidx[i] = 0;
  }
  s.colidx[0] = 1;
  s.rowidx.set_size(ub);
  for (i = 0; i < ub; i++) {
    s.rowidx[i] = 0;
  }
  ub = varargin_2.size(0);
  for (nd_tmp = 0; nd_tmp < ub; nd_tmp++) {
    s.colidx[nd_tmp + 1] = 1;
  }
  s.fillIn();
  if (nd != 0) {
    nd = 0;
    for (int cidx{0}; cidx <= sn; cidx++) {
      int colstart_tmp;
      ub = static_cast<int>(varargin_2[cidx]);
      colstart_tmp = colidx[ub - 1];
      ub = colidx[ub] - colstart_tmp;
      if (ub > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int k{0}; k < ub; k++) {
        i = (colstart_tmp + k) - 1;
        nd_tmp = nd + k;
        s.d[nd_tmp] = d[i];
        s.rowidx[nd_tmp] = rowidx[i];
      }
      if (ub - 1 >= 0) {
        nd += ub;
      }
      s.colidx[cidx + 1] = s.colidx[cidx] + ub;
    }
  }
}

//
// Arguments    : g_sparse &s
// Return Type  : void
//
void sparse::parenReference(g_sparse &s) const
{
  int i;
  int nd_tmp;
  int numalloc;
  if (n < 1) {
    rtErrorWithMessageID(static_cast<long>(1L), static_cast<int>(0),
                         mc_emlrtRTEI.fName, mc_emlrtRTEI.lineNo);
  }
  nd_tmp = colidx[1] - colidx[0];
  if ((nd_tmp > m) && (m != 0)) {
    i_rtErrorWithMessageID(tc_emlrtRTEI.fName, tc_emlrtRTEI.lineNo);
  }
  if (m < 0) {
    fc_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  if (m >= MAX_int32_T) {
    uc_rtErrorWithMessageID(gc_emlrtRTEI.fName, gc_emlrtRTEI.lineNo);
  }
  s.m = m;
  if (nd_tmp < 0) {
    fc_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  if (nd_tmp >= MAX_int32_T) {
    uc_rtErrorWithMessageID(gc_emlrtRTEI.fName, gc_emlrtRTEI.lineNo);
  }
  if (nd_tmp >= 1) {
    numalloc = nd_tmp;
  } else {
    numalloc = 1;
  }
  s.d.set_size(numalloc);
  s.maxnz = numalloc;
  s.colidx.set_size(2);
  s.rowidx.set_size(numalloc);
  for (i = 0; i < numalloc; i++) {
    s.d[i] = 0.0;
    s.rowidx[i] = 0;
  }
  s.colidx[0] = 1;
  s.colidx[1] = 1;
  if (nd_tmp != 0) {
    numalloc = colidx[0] - 2;
    for (int k{0}; k < nd_tmp; k++) {
      i = (numalloc + k) + 1;
      s.d[k] = d[i];
      s.rowidx[k] = rowidx[i];
    }
    s.colidx[1] = nd_tmp + 1;
  }
}

//
// Arguments    : const array<double, 2U> &varargin_1
//                d_sparse &s
// Return Type  : void
//
void f_sparse::parenReference(const array<double, 2U> &varargin_1,
                              d_sparse &s) const
{
  double dv[2];
  double varargout_1_tmp[2];
  int a__1;
  int colNnz;
  int i;
  int ncol;
  int overflow;
  boolean_T found;
  internal::b_bigProduct(m, n, overflow);
  if (overflow == 0) {
    a__1 = m * n;
    i = varargin_1.size(1);
    for (overflow = 0; overflow < i; overflow++) {
      double b_d;
      double d1;
      b_d = varargin_1[overflow];
      d1 = std::floor(b_d);
      if ((!(d1 == b_d)) || std::isinf(b_d)) {
        jc_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
      }
      if (!(b_d <= a__1)) {
        rtErrorWithMessageID(static_cast<long>(d1), a__1, mc_emlrtRTEI.fName,
                             mc_emlrtRTEI.lineNo);
      }
    }
  } else {
    i = varargin_1.size(1);
    for (overflow = 0; overflow < i; overflow++) {
      double b_d;
      b_d = varargin_1[overflow];
      if ((!(std::floor(b_d) == b_d)) || std::isinf(b_d)) {
        jc_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
      }
    }
  }
  ncol = varargin_1.size(1);
  varargout_1_tmp[0] = m;
  varargout_1_tmp[1] = n;
  dv[0] = 1.0;
  dv[1] = (static_cast<double>(varargin_1.size(1)) - 1.0) + 1.0;
  internal::indexShapeCheck(varargout_1_tmp, dv);
  s.n = varargin_1.size(1);
  found = (varargin_1.size(1) + 1 < 0);
  if (found) {
    rtNonNegativeError(static_cast<double>(varargin_1.size(1) + 1), o_emlrtDCI);
  }
  s.d.set_size(0);
  s.rowidx.set_size(0);
  a__1 = varargin_1.size(1) + 1;
  s.colidx.set_size(varargin_1.size(1) + 1);
  for (i = 0; i < a__1; i++) {
    s.colidx[i] = 0;
  }
  s.colidx[0] = 1;
  colNnz = 1;
  if (varargin_1.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int cidx{0}; cidx < ncol; cidx++) {
    a__1 = internal::ind2sub(varargout_1_tmp,
                             static_cast<int>(varargin_1[cidx]), overflow);
    a__1 = sparse_locBsearch(rowidx, static_cast<double>(a__1),
                             colidx[overflow - 1], colidx[overflow], found);
    if (found) {
      i = s.d.size(0);
      s.d.set_size(s.d.size(0) + 1);
      s.d[i] = d[a__1 - 1];
      i = s.rowidx.size(0);
      s.rowidx.set_size(s.rowidx.size(0) + 1);
      s.rowidx[i] = 1;
      colNnz++;
    }
    s.colidx[cidx + 1] = colNnz;
  }
  if (s.d.size(0) == 0) {
    s.d.set_size(1);
    s.d[0] = false;
    s.rowidx.set_size(1);
    s.rowidx[0] = 0;
  }
}

//
// Arguments    : c_sparse &s
// Return Type  : void
//
void b_sparse::parenReference(c_sparse &s) const
{
  int idx;
  boolean_T found;
  if (n < 1) {
    rtErrorWithMessageID(static_cast<long>(1L), static_cast<int>(0),
                         mc_emlrtRTEI.fName, mc_emlrtRTEI.lineNo);
  }
  s.colidx.set_size(2);
  s.colidx[0] = 1;
  s.colidx[1] = 1;
  idx = sparse_locBsearch(rowidx, 1.0, colidx[0], colidx[1], found);
  if (found) {
    s.d.set_size(1);
    s.d[0] = d[idx - 1];
    s.rowidx.set_size(1);
    s.rowidx[0] = 1;
    s.colidx[1] = 2;
  } else {
    s.d.set_size(1);
    s.d[0] = 0.0;
    s.rowidx.set_size(1);
    s.rowidx[0] = 0;
  }
}

} // namespace coder

//
// File trailer for sparse1.cpp
//
// [EOF]
//
