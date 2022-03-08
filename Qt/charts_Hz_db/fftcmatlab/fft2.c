/*
 * File: fft2.c
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 02-Mar-2022 20:22:02
 */

/* Include Files */
#include <math.h>
#include "rt_nonfinite.h"
#include "FFT.h"
#include "fft2.h"
#include "bluesteinSetup.h"

/* Function Declarations */
static void b_r2br_r2dit_trig(const creal_T x_data[], const int x_size[1], int
  n1_unsigned, const double costab_data[], const double sintab_data[], creal_T
  y_data[], int y_size[1]);
static void c_r2br_r2dit_trig(const creal_T x_data[], const int x_size[1], int
  n1_unsigned, const double costab_data[], const double sintab_data[], creal_T
  y_data[], int y_size[1]);
static void r2br_r2dit_trig_impl(const creal_T x_data[], const int x_size[1],
  int unsigned_nRows, const double costab_data[], const double sintab_data[],
  creal_T y_data[], int y_size[1]);

/* Function Definitions */

/*
 * Arguments    : const creal_T x_data[]
 *                const int x_size[1]
 *                int n1_unsigned
 *                const double costab_data[]
 *                const double sintab_data[]
 *                creal_T y_data[]
 *                int y_size[1]
 * Return Type  : void
 */
static void b_r2br_r2dit_trig(const creal_T x_data[], const int x_size[1], int
  n1_unsigned, const double costab_data[], const double sintab_data[], creal_T
  y_data[], int y_size[1])
{
  int istart;
  int nRowsM2;
  int nRowsD2;
  int nRowsD4;
  int ix;
  int iy;
  int ju;
  int i;
  boolean_T tst;
  double temp_re;
  double temp_im;
  double twid_re;
  double twid_im;
  int temp_re_tmp;
  int ihi;
  istart = x_size[0];
  if (istart >= n1_unsigned) {
    istart = n1_unsigned;
  }

  nRowsM2 = n1_unsigned - 2;
  nRowsD2 = n1_unsigned / 2;
  nRowsD4 = nRowsD2 / 2;
  y_size[0] = n1_unsigned;
  if (n1_unsigned > x_size[0]) {
    y_size[0] = n1_unsigned;
    for (iy = 0; iy < n1_unsigned; iy++) {
      y_data[iy].re = 0.0;
      y_data[iy].im = 0.0;
    }
  }

  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i <= istart - 2; i++) {
    y_data[iy] = x_data[ix];
    iy = n1_unsigned;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  y_data[iy] = x_data[ix];
  if (n1_unsigned > 1) {
    for (i = 0; i <= nRowsM2; i += 2) {
      temp_re = y_data[i + 1].re;
      temp_im = y_data[i + 1].im;
      twid_re = y_data[i].re;
      twid_im = y_data[i].im;
      y_data[i + 1].re = y_data[i].re - y_data[i + 1].re;
      y_data[i + 1].im = y_data[i].im - y_data[i + 1].im;
      twid_re += temp_re;
      twid_im += temp_im;
      y_data[i].re = twid_re;
      y_data[i].im = twid_im;
    }
  }

  iy = 2;
  ix = 4;
  ju = 1 + ((nRowsD4 - 1) << 2);
  while (nRowsD4 > 0) {
    for (i = 0; i < ju; i += ix) {
      temp_re_tmp = i + iy;
      temp_re = y_data[temp_re_tmp].re;
      temp_im = y_data[i + iy].im;
      y_data[temp_re_tmp].re = y_data[i].re - y_data[temp_re_tmp].re;
      y_data[temp_re_tmp].im = y_data[i].im - temp_im;
      y_data[i].re += temp_re;
      y_data[i].im += temp_im;
    }

    istart = 1;
    for (nRowsM2 = nRowsD4; nRowsM2 < nRowsD2; nRowsM2 += nRowsD4) {
      twid_re = costab_data[nRowsM2];
      twid_im = sintab_data[nRowsM2];
      i = istart;
      ihi = istart + ju;
      while (i < ihi) {
        temp_re_tmp = i + iy;
        temp_re = twid_re * y_data[temp_re_tmp].re - twid_im * y_data[i + iy].im;
        temp_im = twid_re * y_data[i + iy].im + twid_im * y_data[i + iy].re;
        y_data[temp_re_tmp].re = y_data[i].re - temp_re;
        y_data[temp_re_tmp].im = y_data[i].im - temp_im;
        y_data[i].re += temp_re;
        y_data[i].im += temp_im;
        i += ix;
      }

      istart++;
    }

    nRowsD4 /= 2;
    iy = ix;
    ix += ix;
    ju -= iy;
  }
}

/*
 * Arguments    : const creal_T x_data[]
 *                const int x_size[1]
 *                int n1_unsigned
 *                const double costab_data[]
 *                const double sintab_data[]
 *                creal_T y_data[]
 *                int y_size[1]
 * Return Type  : void
 */
static void c_r2br_r2dit_trig(const creal_T x_data[], const int x_size[1], int
  n1_unsigned, const double costab_data[], const double sintab_data[], creal_T
  y_data[], int y_size[1])
{
  int j;
  int nRowsM2;
  int nRowsD2;
  int nRowsD4;
  int ix;
  int iDelta2;
  int ju;
  int iy;
  int i;
  boolean_T tst;
  double temp_re;
  double temp_im;
  double twid_re;
  double twid_im;
  int temp_re_tmp;
  j = x_size[0];
  if (j >= n1_unsigned) {
    j = n1_unsigned;
  }

  nRowsM2 = n1_unsigned - 2;
  nRowsD2 = n1_unsigned / 2;
  nRowsD4 = nRowsD2 / 2;
  y_size[0] = n1_unsigned;
  if (n1_unsigned > x_size[0]) {
    y_size[0] = n1_unsigned;
    for (iDelta2 = 0; iDelta2 < n1_unsigned; iDelta2++) {
      y_data[iDelta2].re = 0.0;
      y_data[iDelta2].im = 0.0;
    }
  }

  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i <= j - 2; i++) {
    y_data[iy] = x_data[ix];
    iDelta2 = n1_unsigned;
    tst = true;
    while (tst) {
      iDelta2 >>= 1;
      ju ^= iDelta2;
      tst = ((ju & iDelta2) == 0);
    }

    iy = ju;
    ix++;
  }

  y_data[iy] = x_data[ix];
  if (n1_unsigned > 1) {
    for (i = 0; i <= nRowsM2; i += 2) {
      temp_re = y_data[i + 1].re;
      temp_im = y_data[i + 1].im;
      twid_re = y_data[i].re;
      twid_im = y_data[i].im;
      y_data[i + 1].re = y_data[i].re - y_data[i + 1].re;
      y_data[i + 1].im = y_data[i].im - y_data[i + 1].im;
      twid_re += temp_re;
      twid_im += temp_im;
      y_data[i].re = twid_re;
      y_data[i].im = twid_im;
    }
  }

  iy = 2;
  iDelta2 = 4;
  ix = 1 + ((nRowsD4 - 1) << 2);
  while (nRowsD4 > 0) {
    for (i = 0; i < ix; i += iDelta2) {
      temp_re_tmp = i + iy;
      temp_re = y_data[temp_re_tmp].re;
      temp_im = y_data[i + iy].im;
      y_data[temp_re_tmp].re = y_data[i].re - y_data[temp_re_tmp].re;
      y_data[temp_re_tmp].im = y_data[i].im - temp_im;
      y_data[i].re += temp_re;
      y_data[i].im += temp_im;
    }

    ju = 1;
    for (j = nRowsD4; j < nRowsD2; j += nRowsD4) {
      twid_re = costab_data[j];
      twid_im = sintab_data[j];
      i = ju;
      nRowsM2 = ju + ix;
      while (i < nRowsM2) {
        temp_re_tmp = i + iy;
        temp_re = twid_re * y_data[temp_re_tmp].re - twid_im * y_data[i + iy].im;
        temp_im = twid_re * y_data[i + iy].im + twid_im * y_data[i + iy].re;
        y_data[temp_re_tmp].re = y_data[i].re - temp_re;
        y_data[temp_re_tmp].im = y_data[i].im - temp_im;
        y_data[i].re += temp_re;
        y_data[i].im += temp_im;
        i += iDelta2;
      }

      ju++;
    }

    nRowsD4 /= 2;
    iy = iDelta2;
    iDelta2 += iDelta2;
    ix -= iy;
  }

  if (y_size[0] > 1) {
    twid_re = 1.0 / (double)y_size[0];
    iy = y_size[0];
    for (iDelta2 = 0; iDelta2 < iy; iDelta2++) {
      y_data[iDelta2].re *= twid_re;
      y_data[iDelta2].im *= twid_re;
    }
  }
}

/*
 * Arguments    : const creal_T x_data[]
 *                const int x_size[1]
 *                int unsigned_nRows
 *                const double costab_data[]
 *                const double sintab_data[]
 *                creal_T y_data[]
 *                int y_size[1]
 * Return Type  : void
 */
static void r2br_r2dit_trig_impl(const creal_T x_data[], const int x_size[1],
  int unsigned_nRows, const double costab_data[], const double sintab_data[],
  creal_T y_data[], int y_size[1])
{
  int istart;
  int nRowsM2;
  int nRowsD2;
  int nRowsD4;
  int ix;
  int iy;
  int ju;
  int i;
  boolean_T tst;
  double temp_re;
  double temp_im;
  double twid_re;
  double twid_im;
  int temp_re_tmp;
  int ihi;
  istart = x_size[0];
  if (istart >= unsigned_nRows) {
    istart = unsigned_nRows;
  }

  nRowsM2 = unsigned_nRows - 2;
  nRowsD2 = unsigned_nRows / 2;
  nRowsD4 = nRowsD2 / 2;
  y_size[0] = unsigned_nRows;
  if (unsigned_nRows > x_size[0]) {
    y_size[0] = unsigned_nRows;
    for (iy = 0; iy < unsigned_nRows; iy++) {
      y_data[iy].re = 0.0;
      y_data[iy].im = 0.0;
    }
  }

  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i <= istart - 2; i++) {
    y_data[iy] = x_data[ix];
    iy = unsigned_nRows;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  y_data[iy] = x_data[ix];
  if (unsigned_nRows > 1) {
    for (i = 0; i <= nRowsM2; i += 2) {
      temp_re = y_data[i + 1].re;
      temp_im = y_data[i + 1].im;
      twid_re = y_data[i].re;
      twid_im = y_data[i].im;
      y_data[i + 1].re = y_data[i].re - y_data[i + 1].re;
      y_data[i + 1].im = y_data[i].im - y_data[i + 1].im;
      twid_re += temp_re;
      twid_im += temp_im;
      y_data[i].re = twid_re;
      y_data[i].im = twid_im;
    }
  }

  iy = 2;
  ix = 4;
  ju = 1 + ((nRowsD4 - 1) << 2);
  while (nRowsD4 > 0) {
    for (i = 0; i < ju; i += ix) {
      temp_re_tmp = i + iy;
      temp_re = y_data[temp_re_tmp].re;
      temp_im = y_data[i + iy].im;
      y_data[temp_re_tmp].re = y_data[i].re - y_data[temp_re_tmp].re;
      y_data[temp_re_tmp].im = y_data[i].im - temp_im;
      y_data[i].re += temp_re;
      y_data[i].im += temp_im;
    }

    istart = 1;
    for (nRowsM2 = nRowsD4; nRowsM2 < nRowsD2; nRowsM2 += nRowsD4) {
      twid_re = costab_data[nRowsM2];
      twid_im = sintab_data[nRowsM2];
      i = istart;
      ihi = istart + ju;
      while (i < ihi) {
        temp_re_tmp = i + iy;
        temp_re = twid_re * y_data[temp_re_tmp].re - twid_im * y_data[i + iy].im;
        temp_im = twid_re * y_data[i + iy].im + twid_im * y_data[i + iy].re;
        y_data[temp_re_tmp].re = y_data[i].re - temp_re;
        y_data[temp_re_tmp].im = y_data[i].im - temp_im;
        y_data[i].re += temp_re;
        y_data[i].im += temp_im;
        i += ix;
      }

      istart++;
    }

    nRowsD4 /= 2;
    iy = ix;
    ix += ix;
    ju -= iy;
  }
}

/*
 * Arguments    : const double x_data[]
 *                const int x_size[1]
 *                int N2
 *                int n1
 *                const double costab_data[]
 *                const double sintab_data[]
 *                const double sintabinv_data[]
 *                creal_T y_data[]
 *                int y_size[1]
 * Return Type  : void
 */
void dobluesteinfft(const double x_data[], const int x_size[1], int N2, int n1,
                    const double costab_data[], const double sintab_data[],
                    const double sintabinv_data[], creal_T y_data[], int y_size
                    [1])
{
  creal_T wwc_data[1023];
  int wwc_size[1];
  int minNrowsNx;
  int xidx;
  int i1;
  int k;
  creal_T fv_data[2048];
  int fv_size[1];
  creal_T b_fv_data[2048];
  int b_fv_size[1];
  double fv_data_re;
  bluesteinSetup(n1, wwc_data, wwc_size);
  minNrowsNx = x_size[0];
  if (n1 < minNrowsNx) {
    minNrowsNx = n1;
  }

  y_size[0] = n1;
  if (n1 > x_size[0]) {
    y_size[0] = n1;
    for (i1 = 0; i1 < n1; i1++) {
      y_data[i1].re = 0.0;
      y_data[i1].im = 0.0;
    }
  }

  xidx = 0;
  for (k = 0; k < minNrowsNx; k++) {
    y_data[k].re = wwc_data[(n1 + k) - 1].re * x_data[xidx];
    y_data[k].im = wwc_data[(n1 + k) - 1].im * -x_data[xidx];
    xidx++;
  }

  i1 = minNrowsNx + 1;
  for (k = i1; k <= n1; k++) {
    y_data[k - 1].re = 0.0;
    y_data[k - 1].im = 0.0;
  }

  r2br_r2dit_trig_impl(y_data, y_size, N2, costab_data, sintab_data, fv_data,
                       fv_size);
  b_r2br_r2dit_trig(wwc_data, wwc_size, N2, costab_data, sintab_data, b_fv_data,
                    b_fv_size);
  b_fv_size[0] = fv_size[0];
  xidx = fv_size[0];
  for (i1 = 0; i1 < xidx; i1++) {
    fv_data_re = b_fv_data[i1].re;
    b_fv_data[i1].re = fv_data[i1].re * b_fv_data[i1].re - fv_data[i1].im *
      b_fv_data[i1].im;
    b_fv_data[i1].im = fv_data[i1].re * b_fv_data[i1].im + fv_data[i1].im *
      fv_data_re;
  }

  c_r2br_r2dit_trig(b_fv_data, b_fv_size, N2, costab_data, sintabinv_data,
                    fv_data, fv_size);
  xidx = 0;
  i1 = wwc_size[0];
  for (k = n1; k <= i1; k++) {
    y_data[xidx].re = wwc_data[k - 1].re * fv_data[k - 1].re + wwc_data[k - 1].
      im * fv_data[k - 1].im;
    y_data[xidx].im = wwc_data[k - 1].re * fv_data[k - 1].im - wwc_data[k - 1].
      im * fv_data[k - 1].re;
    xidx++;
  }
}

/*
 * Arguments    : int nRows
 *                boolean_T useRadix2
 *                double costab_data[]
 *                int costab_size[2]
 *                double sintab_data[]
 *                int sintab_size[2]
 *                double sintabinv_data[]
 *                int sintabinv_size[2]
 * Return Type  : void
 */
void generate_twiddle_tables(int nRows, boolean_T useRadix2, double costab_data[],
  int costab_size[2], double sintab_data[], int sintab_size[2], double
  sintabinv_data[], int sintabinv_size[2])
{
  double e;
  int n;
  double costab1q_data[513];
  int nd2;
  int k;
  int i0;
  e = 6.2831853071795862 / (double)nRows;
  n = nRows / 2 / 2;
  costab1q_data[0] = 1.0;
  nd2 = n / 2 - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q_data[1 + k] = cos(e * (1.0 + (double)k));
  }

  i0 = nd2 + 2;
  nd2 = n - 1;
  for (k = i0; k <= nd2; k++) {
    costab1q_data[k] = sin(e * (double)(n - k));
  }

  costab1q_data[n] = 0.0;
  if (!useRadix2) {
    i0 = n << 1;
    costab_size[0] = 1;
    costab_size[1] = (short)(i0 + 1);
    sintab_size[0] = 1;
    sintab_size[1] = (short)(i0 + 1);
    costab_data[0] = 1.0;
    sintab_data[0] = 0.0;
    sintabinv_size[0] = 1;
    sintabinv_size[1] = (short)(i0 + 1);
    for (k = 0; k < n; k++) {
      sintabinv_data[1 + k] = costab1q_data[(n - k) - 1];
    }

    nd2 = n + 1;
    for (k = nd2; k <= i0; k++) {
      sintabinv_data[k] = costab1q_data[k - n];
    }

    for (k = 0; k < n; k++) {
      costab_data[1 + k] = costab1q_data[1 + k];
      sintab_data[1 + k] = -costab1q_data[(n - k) - 1];
    }

    nd2 = n + 1;
    for (k = nd2; k <= i0; k++) {
      costab_data[k] = -costab1q_data[i0 - k];
      sintab_data[k] = -costab1q_data[k - n];
    }
  } else {
    nd2 = n << 1;
    costab_size[0] = 1;
    costab_size[1] = (short)(nd2 + 1);
    sintab_size[0] = 1;
    sintab_size[1] = (short)(nd2 + 1);
    costab_data[0] = 1.0;
    sintab_data[0] = 0.0;
    for (k = 0; k < n; k++) {
      costab_data[1 + k] = costab1q_data[1 + k];
      sintab_data[1 + k] = -costab1q_data[(n - k) - 1];
    }

    i0 = n + 1;
    for (k = i0; k <= nd2; k++) {
      costab_data[k] = -costab1q_data[nd2 - k];
      sintab_data[k] = -costab1q_data[k - n];
    }

    sintabinv_size[0] = 1;
    sintabinv_size[1] = 0;
  }
}

/*
 * Arguments    : int n1
 *                boolean_T useRadix2
 *                int *N2blue
 *                int *nRows
 * Return Type  : void
 */
void get_algo_sizes(int n1, boolean_T useRadix2, int *N2blue, int *nRows)
{
  int n;
  int pmax;
  int pmin;
  boolean_T exitg1;
  int p;
  int pow2p;
  *N2blue = 1;
  if (useRadix2) {
    *nRows = n1;
  } else {
    n = (n1 + n1) - 1;
    pmax = 31;
    if (n <= 1) {
      pmax = 0;
    } else {
      pmin = 0;
      exitg1 = false;
      while ((!exitg1) && (pmax - pmin > 1)) {
        p = (pmin + pmax) >> 1;
        pow2p = 1 << p;
        if (pow2p == n) {
          pmax = p;
          exitg1 = true;
        } else if (pow2p > n) {
          pmax = p;
        } else {
          pmin = p;
        }
      }
    }

    *N2blue = 1 << pmax;
    *nRows = *N2blue;
  }
}

/*
 * Arguments    : const double x_data[]
 *                const int x_size[1]
 *                int n1_unsigned
 *                const double costab_data[]
 *                const double sintab_data[]
 *                creal_T y_data[]
 *                int y_size[1]
 * Return Type  : void
 */
void r2br_r2dit_trig(const double x_data[], const int x_size[1], int n1_unsigned,
                     const double costab_data[], const double sintab_data[],
                     creal_T y_data[], int y_size[1])
{
  int istart;
  int nRowsM2;
  int nRowsD2;
  int nRowsD4;
  int ix;
  int iy;
  int ju;
  int i;
  boolean_T tst;
  double temp_re;
  double temp_im;
  double twid_re;
  double twid_im;
  int temp_re_tmp;
  int ihi;
  istart = x_size[0];
  if (istart >= n1_unsigned) {
    istart = n1_unsigned;
  }

  nRowsM2 = n1_unsigned - 2;
  nRowsD2 = n1_unsigned / 2;
  nRowsD4 = nRowsD2 / 2;
  y_size[0] = n1_unsigned;
  if (n1_unsigned > x_size[0]) {
    y_size[0] = n1_unsigned;
    for (iy = 0; iy < n1_unsigned; iy++) {
      y_data[iy].re = 0.0;
      y_data[iy].im = 0.0;
    }
  }

  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i <= istart - 2; i++) {
    y_data[iy].re = x_data[ix];
    y_data[iy].im = 0.0;
    iy = n1_unsigned;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  y_data[iy].re = x_data[ix];
  y_data[iy].im = 0.0;
  if (n1_unsigned > 1) {
    for (i = 0; i <= nRowsM2; i += 2) {
      temp_re = y_data[i + 1].re;
      temp_im = y_data[i + 1].im;
      twid_re = y_data[i].re;
      twid_im = y_data[i].im;
      y_data[i + 1].re = y_data[i].re - y_data[i + 1].re;
      y_data[i + 1].im = y_data[i].im - y_data[i + 1].im;
      twid_re += temp_re;
      twid_im += temp_im;
      y_data[i].re = twid_re;
      y_data[i].im = twid_im;
    }
  }

  iy = 2;
  ix = 4;
  ju = 1 + ((nRowsD4 - 1) << 2);
  while (nRowsD4 > 0) {
    for (i = 0; i < ju; i += ix) {
      temp_re_tmp = i + iy;
      temp_re = y_data[temp_re_tmp].re;
      temp_im = y_data[i + iy].im;
      y_data[temp_re_tmp].re = y_data[i].re - y_data[temp_re_tmp].re;
      y_data[temp_re_tmp].im = y_data[i].im - temp_im;
      y_data[i].re += temp_re;
      y_data[i].im += temp_im;
    }

    istart = 1;
    for (nRowsM2 = nRowsD4; nRowsM2 < nRowsD2; nRowsM2 += nRowsD4) {
      twid_re = costab_data[nRowsM2];
      twid_im = sintab_data[nRowsM2];
      i = istart;
      ihi = istart + ju;
      while (i < ihi) {
        temp_re_tmp = i + iy;
        temp_re = twid_re * y_data[temp_re_tmp].re - twid_im * y_data[i + iy].im;
        temp_im = twid_re * y_data[i + iy].im + twid_im * y_data[i + iy].re;
        y_data[temp_re_tmp].re = y_data[i].re - temp_re;
        y_data[temp_re_tmp].im = y_data[i].im - temp_im;
        y_data[i].re += temp_re;
        y_data[i].im += temp_im;
        i += ix;
      }

      istart++;
    }

    nRowsD4 /= 2;
    iy = ix;
    ix += ix;
    ju -= iy;
  }
}

/*
 * File trailer for fft2.c
 *
 * [EOF]
 */
