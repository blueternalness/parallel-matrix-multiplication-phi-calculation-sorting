#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define size 2*1024*1024

// Serial Quicksort function
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
    
    // Call Serial Quicksort
    quickSort(m, 0, size - 1);
    
    if (clock_gettime(CLOCK_REALTIME, &stop) == -1) { perror("clock gettime"); }       
    exe_time = (stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec) / 1e9;
    
    for(i = 0; i < 16; i++) printf("%d ", m[i]);      
    printf("\nExecution time (Serial) = %f sec\n", exe_time);       
    
    free(m);
    return 0;
}