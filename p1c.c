#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int p = atoi(argv[1]);
    int num_threads = p * p;
    omp_set_num_threads(num_threads);
    int i, j, k;
    struct timespec start, stop; 
    double time;
    int n = 2048; 
    double **A = (double**) malloc (sizeof(double*)*n);
    double **B = (double**) malloc (sizeof(double*)*n);
    double **B_T = (double**) malloc (sizeof(double*)*n); // Transposed B
    double **C = (double**) malloc (sizeof(double*)*n);
    for (i=0; i<n; i++) {
        A[i] = (double*) malloc(sizeof(double)*n);
        B[i] = (double*) malloc(sizeof(double)*n);
        B_T[i] = (double*) malloc(sizeof(double)*n);
        C[i] = (double*) malloc(sizeof(double)*n);
    }
    
    for (i=0; i<n; i++){
        for(j=0; j< n; j++){
            A[i][j]=i;
            B[i][j]=i+j;
            B_T[j][i]=i+j;
            C[i][j]=0;          
        }
    }
            
    if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}
    
    #pragma omp parallel for private(j, k) shared(A, B_T, C, n)
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            double sum = 0;
            for (k = 0; k < n; k++) {
                sum += A[i][k] * B_T[j][k];
            }
            C[i][j] = sum;
        }
    }
    
    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}       
    time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
    
    printf("Threads = %d\n", num_threads);
    printf("Execution time = %f sec\n", time);
    printf("C[100][100]=%f\n", C[100][100]);
    
    for (i=0; i<n; i++) {
        free(A[i]); free(B[i]); free(B_T[i]); free(C[i]);
    }
    free(A); free(B); free(B_T); free(C);
    
    return 0;
}