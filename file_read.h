#ifndef FILE_READ_H
#define FILE_READ_H

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

unsigned int read_file(char *fname, complex double **seq);
unsigned int reverse(unsigned int a, unsigned int nbits);
unsigned int next_pow_2(unsigned int v);
unsigned int pow2log2(unsigned int a);

#endif /* FILE_READ_H */