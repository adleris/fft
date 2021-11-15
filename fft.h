#ifndef FFT_H
#define FFT_H

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#define PRINT_CPLX(z) printf("%lf +j%lf\n", creal(z), cimag(z))


void fft(complex double *seq, int len, complex double *y);
complex double circular_prefix(int k, int N);

#endif