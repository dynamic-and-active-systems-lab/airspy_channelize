//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: imresize.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "imresize.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "sub2ind.h"
#include "sum.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
namespace coder {
static void b_resizeAlongDim2D(const array<double, 2U> &in,
                               const array<double, 2U> &weights,
                               const array<int, 2U> &indices, double out_length,
                               array<double, 2U> &out);

static void contributions(int in_length, double out_length, double scale,
                          double kernel_width, array<double, 2U> &weights,
                          array<int, 2U> &indices);

static void resizeAlongDim2D(const array<double, 2U> &in,
                             const array<double, 2U> &weights,
                             const array<int, 2U> &indices, double out_length,
                             array<double, 2U> &out);

} // namespace coder
static void nc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const array<double, 2U> &in
//                const array<double, 2U> &weights
//                const array<int, 2U> &indices
//                double out_length
//                array<double, 2U> &out
// Return Type  : void
//
namespace coder {
static void b_resizeAlongDim2D(const array<double, 2U> &in,
                               const array<double, 2U> &weights,
                               const array<int, 2U> &indices, double out_length,
                               array<double, 2U> &out)
{
  double sumVal1;
  int iv[2];
  int i;
  int i1;
  int k;
  int ndx;
  int outCInd;
  int pixelIndex;
  int pixelIndex_tmp;
  int ub_loop;
  ub_loop = in.size(0) - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    pixelIndex, sumVal1, i, outCInd, iv, ndx, i1, k, pixelIndex_tmp)

  for (int inRInd = 0; inRInd <= ub_loop; inRInd++) {
    if (inRInd + 1 > in.size(0)) {
      hc_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
    }
    if (in.size(1) < 1) {
      hc_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
    }
    i = static_cast<int>(out_length);
    for (outCInd = 0; outCInd < i; outCInd++) {
      sumVal1 = 0.0;
      //  Core - second dimension
      iv[0] = (*(int(*)[2])((array<double, 2U> *)&weights)->size())[0];
      iv[1] = (*(int(*)[2])((array<double, 2U> *)&weights)->size())[1];
      ndx = internal::sub2ind(iv, static_cast<double>(outCInd) + 1.0);
      i1 = weights.size(0);
      for (k = 0; k < i1; k++) {
        pixelIndex_tmp = (ndx + k) - 1;
        pixelIndex = (inRInd + (indices[pixelIndex_tmp] - 1) * in.size(0)) + 1;
        sumVal1 += weights[pixelIndex_tmp] * in[pixelIndex - 1];
      }
      out[inRInd + out.size(0) * outCInd] = sumVal1;
    }
  }
}

//
// Arguments    : int in_length
//                double out_length
//                double scale
//                double kernel_width
//                array<double, 2U> &weights
//                array<int, 2U> &indices
// Return Type  : void
//
static void contributions(int in_length, double out_length, double scale,
                          double kernel_width, array<double, 2U> &weights,
                          array<int, 2U> &indices)
{
  array<double, 2U> absx;
  array<double, 2U> absx2;
  array<double, 2U> b_x;
  array<double, 2U> y;
  array<double, 1U> u;
  array<double, 1U> x;
  array<int, 2U> aux;
  array<int, 2U> b_indices;
  array<int, 2U> r;
  array<int, 1U> left;
  array<boolean_T, 2U> copyCols;
  double b_kernel_width;
  int b_i;
  int b_k;
  int csz_idx_0;
  int i;
  int loop_ub_tmp;
  int nx;
  int yk;
  boolean_T iscompatible;
  //  Contributions, using pixel indices
  if (scale < 1.0) {
    kernel_width = 4.0 / scale;
  }
  if (std::isnan(out_length)) {
    y.set_size(1, 1);
    y[0] = rtNaN;
  } else if (out_length < 1.0) {
    y.set_size(1, 0);
  } else {
    y.set_size(1, static_cast<int>(out_length - 1.0) + 1);
    yk = static_cast<int>(out_length - 1.0);
    for (i = 0; i <= yk; i++) {
      y[i] = static_cast<double>(i) + 1.0;
    }
  }
  b_kernel_width = 0.5 * (1.0 - 1.0 / scale);
  u.set_size(y.size(1));
  yk = y.size(1);
  for (i = 0; i < yk; i++) {
    u[i] = y[i] / scale + b_kernel_width;
  }
  b_kernel_width = kernel_width / 2.0;
  x.set_size(u.size(0));
  yk = u.size(0);
  for (i = 0; i < yk; i++) {
    x[i] = u[i] - b_kernel_width;
  }
  nx = x.size(0);
  if (x.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nx; k++) {
    x[k] = std::floor(x[k]);
  }
  left.set_size(x.size(0));
  yk = x.size(0);
  for (i = 0; i < yk; i++) {
    left[i] = static_cast<int>(x[i]);
  }
  nx = static_cast<int>(std::ceil(kernel_width) + 2.0);
  aux.set_size(1, nx);
  aux[0] = 0;
  yk = 0;
  if (static_cast<int>(std::ceil(kernel_width) + 2.0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{2}; k <= nx; k++) {
    yk++;
    aux[k - 1] = yk;
  }
  indices.set_size(left.size(0), aux.size(1));
  if (left.size(0) != 0) {
    i = aux.size(1) - 1;
    yk = (left.size(0) != 1);
    for (int k{0}; k <= i; k++) {
      b_i = indices.size(0) - 1;
      for (b_k = 0; b_k <= b_i; b_k++) {
        indices[b_k + indices.size(0) * k] = left[yk * b_k] + aux[k];
      }
    }
  }
  absx.set_size(indices.size(0), indices.size(1));
  loop_ub_tmp = indices.size(0) * indices.size(1);
  for (i = 0; i < loop_ub_tmp; i++) {
    absx[i] = indices[i];
  }
  if (absx.size(0) == 1) {
    csz_idx_0 = u.size(0);
  } else if (u.size(0) == 1) {
    csz_idx_0 = absx.size(0);
  } else if (u.size(0) == absx.size(0)) {
    csz_idx_0 = u.size(0);
  } else {
    u_rtErrorWithMessageID(cb_emlrtRTEI.fName, cb_emlrtRTEI.lineNo);
  }
  b_x.set_size(csz_idx_0, absx.size(1));
  if (csz_idx_0 != 0) {
    i = absx.size(1) - 1;
    nx = (u.size(0) != 1);
    for (int k{0}; k <= i; k++) {
      b_i = b_x.size(0) - 1;
      for (b_k = 0; b_k <= b_i; b_k++) {
        yk = nx * b_k;
        b_x[b_k + b_x.size(0) * k] = u[yk] - absx[yk + absx.size(0) * k];
      }
    }
  }
  if (scale < 1.0) {
    yk = b_x.size(0) * b_x.size(1);
    for (i = 0; i < yk; i++) {
      b_x[i] = scale * b_x[i];
    }
  }
  nx = b_x.size(0) * b_x.size(1);
  absx.set_size(b_x.size(0), b_x.size(1));
  if (nx > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nx; k++) {
    absx[k] = std::abs(b_x[k]);
  }
  absx2.set_size(absx.size(0), absx.size(1));
  nx = absx.size(0) * absx.size(1);
  if (nx > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nx; k++) {
    absx2[k] = absx[k] * absx[k];
  }
  weights.set_size(absx.size(0), absx.size(1));
  for (int k{0}; k < nx; k++) {
    weights[k] = rt_powd_snf(absx[k], 3.0);
  }
  for (i = 0; i < nx; i++) {
    absx2[i] = 2.5 * absx2[i];
  }
  for (i = 0; i < nx; i++) {
    weights[i] = ((1.5 * weights[i] - absx2[i]) + 1.0) *
                     static_cast<double>(absx[i] <= 1.0) +
                 (((-0.5 * weights[i] + absx2[i]) - 4.0 * absx[i]) + 2.0) *
                     static_cast<double>((absx[i] > 1.0) && (absx[i] <= 2.0));
  }
  if (scale < 1.0) {
    for (i = 0; i < nx; i++) {
      weights[i] = scale * weights[i];
    }
  }
  absx.set_size(weights.size(0), weights.size(1));
  for (i = 0; i < nx; i++) {
    absx[i] = weights[i];
  }
  sum(weights, u);
  iscompatible = true;
  if (u.size(0) == 1) {
    csz_idx_0 = weights.size(0);
  } else if (weights.size(0) == 1) {
    csz_idx_0 = u.size(0);
  } else if (weights.size(0) == u.size(0)) {
    csz_idx_0 = weights.size(0);
  } else {
    iscompatible = false;
    nx = u.size(0);
    csz_idx_0 = weights.size(0);
    if (nx <= csz_idx_0) {
      csz_idx_0 = nx;
    }
  }
  nx = weights.size(1);
  if (!iscompatible) {
    u_rtErrorWithMessageID(cb_emlrtRTEI.fName, cb_emlrtRTEI.lineNo);
  }
  weights.set_size(csz_idx_0, nx);
  if (csz_idx_0 != 0) {
    i = nx - 1;
    yk = (absx.size(0) != 1);
    nx = (u.size(0) != 1);
    for (int k{0}; k <= i; k++) {
      b_i = weights.size(0) - 1;
      for (b_k = 0; b_k <= b_i; b_k++) {
        weights[b_k + weights.size(0) * k] =
            absx[yk * b_k + absx.size(0) * k] / u[nx * b_k];
      }
    }
  }
  //  Create the auxiliary matrix:
  nx = in_length << 1;
  aux.set_size(1, nx);
  aux[0] = 1;
  aux[in_length] = in_length;
  if (in_length > 2147483646) {
    check_forloop_overflow_error();
  }
  for (b_i = 2; b_i <= in_length; b_i++) {
    aux[b_i - 1] = aux[b_i - 2] + 1;
    yk = in_length + b_i;
    aux[yk - 1] = aux[yk - 2] - 1;
  }
  //  Mirror the out-of-bounds indices using mod:
  for (b_i = 0; b_i < loop_ub_tmp; b_i++) {
    double c_k;
    b_kernel_width = static_cast<double>(indices[b_i]) - 1.0;
    c_k = b_kernel_width;
    if (nx == 0) {
      if (b_kernel_width == 0.0) {
        c_k = 0.0;
      }
    } else if (b_kernel_width == 0.0) {
      c_k = 0.0;
    } else {
      c_k = std::fmod(b_kernel_width, static_cast<double>(nx));
      if (c_k == 0.0) {
        c_k = 0.0;
      } else if (b_kernel_width < 0.0) {
        c_k += static_cast<double>(nx);
      }
    }
    indices[b_i] = aux[static_cast<int>(c_k)];
  }
  copyCols.set_size(1, weights.size(1));
  yk = weights.size(1);
  for (i = 0; i < yk; i++) {
    copyCols[i] = false;
  }
  nx = weights.size(1);
  yk = 0;
  if (weights.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (b_i = 0; b_i < nx; b_i++) {
    boolean_T exitg1;
    b_k = yk + weights.size(0);
    csz_idx_0 = yk;
    yk = b_k;
    if ((csz_idx_0 + 1 <= b_k) && (b_k > 2147483646)) {
      check_forloop_overflow_error();
    }
    exitg1 = false;
    while ((!exitg1) && (csz_idx_0 + 1 <= b_k)) {
      if ((weights[csz_idx_0] == 0.0) || std::isnan(weights[csz_idx_0])) {
        csz_idx_0++;
      } else {
        copyCols[b_i] = true;
        exitg1 = true;
      }
    }
  }
  yk = copyCols.size(1) - 1;
  nx = 0;
  for (b_i = 0; b_i <= yk; b_i++) {
    if (copyCols[b_i]) {
      nx++;
    }
  }
  r.set_size(1, nx);
  nx = 0;
  for (b_i = 0; b_i <= yk; b_i++) {
    if (copyCols[b_i]) {
      r[nx] = b_i;
      nx++;
    }
  }
  nx = weights.size(0);
  absx.set_size(r.size(1), weights.size(0));
  for (i = 0; i < nx; i++) {
    yk = r.size(1);
    for (b_i = 0; b_i < yk; b_i++) {
      absx[b_i + absx.size(0) * i] = weights[i + weights.size(0) * r[b_i]];
    }
  }
  weights.set_size(absx.size(0), absx.size(1));
  yk = absx.size(0) * absx.size(1);
  for (i = 0; i < yk; i++) {
    weights[i] = absx[i];
  }
  nx = indices.size(0);
  b_indices.set_size(r.size(1), indices.size(0));
  for (i = 0; i < nx; i++) {
    yk = r.size(1);
    for (b_i = 0; b_i < yk; b_i++) {
      b_indices[b_i + b_indices.size(0) * i] =
          indices[i + indices.size(0) * r[b_i]];
    }
  }
  indices.set_size(b_indices.size(0), b_indices.size(1));
  yk = b_indices.size(0) * b_indices.size(1);
  for (i = 0; i < yk; i++) {
    indices[i] = b_indices[i];
  }
}

//
// Arguments    : const array<double, 2U> &in
//                const array<double, 2U> &weights
//                const array<int, 2U> &indices
//                double out_length
//                array<double, 2U> &out
// Return Type  : void
//
static void resizeAlongDim2D(const array<double, 2U> &in,
                             const array<double, 2U> &weights,
                             const array<int, 2U> &indices, double out_length,
                             array<double, 2U> &out)
{
  double sumVal1;
  int iv[2];
  int i;
  int i1;
  int k;
  int ndx;
  int outRInd;
  int sumVal1_tmp;
  int ub_loop;
  ub_loop = static_cast<int>(static_cast<double>(in.size(0) * in.size(1)) /
                             static_cast<double>(in.size(0))) -
            1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    sumVal1, i, outRInd, iv, ndx, i1, k, sumVal1_tmp)

  for (int inCInd = 0; inCInd <= ub_loop; inCInd++) {
    i = static_cast<int>(out_length);
    for (outRInd = 0; outRInd < i; outRInd++) {
      sumVal1 = 0.0;
      iv[0] = (*(int(*)[2])((array<double, 2U> *)&weights)->size())[0];
      iv[1] = (*(int(*)[2])((array<double, 2U> *)&weights)->size())[1];
      ndx = internal::sub2ind(iv, static_cast<double>(outRInd) + 1.0);
      //  Core - first dimension
      i1 = weights.size(0);
      for (k = 0; k < i1; k++) {
        sumVal1_tmp = (ndx + k) - 1;
        sumVal1 += weights[sumVal1_tmp] *
                   in[(indices[sumVal1_tmp] + in.size(0) * inCInd) - 1];
      }
      out[outRInd + out.size(0) * inCInd] = sumVal1;
    }
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
} // namespace coder
static void nc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "OUTPUTSIZE must be a two-element vector of positive values.";
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
// Arguments    : const array<double, 2U> &Ain
//                const double varargin_1[2]
//                array<double, 2U> &Bout
// Return Type  : void
//
namespace coder {
void imresize(const array<double, 2U> &Ain, const double varargin_1[2],
              array<double, 2U> &Bout)
{
  static rtRunTimeErrorInfo
      bd_emlrtRTEI{
          319,        // lineNo
          5,          // colNo
          "imresize", // fName
          "/Applications/MATLAB_R2023b.app/toolbox/eml/lib/matlab/images/"
          "imresize.m" // pName
      };
  array<double, 2U> out;
  array<double, 2U> weights;
  array<int, 2U> indices;
  double outputSize_idx_0;
  double outputSize_idx_1;
  double scale_idx_0;
  double scale_idx_1;
  int k;
  boolean_T x[2];
  boolean_T exitg1;
  boolean_T y;
  if ((Ain.size(0) == 0) || (Ain.size(1) == 0)) {
    h_rtErrorWithMessageID("input number 1, A,", y_emlrtRTEI.fName,
                           y_emlrtRTEI.lineNo);
  }
  x[0] = (varargin_1[0] <= 0.0);
  x[1] = (varargin_1[1] <= 0.0);
  y = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 2)) {
    if (x[k]) {
      y = true;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (y) {
    nc_rtErrorWithMessageID(bd_emlrtRTEI.fName, bd_emlrtRTEI.lineNo);
  }
  if (std::isnan(varargin_1[0])) {
    outputSize_idx_0 =
        std::ceil(varargin_1[1] * static_cast<double>(Ain.size(0)) /
                  static_cast<double>(Ain.size(1)));
    outputSize_idx_1 = std::ceil(varargin_1[1]);
    scale_idx_0 = outputSize_idx_1 / static_cast<double>(Ain.size(1));
    scale_idx_1 = outputSize_idx_1 / static_cast<double>(Ain.size(1));
  } else if (std::isnan(varargin_1[1])) {
    outputSize_idx_0 = std::ceil(varargin_1[0]);
    outputSize_idx_1 =
        std::ceil(varargin_1[0] * static_cast<double>(Ain.size(1)) /
                  static_cast<double>(Ain.size(0)));
    scale_idx_0 = outputSize_idx_0 / static_cast<double>(Ain.size(0));
    scale_idx_1 = scale_idx_0;
  } else {
    outputSize_idx_0 = std::ceil(varargin_1[0]);
    outputSize_idx_1 = std::ceil(varargin_1[1]);
    scale_idx_0 = outputSize_idx_0 / static_cast<double>(Ain.size(0));
    scale_idx_1 = outputSize_idx_1 / static_cast<double>(Ain.size(1));
  }
  if (scale_idx_0 <= scale_idx_1) {
    //  Resize first dimension
    contributions(Ain.size(0), outputSize_idx_0, scale_idx_0, 4.0, weights,
                  indices);
    out.set_size(weights.size(1), Ain.size(1));
    resizeAlongDim2D(Ain, weights, indices,
                     static_cast<double>(weights.size(1)), out);
    //  Resize second dimension
    contributions(Ain.size(1), outputSize_idx_1, scale_idx_1, 4.0, weights,
                  indices);
    Bout.set_size(out.size(0), weights.size(1));
    b_resizeAlongDim2D(out, weights, indices,
                       static_cast<double>(weights.size(1)), Bout);
  } else {
    contributions(Ain.size(1), outputSize_idx_1, scale_idx_1, 4.0, weights,
                  indices);
    out.set_size(Ain.size(0), weights.size(1));
    b_resizeAlongDim2D(Ain, weights, indices,
                       static_cast<double>(weights.size(1)), out);
    //  Resize second dimension
    contributions(Ain.size(0), outputSize_idx_0, scale_idx_0, 4.0, weights,
                  indices);
    Bout.set_size(weights.size(1), out.size(1));
    resizeAlongDim2D(out, weights, indices,
                     static_cast<double>(weights.size(1)), Bout);
  }
}

} // namespace coder

//
// File trailer for imresize.cpp
//
// [EOF]
//
