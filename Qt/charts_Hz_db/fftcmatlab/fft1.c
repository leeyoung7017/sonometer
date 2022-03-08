/*
 * File: fft1.c
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 02-Mar-2022 20:22:02
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "FFT.h"
#include "fft1.h"
#include "fft2.h"

/* Function Definitions */

/*
 * Arguments    : const double x_data[]
 *                const int x_size[1]
 *                creal_T y_data[]
 *                int y_size[1]
 * Return Type  : void
 */
void fft(double x_data[],int x_size[1], creal_T y_data[], int y_size[1])
{
  boolean_T useRadix2;
  int N2blue;
  int nRows;
  double costab_data[1025];
  int costab_size[2];
  double sintab_data[1025];
  int sintab_size[2];
  double sintabinv_data[1025];
  int sintabinv_size[2];
  if (x_size[0] == 0) 
    y_size[0] = 0;
  else {
    useRadix2 = ((x_size[0] & (x_size[0] - 1)) == 0);
    get_algo_sizes(x_size[0], useRadix2, &N2blue, &nRows);
    generate_twiddle_tables(nRows, useRadix2, costab_data, costab_size,
      sintab_data, sintab_size, sintabinv_data, sintabinv_size);
    if (useRadix2) {
      r2br_r2dit_trig(x_data, x_size, x_size[0], costab_data, sintab_data,
                      y_data, y_size);
    } else {
      dobluesteinfft(x_data, x_size, N2blue, x_size[0], costab_data, sintab_data,
                     sintabinv_data, y_data, y_size);
    }
  }
}

/*
 * File trailer for fft1.c
 *
 * [EOF]
 */
