#ifndef FILE_READ_H
#define FILE_READ_H

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#define SHOW_INDEX_REVERSAL 0

unsigned int read_file(char *fname, complex double **seq);
unsigned int reverse(unsigned int a, unsigned int nbits);
unsigned int next_pow_2(unsigned int v);
unsigned int pow2log2(unsigned int a);
void show_arr_read_in(complex double *arr, unsigned int len);

#endif /* FILE_READ_H */