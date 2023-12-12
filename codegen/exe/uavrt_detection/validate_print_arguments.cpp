//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: validate_print_arguments.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 08:11:23
//

// Include Files
#include "validate_print_arguments.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : unsigned int varargin_1
//                unsigned int varargin_2
//                unsigned int varargin_3
//                unsigned int validatedArguments[3]
// Return Type  : void
//
namespace coder {
namespace internal {
void validate_print_arguments(unsigned int varargin_1, unsigned int varargin_2,
                              unsigned int varargin_3,
                              unsigned int validatedArguments[3])
{
  validatedArguments[0] = varargin_1;
  validatedArguments[1] = varargin_2;
  validatedArguments[2] = varargin_3;
}

} // namespace internal
} // namespace coder

//
// File trailer for validate_print_arguments.cpp
//
// [EOF]
//
