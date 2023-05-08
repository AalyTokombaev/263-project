
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "pmerge.c"
#include "pmergesort.c"
#include "merge.c"
#include "mergesort.c"


#define SIZE 16

int main(){
    int arr[SIZE] = {1, 3, 2, 6, 4, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15};

    printf("arr before sort: ");
    printArray(arr, 0, SIZE);
    printf("\n");

    pmergeSort(arr, 0, SIZE - 1); // 13 because of 0 indexing, I'm so fuckign stupid
    printf("this is in main: arr after sort: ");
    printArray(arr, 0, SIZE);
    printf("\n");
    
    return 0;

}