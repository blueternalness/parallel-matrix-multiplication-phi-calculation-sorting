#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define MIN(a,b) (((a)<(b))?(a):(b))

int main(int argc, char *argv[]) {
    int p = atoi(argv[1]);
    int num_threads = p * p;
    omp_set_num_threads(num_threads);
    int i, j, k;
    struct timespec start, stop; 
    double time;
    int n = 2048; 
    int b = 8;
    double **A = (double**) malloc (sizeof(double*)*n);
    double **B = (double**) malloc (sizeof(double*)*n);
    double **C = (double**) malloc (sizeof(double*)*n);
    for (i=0; i<n; i++) {
        A[i] = (double*) malloc(sizeof(double)*n);
        B[i] = (double*) malloc(sizeof(double)*n);
        C[i] = (double*) malloc(sizeof(double)*n);
    }
    
    for (i=0; i<n; i++){
        for(j=0; j< n; j++){
            A[i][j]=i;
            B[i][j]=i+j;
            C[i][j]=0;          
        }
    }
            
    if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}
    
    int ii, jj, kk;
    #pragma omp parallel for private(jj, kk, i, j, k) shared(A, B, C, n, b)
    for (ii = 0; ii < n; ii += b) {
        for (jj = 0; jj < n; jj += b) {
            for (kk = 0; kk < n; kk += b) {
                for (i = ii; i < ii + b; i++) {
                    for (j = jj; j < jj + b; j++) {
                        double sum = 0;
                        for (k = kk; k < kk + b; k++) {
                            sum += A[i][k] * B[k][j];
                        }
                        C[i][j] += sum;
                    }
                }
            }
        }
    }       
    
    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}       
    time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
    
    printf("Threads = %d\n", num_threads);
    printf("Execution time = %f sec\n", time);
    printf("C[100][100]=%f\n", C[100][100]);
    
    for (i=0; i<n; i++) {
        free(A[i]); free(B[i]); free(C[i]);
    }
    free(A); free(B); free(C);
    
    return 0;
}