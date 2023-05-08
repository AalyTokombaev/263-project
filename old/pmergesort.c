#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "pmerge.c"

#define SIZE 16

void pmergeSort(int *arr, int start, int end) {

    if (start < end) {
        // find the middle and mergesort the left and right
        // int middle = start + (end - start) / 2;
        int middle  = start + (end - start)/ 2;
        // int middle = (start + end) / 2;

        // print start middle and end
        // printf("start: %d, middle: %d, end: %d\n", start, middle, end);
        pmergeSort(arr, start, middle);
        pmergeSort(arr, middle + 1, end);
        // parallel region goes here ;) 
        pmerge(arr, start, middle, end);
    }
    
}

// I mean merge sort is quote simple



// p: start index, r = end index 
// mergesort interval [p, r]
