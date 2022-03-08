/*
 * File: fft2.h
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 02-Mar-2022 20:22:02
 */

#ifndef FFT2_H
#define FFT2_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "FFT_types.h"

/* Function Declarations */
extern void dobluesteinfft(const double x_data[], const int x_size[1], int N2,
  int n1, const double costab_data[], const double sintab_data[], const double
  sintabinv_data[], creal_T y_data[], int y_size[1]);
extern void generate_twiddle_tables(int nRows, boolean_T useRadix2, double
  costab_data[], int costab_size[2], double sintab_data[], int sintab_size[2],
  double sintabinv_data[], int sintabinv_size[2]);
extern void get_algo_sizes(int n1, boolean_T useRadix2, int *N2blue, int *nRows);
extern void r2br_r2dit_trig(const double x_data[], const int x_size[1], int
  n1_unsigned, const double costab_data[], const double sintab_data[], creal_T
  y_data[], int y_size[1]);

#endif

/*
 * File trailer for fft2.h
 *
 * [EOF]
 */
