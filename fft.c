#include "fft.h"

complex double J2PI = 6.28318530718 * I; // see https://samwho.dev/blog/duplicate-symbol-what/

/* recursively compute the FFT of a sequence x of length len.
 * stores the FFT into y
 * len must be a power of two. This will not be checked inside the function for speed
 */
void fft(complex double *x, int len, complex double *y){
    /* recursive base case */
    if (len == 2){
        y[0] = x[0]+x[1];
        y[1] = x[0]-x[1];
        return;
    }

    /* take FFTs of each side */
    // the divisions here need to be adjusted!
    // the split in half is ok, but the orders inside x must be shifted too. //i dont think they do
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

/* compute the circular prefix
 * has the form $W_N^k = \exp(-j2\pi k/N)$
 * N is length of the dft being taken and k the index aruond the circle
 */
complex double circular_prefix(int k, int N){
    /* N is power of two, can we make a simplification in the operation? */
    return cexp( - J2PI * k / N);
}

