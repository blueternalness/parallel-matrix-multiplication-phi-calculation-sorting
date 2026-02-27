#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define size 2*1024*1024

// Base Quicksort function used by the threads
void quickSort(int *array, int start, int end) {
    if (start >= end) return;
    
    int pivot = array[start + (end - start) / 2];
    int i = start;
    int j = end;
    
    while (i <= j) {
        while (array[i] < pivot) i++;
        while (array[j] > pivot) j--;
        if (i <= j) {
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }
    
    if (start < j) quickSort(array, start, j);
    if (i < end) quickSort(array, i, end);
}

int main(void) {
    int i;
    struct timespec start, stop; 
    double exe_time;
    srand(time(NULL)); 
    
    int *m = (int *) malloc(sizeof(int) * size);
    for(i = 0; i < size; i++) {
        m[i] = size - i;
        //m[i] = rand(); // Uncomment for random initialization
    }
    
    if (clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime"); }
    
    // OpenMP Quicksort Logic
    int pivot_idx = rand() % size;
    int pivot = m[pivot_idx];
    
    int l = 0;
    int r = size - 1;
    
    // Initial top-level partitioning
    while (l <= r) {
        while (m[l] < pivot) l++;
        while (m[r] > pivot) r--;
        if (l <= r) {
            int temp = m[l];
            m[l] = m[r];
            m[r] = temp;
            l++;
            r--;
        }
    }
    
    int f = l; // The dividing index
    
    // Run 2 threads in parallel using OpenMP sections
    #pragma omp parallel sections num_threads(2)
    {
        #pragma omp section
        {
            if (f - 1 >= 0) quickSort(m, 0, f - 1);
        }
        
        #pragma omp section
        {
            if (f < size) quickSort(m, f, size - 1);
        }
    }
    
    if (clock_gettime(CLOCK_REALTIME, &stop) == -1) { perror("clock gettime"); }       
    exe_time = (stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec) / 1e9;
    
    for(i = 0; i < 16; i++) printf("%d ", m[i]);      
    printf("\nExecution time (OpenMP) = %f sec\n", exe_time);       
    
    free(m);
    return 0;
}