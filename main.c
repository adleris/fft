#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#include "file_read.h"
#include "fft.h"

char *get_fname(int argc, char **argv);

int main(int argc, char **argv){

    /* read in a data sequence from a file */
    complex double *x = NULL;
    unsigned int len = read_file(get_fname(argc, argv), &x);

    /* compute the fft */
    complex double *y = (complex double *)malloc(len * sizeof(complex double));
    fft(x,len,y);

    /* output to a text file where it can be read by matlab */
    FILE *out = fopen("fftout.txt", "w+");
    for (int i=0; i<len; i++){
        fprintf(out, "%lf%s%lfi\n", creal(y[i]), (cimag(y[i])>=0.0)?"+":"", cimag(y[i]));
    }

    free(x);
    free(y);
    return 0;
}

char *get_fname(int argc, char **argv){
    if (argc > 1) {
        return argv[1];
    }
    printf("usage: %s fname\n",argv[0]);
    exit(EXIT_FAILURE);
}