#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "merge.c"

void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]); 
    }
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
int main(){
    int arr[14] = {2, 1, 3, 6, 5, 4, 1, 2, 9, 8, 8, 7, 1, 2};

    printf("arr before sort: ");
    printArray(arr, 14);
    printf("\n");

    mergeSort(arr, 0, 13); // 13 because of 0 indexing, I'm so fuckign stupid
    printf("arr after sort: ");
    printArray(arr, 14);
    printf("\n");
    
    return 0;

}


// p: start index, r = end index 
// mergesort interval [p, r]
