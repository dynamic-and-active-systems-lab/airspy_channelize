//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: threshold.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "threshold.h"
#include "anonymous_function.h"
#include "buildtimecorrelatormatrix.h"
#include "eml_int_forloop_overflow_check.h"
#include "evfit.h"
#include "fileManager.h"
#include "find.h"
#include "fzero.h"
#include "interp1.h"
#include "nullAssignment.h"
#include "repetitionrejector.h"
#include "rt_nonfinite.h"
#include "sparse1.h"
#include "stft.h"
#include "toc.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "unaryMinOrMax.h"
#include "waveform.h"
#include "wfmstft.h"
#include "wgn.h"
#include "coder_array.h"
#include <cmath>
#include <cstddef>
#include <cstdio>

// Function Definitions
//
// THRESHOLD Constructs an instance of this class
// INPUTS:
//    pf  probability of false alarm
//
//
// Arguments    : double b_pf
// Return Type  : void
//
void threshold::init(double b_pf)
{
  trials = 100U;
  pf = b_pf;
  evMuParam = 0.0;
  evSigmaParam = 0.0;
  thresh1W = 0.0;
  threshVecFine.set_size(1);
  threshVecFine[0] = 0.0;
}

//
// BUILDTHRESHOLD generates a threshold vector for the waveform argument
// based on the false alarm probability input.
//
// This function creates a vector of thresholds for the incoherently summed
// results of the data in the input waveform. The probability of false alarm
// input is used for threshold generation. The output vector is a spectrally
// tuned threshold for each frequency in the STFT of the waveform. These
// thresholds are dependent on the power spectral density for each frequency
// bin, so areas of the spectrum with a high noise floor will have a higher
// output thresholde value
//
// INPUTS:
//    Wfm     A single waveform object
//    PF      A scalar probability of false alarm value (0 1];
// OUTPUTS:
//    newThresh   A vector of threshold with as many elements as rows in the
//                S matrix of the wfmstft object within the Wfm input.
//
// Author:    Michael W. Shafer
// Date:      2022-05-04
// --------------------------------------------------------------------------
//
// Arguments    : const waveform &Wfm
// Return Type  : void
//
void threshold::makenewthreshold(const waveform &Wfm)
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      165,                          // lineNo
      28,                           // colNo
      "scores",                     // aName
      "threshold/makenewthreshold", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      -1,                                       // iFirst
      -1,                                       // iLast
      310,                                      // lineNo
      37,                                       // colNo
      "values",                                 // aName
      "threshold/loadThresholdValuesFromCache", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      -1,                                       // iFirst
      -1,                                       // iLast
      309,                                      // lineNo
      37,                                       // colNo
      "values",                                 // aName
      "threshold/loadThresholdValuesFromCache", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      165,                          // lineNo
      59,                           // colNo
      "Ssynth",                     // aName
      "threshold/makenewthreshold", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtDoubleCheckInfo s_emlrtDCI{
      148,                          // lineNo
      17,                           // colNo
      "threshold/makenewthreshold", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      1                                              // checkKind
  };
  std::FILE *f;
  coder::b_anonymous_function theFunc;
  coder::sparse Wq;
  coder::sparse serialRejectionMatrix;
  coder::array<creal_T, 3U> Ssynth;
  coder::array<creal_T, 2U> b;
  coder::array<creal_T, 2U> xsynth;
  coder::array<creal_T, 2U> y;
  coder::array<double, 2U> b_y;
  coder::array<double, 2U> r;
  coder::array<double, 1U> b_Wfm;
  coder::array<double, 1U> bigA;
  coder::array<double, 1U> scores;
  coder::array<double, 1U> tStft;
  coder::array<int, 2U> b_stftSz;
  coder::array<char, 2U> b_str;
  coder::array<char, 2U> b_varargin_1;
  coder::array<char, 2U> str;
  coder::array<char, 2U> varargin_1;
  double nSamps;
  double previousToc;
  double s_im;
  double varargin_2;
  double varargin_3;
  double varargin_4;
  double varargin_5;
  int i;
  int loop_ub;
  int n;
  int nbytes;
  int numRead;
  signed char fileid;
  boolean_T incompleteRead;
  boolean_T overflow;
  previousToc = coder::toc();
  nSamps = 0.0;
  s_im = 0.0;
  varargin_2 = Wfm.N;
  varargin_3 = Wfm.M;
  varargin_4 = Wfm.J;
  varargin_5 = Wfm.K;
  varargin_1.set_size(1, globalThresholdCachePath.size(1) + 1);
  nbytes = globalThresholdCachePath.size(1);
  for (i = 0; i < nbytes; i++) {
    varargin_1[i] = globalThresholdCachePath[i];
  }
  varargin_1[globalThresholdCachePath.size(1)] = '\x00';
  b_varargin_1.set_size(1, globalThresholdCachePath.size(1) + 1);
  nbytes = globalThresholdCachePath.size(1);
  for (i = 0; i < nbytes; i++) {
    b_varargin_1[i] = globalThresholdCachePath[i];
  }
  b_varargin_1[globalThresholdCachePath.size(1)] = '\x00';
  nbytes = std::snprintf(nullptr, 0, "%s/N%f-M%f-J%f-K%f-Trials%u.threshold",
                         &b_varargin_1[0], varargin_2, varargin_3, varargin_4,
                         varargin_5, trials);
  if (nbytes + 1 < 0) {
    rtNonNegativeError(static_cast<double>(nbytes + 1), emlrtDCI);
  }
  str.set_size(1, nbytes + 1);
  std::snprintf(&str[0], (size_t)(nbytes + 1),
                "%s/N%f-M%f-J%f-K%f-Trials%u.threshold", &varargin_1[0],
                varargin_2, varargin_3, varargin_4, varargin_5, trials);
  if (nbytes < 1) {
    nbytes = 0;
  }
  str.set_size(str.size(0), nbytes);
  fileid = coder::internal::cfopen(str, "rb");
  if (fileid != -1) {
    boolean_T exitg1;
    nSamps = 0.0;
    // If formatSpec contains a combination of numeric and character specifiers,
    // then fscanf converts each character to its numeric equivalent. This
    // conversion occurs even when the format explicitly skips all numeric
    // values (for example, formatSpec is '%*d %s').
    bigA.set_size(0);
    numRead = 1;
    f = coder::internal::getfilestar(static_cast<double>(fileid),
                                     incompleteRead);
    exitg1 = false;
    while ((!exitg1) && (numRead > 0)) {
      nbytes = -1;
      numRead = std::fscanf(f, "%lf%n", &nSamps, &nbytes);
      if (nbytes != -1) {
        numRead++;
      }
      incompleteRead = (numRead == 0);
      if (numRead > 0) {
        i = bigA.size(0);
        bigA.set_size(bigA.size(0) + 1);
        bigA[i] = nSamps;
        incompleteRead = ((numRead < 2) || incompleteRead);
      }
      if (incompleteRead) {
        exitg1 = true;
      }
    }
    if (bigA.size(0) < 1) {
      rtDynamicBoundsError(1, 1, bigA.size(0), cb_emlrtBCI);
    }
    nSamps = bigA[0];
    if (bigA.size(0) < 2) {
      rtDynamicBoundsError(2, 1, bigA.size(0), bb_emlrtBCI);
    }
    s_im = bigA[1];
    coder::internal::cfclose(static_cast<double>(fileid));
  } else {
    //  Cache miss
  }
  evMuParam = nSamps;
  evSigmaParam = s_im;
  if ((nSamps == 0.0) && (s_im == 0.0)) {
    double stftSz[2];
    int k;
    unsigned int u;
    //  Mu and Sigma were not available from the cache. We have to generate them
    //  here.
    // This will be the reference power for the trials. Thresholds will be
    // interpolated for each bin from this value based on their bin power
    // median(freqBinPow);
    stftSz[0] = Wfm.stft->S.size(0);
    stftSz[1] = Wfm.stft->S.size(1);
    std::printf("\n \t Building time correlation matrix ...");
    std::fflush(stdout);
    // Build the Wq time correlation matrix
    buildtimecorrelatormatrix(Wfm.N, Wfm.M, Wfm.J, Wfm.K, Wq);
    nSamps = coder::toc() - previousToc;
    std::printf("complete. Elapsed time: %f seconds \n", nSamps);
    std::fflush(stdout);
    previousToc = coder::toc();
    std::printf("\t Building synthetic data and taking STFTs ...");
    std::fflush(stdout);
    i = static_cast<int>(stftSz[1]);
    if (i != Wq.m) {
      rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
    }
    // Here we approximated the number of samples of synthetic noise data needed
    // to get the correct number of time windows. We over estimate here and then
    // clip the number of correct windows after the stft operation.
    nSamps = (stftSz[1] + 1.0) * Wfm.n_ws + Wfm.n_ol;
    // Based on the STFT help file for the number of windows as a function of
    // samples. We add an additional windows worth of samples to ensure we have
    // enough in our STFT output. We'll clip off any excess after the STFT
    u = trials;
    if (static_cast<double>(u) != static_cast<int>(u)) {
      rtIntegerError(static_cast<double>(u), s_emlrtDCI);
    }
    nbytes = static_cast<int>(u);
    scores.set_size(nbytes);
    if (static_cast<double>(u) != static_cast<int>(u)) {
      rtIntegerError(static_cast<double>(u), s_emlrtDCI);
    }
    for (k = 0; k < nbytes; k++) {
      scores[k] = 0.0;
    }
    // Preallocate the scores matrix
    // Calculate the total power in the waveform for all frequency bins. Units
    // are W/bin * # bins = W
    coder::wgn(nSamps, trials, stftSz[0], xsynth);
    // Generate the synthetic data
    b_Wfm.set_size(Wfm.stft->wind.size(0));
    nbytes = Wfm.stft->wind.size(0) - 1;
    for (k = 0; k <= nbytes; k++) {
      b_Wfm[k] = Wfm.stft->wind[k];
    }
    coder::stft(xsynth, Wfm.Fs, b_Wfm, Wfm.n_ol, Wfm.n_w, Ssynth, bigA, tStft);
    nbytes = Ssynth.size(1) - i;
    b_stftSz.set_size(1, nbytes);
    for (k = 0; k < nbytes; k++) {
      b_stftSz[k] = (i + k) + 1;
    }
    coder::internal::nullAssignment(Ssynth, b_stftSz);
    // Trim excess so we have the correct number of windows.
    bigA.set_size(tStft.size(0));
    nbytes = tStft.size(0);
    for (k = 0; k < nbytes; k++) {
      bigA[k] = tStft[k];
    }
    nbytes = tStft.size(0) - i;
    b_stftSz.set_size(1, nbytes);
    for (k = 0; k < nbytes; k++) {
      b_stftSz[k] = (i + k) + 1;
    }
    coder::internal::nullAssignment(bigA, b_stftSz);
    nSamps = coder::toc() - previousToc;
    std::printf("complete. Elapsed time: %f seconds \n", nSamps);
    std::fflush(stdout);
    previousToc = coder::toc();
    std::printf("\t Running pulse summing process for all datasets ...");
    std::fflush(stdout);
    // Preform the incoherent summation using a matrix multiply.
    // Could use pagetimes.m for this, but it isn't supported for
    // code generation with sparse matrices as of R2023a
    repetitionrejector(bigA, serialRejectionMatrix);
    // [serialRejectionMatrix] = repetitionrejector(tStft, [0]);
    if (trials > 4294967294U) {
      coder::b_check_forloop_overflow_error();
    }
    i = static_cast<int>(trials);
    if (i - 1 >= 0) {
      loop_ub = Ssynth.size(1);
      n = Ssynth.size(1);
      overflow = (Ssynth.size(1) > 2147483646);
    }
    for (int b_i{0}; b_i < i; b_i++) {
      int inner;
      int m;
      xsynth.set_size(Wfm.W.size(0), Wfm.W.size(1));
      nbytes = Wfm.W.size(0) * Wfm.W.size(1);
      for (k = 0; k < nbytes; k++) {
        xsynth[k] = Wfm.W[k];
      }
      if ((static_cast<int>(static_cast<unsigned int>(b_i) + 1U) < 1) ||
          (static_cast<int>(static_cast<unsigned int>(b_i) + 1U) >
           Ssynth.size(2))) {
        rtDynamicBoundsError(
            static_cast<int>(static_cast<unsigned int>(b_i) + 1U), 1,
            Ssynth.size(2), db_emlrtBCI);
      }
      b.set_size(Ssynth.size(0), Ssynth.size(1));
      for (k = 0; k < loop_ub; k++) {
        nbytes = Ssynth.size(0);
        for (numRead = 0; numRead < nbytes; numRead++) {
          b[numRead + b.size(0) * k] =
              Ssynth[(numRead + Ssynth.size(0) * k) +
                     Ssynth.size(0) * Ssynth.size(1) * b_i];
        }
      }
      if (xsynth.size(0) != Ssynth.size(0)) {
        if (((xsynth.size(0) == 1) && (xsynth.size(1) == 1)) ||
            ((Ssynth.size(0) == 1) && (Ssynth.size(1) == 1))) {
          dc_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
        } else {
          tb_rtErrorWithMessageID(lc_emlrtRTEI.fName, lc_emlrtRTEI.lineNo);
        }
      }
      m = xsynth.size(1);
      inner = xsynth.size(0);
      y.set_size(xsynth.size(1), Ssynth.size(1));
      if (overflow) {
        coder::check_forloop_overflow_error();
      }
      for (int j{0}; j < n; j++) {
        int boffset;
        int coffset;
        coffset = j * m;
        boffset = j * Ssynth.size(0);
        if (m > 2147483646) {
          coder::check_forloop_overflow_error();
        }
        for (int c_i{0}; c_i < m; c_i++) {
          numRead = c_i * xsynth.size(0);
          nSamps = 0.0;
          s_im = 0.0;
          if (inner > 2147483646) {
            coder::check_forloop_overflow_error();
          }
          for (k = 0; k < inner; k++) {
            nbytes = numRead + k;
            varargin_2 = xsynth[nbytes].re;
            varargin_3 = -xsynth[nbytes].im;
            nbytes = boffset + k;
            varargin_4 = b[nbytes].im;
            varargin_5 = b[nbytes].re;
            nSamps += varargin_2 * varargin_5 - varargin_3 * varargin_4;
            s_im += varargin_2 * varargin_4 + varargin_3 * varargin_5;
          }
          k = coffset + c_i;
          y[k].re = nSamps;
          y[k].im = s_im;
        }
      }
      nbytes = y.size(0) * y.size(1);
      b_y.set_size(y.size(0), y.size(1));
      if (nbytes > 2147483646) {
        coder::check_forloop_overflow_error();
      }
      for (k = 0; k < nbytes; k++) {
        b_y[k] = rt_hypotd_snf(y[k].re, y[k].im);
      }
      r.set_size(b_y.size(0), b_y.size(1));
      nbytes = b_y.size(0) * b_y.size(1);
      for (k = 0; k < nbytes; k++) {
        nSamps = b_y[k];
        r[k] = nSamps * nSamps;
      }
      serialRejectionMatrix.mtimes(r, b_y);
      Wq.mtimes(b_y, r);
      nbytes = r.size(0) * r.size(1);
      if ((static_cast<int>(static_cast<unsigned int>(b_i) + 1U) < 1) ||
          (static_cast<int>(static_cast<unsigned int>(b_i) + 1U) >
           scores.size(0))) {
        rtDynamicBoundsError(
            static_cast<int>(static_cast<unsigned int>(b_i) + 1U), 1,
            scores.size(0), ab_emlrtBCI);
      }
      bigA = r.reshape(nbytes);
      scores[b_i] = coder::internal::unaryMinOrMax_anonFcn1(bigA);
      // 'all' call finds max across all temporal correlation sets and frequency
      // bins just like we do in the dectection code.
    }
    nSamps = coder::toc() - previousToc;
    std::printf("complete. Elapsed time: %f seconds \n", nSamps);
    std::fflush(stdout);
    previousToc = coder::toc();
    std::printf("\t Extracing extreme value fit parameters ...");
    std::fflush(stdout);
    // Build the distribution for all scores.
    // Old kernel density estimation method
    //  [f,xi]   =
    //  ksdensity(scores(:),'BoundaryCorrection','reflection','Support','positive');
    //  F        = cumtrapz(xi,f);
    // Updated extreme value estimation method
    // xi = linspace(1/2*min(scores),2*max(scores),1000);
    // paramEstsMaxima = evfit(-scores);
    // cdfVals = evcdf(-xi,paramEstsMaxima(1),paramEstsMaxima(2));
    // F = 1 - cdfVals;
    nbytes = scores.size(0);
    for (i = 0; i < nbytes; i++) {
      scores[i] = -scores[i];
    }
    coder::evfit(scores, stftSz);
    evMuParam = stftSz[0];
    evSigmaParam = stftSz[1];
    varargin_2 = Wfm.N;
    varargin_3 = Wfm.M;
    varargin_4 = Wfm.J;
    varargin_5 = Wfm.K;
    varargin_1.set_size(1, globalThresholdCachePath.size(1) + 1);
    nbytes = globalThresholdCachePath.size(1);
    for (i = 0; i < nbytes; i++) {
      varargin_1[i] = globalThresholdCachePath[i];
    }
    varargin_1[globalThresholdCachePath.size(1)] = '\x00';
    b_varargin_1.set_size(1, globalThresholdCachePath.size(1) + 1);
    nbytes = globalThresholdCachePath.size(1);
    for (i = 0; i < nbytes; i++) {
      b_varargin_1[i] = globalThresholdCachePath[i];
    }
    b_varargin_1[globalThresholdCachePath.size(1)] = '\x00';
    nbytes = std::snprintf(nullptr, 0, "%s/N%f-M%f-J%f-K%f-Trials%u.threshold",
                           &b_varargin_1[0], varargin_2, varargin_3, varargin_4,
                           varargin_5, trials);
    if (nbytes + 1 < 0) {
      rtNonNegativeError(static_cast<double>(nbytes + 1), emlrtDCI);
    }
    b_str.set_size(1, nbytes + 1);
    std::snprintf(&b_str[0], (size_t)(nbytes + 1),
                  "%s/N%f-M%f-J%f-K%f-Trials%u.threshold", &varargin_1[0],
                  varargin_2, varargin_3, varargin_4, varargin_5, trials);
    if (nbytes < 1) {
      nbytes = 0;
    }
    b_str.set_size(b_str.size(0), nbytes);
    fileid = coder::internal::cfopen(b_str, "wb");
    if (fileid == -1) {
      varargin_1.set_size(1, b_str.size(1) + 1);
      nbytes = b_str.size(1);
      for (i = 0; i < nbytes; i++) {
        varargin_1[i] = b_str[i];
      }
      varargin_1[b_str.size(1)] = '\x00';
      std::printf("threshold::saveThresholdValuesToCache ERROR - Unable to "
                  "open file %s\n",
                  &varargin_1[0]);
      std::fflush(stdout);
    } else {
      if (fileid == 0) {
        g_rtErrorWithMessageID(uc_emlrtRTEI.fName, uc_emlrtRTEI.lineNo);
      }
      f = coder::internal::getfilestar(static_cast<double>(fileid),
                                       incompleteRead);
      if (f == nullptr) {
        c_rtErrorWithMessageID(vc_emlrtRTEI.fName, vc_emlrtRTEI.lineNo);
      } else {
        std::fprintf(f, "%f\n", stftSz[0]);
        if (incompleteRead) {
          std::fflush(f);
        }
      }
      if (fileid == 0) {
        g_rtErrorWithMessageID(uc_emlrtRTEI.fName, uc_emlrtRTEI.lineNo);
      }
      f = coder::internal::getfilestar(static_cast<double>(fileid),
                                       incompleteRead);
      if (f == nullptr) {
        c_rtErrorWithMessageID(vc_emlrtRTEI.fName, vc_emlrtRTEI.lineNo);
      } else {
        std::fprintf(f, "%f\n", stftSz[1]);
        if (incompleteRead) {
          std::fflush(f);
        }
      }
      coder::internal::cfclose(static_cast<double>(fileid));
    }
    // figure;plot(xi,F)
    // Uncomment to see how fitted distribution compares to histogram of max
    // scores
    //  p = evpdf(-xi,paramEstsMaxima(1),paramEstsMaxima(2));
    //  figure
    //  histogram(scores,'Normalization','pdf');
    //  hold on
    //  plot(xi,p,'DisplayName','EV Fit'); legend('Location','best')
    //  p = 1-evcdf(-xi,paramEstsMaxima(1),paramEstsMaxima(2));
    //  figure
    //  histogram(scores,'Normalization','cdf');
    //  hold on
    //  plot(xi,p,'DisplayName','EV Fit'); legend('Location','best')
  } else {
    std::printf("\t threshold values were pulled from cache\n");
    std::fflush(stdout);
  }
  // EVTHRESH computs a threshold value based on the parameters of an extreme
  // value distribution and a desired false alarm probability
  //
  // INPUTS:
  //    mu      scalar location parameter of the EV distribution
  //    sigma   scalar scale parameter of the EV distribution
  //    pf      scalar probability of false alarm desired
  // OUPUTS:
  //    thresh  scalar value of the threshold
  // --------------------------------------------------------------------------
  theFunc.workspace.mu = evMuParam;
  if (!(evSigmaParam > 0.0)) {
    d_rtErrorWithMessageID(d_emlrtRTEI.fName, d_emlrtRTEI.lineNo);
  }
  if (!(pf >= 0.0)) {
    n_rtErrorWithMessageID("0", e_emlrtRTEI.fName, e_emlrtRTEI.lineNo);
  }
  // Equivalent to 1-evcdf(x,mu,sigma)-pf
  theFunc.workspace.sigma = evSigmaParam;
  theFunc.workspace.pf = pf;
  // theFunc monitonically decrease, so starting at x = 0 should always converge
  s_im = coder::fzero(theFunc);
  nSamps = coder::toc() - previousToc;
  std::printf("complete. Elapsed time: %f seconds \n", nSamps);
  std::fflush(stdout);
  coder::toc();
  // Now we linearly interpolate the threshold values for different noise
  // powers. We showed elsewhere this linear relationship hold by calculating
  // thresholds for ranges of noise power.
  // Here we deal with points where there is no change in F. Interp needs
  // unique values and at the tails of the distibution, there may be repeated
  // values.
  // nochangelogic = [false,diff(F)==0];
  // threshMedPow =
  // interp1(F(~nochangelogic),xi(~nochangelogic),1-PF,'pchip','extrap');
  //              powGrid    = [0 medPowAllFreqBins];
  //              threshGrid = [0 threshMedPow];
  //              newThresh =
  //              interp1(powGrid,threshGrid,freqBinPow,'linear','extrap');
  //
  //              %Finally,extrapolating the thresholds that are a little beyond
  //              the original %frequeny range can result in negative
  //              thresholds. Here we copy the first %and last valid threshold
  //              out to the places where the extrapolations would %have occured
  //              isnanThreshLogic   = isnan(newThresh);
  //              firstTrueThreshInd = find(~isnanThreshLogic,1,'first');
  //              lastTrueThreshInd  = find(~isnanThreshLogic,1,'last');
  //              firstTrueThresh    = newThresh(firstTrueThreshInd);
  //              lastTrueThresh     = newThresh(lastTrueThreshInd);
  //              newThresh(1:firstTrueThreshInd(1))  = firstTrueThresh; %The
  //              (1) call is needed by coder, as it doesn't know that the find
  //              call above will only produced a scalar output.
  //              newThresh(lastTrueThreshInd(1):end) = lastTrueThresh; %The (1)
  //              call is needed by coder, as it doesn't know that the find call
  //              above will only produced a scalar output. %toc
  //
  //              obj.thresh1W        = threshMedPow;
  //              obj.threshVecCoarse = newThresh;
  //              obj.threshVecFine   =
  //              interp1(Wfm.stft.f,double(newThresh),Wfm.Wf,'linear','extrap');
  setthreshprops(s_im, Wfm);
}

//
// Arguments    : double thresh
//                const waveform &Wfm
// Return Type  : void
//
void threshold::setthreshprops(double thresh, const waveform &Wfm)
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      -1,                         // iFirst
      -1,                         // iLast
      261,                        // lineNo
      44,                         // colNo
      "newThresh",                // aName
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      -1,                         // iFirst
      -1,                         // iLast
      262,                        // lineNo
      44,                         // colNo
      "newThresh",                // aName
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      -1,                         // iFirst
      -1,                         // iLast
      247,                        // lineNo
      63,                         // colNo
      "Wfm.stft.f",               // aName
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      -1,                         // iFirst
      -1,                         // iLast
      247,                        // lineNo
      49,                         // colNo
      "Wfm.stft.f",               // aName
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo eb_emlrtBCI{
      -1,                         // iFirst
      -1,                         // iLast
      263,                        // lineNo
      44,                         // colNo
      "firstTrueThreshInd",       // aName
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo fb_emlrtBCI{
      -1,                         // iFirst
      -1,                         // iLast
      263,                        // lineNo
      23,                         // colNo
      "newThresh",                // aName
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      -1,                         // iFirst
      -1,                         // iLast
      263,                        // lineNo
      25,                         // colNo
      "newThresh",                // aName
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo hb_emlrtBCI{
      -1,                         // iFirst
      -1,                         // iLast
      264,                        // lineNo
      41,                         // colNo
      "lastTrueThreshInd",        // aName
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo ib_emlrtBCI{
      -1,                         // iFirst
      -1,                         // iLast
      264,                        // lineNo
      23,                         // colNo
      "newThresh",                // aName
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo jb_emlrtBCI{
      -1,                         // iFirst
      -1,                         // iLast
      264,                        // lineNo
      44,                         // colNo
      "newThresh",                // aName
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtEqualityCheckInfo g_emlrtECI{
      -1,                         // nDims
      263,                        // lineNo
      13,                         // colNo
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m" // pName
  };
  static rtEqualityCheckInfo h_emlrtECI{
      -1,                         // nDims
      264,                        // lineNo
      13,                         // colNo
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m" // pName
  };
  coder::array<double, 2U> b_newThresh;
  coder::array<double, 1U> freqBinPSD;
  coder::array<double, 1U> newThresh;
  coder::array<boolean_T, 1U> x_tmp;
  double lastTrueThresh_data;
  int firstTrueThreshInd_data;
  int firstTrueThreshInd_size;
  int i;
  int ii_data;
  int ii_size;
  freqBinPSD.set_size(Wfm.stft->psd.size(0));
  firstTrueThreshInd_data = Wfm.stft->psd.size(0);
  for (i = 0; i < firstTrueThreshInd_data; i++) {
    freqBinPSD[i] = Wfm.stft->psd[i];
  }
  // Extract psd for current waveform. Units are W/Hz
  i = Wfm.stft->f.size(0);
  if (i < 2) {
    rtDynamicBoundsError(2, 1, i, db_emlrtBCI);
  }
  i = Wfm.stft->f.size(0);
  if (i < 1) {
    rtDynamicBoundsError(1, 1, i, cb_emlrtBCI);
  }
  lastTrueThresh_data = Wfm.stft->f[1] - Wfm.stft->f[0];
  firstTrueThreshInd_data = freqBinPSD.size(0);
  for (i = 0; i < firstTrueThreshInd_data; i++) {
    freqBinPSD[i] = freqBinPSD[i] * lastTrueThresh_data;
  }
  // PSD (W/Hz) times bin width (Hz/bin) gives bin total power in (W/bin)
  // 1W standard
  newThresh.set_size(freqBinPSD.size(0));
  firstTrueThreshInd_data = freqBinPSD.size(0);
  for (i = 0; i < firstTrueThreshInd_data; i++) {
    newThresh[i] = 0.0;
  }
  if (freqBinPSD.size(0) != 0) {
    double dv[2];
    dv[0] = 0.0;
    dv[1] = thresh;
    coder::interp1Linear(dv, freqBinPSD, newThresh);
  }
  // Finally,extrapolating the thresholds that are a little beyond the original
  // frequeny range can result in negative thresholds. Here we copy the first
  // and last valid threshold out to the places where the extrapolations would
  // have occured
  x_tmp.set_size(newThresh.size(0));
  firstTrueThreshInd_data = newThresh.size(0);
  for (i = 0; i < firstTrueThreshInd_data; i++) {
    x_tmp[i] = !std::isnan(newThresh[i]);
  }
  ii_size = coder::c_eml_find(x_tmp, (int *)&ii_data);
  firstTrueThreshInd_size = ii_size;
  for (i = 0; i < ii_size; i++) {
    firstTrueThreshInd_data = ii_data;
  }
  ii_size = coder::d_eml_find(x_tmp, (int *)&ii_data);
  for (i = 0; i < firstTrueThreshInd_size; i++) {
    if ((firstTrueThreshInd_data < 1) ||
        (firstTrueThreshInd_data > newThresh.size(0))) {
      rtDynamicBoundsError(firstTrueThreshInd_data, 1, newThresh.size(0),
                           ab_emlrtBCI);
    }
  }
  for (i = 0; i < ii_size; i++) {
    if ((ii_data < 1) || (ii_data > newThresh.size(0))) {
      rtDynamicBoundsError(ii_data, 1, newThresh.size(0), bb_emlrtBCI);
    }
    lastTrueThresh_data = newThresh[ii_data - 1];
  }
  if (firstTrueThreshInd_size < 1) {
    rtDynamicBoundsError(1, 1, firstTrueThreshInd_size, eb_emlrtBCI);
  }
  if (newThresh.size(0) < 1) {
    rtDynamicBoundsError(1, 1, newThresh.size(0), fb_emlrtBCI);
  }
  if ((firstTrueThreshInd_data < 1) ||
      (firstTrueThreshInd_data > newThresh.size(0))) {
    rtDynamicBoundsError(firstTrueThreshInd_data, 1, newThresh.size(0),
                         gb_emlrtBCI);
  }
  if (firstTrueThreshInd_data != firstTrueThreshInd_size) {
    rtSizeEq1DError(firstTrueThreshInd_data, firstTrueThreshInd_size,
                    g_emlrtECI);
  }
  b_newThresh.set_size(1, firstTrueThreshInd_data);
  for (i = 0; i < firstTrueThreshInd_data; i++) {
    b_newThresh[i] = newThresh[firstTrueThreshInd_data - 1];
  }
  firstTrueThreshInd_data = b_newThresh.size(1);
  for (i = 0; i < firstTrueThreshInd_data; i++) {
    newThresh[i] = b_newThresh[i];
  }
  // The (1) call is needed by coder, as it doesn't know that the find call
  // above will only produced a scalar output.
  if (ii_size < 1) {
    rtDynamicBoundsError(1, 1, ii_size, hb_emlrtBCI);
  }
  if (ii_data > newThresh.size(0)) {
    i = 0;
    firstTrueThreshInd_size = 0;
  } else {
    if ((ii_data < 1) || (ii_data > newThresh.size(0))) {
      rtDynamicBoundsError(ii_data, 1, newThresh.size(0), ib_emlrtBCI);
    }
    i = ii_data - 1;
    if (newThresh.size(0) < 1) {
      rtDynamicBoundsError(newThresh.size(0), 1, newThresh.size(0),
                           jb_emlrtBCI);
    }
    firstTrueThreshInd_size = newThresh.size(0);
  }
  firstTrueThreshInd_data = firstTrueThreshInd_size - i;
  if (firstTrueThreshInd_data != ii_size) {
    rtSizeEq1DError(firstTrueThreshInd_data, ii_size, h_emlrtECI);
  }
  for (firstTrueThreshInd_size = 0;
       firstTrueThreshInd_size < firstTrueThreshInd_data;
       firstTrueThreshInd_size++) {
    newThresh[i + firstTrueThreshInd_size] = lastTrueThresh_data;
  }
  // The (1) call is needed by coder, as it doesn't know that the find call
  // above will only produced a scalar output. toc
  thresh1W = thresh;
  coder::interp1(Wfm.stft->f, newThresh, Wfm.Wf, threshVecFine);
}

//
// File trailer for threshold.cpp
//
// [EOF]
//
