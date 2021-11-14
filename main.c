#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#include "file_read.h"

#define PRINT_CPLX(z) printf("%lf +j%lf\n",creal(z), cimag(z))

complex double J2PI = 6.28318530718 * I;

char *get_fname(int argc, char **argv);
void fft(complex double *seq, int len, complex double *y);
complex double circular_prefix(int k, int N);
unsigned next_pow_2(unsigned int v);

int main(int argc, char **argv){

    complex double *x = NULL;
    unsigned int len = read_file(get_fname(argc, argv), &x);
    printf("%p\n", x);
    for (int i=0; i<len; i++){
        // PRINT_CPLX(x[i]);
        printf("x[%d]=%lf from [%d]\n", i, creal(x[i]), reverse(i, pow2log2(len)));
    }
    complex double *y = (complex double *)malloc(len * sizeof(complex double));
    // fft(x,len,y);

    free(x);
    free(y);
    return 0;
}

void fft(complex double *x, int len, complex double *y){
    /* recursive base case */
    if (len == 2){
        y[0] = x[0]+x[1];
        y[1] = x[0]-x[1];
        return;
    }

    /* take FFTs of each side */
    // the divisions here need to be adjusted!
    // the split in half is ok, but the orders inside x must be shifted too.
    fft(x, len/2, y);
    fft(x+len/2, len/2, y);

    /* recombine */
    complex double tmp;
    int k;
    for (k = 0; k < len/2; k++){
        tmp = circular_prefix(k, len) * x[len/2 + k];
        y[k] = x[k] + tmp;
        y[len/2 +k] = x[k] - tmp;
    }
}

complex double circular_prefix(int k, int N){
    /* N is power of two, can we make a simplification? */
    return cexp( - J2PI * k / N);
}

char *get_fname(int argc, char **argv){
    if (argc > 1) {
        return argv[1];
    }
    printf("usage: %s fname\n",argv[0]);
    exit(EXIT_FAILURE);
}