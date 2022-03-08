//
// File: FFT.cpp
//
// MATLAB Coder version            : 4.2
// C/C++ source code generated on  : 03-Mar-2022 14:25:36
//

// Include Files
#include <cmath>
#include "rt_nonfinite.h"
#include "FFT.h"
#include "fft1.h"

// Function Declarations
static double rt_hypotd_snf(double u0, double u1);

// Function Definitions

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_hypotd_snf(double u0, double u1)
{
  double y;
  double a;
  double b;
  a = std::abs(u0);
  b = std::abs(u1);
  if (a < b) {
    a /= b;
    y = b * std::sqrt(a * a + 1.0);
  } else if (a > b) {
    b /= a;
    y = a * std::sqrt(b * b + 1.0);
  } else if (rtIsNaN(b)) {
    y = b;
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

//
// Arguments    : const double d_data[]
//                const int d_size[1]
//                double F_data[]
//                int F_size[1]
// Return Type  : void
//
void FFT(const double d_data[], const int d_size[1], double F_data[], int
         F_size[1])
{
  creal_T f_data[512];
  int f_size[1];
  int nx;
  int k;
  fft(d_data, d_size, f_data, f_size);
  nx = f_size[0];
  F_size[0] = static_cast<short>(f_size[0]);
  for (k = 0; k < nx; k++) {
    F_data[k] = rt_hypotd_snf(f_data[k].re, f_data[k].im);
  }
}

//
// File trailer for FFT.cpp
//
// [EOF]
//
