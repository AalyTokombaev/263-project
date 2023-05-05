#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "merge.c"

void printArray(int *arr, int start, int end) {
    for (int i = start; i < end; i++) {
        printf("%d ", arr[i]); 
    }
    printf("\n");
}


void mergeSort(int *arr, int start, int end) {

    //  prints for debugging, I'll keep them here in case I'll need to debug again later.
    /*
    printf("in mergesort\n");
    printf("start: %d, end: %d\n", start, end);
    printf("part arr: ");
    for (int i = start; i < end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("arr: ");
    printArray(arr, 14);
    printf("\n");
    */
    if (start < end) {
        // find the middle and mergesort the left and right
        int middle = start + (end - start) / 2;
        mergeSort(arr, start, middle); 
        mergeSort(arr, middle + 1, end);
        merge(arr, start, middle, end);
    }
}





// I mean merge sort is quote simple
// mergesort interval [p, r]
