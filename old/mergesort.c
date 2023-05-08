#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


void mergeSort(int *arr, int start, int end) {

    if (start < end) {
        // find the middle and mergesort the left and right
        int middle = start + (end - start) / 2;
        mergeSort(arr, start, middle); 
        mergeSort(arr, middle + 1, end);
        merge(arr, start, middle, end);
    }
}





