#include <stdio.h>
unsigned int reverse(unsigned int a, unsigned int nbits);
void assign(void);

int main(int argc, char **argv){
    assign();
}

// slow
unsigned int reverse(unsigned int a, unsigned int nbits){
    unsigned int reverse_num = 0, i, temp;
    for(i=0; i<nbits; i++){
        temp = (a&(1<<i));
        if (temp) reverse_num |= (1 << ((nbits -1)-i));
    }
    return reverse_num;
}

void assign(void){
    int A[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    int B[16] = {0};
    for (int i=0;i<16;i++){
        B[reverse(i, 4)] = A[i];
    }
    for (int i=0; i<16;i++){
        printf("B[%d]:%u\n", i, B[i]);
    }
    
}