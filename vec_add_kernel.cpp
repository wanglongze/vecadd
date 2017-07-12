#define VEC_SIZE 10000
#define TILE 16
#pragma ACCEL kernel name="vec_add"
void vec_add_kernel(int *a, int *b, int*c, int inc)
{
#pragma ACCEL interface variable=a depth=10000
#pragma ACCEL interface variable=b depth=10000
#pragma ACCEL interface variable=c depth=10000
    int j, j0, jj;
    for (j0 = 0 ;j0 < VEC_SIZE/TILE; j0++) { 
        #pragma ACCEL parallel
        for (jj = 0; jj < TILE; jj++) {
            j = j0 * TILE + jj;
            c[j] = a[j]+b[j]+inc;
        }
    }
}

