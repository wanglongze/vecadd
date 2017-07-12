#include <stdio.h>
#include <stdlib.h>
#define AOCL_ALIGNMENT 64
#define VEC_SIZE 10000
#include "__merlinhead_vec_add_kernel.h"

void vec_add_kernel(int *a, int *b, int*c, int inc);

int main()
{   
    int i=0;
    int inc = 1;
    int * a; 
    int * b; 
    int * c; 
    posix_memalign((void**) (&a), AOCL_ALIGNMENT, 4*VEC_SIZE);
    posix_memalign((void**) (&b), AOCL_ALIGNMENT, 4*VEC_SIZE);
    posix_memalign((void**) (&c), AOCL_ALIGNMENT, 4*VEC_SIZE);
    
    for(i=0; i<VEC_SIZE; i++) {
	a[i] = i;
	b[i] = 2*i;
	c[i] = 1;
    }    
#ifdef ALTERA
    opencl_init("kernel_top.aocx");
#endif
#ifdef XILINX
    opencl_init("kernel_top.xclbin");
#endif
    __merlinwrapper_vec_add_kernel(a,b,c,inc);
//    vec_add_kernel(a, b, c, inc);

    for(i=0; i<VEC_SIZE; i++) {
        if(c[i] != a[i] + b[i] + inc) {
            printf("Test failed\n");
            return 0;
        }
    }    
    printf("Test passed\n");
    return 1;
}


