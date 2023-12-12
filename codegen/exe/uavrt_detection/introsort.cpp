//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: introsort.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "introsort.h"
#include "anonymous_function.h"
#include "heapsort.h"
#include "insertionsort.h"
#include "rt_nonfinite.h"
#include "stack1.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include "omp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo xc_emlrtRTEI{
    62,           // lineNo
    39,           // colNo
    "stack/push", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/shared/coder/coder/lib/+coder/"
    "+internal/stack.m" // pName
};

static rtDoubleCheckInfo r_emlrtDCI{
    48,            // lineNo
    48,            // colNo
    "stack/stack", // fName
    "/Applications/MATLAB_R2023b.app/toolbox/shared/coder/coder/lib/+coder/"
    "+internal/stack.m", // pName
    4                    // checkKind
};

// Function Declarations
static void pc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void pc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Cannot push onto a fixed-size stack which is at capacity.";
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
// Arguments    : array<int, 1U> &x
//                int xend
//                const anonymous_function &cmp
// Return Type  : void
//
namespace coder {
namespace internal {
void introsort(array<int, 1U> &x, int xend, const anonymous_function &cmp)
{
  struct_T frame;
  if (xend > 1) {
    if (xend <= 32) {
      insertionsort(x, xend, cmp);
    } else {
      stack st;
      int MAXDEPTH;
      int i;
      int pmax;
      int pmin;
      int pow2p;
      int t;
      boolean_T exitg1;
      pmax = 31;
      pmin = 0;
      exitg1 = false;
      while ((!exitg1) && (pmax - pmin > 1)) {
        t = (pmin + pmax) >> 1;
        pow2p = 1 << t;
        if (pow2p == xend) {
          pmax = t;
          exitg1 = true;
        } else if (pow2p > xend) {
          pmax = t;
        } else {
          pmin = t;
        }
      }
      MAXDEPTH = (pmax - 1) << 1;
      frame.xstart = 1;
      frame.xend = xend;
      frame.depth = 0;
      pmax = MAXDEPTH << 1;
      if (pmax < 0) {
        rtNonNegativeError(static_cast<double>(pmax), r_emlrtDCI);
      }
      st.d.size[0] = pmax;
      for (i = 0; i < pmax; i++) {
        st.d.data[i] = frame;
      }
      if (pmax <= 0) {
        pc_rtErrorWithMessageID(xc_emlrtRTEI.fName, xc_emlrtRTEI.lineNo);
      }
      st.d.data[0] = frame;
      st.n = 1;
      while (st.n > 0) {
        int frame_tmp_tmp;
        frame_tmp_tmp = st.n - 1;
        frame = st.d.data[st.n - 1];
        st.n--;
        i = frame.xend - frame.xstart;
        if (i + 1 <= 32) {
          insertionsort(x, frame.xstart, frame.xend, cmp);
        } else if (frame.depth == MAXDEPTH) {
          b_heapsort(x, frame.xstart, frame.xend, cmp);
        } else {
          int xmid;
          boolean_T varargout_1;
          xmid = (frame.xstart + i / 2) - 1;
          i = cmp.workspace.a[x[xmid] - 1];
          pmax = x[frame.xstart - 1];
          pmin = cmp.workspace.a[pmax - 1];
          if (i < pmin) {
            varargout_1 = true;
          } else if (i == pmin) {
            varargout_1 =
                (cmp.workspace.b[x[xmid] - 1] < cmp.workspace.b[pmax - 1]);
          } else {
            varargout_1 = false;
          }
          if (varargout_1) {
            x[frame.xstart - 1] = x[xmid];
            x[xmid] = pmax;
          }
          i = x[frame.xend - 1];
          pmax = cmp.workspace.a[i - 1];
          pmin = x[frame.xstart - 1];
          t = cmp.workspace.a[pmin - 1];
          if (pmax < t) {
            varargout_1 = true;
          } else if (pmax == t) {
            varargout_1 = (cmp.workspace.b[i - 1] < cmp.workspace.b[pmin - 1]);
          } else {
            varargout_1 = false;
          }
          if (varargout_1) {
            x[frame.xstart - 1] = i;
            x[frame.xend - 1] = pmin;
          }
          i = x[frame.xend - 1];
          pmax = cmp.workspace.a[i - 1];
          pmin = cmp.workspace.a[x[xmid] - 1];
          if (pmax < pmin) {
            varargout_1 = true;
          } else if (pmax == pmin) {
            varargout_1 =
                (cmp.workspace.b[i - 1] < cmp.workspace.b[x[xmid] - 1]);
          } else {
            varargout_1 = false;
          }
          if (varargout_1) {
            t = x[xmid];
            x[xmid] = i;
            x[frame.xend - 1] = t;
          }
          pow2p = x[xmid] - 1;
          x[xmid] = x[frame.xend - 2];
          x[frame.xend - 2] = pow2p + 1;
          pmax = frame.xstart - 1;
          pmin = frame.xend - 2;
          int exitg2;
          do {
            int exitg3;
            exitg2 = 0;
            pmax++;
            do {
              exitg3 = 0;
              i = cmp.workspace.a[x[pmax] - 1];
              if (i < cmp.workspace.a[pow2p]) {
                varargout_1 = true;
              } else if (i == cmp.workspace.a[pow2p]) {
                varargout_1 =
                    (cmp.workspace.b[x[pmax] - 1] < cmp.workspace.b[pow2p]);
              } else {
                varargout_1 = false;
              }
              if (varargout_1) {
                pmax++;
              } else {
                exitg3 = 1;
              }
            } while (exitg3 == 0);
            pmin--;
            do {
              exitg3 = 0;
              i = cmp.workspace.a[x[pmin] - 1];
              if (cmp.workspace.a[pow2p] < i) {
                varargout_1 = true;
              } else if (cmp.workspace.a[pow2p] == i) {
                varargout_1 =
                    (cmp.workspace.b[pow2p] < cmp.workspace.b[x[pmin] - 1]);
              } else {
                varargout_1 = false;
              }
              if (varargout_1) {
                pmin--;
              } else {
                exitg3 = 1;
              }
            } while (exitg3 == 0);
            if (pmax + 1 >= pmin + 1) {
              exitg2 = 1;
            } else {
              t = x[pmax];
              x[pmax] = x[pmin];
              x[pmin] = t;
            }
          } while (exitg2 == 0);
          x[frame.xend - 2] = x[pmax];
          x[pmax] = pow2p + 1;
          if (pmax + 2 < frame.xend) {
            if (frame_tmp_tmp >= st.d.size[0]) {
              pc_rtErrorWithMessageID(xc_emlrtRTEI.fName, xc_emlrtRTEI.lineNo);
            }
            st.d.data[frame_tmp_tmp].xstart = pmax + 2;
            st.d.data[frame_tmp_tmp].xend = frame.xend;
            st.d.data[frame_tmp_tmp].depth = frame.depth + 1;
            st.n = frame_tmp_tmp + 1;
          }
          if (frame.xstart < pmax + 1) {
            if (st.n >= st.d.size[0]) {
              pc_rtErrorWithMessageID(xc_emlrtRTEI.fName, xc_emlrtRTEI.lineNo);
            }
            st.d.data[st.n].xstart = frame.xstart;
            st.d.data[st.n].xend = pmax + 1;
            st.d.data[st.n].depth = frame.depth + 1;
            st.n++;
          }
        }
      }
    }
  }
}

//
// Arguments    : array<int, 1U> &x
//                int xend
//                const c_anonymous_function &cmp
// Return Type  : void
//
void introsort(array<int, 1U> &x, int xend, const c_anonymous_function &cmp)
{
  struct_T frame;
  int pmin;
  if (xend > 1) {
    if (xend <= 32) {
      insertionsort(x, xend, cmp);
    } else {
      stack st;
      int MAXDEPTH;
      int i;
      int pmax;
      int pow2p;
      int t;
      boolean_T exitg1;
      pmax = 31;
      pmin = 0;
      exitg1 = false;
      while ((!exitg1) && (pmax - pmin > 1)) {
        t = (pmin + pmax) >> 1;
        pow2p = 1 << t;
        if (pow2p == xend) {
          pmax = t;
          exitg1 = true;
        } else if (pow2p > xend) {
          pmax = t;
        } else {
          pmin = t;
        }
      }
      MAXDEPTH = (pmax - 1) << 1;
      frame.xstart = 1;
      frame.xend = xend;
      frame.depth = 0;
      pmax = MAXDEPTH << 1;
      if (pmax < 0) {
        rtNonNegativeError(static_cast<double>(pmax), r_emlrtDCI);
      }
      st.d.size[0] = pmax;
      for (i = 0; i < pmax; i++) {
        st.d.data[i] = frame;
      }
      if (pmax <= 0) {
        pc_rtErrorWithMessageID(xc_emlrtRTEI.fName, xc_emlrtRTEI.lineNo);
      }
      st.d.data[0] = frame;
      st.n = 1;
      while (st.n > 0) {
        int frame_tmp_tmp;
        frame_tmp_tmp = st.n - 1;
        frame = st.d.data[st.n - 1];
        st.n--;
        i = frame.xend - frame.xstart;
        if (i + 1 <= 32) {
          insertionsort(x, frame.xstart, frame.xend, cmp);
        } else if (frame.depth == MAXDEPTH) {
          b_heapsort(x, frame.xstart, frame.xend, cmp);
        } else {
          pmin = (frame.xstart + i / 2) - 1;
          i = x[frame.xstart - 1];
          if (cmp.workspace.x[x[pmin] - 1] < cmp.workspace.x[i - 1]) {
            x[frame.xstart - 1] = x[pmin];
            x[pmin] = i;
          }
          i = x[frame.xstart - 1];
          pmax = x[frame.xend - 1];
          if (cmp.workspace.x[pmax - 1] < cmp.workspace.x[i - 1]) {
            x[frame.xstart - 1] = pmax;
            x[frame.xend - 1] = i;
          }
          i = x[frame.xend - 1];
          if (cmp.workspace.x[i - 1] < cmp.workspace.x[x[pmin] - 1]) {
            t = x[pmin];
            x[pmin] = i;
            x[frame.xend - 1] = t;
          }
          pow2p = x[pmin];
          x[pmin] = x[frame.xend - 2];
          x[frame.xend - 2] = pow2p;
          pmax = frame.xstart - 1;
          pmin = frame.xend - 2;
          int exitg2;
          do {
            exitg2 = 0;
            pmax++;
            int exitg3;
            do {
              exitg3 = 0;
              i = cmp.workspace.x[pow2p - 1];
              if (cmp.workspace.x[x[pmax] - 1] < i) {
                pmax++;
              } else {
                exitg3 = 1;
              }
            } while (exitg3 == 0);
            for (pmin--; i < cmp.workspace.x[x[pmin] - 1]; pmin--) {
            }
            if (pmax + 1 >= pmin + 1) {
              exitg2 = 1;
            } else {
              t = x[pmax];
              x[pmax] = x[pmin];
              x[pmin] = t;
            }
          } while (exitg2 == 0);
          x[frame.xend - 2] = x[pmax];
          x[pmax] = pow2p;
          if (pmax + 2 < frame.xend) {
            if (frame_tmp_tmp >= st.d.size[0]) {
              pc_rtErrorWithMessageID(xc_emlrtRTEI.fName, xc_emlrtRTEI.lineNo);
            }
            st.d.data[frame_tmp_tmp].xstart = pmax + 2;
            st.d.data[frame_tmp_tmp].xend = frame.xend;
            st.d.data[frame_tmp_tmp].depth = frame.depth + 1;
            st.n = frame_tmp_tmp + 1;
          }
          if (frame.xstart < pmax + 1) {
            if (st.n >= st.d.size[0]) {
              pc_rtErrorWithMessageID(xc_emlrtRTEI.fName, xc_emlrtRTEI.lineNo);
            }
            st.d.data[st.n].xstart = frame.xstart;
            st.d.data[st.n].xend = pmax + 1;
            st.d.data[st.n].depth = frame.depth + 1;
            st.n++;
          }
        }
      }
    }
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for introsort.cpp
//
// [EOF]
//
