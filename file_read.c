#include "file_read.h"

unsigned int read_file(char *fname, complex double **seq){
    FILE *fp = fopen(fname, "r");
    int len_to_read;
    int r = fscanf(fp, "%d", &len_to_read);
    unsigned int padded_len = next_pow_2(len_to_read);
    // if (r != EOF) {
    //     // todo is this how to check???
    //     fprintf(stderr, "read error\n");
    //     exit(EXIT_FAILURE);
    // }

    /* using calloc will automatically zero-pad the sequence for us */
    *seq = (complex double*)calloc(padded_len, sizeof(complex double));

    /* read in and allocate to the correct indicies of the array */
    int index = 0;
    double tmp;
    while ((r=fscanf(fp, "%lf", &tmp)) != EOF){
        /* is there an efficient way to jump right into the correct index? 
            - potentially a precomupted lookup table of index reverses. */
        index++;
        (*seq)[reverse(index, pow2log2(padded_len))] = tmp + 0*I; // do i have to explicityly convert to cplx
    }

    // show_arr_read_in(*seq, padded_len);

    fclose(fp);
    return padded_len;
}

unsigned next_pow_2(unsigned int v){
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    // v++;
    // return v;
    return v+1;
}


// unsigned int reverse(unsigned int a, unsigned int nbits){
//     unsigned int reverse_num = 0, i, temp;
//     for(i=0; i<nbits; i++){
//         temp = (a&(1<<i));
//         if (temp) reverse_num |= (1 << ((nbits -1)-i));
//     }
//     return reverse_num;
// }

/* reverse the first nbits in an unsigned int.
 * Verified for a \in [0,16] with nbits up to 4 by hand
 * this will be slower than a lookup table.
 */
unsigned int reverse(unsigned int a, unsigned int nbits){
    unsigned int out = 0x0;
    unsigned int i=0x0, p=0x0;
    for (i=0,p=1; i<nbits; i++, p*=2){
        if ((a & p) != 0){
            out |= (0x1 << (nbits-i-1));
        }
    }

#if SHOW_INDEX_REVERSAL
    /* display the reversal */
    printf("%u->%u\n\t",a,out);

    // REVERSE ORDER 16 bit printing
    for (int j=1, i=0; i</*16*/8; i++, j*=2){
        printf("%u", (a & j) != 0);
        // if ((i +1) % 8 == 0) printf(" ");
    }
    printf("\t");
    for (int j=1, i=0; i</*16*/8; i++, j*=2){
        printf("%u", (out & j) != 0);
        // if ((i +1) % 8 == 0) printf(" ");
    }
    printf("\n");
#endif
    return out;
}


unsigned int pow2log2(unsigned int a){
    // static int *powers = {0,1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32786,65536};
    // return powers[a];
    for (int i=0;i<31;i++){
        if (a >> i == 0){
            return i-1;//why -1 !
        }
    }
}

/* 
 * Display contents of the just read in array. Also includes index in the data file that the value was originally stored at, to verify the reversal.
 */
void show_arr_read_in(complex double *arr, unsigned int len){
    printf("%p\n", arr);
    for (int i=0; i<len; i++){
        // PRINT_CPLX(arr[i]);
        /* only show the reals, read in data is real only */
        printf("arr[%d]=%lf from [%d]\n", i, creal(arr[i]), reverse(i, pow2log2(len)));
    }
}